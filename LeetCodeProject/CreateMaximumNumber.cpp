#include<vector>
#include<iostream>
using namespace std;

class Solution321 {
public:

	//最终还是不对的
	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {

		if ((nums1.size() + nums2.size()) >= k) {

			vector<int> a1, a2,res;
			vector<int> b1, b2;

			bool isA;
			for (int i = 1; i <= k; i++) {
				a1 = kMax(nums1, i, 0, nums1.size() - 1);
				a2 = kMax(nums2, i, 0, nums2.size() - 1);
				if (vectorGreater(a1, a2, res,isA)) {
					if (isA) {
						if ((k - i) <= nums2.size()) {
							b1=kMax(nums2, k-i, 0, nums2.size() - 1);
							for (int ite = 0; i < b1.size(); ite++)a1.push_back(b1[i]);
							return a1;
						}
						else {
							continue;
						}

					}
					else {
						if ((k - i) <= nums1.size()) {
							b2 = kMax(nums1, k - i, 0, nums1.size() - 1);
							for (int ite = 0; i < b2.size(); ite++)a2.push_back(b2[i]);
							return a2;
						}
						else {
							continue;
						}
						
					}
				}
				else {
					continue;
				}
			}
		}
		else {
			throw exception("invalid input");
		}



	}
	//a 大于b
	bool vectorGreater(vector<int>& a, vector<int>& b,vector<int>& res,bool& isA) {
		int i;
		for ( i = 0; i < a.size(); i++) {
			if (a[i] > b[i]) {
				res = a;
				isA = true;
				return true;
			}
			else if (a[i] < b[i]) {
				res = b;
				isA = false;
				return true;
			}
			else continue;
		}
		if (i == a.size())return false;
	}

	//最大的K位数
	vector<int> kMax(vector<int>& nums, int k,int start, int end) {
		if (k == 0)
		{
			vector<int> r;
			return r;
		}
		if (start <= end) {
			if (start == end) {
				vector<int> t(1,nums[start]);
				return t;
			}
			int position = start;
			int max = nums[start];

			for (int j = start + 1; j <= end; j++) {
				if (nums[j] > max) {
					max = nums[j];
					position = j;
				}
			}
			vector<int> rear;
			vector<int> front;
			vector<int> res;
			if ((end - position + 1) >= k) {			
				rear = kMax(nums, k - 1, position + 1, end);
			}
			else {
				int frontLeng = k - (end - position + 1);
				front = kMax(nums, frontLeng, start, position - 1);
				for (int j = position + 1; j <= end; j++)rear.push_back(nums[j]);

			}
			for (int i = 0; i < front.size(); i++)res.push_back(front[i]);
			res.push_back(max);
			for (int i = 0; i < rear.size(); i++)res.push_back(rear[i]);
			return res;
		}
		else {
			vector<int> r;
			return r;
		}
		
	}

};

int t321main() {
	Solution321 s = Solution321();
	vector<int> res,res2;
	vector<int> ts1{ 3, 4, 6, 5 };
	vector<int> ts2{ 9, 1, 2, 5, 8, 3 };


	res2 = s.maxNumber(ts1, ts2, 5);
	for (int i = 0; i < res2.size(); i++)cout << res2[i] << " ";
	cin.get();
	return 0;

}