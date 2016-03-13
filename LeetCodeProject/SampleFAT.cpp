// Created by ChenJensen on 16/1/1.
#include <stdio.h>
#include <malloc.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#define BLOCKSIZE 1024
#define SIZE 1024000
#define END 65535
#define FREE 0
#define ROOTBLOCKNUM 2
#define MAXOPENFILE 10
#define FILENAME "C:\\Users\\darkknight\\Documents\\Tencent Files\\305790465\\FileRecvmyfsys"
#define MODE "r"

typedef struct FCB
{
	unsigned char attribute;// ��ʱֻ���������ԣ�0��Ŀ¼�ļ���1�������ļ�
	unsigned short time;
	unsigned short data;
	unsigned short first;//��fcb��ָ��ĵ�һ������
	unsigned long length;//����,Ŀ¼��
	short  free;// ��ʾĿ¼���Ƿ�Ϊ�գ�0Ϊ�գ�1Ϊ�ѷ���
	char filename[8];//�ļ���
	char exname[4];//��׺��

}fcb;

//Fat�����б�ʾ��ָ����һ����ַ,���û������Ϊend,û��ռ�е�ʱ����Ϊfree
typedef struct FAT
{
	unsigned short id;
}fat;

//��ǰ��Ŀ¼��ṹ��,������fcb��,Ȼ����
typedef struct USEROPEN
{
	char filename[8];
	char exname[4];
	unsigned char attribute;// ��ʱֻ���������ԣ�0��Ŀ¼�ļ���1�������ļ�
	unsigned short time;
	unsigned short data;
	unsigned short first;
	unsigned long length;
	short free;

	int dirno;// ��Ӧ���ļ����ڵ�Ŀ¼���ڸ�Ŀ¼�ļ��е��̿��
	int diroff;// ��Ӧ���ļ���Ŀ¼���ڸ�Ŀ¼�ļ���dirno�̿��е�Ŀ¼�����
	int count;//��дָ�����ļ��е�λ��
	char dir[80];//��Ӧ���ļ����ڵ�Ŀ¼��
	short fcbstate;// �Ƿ��޸����ļ���FCB�����ݣ�1���޸ģ�0��δ�޸�
	short topenfile;// ��ʾ���û��򿪱����Ƿ�Ϊ�գ�0���գ�1���ѷ���
}useropen;

typedef struct BLOCK0
{
	char information[200];
	unsigned short root;// ��Ŀ¼�ļ�����ʼ�̿��
	unsigned char *startblock;
}block0;

unsigned char *myvhard;
useropen openfilelist[MAXOPENFILE];
useropen *ptrcurdir;// ָ���û����ļ����еĵ�ǰĿ¼���ڴ��ļ������λ��
char currentdir[80];
unsigned char *startp;// �����������������ʼ��λ��

void startsys();
void my_format();
void my_cd(char *dirname);
int my_open(char *filename);
int do_read(int fd, int len, char *text);
void my_close(int fd);
void my_mkdir(char *dirname);
void my_ls();
int do_write(int fd, char *text, int len, int wstyle);
void my_rmdir(char *dirname);
int my_create(char *filename);
void my_rm(char *filename);

/*first open the file judge if it exits
if not exits apply an area from the memory of
size of SIZE,
*/

void startsys()
{
	myvhard = (unsigned char*)malloc(SIZE);
	memset(myvhard, 0, SIZE);
	FILE * fp;
	if ((fp = fopen(FILENAME, MODE)) != NULL) {
		fread(myvhard, SIZE, 1, fp);
		fclose(fp);
	}
	else {
		printf("The file not exits,please create the file,now init the file system.\n");
		//�����̽��и�ʽ��
		my_format();
	}
	strcpy(openfilelist[0].filename, "root");
	strcpy(openfilelist[0].exname, "di");
	openfilelist[0].attribute = 0;
	openfilelist[0].time = ((fcb *)(myvhard + 5 * BLOCKSIZE))->time;
	openfilelist[0].data = ((fcb *)(myvhard + 5 * BLOCKSIZE))->data;
	openfilelist[0].first = ((fcb *)(myvhard + 5 * BLOCKSIZE))->first;
	openfilelist[0].length = ((fcb *)(myvhard + 5 * BLOCKSIZE))->length;
	openfilelist[0].fcbstate = 0;
	openfilelist[0].free = 1;
	openfilelist[0].topenfile = 1;
	openfilelist[0].count = 1;
	//��Ŀ¼�͵�ǰĿ¼���ڵ��̿��
	openfilelist[0].dirno = ((fcb *)(myvhard + 5 * BLOCKSIZE))->first;
	openfilelist[0].diroff = ((fcb *)(myvhard + 5 * BLOCKSIZE))->first;
	//��ǰĿ¼ָ���һ��
	ptrcurdir = &openfilelist[0];
	int i;
	for (i = 1; i < MAXOPENFILE; i++) {
		strcpy(openfilelist[i].filename, "\0");
		strcpy(openfilelist[i].exname, "\0");
		openfilelist[i].attribute = 0;
		openfilelist[i].time = 0;
		openfilelist[i].data = 0;
		openfilelist[i].first = 0;
		openfilelist[i].length = 0;
		openfilelist[i].fcbstate = 0;
		openfilelist[i].free = 0;
		openfilelist[i].topenfile = 0;
		openfilelist[i].count = 1;
	}
	// ���õ�ǰĿ¼Ϊ��Ŀ¼
	strcpy(currentdir, "\\root\\");
	strcpy(openfilelist[0].dir, currentdir);
	startp = ((block0 *)myvhard)->startblock;
}
void my_format() {
	//pָ��Ӳ�̿鿪ʼ��
	unsigned char *p;
	p = myvhard;
	//ʱ��ṹ�����ǰʱ��
	time_t *now;
	now = (time_t *)malloc(sizeof(time_t));
	//������
	block0 *b0;
	b0 = (block0 *)p;
	p += BLOCKSIZE;//p��ǰָ��1����ʼ��ַ
				   //��ʼ��������fat��
	fat *fat1 = (fat*)(p);
	fat *fat2 = (fat*)(p + 2 * BLOCKSIZE);
	//�������5�������fat����д
	int i;
	for (i = 0; i < 5; i++, fat1++, fat2++)
	{
		fat1->id = END;
		fat2->id = END;
	}
	//�������������Ŀ¼,ռ������fat,5,6��,��6,7��
	fat1->id = 6;
	fat2->id = 6;
	fat1++;
	fat2++;
	fat1->id = END;
	fat2->id = END;
	fat1++;
	fat2++;
	//��ʱ��fat1,fat2ָ����һ������
	//��fat����ʣ�༸���ʼ��
	//??????? ��ʼ��ʣ��ı���,fatռ�ж��???????
	for (i = 7; i < 2 * BLOCKSIZE / sizeof(fat); i++, fat1++, fat2++)
	{
		fat1->id = FREE;
		fat2->id = FREE;
	}
	//p��ǰָ��5��,׼���ָ�rootһ����
	p += BLOCKSIZE * 4;
	//��5�����fcb
	fcb *root = (fcb *)p;
	// ���õ�"." ".."
	strcpy(root->filename, ".");
	strcpy(root->exname, "di");
	root->attribute = 1;
	time(now);

	struct tm *nowtime;
	nowtime = localtime(now);
	root->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
	root->data = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
	root->first = 5;
	//�䳤�ȱ�ʾռ��������fcb
	root->length = 2 * sizeof(fcb);
	//��ʾ��ռ��
	root->free = 1;
	//root�ƶ�����һ��fcb��
	root++;
	strcpy(root->filename, "..");
	strcpy(root->exname, "di");
	root->attribute = 1;
	time(now);
	nowtime = localtime(now);
	root->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
	root->data = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
	root->first = 5;
	root->length = 2 * sizeof(fcb);
	root->free = 1;

	root++;

	// ��ʼ����Ŀ¼��ʣ��ı���
	for (i = 2; i<BLOCKSIZE * 2 / sizeof(fcb); i++, root++)
	{
		//root->filename[0]='\0';
		root->free = 0;
	}

	//����������ʼ��ַ
	b0->startblock = p + BLOCKSIZE * 4;
}

void my_ls() {
	// ��ȡ��ǰĿ¼�ļ������ݵ��ڴ�
	//char *buf = (char *)malloc(1024);
	useropen *usp = &openfilelist[0];
	int i;
	for (i = 0; i < MAXOPENFILE; i++, usp++) {
		if (ptrcurdir == usp) {
			break;
		}
	}
	//����fcb�ҵ��ļ�����ʼ��
	char *p = (char *)(myvhard + ptrcurdir->first * BLOCKSIZE);
	fcb *fileFcb = (fcb *)p;
	//fcb�Ŀ���
	int num = fileFcb->length / sizeof(fcb);
	for (i = 0; i < num; i++, fileFcb++) {
		if (fileFcb->free == 1)
			printf("filename:%s   exname:%s   time:%d:%d:%d   data:%d,%d,%d   size:%d\n", fileFcb->filename, fileFcb->exname, fileFcb->time / 2048, (fileFcb->time % 2048) / 32, (fileFcb->time % 32) * 2, fileFcb->data / 512 + 1980, fileFcb->data % 512 / 32,
				fileFcb->data % 32, fileFcb->length);
		else i--;
	}
}

void my_mkdir(char *dirname) {
	// ��ȡ��ǰĿ¼�ļ������ݵ��ڴ�
	useropen *usp = &openfilelist[0];
	int i;
	//�Ҵ�ǰĿ¼��fat���ж�Ӧ�Ķ˿�
	for (i = 0; i < MAXOPENFILE; i++, usp++) {
		if (ptrcurdir == usp)
			break;
	}
	int curOpenNum = i;
	char *buf = (char *)malloc(1024);
	do_read(i, 1024, buf);
	// ��鵱ǰĿ¼���½���Ŀ¼�ļ��Ƿ�����
	fcb *fileFcb = (fcb *)buf;
	int length = fileFcb->length;
	for (i = 0; i < length / sizeof(fcb); i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, dirname)) {
			printf("Ŀ¼����\n");
			return;
		}
		if (fileFcb->free == 0)
			i--;
	}

	// ��������ļ��򿪱�
	for (i = 0; i < MAXOPENFILE; i++) {
		if (openfilelist[i].topenfile == 0) {
			break;
		}
	}

	if (i == MAXOPENFILE)
	{
		printf("�ļ���̫��\n");
		return;
	}

	int fd = i;
	// ���FAT�Ƿ��п����̿�
	fat *fat1 = (fat *)(myvhard + BLOCKSIZE);
	fat *fat2 = (fat *)(myvhard + BLOCKSIZE * 3);
	int freeBlock = 0;

	for (i = 0; i < BLOCKSIZE * 2 / sizeof(fat); i++, fat1++, fat2++)
	{
		if (fat1->id == FREE)
		{
			freeBlock = i;
			break;
		}
	}
	if (i == BLOCKSIZE * 2 / sizeof(fat))
	{
		printf("FAT���ˣ�");
		return;
	}
	// ��Ŀ¼�з���FCB���µ�Ŀ¼
	fileFcb = (fcb *)buf;
	for (i = 0; i < length / sizeof(fcb); i++, fileFcb++) {
		//|| ??????!strcmp(fileFcb->filename, "..")????????
		if (!strcmp(fileFcb->filename, "."))
			fileFcb->length += sizeof(fcb);
		if (fileFcb->free == 0)
			break;
	}
	strcpy(fileFcb->filename, dirname);
	strcpy(fileFcb->exname, "di");
	fileFcb->attribute = 0;
	time_t *now = (time_t *)malloc(sizeof(time_t));
	time(now);
	struct tm *nowtime = localtime(now);
	fileFcb->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
	fileFcb->data = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
	fileFcb->first = freeBlock;
	fileFcb->free = 1;
	//fileFcb->length = BLOCKSIZE;// �����ļ��ĳ���
	fileFcb->length = 2 * sizeof(fcb);
	// ����Ŀ¼����Ĵ��̿��н������������Ŀ¼��"." ".."
	fcb *p = (fcb *)(myvhard + freeBlock * BLOCKSIZE);
	// ���õ�"." ".."
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
	//ԭ����������Ҫд�غ�Ż���µ�
	ptrcurdir->length += sizeof(fcb);
	for (i = 2; i<BLOCKSIZE / sizeof(fcb); i++, p++)
	{
		p->free = 0;
	}
	do_write(curOpenNum, buf, 1024, 0);
	free(buf);
}

void my_rm(char *filename) {
	int flag;
	// ��ȡ��ǰĿ¼�ļ������ݵ��ڴ�
	char *buf = (char *)malloc(1024);
	useropen *usp = &openfilelist[0];
	int i;
	for (i = 0; i < MAXOPENFILE; i++, usp++) {
		if (ptrcurdir == usp) {
			break;
		}
	}
	int fd = i;
	do_read(i, 1024, buf);
	// ���Ҫɾ����Ŀ¼�Ƿ����
	fcb *fileFcb = (fcb *)buf;
	int length = fileFcb->length;
	flag = 0;
	for (i = 0; i < length / sizeof(fcb); i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, filename)) {
			flag = 1;
			break;
		}
		if (fileFcb->free == 0)
			i--;
	}
	if (flag == 0) {
		printf("%sĿ¼�����ڣ�\n", filename);
		return;
	}
	// ���մ��̿�
	fat *fat1 = (fat *)(myvhard + BLOCKSIZE);
	fat *fat2 = (fat *)(myvhard + BLOCKSIZE * 3);
	int index = fileFcb->first;
	int indexT;
	do {
		indexT = fat1[index].id;
		fat1[index].id = FREE;
		fat2[index].id = FREE;
		index = indexT;
	} while (index != END);
	// ���Ŀ¼��
	fileFcb->filename[0] = '\0';
	fileFcb->free = 0;
	fileFcb = (fcb *)buf;
	// �޸�Ŀ¼�ĳ���
	fileFcb->length -= sizeof(fcb);
	do_write(fd, buf, 1024, 0);
	ptrcurdir->length -= sizeof(fcb);
	free(buf);
}

void my_rmdir(char *dirname) {
	int i = 0;
	// ��ȡ��ǰĿ¼�ļ������ݵ��ڴ�
	char *buf = (char *)malloc(1024);
	useropen *usp = &openfilelist[0];
	for (i = 0; i < MAXOPENFILE; i++, usp++) {
		if (ptrcurdir == usp) {
			break;
		}
	}
	int fd = i;
	//    curOpenNum = i;
	do_read(i, 1024, buf);

	// ���Ҫɾ����Ŀ¼�Ƿ����
	fcb *fileFcb = (fcb *)buf;
	int length = fileFcb->length;
	for (i = 0; i < length / sizeof(fcb); i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, dirname)) {
			break;
		}
		if (fileFcb->free == 0)
			i--;
	}
	if (i == length / sizeof(fcb)) {
		printf("Ŀ¼�����ڣ�\n");
		return;
	}
	// ���Ҫɾ����Ŀ¼�ļ��Ƿ�Ϊ��
	fcb *temp = (fcb *)(myvhard + BLOCKSIZE * fileFcb->first);
	if (temp->length > 2 * sizeof(fcb)) {
		printf("Ŀ¼��Ϊ��,ȷ��Ҫɾ��??\n");
		return;
	}
	int flag = 0;
	// ����Ŀ¼�Ƿ��Ѿ���
	for (i = 0; i < MAXOPENFILE; i++) {
		if (strcmp(openfilelist[i].filename, dirname) == 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {// �Ѵ򿪵�Ŀ¼�ر�
		my_close(i);
	}

	// ���մ��̿�
	fat *fat1 = (fat *)(myvhard + BLOCKSIZE);
	fat *fat2 = (fat *)(myvhard + BLOCKSIZE * 3);
	int index = fileFcb->first;
	int indexT;
	//length = fileFcb->length;
	do {
		indexT = fat1[index].id;
		fat1[index].id = FREE;
		fat2[index].id = FREE;
		index = indexT;
	} while (index != END);

	// ���Ŀ¼��,����free����Ϊ0����,Ȼ���ǽ��ϲ�Ŀ¼�ĳ��Ƚ��и���,ͬʱ����openlist��ҲҪ����,��Ϊ��ָ�򲢲���ͬ.
	fileFcb->filename[0] = '\0';
	fileFcb->free = 0;
	fileFcb = (fcb *)buf;
	fileFcb->length -= sizeof(fcb);
	ptrcurdir->length -= sizeof(fcb);
	do_write(fd, buf, 1024, 0);
	free(buf);
}

int my_create(char *filename) {
	int fd;
	// ��ȡ��ǰĿ¼�ļ������ݵ��ڴ�
	char *buf = (char *)malloc(1024);
	useropen *usp = &openfilelist[0];
	int i;
	for (i = 0; i < MAXOPENFILE; i++, usp++) {
		if (ptrcurdir == usp)
			break;
	}
	int curOpenNum = i;
	do_read(i, 1024, buf);
	// ��鵱ǰĿ¼���½���Ŀ¼�ļ��Ƿ�����
	fcb *fileFcb = (fcb *)buf;
	int length = fileFcb->length;
	for (i = 0; i < length / sizeof(fcb); i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, filename)) {
			printf("�ļ�������");
			return -1;
			break;
		}
		if (fileFcb->free == 0)
			i--;
	}
	// ���FAT�Ƿ��п����̿�
	fat *fat1 = (fat *)(myvhard + BLOCKSIZE);
	fat *fat2 = (fat *)(myvhard + BLOCKSIZE * 3);
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
		printf("FAT���ˣ�");
		return -1;
	}

	// ��Ŀ¼�з���FCB���µ�Ŀ¼
	time_t *now;
	struct tm *nowtime;
	fileFcb = (fcb *)buf;
	now = (time_t *)malloc(sizeof(time_t));
	for (i = 0; i < length / sizeof(fcb); i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, "."))
			fileFcb->length += sizeof(fcb);
		if (fileFcb->free == 0)
			break;
	}
	strcpy(fileFcb->filename, filename);
	strcpy(fileFcb->exname, "txt");
	fileFcb->attribute = 1;
	time(now);
	nowtime = localtime(now);
	fileFcb->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
	fileFcb->data = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
	fileFcb->first = freeBlock;
	fileFcb->free = 1;
	fileFcb->length = BLOCKSIZE;// �����ļ��ĳ���
	ptrcurdir->length += sizeof(fcb);
	do_write(curOpenNum, buf, 1024, 0);
	free(buf);
	return fd;
}

void my_cd(char *dirname) {
	// �򿪸�Ŀ¼�ļ�
	int fd = my_open(dirname);
	switch (fd) {
	case -1:printf("��Ŀ¼Ϊ�Ѵ򿪵ĵ�ǰĿ¼\n"); break;
	case -2:printf("���ļ�������\n"); break;
	case -3:printf("���ص��ϲ�Ŀ¼\n"); break;
	default:break;
	}
}

int my_open(char *filename) {
	int i;
	// ��ȡ��Ŀ¼�ļ����ݵ��ڴ�
	char *buf = (char *)malloc(1024);
	useropen *usp = &openfilelist[0];
	for (i = 0; i < MAXOPENFILE; i++, usp++) {
		if (ptrcurdir == usp)
			break;
	}
	do_read(i, 1024, buf);
	// ��������ļ��Ƿ����
	fcb *fileFcb = (fcb *)buf;
	int flag = 0;
	int diroff = 0;
	int length = fileFcb->length;
	for (i = 0; i < length / sizeof(fcb); i++, fileFcb++) {
		if (!strcmp(fileFcb->filename, filename)) {
			flag = 1;
			diroff = i;
			break;
		}
	}
	if (flag == 0) {
		return -2;
	}
	// ����ļ��Ƿ��Ѵ�
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
	// ����ļ��򿪱��Ƿ��пձ���
	flag = 0;
	for (i = 0; i < MAXOPENFILE; i++) {
		if (openfilelist[i].topenfile == 0) {
			flag = 1;
			break;
		}
	}
	int fd = i;
	if (flag == 0) {
		printf("�ļ���̫�࣡\n");
		return -1;
	}
	// ��д���ļ������
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
	//dirno ��ʾ����
	openfilelist[i].dirno = ptrcurdir->first;
	openfilelist[i].diroff = diroff;
	ptrcurdir = &openfilelist[i];
	//printf("%d\n",i);
	/*
	// ���õ�ǰĿ¼Ϊ��Ŀ¼
	strcat(currentdir, filename);
	strcat(currentdir, "\\");
	*/
	free(buf);
	return fd;
}

void my_close(int fd) {
	if (fd >= MAXOPENFILE)
	{
		printf("�ļ��򿪱����\n");
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

void my_write(int fd)
{
	int writeStyle;
	char *text = (char *)malloc(BLOCKSIZE);
	if (fd >= MAXOPENFILE || fd<0)
		printf("�������ܵ��ﷶΧ\n");
	else {
		printf("������Ҫд�������\n");
		scanf("%s", text);
	}
	do_write(fd, text, BLOCKSIZE, writeStyle);
	free(text);
}

void my_read(int fd, int len)
{
	int i;
	int j = 0;
	for (i = 0; i < MAXOPENFILE; i++) {
		if (fd == 0) {
			break;
		}
		if (openfilelist[i].topenfile == 1) {
			fd--;
		}
	}
	fd = i;

	char *text = (char *)malloc(BLOCKSIZE);
	if (fd>MAXOPENFILE || fd<0)
		printf("���������߽�\n");
	else {
		//printf("%d",do_read(fd,len,text));
		printf("%s\n", text);
	}
}

int  do_read(int fd, int len, char *text)
{
	// ����FAT��
	int index = openfilelist[fd].first;// �ļ����ڵ��̿��
	unsigned char *p = openfilelist[fd].first * BLOCKSIZE + myvhard;
	int length = openfilelist[fd].length;
	//��ʾ����ռ�˼����̿�
	int n = openfilelist[0].length / BLOCKSIZE + 1;
	//fat��Ŀ�ʼ
	fat *fat1 = (fat *)(myvhard + BLOCKSIZE);
	int i, j, k = 0;
	//����ռ���˶���̿�
	for (i = 0; i < n; i++) {
		for (j = 0; j < BLOCKSIZE && k < length; j++, k++, p++)
		{
			text[k] = *p;
		}
		p = myvhard + BLOCKSIZE * (fat1[index].id);
		index = fat1[index].id;
	}
	text[k] = '\0';
	return k;
}

int do_write(int fd, char *text, int len, int wstyle) {
	int index = openfilelist[fd].first;// �ļ����ڵ��̿��
	fat *fat1 = (fat *)(myvhard + BLOCKSIZE);
	int blkno = openfilelist[fd].first;
	unsigned char *p = blkno * BLOCKSIZE + myvhard;
	int length = ptrcurdir->length;
	int n = ptrcurdir->length / BLOCKSIZE + 1;
	int i, j, k = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < BLOCKSIZE && k < length; j++, k++) {
			*p = text[k];
			p++;
		}
		p = myvhard + BLOCKSIZE * (fat1[index].id);
		index = fat1[index].id;
	}
	//*p = '\0';
	return 1024;
}

void my_exitsys() {
	FILE *fp;
	fp = fopen(FILENAME, "w");
	fwrite(myvhard, SIZE, 1, fp);
	free(myvhard);
	fclose(fp);
}

void inputJudge()
{
	printf("........�ļ�����ϵͳ......\n");
	while (1) {
		scanf("d");
	}
}

void showOpenFile() {
	int i;
	int j = 0;
	for (i = 0; i < MAXOPENFILE; i++) {
		if (openfilelist[i].topenfile == 1) {
			cout << j << " " << openfilelist[i].filename << endl;
			j++;
		}
	}
}

int main(int argc, const char * argv[]) {
	startsys();
	string cmd;
	int fd;
	char command[16];
	while (1) {
		cout << "C:// ";
		cin>>cmd;
		if (cmd == "mkdir") {
			cin >> command;
			my_mkdir(command);
		}
		else if (cmd == "rmdir") {
			cin >> command;
			my_rmdir(command);
		}
		else if (cmd == "ls") {
			my_ls();
		}
		else if (cmd == "cd") {
			cin >> command;
			my_cd(command);
		}
		else if (cmd == "create") {
			cin >> command;
			my_create(command);
		}

		else if (cmd == "write") {
			cin >> fd;
			my_write(fd);
		}
		else if (cmd == "read") {
			cin >> fd;
			my_read(fd, 1024);
		}
		else if (cmd == "rm") {
			cin >> command;
			my_rm(command);
		}
		else if (cmd == "open") {
			cin >> command;
			my_open(command);
		}
		else if (cmd == "close") {
			cin >> fd;
			my_close(fd);
		}
		else if (cmd == "exit") {
			my_exitsys();
			break;
		}
		else if (cmd == "show") {
			showOpenFile();
		}
		else cout << "��Чָ��,����������:" << endl;
	}
	return 0;
}
