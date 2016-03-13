#include<vector>
#include<iostream>
using namespace std;
class Solution73 {
public:
	int rotatedSearch(vector<int>& nums, int target) {
		int begin = 0;
		int end = nums.size() - 1;
		int mid = (begin + end) / 2;
		while (begin < end) {
			mid = (begin + end) / 2;
			if (nums[mid] > nums[begin] && nums[mid] > nums[end]) {
				if (target == nums[mid])return mid;
				if (target < nums[mid]) {
					end = mid - 1;
				}
				else {
					begin = mid + 1;
				}
			}
			else if (nums[mid] < nums[begin] && nums[mid] < nums[end]) {
				if (target == nums[mid])return mid;
				if (target > nums[mid]) {
					begin = mid + 1;
				}
				else {
					end = mid - 1;
				}
			}

		}
		return -1;
	}

	int searchInsert(vector<int>& nums, int target) {
		int i;
		for ( i = 0; i < nums.size(); i++) {
			if (target < nums[i])return i;
		}
		return ++i;
	}
	int bsearchInsert(vector<int>& nums, int target) {
		int begin = 0;
		int end = nums.size() - 1;
		int mid;
		bool flag = true;
		while (flag) {
			mid = (begin + end) / 2;
			if (nums[mid] < target&&target <= nums[mid + 1]) {
				flag = false;
			}
			else if(target>=nums[mid]){
				begin = mid + 1;
			}
			else {
				end = mid - 1;
			}

		}
		return mid;
	}

	void setZeroes(vector<vector<int>>& matrix) {
		if (matrix.size() == 0)return;
		int row = matrix.size();
		int range = matrix[0].size();
		vector<int> zeroRow, zeroRange;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < range; j++) {
				if (matrix[i][j] == 0)
				{
					zeroRow.push_back(i);
					zeroRange.push_back(j);
				}
			}
		}
		for (int i = 0; i < zeroRow.size(); i++) {
			for (int j = 0; j < range; j++) {
				matrix[zeroRow[i]][j] = 0;
			}
		}

		for (int i = 0; i < zeroRange.size(); i++) {
			for (int j = 0; j < row; j++) {
				matrix[i][zeroRange[j]] = 0;
			}
		}


	}
};

int t73_main()
{
	vector<int> test{ 4 ,5, 6, 7, 0, 1, 2 };
	Solution73 s = Solution73();
	s.rotatedSearch(test,1);


	cin.get();
	return 0;
}