#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>  //用来改变颜色 

typedef struct Student {      //学生信息结构体 
	char id[20]; //学号
	char name[10];  //姓名
	float score[4]; //成绩
	int flag;     //定义flag进行验证，students[i].flag == 1为真，继续执行下一步操作 
}student;

student students[50];   //定义可以容纳50个学生的数组，50也可以为后续循环结束的标志 

void printHead() //输出成绩单的表头
{
	printf("学号    姓名    语文    数学    英语    总成绩\n");
}


void Menu()  //主菜单页 
{
	printf("\n\n\n");
	printf("\t\t************************欢迎访问学生成绩管理系统*************************\n\n\n");
	printf("\t\t                      1---学生信息数据的录入\n");
	printf("\t\t                      2---学生信息数据查询\n");
	printf("\t\t                      3---学生信息数据删除\n");
	printf("\t\t                      4---学生信息数据修改\n");
	printf("\t\t                      5---显示所有学生的信息\n");
	printf("\t\t                      6---成绩及格率查询\n");
	printf("\t\t                      0---退出系统\n");
	printf("\n\n\n\t\t*************************************************************************");
	printf("\n\n请在0-6中选择，以回车键结束\n");
}


/*在Excel或者WPS中将成绩表格另存为以制表符分割的文本文件 ，并命名为score.txt保存在程序
所在的文件夹内方便读写文件 ，请记得删除表头，否则会出错*/


void writefile()  //写入文件，进行增加和删除之后调用以保存数据 
{
	int i, j;
	FILE* file = fopen("score.txt", "w");
	for (i = 0; i < 50; i++)
	{
		if (students[i].flag == 1)
		{
			fprintf(file, "%s %s ", students[i].id, students[i].name); //学号，姓名 

			for (j = 0; j < 4; j++) //利用循环将成绩保存在结构体数组内
			{
				fprintf(file, "%f ", students[i].score[j]); /* 数组下标从0开始，将第一门成绩存入students[i].score[0] ，以此类推 */
			}
			fprintf(file, "\n");
		}
	}
}

void readfile() //读出文件 
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



void print(int i) //打印函数，输出信息 
{
	int j;
	printf("%-8s%-8s", students[i].id, students[i].name);
	for (j = 0; j < 4; j++)
	{
		printf("%-8.2f", students[i].score[j]);
	}
	printf("\n");
}


void add()  //信息增加函数 
{
	int i, j;
	printf("请输入学生学号,姓名，语文，数学，英语，总成绩: \n");
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
			printf("录入完成\n");
			break;
		}
	}

	writefile();  //把修改后的数据进行保存 
}

void search_id()  //学号搜索 
{
	char id[20];
	int i, j;
	printf("请输入要搜索的学生学号：");
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


void search_name()  //姓名搜索函数 
{
	char name[20];
	int i, j;
	printf("请输入要搜索的学生姓名：");
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


void search_stu()   //信息搜索函数 
{
	int select;
	printf("按学号查找请输：1\n按姓名查找请按：2\n");
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

void del()  //按学号删除信息 
{
	char id[20]; //该id与结构体内的id不同，这里只是暂存输入的id 
	int i, j;
	printf("请输入要删除的学生学号：");
	scanf("%s", id);
	for (i = 0; i < 50; i++)
	{
		if (students[i].flag == 1)
		{
			if (strcmp(students[i].id, id) == 0) //将输入的id复制给结构体数组内的id 
			{
				printHead(); //表头函数 
				print(i);
				students[i].flag = 0;
				printf("已删除\n");
				break;
			}
		}
	}
	writefile();  //把修改后的数据进行保存 
}


void modification() //按学号修改信息 
{
	char id[20];
	int i, j;
	printf("请输入要修改的学生学号：");
	scanf("%s", id);
	for (i = 0; i < 50; i++)
	{
		if (students[i].flag == 1)
		{
			if (strcmp(students[i].id, id) == 0)
			{
				printHead();
				print(i);
				printf("请输入学生学号,姓名，语文，数学，英语，总成绩: \n");
				scanf("%s %s", students[i].id, students[i].name);
				for (j = 0; j < 4; j++)
				{
					scanf("%f", &students[i].score[j]);
				}
				printf("修改完成\n");
				printHead();
				print(i);
				break;
			}
		}
		else
			printf("当前学号不存在!");

	}
	writefile();  //把修改后的数据进行保存 
}


void sort()  //及格率统计 
{
	int i, count = 0, count1 = 0, count2 = 0, count3 = 0;  // count 用来统计及格人数, count1,2,3分别统计语数英各科及格人数 
	float rate = 0; //及格率 	 
	for (i = 0; i < 50; i++)
	{
		if (students[i].score[3] >= 270)  //及格判断标志 
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


	printf("总分及格的人数共有：%d人\n", count);
	printf("语文成绩及格的人数共有：%d人\n:", count1);
	printf("数学成绩及格的人数共有：%d人\n", count2);
	printf("英语成绩及格的人数共有：%d人\n", count3);


}


void printAll() //输出所有学生的信息 
{
	int i;
	printHead(); //表头函数，在这里调用 
	for (i = 0; i < 50; i++)
	{
		if (students[i].flag == 1)
		{
			print(i);  //调用打印函数 
		}
	}
}


int main() //主函数 
{
	system("title 成绩管理系统");
	system("color BD");    // 改变界面颜色 
	readfile();     //将文件内的数据读入 
	while (1)
	{
		Menu();
		int choice; //根据输入数字进行对应的函数功能调用  
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			add(); //添加函数 
			break;
		case 2:
			search_stu(); //搜索函数 
			break;
		case 3:
			del(); //删除函数 
			break;
		case 4:
			modification(); //信息修改函数 
			break;
		case 5:
			printAll(); //信息输出
			break;
		case 6:
			sort(); //及格情况统计 
			break;
		case 0:
			exit(0);
			break;
		}
	}
}


