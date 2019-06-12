#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>


#include "LTimer.h"
#include "Deer.h"
#include "Tree.h"

#include "SDL2/SDL.h"

using namespace std;

vector<Tree> treeVector;
vector<Deer> deerVector;


//void initializeSDL(SDL_Window *window, SDL_Renderer *renderer, int area);

void initializeTrees(int quantity, int area);
void initializeDeer(int quantity, int area);

int main() {
	srand(time(0));

	const int WINDOW_AREA = 900;
	const int FRAMES_PER_SECOND = 30;

	// Keep track of the current frame
	int frame = 0;

	// The frame rate regulator
	LTimer fps;

	// Initialize SDL window and renderer
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow ("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_AREA, WINDOW_AREA,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

	SDL_RenderSetLogicalSize( renderer, WINDOW_AREA, WINDOW_AREA);

	SDL_SetRenderDrawColor( renderer, 0, 255, 255, 255);

	SDL_RenderClear( renderer );

	initializeTrees(20, WINDOW_AREA);
	initializeDeer(4, WINDOW_AREA);

	SDL_Rect rect;

	// Main loop flag
	bool quit = false;


	// While simulation is on
	while(!quit){
		// Event Handler
		SDL_Event e;
		// Check if user closed window
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			}
		}

		// Start the frame timer
		fps.start();

		// Redraw background
		SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
		SDL_RenderClear( renderer );

		// Do simulation

		for(int i=treeVector.size()-1; i>=0; i--){
			if(rand()%300 == 0){
				treeVector.push_back(Tree(treeVector[i].getX()+(rand() % 60 + 20)*(rand()%2-1), treeVector[i].getY()+(rand() % 60 + 20)*(rand()%2-1)));
			}
		}

		// check for closest deers or trees based on priority of eating vs reproducing
		int closestDeer;
		int closestTree;
		int distance;
		int smallest_distance;
		for(int i=deerVector.size()-1; i>=0; i--){ // backwards for loop to allow for erasing of index
			if (frame % FRAMES_PER_SECOND == 0){
				deerVector[i].addAge(1);
				deerVector[i].addHealth(-1);
			}

			if((deerVector[i].getHealth() - (deerVector[i].getAge()/4)) <= 0){
				deerVector.erase(deerVector.begin() + i);
				continue;
			}else if((deerVector[i].getHealth() > 50) && (deerVector.size() > 1)){
				distance = WINDOW_AREA*5;
				smallest_distance = WINDOW_AREA*5;
				for(int j=0; j<deerVector.size(); j++){
					if(i == j){
						continue;
					}

					distance = sqrt(pow(deerVector[j].getX()-deerVector[i].getX(),2)+pow(deerVector[j].getY()-deerVector[i].getY(),2));
					if(distance < smallest_distance){
						smallest_distance = distance;
						closestDeer = j;
					}
				}

				if(smallest_distance < 3){
					deerVector[i].addHealth(-50);
					deerVector[closestDeer].addHealth(-50);
					deerVector.push_back(Deer(deerVector[i].getX()+rand()%5-2, deerVector[i].getY()+rand()%5-2, 50));
				}else{
					if(deerVector[closestDeer].getX()>deerVector[i].getX()){
						deerVector[i].addX((int)(1*(int)(deerVector[i].getHealth()/33))+1);
					}else if(deerVector[closestDeer].getX()<deerVector[i].getX()){
						deerVector[i].addX((int)(-1*(int)(deerVector[i].getHealth()/33))-1);
					}
					if(deerVector[closestDeer].getY()>deerVector[i].getY()){
						deerVector[i].addY((int)(1*(int)(deerVector[i].getHealth()/33))+1);
					}else if(deerVector[closestDeer].getY()<deerVector[i].getY()){
						deerVector[i].addY((int)(-1*(int)(deerVector[i].getHealth()/33))-1);
					}
				}
			}else if((deerVector[i].getHealth() < 50) && (treeVector.size() > 0)){
				distance = WINDOW_AREA*5;
				smallest_distance = WINDOW_AREA*5;
				for(int j=0; j<treeVector.size(); j++){
					distance = sqrt(pow(treeVector[j].getX()-deerVector[i].getX(),2)+pow(treeVector[j].getY()-deerVector[i].getY(),2));
					if(distance < smallest_distance){
						smallest_distance = distance;
						closestTree = j;
					}
				}

				if(smallest_distance < 3){
					deerVector[i].addHealth(50);
					treeVector.erase(treeVector.begin() + closestTree);
				}else{
					if(treeVector[closestTree].getX()>deerVector[i].getX()){
						deerVector[i].addX((int)(1*(int)(deerVector[i].getHealth()/33))+1);
					}else if(treeVector[closestTree].getX()<deerVector[i].getX()){
						deerVector[i].addX((int)(-1*(int)(deerVector[i].getHealth()/33))-1);
					}
					if(treeVector[closestTree].getY()>deerVector[i].getY()){
						deerVector[i].addY((int)(1*(int)(deerVector[i].getHealth()/33))+1);
					}else if(treeVector[closestTree].getY()<deerVector[i].getY()){
						deerVector[i].addY((int)(-1*(int)(deerVector[i].getHealth()/33))-1);
					}
				}
			}else{
				continue; // do nothing, no food, no deer, etc.
			}
		}

		// Render screen with trees and deer

		SDL_SetRenderDrawColor( renderer, 0, 153, 0, 255);
		for(Tree current : treeVector){
			rect.x = current.getX();
			rect.y = current.getY();
			rect.w = 30;
			rect.h = 30;
			SDL_RenderFillRect( renderer, &rect );
		}

		for(Deer current : deerVector){
			SDL_SetRenderDrawColor( renderer, 20+(current.getHealth()*2), 50, 33, 255);
			rect.x = current.getX();
			rect.y = current.getY();
			rect.w = 20;
			rect.h = 20;
			SDL_RenderFillRect( renderer, &rect );
		}


		SDL_RenderPresent( renderer );

		frame++;

		if(( fps.getTicks() < 1000 / FRAMES_PER_SECOND ) ) {
			//Sleep the remaining frame time
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.getTicks() );
		}
	}

	return 0;
}

/*void initializeSDL(SDL_Window *window, SDL_Renderer *renderer, int area){
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow ("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, area, area,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

	SDL_RenderSetLogicalSize( renderer, area, area);

	SDL_SetRenderDrawColor( renderer, 0, 255, 255, 255);

	SDL_RenderClear( renderer );
}*/

void initializeTrees(int quantity, int area){
	for(int i = 0; i < quantity; i++){
		treeVector.push_back(Tree(rand() % (area+1), rand() % (area+1))); //0-area inclusive
	}
}

void initializeDeer(int quantity, int area){
	for(int i = 0; i < quantity; i++){
		deerVector.push_back(Deer(rand() % (area+1), rand() % (area+1), 100)); //0-area inclusive
	}
}
