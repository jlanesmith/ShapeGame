#include <iomanip>
#include <cstring>
#include "orientationCalculations.h"

using namespace std;

const int height = 6, width = 10;
int grid[height][width] = {0};

set<string> solutionCodes;
int numSolutions = 0;

// Each real solution will have four "solutions", since it can be flipped horiztonally and vertically
// Codes are a simplified version of the board
string generateCode(int someGrid[height][width]) {
	string code;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if ((i == height-1) || (someGrid[i][j] != someGrid[i+1][j]))
				code.push_back('1'); // _
			else
				code.push_back('0');
			if ((j == width-1) || (someGrid[i][j] != someGrid[i][j+1]))
				code.push_back('1'); // |
			else
				code.push_back('0');
		}
	}
	return code;
}

// Determine if the solution is a unique solution or whether a flipped version of it has already been found
bool isSolution() {

	string codes[4];
	int someGrid[height][width];
	memcpy(someGrid, grid, height*width*sizeof(int));

	for (int k = 0; k < 2; k++) {

		// Flip horizontally
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width/2; j++) {
				int temp = someGrid[i][j];
				someGrid[i][j] = someGrid[i][width-j-1];
				someGrid[i][width-j-1] = temp;
			}	
		}
		codes[2*k] = generateCode(someGrid);

		// Flip horizontally
		for (int i = 0; i < height/2; i++) {
			for (int j = 0; j < width; j++) {
				int temp = someGrid[i][j];
				someGrid[i][j] = someGrid[height-i-1][j];
				someGrid[height-i-1][j] = temp;
			}	
		}
		codes[2*k+1] = generateCode(someGrid);
	}

	// See if any version of the current solution has already been found
	for (int i = 0; i < 4; i++) {
		if (solutionCodes.find(codes[i]) != solutionCodes.end())
			return false;
	}

	// This is a new solution, so add it to the set of new solutions
	solutionCodes.insert(codes[3]);
	return true;
}

void printBoard() {
	for (int i = 0; i < width; i++)
		cout << " _"; // Print top
	cout << endl;
	for (int i = 0; i < height; i++) {
		cout << "|";
		for (int j = 0; j < width; j++) {
			if ((i == height-1) || (grid[i][j] != grid[i+1][j]))
				cout << "_";
			else
				cout << " ";
			if ((j == width-1) || (grid[i][j] != grid[i][j+1]))
				cout << "|";
			else
				cout << " ";
		}
		cout << endl;
	}	
}

void printGrid() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}


// Checks if the shape will fit in the grid and the position
// Returns how much the shape is shifted to the left (-1 if it doesn't fit)
int checkFit(vector<vector<int>> shape, int x, int y) {
	int shiftFactor = 0;
	while (shape[0][shiftFactor] == 0)
		shiftFactor++;
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (x+i < 0 || x+i >= height || y+j-shiftFactor < 0 || y+j-shiftFactor >= width)
				return -1;			
			if (grid[x+i][y+j-shiftFactor] >= 1 && shape[i][j] == 1)
				return -1;
		}
	}
	return shiftFactor;
}

void addShapeToGrid(vector<vector<int>> shape, int x, int y, int shapeIndex) {
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] == 1)
				grid[x+i][y+j] = shapeIndex;
		}
	}
}

void removeShapeFromGrid(vector<vector<int>> shape, int x, int y) {
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] == 1)
				grid[x+i][y+j] = 0;
		}
	}
}

void addShape(int pos, set<set<vector<vector<int>>>> remainingShapes) {

	if (remainingShapes.size() == 0) { // If all shapes added
		if (isSolution()) {
			cout << "Success! Solution " << ++numSolutions << endl;
			printBoard();
		}
		return;
	}

	while (grid[pos/width][pos%width] >= 1)
		pos++;

	int x = pos/width;
	int y = pos%width;

	for (auto shapeOrientations: remainingShapes) { // For each available shape
		for (auto shape : shapeOrientations) { // For each orientation
			int shiftFactor = checkFit(shape, x, y);
			if (shiftFactor >= 0) {
				addShapeToGrid(shape, x, y-shiftFactor, allShapes.size()+1-remainingShapes.size());
				set<set<vector<vector<int>>>> nextRemainingShapes = remainingShapes;
				nextRemainingShapes.erase(shapeOrientations);
				addShape(pos+1, nextRemainingShapes);
				removeShapeFromGrid(shape, x, y-shiftFactor);
			}
		}
	}
}

int main() 
{
	calculateShapeOrientations();
	addShape(0, allShapes);
	
    cout << "Complete!" << endl;
    return 0;
}
