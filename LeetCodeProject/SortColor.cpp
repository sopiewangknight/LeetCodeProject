#include<vector>

using namespace std;
class Solution75 {
public:
	void sortColors(vector<int>& nums) {

		int zeroflag = 0;
		int tmp;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] == 0) {
				tmp = nums[i];
				nums[i] = nums[zeroflag];
				nums[zeroflag] = tmp;
				zeroflag++;
			}
		}
		for (int i = zeroflag; i < nums.size(); i++) {
			if (nums[i] == 1) {
				tmp = nums[i];
				nums[i] = nums[zeroflag];
				nums[zeroflag] = tmp;
				zeroflag++;
			}
		}

	}
};