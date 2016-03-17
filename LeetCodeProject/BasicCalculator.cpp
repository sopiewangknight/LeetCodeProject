#include<string>
#include<iostream>
#include<stack>
#include<sstream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution227 {
public:

	void intToEngWord(int num) {
		stringstream s;
		s << num;
		string res = s.str();
		int length = res.length();
		string digits[10] = {"zero","one","two" ,"three" ,"four" ,"five" ,"six" ,"seven" ,"eight" ,"nine" };
		string jump[5] = { "","thousand","million","billion","trilion" };
		string two[10] = {"ten","twenty","thirty","fourty","fifty","sixth","seventy","eighty","nighty"};

		for (int i = 0; i < length;i++) {
			int weishu = length - i;
			int modshu = weishu % 3;
			int jibie = weishu / 3;
			int dig = res[i] - '0';
			if (modshu == 1) {
				cout << digits[dig] << " " << jump[jibie] << " ";
			}
			else if (modshu == 2) {
				cout << two[dig-1] << " ";
			}
			//mo shu wei 0
			else {
				cout << digits[dig] << " " << "hundred" << " ";
			}
				
			
		}


	}
	int calculate(string s) {
		stack<int> num;
		stack<char>symbol;
		symbol.push('#');
		char* res = postfix(discardSpace(s));
		bool zeroDivisor = false;
		for (int i = 0; i < s.length()&&res[i]!='\0'; i++) {
			if (isSymbol(res[i])) {
				int top1 = num.top();
				num.pop();
				int top2 = num.top();
				num.pop();
				
				if (res[i] == '+') {
					num.push(top2 + top1);
				}
				else if (res[i] == '-') {
					num.push(top2 - top1);
				}
				else if (res[i] == '*') {
					num.push(top2 *top1);
				}
				else {
					if (top1 != 0) {
						num.push(top2 /top1);
					}
					else {
						zeroDivisor = true;
						break;
					}
				}
			}
			else {

				num.push(res[i]-'0');
			}


		}
		

		if (zeroDivisor) {
			return -1;
		}
		else {
			return num.top();
		}
	}

	char* postfix(char* s) {
		int len = strlen(s);
		char* res = new char[len];
		int i = 0;
		stack<char> symstack;
		symstack.push('#');
		for (int j = 0; j < len; j++) {
			if (isSymbol(s[j])) {
				if (priority(s[j])>priority(symstack.top())) {
					symstack.push(s[j]);
				}
				else {
					res[i++]=symstack.top();
					symstack.pop();
					symstack.push(s[j]);
				}
			}
			else {
				res[i++] = s[j];
			}
		}
		while (symstack.top() != '#') {
			res[i++] = symstack.top();
			symstack.pop();
		}
		res[i] = '\0';
		return res;
	}
	int priority(char a) {
		switch (a)
		{
		case '+':
		case '-': return 1; break;
		case '*':
		case '/':return 2; break;
		default:
			return 0;
			break;
		}
	}

	bool isSymbol(char c) {
		if (c == '+' || c == '-' || c == '*' || c == '/')return true;
		else return false;
	}

	char* discardSpace(string s) {

		int j = 0;
		int i = 0;
		char* res = new char[s.length()];
		while (j < s.length()) {
			while (s[j] == ' '&&j<s.length())j++;
			while (s[j] != ' '&&j<s.length()) {
				res[i++] = s[j++];
			}
		}
		res[i] = '\0';
		return res;

	}




	void queen(int n) {
		vector<int> answer(n, 0);
		for (int i = 0; i < n; i++) {
			answer[0] = i;
			queenN(answer, 1);
		}
	}

	void queenN(vector<int>& answer,int range) {
		if (range == answer.size()) {
			for (int i = 0; i < answer.size(); i++)cout << answer[i] << " ";
			cout << endl;
		}

		for (int i = 0; i < answer.size(); i++) {
			bool flag = true;;
			for (int j = 0; j < range; j++) {
				if (i == answer[j] || abs(answer[j] - i) == abs(j  - range)) {
					flag = false;
				}
			}
			if (flag) {
				answer[range] = i;
				queenN(answer, range + 1);
			}
		}

	}

	int zeroOnePack(vector<vector<int>> goods, int packWeight) {
		int** p = new int*[goods.size()+1];
		for (int i = 0; i <= goods.size(); i++) {
			p[i] = new int[packWeight+1] ;
		}
		int minWeight = INT16_MAX;
		for (int i = 0; i < goods.size(); i++) {
			if (goods[i][0] < minWeight)minWeight = goods[i][0];
		}
		for (int j = 0; j <= goods.size(); j++) {
			for (int i = 0; i <= minWeight; i++) {
				p[j][i] = 0;
			}
		}
		for (int i = 0; i <= packWeight; i++) {
			p[0][i] = 0;
		}


		for (int i = 1; i <= goods.size(); i++) {
			for (int j = minWeight; j <= packWeight; j++) {
				if ((j - goods[i-1][0])>=0) {
					p[i][j] = p[i - 1][j]>(p[i - 1][j - goods[i-1][0]]+goods[i][1]) ? p[i - 1][j] : (p[i - 1][j - goods[i-1][0]] + goods[i][1]);
				}
				else {
					p[i][j] = p[i - 1][j];
				}

			}
		}
		return p[goods.size()][packWeight];

	}

	string simplifyPath(string path) {
		stack<char> res;

		for (int i = 0; i < path.length(); i++) {
			if (path[i] == '.') {
				if (path[i + 1] == '.')
				{
					int popcnt = 2;
					while (!res.empty() && popcnt > 0) {
						if (res.top() == '/') {
							popcnt--;
						}
						while (res.top() != '/') {
							res.pop();
						}
					}
					i++;
				}
				else {

					while (res.top() != '/') {
						res.pop();
					}
				
				}

			}
			else {
				
					res.push(path[i]);
				
				
			}
		}

		string s = "";
		if (res.top() == '/')res.pop();
		while (!res.empty())
		{
			char tmp = res.top();
			res.pop();
			s = tmp + s;
		}

		return s;

	}

	bool wordPatten(string pattern, string str) {
		unordered_map<string, char> map;
		unordered_map<char, string> smap;
		char* s = new char[str.length()];
		strcpy(s, str.c_str());
		char* word = strtok(s, " ");
		for (int i = 0; i < pattern.size(); i++) {
			if (word == NULL)return false;
			if (map.find(word) == map.end() && smap.find(pattern[i]) == smap.end()) {
				map[word] = pattern[i];
				smap[pattern[i]] = word;
				word = strtok(NULL, " ");
			}
			else if (map[word] != pattern[i] || smap[pattern[i]] != word) {
				return false;
			}
			else {
				word = strtok(NULL, " ");
			}
		}
		return true;


	}
};

int t227main() {

	Solution227 s = Solution227();

	cout << s.simplifyPath("/home/./darkknight/../../myhome/");






	/*vector<int> t;

	vector<vector<int>> ts;
	t = { 3,4 };
	ts.push_back(t);
	t = { 4,5 };
	ts.push_back(t);
	t = { 5,6 };
	ts.push_back(t);
	cout<<s.zeroOnePack(ts, 10);*/



	//s.queen(8);
	//string ts = "9+   6   /    4*  3  -2";
	//cout << s.postfix(s.discardSpace(ts))<<endl;
	//cout << s.calculate(ts);
	//s.intToEngWord(123456789);

	cin.get();
	return 0;
}