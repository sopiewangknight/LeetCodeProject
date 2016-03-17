#include<iostream>


using namespace std;
struct RandomListNode
{
	int label;
	RandomListNode* next;
	RandomListNode* random;
	RandomListNode(int l) :label(l), next(NULL), random(NULL) {};
};


class Solution128 {
public:
	RandomListNode *copyRandomList(RandomListNode *head) {
		RandomListNode* resHead = NULL;
		if (head == NULL)return resHead;
		RandomListNode* iterate = head;
		
		while (iterate != NULL) {
			


			iterate = iterate->next;
		}

	}
};