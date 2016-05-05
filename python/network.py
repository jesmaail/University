import tensorflow as tf
import numpy as np
import scipy.ndimage
import sys
import random
import math
from random import randrange
from ale_python_interface import ALEInterface
from collections import deque

USE_SDL = True
DISP_SCREEN = True
PLAY_SOUND = False

EPOCH_COUNT = 1
EPISODE_COUNT = 1

START_EPSILON = 99
FINAL_EPSILON = 1

MINIBATCH_SIZE = 16

INITIAL_RUN = 17

IMAGE_COUNT = 2
INPUT_X = 160
INPUT_Y = 210
DESIRED_XY = 84
ROI_TOP = 32
ROI_BOT = 18

FIRST_F_SIZE = 8
FIRST_F_COUNT = 2
FIRST_F_STRIDE = 4

FIRST_FILTER = [8, 8, 2, 2]

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
	ph_in = tf.placeholder(tf.float32, shape=(None, 84, 84, 2))#[None, 84, 84, 2]) #84*84
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

sess.run(tf.initialize_all_variables())



global action
action = 0
state = []
next_state = []
count =0
epsilon = START_EPSILON

screen = get_screen()
screen = np.reshape(screen, (84, 84))

ale.act(legal_actions[0])
screen2 = get_screen()
screen2 = np.reshape(screen2, (84, 84))

screens = np.stack((screen, screen2), axis=2)

next_state.append(screens)




for i in range(EPOCH_COUNT):

	state = next_state

	net_result = net_out.eval(feed_dict={net_in : state})

	while ale.game_over() == False:
		if randrange(100)+1 < epsilon:
			action = perform_random_action()
			print "r:", action
		else:
			#net_out = run_network(screen, weights)
			action = np.argmax(net_result)
			print "n:", action

		if epsilon > FINAL_EPSILON:
			epsilon -= 0.01

		reward = ale.act(legal_actions[action])

		screen = get_screen()
		screen = np.reshape(screen, (84, 84))

		ale.act(legal_actions[0])
		screen2 = get_screen()
		screen2 = np.reshape(screen2, (84, 84))

		screens = np.stack((screen, screen2), axis=2)

		next_state.append(screens)

		terminal = ale.game_over()

		if ale.game_over():
			print "game over"

		replay_mem.append((state, action, reward, next_state, terminal))

		count += 1

		if count > INITIAL_RUN:
			minibatch = random.sample(replay_mem, 16)

			state_train = [d[0] for d in minibatch]
			action_train = [d[1] for d in minibatch]
			reward_train = [d[2] for d in minibatch]
			next_train = [d[3] for d in minibatch]

			y_batch_val = []

			batch_run = net_out.eval(feed_dict={net_in : next_train})

			for i in range(0, len(minibatch)):
				terminal = minibatch[i][4]

				if terminal:
					y_batch_val.append(reward_train[i])
				else:
					y_batch_val.append(reward_train[i] + 0.99 ++ np.max(batch_run[i]))