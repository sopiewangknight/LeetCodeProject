#include<vector>
#include<iostream>

using namespace std;
class Solution198 {
public:
	int rob(vector<int>& nums) {
		int length = nums.size();

		if (length == 0)return 0;
		if (length == 1)return nums[0];
		if (length == 2)return nums[0]>nums[1] ? nums[0] : nums[1];
		if (length == 3) return nums[1]>(nums[0] + nums[2]) ? nums[1] : (nums[0] + nums[2]);
		vector<int> dp(length + 1, 0);
		dp[1] = nums[0];
		dp[2] = nums[0]>nums[1] ? nums[0] : nums[1];
		dp[3] = nums[1]>(nums[0] + nums[2]) ? nums[1] : (nums[0] + nums[2]);
		for (int j = 4; j <= length; j++) {
			int fn2 = nums[j-1] + dp[j - 2];
			int fn3 = nums[j - 1-1] + dp[j - 3];
			dp[j] = (fn2 > fn3) ? fn2 : fn3;
		}
		return dp[length];
	}
};

int t198main() {
	vector<int> test{ 1,1,1,1 };
	Solution198 s = Solution198();
	cout << s.rob(test);
	cin.get();
	return 0;
}