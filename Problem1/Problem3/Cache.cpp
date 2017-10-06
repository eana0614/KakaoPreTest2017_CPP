#include "Cache.h"

int Cache::findOldElement() {

	int old = INT_MAX;
	int index = INT_MAX;

	for (int i = 0; i < cacheSize; i++) {
		if (old > caches[i].getTime()) {
			index = i;
			old = caches[i].getTime();
		}
	}

	return index;
}

void Cache::swapSameElement(string str, int t) {
	int index;

	for (int i = 0; i < cachesCount; i++) {
		if (caches[i].getKey() == str) {
			caches[i].setTime(t);
			break;
		}
	}
}

bool Cache::isSameElement(string city) {
	bool find = false;

	for (int i = 0; i < cachesCount; i++) {
		if (caches[i].getKey() == city) {
			find = true;
			break;
		}
	}

	return find;
}

void Cache::changeCitiesCase() {

	for (int i = 0; i < cities.size(); i++) {
		transform(cities[i].begin(), cities[i].end(), cities[i].begin(), ::tolower);
	}

}

bool Cache::isCachesFull() {
	return (cachesCount < cacheSize);
}

int Cache::addCities() {

	for (int i = 0; i < cities.size(); i++) {
		if (cacheSize <= 0) {
			miss++;
		}
		else {
			if (isSameElement(cities[i])) {
				hit++;
				swapSameElement(cities[i], i);
			}
			else {
				miss++;
				if (isCachesFull()) {
					caches[cachesCount] = Element::Element(cities[i], i);
					cachesCount++;
				}
				else {
					int old = findOldElement();
					caches[old] = Element::Element(cities[i], i);
				}
			}
		}
	}

	return (hit *1 ) + (miss * 5);
}

void Cache::rundLRUCache() {

	int hmTime = 0;

	cout << "[ ";

	for (int i = 0; i < cities.size(); i++) {
		cout << cities[i] << " ";
	}

	changeCitiesCase();

	hmTime = addCities();

	cout << "] Cache runtime : " << hmTime << endl;

}

Cache::Cache(int cs, vector<string> input) {
	cacheSize = cs;
	caches = new Element[cacheSize];
	cachesCount = 0;

	cities = input;

	hit = 0;
	miss = 0;
}


Cache::~Cache()
{
}
