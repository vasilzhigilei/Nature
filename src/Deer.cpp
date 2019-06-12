/*
 * Deer.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: vasil
 */

#include "Deer.h"

Deer::Deer(int posX, int posY, int health) {
	age = 0;
	this->health = health;
	this->posX = posX;
	this->posY = posY;
}

int Deer::getAge(){
	return age;
}

int Deer::getHealth(){
	return health;
}

int Deer::getX(){
	return posX;
}

int Deer::getY(){
	return posY;
}

void Deer::addAge(int change){
	age += change;
}

void Deer::addHealth(int change){
	health += change;
}

void Deer::addX(int change){
	posX += change;
}

void Deer::addY(int change){
	posY += change;
}

Deer::~Deer() {
	// TODO Auto-generated destructor stub
}

