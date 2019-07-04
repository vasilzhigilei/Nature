/*
 * Eukaryote.h
 *
 *  Created on: Jun 14, 2019
 *      Author: vasil
 */

#ifndef EUKARYOTE_H_
#define EUKARYOTE_H_

#include <vector>

class Eukaryote {
private:
	int age;
	int width;
protected:
	std::vector<int> position;
public:
	Eukaryote(std::vector<int> position, int width);

	int getAge();
	std::vector<int> getPosition();
	int getWidth();

	void addAge(int change);
	void changeWidth(int change);

	virtual ~Eukaryote();
};

#endif /* EUKARYOTE_H_ */
