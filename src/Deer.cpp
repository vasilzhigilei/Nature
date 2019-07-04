/*
 * Deer.cpp
 *
 */

#include "Deer.h"
#include <algorithm>
#include <functional>

Deer::Deer(std::vector<int> position, int health, int width) : Eukaryote(position, width) {
	this->velocity = {0,0};
	this->health = health;
	this->target = position;
}

int Deer::getHealth(){
	return health;
}

std::vector<int> Deer::getVelocity(){
	return velocity;
}

std::vector<int> Deer::getTarget(){
	return target;
}

void Deer::changeHealth(int change){
	health += change;
}

void Deer::setVelocity(std::vector<int> newVelocity){
	this->velocity = newVelocity;
}

void Deer::move_velocity(){
	std::transform(position.begin(), position.end(), velocity.begin(), position.begin(), std::plus<int>());
}

void Deer::setTarget(std::vector<int> targetPosition){
	this->target = targetPosition;
}

Deer::~Deer() {
	// TODO Auto-generated destructor stub
}

