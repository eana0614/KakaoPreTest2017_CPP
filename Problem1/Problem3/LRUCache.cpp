#include<iostream>
#include<string>
#include<vector>
#include"Cache.h"

using namespace std;


int main(void) {

	vector<vector<string>> city = { { "Jeju", "Pangyo", "Seoul", "NewYork", "LA", "Jeju", "Pangyo", "Seoul", "NewYork", "LA" },
	{ "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul" },
	{ "Jeju", "Pangyo", "Seoul", "NewYork", "LA", "SanFrancisco", "Seoul", "Rome", "Paris", "Jeju", "NewYork", "Rome" },
	{ "Jeju", "Pangyo", "Seoul", "NewYork", "LA", "SanFrancisco", "Seoul", "Rome", "Paris", "Jeju", "NewYork", "Rome" },
	{ "Jeju", "Pangyo", "NewYork", "newyork" },
	{ "Jeju", "Pangyo", "Seoul", "NewYork", "LA" } };

	int cacheSize[] = {3, 3, 2, 5, 2, 0};

	for (int i = 0; i < city.size(); i++) {
		
		Cache cache(cacheSize[i], city[i]);
		
		cache.rundLRUCache();

		cout << endl;

	}

	return 0;
}