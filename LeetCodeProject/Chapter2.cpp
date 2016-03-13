#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

struct ListNode {
	int value;
	ListNode* next;
};

struct TreeNode {
	int value;
	TreeNode* left;
	TreeNode* right;
};
void _CreateTree(TreeNode* root, TreeNode* last, bool isLeft) {
	int inputValue;
	if (last == NULL) {
		cout << "input root value" << endl;
		cin >> inputValue;
		if (root == NULL) {
			root = new TreeNode();
		}
		root->value = inputValue;
		root->left = NULL;
		root->right = NULL;
		last = root;
		_CreateTree(root->left, last, true);
		_CreateTree(root->right, last, false);
	}
	else {
		if (isLeft) {
			cout << "input " << last->value << "'s left node" << endl;
		
		}
		else {
			cout << "input " << last->value << "'s right node" << endl;
		}
		cin >> inputValue;
		if (inputValue > 0) {
			root = new TreeNode();
			root->value = inputValue;
			root->left = NULL;
			root->right = NULL;
			if (isLeft) {
				last->left = root;
			}
			else {
				last->right = root;
			}
			last = root;
			_CreateTree(root->left, last, true);
			_CreateTree(root->right, last, false);
		}
	}
}

void CreateTree(TreeNode* root) {
	_CreateTree(root, NULL, true);
}

TreeNode* invertBT(TreeNode* root) {
	if (root == NULL) return NULL;
	TreeNode* left = root->left;
	TreeNode* right = root->right;
	root->left = right;
	root->right = left;
	invertBT(root->left);
	invertBT(root-> right);
	return root;
}

vector<vector<int>> levelOrder(TreeNode* root) {
	queue<TreeNode*> level;
	vector<vector<int>> res;
	vector<int> lineRes;
	level.push(root);
	int count = 1;
	TreeNode* tmp;
	while (!level.empty()) {
		lineRes.clear();
		for (int i = count; i > 0; i--) {
			tmp = level.front();
			lineRes.push_back(tmp->value);
			if (tmp->left != NULL) {
				level.push(tmp->left);
			}
			if (tmp->right != NULL) {
				level.push(tmp->right);
			}
			level.pop();

		}
		res.push_back(lineRes);
		count = level.size();
	}
	vector<int> swap;
	for (int i = 0;i< res.size()/2; i++) {
		swap = res[i];
		res[i] = res[res.size() - 1 - i];
		res[res.size() - 1 - i] = swap;
	}
	return res;
}

void inOrder(TreeNode* root) {
	if (root == NULL) return;
	inOrder(root->left);
	cout << root->value;
	inOrder(root->right);
}

void postOrder(TreeNode* root) {
	if (root == NULL) return;
	postOrder(root->left);
	postOrder(root->right);
	cout << root->value << " ";
}

void preOrderUnRecur(TreeNode* root) {
	stack<TreeNode*> nodeStack;
	TreeNode* i;
	i = root;

	while (!nodeStack.empty()||i!=NULL) {
		while (i!=NULL) {
			cout << i->value << " ";
			nodeStack.push(i);
			i = i->left;
		}
		if (!nodeStack.empty()) {
			i = nodeStack.top();
			nodeStack.pop();
			i = i->right;
		}
	}
}

vector<int> inOrderUnRecur(TreeNode* root) {
	stack<TreeNode*> nodeStack;
	TreeNode* i = root;
	vector<int> res;

	while (i != NULL || !nodeStack.empty()) {
		while (i != NULL) {
			nodeStack.push(i);
			i = i->left;
		}
		if (!nodeStack.empty()) {
			i = nodeStack.top();
			nodeStack.pop();
			res.push_back(i->value);
			
			i = i->right;
		}

	}
	return res;
}

int depth(TreeNode* root) {
	if (root == NULL) return 0;
	int leftHeight = depth(root->left);
	int rightHeight = depth(root->right);
	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}




void PrePrint(TreeNode* root) {
	if (root == NULL)return;
	if (root->value > 0)cout << root->value << " ";
	if (root->left != NULL) {
		PrePrint(root->left);
	}
	if (root->right != NULL) {
		PrePrint(root->right);
	}
}

void AddToTail(int value, ListNode** head) {
	if (*head == NULL) {
		ListNode* newhead = new ListNode();
		newhead->value = value;
		newhead->next = NULL;
		*head = newhead;
	}
	else {
		ListNode* i = *head;
		while (i->next != NULL) {
			i = i->next;
		}
		ListNode* n = new ListNode();
		n->value = value;
		n->next = NULL;
		i->next = n;
	}

}

void createList(vector<int>& nums,ListNode** head) {
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

void printList(ListNode** head) {
	ListNode* i = *head;
	while (i != NULL) {
		cout << i->value << "->";
		i = i->next;
	}
	cout << endl;
}


class SolutionChapter2 {
public:

	void ReplaceBlank(char str[],int len) {
		if (str == NULL || len <= 0)return;
		char* i = str;
		int length = 0;
		int blank = 0;
		int sumlength = 0;
		if (str == NULL)return;
		while (*i != '\0') {
			if (*i == ' ')blank++;
			length++;
			i = ++i;
		}
		
		sumlength = length + 2 * blank;
		if (sumlength > len)return;
		str[sumlength] = '\0';
		sumlength--;
		for (int i = length - 1; i >= 0; i--) {
			if (str[i] != ' ')str[sumlength--] = str[i];
			if (str[i] == ' ') {
				str[sumlength--] = '0';
				str[sumlength--] = '2';
				str[sumlength--] = '%';
			}

		}
		

	}
};


int sword_to_offer_main() {
	string patten = "annacanna";
	int n = patten.length();
	int* overlay = new int[n];
	int index;
	overlay[0] = -1;
	for (int i = 1; i < n; i++) {
		index = overlay[i - 1];
		while (index >= 0 && patten[i] != patten[index + 1]) {
			index = overlay[index];
		}
		if (patten[i] == patten[index + 1]) {
			overlay[i] = index + 1;
		}
		else {
			overlay[i] = -1;
		}
	}
	for (int i = 0; i < n; i++)cout << overlay[i] << " ";
	const string& target = "annbcdanacadsannacannaannannabnna";
	int target_length = target.length();
	int pattern_index = 0;
	int target_index = 0;
	while (pattern_index < n&&target_index < target_length) {
		if (target[target_index] == patten[pattern_index]) {
			++target_index;
			++pattern_index;
		}
		else if(pattern_index==0){
			++target_index;
		}
		else {
			pattern_index = overlay[pattern_index - 1] + 1;
		}
	}
	if (pattern_index == n) {
		cout <<"matched in"<< target_index - pattern_index;
	}
	else {
		cout << "do not match up" << endl;
	}







	//vector<vector<int>> res;
	/*TreeNode* root = new TreeNode();
	CreateTree(root);

	cout << "tree created" << endl;
	PrePrint(root);
	cout << "tree printed then tree's height:" << endl;

	vector<int> res = inOrderUnRecur(root);
	cout << "[";
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}
	cout << "]" << endl;*/

	//cout << depth(root);
	
	/*inOrder(root);
	cout << "postOrder:" << endl;
	postOrder(root);*/


	/*res = levelOrder(root);

	for (int i = 0; i < res.size(); i++) {
		cout << "[";
		for (int j = 0; j < res[i].size(); j++) {
			cout << res[i][j] << " ";
		}
		cout << "]" << endl;
	}*/

	/*PrePrint(invertBT(root));
	cout << "invert BT" << endl;*/
	cin.get();


	//int arr[] = {1,2,3,4,4,5,6,7,8,9};
	//for (int i = 0; i < sizeof(arr) / sizeof(int); i++)cout << arr[i] << " ";
	//vector<int> list(arr, arr + sizeof(arr) / sizeof(int));
	//ListNode* p = new ListNode();
	//ListNode** head;
	//head= &p;
	//createList(list, head);
	//printList(head);
	
	/*ListNode* null = NULL;
	AddToTail(100, &null);
	printList(&null);
	AddToTail(1001, &null);
	printList(&null);	
	AddToTail(1002, &null);
	printList(&null);
	AddToTail(1003, &null);
	printList(&null);
	AddToTail(1004, &null);
	printList(&null);*/







	/* ReplaceBlank ≤‚ ‘¥˙¬Î
	const int length = 20;
	char* str;
	str= "we are happy";
	char str2[length] = "we are happy";

	cout << str2<<endl;
	SolutionChapter2 s = SolutionChapter2();
	s.ReplaceBlank(str2,length);

	cout << str2<<endl;*/
	cin.get();
	return 0;
}