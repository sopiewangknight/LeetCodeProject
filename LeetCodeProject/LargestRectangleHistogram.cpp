#include<vector>
using namespace std;
class Solution84 {
public:

	//时间复杂度为平方，不能通过
	int largestRectangleArea(vector<int>& heights) {
		int n = heights.size();
		if (n == 0)return 0;
		vector<int> dp(n, 0);
		dp[0] = heights[0];
		for (int i = 1; i < n; i++) {
			int min = heights[i];
			int max = 0;
			for (int j = i - 1; j >= 0; j--) {
				if (heights[j] < min)min = heights[j];
				int area = (i - j + 1)*min;
				if (area > max)max = area;
			}
			dp[i] = max > dp[i - 1] ? max : dp[i - 1];
		}
		return dp[n - 1];
	}

	
};