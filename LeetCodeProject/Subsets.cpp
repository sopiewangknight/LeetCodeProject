#include<vector>
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;
class Solution78 {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> container;
		vector<int> res;
		for (int i = 0; i <= nums.size(); i++) {
			kint_sub(nums, 0, i, res, i, container);
		}
		return container;
		 

	}

	void kint_sub(vector<int>& nums, int i,int k, vector<int>& res, int length,vector<vector<int>>& container) {
		if (res.size() == length) {
			sort(res.begin(), res.end(), less<int>());
			container.push_back(res);
			return;
		}
		if (i < nums.size() ) {
			int a = nums[i];
			res.push_back(a);
			kint_sub(nums, ++i, k - 1, res, length, container);
			res.pop_back();
			kint_sub(nums, i, k, res, length, container);
		}
		
	}
	void k_subset2(char* s, int k, vector<char>& res, int length) {
		if (res.size() == length) {
			for (int i = 0; i < res.size(); i++)cout << res[i];
			cout << endl;
			return;
		}

		if (*s != '\0') {
			char a = *s;
			res.push_back(a);
			s++;
			k_subset2(s, k - 1, res, length);
			res.pop_back();
			k_subset2(s, k, res, length);
		}


		return;
	}




	void k_subset(char* s, int k, char* res,int length) {
		if (*res=='\0') {
			cout << res-length << endl;
			return;
		}
		char a = *s;
		*res = a;
		s++;
		res++;
		k_subset(s, k - 1, res,length);

		if (*s != '\0') {
			res--;
			k_subset(s, k, res,length);
		}
		return;
	}
};

int t78_main()
{
	char s[] = "abcdefghijklmn";
	vector<char> r;
	char res[4];
	res[3] = '\0';
	vector<int> test = { 1,2,3,4,5,6 };
	Solution78 solution= Solution78();
	//solution.k_subset2(s,4,r,4);
	vector<vector<int>> result=solution.subsets(test);
	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < result[i].size(); j++) {
			cout << result[i][j];
		}
		cout << endl;
	}

	cin.get();
	
	return 0;
}