#include<vector>
#include<algorithm>
#include <stdlib.h>

struct Interval {
	int start;
	int end;
	Interval() :start(0) , end(0) {}
	Interval(int s, int e) :start(s), end(e) {}
};

using namespace std;
class Solution57 {
public:
	bool static compare( Interval a,  Interval b) {
		return a.start<b.start;
	}
	/*vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		vector<Interval> interset;
		vector<Interval> res;
		Interval tmp;
		for (int i = 0; i < intervals.size(); i++) {
			tmp = intervals[i];
			if ((tmp.start <= newInterval.end&&tmp.start >= newInterval.start) || (tmp.end <= newInterval.end&&tmp.end >= newInterval.start) || (newInterval.start <= tmp.end&&newInterval.start >= tmp.start) || (newInterval.end <= tmp.end&&newInterval.end >= tmp.start))
			{
				interset.push_back(tmp);
			}
			else {
				res.push_back(tmp);
			}
		}
		for (int i = 0; i < interset.size(); i++) {
			tmp = interset[i];
			int left = tmp.start < newInterval.start ? tmp.start : newInterval.start;
			int right = tmp.end > newInterval.end ? tmp.end : newInterval.end;
			newInterval.start = left;
			newInterval.end = right;
		}
		res.push_back(newInterval);
		sort(&res, &res + res.size(), compare);
		return res;

	}*/

};