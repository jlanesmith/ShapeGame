#include <iostream>
#include <vector>
#include <set>
#include <iomanip>

using namespace std;

int grid[6][10] = {0};
float percentProgress = 0;

const vector<vector<vector<int>>> shapes {
	{{1,1,1,1,1}}, // 2 orientations
	{{1,1,1,1}, {1,0,0,0}}, // 8 orientations
	{{1,1,1,1}, {0,1,0,0}}, // 8 orientations
	{{1,1,1,0}, {0,0,1,1}}, // 8 orientations
	{{1,1,1}, {1,0,0}, {1,0,0}},
	{{1,1,1}, {0,1,0}, {0,1,0}},
	{{0,1,1}, {1,1,0}, {1,0,0}},
	{{1,1,0}, {0,1,1}, {0,1,0}},
	{{1,1,1}, {1,0,1}},
	{{1,1,1}, {1,1,0}},
	{{0,1,0}, {1,1,1}, {0,1,0}},
	{{0,1,1}, {0,1,0}, {1,1,0}}
};

vector<set<vector<vector<int>>>> allOrientations;

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
set<vector<vector<int>>> getOrientations (int shapeIndex) {
	vector<vector<int>> shape = shapes[shapeIndex];
	set<vector<vector<int>>> orientations;
	// Rotate 4 times, flip shape, and rotate 4 more times
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			shape = rotateShape(shape);
			if (orientations.find(shape) == orientations.end())
				orientations.insert(shape);
		}
		shape = flipShape(shape);
	}
	return orientations;
};

// Calculate all orientations for every shape
void calculateShapeOrientations() {
	for (int i = 0; i < shapes.size(); i++)
		allOrientations.push_back(getOrientations(i));
}

// Prints the shape for debugging purposes
void printShape(vector<vector<int>> shape) {
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			cout << shape[i][j];
		}
		cout << endl;
	}
}

// Add shapes in order of each shape
void addShapes(int shapeIndex) {
	if (shapeIndex == 4) {
		percentProgress += (100.0/(2*8*8*8));
		cout << fixed << setprecision(2) << percentProgress << endl;
	}
	if (shapeIndex == shapes.size())
		return;
	for (auto orientation : allOrientations[shapeIndex]) {

		// Add shape to each possible position and check

		addShapes(shapeIndex+1);		
	}

}

int main() 
{

	calculateShapeOrientations();
	addShapes(0);
	
    cout << "Complete!" << endl;
    return 0;
}
