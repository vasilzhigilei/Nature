/*
 * Tree.h
 *
 */

#ifndef TREE_H_
#define TREE_H_

class Tree {
private:
	int age;
	int posX;
	int posY;
public:
	Tree(int posX, int posY);
	int getAge();
	int getX();
	int getY();
	virtual ~Tree();
};

#endif /* TREE_H_ */
