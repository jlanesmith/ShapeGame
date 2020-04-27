// 2339 Solutions

#include <iomanip>
#include <cstring>
#include <fstream>
#include <time.h>
#include "orientationCalculations.h"

using namespace std;

const int height = 6, width = 10;
int grid[height][width] = {0};
int testGrid[height][width]; // For isSolution() and isBadAlgorithm()
set<set<vector<vector<int>>>> shapesUsedInCorner;

set<string> solutionCodes;
int numSolutions = 0;

ofstream myFile("solutions.txt");

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
	memcpy(testGrid, grid, height*width*sizeof(int));

	for (int k = 0; k < 2; k++) {

		// Flip horizontally
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width/2; j++) {
				int temp = testGrid[i][j];
				testGrid[i][j] = testGrid[i][width-j-1];
				testGrid[i][width-j-1] = temp;
			}	
		}
		codes[2*k] = generateCode(testGrid);

		// Flip horizontally
		for (int i = 0; i < height/2; i++) {
			for (int j = 0; j < width; j++) {
				int temp = testGrid[i][j];
				testGrid[i][j] = testGrid[height-i-1][j];
				testGrid[height-i-1][j] = temp;
			}	
		}
		codes[2*k+1] = generateCode(testGrid);
	}

	// See if any version of the current solution has already been found
	for (int i = 0; i < 4; i++) {
		if (solutionCodes.find(codes[i]) != solutionCodes.end())
			return false;
	}

	// This is a new solution, so add it to the set of new solutions
	solutionCodes.insert(codes[3]);
	numSolutions++;
	return true;
}

void printSolution(ostream& out) {
	out << "Solution " << numSolutions << endl;
	for (int i = 0; i < width; i++)
		out << " _"; // Print top
	out << endl;
	for (int i = 0; i < height; i++) {
		out << "|";
		for (int j = 0; j < width; j++) {
			if ((i == height-1) || (grid[i][j] != grid[i+1][j]))
				out << "_";
			else
				out << " ";
			if ((j == width-1) || (grid[i][j] != grid[i][j+1]))
				out << "|";
			else
				out << " ";
		}
		out << endl;
	}
	out << endl;
}

void printGrid() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

// Recursive function, used to find amount of connected empty space for isSpaceNotMultipleOfFive()
int recurseEmpty(int x, int y) {
	if (x<0 || x>=height || y<0 || y>=width || testGrid[x][y] != 0)
		return 0;
	testGrid[x][y] = 1;
	return 1 + recurseEmpty(x+1,y) + recurseEmpty(x-1,y) + recurseEmpty(x,y+1) + recurseEmpty(x,y-1);
}

// Additional optimization, determing if the areas of remaining space are multiples of 5 or not
bool isSpaceNotMultipleOfFive(int numRemShapes) {

	memcpy(testGrid, grid, height*width*sizeof(int));

	int numEmpty = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (testGrid[i][j] == 0) {
				numEmpty = recurseEmpty(i,j);
				if (numEmpty % 5 != 0) // If the empty space isn't divisible by 5, it's impossible for shapes to fit in it
					return true;
				if (numEmpty == numRemShapes*5) // If the empty space is all of the empty space, there's no more empty space
					return false;
			}
		}
	}
	return false;
}

void removeShapeFromGrid(vector<vector<int>> shape, int x, int y) {
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] == 1)
				grid[x+i][y+j] = 0;
		}
	}
}

bool isCorner(int x, int y) {
	return ((x==0 || x==height-1) && (y==0 || y==width-1));
}

// Checks if the shape will fit in the grid and the position
// Returns how much the shape is shifted to the left (-1 if it doesn't fit)
int checkFitAddShape(vector<vector<int>> shape, int x, int y, int numRemShapes, bool alreadyUsed) {
	int shiftFactor = 0;
	while (shape[0][shiftFactor] == 0)
		shiftFactor++;
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (x+i < 0 || x+i >= height || y+j-shiftFactor < 0 || y+j-shiftFactor >= width) // If it's out of bounds
				return -1;			
			if (grid[x+i][y+j-shiftFactor] >= 1 && shape[i][j] == 1) // If a shape is already there
				return -1;
			// If the shape has already been used in the initial corner, all solutions with it in any corner have been found
			if (shape[i][j] == 1 && alreadyUsed && isCorner(x+i, y+j-shiftFactor)) {// Additional optimization
				return -1;
			}
		}
	}

	// Add shape
	y -= shiftFactor;
	int shapeIndex = allShapes.size()+1-numRemShapes;
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] == 1)
				grid[x+i][y+j] = shapeIndex;
		}
	}

	if (isSpaceNotMultipleOfFive(numRemShapes)) { // Additional optimization 
		removeShapeFromGrid(shape, x, y);
		return -1;
	}
	
	return shiftFactor;
}

void addShape(int pos, set<set<vector<vector<int>>>> remainingShapes) {

	if (remainingShapes.size() == 0) { // If all shapes added
		if (isSolution()) {
			printSolution(cout);
			printSolution(myFile);
		}
		return;
	}

	while (grid[pos/width][pos%width] >= 1)
		pos++;

	int x = pos/width;
	int y = pos%width;

	for (auto shapeOrientations: remainingShapes) { // For each available shape
		// Check if shape has been used in corner already
		bool alreadyUsed = (shapesUsedInCorner.find(shapeOrientations) != shapesUsedInCorner.end());
		for (auto shape : shapeOrientations) { // For each orientation
			int shiftFactor = checkFitAddShape(shape, x, y, remainingShapes.size(), alreadyUsed);
			if (shiftFactor >= 0) {
				set<set<vector<vector<int>>>> nextRemainingShapes = remainingShapes;
				nextRemainingShapes.erase(shapeOrientations);
				addShape(pos+1, nextRemainingShapes);
				removeShapeFromGrid(shape, x, y-shiftFactor);
			}
		}
		if (pos == 0) { // Additional optimization, if in initial corner
			shapesUsedInCorner.insert(shapeOrientations);
			if (allShapes.size() - shapesUsedInCorner.size() < 4)
				return; // All other solutions will have been found by now
		}
	}
}

int main() 
{

	if (myFile.is_open())
		cout << "File open successfully" << endl;
	else {
		cout << "File unable to open, aborting..." << endl;
		return 0;
	}

	calculateShapeOrientations();
	clock_t start = clock();
	addShape(0, allShapes);	
	clock_t end = clock();

    cout << "Total solutions: " << numSolutions << endl;
	myFile << "Total solutions: " << numSolutions << endl;
	cout << "Calculation time (ms): " << (end-start)/(CLOCKS_PER_SEC/1000) << endl; 
	myFile << "Calculation time (s): " << (end-start)/(CLOCKS_PER_SEC) << endl;
	myFile.close();
    return 0;
}
