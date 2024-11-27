import numpy as np
import matplotlib.pyplot as plt
def sigmoid(x):
    return 1/(1+np.exp(-x))

class Node():
    def __init__(self, weights, bias) -> None:
        self.weights = np.array(weights)
        self.bias = bias
        self.pre_activation_output = 0

    def calculate(self, inputs):
        inputs = np.array(inputs)
        assert len(inputs) == len(self.weights), "Input and weight lengths must match"
        self.pre_activation_output = np.dot(inputs, self.weights) + self.bias
        return sigmoid(self.pre_activation_output)  # Correct sigmoid formula

class NeuralNet():
    def __init__(self, randInit, layers=None, setLayers=None) -> None:
        if randInit:
            self.layers = []
            weights, biases = self.randomInit(layers)
            for i in range(len(layers) - 1):  # Skip input layer, connect hidden and output layers
                curLayer = []
                for weight, bias in zip(weights[i], biases[i]):  # Iterate over each node's weight/bias
                    curLayer.append(Node(weight, bias))  # Correct the class reference to Node
                self.layers.append(curLayer)
        else:
            self.layers = setLayers

    def randomInit(self, layers):
        weights = []
        biases = []
        for i in range(1, len(layers)):
            # Xavier initialization for weights
            weight_matrix = np.random.randn(layers[i], layers[i-1]) * np.sqrt(1 / layers[i-1])
            bias_vector = np.zeros(layers[i])
            weights.append(weight_matrix)
            biases.append(bias_vector)
        return weights, biases

    def forwardPass(self, xs):
        cur = np.array(xs).copy()
        allOutputs = []
        for layer in self.layers:
            outputs = []
            for node in layer:
                outputs.append(node.calculate(cur))
            cur = np.array(outputs)
            allOutputs.append(cur.copy())  # Store the outputs of the current layer
        return cur

    def mse(self, trueY, xs):
        # assert len(trueY) == len(xs), "Oi, trueY != xs"
        predictions = self.forwardPass(xs)  # Call forward pass properly
        return (1/2) * np.mean((trueY - predictions) ** 2)  # Mean Squared Error across all outputs

    def backpropagate(self, trueY, xs, learning_rate):
        predictions = self.forwardPass(xs)  # Get predictions

        # Initialize gradients for each layer
        gradients = [None] * len(self.layers)

        # Calculate gradients for the output layer
        output_layer_index = len(self.layers) - 1
        gradients[output_layer_index] = np.zeros(len(self.layers[output_layer_index]))

        for k, node in enumerate(self.layers[output_layer_index]):
            # Calculate gradient of loss w.r.t activation of output node
            dL_da = (predictions[k] - trueY[k]) # Mean Squared Error derivative
            da_dz = predictions[k] * (1 - predictions[k])  # Derivative of sigmoid
            gradients[output_layer_index][k] = dL_da * da_dz

            # Update weights and bias for the output layer
            for j in range(len(node.weights)):
                input_value = sigmoid(self.layers[output_layer_index - 1][j].pre_activation_output) if output_layer_index > 0 else xs[j]
                node.weights[j] -= learning_rate * gradients[output_layer_index][k] * input_value
            node.bias -= learning_rate * gradients[output_layer_index][k]

        # Backpropagate to the hidden layers
        for layer_index in reversed(range(output_layer_index)):
            layer = self.layers[layer_index]
            gradients[layer_index] = np.zeros(len(layer))  # Initialize gradient storage

            for j, node in enumerate(layer):
                # Calculate the gradient for the hidden layer node
                dL_da = 0
                for k in range(len(self.layers[layer_index + 1])):
                    next_node = self.layers[layer_index + 1][k]
                    dL_da += gradients[layer_index + 1][k] * next_node.weights[j]

                # Multiply by the derivative of the activation function
                da_dz = sigmoid(node.pre_activation_output) * (1 - sigmoid(node.pre_activation_output))
                gradients[layer_index][j] = dL_da * da_dz

                # Update weights and biases of this one node
                for i in range(len(node.weights)):
                    input_value = xs[i] if layer_index == 0 else sigmoid(self.layers[layer_index - 1][i].pre_activation_output)
                    node.weights[i] -= learning_rate * gradients[layer_index][j] * input_value
                node.bias -= learning_rate * gradients[layer_index][j]

if __name__ == "__main__":
    layers = [1, 2, 1]
    nn = NeuralNet(randInit=True, layers=layers)
    ys = [[0], [1]]
    xs = [[1], [0]]
    epochs = 10000000
    learningRate = 0.001
    totalError = []
    totalTestCase = []
    for epoch in range(epochs):
        for g in range(len(xs)):
            nn.backpropagate(ys[g], xs[g], learningRate)
        if not epoch%10000:
            for k in range(len(xs)):
                curError = nn.mse(ys[k], xs[k])
                totalError.append(curError)
                totalTestCase.append(epoch)
                print(epoch)
    for testCase in range(len(xs)):
        print(xs[testCase])
        print("predictions: ", nn.forwardPass(xs[testCase]))
    plt.plot(totalError, totalTestCase)
    plt.show()