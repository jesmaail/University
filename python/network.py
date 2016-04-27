import tensorflow as tf
import numpy as np
import scipy.ndimage
import sys
import math
from random import randrange
from ale_python_interface import ALEInterface

USE_SDL = True

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

def main():
	if len(sys.argv) < 2:
  		print 'Usage:', sys.argv[0], 'rom_file'
  		sys.exit()

  	global ale
	ale = ALEInterface()
	ale.setInt('random_seed', 123)

	if USE_SDL:
		ale.setBool('sound', False)
		ale.setBool('display_screen', False)

	ale.loadROM(sys.argv[1])

	global legal_actions, action_size
	legal_actions = ale.getLegalActionSet()
	action_size = len(legal_actions)

	for i in range(EPISODE_COUNT):
		agent()


def weight_init(struct):
	structure = tf.truncated_normal(struct, stddev = 0.01)
	return tf.Variable(structure)


def create_conv_layer(input, filter, stride):
	strides = [1, stride, stride, 1]
	return tf.nn.conv2d(input, filter, strides, "SAME")


def perform_random_action():
	return randrange(action_size)


def create_neural_network():
	input_layer = tf.placeholder("float", [None, 84, 84, 1])
	# X = tf.reshape(game_screens, shape=[-1, 84, 84, 1])
	# print X

	first_weights = weight_init(FIRST_FILTER)
	second_layer = tf.nn.relu(create_conv_layer(input_layer, first_weights, FIRST_F_STRIDE))
	# second_layer = tf.nn.relu(create_conv_layer(X, first_weights, FIRST_F_STRIDE))
	# print second_layer

	second_weights = weight_init(SECOND_FILTER)
	third_layer = tf.nn.relu(create_conv_layer(second_layer, second_weights, SECOND_F_STRIDE))
	# print third_layer

	reshape_third = tf.reshape(third_layer, [-1, 484])

	third_weights = weight_init(THIRD_FILTER)
	fourth_layer = tf.nn.relu(tf.matmul(reshape_third, third_weights))
	# print fourth_layer

	fourth_weights = weight_init([256, action_size])
	output_layer = tf.nn.relu(tf.matmul(fourth_layer, fourth_weights))
	# print output_layer

	return np.argmax(output_layer)

def get_screen():
	raw_screen = ale.getScreenGrayscale()
	pp_screen = raw_screen[32:192, :]
	scale_screen = scipy.ndimage.zoom(pp_screen, 0.525, order=0)

	return scale_screen.astype("float32")


def agent():
	#create minibatch
	# screens = []
	global action
	action = 0
	screen = get_screen()
	# screens.append(screen)

	for i in range(EPOCH_COUNT):

		while ale.game_over() == False:
			if randrange(100)+1 < EPSILON:
				action = perform_random_action()
				print "random ", action
			else:
				action = create_neural_network(screen)
				print "network ", action

			reward = ale.act(legal_actions[action])
			#get next screen



			if ale.game_over():
				print "game over"
			#if gameover:
				#terminal flag for transiton

			#add transition to replay memory

			#perform learning



	# values =[1,2,3,4,5,6,7,8,9,10]
	# for value in values:
	# 	print(value)

	# values1 = [x*2 for x in range(10)]


main()