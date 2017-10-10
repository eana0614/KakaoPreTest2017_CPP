#pragma once
class Block {

private:
	Block * up;
	Block * down;
	Block * left;
	Block * right;

	char blocks;

public:
	Block();
	~Block();
	Block getUp();
	Block getDown();
	Block getRight();
	Block getLeft();
	void setUp(Block b);
	void setDown(Block b);
	void setRight(Block b);
	void setLeft(Block b);

	void setBlock(char c);
	char getBlock();
};

