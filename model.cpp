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
	
	scoreCounter.x = 7;
	scoreCounter.y = 3;
	
	scoreCounterShadow.x = 9;
	scoreCounterShadow.y = 5;
	
	MESSAGE.x = 233;
	MESSAGE.y = 330;
	
	MESSAGE_SHADOW.x = 235;
	MESSAGE_SHADOW.y = 332;
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
	
}

bool Model::gameOver() {
	//collision detection
       // return (((destination_obstacle.y + destination_obstacle.h) >= 530 && (destination_obstacle.y + destination_obstacle.h) <= 720) &&
		//	!(destination_car.x + 121 < destination_obstacle.x || destination_car.x > destination_obstacle.x + destination_obstacle.w));
			
			return false;
}

bool Model::collided() {
	//collision detection
    return (((destination_obstacle.y + destination_obstacle.h) >= 530 && (destination_obstacle.y + destination_obstacle.h) <= 720) &&
			!(destination_car.x + 121 < destination_obstacle.x || destination_car.x > destination_obstacle.x + destination_obstacle.w));
}

void Model::go(Direction d)
{
	direction = d;
	return;
}

void Model::calculate(Model * model)
{
	currentTime = SDL_GetTicks();
	if(currentTime - lastTime > 1000)
	{
		score += 100*MULTIPLIER;
		lastTime = currentTime;
	}
	
/* Speed phases - for later
	if(currentTime > 5000 && source_road_2.y == 720)
	{
		MULTIPLIER = 2;
		OFFSET = 30;
	}
	
	if(currentTime > 10000 && source_road_2.y == 720)
	{
		MULTIPLIER = 3;
		OFFSET = 40;
	}
*/
		
	//update bottom part of road image
	source_road_1.h -= 1*MULTIPLIER;// = source_road_1.h - 1;
	destination_road_1.y += 1*MULTIPLIER;// = destination_road_1.y + 1;
	

	//update top part of road image
    source_road_2.y -= 1 * MULTIPLIER;// = source_road_2.y - 1;
    source_road_2.h += 1*MULTIPLIER;// = source_road_2.h + 1;


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
		case LEFT: destination_car.x = destination_car.x - OFFSET;
		break;
		case RIGHT: destination_car.x = destination_car.x + OFFSET;
		break;
		case STAGNANT:
		break;
	}
	
	if(destination_car.x < 200)
		destination_car.x += 100;
	
	if(destination_car.x > 1000)
		destination_car.x -= 100;
	
	//update obstacle position
	destination_obstacle.y++;
	if (source_obstacle.y > 0) {
		source_obstacle.y--;
		source_obstacle.h++;
		destination_obstacle.y--;
	}
	
	return;
}

