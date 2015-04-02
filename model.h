#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#ifndef _MODEL_H
#define _MODEL_H

enum Direction { LEFT, RIGHT, STAGNANT };

// The model manages the state of the game
class Model {
public:

	int score = 0;
	std::string message = "";
	
	int MULTIPLIER = 1;
	int OFFSET = 20;
	
	int currentTime = 0;
	int lastTime = 0;
	
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

    // Constructor (instantiates object)
    Model();
    // Destructor deletes all dynamically allocated stuff
    ~Model();
    // Is the game over?
    bool gameOver();
	
	bool collided();
	//direction of car
	Direction direction;
	//update direction of car
	void go(Direction d);
	//update locations of images
	void calculate(Model * model);

	//SDL location variables for images
	SDL_Rect source_road_1, source_road_2, source_obstacle, scoreCounter, scoreCounterShadow, MESSAGE, MESSAGE_SHADOW;
	SDL_Rect destination_road_1, destination_road_2, destination_car, destination_obstacle;
	
};

#endif