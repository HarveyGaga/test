/*************************************************************************
	> File Name: test.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年04月24日 星期一 09时51分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sqlite3.h>

#define DATABASE_NAME		"database.db"

void AppExit(void)
{
	printf("App exit.\n");
}

void Db_CreateTable(sqlite3 *db)
{
	
}

int main(void)
{
	sqlite3 *db = NULL;
	int ret;
	char *zErrMsg;
	char *sql = NULL;

	atexit(AppExit);

	/* open database */
	ret = sqlite3_open(DATABASE_NAME, &db);
	printf("ret = %d\n", ret);
	if(ret)
	{
		printf("Can't open %s database.\n ", DATABASE_NAME);
		exit(1);
	}

	printf("Open %s database suceess.\n", DATABASE_NAME);

	Db_CreateTable(db);

	sqlite3_close(db);

	fprintf(stdout, "close database.\n");

	exit(0);
}
