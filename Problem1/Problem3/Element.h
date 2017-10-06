#include<string>
#include<iostream>

using namespace std;

class Element {
private:
	string key;
	int time;

public:
	Element();
	Element(string k, int t);
	~Element();
	string getKey();
	int getTime();
	void setTime(int t);
};

