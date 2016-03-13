#include<vector>
using namespace std;

class Solution55 {
public:
	bool canJump(vector<int>& nums,int n) {
		if (n == 0 || n == 1)return true;

		for (int i = 0; i < n - 1; i++) {
			if (i + nums[i] >= n - 1 && canJump(nums, i + 1)) {
				return true;
			}
		}
		return false;
	}

	bool canJump(vector<int>& nums) {
		if (nums.size() == 0 || nums.size() == 1)return true;
		if (nums[0] == 0) return false;
		int max = nums[0];
		for (int i = 1; i < nums.size() - 1; i++) {
			if ((i + nums[i] > max)&&max>=i)max = i + nums[i];
		}
		if (max >= nums.size() - 1)return true;
		else return false;


	}
	int canJump2(vector<int>& nums) {
		if (nums.size() == 0 || nums.size() == 1)return 0;
		if (nums[0] == 0)return -1;
		int max = nums[0];
		vector<int> minjump(nums.size(), nums.size());
		minjump[0] = 0;
		for (int i = 1; i < nums.size() - 1; i++) {
			if ((i + nums[i] > max) && max >= i) {
				max = i + nums[i];
				int end = max > (nums.size() - 1) ? (nums.size() - 1) : max;
				for (int j = i; j <= end; j++) {
					minjump[j] = (minjump[i] + 1) > minjump[j] ? minjump[j] : (minjump[i] + 1);
				}
			}
		}
		if (max >= nums.size() - 1)return minjump[nums.size() - 1];
		else return -1;
	}

};
