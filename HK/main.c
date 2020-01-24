#include <stdio.h>
#include <string.h>
#include <iconv.h>

#define DRAW_CHAR '*'
#define HZK16 "HZK16"
#define ASC16 "ASC16"
#define GBK16 "GBK16"

int pattern;                                                //全局变量pattern用来表明现在用的是哪种字库 0--HZK 1--GBK


/*
   Name:code_convert
   Function:编码转换
   Input:原来的编码类型，要转换的编码类型，输入字符数组，字符串长度，输出字符数组，缓冲区长度
   output:正常输出0 错误输出1
*/
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
{
   iconv_t cd;
   int rc;
   char **pin = &inbuf;
   char **pout = &outbuf;

   cd = iconv_open(to_charset,from_charset);
   if (cd==0)
   {
         printf("转换失败！");
         return -1;
   }
   memset(outbuf,0,outlen);
   if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
   iconv_close(cd);
   return 0;
}
 /*
   Name:u2g
   Function:UTF8转GB2312码
   Input:输入字符数组，字符串长度，输出字符数组，缓冲区长度
   output:正常输出0 错误输出1
*/
int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
{
   return code_convert("utf-8","gbk//translit",inbuf,inlen,outbuf,outlen);
}

 /*
   Name:get_CC_offset
   Function:计算偏移量
   Input:字符
   output:偏移量
*/
int get_CC_offset(char *s)
{
     unsigned char part_code = s[0] ;    //区码
    unsigned char site_code = s[1];        //位码
	printf("区码%d,位码%d\n",part_code,site_code);
     if(!pattern)
          return (94 * (part_code - 1-0xa0) + (site_code - 1-0xa0)) * 32;


             return (191* (part_code -0x81) + (site_code-0x40)) * 32;


}
 /*
   Name:is_set_bit
   Function:判断这一位是否是星号
   Input:偏移量表的地址，偏移的位数
   output:是星号输出1，不是输出0
*/
int is_set_bit(char *s, int off)
{
    return *(s + off / 8) & (0x80 >> (off % 8));
}
/*
   Name:print_line_n_CC
   Function:打印有n个汉字的一行
   Input:要打印的字符数组，一行的字符个数
   output:无
*/
void print_line_n_CC(char *s, int n)
{
    if(!s ||( n * 2 > strlen(s)) || n > 4)       //如果字符数组为空，或者字符数组内汉字数量不够，或者一行超过四个；返回
        return;

    int offset = 0;
    int i = 0, j = 0, k = 0;
    char **code_table = NULL;
    char buf1[16],buf2[16];

    FILE *fp ;
    FILE *fp_asc = fopen(ASC16, "rb");          //打开ASC16
    if(!pattern)
      fp= fopen(HZK16, "rb");                        //如果pattern是0 打开HZK16
    else
        fp= fopen(GBK16, "rb");                     //如果pattern是1 打开GBK16

    if(!fp || !fp_asc)                                      //打开文件失败
    {
        printf("font is absent!\n");
        return;
    }

    code_table = (char **)malloc(n * sizeof(char *));                                     //n个汉字 每个汉字对应一个有32个char型变量的数组 用于存放汉字的编码
    for(i = 0; i < n; i++)
        code_table[i] = (char *)malloc(32);                                                                //构造n*32的表格

    // 计算偏移，得到该汉字的码表
    for(i = 0; i < n; i++)
    {
        if((*(s+i*2)&0x80))                                                                                               //如果是汉字
        {
            offset = get_CC_offset(s + i * 2);                                                                      //获取偏移位置
            fseek(fp, offset, SEEK_SET);
            fread(code_table[i], 32, 1, fp);                                                                        //获取对应字的编码
        }
        else          //如果是ASCII码
        {
              offset=16**(s+i*2);                     //偏移量为值*16          读取第一个字节的编码
              fseek(fp_asc, offset, SEEK_SET);
              fread(buf1, 16, 1, fp_asc);
              offset=16**(s+i*2+1);                //读取第二个字节的编码
              fseek(fp_asc, offset, SEEK_SET);
              fread(buf2, 16, 1, fp_asc);
              for(k=0;k<32;k++)                    //交叉填入编码表
              {
                   if(k % 2 == 0)
                   code_table[i][k]=buf1[k/2];
                   else
                   code_table[i][k]=buf2[k/2];
              }
        }
    }
    fclose(fp);
    fclose(fp_asc);

    for(i = 0; i < 16; i++)
    {
        for(j = 0; j < n * 16; j++)
        {
            if(j != 0 && j % 16 == 0)
                printf("    ");

            if(is_set_bit(code_table[j / 16], i * 16 + j % 16 - 16))
                printf("%c", DRAW_CHAR);
            else
                printf(" ");

        }
        printf("\n");
    }
    printf("\n");

    for(i = 0; i < n; i++)       //释放链表
        free(code_table[i]);
    free(code_table);
}


/*
   Name:print_CC
   Function:打印全部汉字
   Input:要打印的字符数组，一行最大的字符个数
   output:无
*/
void print_CC(char *s, int line_max_char)                              //分行打印
{
    if(!s)
        return;

    if(line_max_char > 4)   //如果行最大字数大于4 返回
    {
        printf("line max print 4 chinese charcter\n");
        return;

    }
    int i = 0;
    int len = strlen(s);
    int max_len = 0;

    for(i = 0; i < len; i = i + 2 * line_max_char)    //计算所需行数 并逐行打印
    {
        if( i + line_max_char * 2 > len)
            max_len = (len - i) / 2;
        else
            max_len = line_max_char;

        print_line_n_CC(s + i, max_len);
    }
}

int main(int argc, char const *argv[])
{
    char incode[81];
    char outcode[81];
    char buf[1024];
    pattern = 0;
    printf("请选择编码方式：\n 0--HZK \n 1--GBK\n");
    scanf("%s",buf);
    if(strcmp(buf,"0") == 0)
    {
           pattern = 0;
    }
    else  if(strcmp(buf,"1") == 0)
    {
           pattern =1;
    }
    else
    {
        printf("无效！\n");
        exit(0);
    }
  //  printf("%d",pattern);
    printf("请输入字符:\n");
   scanf("%s",incode);
  // printf("%c %c",incode[0],incode[1]);
 if(u2g(incode,strlen(incode),outcode,255))
        printf("格式转换错误");
  // printf("%s",outcode);
    print_CC(outcode, 4);
    return 0;
}

