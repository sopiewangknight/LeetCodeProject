#include<vector>
#include<unordered_set>
#include<iostream>

using namespace std;
class Solution128 {
public:
	int longestConsecutive(vector<int>& nums) {
		unordered_set<int> set;
		for (int i = 0; i < nums.size(); i++)
		{
			set.insert(nums[i]);
		}

		int left, right;
		int maxLength = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (set.find(nums[i]) == set.end())continue;
			left = nums[i] - 1;
			right = nums[i] +1 ;
			while (set.find(left) != set.end() || set.find(right) != set.end()) {
				if (set.find(left) != set.end()) {
					set.erase(left);
					left -= 1;
				}
				else {
					set.erase(right);
					right += 1;
				}
			}
			if (maxLength < (right - left - 1))maxLength = (right - left - 1);
		}
		return maxLength;
	}
};

int t128main() {
	int arr[] = { 100, 4, 200, 1, 3, 2 };
	vector<int> test(arr,arr+6);
	Solution128 s = Solution128();
	cout << s.longestConsecutive(test);
	cin.get();
	return 0;
}