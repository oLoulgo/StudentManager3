#pragma once
#define MAX 1000
#define MIN -1
/*ѧ���ṹ*/
typedef struct Student
{
	unsigned long long number;	//ѧ��
	char name[10];				//����
	char class[32];				//�༶
	float math;
	float english;
	float computer;
	float average;				//��δ��
}Student;

/*�ڵ� Node*/
typedef struct Node
{
	Student stu;		//ѧ��
	struct Node* next;	//ָ����һ���ڵ��ָ��
}Node;	//����ֱ��ʹ�������������Ϊʹ��ʱδ�����������ں���

/*����*/
typedef struct List
{
	Node* front;	//ָ���һ���ڵ�
	int size;		//��ǰ�ڵ�����
}List;

/*�˵�����*/
typedef enum MenuOptions
{
	Quit,		//�˳�ϵͳ
	Entry,		//¼��ѧ��
	Print,		//��ӡѧ��
	Remove,		//ɾ��ѧ��
	Alter,		//�޸�ѧ��
	Rank,		//ѧ������
	Analyse,	//�ɼ�����
	Char,		//ѧ���ܱ�
	Save,		//����ѧ��
	Read,		//��ȡѧ��
	Find,		//����ѧ��
	//test,
}MenuOptions;

/*��ӡ�˵�������ʾ�û�ѡ����*/
int menu();

/*ѧ��¼��*/
void entryStudent(List* list);

/*ѧ����ӡ������*/
void printStudent(List* list);

/*����ѧ��,�����Ʊ��棨��������*/
void saveStudent(List* list);

/*����ѧ�������ö���*/
void saveStudentHuman(List* list);

/*��ȡѧ��,������*/
void readStudent(List* list);

/*��ȡѧ��,����*/
void readStudentHuman(List* list);

/*����ѧ��*/
/*Node* findStudent(List* list);*/
void findStudent(List* list);

/*�޸�ѧ��*/
void alterStudent(List* list);

/*�޸�ѧ��*/
void removeStudent(List* list);

/*��ƽ���ɼ�����*/
void rankStudent(List* list);

/*�༶�ɼ�����*/
void analyseStudent(List* list);

void printStudentInfoByClass(List* list, const char* className);

void printAllStudentInfo(List* list);

