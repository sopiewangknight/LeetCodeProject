#include<iostream>

using namespace std;
struct TreeNode {
	int value;
	TreeNode* left;
	TreeNode* right;
};


TreeNode* reConstruct
(
	int* startPre, int* endPre,
	int* startIn, int* endIn
) 
{
	int rootValue = *startPre;
	TreeNode* root = new TreeNode();
	root->value = rootValue;
	root->left = NULL;
	root->right = NULL;

	if (startPre == startPre) {
		if (startIn == endIn&&*startIn == *endIn) {
			return root;
		}
		else {
			throw exception("invalid input");
		}
	}

	int* middle = startIn;
	while (*middle != rootValue) {
		middle++;
	}
	if (middle > endIn) {
		throw exception("invalid input");
	}
	int leftLeng = middle - startIn;
	int* leftPreEnd = startPre + leftLeng;
	if (leftLeng > 0) {
		root->left = reConstruct(startPre + 1, leftPreEnd, startIn, middle - 1);
	}
	if (leftLeng < endPre - startPre) {
		root->right = reConstruct(leftPreEnd+1,endPre,middle+1,endIn);
	}
	return root;
}
TreeNode* Construct(int* preOrder, int* inOrder, int length) {
	if (preOrder == NULL || inOrder == NULL || length <= 0 )return NULL;
	return reConstruct(preOrder, preOrder + length - 1, inOrder, inOrder + length - 1);
}

int treemain() {

	int pre[] = {1,2,4,7,3,5,6,8};
	int ino[] = {4,7,2,1,5,3,8,6};
	int length = sizeof(pre) / sizeof(int);
	TreeNode* root = Construct(pre,ino,length);

	cout << "heh";
	cin.get();
	return 0;
}