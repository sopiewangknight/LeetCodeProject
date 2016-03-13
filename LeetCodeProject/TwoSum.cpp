#include<vector>
#include<algorithm>

using namespace std;
class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end(), less<int>());
		vector<int> res;
		int begin = 0;
		int end = nums.size()-1;
		while (begin < end) {
			if (nums[begin] + nums[end] == target) {
				res.push_back(begin);
				res.push_back(end);
				return res;
			}
			else if (nums[begin] + nums[end] < target)begin++;
			else end--;
			
		}
		return res;

	}
};
