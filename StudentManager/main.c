#include<stdio.h>                                                                              
#include<stdbool.h>
#include<stdlib.h>
#include <string.h>

#include "StudentManager.h"		//���´���Ҫ�õ�ͷ�ļ�StudentManager.h�е�menu����˰Ѹ�ͷ�ļ���������





int main(int argc, char* arv[])
{
	//��������
	List list = { 0 };
	//�ڴ�����
	memset(&list, 0, sizeof(List));
	//02 10m	//��list�ĵ�ַ��ʼ����������sizeof(s)���ֽ�ȫ����Ϊ0��ȷ���ṹ���ʼ����Ҳ��ֹҰָ�����

	bool isRunning = true;
	while (isRunning)	//ʵ�ֶ�ι���ѡ�񣬶���ѡ��һ�ξ��˳�
	{

		switch (menu())	//���Ӵ���ɶ���
		{
		case Quit:
			isRunning = false;
			system("cls");
			printf("���˳�ѧ���ɼ�����ϵͳ\n");
			break;
		case Entry:
			entryStudent(&list);
			break;
		case Print:
			printStudent(&list);
			//printAllStudentInfo(&list);
			break;
		case Remove:
			removeStudent(&list);
			break;
		case Alter:
			alterStudent(&list);
			break;
		case Rank:
			rankStudent(&list);
			break;
		case Analyse:
			analyseStudent(&list);
			break;
		case Char:
			/*printAllStudentInfo(&list);*/
			break;
		case Save:
			//saveStudent(&list);
			saveStudentHuman(&list);
			break;
		case Read:
			//readStudent(&list);
			readStudentHuman(&list);
			break;
		case Find:
		{
			/*Node* node = findStudent(&list);
			if (!node)
			{
				printf("δ�ҵ�����ѯѧ��\n");
			}*/
			findStudent(&list);
			break;
		}
		/*case test:
		{
			char className[20];
			printf("������Ҫ��ѯ�İ༶���ƣ�");
			scanf("%s", className);
			printStudentInfoByClass(&list, className);
		}
		break;*/
		
		default:
			printf("�����������\n");
			//isRunning = false;	//������ٽ���˵���
			break;
		}

		if (isRunning)
		{
			//�ó�����ͣһ���
			system("pause");
			//����������ɾ��ѭ����ӡ�Ķ���˵�
			system("cls");
		}	
		}

		return 0;
	
}

