#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
int ncount = 0;
static int callback(void *arg, int coln, char **value, char **names) {
	int i;
	if(0 == ncount) {	// ��ӡ��ͷ
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
	const char *create_students = "create table students(ѧ��, ����, �༶)";
	const char *create_score = "create table score(ѧ��, ʵ��1, ʵ��2, \
								ʵ��3, ʵ��4, ʵ��5, ƽʱ�ɼ�, ���Գɼ�)";
	if(sqlite3_open("test.db", &db)) { // �򿪵�ǰ·���µ�test.db���ݿ�
		printf("�����ݿ�ʧ�ܣ�\n");
		exit(0);
	}
	// �жϱ��Ƿ����
	rc = sqlite3_exec(db, "select count(*) from students", 0, 0, 0);
	if (rc != SQLITE_OK)	// û�оʹ����±�
		sqlite3_exec(db, create_students, 0, 0, 0);
	rc = sqlite3_exec(db, "select count(*) from score", 0, 0, 0);
	if (rc != SQLITE_OK)
		sqlite3_exec(db, create_score, 0, 0, 0);
	while (brun) {
		char buf[512], sql[512], *pos = NULL;
		printf("1 ����ѧ����Ϣ\t2 ����ѧ���ɼ�\t3 ��ӡѧ���ɼ�\t4 �˳�����.\n");
		printf("����������ѡ���Ӧ�Ĳ�����");	fflush(stdout);
		scanf("%d", &rc); getchar();
		switch(rc) {
			case 1:
			printf("����Ӣ�Ķ��ŷָ�����ѧ�š������Ͱ༶��Ϣ��ֱ������س����أ���\n");
				while (fgets(buf, 512, stdin)) {
				if (strcmp(buf, "\n") == 0) 	break; // �жϵ��������˳�
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
					if (i == 3) { // ֻ���������������ȷ��ʽ
						if (sqlite3_exec(db, sql, 0, 0, 0) != SQLITE_OK)
							printf("����������Ϣʧ�ܣ�\n");
						else
							printf("����ɹ���\n");
					}
					memset(buf, 0, 512);
				}
			case 2:
printf("����Ӣ�Ķ��ŷָ�����ѧ�š�5��ʵ��ɼ���ƽʱ�ɼ��Ͳ��Գɼ���ֱ������س����أ���\n");
				while (fgets(buf, 512, stdin)) {
					if (strcmp(buf, "\n") == 0) 	break;  // �����˳�
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
							printf("����������Ϣʧ�ܣ�\n");
						else
							printf("����ɹ���\n");
					}
					memset(buf, 0, 512);
				}
				break;
			case 3:
				ncount = 0;
		sqlite3_exec(db,"select students.ѧ��,students.����,students.�༶, \
					score.ʵ��1, score.ʵ��2, score.ʵ��3, score.ʵ��4, \
					score.ʵ��5, score.ƽʱ�ɼ�,score.���Գɼ� from students \
				inner join score on students.ѧ��=score.ѧ��", callback,0,0);
				break;
			case 4:
				brun = 0;
				break;
		}
	}
	sqlite3_close(db);	//�ر����ݿ�
	return 0;
}
