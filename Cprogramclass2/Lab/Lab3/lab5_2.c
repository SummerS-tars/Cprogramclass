#include <stdio.h>
#include <string.h>

int main()
{
    char job_1[20] ="自由职业", job_2[20] = "白领", job_3[20] = "工人";
    char job[20];
    scanf("%s", job);

    int age, salary;
    char degree_1[20] = "初中", degree_2[20] = "小学";
    char degree[20];

    if (strcmp(job, job_1) == 0)
    {
        scanf("%d", &age);
        if (age > 25)
            printf("有贷款意向\n");
        else
            printf("无贷款意向\n");
    }
    else if (strcmp(job,job_2)==0)
    {
        scanf("%d", &age);
        if (age > 35)
        {
            printf("有贷款意向\n");
            return 0;
        }
        scanf("%d", &salary);
        if (salary < 10000)
            printf("无贷款意向\n");
        else
            printf("有贷款意向\n");
    }
    else
    {
        scanf("%d", &age);
        if (age > 40)
        {
            printf("无贷款意向\n");
            return 0;
        }
        scanf("%s", degree);
        if (strcmp(degree, degree_1) == 0)
            printf("有贷款意向\n");
        else
            printf("无贷款意向\n");
    }
    return 0;
}
