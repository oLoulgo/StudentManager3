#include "StudentManager.h"

#include<stdio.h>		//�˴�Ҫ�õ�printf��scanf����
#include<malloc.h>
#include<string.h>

static Node* CreateNode()	//Ϊ�����ڵ�дһ����������̬�ڲ��ģ�����Ϊ�������Ḵ�ö�Σ�entryStudent��readStudent��,ʹ��������
{
	//�����ڵ�
	Node* node = malloc(sizeof(Node));
	if (!node)	//�ڴ治��ͷ���ʧ��
	{
		printf("malloc failed\n");
		return NULL;
	}
	node->next = NULL;
	return node;
}

int menu()
{
	printf("**********************************************************************\n");
	printf("*		ѧ���ɼ�����ϵͳ		*\n");
	printf("**********************************************************************\n");
	printf("*	    	    ѡ����    	    	*\n");
	printf("**********************************************************************\n");
	printf("*	    	  1.���ѧ����Ϣ    	    	*\n");
	printf("*	    	  2.��ӡѧ����Ϣ    	    	*\n");
	printf("*	    	  3.ɾ��ѧ����Ϣ    	    	*\n");
	printf("*	    	  4.�޸�ѧ����Ϣ    	    	*\n");
	printf("*	    	  5.ѧ����������    		*\n");
	printf("*	    	  6.�༶�ɼ�����    	    	*\n");
	printf("*	    	  7.���ѧ����Ϣ��    		*\n");
	printf("*	    	  8.����ѧ����Ϣ    	    	*\n");
	printf("*	    	  9.��ȡѧ����Ϣ    	    	*\n");
	printf("*	    	  10.����ѧ����Ϣ    	    	*\n");
	printf("*	    	  0.�˳�ϵͳ    	    	*\n");
	printf("*************************************************\n");
	printf("select>");
	int select = -1;
	scanf("%d", &select);
	return select;
}

void entryStudent(List* list)
{
	/*//�����ڵ�	
	Node* node = malloc(sizeof(Node));
	if (!node)	//�ڴ治��ͷ���ʧ��
	{
		printf("malloc failed\n");
		return;
	}
	node->next = NULL;
	*/

	//����ͷ���
	Node* node = CreateNode();	//�����˴����ڵ�

	//����ѧ����Ϣ
	printf("������ѧ��ѧ��>");
	scanf("%llu", &node->stu.number);	//��Ϊ�Ǹ�����(������)������ȡ��ַ&

	printf("������ѧ������>");
	scanf("%s", node->stu.name);		//�������ַ��������ַ�����,�����������׵�ַ����˲���&

	printf("������ѧ���༶>");
	scanf("%s", node->stu.class);

	printf("������ѧ����ѧ�ɼ�>");
	scanf("%f", &node->stu.math);

	printf("������ѧ��Ӣ��ɼ�>");
	scanf("%f", &node->stu.english);

	printf("������ѧ��������ɼ�>");
	scanf("%f", &node->stu.computer);

	node->stu.average = (node->stu.math + node->stu.english + node->stu.computer) /3.0f;

	//���뵽������
	node->next = list->front;	//ͷ�壺�½��ָ��ԭ�������һ����frontָ���½��
	list->front = node;
	list->size++;

}

void printStudent(List* list)
{
	printf("********************************************************************\n");
	printf("*			ѧ���ɼ�����ϵͳ			   *\n");
	printf("********************************************************************\n");
	printf("*	ѧ��	*  ����  *  �༶  *  ��ѧ  *  Ӣ��  *   �����   *  ƽ���ɼ�  *\n");	//��������tab����
	printf("********************************************************************\n");

	//��������	//04  4m
	Node* curNode = list->front;
	while (curNode != NULL)
	{
		printf("*%llu \t*%s \t*%s \t*%.1lf \t*%.1lf \t*%.1lf \t*%.2lf \t\n",curNode->stu.number,curNode->stu.name,curNode->stu.class,
			curNode->stu.math,curNode->stu.english,curNode->stu.computer,curNode->stu.average);
		curNode = curNode->next;
	}
}

void saveStudent(List* list)
{
	//���ļ�
	FILE* fp = fopen("students.data", "wb");	//wbָ�ö�����д�룬����ļ��п�����
	if (!fp)
	{
		perror("file open failed");
		return;
	}

	//д��ѧ����Ϣ
	Node* curNode = list->front;
	while (curNode != NULL)
	{
		fwrite(&curNode->stu, sizeof(Student), 1, fp);	//д�����ݵĵ�ַ��Ҫд��Ԫ�صĴ�С��д��1����д��fp�ļ�
		curNode = curNode->next;
	}

	//�ر��ļ�
	fclose(fp);
}

void saveStudentHuman(List* list)
{
	//���ļ�
	FILE* fp = fopen("students.txt", "w");	//wbָ�ö�����д�룬����ļ��п�����
	if (!fp)
	{
		perror("file open failed");
		return;
	}

	//д��ѧ����Ϣ
	Node* curNode = list->front;
	while (curNode != NULL)
	{
		fprintf(fp,"%llu\t%s\t%s\t%.lf\t%.lf\t%.lf\t%.lf\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
			curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
		curNode = curNode->next;
	}

	//�ر��ļ�
	fclose(fp);
}

void readStudent(List* list)
{
	//���ļ�
	FILE* fp = fopen("students.data", "rb");	//�����saveStudent��ĸ��ƹ��������ǰ������wb�ĳ�rb�����Դ洢�ļ����������֮ǰ�Լ���ʾһ�����ر������¶�ȡ��ʾ�ļ��հ�
	if (!fp)
	{
		perror("file open failed");
		return;
	}

	//��ȡѧ����Ϣ
	while (!feof(fp))	//δ����ʱ��һֱ��
	{
		Node* node = CreateNode();	//�����˴����ڵ�
		if (!node)	//����ʧ�ܾ�����ѭ��
			break;

		size_t len = fread(&node->stu, sizeof(Student), 1, fp);		//ָ��һ���ڴ��ָ�루��Ŷ�ȡ���������ݣ���ÿ��Ԫ�صĴ�С��Ҫ��ȡ��Ԫ�ظ�������fp����ļ����
		if (len == 0)	//����0��˵����ʧ���ˣ��Ϳ��Բ����ˣ�
		{
			free(node);
			break;
		}

		//���뵽������		//�Ѷ�ȡ��Ԫ�ز��뵽�����У�
		node->next = list->front;
		list->front = node;
		list->size++;
	}

	//�ر��ļ�
	fclose(fp);

}

void readStudentHuman(List* list)
{
	//���ļ�
	FILE* fp = fopen("students.txt", "r");	//r,���ķ�ʽ
	if (!fp)
	{
		perror("file open failed");
		return;
	}

		//��ȡѧ����Ϣ
	while (!feof(fp))	//δ�����һֱ��
	{
		Node* node = CreateNode();
		if (!node)
			break;
		fscanf(fp,"%llu\t%s\t%s\t%f\t%f\t%f\t%f\n", &node->stu.number, node->stu.name, node->stu.class,
			&node->stu.math, &node->stu.english, &node->stu.computer, &node->stu.average);	//Ϊʲô%.lf�ĳ���%f	/ԭ��if ��7 ��=��
		//{
		//	free(node);
		//	break;
		//}

		//��������
		node->next = list->front;
		list->front = node;
		list->size++;
	}

		//�ر��ļ�
		fclose(fp);

}

/*Node* findStudent(List* list)
{
	///if (list->size == 0)
	//{
	//	//printf("ϵͳ����ѧ����Ϣ\n");
	//	return;
	//}

	char buffer[32];
	printf("������ѧ����ѧ�Ż�����>");
	scanf("%s", buffer);

	//��bufferת������
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL)
	{
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)
		{
			printf("%llu\t%s\t%s\t%.1lf\t%.1lf\t%.1lf\t%.2lf\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
				curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
			return curNode;
		}
		curNode = curNode->next;
	}

	return NULL;
}	 //Ϊʲô����void*/
void findStudent(List* list)
{
	char buffer[32];
	printf("������ѧ����ѧ�Ż�����>");
	scanf("%s", buffer);

	//��bufferת������
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL)
	{
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)
		{
			printf("%llu\t%s\t%s\t%.1lf\t%.1lf\t%.1lf\t%.2lf\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
				curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
			break;
		}
		curNode = curNode->next;
	}
	if(!curNode)
		{
			printf("δ�ҵ�����ѯѧ��\n");
		}
	
}

void alterStudent(List* list)	//�Ȳ������޸�
{
	if (list->size == 0)
	{
		printf("ϵͳ����ѧ����Ϣ\n");
		return;
	}

	char buffer[32];
	printf("������Ҫ�޸ĵ�ѧ����ѧ�Ż�����>");
	scanf("%s", buffer);

	//��bufferת������
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL)
	{
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)
		{
			printf("������Ҫ�޸ĵ�ѧ�����Ƴɼ�>");
			scanf("%f %f %f", &curNode->stu.math, &curNode->stu.english, &curNode->stu.computer);
			curNode->stu.average = (curNode->stu.math + curNode->stu.english + curNode->stu.computer) / 3.0f;
			printf("�޸ĳɹ�\n");
			break;
		}
		curNode = curNode->next;
	}
	if (curNode == NULL)
		printf("δ�ҵ���ѧ�����޸�ʧ��\n");
}

void removeStudent(List* list)	//�Ƴ�ǰ���ҵ�
{
	if (list->size == 0)
	{
		printf("ϵͳ����ѧ����Ϣ\n");
		return;
	}

	char buffer[32];
	printf("������Ҫɾ����ѧ����ѧ�Ż�����>");
	scanf("%s", buffer);

	//��bufferת������
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	Node* curNode = list->front;
	Node* prevNode = NULL;
	while (curNode != NULL)
	{
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)
		{
			break;
		}
		prevNode = curNode;
		curNode = curNode->next;

	}

	//�Ƿ��ҵ�
	if (curNode)
	{
		//Ҫɾ�����ǵ�һ���ڵ�
		if (prevNode == NULL)
		{
			list->front = curNode->next;
		}
		else
		{
			prevNode->next = curNode->next;
		}
		free(curNode);
		list->size--;
		printf("ɾ���ɹ�\n");
	}
	else
		printf("δ�ҵ���ѧ�����޸�ʧ��\n");
}

void rankStudent(List* list) {
	if (list->size <= 1) return;  // �������Ϊ�ջ�ֻ��һ���ڵ㣬����Ҫ����

	Node* sorted = NULL;  // ����������
	Node* current = list->front;

	while (current != NULL) {
		Node* next = current->next;
		if (sorted == NULL || (current->stu.math + current->stu.english + current->stu.computer) >= (sorted->stu.math + sorted->stu.english + sorted->stu.computer)) {
			current->next = sorted;
			sorted = current;
		}
		else {
			Node* temp = sorted;
			while (temp->next != NULL && (current->stu.math + current->stu.english + current->stu.computer) < (temp->next->stu.math + temp->next->stu.english + temp->next->stu.computer)) {
				temp = temp->next;
			}
			current->next = temp->next;
			temp->next = current;
		}
		current = next;
	}

	list->front = sorted;
}

void analyseStudent(List* list) {
	if (list->size == 0) 
	{
		printf("û��ѧ����Ϣ��\n");
		return;
	}

	// ��ʼ��ͳ�Ʊ���
	int acount = 0;
	float pass_math = 0, pass_english = 0, pass_computer = 0;
	float sum_math = 0, sum_english = 0, sum_computer = 0;
	float max_math = MIN, max_english = MIN, max_computer = MIN;
	float min_math = MAX, min_english = MAX, min_computer = MAX;

	Node* curNode = list->front;
	while (curNode != NULL) 
	{
		// �ۼ��ܷ�
		sum_math += curNode->stu.math;
		sum_english += curNode->stu.english;
		sum_computer += curNode->stu.computer;

		// ������߷�
		if (curNode->stu.math > max_math)
			max_math = curNode->stu.math;
		if (curNode->stu.english > max_english) 
			max_english = curNode->stu.english;
		if (curNode->stu.computer > max_computer) 
			max_computer = curNode->stu.computer;

		// ������ͷ�
		if (curNode->stu.math < min_math) 
			min_math = curNode->stu.math;
		if (curNode->stu.english < min_english) 
			min_english = curNode->stu.english;
		if (curNode->stu.computer < min_computer) 
			min_computer = curNode->stu.computer;

		// ͳ�Ƽ�������
		if (curNode->stu.math >= 60) 
			pass_math++;
		if (curNode->stu.english >= 60) 
			pass_english++;
		if (curNode->stu.computer >= 60) 
			pass_computer++;

		acount++;
		curNode = curNode->next;
	}

	// ����ƽ����
	float ave_math = sum_math / acount;
	float ave_english = sum_english / acount;
	float ave_computer = sum_computer / acount;

	// ���㼰����
	float pass_rate_math = pass_math / acount * 100;
	float pass_rate_english = pass_english / acount * 100;
	float pass_rate_computer = pass_computer / acount * 100;

	// ������
	printf("�༶�ɼ�����:\n");
	printf("��ѧ: ƽ���� %.2f, ��߷� %.2f, ��ͷ� %.2f, ������ %.2f%%\n", ave_math, max_math, min_math, pass_rate_math);
	printf("Ӣ��: ƽ���� %.2f, ��߷� %.2f, ��ͷ� %.2f, ������ %.2f%%\n", ave_english, max_english, min_english, pass_rate_english);
	printf("�����: ƽ���� %.2f, ��߷� %.2f, ��ͷ� %.2f, ������ %.2f%%\n", ave_computer, max_computer, min_computer, pass_rate_computer);
}

/*void printStudentInfoByClass(List* list, const char* className) {
	printf("********************************************************************\n");
	printf("*                       ѧ���ɼ�����ϵͳ                         *\n");
	printf("********************************************************************\n");
	printf("*  ѧ��\t* ����\t* �༶\t* ��ѧ\t* Ӣ��\t* �����\t* ƽ���ɼ�\t*\n");
	printf("********************************************************************\n");

	Node* curNode = list->front;
	int found = 0;

	while (curNode != NULL) {
		if (strcmp(curNode->stu.class, className) == 0) {
			found = 1;
			printf("* %llu\t* %s\t* %s\t* %.1f\t* %.1f\t* %.1f\t* %.1f\t*\n",
				curNode->stu.number, curNode->stu.name, curNode->stu.class,
				curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
		}
		curNode = curNode->next;
	}

	if (!found) {
		printf("δ�ҵ��ð༶��ѧ����Ϣ��\n");
	}

	printf("********************************************************************\n");
}*/

/*// ��ӡ����ѧ����Ϣ
void printAllStudentInfo(List* list) {
	printStudentInfoByClass(list, "");  // ���ݿ��ַ�����ʾ��ӡ����ѧ��
}*/