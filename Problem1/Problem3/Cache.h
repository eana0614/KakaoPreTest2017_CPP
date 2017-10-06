#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

#include"Element.h"

using namespace std;

class Cache {
private:
	int cacheSize;
	Element * caches;
	int cachesCount;

	vector<string> cities;
	
	int hit;
	int miss;

	int addCities();
	int findOldElement();
	void swapSameElement(string str, int t);
	bool isSameElement(string city);
	void changeCitiesCase();
	bool isCachesFull();

public:
	Cache(int cs, vector<string> input);
	void rundLRUCache();
	~Cache();
};

