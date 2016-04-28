import tensorflow as tf
import numpy as np
import scipy.ndimage
import sys
import math
from random import randrange
from ale_python_interface import ALEInterface
from collections import deque

USE_SDL = True
DISP_SCREEN = False
PLAY_SOUND = False

EPOCH_COUNT = 1
EPISODE_COUNT = 1
EPSILON = 90

IMAGE_COUNT = 2
INPUT_X = 160
INPUT_Y = 210
DESIRED_XY = 84
ROI_TOP = 32
ROI_BOT = 18

FIRST_F_SIZE = 8
FIRST_F_COUNT = 2
FIRST_F_STRIDE = 4

FIRST_FILTER = [8, 8, 1, 2]

SECOND_F_SIZE = 4
SECOND_F_COUNT = 2
SECOND_F_STRIDE = 2

SECOND_FILTER = [4, 4, 2, 4]

THIRD_FILTER = [484, 256]

FIRST_L_SIZE = 84
SECOND_L_SIZE = 20
THIRD_L_SIZE = 9
FOURTH_L_SIZE = 256


def conv_layer(input, filter, stride):
	return tf.nn.relu(tf.nn.conv2d(input, filter, [1, stride, stride, 1], "SAME"))

def full_conn_layer(input, filter):
	return tf.nn.relu(tf.matmul(input, filter))


def init_network():
	#weights = init_weights()
	ph_in = tf.placeholder(tf.float32, [None, 84, 84, 1]) #84*84
	second_layer = conv_layer(ph_in, weights['w1'], FIRST_F_STRIDE)
	third_layer = conv_layer(second_layer, weights['w2'], SECOND_F_STRIDE)
	third_reshape = tf.reshape(third_layer, [-1, 484])
	fourth_layer = full_conn_layer(third_reshape, weights['w3'])
	output_layer = tf.matmul(fourth_layer, weights['w4'])
	return ph_in, output_layer


def perform_random_action():
	return randrange(action_size)


def get_screen():
	raw_screen = ale.getScreenGrayscale()
	pp_screen = raw_screen[32:192, :]
	scale_screen = scipy.ndimage.zoom(pp_screen, 0.525, order=0)

	return scale_screen.astype("float32")



if len(sys.argv) < 2:
	print 'Usage:', sys.argv[0], 'rom_file'
	sys.exit()

global ale
ale = ALEInterface()
ale.setInt('random_seed', 123)

if USE_SDL:
	ale.setBool('sound', PLAY_SOUND)
	ale.setBool('display_screen', DISP_SCREEN)

ale.loadROM(sys.argv[1])

global legal_actions, action_size
legal_actions = ale.getLegalActionSet()
action_size = len(legal_actions)

global replay_mem
replay_mem = deque()

weights ={
	'w1' : tf.Variable(tf.random_normal(FIRST_FILTER)),
	'w2' : tf.Variable(tf.random_normal(SECOND_FILTER)),
	'w3' : tf.Variable(tf.random_normal(THIRD_FILTER)),
	'w4' : tf.Variable(tf.random_normal([256, action_size]))
}


sess = tf.InteractiveSession()
net_in, net_out = init_network()

ph_out = tf.placeholder(tf.float32, [None, action_size])
ph_target = tf.placeholder(tf.float32, [None])

action_choice = tf.reduce_sum(tf.mul(net_out, ph_out), reduction_indices = 1)
cost = tf.reduce_mean(tf.square(ph_target - action_choice))
optimizer = tf.train.RMSPropOptimizer(0.99).minimize(cost)

# init = tf.initialise_all_variables()


global action
action = 0
screen = get_screen()
screen = np.reshape(screen, (1, 84, 84))
ale.act(legal_actions[0])
screen2 = get_screen()
screen2 = np.reshape(screen2, (1, 84, 84))

# state = [screen, screeneen2]
state = [[[]]]
state.append(screen)



for i in range(EPOCH_COUNT):

	#input_img = tf.convert_to_tensor(screens)

	net_result = net_out.eval(feed_dict={net_in : screen})

	while ale.game_over() == False:
		if randrange(100)+1 < EPSILON:
			action = perform_random_action()
			#print "r:", action
		else:
			#net_out = run_network(screen, weights)
			#action = np.argmax(net_out)
			print "n:", action

		reward = ale.act(legal_actions[action])

		next_screen = get_screen()
		terminal = ale.game_over()

		if ale.game_over():
			print "game over"

		replay_mem.append((screen, action, reward, next_screen, terminal))