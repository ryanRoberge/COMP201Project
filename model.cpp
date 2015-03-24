#include "model.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor initializes the object
Model::Model() {
	//initialize location variables for road and car
	source_road_1.x = 0;
	source_road_1.y = 0;
	source_road_1.w = 1280;
	source_road_1.h = 720;
	destination_road_1.y = 0;
	destination_road_1.x = 0;
	
	source_road_2.x = 0;
	source_road_2.y = 720;
	source_road_2.w = 1280;
	source_road_2.h = 0;
	destination_road_2.y = 0;
	destination_road_2.x = 0;
	
	destination_car.y = 555;
	destination_car.x = 490;
	
	source_obstacle.x = 0;
	source_obstacle.y = 101;
	source_obstacle.w = 80;
	source_obstacle.h = 1;
	destination_obstacle.y = 0;
	destination_obstacle.x = 490;
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
	
}

bool Model::gameOver() {
	//collision detection
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
	source_road_1.h--;// = source_road_1.h - 1;
    destination_road_1.y++;// = destination_road_1.y + 1;
	
	//update top part of road image
    source_road_2.y--;// = source_road_2.y - 1;
    source_road_2.h++;// = source_road_2.h + 1;
	
	//reset road image after every loop through
	if (source_road_2.y == 0 || source_road_2.h == 720) {
		source_road_1.h = 720;
		destination_road_1.y = 0;
		source_road_2.y = 720;
		source_road_2.h = 0;
	}
	
	//updates car position
	switch(direction)
	{
		case LEFT: destination_car.x = destination_car.x - 10;
		break;
		case RIGHT: destination_car.x = destination_car.x + 10;
		break;
		case STAGNANT:
		break;
	}
	
	//update obstacle position
	destination_obstacle.y++;
	if (source_obstacle.y > 0) {
		source_obstacle.y--;
		source_obstacle.h++;
		destination_obstacle.y--;

	}
	
	return;
}

