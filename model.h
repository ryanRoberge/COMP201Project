#ifndef _MODEL_H
#define _MODEL_H

enum Direction { UP, DOWN, LEFT, RIGHT, STAGNANT };

// The model manages the state of the game
class Model {
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

    // Constructor (instantiates object)
    Model();
    // Destructor deletes all dynamically allocated stuff
    ~Model();
    // Is the game over?
    bool gameOver();
    // TODO: Put your stuff here
	
	Direction direction;
	
	void go(Direction d);
	
	void calculate(Model * model);
	
};

#endif