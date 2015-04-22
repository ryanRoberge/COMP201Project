#include "controller.h"
#include <map>
#include <ctime>

using namespace std;

Controller::Controller() {
    model = new Model();
    view = new View("An Ode to Pro Monaco", 1280, 720);
	
	//for random obstacle generation
	srand(time(0));
}

Controller::~Controller() {
    delete model;
    delete view;
}
/**
References:
https://wiki.libsdl.org/SDL_PollEvent
https://wiki.libsdl.org/SDL_Event
*/
void Controller::loop() {
    SDL_Event e;
    unsigned int lastTime = 0, currentTime;
    std::map<SDL_Keycode, Direction> direction;
    direction[SDLK_LEFT] = LEFT;
    direction[SDLK_RIGHT] = RIGHT;
	
	//used to calculate how much time has passed since last obstacle was spawned
    float deltaTime = 0;
	//creates a random time between .5 and 1.75 seconds. Next obstacle will spawn after this amount of time
	int obst_gen_rate = (rand() % 1250) + 500;

	//used to eliminate key lag. switched to true when key is pressed; even if program doesnt realize key is still being pressed for a second,
	//this bool will ensure car moves anyways until the program catches up and realizes the key is still being held 
	bool keyDown = false;
	while(true){ //!model->gameOver()) {
	if(model->gameOver()){
		model->reset();
	}
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime);
		
        // Do stuff here to animate as necessary
		view->show(model);
        if (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN:
		switch(e.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
			keyDown = true;
			model->go(direction[e.key.keysym.sym]);
			//model->calculate(model);
			break;
                case SDLK_RETURN:
			model->start();
			break;
		case SDLK_UP:
			if(model->selected==0){
			model->selected=2;
			}else{
			model->selected--;
			}
			break;
		case SDLK_DOWN:
			if(model->selected==2){
				model->selected=0;
			}else{
				model->selected++;
			}
			break;
		default:
                break;
                }	
				break;
            case SDL_KEYUP:
				keyDown = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
                break;
            }
        }
		else { 
			if (!keyDown) {model->direction = STAGNANT;}
			else {model->go(direction[e.key.keysym.sym]);}
			model->calculate();
		}
		//every two seconds, add a new debris to the obstacles list
		if(model->spawnDebris){
		if (deltaTime > obst_gen_rate) {
			//reset obstacle generation rate
			obst_gen_rate = (rand() % 1250) + 500;
			//reset clock
			lastTime = currentTime;
			Debris * debris = new Debris;
			int x = rand() % 5;
			debris->debris_image = view->obst[x];
			debris->dest.x = 90 + 200*((rand() % 4) + 1);
			debris->img_num = x;
			(model->obstacles).push_back(*debris);
			delete debris;
		}
		}
    }
    // TODO: show something nice?
    view->show(model);
    SDL_Delay(2000);
}

