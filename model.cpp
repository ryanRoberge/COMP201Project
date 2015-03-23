#include "model.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor initializes the object
Model::Model() {
public:
	int sourceRoad1_w = 1280;
	int sourceRoad1_h = 720;
	
	int sourceRoad2_w = 1280;
	int sourceRoad2_h = 720;
	
	int sourceRoad1_x = 0;
	int sourceRoad1_y = 0;
	
	int sourceRoad2_x = 0;
	int sourceRoad2_y = 720;
	
	int destinationRoad1_y = 0;
	int destinationRoad1_x = 0;
	
	int destinationRoad2_y = 0;
	int destinationRoad2_x = 0;
	
	int destinationCar_y = 555;
	int destinationCar_x = 490;
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
}

bool Model::gameOver() {
    return false;
}

void Model::go(Direction d)
{
	direction = d;
	
	return;
}

void Model::calculate()
{
	//update bottom part of road image
	sourceRoad1_h++;
    destinationRoad1_y++;
	
	//update top part of road image
	sourceRoad2_h++;
    destinationRoad2_y++;
	
	//reset road image after every loop through
	if (model->sourceRoad2_y == 0 || model->sourceRoad2_h == 720) {
		model->sourceRoad1_h = 720;
		model->destinationRoad1_y = 0;
		model->sourceRoad2_y = 720;
		model->sourceRoad2_h = 0;
	}
	
	//updates car position
	switch(model->direction)
	{
		case LEFT: model->destinationCar_x--;
		break;
		case RIGHT: model->destinationCar_x++;
		break;
		case STAGNANT:
		break;
	}
	
	return;
}

