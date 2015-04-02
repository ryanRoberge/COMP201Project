#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "model.h"
#include <map>
#include <sstream>
#include <string>
#include <iostream>

#ifndef _VIEW_H
#define _VIEW_H

// Show (output) the state of the model
class View {
public:
    View(std::string title, int width, int height);
    ~View();
    // Print out the visible stuff in the grid
    void show(Model * model);
	std::string to_string(int x);

private:
    SDL_Window* window;
    SDL_Surface* screen;
    bool fail;
    SDL_Surface* load(char * path);
	//object road
	SDL_Surface* road;
	//object car
	SDL_Surface* car;
	//obstacle 1
	SDL_Surface* cage;

	SDL_Surface *scoreCounter = NULL;
	SDL_Surface *scoreCounterShadow = NULL;
	
	SDL_Surface *message = NULL;
	SDL_Surface *messageShadow = NULL;
	
	//The font that's going to be used
	TTF_Font *font = NULL;

	//The color of the font
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Color messageColor = { 210, 0, 0 };
	SDL_Color shadowColor = { 56, 56, 56 };
	
	std::string textScore;
	
	
//    SDL_Surface* text;
//    Mix_Music * music;
//    Mix_Chunk * food;
};
#endif