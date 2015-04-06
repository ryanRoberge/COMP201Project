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
	
	destination_car.y = 530;
	destination_car.x = 490;
	
	p = 2;
	
	//at start of game, game is NOT over
	game_over = false;
	
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
	//collision detection  						Doesnt work half the time when hitting obstacle from the right side. FIX***********
	for (std::list<Debris>::iterator it = obstacles.begin(); it != obstacles.end(); it++) {
		game_over = (((it->dest.y + it->source.h) >= 530) && !(destination_car.x + 121 < it->dest.x || destination_car.x > it->dest.x + it->source.w));
	}
	return game_over;
}

/**bool Model::collided() {
	//collision detection
    return (((destination_obstacle.y + destination_obstacle.h) >= 530 && (destination_obstacle.y + destination_obstacle.h) <= 720) &&
			!(destination_car.x + 121 < destination_obstacle.x || destination_car.x > destination_obstacle.x + destination_obstacle.w));
}*/

void Model::go(Direction d)
{
	direction = d;
	return;
}

void Model::calculate(/*Model * model*/)
{
	currentTime = SDL_GetTicks();
	if(currentTime - lastTime > 1000)
	{
		score += 100*MULTIPLIER;
		lastTime = currentTime;
	}
	

	if(currentTime > 30000 && source_road_2.y == 720)
	{
		MULTIPLIER = 2;
		OFFSET = 3;
	}
	
	if(currentTime > 60000 && source_road_2.y == 720)
	{
		MULTIPLIER = 3;
		OFFSET = 4;
	}

		
	//update bottom part of road image
	source_road_1.h -= MULTIPLIER;// = source_road_1.h - 1;
	destination_road_1.y += MULTIPLIER;// = destination_road_1.y + 1;
	

	//update top part of road image
    source_road_2.y -= MULTIPLIER;// = source_road_2.y - 1;
    source_road_2.h += MULTIPLIER;// = source_road_2.h + 1;


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
		destination_car.x += 50;
	
	if(destination_car.x > 1000)
		destination_car.x -= 50;
	
	/*
	if(SDL_GetTicks() > 20000)
	{
	for (std::list<Debris>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		obstacles.pop_back();
			
	}
	*/
	
	//update obstacle positions
	for (std::list<Debris>::iterator it = obstacles.begin(); it != obstacles.end(); it++) {
		it->dest.y = it->dest.y + MULTIPLIER;	
			if (it->source.y > 0) {
				it->source.y = it->source.y - MULTIPLIER;
				it->source.h = it->source.h + MULTIPLIER;
				it->dest.y = it->dest.y - MULTIPLIER;
		}
		//check if image is off screen. if so, pop that ish outa hurr
		if (it->dest.y > 720) {
			//just do pop_front instead of getting rid of the specific debris because the only obstacle which will be this far down at any 
			//given time is the first element (oldest one)
			obstacles.pop_front();
		}
	}
	return;
}

Debris::Debris() {
	source.x = 0;
	source.y = 120;
	source.w = 100;
	source.h = 1;
	dest.y = 0;
	//dest.x is set randomly in controller
}

