#include <iomanip>
#include "orientationCalculations.h"

using namespace std;

int grid[6][10] = {0};
float percentProgress = 0;

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
