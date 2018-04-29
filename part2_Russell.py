#Part 2
# Created by Scott Russell
#CS 434: Spring 2018

#Used https://machinelearningmastery.com/implement-decision-tree-algorithm-scratch-python/
# as a resource For Code Blocks specific to decision tree algorithm implementation
import csv
import math
import numpy as np
#using genfromtxt to store data in array form
from numpy import genfromtxt

#define MAX Depth of tree (can be less depending if no gain is found)
TREE_DEPTH = 6
ABSOLUTES = [-1.0, 1.0]


# Splits data, depending on where the row[index] is valued at.
def split_Data(index, value, data):	
	left, right = list(), list()
	for row in data:
		if row[index] < value:
			left.append(row)
		else:
			right.append(row)
	return left, right


	#Evaluates which split would benefit the most for each data set
def getBestSplit(data):
	bestIndex, bestValue, bestScore, bestGroups = 100, 100, 100, None
    # All the columns
	for i in range(len(data[0]) - 1):
		# All the rows
		for row in data:
			groups = split_Data(i, row[i], data)
			gini = giniCalculation(groups)
			if gini < bestScore:
				bestIndex, bestValue, bestScore, bestGroups = i, row[i], gini, groups

	return {"index": bestIndex, "value": bestValue, "groups": bestGroups, "infoGain": bestScore}

	#Majority Calculation
def setMajorityClass(section):
	majority = [row[-1] for row in section]
	return max(set(majority), key=majority.count)

	
	
	
	
	
	
	

#Calculates Guess vs Correct Probability
def errorCalculation(tree, data):	
	#loops through testing ratio of Guesses to Correct Result
	correct = 0
	for row in data:
		guess = leftOrRight(tree, row)
		if guess == row[-1]:
			correct += 1
	return 1 - (float(correct) / len(data))

	
#builds the tree Recurssively
#(using DepthMAX to prevent from overbuilding and to work with Stump)
def buildTree(node, depthTracker, depthMAX, sizeMIN):
	#Build Tree through Recurssion
	left, right = node["groups"]
	del(node["groups"])
	# Check if there's no split
	if not left or not right:
		node["left"] = node["right"] = setMajorityClass(left + right)
		return
    # if at max depth, force stop to prevent digging furthur
	if depthMAX <= depthTracker:
		node["left"], node["right"] = setMajorityClass(left), setMajorityClass(right)
		return
    # left side check
	if len(left) <= sizeMIN:
		node["left"] = setMajorityClass(left)
	else:
		node["left"] = getBestSplit(left)
		buildTree(node["left"], depthTracker + 1, depthMAX, sizeMIN)
	# right side check
	if len(right) <= sizeMIN:
		node["right"] = setMajorityClass(right)
	else:
		node["right"] = getBestSplit(right)
		buildTree(node["right"], depthTracker + 1, depthMAX, sizeMIN)

#used for gini Calculation, see source
def giniCalculation(sections):
	#See https://machinelearningmastery.com/implement-decision-tree-algorithm-scratch-python/
	# for algorithm specifics
	gini = 0.0
	for value in ABSOLUTES:
		for section in sections:
			sectionSize = len(section)
			if sectionSize == 0:
				continue
			ratio = [classRow[-1] for classRow in section].count(value) / float(sectionSize)
			gini += (ratio * (1.0 - ratio))
	return gini

	
#loops through testing ratio of Guesses to Correct Result
def errorCalculation(tree, data):		
	correct = 0
	for row in data:
		guess = leftOrRight(tree, row)
		if guess == row[-1]:
			correct += 1
	return 1 - (float(correct) / len(data))


#Prediciton of Left Or Right.
def leftOrRight(treeBranch, row):
	#recursive call to predict Left Or Right
	if row[treeBranch["index"]] < treeBranch["value"]:
		if isinstance(treeBranch["left"], dict):
			return leftOrRight(treeBranch["left"], row)
		else:
			return treeBranch["left"]
	else:
		if isinstance(treeBranch["right"], dict):
			return leftOrRight(treeBranch["right"], row)
		else:
			return treeBranch["right"]		
			
#print tree algorithm, see link for source of creation			
def printTree(treeBranch, depth = 0):
   #http://machinelearningmastery.com/implement-decision-tree-algorithm-scratch-python/
  #  @param treeBranch: The decision tree node
  #  @param depth: Current depth
	if isinstance(treeBranch, dict):
		print "%s{X%d = %.4f}" % ((depth*str(depth), (treeBranch["index"] + 1), treeBranch["value"]))
		printTree(treeBranch["left"], depth + 1)
		printTree(treeBranch["right"], depth + 1)
	else:
		print "%s{%s}" % ((depth * "*", treeBranch))


	
#prints out the Depth and gain at each level
def ganiGainPrint(treeBranch, depth=0):
	#iterates and prints out entire gini (see source)
	if isinstance(treeBranch, dict):
		print "Current Depth: " + str(depth)
		print "Information Gain(Reduction in Entropy) : " + str(treeBranch["infoGain"])
		ganiGainPrint(treeBranch["left"], depth + 1)
		ganiGainPrint(treeBranch["right"], depth + 1)


#calling program, initiates input for data stream + normalize functions.
def main():
	#using genfromtxt we are easily get the entire data stream from test/train
	testing_data = genfromtxt ('knn_test.csv', delimiter=',')
	training_data = genfromtxt('knn_train.csv', delimiter=',')
	
	#apply data to x/y axis for both test/training sets
	#31 elements in each row (for x row count)
	x_training = np.array(training_data[:,1:31])
	y_training = np.array(training_data[:,0:1])
	x_testing = np.array(testing_data[:,1:31])
	y_testing = np.array(testing_data[:,0:1])

	#normalization formula: y = (x-min) / (max-min)	
	#normalize dataset (first we normalize x axis on each, then compute entire data set normalization)
	x_training /= x_training.sum(axis=1)[:,np.newaxis]
	x_testing /= x_testing.sum(axis=1)[:,np.newaxis]
	normalized_Training = np.append(x_training,y_training, axis=1)
	normalized_Testing = np.append(x_testing, y_testing, axis=1)
	
	#Decision Stump Call 
	tree = getBestSplit(normalized_Training)
	buildTree(tree, 1, 1, 10)
	print "Data for Stump:"
	print_Results(tree, normalized_Testing, normalized_Training)
	
	#Decision tree with Depth of 6	
	tree = getBestSplit(normalized_Training)
	buildTree(tree, 1, TREE_DEPTH, 10)
	print "Data for Tree: Depth up to " + str(TREE_DEPTH)
	print_Results(tree, normalized_Testing, normalized_Training)
	
# prints out results, Both the Tree itself, the Gain for each
# Depth calculation and the Training/Testing Erros for both the Stump and Tree
def print_Results(tree, normalized_Testing,normalized_Training):
	printTree(tree)
	ganiGainPrint(tree)

	print "Train Error: " + str(errorCalculation(tree, normalized_Training))
	print "Test Error: " + str(errorCalculation(tree, normalized_Testing))
	print "\n"
	
#in case of improper call, call main
if __name__ == '__main__':
	main()

