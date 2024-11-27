from NN import Node
from NN import sigmoid
from NN import NeuralNet
import numpy as np
import copy
import time
import random
import statistics

def show(net):
    layers = []
    nodes = []
    node = []
    for i in net.layers:
        for g in i:
            nodes.append([[float(k) for k in g.weights], float(g.bias)])
        layers.append(nodes[:])
        nodes = []
    return layers

class snakeNN(NeuralNet):
    def mutate(self, stepSize):
        mutatedNN = []
        for layer in range(len(self.layers)):
            for node in range(len(self.layers[layer])):
                for weight in range(len(self.layers[layer][node].weights)):
                    self.layers[layer][node].weights[weight] += stepSize
                    mutatedNN.append(copy.deepcopy(self))
                    self.layers[layer][node].weights[weight] -= 2*stepSize
                    mutatedNN.append(copy.deepcopy(self))
                    self.layers[layer][node].weights[weight] += stepSize
                self.layers[layer][node].bias += stepSize
                mutatedNN.append(copy.deepcopy(self))
                self.layers[layer][node].bias -= 2*stepSize
                mutatedNN.append(copy.deepcopy(self))
                self.layers[layer][node].bias += stepSize
        return mutatedNN
def find_head_position(state, head_value=2):  # Assuming 2 represents the head
    for i, row in enumerate(state):
        for j, cell in enumerate(row):
            if cell == head_value:
                return (i, j)  # Return the coordinates as a tuple
    return False  # If head not found
def increment_body_segments(state):
    for row in state:
        for i in range(len(row)):
            if row[i] > 0 and row[i] != -9:  # Check if the cell is part of the snake's body or head
                row[i] += 1  # Increment the segment value by 1
def place_apple(state, thing):
    # Find all empty cells (represented by 0)
    empty_cells = []
    for row in range(len(state)):
        for col in range(len(state[0])):
            if state[row][col] == 0:
                empty_cells.append((row, col))
    
    # Place the apple randomly in an empty cell if there are any
    if empty_cells:
        apple_pos = random.choice(empty_cells)
        state[apple_pos[0]][apple_pos[1]] = thing  # Set the apple position to 3
def updateState(state, direction, apple=False):
    # Define movement directions
    directions = {0: (-1, 0), 1: (0, 1), 2: (1, 0), 3: (0, -1)}
    dx, dy = directions[direction]
    rows = len(state)
    cols = len(state[0])
    # Locate the head of the snake (marked as 99)
    head_pos = find_head_position(state, 99)
    if not head_pos: return "Oi there ain't no head"
    head_row, head_col = head_pos # Extract row and col of the head
    # Calculate the new head position
    new_head_row, new_head_col = head_row + dx, head_col + dy
    # Check for boundary or self-collision
    if not (0 <= new_head_row and new_head_row < rows and 0 <= new_head_col and new_head_col < cols):
        return "COLLISION!!"
    if state[new_head_row][new_head_col] > 0 and state[new_head_row][new_head_col] != -9:
        return "HIT YOURSELF"
    # Check if the snake eats the apple
    apple_eaten = state[new_head_row][new_head_col] == -9
    increment_body_segments(state)

    # Set the new head position to 1 (freshly moved head)
    state[new_head_row][new_head_col] = 99

    # If the apple is eaten, mark apple_eaten and regenerate it elsewhere
    if apple_eaten:
        place_apple(state, -9)
    elif any(100 in sublist for sublist in state):
        # Remove the tail if the snake did not eat an apple
        tail_pos = np.argwhere(state == np.max(state))
        if len(tail_pos) > 0:
            tail_row, tail_col = tail_pos[0]
            state[tail_row][tail_col] = 0

    # Update the new head position (set as 99, the head marker)
    state[new_head_row][new_head_col] = 99
    return (state, apple_eaten)


test = snakeNN(True, [10, 10, 4])
def printState(state):
    for i in state: 
        print(i)
def playNet(Network, x):
    score = 5
    state = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
    place_apple(state, -9)
    place_apple(state, 99)
    apple = 0
    for i in range(50):
        if apple:
            score += 10
        if score<0:
            break
        if x: printState(state)
        input = []
        for row in range(len(state)):
            for square in range(len(state[0])):
                input.append(state[row][square])
        input.append(apple)
        prediction = Network.forwardPass(input)
        move = max([0, 1, 2, 3], key=lambda x:prediction[x])
        if x: print(move)
        newState = updateState(state, move, apple)
        if type(newState) != str:
            state, apple = newState
        else:
            break
    return score
epochs = 200
newBest = test
tic = time.perf_counter()
for i in range(epochs):
    if not i%20:
        playNet(newBest, True)
    mutations = newBest.mutate(10000)
    mutations.append(newBest)
    newBest = max(mutations, key=lambda x:((playNet(x, False) + playNet(x, False) + playNet(x, False) + playNet(x, False) +playNet(x, False))))
    # print(show(max(test.mutate(0.1), key=lambda x:testNet(x))))
    toc = time.perf_counter()
    print((epochs/(i+1))*(toc-tic)-(toc-tic), "Seconds remaining.")
print(f"It is finished after:{toc - tic} seconds")
print("FINAL Big Mutation")
playNet(newBest, True)

tic = time.perf_counter()
for i in range(epochs):
    if not i%20:
        playNet(newBest, True)
    mutations = newBest.mutate(((epochs-i)/10)*3+0.1)
    mutations.append(newBest)
    newBest = max(mutations, key=lambda x:((playNet(x, False) + playNet(x, False) + playNet(x, False) + playNet(x, False) +playNet(x, False))))
    # print(show(max(test.mutate(0.1), key=lambda x:testNet(x))))
    toc = time.perf_counter()
    print((epochs/(i+1))*(toc-tic)-(toc-tic), "Seconds remaining.")
print(f"It is finished after:{toc - tic} seconds")
print("FINAL")
playNet(newBest, True)

# test.mutate(0.1)
# print("yay")