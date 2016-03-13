#include<iostream>
#include<vector>
#include<stack>
using namespace std;
struct ListNode {
	int value;
	ListNode* next;
};
void createlist(vector<int>& nums, ListNode** head) {
	if (nums.size() == 0)return;
	(*head)->value = nums[0];
	ListNode* last = *head;
	ListNode* p;
	for (int i = 1; i < nums.size(); i++) {
		p = new ListNode();
		p->value = nums[i];
		last->next = p;
		last = p;
	}
}

void PrintListFromTail(ListNode* head) {
	if (head == NULL)return;
	if (head->next != NULL) {
		PrintListFromTail(head->next);
	}
	if (head != NULL) {
		cout << head->value << " ";
	}
}
void PrintListWithStack(ListNode* head) {
	stack<ListNode*> s;
	while (head != NULL) {
		s.push(head);
		head = head->next;
	}
	while (!s.empty()) {
		cout << s.top()->value << " ";
		s.pop();
	}
}

int tlistmain() {
	ListNode* head=new ListNode();
	head = NULL;
	/*vector<int> ts{1,2,3,4,5,6,7,8,9,10};
	createlist(ts, &head);*/
	PrintListFromTail(head);
	cout << endl;
	PrintListWithStack(head);
	cin.get();
	return 0;
}