#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

class Solution279 {
public:
	int numSquares(int n) {
		int length = floor(sqrt(n));
		vector<int> table(length + 1, 0);
		vector<int> dp(n + 1, 0);
		for (int i = 1; i < table.size(); i++)table[i] = i*i;
		dp[1] = 1;
		for (int i = 1; i < dp.size(); i++) {
			int max_table_i = floor(sqrt(i));
			int min = INT16_MAX;
			for (int k = 1; k <= max_table_i; k++) {
				if (dp[i - table[k]] < min)min = dp[i - table[k]];
			}
			dp[i] = min+1;
		}
		return dp[n];
	}
};