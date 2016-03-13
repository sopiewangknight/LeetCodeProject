#include<iostream>
using namespace std;
class Solution264 {
public:
	int nthUglyNumber(int n) {
		int two = 2;
		int three = 3;
		int five = 5;
		int i = 1;
		int res = 1;
		while (i < n) {
			if (two < three&&two < five) {
				res = two;
				two += 2;
				i++;
				continue;
			}
			if (three < two&&three < five) {
				res = three;
				three += 3;
				i++;
				continue;

			}
			if (five < three&&five < two) {
				res = five;
				five += 5;
				i++;
				continue;

			}
			if (two == three&&two < five) {
				res = two;
				two += 2;
				three += 3;
				i++;
				continue;

			}
			if (two == five&&two < three) {
				res = two;
				two += 2;
				five += 5;
				i++;
				continue;

			}
			if (three == five&&three < two) {
				res = three;
				three += 3;
				five += 5;
				i++;
				continue;

			}
			if (two == five&&two == three) {
				res = two;
				two += 2;
				three += 3;
				five += 5;
				i++;
				continue;

			}

		}
		return res;
	}
};

int t264main()
{
	Solution264 s = Solution264();
	cout << s.nthUglyNumber(40);
	cin.get();
	return 0;
}