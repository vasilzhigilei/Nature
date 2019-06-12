/*
 * Tree.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: vasil
 */

#include "Tree.h"

Tree::Tree(int posX, int posY) {
	age = 0;
	this->posX = posX;
	this->posY = posY;
}

int Tree::getAge(){
	return age;
}

int Tree::getX(){
	return posX;
}

int Tree::getY(){
	return posY;
}

Tree::~Tree() {
	// TODO Auto-generated destructor stub
}

