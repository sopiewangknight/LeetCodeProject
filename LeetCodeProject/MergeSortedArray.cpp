#include<vector>
#include<iostream>

using namespace std;
class Solution88 {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

		if (nums1.size()<unsigned(m + n))return;
		for (int i = m - 1; i >= 0; i--) {
			nums1[i + n] = nums1[i];
		}
		int flag1, flag2;
		flag1 = n;
		flag2 = 0;
		int i = 0;
		while (flag1 <= m + n - 1 && flag2 <= n - 1 && i <= m + n - 1) {
			if (nums1[flag1]<nums2[flag2]) {
				nums1[i] = nums1[flag1];
				flag1++;

			}
			else {
				nums1[i] = nums2[flag2];
				flag2++;
			}
			i++;
		}

		if (flag1 >= m + n) {
			while (flag2 <= n - 1 && i <= m + n - 1) {
				nums1[i] = nums2[flag2];
				flag2++;
				i++;
			}
		}
	}
};

int t5_main() {
	int arraynums[] = { 1,2,4,5,6,7,8,0,0,0,0,0,0,0,0,0 };

	int  arraynums2[] = {9,10,11,23,24,25};

	size_t count = sizeof(arraynums) / sizeof(int);

	vector<int> nums(arraynums, arraynums + count);

	

	 count = sizeof(arraynums2) / sizeof(int);
	vector<int> nums2(arraynums2, arraynums2 + count);

	

	Solution88 s = Solution88();
	s.merge(nums,7,nums2,6);



	cin.get();
	return 0;
}