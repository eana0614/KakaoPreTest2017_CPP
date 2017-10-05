#include<iostream>
#include<string>
#include<vector>
#include<regex>

using namespace std;

class Score {

private:
	double basic;
	char bonus;
	bool optionAble;
	char option;
	double roundScore;

public:
	Score() {

	}

	Score(double s, char b, bool opA, char op) {
		basic = s;
		bonus = b;
		optionAble = opA;
		option = op;
		roundScore = s;
	}

	double getBasic() {
		return basic;
	}

	char getBonus() {
		return bonus;
	}
	
	bool isOptionAble() {
		return optionAble;
	}

	char getOption() {
		return option;
	}

	void setRoundScore(double in) {
		roundScore = in;
	}
	double getRoundScore() {
		return roundScore;
	}
};

vector<Score> calculateBonus(vector<Score> scores) {
	int length = scores.size();

	for (int i = 0; i < length; i++) {
		double basic = scores[i].getBasic();

		switch (scores[i].getBonus()) {
		case 'S':
			scores[i].setRoundScore(pow(basic, 1));
			break;
		case 'D':
			scores[i].setRoundScore(pow(basic, 2));
			break;
		case 'T':
			scores[i].setRoundScore(pow(basic, 3));
			break;
		default:
			cout << "Incorrect Bonus input." << endl;
			break;
		}
	}

	return scores;
}

double calculateRoundScore(vector<Score> score) {

	double temp;
	double sum = 0;

	score = calculateBonus(score);

	for (int i = 0; i < score.size(); i++) {
		temp = score[i].getRoundScore();

		if (score[i].isOptionAble()) {
			if (score[i].getOption() == '*') {
				if (i < 2) {
					if (score[i + 1].isOptionAble()) {
						if (score[i + 1].getOption() == '*') {
							score[i].setRoundScore(temp * 4);
						}
						else {
							score[i].setRoundScore(temp * 2);
						}
					}
					else {
						score[i].setRoundScore(temp * 2);
					}
				}
				else {
					score[i].setRoundScore(temp * 2);
				}
			}
			else {
				if (i < 2) {
					if (score[i + 1].isOptionAble()) {
						if (score[i + 1].getOption() == '*') {
							score[i].setRoundScore(temp * -2);
						}
						else {
							score[i].setRoundScore(temp * -1);
						}
					}
					else {
						score[i].setRoundScore(temp * -1);
					}
				}
				else {
					score[i].setRoundScore(temp * -1);
				}
			}
		}
		else {
			if (i < 2) {
				if (score[i + 1].isOptionAble()) {
					if (score[i + 1].getOption() == '*') {
						score[i].setRoundScore(temp * 2);
					}
				}
			}
		}

		sum += score[i].getRoundScore();
	}

	return sum;
}

vector<Score> covertScoreInfoArray(vector<string> strs) {

	vector<Score> result;

	double basic;
	char bo;
	bool optionAble;
	char option;
	int index = 0;
	string tmpStr;

	regex numPattern("[0-9]+");
	smatch numMatch;

	for (int i = 0; i < strs.size(); i++) {
	
		tmpStr = strs[i];
		optionAble = false;
		option = ' ';

		while (regex_search(tmpStr, numMatch, numPattern)) {
			for (size_t j = 0; j < numMatch.size(); j++) {
				string tmp = numMatch[j];
				index = tmp.length();
				basic = atof(tmp.c_str());
			}
			tmpStr = numMatch.suffix();
		}

		
		bo = strs[i].at(index);
		
		if (strs[i].length() == index + 2) {
			optionAble = true;
			option = strs[i].at(strs[i].length() - 1);
		}

		result.push_back(Score(basic, bo, optionAble, option));
	}

	return result;
	
}

vector<Score> createroundScore(string str) {
	vector<string> rounds;
	int count = 0;

	regex allPattern("^[0-9]+[S,D,T][*,#]?[0-9]+[S,D,T][*,#]?[0-9]+[S,D,T][*,#]?$");

	smatch sm;

	if (regex_match(str, sm, allPattern)) {

		regex roundsPattern("[0-9]+[S,D,T][*,#]?");
		smatch roundMatch;

		while (regex_search(str, roundMatch, roundsPattern)) {

			for (size_t i = 0; i < roundMatch.size(); i++) {
				rounds.push_back(roundMatch[i]);
			}

			str = roundMatch.suffix();
		}

	}
	else {
		cout << "Incorrect Input." << endl;
	}

	vector<Score> scores = covertScoreInfoArray(rounds);

	return scores;
}

void runDartGame(string str) {

	vector<Score> rounds = createroundScore(str);
	int sum = (int)calculateRoundScore(rounds);

	cout << "!] [ " << str << " ] Result : " << sum << endl;

}

int main(void) {

	vector<string> inputs = { "1S2D*3T", "1D2S#10S", "1D2S0T", "1S*2T*3S", "1D#2S*3S", "1T2D3D#", "1D2S3T*"};

	cout << "Input : score bonus option X3." << endl;
	cout << "       ex.1S2D*3T " << endl;
	cout << "Output : Round score sum Value." << endl;
	cout << "       ex. [ 1S2D*3T ] Result : 37" << endl << endl;

	for (int i = 0; i < inputs.size(); i++) {

		runDartGame(inputs[i]);
		cout << endl;

	}

	return 0;
}

