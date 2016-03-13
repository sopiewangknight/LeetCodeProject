#include<vector>
using namespace std;
struct Interval {
	int start;
	int end;
	Interval() :start(0), end(0) {}
	Interval(int s, int e) :start(s), end(e) {}
};
class Solution56 {
public:
	vector<Interval> merge(vector<Interval>& intervals) {
		vector<Interval> interset;
		while (!intervals.empty()) {
			Interval first = intervals[0];
			for (int i = 1; i < intervals.size(); i++) {
				if (isInterset(intervals[i], first)) {
					interset.push_back(intervals[i]);
				}
			}


		}





	}
	bool isInterset(Interval a, Interval b) {
		if ((a.start <= b.end&&a.start >= b.start) || (a.end <= b.end&&a.end >= b.start) || (b.start <= a.end&&b.start >= a.start) || (b.end <= a.end&&b.end >= a.start)) {
			return true;
		}
		else {
			return false;
		}
	}
};