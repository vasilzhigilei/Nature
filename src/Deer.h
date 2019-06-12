/*
 * Deer.h
 *
 *  Created on: Jun 6, 2019
 *      Author: vasil
 */

#ifndef DEER_H_
#define DEER_H_

class Deer {
private:
	int age;
	int health;
	int posX;
	int posY;
public:
	Deer(int posX, int posY, int health);
	int getAge();
	int getHealth();
	int getX();
	int getY();

	void addAge(int change);
	void addHealth(int change);
	void addX(int change);
	void addY(int change);

	virtual ~Deer();
};

#endif /* DEER_H_ */
