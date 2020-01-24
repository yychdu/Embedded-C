#include <stdio.h>
#include <errno.h>
#include<string.h>
#include <sys/types.h>
 #include <sys/stat.h>
  #include <dirent.h>
  #include <time.h>
#include<stdlib.h>


void pri(char *a)
{
   FILE *fp;
   fp=fopen(a,"r");
   if(fp)
    {
    char ch;
    while((ch=fgetc(fp))!=EOF)
    putchar(ch);
    fclose(fp);
    }
    else printf("无文件!");
}

void co(char *o,char *sou)
{
        FILE *fp1 = fopen(sou,"rb");
        FILE *fp2 =fopen(o,"wb");
       if( fp1 == NULL ||fp2 == NULL)
          printf("ERROR !");
          return;

          int* data;
          data = (int *)malloc(sizeof(int));
          while(!feof(fp1))
          {
             fread(&data,sizeof(int),1,fp1);
             fwrite(&data,sizeof(int),1,fp2);
          }
          return;
}
void get_updir(char *current_dir)
{
         int lenth = strlen(current_dir);                                                                                                                           
                        for (;lenth > 0 ; --lenth)
                             if(current_dir[lenth] =='/')
                                break;
          strcpy(current_dir + lenth,"" );
          return;
}


char * get_subdir(char *current_dir)
{
       char *subdir;
        subdir=(char *)malloc(128);
         int lenth = strlen(current_dir);                                                                                                                                    
                        for (;lenth > 0 ; --lenth)
                             if(current_dir[lenth] =='/')
                                break;
          strcpy(subdir,current_dir + lenth);                                                                                                                     
          return subdir;
}

static int get_file_size_time(const char *filename)
{
    struct stat statbuf;
    int lenth = strlen(filename);
    int i;
    char strbuf[80];
    stat(filename, &statbuf) ;
    for(i = lenth; i > 0 ; i--)
         if(filename[i] == '/') break;
    strcpy(strbuf,filename+i+1);
    if (S_ISDIR(statbuf.st_mode))
    {
          if(strcmp(strbuf,".")!= 0)
          {
          printf("[%s] \t  %ld bytes\t %s",strbuf,statbuf.st_size, ctime(&statbuf.st_mtime));
          }
           return 1;
    }
            if (S_ISREG(statbuf.st_mode))
            {
                if((filename[lenth-2] == '.')&&(filename[lenth-1] == 'c' ||filename[lenth-1] =='h'))
                {
                printf("%s \t  %ld bytes\t %s",  strbuf, statbuf.st_size, ctime(&statbuf.st_mtime));
                return (0);
                }
            }
}




int main(int argc, char **argv)
 {
    DIR *dirp;
    struct dirent *direntp;
    char buf[80];
    char input[80];
    char current_dir[80];
   getcwd(current_dir , 1024);
    while(1)
    {
          if( (dirp = opendir(current_dir) )== NULL)
            {
               int leng = strlen (current_dir);
                if(current_dir[leng-2] == '.'&&(current_dir[leng-1] =='c' || current_dir[leng-1] =='h')) 
                {
                      pri(current_dir);
                      printf("文件操作：[1]    复制文件到指定路径\n[2]  剪切文件到指定路径\n[3]  删除文件\n[..]  返回上层目录");
                      strcpy(buf,"");
                      scanf("%s",buf);

                      if(strcmp(buf,"..") == 0)
                      {
                          get_updir(current_dir);
                      }

                     else   if(strcmp(buf,"1") == 0)
                                {
                                    printf("输入路径:\n");
                                    scanf("%s",buf);
                                    strcat(buf,get_subdir(current_dir));
                                    co(buf,current_dir);
                                }
                                else   if(strcmp(buf,"2") == 0)
                                            {
                                                printf("输入路径:\n");
                                                scanf("%s",buf);
                                                strcat(buf,get_subdir(current_dir));
                                                co(buf,current_dir);
                                                remove(current_dir);
                                                get_updir(current_dir);
                                            }
                                            else if(strcmp(buf,"3")==0)
                                                        {
                                                            remove(current_dir);
                                                            get_updir(current_dir);
                                                        }

                      }
                    else
                    {
                        printf("错误格式！\n");
                        exit(1);
                    }
               }

           else
            {
                 printf("当前路径:  %s\n" , current_dir);
                 printf("名称 \t    大小\t                 时间\n");
                while ((direntp = readdir(dirp)) != NULL)
                {

                            sprintf(buf,"%s/%s",current_dir,direntp->d_name);
                            get_file_size_time(buf) ;
                }
                closedir(dirp);
               printf("目录操作：[..]-- 返回上级目录\n[文件夹名]-- 打开文件夹\n[.c.h文件名]（带后缀）--打开.c.h文件\n");
                scanf("%s",input);
               if(strcmp(input,"exit") == 0)                                                              
                  break;
                        if(strcmp(input,"..") == 0)                                                               
                        {
                             get_updir(current_dir);
                             if(strlen(current_dir) <= 1)
                             {
                                  strcpy(current_dir,"/");
                             }

                        }

                        else                                                                              
                           strcat(current_dir,"/");
                           strcat(current_dir,input);
                        }
           }
    }
}

