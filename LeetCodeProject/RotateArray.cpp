#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
class Solution189 {
public:
	void rotate(vector<int>& nums, int k) {

		if (nums.size() == 0 || nums.size() == 1)
			return;
		vector<int>::iterator it=nums.begin();
		reverse(nums.begin(), nums.end());
		for (int i = 0; i < k; i++)it++;
		reverse(nums.begin(), it);
		reverse(it, nums.end());
		
	}


};

int t2_main() {
	Solution189 s = Solution189();
	int arraynums[] = { 0,2,3,4,6,7,8,9,22,24,26,27,28,30 };
	size_t count = sizeof(arraynums) / sizeof(int);
	vector<int> nums(arraynums, arraynums + count);

	s.rotate(nums,0);

	vector<int>::iterator i;
	for (i = nums.begin(); i != nums.end(); i++) {
		cout << *i << "  ";
	}

	cin.get();
	return 0;
}