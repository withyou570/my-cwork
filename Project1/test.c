#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>  //�����ı���ɫ 

typedef struct Student {      //ѧ����Ϣ�ṹ�� 
	char id[20]; //ѧ��
	char name[10];  //����
	float score[4]; //�ɼ�
	int flag;     //����flag������֤��students[i].flag == 1Ϊ�棬����ִ����һ������ 
}student;

student students[50];   //�����������50��ѧ�������飬50Ҳ����Ϊ����ѭ�������ı�־ 

void printHead() //����ɼ����ı�ͷ
{
	printf("ѧ��    ����    ����    ��ѧ    Ӣ��    �ܳɼ�\n");
}


void Menu()  //���˵�ҳ 
{
	printf("\n\n\n");
	printf("\t\t************************��ӭ����ѧ���ɼ�����ϵͳ*************************\n\n\n");
	printf("\t\t                      1---ѧ����Ϣ���ݵ�¼��\n");
	printf("\t\t                      2---ѧ����Ϣ���ݲ�ѯ\n");
	printf("\t\t                      3---ѧ����Ϣ����ɾ��\n");
	printf("\t\t                      4---ѧ����Ϣ�����޸�\n");
	printf("\t\t                      5---��ʾ����ѧ������Ϣ\n");
	printf("\t\t                      6---�ɼ������ʲ�ѯ\n");
	printf("\t\t                      0---�˳�ϵͳ\n");
	printf("\n\n\n\t\t*************************************************************************");
	printf("\n\n����0-6��ѡ���Իس�������\n");
}


/*��Excel����WPS�н��ɼ�������Ϊ���Ʊ���ָ���ı��ļ� ��������Ϊscore.txt�����ڳ���
���ڵ��ļ����ڷ����д�ļ� ����ǵ�ɾ����ͷ����������*/


void writefile()  //д���ļ����������Ӻ�ɾ��֮������Ա������� 
{
	int i, j;
	FILE* file = fopen("score.txt", "w");
	for (i = 0; i < 50; i++)
	{
		if (students[i].flag == 1)
		{
			fprintf(file, "%s %s ", students[i].id, students[i].name); //ѧ�ţ����� 

			for (j = 0; j < 4; j++) //����ѭ�����ɼ������ڽṹ��������
			{
				fprintf(file, "%f ", students[i].score[j]); /* �����±��0��ʼ������һ�ųɼ�����students[i].score[0] ���Դ����� */
			}
			fprintf(file, "\n");
		}
	}
}

void readfile() //�����ļ� 
{
	int i, j;
	FILE* file = fopen("score.txt", "r");
	if (file)
	{
		for (i = 0; i < 50; i++)
		{
			if (students[i].flag == 0)
			{
				fscanf(file, "%s %s ", students[i].id, students[i].name);
				for (j = 0; j < 4; j++)
				{
					fscanf(file, "%f ", &students[i].score[j]);
				}
				fscanf(file, "\n");
				students[i].flag = 1;
				if (feof(file)) break;
			}
		}
	}
}



void print(int i) //��ӡ�����������Ϣ 
{
	int j;
	printf("%-8s%-8s", students[i].id, students[i].name);
	for (j = 0; j < 4; j++)
	{
		printf("%-8.2f", students[i].score[j]);
	}
	printf("\n");
}


void add()  //��Ϣ���Ӻ��� 
{
	int i, j;
	printf("������ѧ��ѧ��,���������ģ���ѧ��Ӣ��ܳɼ�: \n");
	for (i = 0; i < 50; i++)
	{
		if (students[i].flag == 0)
		{
			scanf("%s %s", students[i].id, students[i].name);
			for (j = 0; j < 4; j++)
			{
				scanf("%f", &students[i].score[j]);
			}
			students[i].flag = 1;
			printf("¼�����\n");
			break;
		}
	}

	writefile();  //���޸ĺ�����ݽ��б��� 
}

void search_id()  //ѧ������ 
{
	char id[20];
	int i, j;
	printf("������Ҫ������ѧ��ѧ�ţ�");
	scanf("%s", id);
	for (i = 0; i < 50; i++)
	{
		if (students[i].flag == 1)
		{
			if (strcmp(students[i].id, id) == 0)
			{
				printHead();
				print(i);
				break;
			}
		}
	}
}


void search_name()  //������������ 
{
	char name[20];
	int i, j;
	printf("������Ҫ������ѧ��������");
	scanf("%s", name);
	for (i = 0; i < 50; i++)
	{
		if (students[i].flag == 1)
		{
			if (strcmp(students[i].name, name) == 0)
			{
				printHead();
				print(i);
				break;
			}
		}
	}
}


void search_stu()   //��Ϣ�������� 
{
	int select;
	printf("��ѧ�Ų������䣺1\n�����������밴��2\n");
	scanf("%d", &select);
	switch (select)
	{
	case 1:
		search_id();
		break;
	case 2:
		search_name();
		break;
	}

}

void del()  //��ѧ��ɾ����Ϣ 
{
	char id[20]; //��id��ṹ���ڵ�id��ͬ������ֻ���ݴ������id 
	int i, j;
	printf("������Ҫɾ����ѧ��ѧ�ţ�");
	scanf("%s", id);
	for (i = 0; i < 50; i++)
	{
		if (students[i].flag == 1)
		{
			if (strcmp(students[i].id, id) == 0) //�������id���Ƹ��ṹ�������ڵ�id 
			{
				printHead(); //��ͷ���� 
				print(i);
				students[i].flag = 0;
				printf("��ɾ��\n");
				break;
			}
		}
	}
	writefile();  //���޸ĺ�����ݽ��б��� 
}


void modification() //��ѧ���޸���Ϣ 
{
	char id[20];
	int i, j;
	printf("������Ҫ�޸ĵ�ѧ��ѧ�ţ�");
	scanf("%s", id);
	for (i = 0; i < 50; i++)
	{
		if (students[i].flag == 1)
		{
			if (strcmp(students[i].id, id) == 0)
			{
				printHead();
				print(i);
				printf("������ѧ��ѧ��,���������ģ���ѧ��Ӣ��ܳɼ�: \n");
				scanf("%s %s", students[i].id, students[i].name);
				for (j = 0; j < 4; j++)
				{
					scanf("%f", &students[i].score[j]);
				}
				printf("�޸����\n");
				printHead();
				print(i);
				break;
			}
		}
		else
			printf("��ǰѧ�Ų�����!");

	}
	writefile();  //���޸ĺ�����ݽ��б��� 
}


void sort()  //������ͳ�� 
{
	int i, count = 0, count1 = 0, count2 = 0, count3 = 0;  // count ����ͳ�Ƽ�������, count1,2,3�ֱ�ͳ������Ӣ���Ƽ������� 
	float rate = 0; //������ 	 
	for (i = 0; i < 50; i++)
	{
		if (students[i].score[3] >= 270)  //�����жϱ�־ 
			count++;
	}
	for (i = 0; i < 50; i++)
	{
		if (students[i].score[0] >= 90)
			count1++;
	}
	for (i = 0; i < 50; i++)
	{
		if (students[i].score[1] >= 90)
			count2++;
	}
	for (i = 0; i < 50; i++)
	{
		if (students[i].score[2] >= 90)
			count3++;
	}


	printf("�ּܷ�����������У�%d��\n", count);
	printf("���ĳɼ�������������У�%d��\n:", count1);
	printf("��ѧ�ɼ�������������У�%d��\n", count2);
	printf("Ӣ��ɼ�������������У�%d��\n", count3);


}


void printAll() //�������ѧ������Ϣ 
{
	int i;
	printHead(); //��ͷ��������������� 
	for (i = 0; i < 50; i++)
	{
		if (students[i].flag == 1)
		{
			print(i);  //���ô�ӡ���� 
		}
	}
}


int main() //������ 
{
	system("title �ɼ�����ϵͳ");
	system("color BD");    // �ı������ɫ 
	readfile();     //���ļ��ڵ����ݶ��� 
	while (1)
	{
		Menu();
		int choice; //�����������ֽ��ж�Ӧ�ĺ������ܵ���  
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			add(); //��Ӻ��� 
			break;
		case 2:
			search_stu(); //�������� 
			break;
		case 3:
			del(); //ɾ������ 
			break;
		case 4:
			modification(); //��Ϣ�޸ĺ��� 
			break;
		case 5:
			printAll(); //��Ϣ���
			break;
		case 6:
			sort(); //�������ͳ�� 
			break;
		case 0:
			exit(0);
			break;
		}
	}
}


