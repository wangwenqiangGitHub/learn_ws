#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int print(void * arg, int colum, char** value, char** name)
{
    int i;
    for(i = 0; i < colum; i++)
    {
        printf("%s = %s ",name[i],value[i]);
    }
    printf("\n");
    return 0;
}
int main()
{
    //打开或者创建数据库
    sqlite3 *ppdb;
    int ret = sqlite3_open("student.db", &ppdb);
    if(ret != SQLITE_OK)
    {
        printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb));
        exit(1);
    }
    //创建表
    char sql[128] = {0};
    sprintf(sql,"create table if not exists student (id integer, name text, age integer);");
    ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
    if(ret != SQLITE_OK)
    {
        printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb));
        exit(1);
    }
    //插入数据
    int id, age, i;
    char name[32] = {0};
    for(i= 0; i< 2; i++)
    {
        printf("请输入学号，姓名，年龄\n");
        scanf("%d%s%d", &id,name,&age);
        sprintf(sql,"insert into student values(%d, %s, %d)",id,name,age);
        ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
        if(ret != SQLITE_OK)
        {
            printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb));
            exit(1);
        }
    }

    memset(sql, 0, sizeof(sql));
    sprintf(sql,"select * from student;");
    ret = sqlite3_exec(ppdb, sql, print, NULL,NULL);
    if(ret != SQLITE_OK)
    {
        printf("sqlite3_exec22:%s\n",sqlite3_errmsg(ppdb));
        exit(1);
    }
    /*
     char **result;
     int row, colum;
     ret = sqlite3_get_table(ppdb, sql, &result, &row, &colum, NULL);
     if(ret != SQLITE_OK)
     {
        printf("sqlite3_get_table: %s\n", sqlite3_errmsg(ppdb));
        exit(1);
     }

     int j;
     int index = colum;
     for(i= 0; i<row; i++)
     {
        for(j = 0; j< colum; j++)
        {
            printf("%s = %s", result[j], result[index]);
            index++;
            printf("\n");
        }
     }
     * */
    return 0;
}
