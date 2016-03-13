#include<string>
#include<unordered_set>
#include<iostream>
using namespace std;
int cnt = 0;
void permutation(string s, int k,int length) {
	if (k >= length)return;
	if (k == (length - 1)) {
		cout <<cnt<<":"<< s << endl;
		cnt++;
		return;
	}
	permutation(s, k + 1, length);

	unordered_set<char> set;
	
	for (int j = k+1; j < length; j++) {
		if (set.find(s[j]) == set.end()) {
			set.insert(s[j]);
			if (s[j] != s[k]) {
				char tmp;
				tmp = s[j];
				s[j] = s[k];
				s[k] = tmp;
				permutation(s, k + 1, length);
				tmp = s[j];
				s[j] = s[k];
				s[k] = tmp;
			}
		}
		
	}
	set.clear();
}

int perm_main() {
	string s = "1223";
	permutation(s, 0, s.length());
	cout << endl;
	cout << "count:" << cnt << endl;
	cin.get();
	return 0;
}
