#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef _MODEL_H
#define _MODEL_H

enum Direction { LEFT, RIGHT, STAGNANT };

// The model manages the state of the game
class Model {
public:
    // Constructor (instantiates object)
    Model();
    // Destructor deletes all dynamically allocated stuff
    ~Model();
    // Is the game over?
    bool gameOver();
	//direction of car
	Direction direction;
	//update direction of car
	void go(Direction d);
	//update locations of images
	void calculate();

	//SDL location variables for images
	SDL_Rect source_road_1, source_road_2, source_obstacle;
	SDL_Rect destination_road_1, destination_road_2, destination_car, destination_obstacle;
	
};

#endif