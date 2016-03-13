#include<vector>
#include<iostream>

using namespace std;
class Solution33 {
public:
	int search(vector<int>& nums, int target) {
		if (nums.size() == 0)return -1;
		if (nums.size() == 1)return nums[0] == target ? 0 : -1;
		int start = findRotatePosition(nums);
		int begin = 0;
		int end = nums.size() - 1;
		if (start == 0) {
			int mid = (begin + end) / 2;
			while (begin <= end) {
				mid = (begin + end) / 2;
				if (nums[mid] == target) return mid;
				if (nums[mid] < target) {
					begin = mid + 1;
				}
				else {
					end = mid - 1;
				}
			}
		}

		if (target >= nums[0]) {
			end = (start - 1>=0)?start-1:0;
		}
		else {
			begin = start;
		}
		int mid = (begin + end) / 2;
		while (begin <= end) {
			mid = (begin + end) / 2;
			if (nums[mid] == target) return mid;
			if (nums[mid] < target) {
				begin = mid+1;
			}
			else {
				end = mid-1;
			}
		}
		return -1;
	}

	int findRotatePosition(vector<int>& nums) {

		int begin = 0;
		int end = nums.size() - 1;
		if (nums[begin] < nums[end])return begin;
		int mid = (begin + end) / 2;
		while (nums[begin] >= nums[end]) {
			if (end - begin == 1) {
				return end;
			}
			mid = (begin + end) / 2;
			if (nums[mid] >= nums[begin]) {
				begin = mid;
			}
			else if (nums[mid] <= nums[end]) {
				end = mid;
			}
		}
	}
};

int t33_main() {
	int arr[] = { 1,2,3,4,5 };
	vector<int> test(arr,arr+sizeof(arr)/sizeof(int));
	Solution33 s = Solution33();
	
	//cout << s.findRotatePosition(test)<<endl;
	cout << s.search(test, 5)<<endl;
	cin.get();
	return 0;
	
}