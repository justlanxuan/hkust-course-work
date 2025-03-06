import csv

def load_data(file_path):
    data = []
    with open(file_path, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            # Convert the first 8 values to floats and the 9th value (label) to int
            inputs = list(map(float, row[:-1]))  # Keep sensor readings as floats
            label = int(row[-1])  # Keep label as integer (0 or 1)
            data.append((inputs, label))
    return data

class Perceptron:
    def __init__(self, num_features, learning_rate=1):
        self.weights = [0.0] * (num_features + 1)  # +1 for the bias term
        self.learning_rate = learning_rate

    def predict(self, inputs):
        """Make a prediction based on current weights."""
        activation = sum(w * x for w, x in zip(self.weights, inputs + [1]))
        return 1 if activation >= 0 else 0

    def update_weights(self, inputs, target):
        """Update weights based on prediction error."""
        prediction = self.predict(inputs)
        error = target - prediction
        if error != 0:
            for i in range(len(inputs)):
                self.weights[i] += self.learning_rate * error * inputs[i]
            self.weights[-1] += self.learning_rate * error  # Update the bias

    def train(self, training_data, epochs=10):
        """Train the perceptron using Error-Correction for a number of epochs."""
        for epoch in range(epochs):
            for inputs, label in training_data:
                self.update_weights(inputs, label)
        print(f"Final weights after training: {self.weights}")

# File paths for the training data
east_file = "east.csv"
west_file = "west.csv"
north_file = "north.csv"
south_file = "south.csv"

# Load training data
east_data = load_data(east_file)
west_data = load_data(west_file)
north_data = load_data(north_file)
south_data = load_data(south_file)

# Number of features (sensor readings)
num_features = 8

# Create and train perceptrons
east_perceptron = Perceptron(num_features)
west_perceptron = Perceptron(num_features)
north_perceptron = Perceptron(num_features)
south_perceptron = Perceptron(num_features)

# Train each perceptron
east_perceptron.train(east_data, epochs=10)
west_perceptron.train(west_data, epochs=10)
north_perceptron.train(north_data, epochs=10)
south_perceptron.train(south_data, epochs=10)