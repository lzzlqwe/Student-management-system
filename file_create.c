#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int arr[4000];
int main(void)
{
    FILE *f1; //生成表一
    if((f1 = fopen("学生信息.txt", "w")) == NULL)
    {
        printf("read error!");
        exit(0);
    }
    int tmp = 0, i = 0, k, age;
    char a, b, c; //名字的三个字母
    char sex; //性别
    char str[4];
    char *college[5] = {"science", "geography", "biology", "aviation", "math"}; //院系名
    srand(time(NULL));  //随机数种子
    while(i < 4000)  //生成1200名学生
    {
        tmp += rand() % 2 + 1;
        arr[i] = tmp;
        a = rand() % 26 + 65; //26个大写字母
        b = rand() % 26 + 65;
        c = rand() % 26 + 65;
        str[0] = a; str[1] = b; str[2] = c; str[4] = '\0';
        age = rand() % 8 + 19; //年龄19~26
        fprintf(f1, "%d  %s  %c  %d  %s\n", tmp + 2000, str, "MF"[tmp%2], age, college[tmp%5]);
        i++;
    }
    fclose(f1);
    FILE *f2; //生成表二
    if((f2 = fopen("课程信息.txt", "w")) == NULL)
    {
        printf("read error!");
        exit(0);
    }
    tmp = 0; i = 0;
    while(i < 60)
    {
        tmp++;
        str[0] = rand() % 26 + 97;
        str[1] = rand() % 26 + 97;
        str[2] = '\0';
        fprintf(f2, "%d  %s  %c  %d\n", tmp+1000, str, rand()%26+65 , rand()%5+1);
        i++;
    }
    fclose(f2);
    FILE *f3; //生成表三
    if((f3 = fopen("学生-课程成绩信息.txt", "w")) == NULL)
    {
        printf("read error!");
        exit(0);
    }   
    int x;//课程号
    for(i = 0; i < 4000; i++)
    {
        x = rand() % 60 + 1;
        if(x >= 42)
            x -= (rand()%7 + 1);
        for(k = 0; k < 5; k++)
        {
            x = x + rand() % 2 + 1;
            fprintf(f3, "%d  %d  %d\n", arr[i]+2000, x+1000, rand()%60+40);
        }
    }
    fclose(f3);
    return 0;
}