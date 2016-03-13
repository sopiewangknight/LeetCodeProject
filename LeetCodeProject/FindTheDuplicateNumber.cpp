#include<vector>
using namespace std;

class Solution287 {
public:
	int findDuplicate(vector<int>& nums) {
		
		int max = nums.size() - 1;
		int min = 1;//change to zero and the accepted!???

		while (min <= max) {
			int middle = min + (max - min) / 2;
			int leftcount = 0;

			for (int i = 0; i < nums.size(); i++) {
				if (nums[i] <= middle)leftcount++;
			}
			if (leftcount<middle) {
				min = middle + 1;
			}
			else {
				max = middle - 1;
			}


		}
		return min;

	}
};