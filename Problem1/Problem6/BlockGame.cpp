#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include"Block.h"

using namespace std;

#define regexStr "^e*[A-Z]*$"


void printBlocks(vector<vector<Block>> b) {
	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < b[0].size(); j++) {
			if (b[i][j].getBlock() == 'e') {
				cout << " " << " ";
			}
			else {
				cout << b[i][j].getBlock() << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

vector<vector<Block>> createBlocks(vector<string> strs, int h, int w) {

	vector<vector<Block>> b;
	vector<Block> t;
	
	Block nullBlock = Block();
	nullBlock.setBlock('0');

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			t.push_back(Block());
			t[j].setBlock(strs[i][j]);
		}
		b.push_back(t);
		t.clear();
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {

			if (i == 0) {
				b[i][j].setUp(nullBlock);
			}
			else {
				b[i][j].setUp(b[i - 1][j]);
			}

			if (i == h - 1) {
				b[i][j].setDown(nullBlock);
			}
			else {
				b[i][j].setDown(b[i + 1][j]);
			}

			if (j == 0) {
				b[i][j].setLeft(nullBlock);
			}
			else {
				b[i][j].setLeft(b[i][j-1]);
			}

			if (j == w-1) {
				b[i][j].setRight(nullBlock);
			}
			else {
				b[i][j].setRight(b[i][j + 1]);
			}

		}
	}
	
	return b;
}

bool isSameblocks(vector<vector<Block>> block, int y, int x) {
	bool result = false;

	char myBlock = block[y][x].getBlock();

	char right = block[y][x + 1].getBlock();
	char down = block[y + 1][x].getBlock();
	char diagonal = block[y + 1][x + 1].getBlock();

	if (diagonal >= 'A' && diagonal <= 'Z' && right >= 'A' && right <= 'Z' && down >= 'A' && down <='Z') {

		if (myBlock == right && myBlock == down && myBlock == diagonal) {
			result = true;
		}

	}
	
	return result;
}

vector<pair<int, int>> findFourBlocks(vector<vector<Block>> block) {

	pair<int, int> p;
	vector<pair<int, int>> result;

	string temp = "";

	for (int i = 0; i < block.size()-1; i++) {
		for (int j = 0; j < block[0].size()-1; j++) {
			if (isSameblocks(block, i, j)) {

				pair<int, int> pa = make_pair(i,j);
				result.push_back(pa);
			}
		}
	}

	return result;
}

bool correctRelocation(vector<vector<Block>> b, int y, int x) {

	regex pattern(regexStr);
	smatch sm;

	string temp ="";

	for (int i = 0; i < y; i++) {
		temp = temp + b[i][x].getBlock();
	}

	if (regex_match(temp, sm, pattern)) {
		return true;
	}
	else {
		return false;
	}
}

int findEmptyBlock(vector<vector<Block>> b, int x) {

	int result = -1;

	for (int i = b.size()-2; i >=0 ; i--) {
		if (b[i][x].getBlock() != 'e' && b[i + 1][x].getBlock() == 'e') {
			result = i;
			break;
		}
	}

	return result;
}

int countNullBlocks(vector<vector<Block>> b, int x, int start) {

	int count = 0;

	for (int i = start+1; i < b.size(); i++) {
		if (b[i][x].getBlock() == 'e') {
			count++;
		}
		else {
			break;
		}
	}

	return count;
}

vector<vector<Block>> relocationBlocks(vector<vector<Block>> b) {

	for (int i = 0; i < b[0].size(); i++) {
		while (!correctRelocation(b, b.size(), i)) {

			int index = findEmptyBlock(b, i);
			int countNullBlock = countNullBlocks(b, i, index);

			b[index + countNullBlock][i].setBlock(b[index][i].getBlock());
			b[index][i].setBlock('e');

		}
	}

	return b;

}

vector < vector<Block>> reBuildBlocksInfo(vector<vector<Block>> b) {

	vector<string> temp;
	string t = "";

	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < b[0].size(); j++) {
			t = t + b[i][j].getBlock();
		}

		temp.push_back(t);
		t = "";
	}

	return createBlocks(temp, b.size(), b[0].size());
}

vector<vector<Block>> removeBlocks(vector<vector<Block>> b, vector<pair<int, int>> indexs) {

	vector<vector<Block>> result;

	for (int i = 0; i < indexs.size(); i++) {
		int y = indexs[i].first;
		int x = indexs[i].second;

		b[y][x].setBlock('e');
		b[y+1][x].setBlock('e');
		b[y][x+1].setBlock('e');
		b[y+1][x+1].setBlock('e');

	}

	b = relocationBlocks(b);
	result = reBuildBlocksInfo(b);

	return result;
}

int countRemainBlocks(vector<vector<Block>> b) {
	int count = 0;

	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < b[0].size(); j++) {
			if (b[i][j].getBlock() == 'e') {
				count++;
			}
		}
	}

	return count;
}

int runBlockGame(vector<string> strs, int height, int width) {
	int deleteBlock;

	vector<vector<Block>> blocks = createBlocks(strs, height, width);

	vector<pair<int, int>> indexs = findFourBlocks(blocks);

	while (!(indexs.size() == 0)) {
		blocks = removeBlocks(blocks, indexs);
		indexs = findFourBlocks(blocks);
	}

	deleteBlock = countRemainBlocks(blocks);
	printBlocks(blocks);

	return deleteBlock;
}

int main(void) {

	vector<vector<string>> vs = {{ "CCBDE", "AAADE", "AAABF", "CCBBF" },
					{ "TTTANT", "RRFACC", "RRRFCC", "TRRRAA", "TTMMMF", "TMMTTJ" }};
	int m[] = { 4, 6 };
	int n[] = { 5, 6};

	for (int i = 0; i < vs.size(); i++) {

		int result = runBlockGame(vs.at(i), m[i], n[i]);

		cout << "OUTPUT : " << result << " blocks deleted." << endl << endl;
	}

	return 0;
}