#include "model.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor initializes the object
Model::Model() {

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

void Model::calculate(Model * model)
{
	//update bottom part of road image
	model->sourceRoad1_h++;
    model->destinationRoad1_y++;
	
	//update top part of road image
	model->sourceRoad2_h++;
    model->destinationRoad2_y++;
	
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

