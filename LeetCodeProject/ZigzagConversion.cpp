#include<string>
#include<iostream>

using namespace std;


class Solution6 {
public:
	string convert(string s, int numRows) {
		
		int mod = 2 * numRows - 2;
		string res = s;
		int length = s.length();
		int k = 0;
		for (int i = 0; i < numRows; i++) {

			if (i == 0 || i == (numRows - 1)) {
				int j = 0;
				while ((i + mod*j) < length) {
					res[k++] = s[i + mod*j];
					j++;
				}
			}
			else {
				for (int j = 0; j < (1+length/mod); j++)
				{
					if ((i + j*mod) < length) {
						res[k++] = s[i + j*mod];
					}
					else {
						break;
					}
					if ((i + j*mod + numRows - 1) < length) {
						res[k++] = s[i + j*mod + numRows - 1];
					}
					else {
						break;
					}
				}
			}
		}
		return res;
	}
};
int t9main() {
	Solution6 s = Solution6();
	
	cout << s.convert("PAYPALISHIRING",4);
	cin.get();
	return 0;
}