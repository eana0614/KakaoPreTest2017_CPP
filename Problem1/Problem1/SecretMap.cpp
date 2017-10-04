#include<iostream>
#include<string>
#include<vector>


using namespace std;

int * creatAllMap(int n, int * array1, int * array2);
void decodeCharMap(int * orMap, int n);
string binaryString(int num, int length);

int main(void) {

	int n = 5;
	int array1[5] = { 9, 20, 28, 18, 11 };
	int array2[5] = { 30, 1, 21, 17, 28 };

	int * orMap = creatAllMap(n, array1, array2);
	decodeCharMap(orMap, n);

	return 0;
}

void decodeCharMap(int * orMap, int n) {

	string str;

	for (int i = 0; i < n; i++) {
		str = binaryString(orMap[i], n);
		char bin;
		for (int j = 0; j < n; j++) {
			bin = str.at(j);

			if (bin == '1') {
				cout << '#';
			}
			else {
				cout << ' ';
			}
		}

		cout << endl;
	}
}

string binaryString(int num, int length) {

	int resultInt = 0;

	for (int i = 1; 0 < num; i *= 10) {
		int b = num % 2;
		resultInt += b * i;
		num /= 2;
	}

	string tmp = to_string(resultInt);

	int tLength = tmp.length();
	if (tLength < length) {
		for (int i = 0; i < length - tLength; i++) {
			tmp = "0" + tmp;
		}
	}

	return tmp;
}

int * creatAllMap(int n, int * array1, int * array2) {

	int * result = new int(n);

	for (int i = 0; i < n; i++) {

		result[i] = array1[i] | array2[i];

	}

	return result;
}

