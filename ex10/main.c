#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
int ncount = 0;
static int callback(void *arg, int coln, char **value, char **names) {
	int i;
	if(0 == ncount) {	// 打印表头
		for (i = 0; i < coln; ++i)
			printf("%s|", names[i]);
		printf("\n");
	}
	for (i = 0; i < coln; ++i)
		printf("%s|", value[i] ? value[i] : "NULL");
	printf("\n");
	++ncount;
	return 0;
}
int main(int argc, char* argv[]) {
	int i, rc, brun = 1;
	sqlite3 *db;
	const char *create_students = "create table students(学号, 姓名, 班级)";
	const char *create_score = "create table score(学号, 实验1, 实验2, \
								实验3, 实验4, 实验5, 平时成绩, 测试成绩)";
	if(sqlite3_open("test.db", &db)) { // 打开当前路径下的test.db数据库
		printf("打开数据库失败！\n");
		exit(0);
	}
	// 判断表是否存在
	rc = sqlite3_exec(db, "select count(*) from students", 0, 0, 0);
	if (rc != SQLITE_OK)	// 没有就创建新表
		sqlite3_exec(db, create_students, 0, 0, 0);
	rc = sqlite3_exec(db, "select count(*) from score", 0, 0, 0);
	if (rc != SQLITE_OK)
		sqlite3_exec(db, create_score, 0, 0, 0);
	while (brun) {
		char buf[512], sql[512], *pos = NULL;
		printf("1 输入学生信息\t2 输入学生成绩\t3 打印学生成绩\t4 退出程序.\n");
		printf("请输入数字选择对应的操作：");	fflush(stdout);
		scanf("%d", &rc); getchar();
		switch(rc) {
			case 1:
			printf("请以英文逗号分隔输入学号、姓名和班级信息（直接输入回车返回）：\n");
				while (fgets(buf, 512, stdin)) {
				if (strcmp(buf, "\n") == 0) 	break; // 判断到空行则退出
					buf[strlen(buf) - 1] = '\0';
					i = 1;
					sprintf(sql, "insert into students values('\0");
					pos = strtok(buf, ",");
					while (pos != NULL) {
						strcat(sql, pos);
						pos = strtok(NULL, ",");
						if (NULL == pos)	break;
						strcat(sql, "','");
						++i;
					}
					strcat(sql, "')");
					if (i == 3) { // 只有三项输入才是正确格式
						if (sqlite3_exec(db, sql, 0, 0, 0) != SQLITE_OK)
							printf("保存输入信息失败！\n");
						else
							printf("输入成功！\n");
					}
					memset(buf, 0, 512);
				}
			case 2:
printf("请以英文逗号分隔输入学号、5次实验成绩、平时成绩和测试成绩（直接输入回车返回）：\n");
				while (fgets(buf, 512, stdin)) {
					if (strcmp(buf, "\n") == 0) 	break;  // 空行退出
					buf[strlen(buf) - 1] = '\0';
					i = 1;
					sprintf(sql, "insert into score values('\0");
					pos = strtok(buf, ",");
					while (pos != NULL) {
						strcat(sql, pos);
						pos = strtok(NULL, ",");
						if (NULL == pos) break;
						strcat(sql, "','");
						++i;
					}
					strcat(sql, "')");
					if (i == 8) {
						if (sqlite3_exec(db, sql, 0, 0, 0) != SQLITE_OK)
							printf("保存输入信息失败！\n");
						else
							printf("输入成功！\n");
					}
					memset(buf, 0, 512);
				}
				break;
			case 3:
				ncount = 0;
		sqlite3_exec(db,"select students.学号,students.姓名,students.班级, \
					score.实验1, score.实验2, score.实验3, score.实验4, \
					score.实验5, score.平时成绩,score.测试成绩 from students \
				inner join score on students.学号=score.学号", callback,0,0);
				break;
			case 4:
				brun = 0;
				break;
		}
	}
	sqlite3_close(db);	//关闭数据库
	return 0;
}
