#include<string>
#include<vector>
#include<stack>
#include<iostream>

struct state {
	int positon;
	int length;
	state(int p, int l) :positon(p), length(l) {}
};
using namespace std;
class Solution91 {
public:

	//没有考虑0不能独立解码，错误！！！
	int linearNumDecodings(string s) {
		int leng = s.length();
		vector<int> res(leng, 0);
		res[leng - 1] = 1;
		if ((s[leng - 2] == '1' || s[leng - 2] == '2') && (
			s[leng - 1] <= '6'&&s[leng - 1] >= '0'
			)) {
			res[leng - 2] = 2;
		}
		else {
			res[leng - 2] = 1;
		}
		for (int j = leng - 3; j >= 0; j--) {
			if ((s[j] == '1' || s[j] == '2') && (
				s[j + 1] <= '6'&&s[j + 1] >= '0'
				)) {
				res[j] = res[j + 2] + res[j + 1];
			}
			else {
				res[j] = res[j + 1];
			}

		}
		return res[0];


	}

	//复杂度太高，要求要线性的
	int numDecodings(string s) {
		stack<state> stateStack;
		int k = 0;
		int leng = s.length();
		int cnt = 0;
		while (k <= (leng - 1) || !stateStack.empty())
		{
			if (k >= (leng - 1)) {
				cnt++;
				if (!stateStack.empty()) {
					state s = stateStack.top();
					stateStack.pop();
					k = s.positon + s.length;
					continue;
				}
				else {
					break;
				}
				
				
			}
			else {
				if (
					(s[k] == '2' || s[k] == '1')
					&& (
						((k+1)>(leng-1))||
						(s[k + 1] <= '6')
						&& (s[k + 1] >= '0')
						)
					)
				{
					state s = state(k,2);
					
					stateStack.push(s);
					k++;
				}
				else {
					k++;
				}

			}
			

		}
		return cnt;
	}
};

int t91main() {
	Solution91 s = Solution91();
	cout << s.numDecodings("1233421414131212121212") << endl;
	cout << s.linearNumDecodings("1233421414131212121212");
	cin.get();
	return 0;
}