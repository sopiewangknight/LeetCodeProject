#include<string>
#include<unordered_map>
#include<unordered_set>
#include<iostream>
using namespace std;
class Solution {
public:
	bool wordPattern(string pattern, string str) {
		unordered_map<string, char> cmap;
		unordered_map<char, string> smap;
		char* s = new char[str.length()];
		strcpy(s, str.c_str());
		char* word = strtok(s, " ");
		for (int i = 0; i < pattern.size(); i++) {
			if (word == NULL)return false;
			if (cmap.find(word) == cmap.end() && smap.find(pattern[i]) == smap.end()) {
				cmap[word] = pattern[i];
				smap[pattern[i]] = word;
				word = strtok(NULL, " ");
			}
			else if (cmap[word] != pattern[i] || smap[pattern[i]] != word) {
				return false;
			}
			else {
				word = strtok(NULL, " ");
			}
		}
		if (word != NULL)return false;
		else {
			return true;

		}
	}

	bool isValidSudoku(vector<vector<char>>& board) {
		int row = board.size();
		int range = board[0].size();
		unordered_set<char> setChar;

		for (int i = 0; i < row; i++) {
			int count = 0;
			int fillablei = i;
			int fillablej = -1;

			for (int j = 0; j < range; j++) {
				if (board[i][j] != '.') {
					count += board[i][j];
					if (setChar.find(board[i][j]) == setChar.end()) {
						setChar.insert(board[i][j]);
					}
					else {

						return false;
					}
				}
				else {
					fillablej = j;
				}
			}
			if (setChar.size() == 8) {
				board[fillablei][fillablej] = 55 - count;
				return isValidSudoku(board);
			}
			setChar.clear();
		}

		for (int i = 0; i < range; i++) {
			int fillablei = i;
			int fillablej = -1;
			int count = 0;
			for (int j = 0; j < row; j++) {
				if (board[j][i] != '.') {
					count += board[j][i];
					if (setChar.find(board[j][i]) == setChar.end()) {
						setChar.insert(board[j][i]);
					}
					else {

						return false;
					}
				}
				else {
					fillablej = j;
				}


			}
			if (setChar.size() == 8) {
				board[fillablej][fillablei] = 55 - count;
				return isValidSudoku(board);
			}
			setChar.clear();
		}


		for (int i = 0; i < 9; i++) {
			int row = i / 3;
			int range = i % 3;

			int cnt = 0;
			int fillablej = -1;
			int fillablek = -1;
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					if (board[row * 3 + j][range * 3 + k] != '.') {
						cnt += board[row * 3 + j][range * 3 + k];
						if (setChar.find(board[row * 3 + j][range * 3 + k]) == setChar.end()) {
							setChar.insert(board[row * 3 + j][range * 3 + k]);
						}
						else {
							return false;
						}
					}
					else {
						fillablej = j;
						fillablek = k;
					}

				}
			}

			if (setChar.size() == 8) {
				board[row * 3 + fillablej][range * 3 + fillablek] = 55 - cnt;
				return isValidSudoku(board);
			}
			setChar.clear();

		}
		return true;

	}

	bool isAnagram(string s1, string s2) {
		unordered_map<char, int> alphabets;
		for (int i = 0; i < s1.length(); i++) {
			if (alphabets.find(s1[i]) == alphabets.end()) {
				alphabets.insert(make_pair(s1[i], 1));
			}
			else {
				alphabets[s1[i]] += 1;
			}
		}

		for (int i = 0; i < s2.length(); i++) {
			if (alphabets.find(s2[i]) == alphabets.end()) {
				return false;
			}
			else {
				alphabets[s2[i]] -= 1;
				if (alphabets[s2[i]] <= 0)alphabets.erase(s2[i]);
			}
		}
		if (!alphabets.empty())
		{
			return false;
		}
		else {
			return true;
		}
	};

	vector<string> findRepeatedDnaSequences(string s) {
		int subLeng = 10;
		vector<string> res;
		if (s.length() <= 10)return res;
		unordered_map<string, int> strMap;
		for (int i = 0; (i + subLeng - 1) < s.length(); i++) {
			string tmp;
			tmp = s.substr(i, subLeng);
			if (strMap.find(tmp) == strMap.end()) {
				strMap.insert(make_pair(tmp, 1));
			}
			else {
				strMap[tmp] += 1;
				if (strMap[tmp] == 2) {
					res.push_back(tmp);
				}
			}
		}
		return res;
	}

};
	int wwmain() {
		Solution s = Solution();





		//cout << s.wordPattern("aaa", "aa aa aa aa");
		cin.get();
		return 0;



	}