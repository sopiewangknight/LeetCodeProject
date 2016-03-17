#include<vector>
#include<iostream>
using namespace std;

void merge(vector<int>& nums, int first, int mid, int end, vector<int>& tmp) {
	int end3 = end;
	int first3 = first;
	int first2 = mid + 1;
	int i = first;
	while (first <= mid&&first2 <= end) {
		if (nums[first] <= nums[first2]) {
			tmp[i] = nums[first];
			i++;
			first++;
		}
		else {
			tmp[i] = nums[first2];
			i++;
			first2++;
		}
	}
	if (first <= mid) {
		while (first <= mid) {
			tmp[i] = nums[first];
			i++;
			first++;
		}
	}
	if (first2 <= end) {
		while (first2 <= end) {
			tmp[i] = nums[first2];
			i++;
			first2++;
		}
	}
	for (int i = 0; i < (end3 - first3 + 1); i++) {
		nums[first3 + i] = tmp[first3 + i];
	}
	return;
}


void mergesort(vector<int>& nums,int first,int end,vector<int>& tmp) {

	if (first < end) {
		int mid = (first + end) / 2;
		mergesort(nums, first, mid,tmp);
		mergesort(nums, mid + 1, end,tmp);
		merge(nums, first, mid, end, tmp);
	}
}

int mergesort_main() {
	vector<int> tst{ 2,6,4,9,1,5,0,4 };
	vector<int> tmp(tst.size(),0);
	mergesort(tst, 0, tst.size() - 1, tmp);
	
	for (int i = 0; i < tst.size() ; i++)cout << tst[i] << " ";


	cin.get();
	return 0;
}