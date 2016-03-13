#include<string>
#include<stack>
#include<iostream>
using namespace std;
struct state {
	int s1;
	int s2;
	int s3;
};
class Solution97 {
public:
	//¸´ÔÓ¶ÈÌ«¸ß
	bool isInterleave(string s1, string s2, string s3) {
		stack<state> stateStack;
		int flag1,flag2,flag3;
		flag1 = flag2 = flag3 = 0;
		int n = s3.length();
		while (flag3<n-1) {
			if (s3[flag3] == s1[flag1] && s3[flag3] != s2[flag2]) {
				flag3++;
				flag1++;
			}
			else if (s3[flag3] == s2[flag2] && s3[flag3] != s1[flag1]) {
				flag3++;
				flag2++;
			}
			else if (s3[flag3] != s2[flag2] && s3[flag3] != s1[flag1]) {
				if (stateStack.empty())break;
				state s = stateStack.top();
				stateStack.pop();
				flag1 = s.s1;
				flag2 = s.s2;
				flag3 = s.s3;
			}
			else {
				state s;
				s.s1 = flag1;
				s.s2 = 1+flag2;
				s.s3 = 1+flag3;
				stateStack.push(s);
				flag1++;
				flag3++;
			}


		}

		if (flag3 == (n - 1))return true;
		else return false;
	}
};

int t97main() {

	
		
	string s1 = "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa";
	string s2 = "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab";
	string s3 = "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab";

	Solution97 s = Solution97();
	cout << s.isInterleave(s1,s2,s3);


	cin.get();
	return 0;
}