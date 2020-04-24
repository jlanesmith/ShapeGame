#include <iostream>
#include <vector>
#include <set>

using namespace std;

int grid[3][10] = {0};

const vector<vector<vector<int>>> shapes {
	{{1,1,1,1,1}},
	{{1,1,1,1}, {1,0,0,0}},
	{{1,1,1,1}, {0,1,0,0}},
	{{1,1,1}, {1,0,0}, {1,0,0}},
	{{1,1,1}, {0,1,0}, {0,1,0}},
	{{0,1,1}, {1,1,0}, {1,0,0}},
	{{1,1,0}, {0,1,1}, {0,1,0}},
	{{1,1,1}, {1,0,1}},
	{{1,1,1}, {1,1,0}},
	{{0,1,0}, {1,1,1}, {0,1,0}}
};


vector<vector<int>> rotateShape (vector<vector<int>> origShape) {
	vector<vector<int>> shape;
	cout << "Swapping" << endl;
	// Swap dimensions
	for (int i = 0; i < origShape[0].size(); i++) {
		shape.push_back(vector<int>());
		for (int j = 0; j < origShape.size(); j++) {
			shape[j].push_back(0);
		}
	}
	cout << "Rotating" << endl;
	// Rotate
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			shape[i][j] = origShape[shape[0].size()-1-j][i];
		}
	}
	cout << "Returning" << endl;
	return shape;
}

vector<vector<int>> flipShape (vector<vector<int>> shape) {
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size()/2; j++) {
			int temp = shape[i][j];
			shape[i][j] = shape[i][shape[0].size()-j];
			shape[i][shape[0].size()-j] = temp;
		}	
	}
	return shape;
}

// Return set of possible orientations for the given shape
set<vector<vector<int>>> getOrientations (int shapeIndex) {
	cout << "GetOrientations" << endl;
	vector<vector<int>> shape = shapes[shapeIndex];
	set<vector<vector<int>>> allOrientations;
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "Rotate" << endl;
			shape = rotateShape(shape);
			cout << "Check" << endl;
			if (allOrientations.find(shape) == allOrientations.end())
				allOrientations.insert(shape);
		}
		cout << "Flip" << endl;
		shape = flipShape(shape);
	}
	cout << allOrientations.size() << endl;
	return allOrientations;
};

void addShapes(int shapeProgress) {
	if (shapeProgress == shapes.size())
		return;
	set<vector<vector<int>>> shapeOrientations = getOrientations(shapeProgress);
	for (auto shapeOrientation : shapeOrientations) {
		// Add shape to each possible position and check
		addShapes(shapeProgress+1);		
	}

}

int main() 
{
	//addShapes(0);
	
    cout << "Hello, World!" << endl;
    return 0;
}
