//============================================================================
// Name        : nature.cpp
//============================================================================

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <functional>

#include "LTimer.h"
#include "Eukaryote.h"
#include "Deer.h"
#include "Tree.h"

#include "SDL2/SDL.h"

using namespace std;

vector<Tree> treeVector;
vector<Deer> deerVector;

// SDL Window to render to
SDL_Window* window = NULL;

// SDL Renderer
SDL_Renderer* renderer = NULL;

// Reusable drawable rectangle template
SDL_Rect rect;

const int WINDOW_AREA = 900;
const int FRAMES_PER_SECOND = 30;

void initializeSDL();

void initializeTrees(int quantity);
void initializeDeer(int quantity);

// Collision detection

bool checkCollision(Eukaryote &a, Eukaryote & b, vector<int> aOffset = {0,0});

// Helper functions with Eukaryote decision making
void treeLogic(bool getOlder);
void deerLogic(bool getOlder);

// Move and display functions for Eukaryotes
void updateTrees();
void updateDeer();

// Main function (runs setup, simulation)

int main() {
	/* SETUP */
	srand(time(0));

	// Initial frame
	int frame = 0;

	// The frame rate regulator
	LTimer fps;

	initializeSDL();

	initializeTrees(20);
	initializeDeer(4);

	// Main loop flag
	bool quit = false;

	// Event Handler
	SDL_Event e;

	// While simulation is on
	while(!quit){
		// Check if user closed window
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT) quit = true;
		}

		// Start the frame timer
		fps.start();

		// Redraw background as light green
		SDL_SetRenderDrawColor(renderer, 80, 255, 80, 255);
		SDL_RenderClear(renderer);

		bool getOlder = frame % FRAMES_PER_SECOND == 0;
		treeLogic(getOlder);
		deerLogic(getOlder);

		updateTrees();
		updateDeer();

		SDL_RenderPresent(renderer); // display screen
		// Increment frame counter and limit frames to the maximum FRAMES_PER_SECOND
		frame++;

		if(( fps.getTicks() < 1000 / FRAMES_PER_SECOND ) ) {
			//Sleep the remaining frame time
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.getTicks() );
		}
	}
	return 0;
}

void updateTrees(){
	/**
	 * Updates trees on screen. No other logic is applicable apart from the actual display of trees.
	 */
	for(int i = treeVector.size() - 1; i >= 0; i--){ // reverse loop to draw oldest trees on top
		// Display trees, color based on age. Width is based on tree age, but is computed in the treeLogic function
		SDL_SetRenderDrawColor( renderer, 0, 200-treeVector[i].getAge(), 0, 255);
		rect.x = treeVector[i].getPosition()[0];
		rect.y = treeVector[i].getPosition()[1];
		rect.w = treeVector[i].getWidth();
		rect.h = rect.w;
		SDL_RenderFillRect(renderer, &rect);
	}
}

void updateDeer(){
	/**
	 * Updates deer on screen. Also moves the deer based on targets, attempting to avoid collision with other dear.
	 */
	for(int i = 0; i < deerVector.size(); i++){
		// Deer movement and "general" avoidance (deer can overlap, this is meant to avoid complete overlap all the time)

		bool conflict = false;
		do{
		int speed = (int)(1*(int)(deerVector[i].getHealth()/33))+1;

		// Figure out velocity based on target location
		if(deerVector[i].getTarget()[0] > deerVector[i].getPosition()[0]){
			deerVector[i].setVelocity({speed, deerVector[i].getVelocity()[0]});
		}else if(deerVector[i].getTarget()[0] < deerVector[i].getPosition()[0]){
			deerVector[i].setVelocity({-speed, deerVector[i].getVelocity()[0]});
		}
		if(deerVector[i].getTarget()[1] > deerVector[i].getPosition()[1]){
			deerVector[i].setVelocity({deerVector[i].getVelocity()[1], speed});
		}else if(deerVector[i].getTarget()[1] < deerVector[i].getPosition()[1]){
			deerVector[i].setVelocity({deerVector[i].getVelocity()[1], -speed});
		}

		// Figure out if this velocity should be changed due other deer conflict
		if(conflict != true){
			for(int j = 0; j < deerVector.size(); j++){
				if(i == j) continue;
				if(checkCollision(deerVector[i], deerVector[j], deerVector[i].getVelocity())){
					int distance = sqrt(pow(treeVector[j].getPosition()[0]-deerVector[i].getPosition()[0],2)+pow(treeVector[j].getPosition()[1]-deerVector[i].getPosition()[1],2));
					deerVector[i].setTarget({deerVector[i].getTarget()[0] + rand() % (distance/8 + 1) - (distance/16),
						deerVector[i].getTarget()[1] + rand() % (distance/8 + 1) - (distance/16)});
					conflict = true;
					break;
				}
			}
		}else{
			conflict = false;
		}
		}while(conflict == true);

		// Update position
		deerVector[i].move_velocity();

		// Display deer, color based on age.
		SDL_SetRenderDrawColor(renderer, 20+(deerVector[i].getHealth()*2), 50, 33, 255);
		rect.x = deerVector[i].getPosition()[0];
		rect.y = deerVector[i].getPosition()[1];
		rect.w = deerVector[i].getWidth();
		rect.h = rect.w;
		SDL_RenderFillRect(renderer, &rect);
	}
}


void treeLogic(bool getOlder){
	/**
	 * Tree life/death cycle logic helper function
	 */
	for(int i=treeVector.size()-1; i>=0; i--){ // Reverse for loop to allow for erasing
		if(getOlder){
			treeVector[i].addAge(1);
			if(treeVector[i].getAge() % 5 == 0){
				treeVector[i].changeWidth(1);
			}
		}
		if(treeVector[i].getAge() >= 99){
			treeVector.erase(treeVector.begin() + i);
			continue;
		}else if (treeVector[i].getAge() >= 19){
			if(rand()%(FRAMES_PER_SECOND*10) == 0){
				// Make sure either -1 or 1, but not 0 multiplier
				int flipX = 0; while(flipX == 0) flipX = rand()%3-1;
				int flipY = 0; while(flipY == 0) flipY = rand()%3-1;
				treeVector.push_back(Tree({treeVector[i].getPosition()[0]+(rand() % 60 + 20)*(flipX), treeVector[i].getPosition()[1]+(rand() % 60 + 20)*(flipY)}, 25));
			}
		}
	}
}

void deerLogic(bool getOlder){
	/**
	 * Deer priorities:
	 *  Older than 20, health over 50 ---> reproduce
	 *  Health less than 100 ---> eat
	 *  else ---> find trees and stay near them, if no trees left, near other deer
	 */
	for(int i=deerVector.size()-1; i>=0; i--){
		int closest; // temporary variable for keeping track of closest deer or tree
		int distance = WINDOW_AREA*1.5;
		int smallest_distance = WINDOW_AREA*1.5;
		if(getOlder){
			deerVector[i].addAge(1);
			deerVector[i].changeHealth(-1);
		}
		if((deerVector[i].getHealth() - (deerVector[i].getAge()/4)) <= 0){
			deerVector.erase(deerVector.begin() + i);
			continue;
		}else if(deerVector[i].getAge() >= 19 && deerVector[i].getHealth() > 50 && deerVector.size() >= 1){
			// REPRODUCE
			for(int j=0; j<deerVector.size(); j++){
				if(j == i) continue;
				distance = sqrt(pow(deerVector[j].getPosition()[0]-deerVector[i].getPosition()[0],2)+pow(deerVector[j].getPosition()[1]-deerVector[i].getPosition()[1],2));
				if(distance < smallest_distance){
					smallest_distance = distance;
					closest = j;
				}
			}

			deerVector[i].setTarget(deerVector[closest].getPosition());

			if(checkCollision(deerVector[i], deerVector[closest])){
				deerVector[i].changeHealth(-50);
				deerVector[closest].changeHealth(-50);
				deerVector.push_back(Deer({(deerVector[i].getPosition()[0] + deerVector[closest].getPosition()[0])/2,
						(deerVector[i].getPosition()[1] + deerVector[closest].getPosition()[1])/2},
						(deerVector[i].getHealth() + deerVector[closest].getHealth())/2 + 50, 20));
			}
		}else if(deerVector[i].getHealth() < 100 && treeVector.size() > 0){
			// EAT
			for(int j=0; j<treeVector.size(); j++){
				distance = sqrt(pow(treeVector[j].getPosition()[0]-deerVector[i].getPosition()[0],2)+pow(treeVector[j].getPosition()[1]-deerVector[i].getPosition()[1],2));
				if(distance < smallest_distance){
					smallest_distance = distance;
					closest = j;
				}
			}

			deerVector[i].setTarget(treeVector[closest].getPosition());

			if(checkCollision(deerVector[i], treeVector[closest])){
				deerVector[i].changeHealth(25 + treeVector[closest].getAge()/2); // 25 to 75 health, depending on tree age
				treeVector.erase(treeVector.begin() + closest);
			}
		}else if(sqrt(pow(deerVector[i].getTarget()[0]-deerVector[i].getPosition()[0],2)+pow(deerVector[i].getTarget()[1]-deerVector[i].getPosition()[1],2)) > 1){
			// STAY NEAR FOOD OR OTHER DEER
			if(treeVector.size() > 0){
				// At least one tree in the world
				for(int j=0; j<treeVector.size(); j++){
					distance = sqrt(pow(treeVector[j].getPosition()[0]-deerVector[i].getPosition()[0],2)+pow(treeVector[j].getPosition()[1]-deerVector[i].getPosition()[1],2));
					if(distance < smallest_distance){
						smallest_distance = distance;
						closest = j;
					}
				}
				deerVector[i].setTarget({treeVector[closest].getPosition()[0] - 50 + (rand() % 100),
								treeVector[closest].getPosition()[1] - 50 + (rand() % 100)});
			}else if(deerVector.size() > 1){
				// Deer is not alone
				int randomDeer;
				do{
					randomDeer = rand() % deerVector.size() - 1;
				}while (randomDeer != i);
				deerVector[i].setTarget({deerVector[randomDeer].getPosition()[0] - 50 + (rand() % 100),
					deerVector[randomDeer].getPosition()[1] - 50 + (rand() % 100)});
			}else{
				// Deer is alone
				// Random target in the middle of the screen
				deerVector[i].setTarget({WINDOW_AREA/2-(WINDOW_AREA/4)+(rand()%(WINDOW_AREA/2)),
					WINDOW_AREA/2-(WINDOW_AREA/4)+(rand()%(WINDOW_AREA/2))});
			}
		}
	}
}

void initializeSDL(){
	// initializes SDL for GUI representation of simulation
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow ("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_AREA, WINDOW_AREA,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_RenderSetLogicalSize(renderer, WINDOW_AREA, WINDOW_AREA);
}

void initializeTrees(int quantity){
	// initializes trees
	for(int i = 0; i < quantity; i++){
		treeVector.push_back(Tree({rand() % (WINDOW_AREA-40) + 20, rand() % (WINDOW_AREA - 40) + 20}, 25)); //0-area inclusive
	}
}

void initializeDeer(int quantity){
	// initializes deer
	for(int i = 0; i < quantity; i++){
		deerVector.push_back(Deer({rand() % (WINDOW_AREA-40) + 20, rand() % (WINDOW_AREA - 40) + 20}, 100, 20)); //0-area inclusive
	}
}

bool checkCollision(Eukaryote &a, Eukaryote &b, vector<int> aOffset){
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.getPosition()[0] + aOffset[0];
	rightA = a.getPosition()[0] + a.getWidth() + aOffset[0];
	topA = a.getPosition()[1] + aOffset[1];
	bottomA = a.getPosition()[1] + a.getWidth() + aOffset[1];

	//Calculate the sides of rect B
	leftB = b.getPosition()[0];
	rightB = b.getPosition()[0] + b.getWidth();
	topB = b.getPosition()[1];
	bottomB = b.getPosition()[1] + b.getWidth();

	//If any of the sides from A are outside of B
	if( bottomA <= topB ){
		return false;
	}
	if( topA >= bottomB ){
		return false;
	}
	if( rightA <= leftB ){
		return false;
	}
	if( leftA >= rightB ){
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
