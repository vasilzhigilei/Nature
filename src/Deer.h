/*
 * Deer.h
 *
 */

#ifndef DEER_H_
#define DEER_H_
#include <vector>

#include "Eukaryote.h"

class Deer : public Eukaryote {
private:
	int health;
	std::vector<int> velocity;
	std::vector<int> target;
public:
	Deer(std::vector<int> position, int health, int width);
	int getHealth();
	std::vector<int> getVelocity();
	std::vector<int> getTarget();

	void changeHealth(int change);

	void setVelocity(std::vector<int> newVelocity);
	void move_velocity(); // Position changes in this method

	void setTarget(std::vector<int> targetPosition);

	virtual ~Deer();
};

#endif /* DEER_H_ */
