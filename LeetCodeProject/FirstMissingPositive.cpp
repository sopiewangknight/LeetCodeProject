#include<vector>
#include<iostream>
using namespace std;
class Solution41 {
public:
	int firstMissingPositive(vector<int>& nums) {
		for (int i = 0; i < nums.size(); i++) {
			int tmp;
			while (nums[i] != (i + 1)) {
				if (nums[i] <= 0 || nums[i] >= nums.size() || nums[i] == nums[nums[i] - 1])break;
				tmp = nums[i];
				nums[i] = nums[nums[i] - 1];
				nums[tmp - 1] = tmp;
			}
		}
		int res = 1;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != (i + 1)) {
				res = i+1;
				break;
			}
		}
		return res;
	}
};

int t41_main() {
	int arr[] = { 3,4,-1,1 };
	vector<int> ts(arr,arr+4);
	Solution41 s = Solution41();
	cout << s.firstMissingPositive(ts);
	cin.get();
	return 0;
}