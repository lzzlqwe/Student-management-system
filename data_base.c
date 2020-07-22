#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Student  //��һ��ʽ
{
    int num; //ѧ��
    char name[4]; //����
    char sex; //�Ա�
    int age; //����
    char college[10]; //Ժϵ
    struct Student *next;
} stu;
typedef struct Class    //�����ʽ
{
    int cla_num; //�γ̺�
    char cla_name[4] ; //�γ���
    char cla_pre; //���п�
    int credit; //ѧ��
} cla;
typedef struct person   //������ʽ
{
    int num; //ѧ��
    int cla_num; //�γ̺�
    int score; //�ɼ�
    struct person *next;
} per;

int n1; //��¼��һ��ѧ��������Ҳ�Ƕ�̬����Ľ�����

int main(void)
{
    stu *create(void);  //��Ӳ�̶���ԭʼѧ��������
    void free_p(stu *p);    //�ͷ��ڴ�
    stu *insert(stu *head, stu *stu_t);  //����ѧ����Ϣ
    stu *dele(stu *head, int num);    //ɾ��ѧ����Ϣ
    stu *change(stu *head, int num);  //�ı�ѧ����Ϣ
    void seek(stu *head, int num);    //Ѱ���ض���ѧ��
    int content(void);   //������ʼ����
    void save(stu *head);  //�����ļ��޸ĵ����ݣ�����Ӳ��
    void seek_aver(stu *head, int num);  //��ѯѧ��ƽ���ɼ�
    stu *p1, *head;
    int key, number; //ѡ������ĺ��룬Ҫ��ӡѧ���ĸ���
    int num_del, num_chg, num_seek; //ɾ����ѧ�ţ��޸ĵ�ѧ�ţ����ҵ�ѧ��
    p1 = head = create(); //��Ӳ�̶���ԭʼѧ�����ݣ���������̬����
    do{
        key = content(); //�����������֣�ѡ��Ҫִ�еĹ���
        switch(key)
        {
            case 0:
                save(head);
                break;
            case 1: //����һ
                printf("����Ҫ��ӡѧ������:");
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
            case 2:{ //���ܶ�
                stu *stu_new = (stu *)malloc(sizeof(stu));
                printf("����Ҫ���ѧ����ѧ��:");
                scanf("%d", &stu_new->num);
                p1 = head;
                while(p1->num != stu_new->num && p1->next != NULL) //ѧ�Ų��ع���
                {
                    p1 = p1->next;
                }
                if(p1->num == stu_new->num) //ȷ��ѧ���Ƿ��غ�
                {
                    printf("��ѧ���Ѿ����ڣ����������룡\n");
                    system("pause");
                    break;
                }
                printf("����Ҫ���ѧ��������(������3����ĸ):");
                scanf("%s", stu_new->name);
                getchar();
                printf("����Ҫ���ѧ�����Ա�(M/F):");
                scanf("%c", &stu_new->sex);
                if(stu_new->sex != 'M' && stu_new->sex != 'F') //�Ա���ż��
                {
                    printf("������Ч�Ա����������룡\n");
                    break;
                }
                printf("����Ҫ���ѧ��������:");
                scanf("%d", &stu_new->age);
                if(stu_new->age > 26 || stu_new->age < 19) //����ļ��
                {
                    printf("������ȷ�������Ƿ���ȷ��\n");
                    break;
                }
                printf("����Ҫ���ѧ����Ժϵ:");
                scanf("%s", stu_new->college);
                p1 = insert(head, stu_new);
                break;}
            case 3: //������
                printf("����Ҫɾ����ѧ��ѧ��:");
                scanf("%d", &num_del);
                p1 = dele(head, num_del);
                break;
            case 4: //������
                printf("����Ҫ�޸ĵ�ѧ��ѧ��:");
                scanf("%d", &num_chg);
                p1 = change(head, num_chg);
                break;
            case 5: //������
                printf("����Ҫ���ҵ�ѧ��ѧ��:");
                scanf("%d", &num_seek);
                seek(head, num_seek);
                break;
            case 6: //������
                printf("��ǰϵͳ¼�������:%d\n", n1);
                system("pause");
                break;
            case 7: //������
                printf("����Ҫ��ѯ��ѧ��ƽ���ɼ���ѧ��:");
                scanf("%d", &num_seek);
                seek_aver(head, num_seek);
                break;
            default: //������Ч����
                printf("û����ز���������������\n");
                system("pause");
                break;
        }
    }while(key);
    free_p(head);
    return 0;
}

int content(void)  //������ʼ����
{
    int n = 0;
    system("cls");
    printf("------------------------\n");
    printf("      ��ϵ���ݿ�\n");
    printf("------------------------\n");
    printf("��ӭ�������ϴ�ѧѧ�����ݿ⣡\n");
    printf("   1:��ӡѧ����Ϣ\n");
    printf("   2:����ѧ����Ϣ\n");
    printf("   3:ɾ��ѧ����Ϣ\n");
    printf("   4:ѧ����Ϣ�޸�\n");
    printf("   5:����ѧ����Ϣ\n");
    printf("   6:ϵͳѧ������\n");
    printf("   7:��ѧ��ƽ���ɼ�\n");
    printf("   0:������Ϣ,�˳�\n");
    printf("------------------------\n");
    printf("ѡ�����:");
    scanf("%d", &n);
    return n;
}

stu *create(void)  //��Ӳ�̶���ԭʼѧ��������
{
    stu *head, *p1, *p2;
    FILE *f1;
    if((f1 = fopen("ѧ����Ϣ.txt", "r")) == NULL)
    {
        printf("error");
        exit(0);
    }
    head = NULL;  //������̬������
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

stu *insert(stu *head, stu *stu_t) //����ѧ����Ϣ
{
    clock_t start, finish;
    double duration = 0;
    start = clock();
    stu *pt, *p1, *p2; //��̬����Ľ�����
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
    per fives[5];  //���������ѧ�����ɳɼ���׼�������ļ���
    for(int i = 0; i < 5; i++)
    {
        fives[i].num = stu_t->num;
        fives[i].cla_num = (rand() % 60 + 1) + 1000;
        fives[i].score = rand() % 60 + 40;
    }
    FILE *f1, *f2; //ͬʱ�����ļ�����ѧ���ɼ���¼
    if((f1 = fopen("ѧ��-�γ̳ɼ���Ϣ.txt", "r")) == NULL)
    {
        printf("error");
        exit(0);
    }
    if((f2 = fopen("ѧ��-�γ̳ɼ���Ϣ����.txt", "w")) == NULL)
    {
        printf("error");
        exit(0);
    }
    per *p = (per*)malloc(sizeof(per));
    int size = 0;
    while(!feof(f1))  //������ѧ�������������д���ļ�
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
    printf("�ɹ�����ѧ��Ϊ%dѧ��\n", stu_t->num);
    duration = (double)(finish - start)/CLOCKS_PER_SEC;
    printf("%f seconds\n", duration);
    system("pause");
    return head;
}

stu *dele(stu *head, int num)  //ɾ��ѧ����Ϣ
{
    clock_t start, end;
    double duration = 0;
    start = clock();
    stu *p1, *p2;  //��̬�������ɾ��
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
        printf("�ɹ�ɾ��ѧ��%d��ͬѧ\n", num);
        n1 = n1 -1;
    }
    else
    {
        printf("error");
    }
    FILE *f1, *f2; //ͬʱɾȥ�ļ�����ѧ���ɼ���¼
    if((f1 = fopen("ѧ��-�γ̳ɼ���Ϣ.txt", "r")) == NULL)
    {
        printf("error");
        exit(0);
    }
    if((f2 = fopen("ѧ��-�γ̳ɼ���Ϣ����.txt", "w")) == NULL)
    {
        printf("error");
        exit(0);
    }
    per *p = (per*)malloc(sizeof(per));
    while(!feof(f1))  //���޸ĺ������д���ļ�
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

stu *change(stu *head, int num)  //�ı�ѧ����Ϣ
{
    clock_t start, end;
    double duration = 0;
    start = clock();
    stu *p1, *p2;
    p1 = head;  //��̬������ķ���
    while(num != p1->num && p1->next != NULL)
    {
        p2 = p1;
        p1 = p1->next;
    }
    end = clock();
    duration = (double)(end - start)/CLOCKS_PER_SEC;
    if(p1->next == NULL)
    {
        printf("û���ҵ�ѧ��%d��ͬѧ\n", num);
    }
    else
    {
        int choice;
        printf("������Ҫ�޸ĵ���Ϣ(0.�˳���1.������2.�Ա�3.���䣬4.Ժϵ):");
        scanf("%d", &choice);
        getchar();
        switch (choice)  //ѡ��Ҫ�޸ĵ�����
        {
        case 1:
            printf("��������:");
            scanf("%s", p1->name);
            printf("�޸ĳɹ�\n");
            break;
        case 2:
            printf("�����Ա�:");
            scanf("%c", &p1->sex);
            printf("�޸ĳɹ�\n");
            break;
        case 3:
            printf("��������:");
            scanf("%d", &p1->age);
            printf("�޸ĳɹ�\n");
            break;
        case 4:
            printf("����Ժϵ:");
            scanf("%s", p1->college);
            printf("�޸ĳɹ�\n");
            break;
        default:
            break;
        }
    }
    printf("%lf seconds\n", duration);
    system("pause");
    return head;
}

void seek(stu *head, int num)  //Ѱ���ض���ѧ��
{
    clock_t start, end;
    double duration = 0;
    start = clock();
    stu *p1, *p2; //��̬������ķ���
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
        printf("û���ҵ�ѧ��%d��ͬѧ\n", num);
    }
    else
    {
        int choice;
        printf("������Ҫ���ҵ���Ϣ(0.�˳���1.������2.�Ա�3.���䣬4.Ժϵ��5.ȫ����Ϣ):");
        scanf("%d", &choice);
        getchar();
        switch (choice) //����Ҫ���ҵ�ѧ������
        {
        case 1:
            printf("ѧ��%dѧ��������Ϊ%s\n", num, p1->name);
            break;
        case 2:
            printf("ѧ��%dѧ�����Ա�Ϊ%c\n", num, p1->sex);
            break;
        case 3:
            printf("ѧ��%dѧ��������Ϊ%s\n", num, p1->age);
            break;
        case 4:
            printf("ѧ��%dѧ����ԺϵΪ%s\n", num, p1->college);;
            break;
        case 5:
            printf("ȫ����Ϣ:%d %s %c %d %s\n", p1->num, p1->name, p1->sex, p1->age, p1->college);
        default:
            break;
        }
    }
    printf("%lf seconds\n", duration);
    system("pause");
}

void save(stu *head)  //�����ļ��޸ĵ����ݣ�����Ӳ��
{
    FILE *f1;
    if((f1 = fopen("ѧ����Ϣ����.txt", "w")) == NULL)
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

void seek_aver(stu *head, int num) //��ѯѧ��ƽ���ɼ�
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
        printf("û���ҵ�ѧ��%d��ͬѧ\n", num);
    }
    else
    {  
        if((f1 = fopen("ѧ��-�γ̳ɼ���Ϣ.txt", "r")) == NULL) //��ȡ����ѧ���ĳɼ�
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
        printf("ѧ��%d��ѧ��ƽ������%.2f\n", num, sum/5);
        free(p);
        fclose(f1);
    }
    end = clock();
    duration = (double)(end - start)/CLOCKS_PER_SEC;
    printf("%lf seconds\n", duration);
    system("pause");
}

void free_p(stu *p)  //�ͷ��ڴ�
{
    stu *t;
    while(p != NULL)
    {
        t = p;
        p = p->next;
        free(t);
    }
}
