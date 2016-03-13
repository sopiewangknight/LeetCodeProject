#include<vector>
#include<iostream>

using namespace std;
class Solution34 {
public:
	vector<int> searchRange(vector<int>& nums, int target) {

		int begin = 0;
		int end = nums.size() - 1;
		int mid;
		vector<int> res;
		while (begin <= end) {
			mid = (begin + end) / 2;
			if (nums[mid] == target && (mid - 1 < 0 || nums[mid - 1] < target)) {
				res.push_back(mid);
				break;
			}
			if(target<=nums[mid]) {
				end = mid - 1;
			}
			else 
			{
				begin = mid + 1;
			}
		}
		if (res.empty())res.push_back(-1);
		 begin = 0;
		 end = nums.size() - 1;
		 mid;
		while (begin <= end) {
			mid = (begin + end) / 2;
			if (nums[mid] == target && (mid + 1 >=nums.size() || nums[mid + 1] > target)) {
				res.push_back(mid);
				break;
			}
			if (target < nums[mid]) {
				end = mid - 1;
			}
			else
			{
				begin = mid + 1;
			}
		}
		if (res.size() == 1)res.push_back(-1);
		return res;
	}
};

int t34_main() {
	int arr[] = {3,3,3,3,3,3,4,5,6,7};
	vector<int> test(arr,arr+sizeof(arr)/sizeof(int));
	Solution34 s = Solution34();
	vector<int> res = s.searchRange(test, 8);
	for (int i = 0; i < res.size(); i++)cout << res[i]<<"  ";
	cin.get();
	return 0;
}