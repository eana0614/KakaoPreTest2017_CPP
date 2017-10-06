#include "Element.h"

Element::Element(){
}

Element::Element(string k, int t) {
	key = k;
	time = t;
}

Element::~Element()
{
}

string Element::getKey()
{
	return key;
}

int Element::getTime()
{
	return time;
}

void Element::setTime(int t){
	time = t;
}
