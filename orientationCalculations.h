#ifndef ORIENTATION_CALCULATIONS
#define ORIENTATION_CALCULATIONS

#include <iostream>
#include <vector>
#include <set>

using namespace std;

const set<vector<vector<int>>> shapes {
	{{1,1,1,1}, {1,0,0,0}},
	{{1,1,1,1}, {0,1,0,0}},
	{{1,1,1,0}, {0,0,1,1}},
	{{1,1,1}, {1,0,0}, {1,0,0}},
	{{1,1,1}, {0,1,0}, {0,1,0}},
	{{0,1,1}, {1,1,0}, {1,0,0}},
	{{1,1,0}, {0,1,1}, {0,1,0}},
	{{1,1,1}, {1,0,1}},
	{{1,1,1}, {1,1,0}},
	{{0,1,0}, {1,1,1}, {0,1,0}},
	{{0,1,1}, {0,1,0}, {1,1,0}},
	{{1,1,1,1,1}}
};

extern set<set<vector<vector<int>>>> allShapes;

vector<vector<int>> rotateShape (vector<vector<int>> origShape);
vector<vector<int>> flipShape (vector<vector<int>> shape);
set<vector<vector<int>>> getOrientations (int shapeIndex);
void calculateShapeOrientations();
void printShape(vector<vector<int>> shape);

#endif 
