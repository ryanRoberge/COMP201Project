#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iostream>
#include <fstream>
#ifndef _MODEL_H
#define _MODEL_H

enum Direction { LEFT, RIGHT, STAGNANT };

class Debris {
public:
	//constructor initializes coordinates of debris
	Debris();
	//source coordinates (x,y,w,h)
	SDL_Rect source;
	//destination coordinates (x,y)
	SDL_Rect dest;
	//obstacle itself
	SDL_Surface* debris_image;
	int img_num;
};

// The model manages the state of the game
class Model {
public:

	int score = 0;
	std::string message = "";
	
	int SCORE_MULTIPLIER = 0;
	int MULTIPLIER = 1;
	int OFFSET = 2;
	bool spawnDebris = false;
	bool startLoop = false;
	bool changeMusic = true;
	std::vector<std::string> menuMessage;
	std::vector<int> topScores;
	int currentTime = 0;
	int lastTime = 0;
	int startTime = -1000000;
	int selected = 0;
	char* music = "assets/menuMusic.mp3";
	int prevScore = 0;
	/*int sourceRoad1_w = 1280;
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
	int destinationCar_x = 490;*/

    // Constructor (instantiates object)
    Model();
    // Destructor deletes all dynamically allocated stuff
    ~Model();
    void start();
    // Is the game over?
    bool gameOver();
    void reset();
    void highScore(int score);
    void showHighScore();
    std::vector<int> merge_sort(std::vector<int>& vec);
    std::vector<int> merge(std::vector<int> &vec,const std::vector<int>& left, const std::vector<int>& right);

    std::string to_string(int x);
    int timeOffset();
    

	//game over token
	bool game_over;
	bool game_over2;
	
	bool collided();
	//direction of car
	Direction direction;
	//update direction of car
	void go(Direction d);
	//update locations of images
	void calculate(/*Model * model*/);
	//how many pixels will the objects redraw at a time
	//obstacles
	std::list<Debris> obstacles;

	//SDL location variables for images
	SDL_Rect source_road_1, source_road_2, scoreCounter, scoreCounterShadow, MESSAGE, MESSAGE_SHADOW;
	SDL_Rect destination_road_1, destination_road_2, destination_car;
	std::vector<SDL_Rect> menu;
	std::vector<SDL_Rect> scoreListRect;
	std::vector<SDL_Rect> scoreListRectShadow;
};

#endif
