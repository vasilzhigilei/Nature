/*
 * Eukaryote.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: vasil
 */

#include "Eukaryote.h"

Eukaryote::Eukaryote(std::vector<int> position, int width) {
	this->age = 0;
	this->position = position;
	this->width = width;

}

int Eukaryote::getAge(){
	return age;
}

std::vector<int> Eukaryote::getPosition(){
	return position;
}

int Eukaryote::getWidth(){
	return width;
}

void Eukaryote::addAge(int change){
	age += change;
}

void Eukaryote::changeWidth(int change){
	width += change;
}

Eukaryote::~Eukaryote() {
	// TODO Auto-generated destructor stub
}

