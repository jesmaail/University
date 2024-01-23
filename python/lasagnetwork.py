import lasagne
import theano
import theano.tensor as T
from lasagne.nonlinearities import rectify

input_var = T.tensor4('states')
action = T.col('actions')
reward = T.col('rewards')
next = T.col('next')
terminal = T.col('terminal')
target_var = T.ivector('y')

network = lasagne.layers.InputLayer((None, 1, 84, 84), input_var)
network = lasagne.layers.Conv2DLayer(network, 2, (20, 20), nonlinearity=rectify)
network = lasagne.layers.Conv2DLayer(network, 4, (9, 9), nonlinearity=rectify)
network = lasagne.layers.DenseLayer(network, 256, nonlinearity=rectify)
network = lasagne.layers.DenseLayer(network, 18)

prediction = lasagne.layers.get_output(network)

loss = lasagne.objectives.squared_error(prediction, target_var)
loss = loss.mean() + 1e-4 * lasagne.regularization.regularize_network_params(
        network, lasagne.regularization.l2)

params = lasagne.layers.get_all_params(network, trainable=True)
updates = lasagne.updates.rmsprop(loss, params, learning_rate=0.99)


train_fn = theano.function([input_var, target_var], loss, updates=updates)

# train network (assuming you've got some training data in numpy arrays)
for epoch in range(5):
    loss = 0
    for input_batch, target_batch in training_data:
        loss += train_fn(input_batch, target_batch)
    print("Epoch %d: Loss %g" % (epoch + 1, loss / len(training_data)))

# use trained network for predictions
test_prediction = lasagne.layers.get_output(network, deterministic=True)
predict_fn = theano.function([input_var], T.argmax(test_prediction, axis=1))
print("Predicted class for first test input: %r" % predict_fn(test_data[0]))