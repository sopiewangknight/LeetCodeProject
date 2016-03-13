#include<vector>
#include<algorithm>
#include<map>
#include<iostream>

using namespace std;
class Solution217 {
public:
	bool containsDuplicate(vector<int>& nums) {
		if (nums.size()==0)
		{
			return false;
		}
		sort(nums.begin(), nums.end(), less<int>());
		
		for (int i = 0; i < nums.size()-1; i++) {
			if (nums[i]==nums[i+1])
			{
				return true;
			}
			
		}
		return false;
	}

	bool containDuplicate2(vector<int>& nums,int k)
	{
		if (nums.size() == 0 || nums.size() == 1)return false;

		for (int i = 0; i < nums.size(); i++) {

			int frontbord = (i + k )<nums.size() ? (i + k ) : nums.size();
			for (int j = i + 1; j <= frontbord; j++) {
				if (nums[i] == nums[j])return true;
			}

		}
		return false;

	}
	bool containDuplicate3(vector<int>& nums, int k) {
		if (nums.size() == 0)return false;
		map<int, int> ktable;
		map<int, int>::iterator ite;

		for (int i = 0; i < nums.size(); i++) {
			if (i < k)
			{
				ite = ktable.find(nums[i]);
				if (ite != ktable.end())return true;
				ktable.insert(make_pair(nums[i], i));
			}
			else {
			
				ite = ktable.find(nums[i]);
				if (ite != ktable.end())return true;
				ktable.insert(make_pair(nums[i], i));
				ktable.erase(nums[i - k]);
			}

		}
		return false;
	}
};
