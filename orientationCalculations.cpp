#include "orientationCalculations.h"

set<set<vector<vector<int>>>> allShapes;

// Return the original shape, rotated clockwise by 90 degrees
vector<vector<int>> rotateShape (vector<vector<int>> origShape) {
	vector<vector<int>> shape;
	// Swap dimensions
	for (int i = 0; i < origShape[0].size(); i++) {
		shape.push_back(vector<int>());
		for (int j = 0; j < origShape.size(); j++) {
			shape[i].push_back(0);
		}
	} 
	// Rotate
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			shape[i][j] = origShape[shape[0].size()-1-j][i];
		}
	}
	return shape;
}

// Returns the shape, flipped along the y-axis
vector<vector<int>> flipShape (vector<vector<int>> shape) {
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size()/2; j++) {
			int temp = shape[i][j];
			shape[i][j] = shape[i][shape[0].size()-j-1];
			shape[i][shape[0].size()-j-1] = temp;
		}	
	}
	return shape;
}

// Return set of possible orientations for the given shape
set<vector<vector<int>>> getOrientations (vector<vector<int>> shape) {
	set<vector<vector<int>>> orientations;
	// Rotate 4 times, flip shape, and rotate 4 more times
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			shape = rotateShape(shape);
			if (orientations.find(shape) == orientations.end()) {
				orientations.insert(shape);
			}
		}
		shape = flipShape(shape);
	}
	return orientations;
};

// Calculate all orientations for every shape
void calculateShapeOrientations() {
	for (auto shape: shapes)
		allShapes.insert(getOrientations(shape));
}

// Prints the shape for debugging purposes
void printShape(vector<vector<int>> shape) {
	cout << "Shape rows: " << shape.size() << endl;
	cout << "Shape columns: " << shape[0].size() << endl;
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			cout << shape[i][j];
		}
		cout << endl;
	}
}