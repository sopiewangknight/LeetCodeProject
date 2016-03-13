#include<vector>
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)>(y)?(y):(x))



using namespace std;




class Solution53 {
public:
	int maxSubArray(vector<int>& nums) {

		int begin = 0;
		int sum = 0;
		int max = INT16_MIN;
		for (int i = 0; i < nums.size(); i++) {
			sum += nums[i];
			if (sum < nums[i]) {
				sum = nums[i];
				begin = i;
			}
			if (sum > max)sum = max;
		}
		return max;
	}
	int dpMaxSubArray(vector<int>& nums) {
		if (nums.size() == 0)return 0;
		int local = nums[0];
		int global = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			local = (local + nums[i])>local ? local + nums[i] : local;
			global = global > local ? global : local;
		}
		return global;

	}

	int dpMaxProductArray(vector<int>& nums) {
		if (nums.size() == 0)return 0;
		int max_local = nums[0];
		int min_local = nums[0];
		int global = nums[0];

		for (int i = 1; i < nums.size(); i++) {
			int max_copy = max_local;
			max_local = MAX(MAX(nums[i]*max_local,nums[i]),nums[i]*min_local);
			min_local = MIN(MIN(nums[i],nums[i]*min_local),nums[i]*max_copy);
			global = MAX(global,max_local);
		}
		return global;

	}

	int DPmaxSubArray(vector<int>& nums) {
		vector<int> dp = nums;
		int max = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			dp[i] = dp[i - 1] <= 0 ? nums[i] : dp[i - 1] + nums[i];
			if (dp[i] > max)max = dp[i];
		}
		return max;


	}
};