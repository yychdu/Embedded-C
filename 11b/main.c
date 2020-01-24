#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
int i=0;p=0;
int get_file_lines(const char *filename){
    int nlines=0;
    char buf[1024];
    FILE *fp = fopen(filename,"r");
    if(fp)
   {
    while(fgets(buf,1024,fp))
    ++nlines;
    ++nlines;

    fclose(fp);
   }
    return nlines;
}

static int get_file_size_time(const char *filename)
{
    struct stat statbuf;
    if (stat(filename, &statbuf) == -1) {
    i--;
        printf("Get stat on %s Error：%s\n",
filename, strerror(errno));
        return (2);
    }
    if (S_ISDIR(statbuf.st_mode))
       return (1);
    if (S_ISREG(statbuf.st_mode))
      {
      int len = strlen(filename) ;
      if (len > 5 && filename[len-1]=='f' && filename[len-2]=='n'&&filename[len-3]=='o'&&filename[len-4]=='c'&&filename[len-5]=='.')
      { int lines = get_file_lines(filename);
            i++;
            p+=lines;

            char *pname = filename + len -1;
      while (pname>filename && *pname != '/')
         --pname;
         if (pname!=filename)
         ++pname;
        // printf("%-20s has %d lines.file size:%d.file time:%d.\n",pname,lines,size,time);
        printf ("%s size：%ld bytes\tmodified at %s",
        filename, statbuf.st_size, ctime (&statbuf.st_mtime));

      }

    }
    return (0);
}
int main(int argc, char **argv) {
    DIR *dirp;	struct dirent *direntp;
    int stats;	char buf[80];
    if (argc != 2) {
        printf("Usage：%s filename\n\a", argv[0]);
        exit(1);
    }
    if (((stats = get_file_size_time(argv[1])) == 0) || (stats == -1))
        exit(1);
    if ((dirp = opendir(argv[1])) == NULL) {

        printf("Open Directory %s Error：%s\n", argv[1], strerror(errno));
        exit(1);
    }
    while ((direntp = readdir(dirp)) != NULL){
        sprintf(buf,"%s/%s",argv[1],direntp->d_name);
        if (get_file_size_time(buf) == -1) break;
    }

    closedir(dirp);
    printf("totally %d files,totally %d lines",i,p);
    exit(1);
}

