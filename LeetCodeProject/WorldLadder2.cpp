#include<string>
#include<vector>
#include<unordered_set>
#include<stack>
#include<iostream>
#include<sstream>
#include<algorithm>
using namespace std;



class Solution126 {
public:
	vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
		stack<string> s;

		vector<string> result;
		s.push((beginWord));
		vector<vector<string>> finaResule;

		while (!s.empty())
		{
			string popout = s.top();
			s.pop();
			result.push_back(popout);
			if (popout == endWord) {
				finaResule.push_back(result);
			}
			else {
				unordered_set<string>::iterator it;
				for (it = wordList.begin(); it != wordList.end(); it++) {
					if (isOneDistance(*it, popout)) {
						s.push(*it);
					}
				}

			}




		}


	}

	bool isOneDistance(string s1, string s2) {
		if (s1.length() != s2.length())return false;
		int count = 0;
		for (int i = 0; i < s1.length(); i++) {
			if (s1[i] != s2[i])count++;
		}
		return count == 1 ? true : false;
		
	}
};

class AddBinary {
public:
	string addBinary(string s1, string s2) {
		int leng1 = s1.length()-1;
		int leng2= s2.length()-1;
		int maxleng = s1.length() > s2.length() ? s1.length() : s2.length();
		int maxi = maxleng ;
		int max = (leng1 < leng2 ? leng1 : leng2);
		string res(maxleng+1, '0');

		bool flag = false;
		while (leng1 >= 0 && leng2 >= 0) {
			if (s1[leng1] == '1'&&s2[leng2] == '1') {
				if (flag) {
					res[maxi--] = '1';
					flag = true;
				}
				else {
					res[maxi--] = '0';
					flag = true;
				}

			}
			else if ((s1[leng1] == '0'&&s2[leng2] == '1')||(s1[leng1] == '1'&&s2[leng2] == '0'))
			{
				if (flag) {
					res[maxi--] = '0';
					flag = true;
				}
				else {
					res[maxi--] = '1';
					flag = false;
				}
			}
			else if (s1[leng1] == '0'&&s2[leng2] == '0') {
				if (flag) {
					res[maxi--] = '1';
					flag = false;
				}
				else {
					res[maxi--] = '0';
					flag = false;
				}
			}
			leng1--;
			leng2--;
		}

		if (leng1 < 0 && leng2 < 0) {
			if (flag) {
				res[maxi] = '1';
			}
		}

		if (leng1 >= 0) {
			while (leng1 >= 0) {
				if (flag) {
					if (s1[leng1] == '1') {
						res[maxi--] = '0';
						flag = true;
					}else{
						res[maxi--] = '1';
						flag = false;
					}
				}
				else {
					res[maxi--] = s1[leng1];
				}
				leng1--;
			}
			if (flag) {
				res[maxi] = '1';
			}
		}
		if(leng2>=0) {
			while (leng2 >= 0) {
				if (flag) {
					if (s2[leng2] == '1') {
						res[maxi--] = '0';
						flag = true;
					}
					else {
						res[maxi--] = '1';
						flag = false;

					}
				}
				else {
					res[maxi--] = s2[leng2];
				}
				leng2--;
			}
			if (flag) {
				res[maxi] = '1';
			}


		}


		//return res;
		if (res[0] == '0')return res.substr(1, maxleng );
		else return res;
	}
	string countAndSay(int n) {
		stringstream strp;
		string begin = "1";
		string res=begin;

		for (int i = 1; i < n; i++) {
			int j = 0;
			char lastChar = ' ';
			int count = 0;
			res = "";
			while (j < begin.length()) {
				if (begin[j] == lastChar)
					count++;
				else {
					if (lastChar != ' ') {
						strp << count;
						string tmp = strp.str() + lastChar;
						strp.str("");
						res += tmp;
						lastChar = begin[j];
						count = 1;
					}
					else {
						lastChar = begin[j];
						count = 1;
					}
				}
				j++;
			}

			if (count != 0) {
				strp << count;
				string tmp = strp.str() + lastChar;
				strp.str("");
				res += tmp;
			}

			begin = res;
		}
		return res;
	}

	int compartVersionNumber(string s1, string s2) {
		int sOneLength = s1.length();
		int sTwoLength = s2.length();
		int i1, i2;
		i1 = i2 = 0;
		int last1 , last2 ;
		last1 = last2 = 0;

		while (i1 < sOneLength&&i2 < sTwoLength) {
			while (s1[i1] != '.'&&i1 < sOneLength)i1++;
			while (s2[i2] != '.'&&i2 < sTwoLength)i2++;

			while (s1[last1] == '0')last1++;
			while (s2[last2] == '0')last2++;
			
			while (last1 <= (i1-1)&&last2 <= (i2-1)) {
				if (s1[last1] == s2[last2]) {
					last1++;
					last2++;
					continue;
				}

				else if(s1[last1]<s2[last2]) {
					return -1;
				}
				else {
					return 1;
				}
				
			}

			if (last1 <= (i1 - 1)) {
				while (last1 <= (i1 - 1)) {
					if (s1[last1] == '0')last1++;
					else {
						return 1;
					}
				}
			}
			if (last2 <= (i2 - 1)) {
				while (last2 <= (i2 - 1)) {
					if (s2[last2] == '0')last2++;
					else {
						return -1;
					}
				}
			}
			last1 = i1 + 1;
			last2 = i2 + 1;
			i1++;
			i2++;
		}
		return 1;


	}

	
};

int t126main() {
	AddBinary a = AddBinary();
	cout << a.compartVersionNumber("01","1");
	cin.get();
	return 0;
}