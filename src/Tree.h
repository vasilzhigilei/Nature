/*
 * Tree.h
 *
 */

#ifndef TREE_H_
#define TREE_H_
#include <vector>

#include "Eukaryote.h"

class Tree : public Eukaryote{
public:
	Tree(std::vector<int> position, int width);
	virtual ~Tree();
};

#endif /* TREE_H_ */
