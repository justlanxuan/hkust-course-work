# -*- coding: utf-8 -*-
"""Untitled0.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/1xs6vll9yTYflgQ47XWIcVSw8mWTQqZlD
"""

from google.colab import drive
drive.mount('/content/drive')

import numpy as np

class Perceptron:
    """Represents a perceptron with weights and a threshold."""
    def __init__(self, n_features):
        self.weights = np.random.uniform(-1, 1, n_features)  # Random weights in [-1, 1]
        self.threshold = np.random.uniform(-1, 1)  # Random threshold in [-1, 1]
        self.fitness = 0  # Fitness score

    def predict(self, X):
        """Predicts the output for a given input X."""
        return (np.dot(X, self.weights) >= self.threshold).astype(int)


def fitness(perceptron, X, y):
    """Computes the fitness of a perceptron on the training set."""
    predictions = perceptron.predict(X)
    return np.mean(predictions == y)  # Accuracy


def crossover(parent1, parent2):
    """Performs crossover between two parents to produce two children."""
    i = np.random.randint(1, len(parent1.weights))  # Random crossover point
    child1, child2 = Perceptron(len(parent1.weights)), Perceptron(len(parent1.weights))

    # Create children by swapping weights and thresholds
    child1.weights = np.concatenate([parent1.weights[:i], parent2.weights[i:]])
    child2.weights = np.concatenate([parent2.weights[:i], parent1.weights[i:]])

    # Average the thresholds
    child1.threshold = (parent1.threshold + parent2.threshold) / 2
    child2.threshold = (parent1.threshold + parent2.threshold) / 2

    return child1, child2


def copy_top_k(population, k):
    """Copies the top k perceptrons (based on fitness) to the next generation."""
    population.sort(key=lambda p: p.fitness, reverse=True)
    return population[:k]


def evolve(X, y, population_size=100, max_generations=100, k=10):
    """Runs the genetic algorithm to evolve perceptrons."""
    n_features = X.shape[1]
    population = [Perceptron(n_features) for _ in range(population_size)]  # Initial population

    for generation in range(max_generations):
        # Evaluate fitness
        for perceptron in population:
            perceptron.fitness = fitness(perceptron, X, y)

        # Check stopping condition
        best_fitness = max(p.fitness for p in population)
        if best_fitness >= 0.95:
            print(f"Stopping early at generation {generation} with fitness {best_fitness}")
            break

        # Create new population
        new_population = copy_top_k(population, k)  # Copy top k perceptrons
        while len(new_population) < population_size:
            # Select two parents randomly
            parent1, parent2 = np.random.choice(population, size=2, replace=False)
            # Perform crossover
            child1, child2 = crossover(parent1, parent2)
            new_population.extend([child1, child2])

        population = new_population

    # Return the best perceptron
    population.sort(key=lambda p: p.fitness, reverse=True)
    return population[0]


# Main
if __name__ == "__main__":
    # Load training set
    data = np.loadtxt("/content/drive/MyDrive/Colab Notebooks/gp-training-set.csv", delimiter=",")
    X = data[:, :-1]  # Features
    y = data[:, -1]   # Labels

    # Run genetic algorithm
    best_perceptron = evolve(X, y)
    print("Best Perceptron Weights:", best_perceptron.weights)
    print("Best Perceptron Threshold:", best_perceptron.threshold)
    print("Fitness:", best_perceptron.fitness)