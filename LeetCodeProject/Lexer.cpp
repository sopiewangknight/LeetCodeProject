#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;
void handlespace(char a[]);
void prePro();
int IsSymbol(char ch);
int IsKeyword(string str);


char tempstr[255] = {};
char word[255] = {};
bool temp = false;
string keyword[26] = {
	"main","if","then","while","do","static","defualt","do","int","double","struct","break","else","long","swtich","case","typedf","char","return","const","float","short","continue","for","void","sizeof" };

int keyword_num[26] = { 1,2,3,4,5,6,39,40,7,8,9,10,11,
12,13,14,15,16,17,18,19,20,21,22,23,24 };

char symbol[9] = { '+','-','*','/','=',';','(',')','#' };
int symbol_num[9] = { 27,28,29,30,38,41,42,43,0 };


int lexer_main() {
	char instr[255] = {};
	bool flag = false;
	string Token;
	char* str = NULL;
	char delims[] = " ";
	
	//freopen("lexer.txt", "r", stdin);
	//freopen("res.txt", "w", stdout);


	freopen("res.txt", "w", stdout);
	FILE* f=fopen("lexer.txt","r");
	while (fgets(instr, 255, f) != NULL) {
		handlespace(instr);
		str = strtok(word, delims);
		while (str != NULL) {
			if (IsKeyword(str)) {
				cout << str << "->" << IsKeyword(str);
			}
			else if (IsSymbol(*str)) {
				cout << str << "->" << *str;
			}
			str = strtok(NULL, delims);
		}
	}
	return 0;
}

bool IsLetter(char ch)
{
	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
		return true;
	return false;
}

bool IsDigit(char ch)
{
	if (ch >= '0'&&ch <= '9')
		return true;
	return false;
}

int IsSymbol(char ch)
{
	for (int i = 0; i<9; i++)
	{
		if (ch == symbol[i])
			return i;
	}
	return -1;
}
int IsKeyword(string str)
{
	for (int i = 0; i<26; i++)
	{
		if (str == keyword[i])
		{
			return i;
		}
	}
	return 25;
}



void handlespace(char a[])
{
	int j = 0;
	memset(word, 0, 255);
	temp = false;
	int start = 0;
	while (a[start] == ' ')start++;

	for (int i =start; i < strlen(a); i++) {
		if (a[i] != ' '&&a[i] != '\t') {
			word[j++] = a[i];
			temp = false;
		}
		else if (a[i] == ' '&&!temp) {
			word[j++] = a[i];
			temp = true;
		}
	}


}