#include "model.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

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
	
	//at start of game, game is NOT over
	game_over = false;	
	game_over2 = false;
	
	scoreCounter.x = 7;
	scoreCounter.y = 3;
	
	scoreCounterShadow.x = 9;
	scoreCounterShadow.y = 5;
	
	MESSAGE.x = 233;
	MESSAGE.y = 330;
	MESSAGE_SHADOW.x = 235;
	MESSAGE_SHADOW.y = 332;
	menuMessage.push_back("Play Game");
	menuMessage.push_back("High Score Table");
	menuMessage.push_back("Exit Game");
	scoreListRect.resize(10);
	topScores.resize(10);
	for(int i = 0; i < scoreListRect.size(); ++i){
		SDL_Rect r;
		menu.push_back(r);
		scoreListRect[i].y=(i+1)*50;
		scoreListRect[i].x=1075;
	}
	for(int i = 0; i < menuMessage.size(); ++i){
		SDL_Rect r;
		menu.push_back(r);
		menu[i].y=(i+1)*150;
		menu[i].x=233;
	}
	for(int i = 0; i < 10; ++i){
		topScores[i]=0;
	}


}
// Destructor deletes dynamically allocated memory
Model::~Model() {
	
}

/*bool Model::gameOver() {
	//collision detection  						Doesnt work half the time when hitting obstacle from the right side. FIX***********
	for (std::list<Debris>::iterator it = obstacles.begin(); it != obstacles.end(); it++) {
		game_over = (((it->dest.y + it->source.h) >= 530) && ((it->dest.y + it->source.h) < 720) && !(destination_car.x + 121 < it->dest.x || destination_car.x > it->dest.x + it->source.w));
		if (it->img_num == 4 && game_over == true) {
			game_over = false;
			SCORE_MULTIPLIER +=2;
			if (SCORE_MULTIPLIER ==3) {
				SCORE_MULTIPLIER -=1;
			}
			obstacles.pop_front();
		}
		if(game_over && startLoop)
			return true;
	}
	return false;
}*/
bool Model::gameOver() {
	//collision detection  						Doesnt work half the time when hitting obstacle from the right side. FIX***********
	for (std::list<Debris>::iterator it = obstacles.begin(); it != obstacles.end(); it++) {
		game_over = (((it->dest.y + it->source.h) >= 530)  && ((it->dest.y + it->source.h) < 720) && !(destination_car.x + 121 < it->dest.x || destination_car.x > it->dest.x + it->source.w));
		if (it->img_num == 4 && game_over == true) {
			game_over = false;
			SCORE_MULTIPLIER +=2;
			if (SCORE_MULTIPLIER ==3) {
				SCORE_MULTIPLIER -=1;
			}
			//obstacles.pop_front();
		}
		if(game_over == true)
			break;
	}
	return game_over;
}
void Model::reset(){	
	if(startLoop){	
		prevScore = score;
		startLoop=false;
		game_over = false;
		game_over2 = false;
		spawnDebris = false;
		selected = 0;
		MULTIPLIER = 1;
		SCORE_MULTIPLIER = 0;
		OFFSET = 2;
		currentTime = 0;
		lastTime = 0;
		startTime = -1000000;
		music = "assets/menuMusic.mp3";
		changeMusic = true;
		highScore(prevScore);
		obstacles.clear();
	}
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
void Model::start(){
	
	if(selected==0){
		startTime=SDL_GetTicks();
		startLoop=true;
		changeMusic=true;
		music = "assets/horn.mp3";
		score = 0;
		game_over2 = true;
		for(int i = 0; i < 10; ++i){
			topScores[i]=0;
		}

	}else if(selected==1){
	showHighScore();
	}else if(selected==2){
		std::exit(1);
	}
	
}
int Model::timeOffset(){
	return SDL_GetTicks() - startTime;

}
std::vector<int> Model::merge_sort(std::vector<int>& vec)
{
    // Termination condition: List is completely sorted if it
    // only contains a single element.
    if(vec.size() == 1)
    {
        return vec;
    }
 
    // Determine the location of the middle element in the vector
    std::vector<int>::iterator middle = vec.begin() + (vec.size() / 2);
 
    std::vector<int> left(vec.begin(), middle);
    std::vector<int> right(middle, vec.end());
 
    // Perform a merge sort on the two smaller vectors
    left = merge_sort(left);
    right = merge_sort(right);
 
    return merge(vec,left, right);
}
std::vector<int> Model::merge(std::vector<int> &vec,const std::vector<int>& left, const std::vector<int>& right)
{
    // Fill the resultant vector with sorted results from both vectors
    std::vector<int> result;
    unsigned left_it = 0, right_it = 0;
 
    while(left_it < left.size() && right_it < right.size())
    {
        // If the left value is smaller than the right it goes next
        // into the resultant vector
        if(left[left_it] < right[right_it])
        {
            result.push_back(left[left_it]);
            left_it++;
        }
        else
        {
            result.push_back(right[right_it]);
            right_it++;
        }
    }
 
    // Push the remaining data from both vectors onto the resultant
    while(left_it < left.size())
    {
        result.push_back(left[left_it]);
        left_it++;
    }
 
    while(right_it < right.size())
    {
        result.push_back(right[right_it]);
        right_it++;
    }
    //show merge process.. 
 
    //take a source vector and parse the result to it. then return it.  
	vec = result;				
	return vec;
}
void Model::highScore(int score){
	int high = 0;
	std::string line;
	std::vector<int> scoreList;
	ifstream scores ("assets/scores.data");
	if(scores.is_open()){
		while ( getline (scores,line) ){
			int s = atoi(line.c_str());			
			scoreList.push_back(s);

		}
	}
	scoreList.push_back(score);
	scores.close();
	merge_sort(scoreList);
	std::reverse(std::begin(scoreList), std::end(scoreList));
	ofstream ofs ("assets/scores.data", std::ofstream::out);
	for(int i=0;i<scoreList.size();++i){
		ofs << scoreList[i] << "\n";
	}
}
std::string Model::to_string(int x)
{
	std::ostringstream os ;
	os << x ;
	return os.str() ;
}
void Model::showHighScore(){
	ifstream scores ("assets/scores.data");
	std::string line;
	for (int i=0;i<10 && scores.is_open() && getline(scores,line);++i){
	topScores[i] = (atoi(line.c_str()));
	}
	scores.close();
}
void Model::calculate(/*Model * model*/)
{
	currentTime = timeOffset();
	if(startLoop){
	if(currentTime > 4300 && music == "assets/horn.mp3"){
		music = "assets/music3.mp3";
		changeMusic = true;
	}
	if(currentTime > 5000 && (currentTime < 20000 || currentTime > 33000) && (currentTime < 50000 || currentTime > 63000)){
		spawnDebris = true;
	}else{
		spawnDebris = false;
	}

	if(currentTime - lastTime > 1000)
	{
		score += 100*(MULTIPLIER+SCORE_MULTIPLIER);
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
		//obstacles.pop_front();
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

