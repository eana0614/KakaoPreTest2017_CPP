#include "Block.h"

Block::Block()
{
}


Block::~Block()
{
}

Block Block::getUp()
{
	return *up;
}

Block Block::getDown()
{
	return *down;
}

Block Block::getRight()
{
	return *right;
}

Block Block::getLeft()
{
	return *left;
}

void Block::setUp(Block b)
{
	*up = b;
}

void Block::setDown(Block b)
{
	*down = b;
}

void Block::setRight(Block b)
{
	*right = b;
}

void Block::setLeft(Block b)
{
	*left = b;
}

void Block::setBlock(char c)
{
	blocks = c;
}

char Block::getBlock()
{
	return blocks;
}

