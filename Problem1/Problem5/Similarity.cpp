#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

#define MULNUM 65536;

bool isOnlyAlphabet(string str) {

	int length = str.length();

	for (int i = 0; i < length; i++) {
		if (str.at(i) < 'a' || str.at(i) > 'z') {
			return false;
		}
	}

	return true;
}

vector<string> createElement(string str) {

	vector<string> ele;

	string temp;

	transform(str.begin(), str.end(), str.begin(), tolower);

	for (int i = 0; i < str.length() - 1; i++) {
		temp = str.substr(i, 2);

		if (isOnlyAlphabet(temp)) {
			ele.push_back(temp);
		}
	}

	return ele;
}

bool isContain(vector<string> arr, string str) {

	for (int i = 0; i < arr.size(); i++) {
		if (arr.at(i) == str) {
			return true;
		}
	}

	return false;
}

int unionArrays(vector<string> s, vector<string> l) {

	vector<string> unions = l;

	for (int i = 0; i < s.size(); i++) {
		if (!isContain(unions, s.at(i))) {
			unions.push_back(s.at(i));
		}
	}

	return unions.size();
}

int intersectionAraays(vector<string> s, vector<string> l) {

	vector<string> inter;

	for (int i = 0; i < s.size(); i++) {
		if (isContain(l, s.at(i))) {
			inter.push_back(s.at(i));
		}
	}

	return inter.size();
}

double compareArrays(vector<string> small, vector<string> large) {

	double result;

	int unionSize = unionArrays(small, large);
	int intersectionSize = intersectionAraays(small, large);

	if (unionSize == 0 || intersectionSize == 0) {
		result = 1.0;
	}
	else {
		result = (double)intersectionSize / unionSize;
	}

	return result * MULNUM;
}

void runSimilarity(string str1, string str2) {

	int result = 0;

	vector<string> element1 = createElement(str1);
	vector<string> element2 = createElement(str2);

	if (element1.size() < element2.size()) {
		result = (int)compareArrays(element1, element2);
	}
	else {
		result = (int)compareArrays(element2, element1);
	}

	cout << " Output : " << result << endl;
}

int main(void) {

	vector<string> strs1 = { "FRANCE", "handshake", "aa1+aa2", "E=M*C^2" };
	vector<string> strs2 = { "french", "shake hands", "AAAA12", "e=m*c^2" };

	for (int i = 0; i < strs1.size(); i++) {

		runSimilarity(strs1[i], strs2[i]);

	}

}