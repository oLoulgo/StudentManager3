#include "StudentManager.h"

#include<stdio.h>		//此处要用到printf和scanf函数
#include<malloc.h>
#include<string.h>

static Node* CreateNode()	//为创建节点写一个函数，静态内部的？，因为这个代码会复用多次（entryStudent和readStudent）,使代码更简洁
{
	//创建节点
	Node* node = malloc(sizeof(Node));
	if (!node)	//内存不足就分配失败
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
	printf("*		学生成绩管理系统		*\n");
	printf("**********************************************************************\n");
	printf("*	    	    选择功能    	    	*\n");
	printf("**********************************************************************\n");
	printf("*	    	  1.添加学生信息    	    	*\n");
	printf("*	    	  2.打印学生信息    	    	*\n");
	printf("*	    	  3.删除学生信息    	    	*\n");
	printf("*	    	  4.修改学生信息    	    	*\n");
	printf("*	    	  5.学生数据排序    		*\n");
	printf("*	    	  6.班级成绩分析    	    	*\n");
	printf("*	    	  7.输出学生信息表    		*\n");
	printf("*	    	  8.保存学生信息    	    	*\n");
	printf("*	    	  9.读取学生信息    	    	*\n");
	printf("*	    	  10.查找学生信息    	    	*\n");
	printf("*	    	  0.退出系统    	    	*\n");
	printf("*************************************************\n");
	printf("select>");
	int select = -1;
	scanf("%d", &select);
	return select;
}

void entryStudent(List* list)
{
	/*//创建节点	
	Node* node = malloc(sizeof(Node));
	if (!node)	//内存不足就分配失败
	{
		printf("malloc failed\n");
		return;
	}
	node->next = NULL;
	*/

	//创建头结点
	Node* node = CreateNode();	//复用了创建节点

	//输入学生信息
	printf("请输入学生学号>");
	scanf("%llu", &node->stu.number);	//因为是个整型(长整型)，必须取地址&

	printf("请输入学生姓名>");
	scanf("%s", node->stu.name);		//姓名是字符串，是字符数组,数组名就是首地址，因此不用&

	printf("请输入学生班级>");
	scanf("%s", node->stu.class);

	printf("请输入学生数学成绩>");
	scanf("%f", &node->stu.math);

	printf("请输入学生英语成绩>");
	scanf("%f", &node->stu.english);

	printf("请输入学生计算机成绩>");
	scanf("%f", &node->stu.computer);

	node->stu.average = (node->stu.math + node->stu.english + node->stu.computer) /3.0f;

	//插入到链表中
	node->next = list->front;	//头插：新结点指向原链表最后一个，front指向新结点
	list->front = node;
	list->size++;

}

void printStudent(List* list)
{
	printf("********************************************************************\n");
	printf("*			学生成绩管理系统			   *\n");
	printf("********************************************************************\n");
	printf("*	学号	*  姓名  *  班级  *  数学  *  英语  *   计算机   *  平均成绩  *\n");	//都用两个tab试试
	printf("********************************************************************\n");

	//遍历链表	//04  4m
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
	//打开文件
	FILE* fp = fopen("students.data", "wb");	//wb指用二进制写入，因此文件中看不懂
	if (!fp)
	{
		perror("file open failed");
		return;
	}

	//写入学生信息
	Node* curNode = list->front;
	while (curNode != NULL)
	{
		fwrite(&curNode->stu, sizeof(Student), 1, fp);	//写入数据的地址，要写入元素的大小，写入1个，写入fp文件
		curNode = curNode->next;
	}

	//关闭文件
	fclose(fp);
}

void saveStudentHuman(List* list)
{
	//打开文件
	FILE* fp = fopen("students.txt", "w");	//wb指用二进制写入，因此文件中看不懂
	if (!fp)
	{
		perror("file open failed");
		return;
	}

	//写入学生信息
	Node* curNode = list->front;
	while (curNode != NULL)
	{
		fprintf(fp,"%llu\t%s\t%s\t%.lf\t%.lf\t%.lf\t%.lf\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
			curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
		curNode = curNode->next;
	}

	//关闭文件
	fclose(fp);
}

void readStudent(List* list)
{
	//打开文件
	FILE* fp = fopen("students.data", "rb");	//这里把saveStudent里的复制过来，但是把里面的wb改成rb，用以存储文件，否则会像之前自己演示一样，关闭再重新读取显示文件空白
	if (!fp)
	{
		perror("file open failed");
		return;
	}

	//读取学生信息
	while (!feof(fp))	//未读完时就一直读
	{
		Node* node = CreateNode();	//复用了创建节点
		if (!node)	//创建失败就跳出循环
			break;

		size_t len = fread(&node->stu, sizeof(Student), 1, fp);		//指向一块内存的指针（存放读取进来的数据），每个元素的大小，要读取的元素个数，从fp这个文件里读
		if (len == 0)	//返回0就说明读失败了，就可以不读了？
		{
			free(node);
			break;
		}

		//插入到链表中		//把读取的元素插入到链表当中？
		node->next = list->front;
		list->front = node;
		list->size++;
	}

	//关闭文件
	fclose(fp);

}

void readStudentHuman(List* list)
{
	//打开文件
	FILE* fp = fopen("students.txt", "r");	//r,读的方式
	if (!fp)
	{
		perror("file open failed");
		return;
	}

		//读取学生信息
	while (!feof(fp))	//未读完就一直读
	{
		Node* node = CreateNode();
		if (!node)
			break;
		fscanf(fp,"%llu\t%s\t%s\t%f\t%f\t%f\t%f\n", &node->stu.number, node->stu.name, node->stu.class,
			&node->stu.math, &node->stu.english, &node->stu.computer, &node->stu.average);	//为什么%.lf改成了%f	/原有if （7 ！=）
		//{
		//	free(node);
		//	break;
		//}

		//插入链表
		node->next = list->front;
		list->front = node;
		list->size++;
	}

		//关闭文件
		fclose(fp);

}

/*Node* findStudent(List* list)
{
	///if (list->size == 0)
	//{
	//	//printf("系统中无学生信息\n");
	//	return;
	//}

	char buffer[32];
	printf("请输入学生的学号或姓名>");
	scanf("%s", buffer);

	//把buffer转成整型
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
}	 //为什么不用void*/
void findStudent(List* list)
{
	char buffer[32];
	printf("请输入学生的学号或姓名>");
	scanf("%s", buffer);

	//把buffer转成整型
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
			printf("未找到所查询学生\n");
		}
	
}

void alterStudent(List* list)	//先查找再修改
{
	if (list->size == 0)
	{
		printf("系统中无学生信息\n");
		return;
	}

	char buffer[32];
	printf("请输入要修改的学生的学号或姓名>");
	scanf("%s", buffer);

	//把buffer转成整型
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL)
	{
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)
		{
			printf("请输入要修改的学生各科成绩>");
			scanf("%f %f %f", &curNode->stu.math, &curNode->stu.english, &curNode->stu.computer);
			curNode->stu.average = (curNode->stu.math + curNode->stu.english + curNode->stu.computer) / 3.0f;
			printf("修改成功\n");
			break;
		}
		curNode = curNode->next;
	}
	if (curNode == NULL)
		printf("未找到该学生，修改失败\n");
}

void removeStudent(List* list)	//移除前先找到
{
	if (list->size == 0)
	{
		printf("系统中无学生信息\n");
		return;
	}

	char buffer[32];
	printf("请输入要删除的学生的学号或姓名>");
	scanf("%s", buffer);

	//把buffer转成整型
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

	//是否找到
	if (curNode)
	{
		//要删除的是第一个节点
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
		printf("删除成功\n");
	}
	else
		printf("未找到该学生，修改失败\n");
}

void rankStudent(List* list) {
	if (list->size <= 1) return;  // 如果链表为空或只有一个节点，不需要排序

	Node* sorted = NULL;  // 排序后的链表
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
		printf("没有学生信息。\n");
		return;
	}

	// 初始化统计变量
	int acount = 0;
	float pass_math = 0, pass_english = 0, pass_computer = 0;
	float sum_math = 0, sum_english = 0, sum_computer = 0;
	float max_math = MIN, max_english = MIN, max_computer = MIN;
	float min_math = MAX, min_english = MAX, min_computer = MAX;

	Node* curNode = list->front;
	while (curNode != NULL) 
	{
		// 累加总分
		sum_math += curNode->stu.math;
		sum_english += curNode->stu.english;
		sum_computer += curNode->stu.computer;

		// 更新最高分
		if (curNode->stu.math > max_math)
			max_math = curNode->stu.math;
		if (curNode->stu.english > max_english) 
			max_english = curNode->stu.english;
		if (curNode->stu.computer > max_computer) 
			max_computer = curNode->stu.computer;

		// 更新最低分
		if (curNode->stu.math < min_math) 
			min_math = curNode->stu.math;
		if (curNode->stu.english < min_english) 
			min_english = curNode->stu.english;
		if (curNode->stu.computer < min_computer) 
			min_computer = curNode->stu.computer;

		// 统计及格人数
		if (curNode->stu.math >= 60) 
			pass_math++;
		if (curNode->stu.english >= 60) 
			pass_english++;
		if (curNode->stu.computer >= 60) 
			pass_computer++;

		acount++;
		curNode = curNode->next;
	}

	// 计算平均分
	float ave_math = sum_math / acount;
	float ave_english = sum_english / acount;
	float ave_computer = sum_computer / acount;

	// 计算及格率
	float pass_rate_math = pass_math / acount * 100;
	float pass_rate_english = pass_english / acount * 100;
	float pass_rate_computer = pass_computer / acount * 100;

	// 输出结果
	printf("班级成绩分析:\n");
	printf("数学: 平均分 %.2f, 最高分 %.2f, 最低分 %.2f, 及格率 %.2f%%\n", ave_math, max_math, min_math, pass_rate_math);
	printf("英语: 平均分 %.2f, 最高分 %.2f, 最低分 %.2f, 及格率 %.2f%%\n", ave_english, max_english, min_english, pass_rate_english);
	printf("计算机: 平均分 %.2f, 最高分 %.2f, 最低分 %.2f, 及格率 %.2f%%\n", ave_computer, max_computer, min_computer, pass_rate_computer);
}

/*void printStudentInfoByClass(List* list, const char* className) {
	printf("********************************************************************\n");
	printf("*                       学生成绩管理系统                         *\n");
	printf("********************************************************************\n");
	printf("*  学号\t* 姓名\t* 班级\t* 数学\t* 英语\t* 计算机\t* 平均成绩\t*\n");
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
		printf("未找到该班级的学生信息。\n");
	}

	printf("********************************************************************\n");
}*/

/*// 打印所有学生信息
void printAllStudentInfo(List* list) {
	printStudentInfoByClass(list, "");  // 传递空字符串表示打印所有学生
}*/