#include<stdio.h>
#include<malloc.h>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

#define BLOCKSIZE 1024
#define SIZE 1024000
#define END  65535
#define FREE 0
#define ROOTBLOCKNUM 2
#define MAXOPENFILE 10
#define FILENAME "C:\\Users\\darkknight\\Desktop\\data\\myfats"
#define MODE "r"

typedef struct FCB
{
	unsigned char attribute;
	unsigned short time;
	unsigned short data;
	unsigned short first;
	unsigned long length;
	short free;
	char filename[8];
	char exname[4];
}fcb;

typedef struct FAT
{
	unsigned short id;
}fat;
typedef struct USEROPEN
{
	char filename[8];
	char exname[4];
	unsigned char attribute;
	unsigned short time;
	unsigned short data;
	unsigned short first;
	unsigned long length;
	short free;
	int dirno;
	int diroff;
	int count;
	char dir[80];
	short fcbstate;
	short topenfile;
}useropen;

typedef struct BLOCK0
{
	char information[200];
	unsigned short root;
	unsigned char* startblock;
}block0;

unsigned char* myvhard;
useropen openfilelist[MAXOPENFILE];
useropen* ptrcurdir;
char currentdir[80];
unsigned char* startp;

void startsys();
void my_format();
int do_write(int fd, char* text, int len, int wstyle);
int do_read(int fd, int len, char* text);



void startsys()
{	
	myvhard = (unsigned char*)malloc(SIZE);
	memset(myvhard, 0, SIZE);
	FILE* fp;
	if ((fp = fopen(FILENAME, MODE)) != NULL) {
		fread(myvhard, SIZE, 1, fp);
		fclose(fp);
	}
	else {
		cout << "file not exists;please create and init the file system" << endl;
		my_format();
	}
	strcpy(openfilelist[0].filename, "root");
	strcpy(openfilelist[0].exname, "di");
	openfilelist[0].attribute = 0;
	openfilelist[0].time = ((fcb*)(myvhard + 5 * BLOCKSIZE))->time;
	openfilelist[0].data = ((fcb*)(myvhard + 5 * BLOCKSIZE))->data;
	openfilelist[0].first = ((fcb*)(myvhard + 5 * BLOCKSIZE))->first;
	openfilelist[0].length = ((fcb*)(myvhard + 5 * BLOCKSIZE))->length;
	openfilelist[0].fcbstate = 0;
	openfilelist[0].free = 1;
	openfilelist[0].dirno= ((fcb*)(myvhard + 5 * BLOCKSIZE))->first;
	openfilelist[0].diroff = ((fcb*)(myvhard + 5 * BLOCKSIZE))->first;;

	ptrcurdir = &openfilelist[0];
	int i;
	for (i = 1; i < MAXOPENFILE; i++) {
		strcpy(openfilelist[i].filename, "\0");
		strcpy(openfilelist[i].exname, "\0");
		openfilelist[i].time = 0;
		openfilelist[i].data = 0;
		openfilelist[i].first = 0;
		openfilelist[i].length = 0;
		openfilelist[i].fcbstate = 0;
		openfilelist[i].topenfile = 0;
		openfilelist[i].count = 0;
		openfilelist[i].free = 0;
	}
	strcpy(currentdir, "\\root\\");
	strcpy(openfilelist[0].dir, currentdir);
	startp = ((block0*)myvhard)->startblock;
}

void my_format() {
	unsigned char* p;
	p = myvhard;
	time_t* now;
	now = (time_t*)malloc(sizeof(time_t));
	block0* b0;
	b0 = (block0*)p;
	p += BLOCKSIZE;
	fat* fat1 = (fat*)p;
	fat* fat2 = (fat*)(p + 2 * BLOCKSIZE);
	int i;
	for (i = 0; i < 5; i++, fat1++, fat2++) {
		fat1->id = END;
		fat2->id = END;
	}
	fat1->id = 6;
	fat2->id = 6;
	fat1++;
	fat2++;
	fat1->id = END;
	fat2->id = END;
	fat1++;
	fat2++;

	for (i = 7; i < 2 * BLOCKSIZE / sizeof(fat); i++, fat1++, fat2++) {
		fat1->id = FREE;
		fat2->id = FREE;
	}

	p += BLOCKSIZE * 4;

	fcb* root = (fcb*)p;
	strcpy(root->filename, ".");
	strcpy(root->exname, "di");
	root->attribute = 1;
	time(now);

	struct tm *nowtime;
	nowtime = localtime(now);
	root->time = nowtime->tm_hour * 2048 * nowtime->tm_min * 32 + nowtime->tm_sec / 2;
	root->data = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
	root->first = 5;
	root->length = 2 * sizeof(fcb);
	root->free = 1;
	root++;

	strcpy(root->filename, "..");
	strcpy(root->exname, "di");
	root->attribute = 1;
	time(now);
	nowtime = localtime(now);
	root->time = nowtime->tm_hour * 2048 * nowtime->tm_min * 32 + nowtime->tm_sec / 2;
	root->data = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
	root->first = 5;
	root->length = 2 * sizeof(fcb);
	root->free = 1;
	root++;

	for (i = 2; i < BLOCKSIZE * 2 / sizeof(fcb); i++, root++) {
		root->free = 0;
	}
	b0->startblock = p ;
}
void my_ls()
{
	useropen* usp = &openfilelist[0];
	int i;
	for (i = 0; i < MAXOPENFILE; i++, usp++) {
		if (ptrcurdir == usp)break;
	}
	char* p = (char*)(myvhard + ptrcurdir->first*BLOCKSIZE);
	fcb* fileFcb = (fcb*)p;
	int num = fileFcb->length / sizeof(fcb);
	for (i = 0; i < num; i++, fileFcb++) {
		if (fileFcb->free == 1)cout << "Filename:" << fileFcb->filename << " Exname:" << fileFcb->exname << endl;
		else i--;
	}
}

void my_mkdir(char* dirname) {
	useropen* usp = &openfilelist[0];
	int i;
	for (i = 0; i < MAXOPENFILE; i++, usp++) {
		if (ptrcurdir == usp)break;
	}
	int curOpenNum = i;
	char* buf = (char*)malloc(1024);
	do_read(i, 1024, buf);
	fcb* fileFcb = (fcb*)buf;
	int length = fileFcb->length;
	for (i = 0; i < length / sizeof(fcb); i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, dirname)) {
			cout << "the same dirname" << endl;
			return;
		}
		if (fileFcb->free == 0)i--;
	}
	for (i = 0; i < MAXOPENFILE; i++) {
		if (openfilelist[i].topenfile == 0)break;
	}

	if (i == MAXOPENFILE)cout << "open too many files" << endl;
	int fd = i;
	fat* fat1 = (fat*)(myvhard + BLOCKSIZE);
	fat* fat2 = (fat*)(myvhard + BLOCKSIZE * 3);
	int freeBlock = 0;
	for (i = 0; i < BLOCKSIZE * 2 / sizeof(fat); i++, fat1++, fat2++) {
		if (fat1->id == FREE) {
			freeBlock = i;
			break;
		}
	}
	if (i == BLOCKSIZE * 2 / sizeof(fat)) {
		cout << "FAT is full" << endl;
		return;
	}

	fileFcb = (fcb*)buf;
	for (i = 0; i < length / sizeof(fcb); i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, "."))
			fileFcb->length += sizeof(fcb);
		if (fileFcb->free == 0)
			break;
	}

	strcpy(fileFcb->filename, dirname);
	strcpy(fileFcb->exname, "di");
	fileFcb->attribute = 0;
	time_t* now = (time_t*)malloc(sizeof(time_t));
	time(now);
	struct tm* nowtime = localtime(now);
	fileFcb->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
	fileFcb->data = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
	fileFcb->first = freeBlock;
	fileFcb->free = 1;
	fileFcb->length = 2 * sizeof(fcb);
	fcb* p = (fcb*)(myvhard + freeBlock*BLOCKSIZE);

	strcpy(p->filename, ".");
	strcpy(p->exname, "di");
	p->attribute = 0;
	time(now);
	nowtime = localtime(now);
	p->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
	p->data = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
	p->first = freeBlock;
	p->length = 2 * sizeof(fcb);
	p->free = 1;
	p++;
	strcpy(p->filename, "..");
	strcpy(p->exname, "di");
	p->attribute = 0;
	time(now);
	nowtime = localtime(now);
	p->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
	p->data = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
	p->first = ptrcurdir->first;
	p->free = 1;
	p++;
	fat1->id = END;
	fat2->id = END;
	ptrcurdir->length += sizeof(fcb);
	for (i = 2; i < BLOCKSIZE / sizeof(fcb); i++, p++) {
		p->free = 0;
	}
	do_write(curOpenNum, buf, 1024, 0);
	free(buf);
}
int do_write(int fd,char* text,int len,int wstyle) {
	int index = openfilelist[fd].first;
	fat* fat1 = (fat*)(myvhard + BLOCKSIZE);
	int blkno = openfilelist[fd].first;
	unsigned char* p = blkno*BLOCKSIZE + myvhard;
	int length = ptrcurdir->length;
	int n = length / BLOCKSIZE + 1;
	int i, j, k = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < BLOCKSIZE&&k < length; j++, k++) {
			*p = text[k];
			p++;
		}
		p = myvhard + BLOCKSIZE*(fat1[index].id);
		index = fat1[index].id;
	}
	return 1024;
}
int do_read(int fd, int len, char* text) {
		int index = openfilelist[fd].first;
		unsigned char* p = openfilelist[fd].first*BLOCKSIZE + myvhard;
		int length = openfilelist[fd].length;
		int n = openfilelist[fd].length / BLOCKSIZE + 1;
		fat* fat1 = (fat*)(myvhard + BLOCKSIZE);
		int i, j, k = 0;
		for (i = 0; i < n; i++) {
			for (j = 0; j < BLOCKSIZE&&k < length; j++, k++, p++) {
				text[k] = *p;
			}
			p = myvhard + BLOCKSIZE*fat1[index].id;
			index = fat1[index].id;
		}
		text[k] = '\0';
		return k;
}
int my_create(char* fileName) {
	char* buf = (char*)malloc(1024);
	useropen* usp = &openfilelist[0];
	int i;
	for (i = 0; i < MAXOPENFILE; i++,usp++) {
		if (ptrcurdir == usp)break;
	}
	int curOpenNum = i;
	do_read(i, 1024, buf);
	fcb* fileFcb = (fcb*)buf;
	int length = fileFcb->length / sizeof(fcb);
	for (i = 0; i < length; i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, fileName)) {
			cout << "rename it" << endl;
			return -1;
			break;
		}
		if (fileFcb->free == 0)i--;
	}
	fat* fat1 = (fat*)(myvhard + BLOCKSIZE);
	fat* fat2 = (fat*)(myvhard + BLOCKSIZE * 3);
	int freeBlock = 0;
	int flag = 0;
	for (i = 0; i < BLOCKSIZE * 2 / sizeof(fat); i++) {
		if (fat1->id == FREE) {
			flag = 1;
			freeBlock = i;
			break;
		}
		fat1++;
		fat2++;
	}
	if (flag == 0) {
		cout << "FAT IS FULL" << endl;
		return -1;
	}

	time_t* now;
	struct tm* nowtime;
	now = (time_t*)malloc(sizeof(time_t));
	fileFcb = (fcb*)buf;

	for (i = 0; i < length; i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, ".")) {
			fileFcb->length += sizeof(fcb);
		}
		if (fileFcb->free == 0)break;
	}

	strcpy(fileFcb->filename, fileName);
	strcpy(fileFcb->exname, "txt");
	fileFcb->attribute = 1;
	time(now);
	nowtime = localtime(now);
	fileFcb->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
	fileFcb->data = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
	fileFcb->first = freeBlock;
	fileFcb->free = 1;
	fileFcb->length = BLOCKSIZE;
	ptrcurdir->length += sizeof(fcb);
	do_write(curOpenNum, buf, 1024, 0);
	free(buf);
	return 1;
}

void my_close(int fd) {
	if (fd >= MAXOPENFILE) {
		cout << "file open table overflow." << endl;
		return;
	}
	strcpy(openfilelist[fd].filename, "\0");
	strcpy(openfilelist[fd].exname, "\0");
	openfilelist[fd].attribute = 0;
	openfilelist[fd].time = 0;
	openfilelist[fd].data = 0;
	openfilelist[fd].first = 0;
	openfilelist[fd].length = 0;
	openfilelist[fd].fcbstate = 0;
	openfilelist[fd].free = 0;
	openfilelist[fd].topenfile = 0;
	openfilelist[fd].count = 1;
}
void my_rmdir(char* dirname) {
	int i = 0;
	useropen* usp = &openfilelist[0];
	for (i = 0; i < MAXOPENFILE; i++,usp++) {
		if (ptrcurdir==usp)break;
	}
	int fd = i;
	char* buf = (char*)malloc(1024);
	do_read(fd, 1024, buf);
	fcb* fileFcb = (fcb*)buf;
	int length = fileFcb->length / sizeof(fcb);
	for (i = 0; i < length; i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, dirname)) {
			break;
		}
		if (fileFcb->free == 0)i--;
	}
	if (i == length) {
		cout << "dir name not exist."<<endl;
		return;
	}

	fcb* tmp = (fcb*)(myvhard + BLOCKSIZE*fileFcb->first);
	if (tmp->length > 2 * sizeof(fcb)) {
		cout << "dir is not empty";
		return;
	}
	int flag = 0;
	for (i = 0; i < MAXOPENFILE; i++) {
		if (!strcmp(openfilelist[i].filename, dirname)) {
			flag = 1;
			break;
		}
	}

	if (flag == 1)my_close(i);
	fat* fat1 = (fat*)(myvhard + BLOCKSIZE);
	fat* fat2 = (fat*)(myvhard + BLOCKSIZE * 3);
	int index = fileFcb->first;
	int indexT;
	do {
		indexT = fat1[index].id;
		fat1[index].id = FREE;
		fat2[index].id = FREE;
		index = indexT;
	} while (index != END);

	fileFcb->filename[0] = '\0';
	fileFcb->free = 0;
	fileFcb = (fcb*)buf;
	fileFcb->length -= sizeof(fcb);
	do_write(fd, buf, 1024, 0);
	free(buf);
}

int my_open(char* filename) {
	int i;
	char* buf = (char*)malloc(1024);
	useropen* usp = &openfilelist[0];
	for (i = 0; i < MAXOPENFILE; i++, usp++) {
		if (ptrcurdir == usp)break;
	}
	do_read(i, 1024, buf);
	fcb* fileFcb = (fcb*)buf;

	int flag = 0;
	int diroff = 0;
	int length = fileFcb->length / sizeof(fcb);
	for (i = 0; i < length; i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, filename)) {
			flag = 1;
			diroff = i;
			break;
		}
	}
	if (flag == 0)return -2;

	for (i = 0; i < MAXOPENFILE; i++)
		if (openfilelist[i].first == fileFcb->first) {
			if (!strcmp(fileFcb->filename, "..")) {
				int j = 0;
				for (j = 0; j<MAXOPENFILE; j++)
					if (openfilelist[j].free == 1 && (&openfilelist[j]) == ptrcurdir)
						my_close(j);
				for (j = 0; j<MAXOPENFILE; j++)
					if (openfilelist[j].free = 1 && openfilelist[j].first == fileFcb->first)
						ptrcurdir = &openfilelist[j];
				return -3;
			}
			return -1;
		}
	flag = 0;
	for (i = 0; i < MAXOPENFILE; i++) {
		if (openfilelist[i].topenfile == 0) {
			flag = 1;
			break;
		}
	}
	int fd = i;
	if (flag == 0) {
		cout << "open too many files." << endl;
		return -1;
	}
	strcpy(openfilelist[i].filename, fileFcb->filename);
	strcpy(openfilelist[i].exname, fileFcb->exname);
	openfilelist[i].attribute = fileFcb->attribute;
	openfilelist[i].time = fileFcb->time;
	openfilelist[i].data = fileFcb->data;
	openfilelist[i].first = fileFcb->first;
	openfilelist[i].length = fileFcb->length;
	openfilelist[i].fcbstate = 0;
	openfilelist[i].free = 1;
	openfilelist[i].topenfile = 1;
	openfilelist[i].count = 1;

	openfilelist[i].dirno = ptrcurdir->first;
	openfilelist[i].diroff = diroff;
	ptrcurdir = &openfilelist[i];
	
	free(buf);
	return fd;
}


int FAT_main() {
	startsys();
	string cmd;
	int fd;
	char command[16];
	while (1) {
		cout << "c://";
		cin >> cmd;
		if (cmd == "ls") {
			my_ls();
		}
		else if (cmd == "mkdir") {
			cin >> command;
			my_mkdir(command);
		}
		else if (cmd == "ls") {
			my_ls();
		}
		else if(cmd=="create"){
			cin >> command;
			my_create(command);
		}if (cmd == "rmdir") {
			cin >> command;
			my_rmdir(command);
		}
	}
	

}

