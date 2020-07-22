#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Student  //表一格式
{
    int num; //学号
    char name[4]; //姓名
    char sex; //性别
    int age; //年龄
    char college[10]; //院系
    struct Student *next;
} stu;
typedef struct Class    //表二格式
{
    int cla_num; //课程号
    char cla_name[4] ; //课程名
    char cla_pre; //先行课
    int credit; //学分
} cla;
typedef struct person   //表三格式
{
    int num; //学号
    int cla_num; //课程号
    int score; //成绩
    struct person *next;
} per;

int n1; //记录表一的学生个数，也是动态链表的结点个数

int main(void)
{
    stu *create(void);  //从硬盘读入原始学生的数据
    void free_p(stu *p);    //释放内存
    stu *insert(stu *head, stu *stu_t);  //插入学生信息
    stu *dele(stu *head, int num);    //删除学生信息
    stu *change(stu *head, int num);  //改变学生信息
    void seek(stu *head, int num);    //寻找特定的学生
    int content(void);   //创建开始界面
    void save(stu *head);  //保存文件修改的内容，导入硬盘
    void seek_aver(stu *head, int num);  //查询学生平均成绩
    stu *p1, *head;
    int key, number; //选择操作的号码，要打印学生的个数
    int num_del, num_chg, num_seek; //删除的学号，修改的学号，查找的学号
    p1 = head = create(); //从硬盘读入原始学生数据，并创建动态链表
    do{
        key = content(); //键盘输入数字，选择要执行的功能
        switch(key)
        {
            case 0:
                save(head);
                break;
            case 1: //功能一
                printf("输入要打印学生人数:");
                scanf("%d", &number);
                int i;
                p1 = head;
                for(i = 0; i < number; i++)
                {
                    printf("%d  %s  %c  %d  %s\n", p1->num, p1->name, p1->sex, p1->age, p1->college);
                    p1 = p1->next;
                }
                system("pause");
                break;
            case 2:{ //功能二
                stu *stu_new = (stu *)malloc(sizeof(stu));
                printf("输入要添加学生的学号:");
                scanf("%d", &stu_new->num);
                p1 = head;
                while(p1->num != stu_new->num && p1->next != NULL) //学号查重功能
                {
                    p1 = p1->next;
                }
                if(p1->num == stu_new->num) //确认学号是否重合
                {
                    printf("该学号已经存在！请重新输入！\n");
                    system("pause");
                    break;
                }
                printf("输入要添加学生的姓名(不大于3个字母):");
                scanf("%s", stu_new->name);
                getchar();
                printf("输入要添加学生的性别(M/F):");
                scanf("%c", &stu_new->sex);
                if(stu_new->sex != 'M' && stu_new->sex != 'F') //性别符号检查
                {
                    printf("输入无效性别！请重新输入！\n");
                    break;
                }
                printf("输入要添加学生的年龄:");
                scanf("%d", &stu_new->age);
                if(stu_new->age > 26 || stu_new->age < 19) //年龄的检查
                {
                    printf("请重新确认年龄是否正确！\n");
                    break;
                }
                printf("输入要添加学生的院系:");
                scanf("%s", stu_new->college);
                p1 = insert(head, stu_new);
                break;}
            case 3: //功能三
                printf("输入要删除的学生学号:");
                scanf("%d", &num_del);
                p1 = dele(head, num_del);
                break;
            case 4: //功能四
                printf("输入要修改的学生学号:");
                scanf("%d", &num_chg);
                p1 = change(head, num_chg);
                break;
            case 5: //功能五
                printf("输入要查找的学生学号:");
                scanf("%d", &num_seek);
                seek(head, num_seek);
                break;
            case 6: //功能六
                printf("当前系统录入的人数:%d\n", n1);
                system("pause");
                break;
            case 7: //功能七
                printf("输入要查询的学生平均成绩的学号:");
                scanf("%d", &num_seek);
                seek_aver(head, num_seek);
                break;
            default: //输入无效操作
                printf("没有相关操作！请重新输入\n");
                system("pause");
                break;
        }
    }while(key);
    free_p(head);
    return 0;
}

int content(void)  //创建开始界面
{
    int n = 0;
    system("cls");
    printf("------------------------\n");
    printf("      关系数据库\n");
    printf("------------------------\n");
    printf("欢迎进入暨南大学学生数据库！\n");
    printf("   1:打印学生信息\n");
    printf("   2:增加学生信息\n");
    printf("   3:删除学生信息\n");
    printf("   4:学生信息修改\n");
    printf("   5:查找学生信息\n");
    printf("   6:系统学生人数\n");
    printf("   7:查学生平均成绩\n");
    printf("   0:保存信息,退出\n");
    printf("------------------------\n");
    printf("选择操作:");
    scanf("%d", &n);
    return n;
}

stu *create(void)  //从硬盘读入原始学生的数据
{
    stu *head, *p1, *p2;
    FILE *f1;
    if((f1 = fopen("学生信息.txt", "r")) == NULL)
    {
        printf("error");
        exit(0);
    }
    head = NULL;  //创建动态单链表
    n1 = 0;
    p1 = p2 = (stu *)malloc(sizeof(stu));
    fscanf(f1, "%d  %s  %c  %d  %s\n", &p1->num, p1->name, &p1->sex, &p1->age, p1->college);
    while(!feof(f1))
    {
        n1++;
        if(n1 == 1)
            head = p1;
        else
        {
            p2->next = p1;
            p2 = p1;
        }
        p1 = (stu *)malloc(sizeof(stu));
        fscanf(f1, "%d  %s  %c  %d  %s\n", &p1->num, p1->name, &p1->sex, &p1->age, p1->college);
    }
    p2->next = NULL;
    fclose(f1);
    return head;
}

stu *insert(stu *head, stu *stu_t) //插入学生信息
{
    clock_t start, finish;
    double duration = 0;
    start = clock();
    stu *pt, *p1, *p2; //动态链表的结点插入
    pt = stu_t;
    p1 = head;
    while(pt->num > p1->num && p1->next != NULL)
    {
        p2 = p1;
        p1 = p1->next;
    }
    if(pt->num <= p1->num)
    {
        if(head == p1)
            head = pt;
        else
            p2->next = pt;
        pt->next = p1;
    }
    else
    {
        p1->next = pt;
        pt->next = NULL;
    }
    n1++;
    per fives[5];  //随机给插入学生生成成绩，准备存入文件三
    for(int i = 0; i < 5; i++)
    {
        fives[i].num = stu_t->num;
        fives[i].cla_num = (rand() % 60 + 1) + 1000;
        fives[i].score = rand() % 60 + 40;
    }
    FILE *f1, *f2; //同时增加文件三的学生成绩记录
    if((f1 = fopen("学生-课程成绩信息.txt", "r")) == NULL)
    {
        printf("error");
        exit(0);
    }
    if((f2 = fopen("学生-课程成绩信息副本.txt", "w")) == NULL)
    {
        printf("error");
        exit(0);
    }
    per *p = (per*)malloc(sizeof(per));
    int size = 0;
    while(!feof(f1))  //将增加学生后的链表重新写入文件
    {
        fscanf(f1, "%d  %d  %d\n", &p->num, &p->cla_num, &p->score);
        if(p->num - stu_t->num == 1 && size == 0)
        {
            for(int i = 0; i < 5; i++)
                fprintf(f2, "%d  %d  %d\n", fives[i].num, fives[i].cla_num, fives[i].score);
            fprintf(f2, "%d  %d  %d\n", p->num, p->cla_num, p->score);
            size = 1;
        }
        else
            fprintf(f2, "%d  %d  %d\n", p->num, p->cla_num, p->score);
    }
    free(p);
    fclose(f1);
    fclose(f2);
    finish = clock();
    printf("成功插入学号为%d学生\n", stu_t->num);
    duration = (double)(finish - start)/CLOCKS_PER_SEC;
    printf("%f seconds\n", duration);
    system("pause");
    return head;
}

stu *dele(stu *head, int num)  //删除学生信息
{
    clock_t start, end;
    double duration = 0;
    start = clock();
    stu *p1, *p2;  //动态链表结点的删除
    p1 = head;
    while(num != p1->num && p1->next != NULL) 
    {
        p2 = p1;
        p1 = p1->next;
    }
    if(num == p1->num)
    {
        if(p1 == head)
            head = p1->next;
        else
            p2->next = p1->next;
        printf("成功删除学号%d的同学\n", num);
        n1 = n1 -1;
    }
    else
    {
        printf("error");
    }
    FILE *f1, *f2; //同时删去文件三的学生成绩记录
    if((f1 = fopen("学生-课程成绩信息.txt", "r")) == NULL)
    {
        printf("error");
        exit(0);
    }
    if((f2 = fopen("学生-课程成绩信息副本.txt", "w")) == NULL)
    {
        printf("error");
        exit(0);
    }
    per *p = (per*)malloc(sizeof(per));
    while(!feof(f1))  //将修改后的链表写入文件
    {
        fscanf(f1, "%d  %d  %d\n", &p->num, &p->cla_num, &p->score);
        if(p->num == num)
            continue;
        fprintf(f2, "%d  %d  %d\n", p->num, p->cla_num, p->score);
    }
    free(p);
    fclose(f1);
    fclose(f2);
    end = clock();
    duration = (double)(end - start)/CLOCKS_PER_SEC;
    printf("%lf seconds\n", duration);
    system("pause");
    return head;
}

stu *change(stu *head, int num)  //改变学生信息
{
    clock_t start, end;
    double duration = 0;
    start = clock();
    stu *p1, *p2;
    p1 = head;  //动态链表结点的访问
    while(num != p1->num && p1->next != NULL)
    {
        p2 = p1;
        p1 = p1->next;
    }
    end = clock();
    duration = (double)(end - start)/CLOCKS_PER_SEC;
    if(p1->next == NULL)
    {
        printf("没有找到学号%d的同学\n", num);
    }
    else
    {
        int choice;
        printf("请输入要修改的信息(0.退出，1.姓名，2.性别，3.年龄，4.院系):");
        scanf("%d", &choice);
        getchar();
        switch (choice)  //选择要修改的属性
        {
        case 1:
            printf("输入姓名:");
            scanf("%s", p1->name);
            printf("修改成功\n");
            break;
        case 2:
            printf("输入性别:");
            scanf("%c", &p1->sex);
            printf("修改成功\n");
            break;
        case 3:
            printf("输入年龄:");
            scanf("%d", &p1->age);
            printf("修改成功\n");
            break;
        case 4:
            printf("输入院系:");
            scanf("%s", p1->college);
            printf("修改成功\n");
            break;
        default:
            break;
        }
    }
    printf("%lf seconds\n", duration);
    system("pause");
    return head;
}

void seek(stu *head, int num)  //寻找特定的学生
{
    clock_t start, end;
    double duration = 0;
    start = clock();
    stu *p1, *p2; //动态链表结点的访问
    p1 = head;
    while(num != p1->num && p1->next != NULL)
    {
        p2 = p1;
        p1 = p1->next;
    }
    end = clock();
    duration = (double)(end - start)/CLOCKS_PER_SEC;
    if(p1->next == NULL)
    {
        printf("没有找到学号%d的同学\n", num);
    }
    else
    {
        int choice;
        printf("请输入要查找的信息(0.退出，1.姓名，2.性别，3.年龄，4.院系，5.全部信息):");
        scanf("%d", &choice);
        getchar();
        switch (choice) //输入要查找的学生属性
        {
        case 1:
            printf("学号%d学生的姓名为%s\n", num, p1->name);
            break;
        case 2:
            printf("学号%d学生的性别为%c\n", num, p1->sex);
            break;
        case 3:
            printf("学号%d学生的年龄为%s\n", num, p1->age);
            break;
        case 4:
            printf("学号%d学生的院系为%s\n", num, p1->college);;
            break;
        case 5:
            printf("全部信息:%d %s %c %d %s\n", p1->num, p1->name, p1->sex, p1->age, p1->college);
        default:
            break;
        }
    }
    printf("%lf seconds\n", duration);
    system("pause");
}

void save(stu *head)  //保存文件修改的内容，导入硬盘
{
    FILE *f1;
    if((f1 = fopen("学生信息副本.txt", "w")) == NULL)
    {
        printf("error");
        exit(0);
    }
    stu *p1 = head;
    do{
        fprintf(f1, "%d  %s  %c  %d  %s\n", p1->num, p1->name, p1->sex, p1->age, p1->college);
        p1 = p1->next;
    }while(p1->next != NULL);
    fclose(f1);
}

void seek_aver(stu *head, int num) //查询学生平均成绩
{
    clock_t start, end;
    double duration = 0;
    start = clock();
    FILE *f1;
    float sum = 0;
    stu *p1, *p2;
    p1 = head;
    while(num != p1->num && p1->next != NULL)
    {
        p2 = p1;
        p1 = p1->next;
    }
    if(p1->next == NULL)
    {
        printf("没有找到学号%d的同学\n", num);
    }
    else
    {  
        if((f1 = fopen("学生-课程成绩信息.txt", "r")) == NULL) //读取表三学生的成绩
        {
            printf("error");
            exit(0);
        }
        per *p = (per*)malloc(sizeof(per));
        while(!feof(f1))
        {
            fscanf(f1, "%d  %d  %d\n", &p->num, &p->cla_num, &p->score);
            if(p->num == num)
                sum += p->score;
        }
        printf("学号%d的学生平均分是%.2f\n", num, sum/5);
        free(p);
        fclose(f1);
    }
    end = clock();
    duration = (double)(end - start)/CLOCKS_PER_SEC;
    printf("%lf seconds\n", duration);
    system("pause");
}

void free_p(stu *p)  //释放内存
{
    stu *t;
    while(p != NULL)
    {
        t = p;
        p = p->next;
        free(t);
    }
}
