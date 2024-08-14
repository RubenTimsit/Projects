from sklearn.base import BaseEstimator,ClassifierMixin
from scipy.spatial.distance import cdist
import numpy as np


class kNN(BaseEstimator, ClassifierMixin):
    def __init__(self, n_neighbors:int = 3):
        self.n_neighbors = n_neighbors
        self.X_train = None
        self.Y_train = None

    def fit(self, X, y):
        self.X_train = np.array(X)
        self.Y_train = np.array(y)
        return self

    def predict(self, X):
        X_test = np.array(X)
        distances = cdist(X_test, self.X_train, metric='euclidean') # Compute distance between each pair in X_test × self.X_train

        # finding the indices of the smallest self.n_neighbors elements from each row of a distances 2D array
        n_neighbors_indices = np.argpartition(distances, self.n_neighbors, axis=1)[:, :self.n_neighbors]
        # for each set of indices in a row, retrieve the corresponding labels from the training set based on those indices
        n_nearest_neighbor_labels = self.Y_train[n_neighbors_indices]
        # for each set of indices in a row, generate a prediction label for the corresponding test set element based on the majority of these labels
        n_nearest_neighbor_labels_sum = np.sum(n_nearest_neighbor_labels, axis=1)
        predictions = np.where(n_nearest_neighbor_labels_sum >= 0, 1, -1)
        return predictions