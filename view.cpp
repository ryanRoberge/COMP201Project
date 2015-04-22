#include "view.h"
#include<string>
#include<sstream>
using namespace std;

// Initialize SDL
View::View(string title, int width, int height) {
   
   fail = false;
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        fail = true;
        return;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fail = true;
        return;
    }
    // Get the screen
    screen = SDL_GetWindowSurface(window);
    //Initialize JPEG and PNG loading
    if( !( IMG_Init( IMG_INIT_JPG|IMG_INIT_PNG ) & (IMG_INIT_JPG|IMG_INIT_PNG) ) ) {
        fail = true;
        return;
    }
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        fail = true;
        return;
    }

    // Initialize True type fonts
    if( TTF_Init() == -1 ) {
        return;
    }
    // Load assets
//    snake = load("assets/snake.png");
    //music = Mix_LoadMUS("assets/menuMusic.mp3");
  if (music != NULL) {
     Mix_PlayMusic( music, -1 );
	}
//    food = Mix_LoadWAV("assets/yummy.wav");
    font = TTF_OpenFont( "assets/LiberationSans-Regular.ttf", 24 );
    menuFont = TTF_OpenFont("assets/LiberationSans-Regular.ttf", 30);
    menuFontSelected = TTF_OpenFont("assets/LiberationSans-Regular.ttf", 45);
	//load road picture
	road = load("assets/road.png"); 
    if (road == NULL) {
        return;
    }
	//load car picture
	car = load("assets/car2.png"); 
    if (car == NULL) {
        return;
    }


	//make background of car transparent
	SDL_SetColorKey( car, SDL_TRUE, SDL_MapRGB( car->format, 20, 20, 20 ) );
	
	//load obstacles
	char paths[] = "assets/1.png";
	for (int i = 0; i < 5; i++) {
		obst[i] = load(paths);
		paths[7]++;
		if (obst[i] == NULL) {return;}
		//make background of  transparent
		SDL_SetColorKey( obst[i], SDL_TRUE, SDL_MapRGB( obst[i]->format, 19, 19, 20 ) );
	}

	//Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return;    
    }
	//Open the font
    //font = TTF_OpenFont( "assets/test.tff", 28 );
	
	//If there was an error in loading the font
    if( font == NULL )
    {
        return;
    }
	menu.resize(3);
	


}

View::~View() {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

/**
 *  Load an image from a file to a SDL_Surface
 */
SDL_Surface* View::load(char * path) {
    // Load image
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        return NULL;
    }
    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, 0 );
    
    // Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    
    return optimizedSurface;
}
string View::to_string(int x)
{
	std::ostringstream os ;
	os << x ;
	return os.str() ;
}

void View::show(Model * model) {

	if(model->changeMusic){
		model->changeMusic=false;
		music = Mix_LoadMUS(model->music);
		Mix_PlayMusic( music, -1 );
	}
	//not needed i guess?
	/*SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,
        0x00, 0x00, 0x00));*/

	SDL_BlitSurface( road, &(model->source_road_1), screen, &(model->destination_road_1) );
	SDL_BlitSurface( road, &(model->source_road_2), screen, &(model->destination_road_2) );
	SDL_BlitSurface( car, NULL, screen, &(model->destination_car) );
	
	for (std::list<Debris>::iterator it = (model->obstacles).begin(); it != (model->obstacles).end(); it++) {
		SDL_BlitSurface( it->debris_image, &(it->source), screen, &(it->dest) );
	}
	
	textScore = "Score: " + to_string(model->score) + " (" + to_string(model->MULTIPLIER+model->SCORE_MULTIPLIER) + "X) Previous Score: " + to_string(model-> prevScore);
	int curTime = model->timeOffset();
	if(curTime > 25000)
		model->message = "        YOU'VE SURVIVED THIS FAR, READY TO SPEED THINGS UP?";
	if(curTime > 30000)
		model->message = "";
	if(curTime > 55000)
		model->message = "                       NOT BAD, BUT CAN YOU HANDLE 3X SPEED";
	if(curTime > 60000)
		model->message = "";	
	if(!model->startLoop){
		for(int i = 0; i < menu.size(); i++){
			if(i==model->selected){
				menu[i] = TTF_RenderText_Solid(menuFontSelected, model->menuMessage[i].c_str(),messageColor);
				SDL_BlitSurface(menu[i],NULL,screen,&(model->menu[i]));
				SDL_FreeSurface(menu[i]);
			}else{
				menu[i] = TTF_RenderText_Solid(menuFont, model->menuMessage[i].c_str(),messageColor);
				SDL_BlitSurface(menu[i],NULL,screen,&(model->menu[i]));
				SDL_FreeSurface(menu[i]);
			}
		}
	
	}
	scoreCounter = TTF_RenderText_Solid( font, textScore.c_str(), textColor );
	scoreCounterShadow = TTF_RenderText_Solid( font, textScore.c_str(), shadowColor );
	
	SDL_BlitSurface( scoreCounterShadow, NULL, screen, &(model->scoreCounterShadow) );
	SDL_BlitSurface( scoreCounter, NULL, screen, &(model->scoreCounter) );
	
	message = TTF_RenderText_Solid( font, model->message.c_str(), messageColor );
	messageShadow = TTF_RenderText_Solid( font, model->message.c_str(), shadowColor );
	
	SDL_BlitSurface( messageShadow, NULL, screen, &(model->MESSAGE_SHADOW) );
	SDL_BlitSurface( message, NULL, screen, &(model->MESSAGE) );	

	// Probably call SDL_FillRect or SDL_BlitSurface a bunch here :-)

    SDL_UpdateWindowSurface(window);
	
	SDL_FreeSurface(scoreCounter);
	SDL_FreeSurface(scoreCounterShadow);
	SDL_FreeSurface(message);
	SDL_FreeSurface(messageShadow);
	
	for(int i = 0; i < menu.size(); i++)
	{
	}	

	return;
}
