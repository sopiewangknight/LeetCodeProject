#include<string>
#include<vector>
using namespace std;
class Solution72 {
public:
	//Accepted!
	int minDistance(string word1, string word2) {
		int leng1 = word1.length();
		int leng2 = word2.length();
		leng1++;
		leng2++;
		vector<vector<int> > res(leng1, vector<int>(leng2));
		res[0][0] = 0;
		for (int j = 1; j < leng1; j++)res[j][0] = j;
		for (int j = 1; j < leng2; j++)res[0][j] = j;
		for (int i = 1; i < leng1; i++) {
			for (int j = 1; j < leng2; j++) {
				int fn = (word1[i - 1] == word2[j - 1]) ? 0 : 1;
				fn += res[i - 1][j - 1];
				int min1 = (res[i - 1][j] < res[i][j - 1]) ? res[i - 1][j] : res[i][j - 1];
				int min2 = min1 + 1;
				int min = fn < min2 ? fn : min2;
				res[i][j] = min;
			}
		}
		return res[leng1 - 1][leng2 - 1];

	}
};