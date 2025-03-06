# reactiveAgents.py
# ---------------
# Licensing Information: You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC
# Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).
from game import Directions
from game import Agent
from game import Actions
import util
import time
import search


class NaiveAgent(Agent):
    "An agent that goes West until it can't."

    def getAction(self, state):
        "The agent receives a GameState (defined in pacman.py)."
        sense = state.getPacmanSensor()
        if sense[7]:
            action = Directions.STOP
        else:
            action = Directions.WEST
        return action

class PSAgent(Agent):
    "An agent that follows the boundary using production system."

    def getAction(self, state):
        sense = state.getPacmanSensor()
        x = [sense[1] or sense[2] , sense[3] or sense[4] ,
        sense[5] or sense[6] , sense[7] or sense[0]]
        if x[0] and not x[1]:
            action = Directions.EAST
        elif x[1] and not x[2]:
            action = Directions.SOUTH
        elif x[2] and not x[3]:
            action = Directions.WEST
        elif x[3] and not x[0]:
            action = Directions.NORTH
        else:
            action = Directions.NORTH
        return action

class ECAgent(Agent):
    "An agent that follows the boundary using error-correction."
    def __init__(self):
        """
        Initialize the agent with the trained perceptron weights for each direction.
        """
        # Trained weights for each direction
        self.weights = {
            "east": [0.0, 1.0, 1.0, -2.0, -2.0, 0.0, 0.0, 0.0, -1.0],
            "west": [-2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, -2.0, -1.0],
            "north": [1.0, -2.0, -2.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0],
            "south": [0.0, 0.0, 0.0, 1.0, 1.0, -2.0, -2.0, 0.0, -1.0],
        }

    def perceptron(self, inputs, weights):
        activation = sum(w * x for w, x in zip(weights[:-1], inputs)) + weights[-1]  # Add bias
        return 1 if activation >= 0 else 0

    def getAction(self, state):

        # Get Pacman's current sensor readings (8 sensor inputs)
        sense = state.getPacmanSensor()

        # Compute the perceptron outputs for each direction
        outputs = {
            "north": self.perceptron(sense, self.weights["north"]),
            "east": self.perceptron(sense, self.weights["east"]),
            "south": self.perceptron(sense, self.weights["south"]),
            "west": self.perceptron(sense, self.weights["west"]),
        }

        # Determine which directions have output 1
        active_directions = [direction for direction, output in outputs.items() if output == 1]

        # Decision logic
        if len(active_directions) == 1:
            # If exactly one perceptron outputs 1, choose that direction
            return getattr(Directions, active_directions[0].upper())
        elif len(active_directions) > 1:
            # If more than one perceptron outputs 1, follow the priority order
            for direction in ["north", "east", "south", "west"]:
                if direction in active_directions:
                    return getattr(Directions, direction.upper())
        else:
            # If no perceptron outputs 1, default to north
            return Directions.NORTH

class SMAgent(Agent):
    "A sensory-impaired agent that follows the boundary using a state machine."

    def registerInitialState(self, state):
        """
        Initialize the agent's state and previous action.
        The agent receives the initial GameState (defined in pacman.py).
        """
        # Get the initial sensory input (limited to 4 directions: North, East, South, West)
        sense = state.getPacmanImpairedSensor()
        self.prevAction = Directions.STOP  # Initially, Pacman is not moving
        self.prevSense = sense  # Store the initial sensor readings

    def getAction(self, state):
        """
        Determine Pacman's action based on impaired sensor readings and the state machine.
        """
        # Get impaired sensor readings (limited to 4 directions: North, East, South, West)
        sense = state.getPacmanImpairedSensor()

        # Decision logic based on the state machine
        if self.prevAction == Directions.NORTH:
            if sense[0]:  # Wall in front (North)
                action = Directions.EAST  # Turn clockwise
            else:
                action = Directions.NORTH  # Continue moving North
        elif self.prevAction == Directions.EAST:
            if sense[1]:  # Wall in front (East)
                action = Directions.SOUTH  # Turn clockwise
            else:
                action = Directions.EAST  # Continue moving East
        elif self.prevAction == Directions.SOUTH:
            if sense[2]:  # Wall in front (South)
                action = Directions.WEST  # Turn clockwise
            else:
                action = Directions.SOUTH  # Continue moving South
        elif self.prevAction == Directions.WEST:
            if sense[3]:  # Wall in front (West)
                action = Directions.NORTH  # Turn clockwise
            else:
                action = Directions.WEST  # Continue moving West
        else:
            # Default to NORTH if no previous action is available
            action = Directions.NORTH

        # Update the agent's state
        self.prevSense = sense  # Update previous sensory input
        self.prevAction = action  # Update previous action

        return action