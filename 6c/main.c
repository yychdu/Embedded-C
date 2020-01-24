#include <stdio.h>
#include <string.h>
void main(void)
{
    char p[20],str[20], sz[20], zm[20], qt[20];
    int i = 0, n, a, b, c;
    a = b = c = 0;
    printf("Please input string:");
    fgets(str, 20, stdin);
    printf("%s\n",str);
    n = strlen(str);
    while(i<n)
    {
        if (str[i]>='0'&&str[i]<='9')
            sz[a++] = str[i];
        else if(str[i]>='a'&&str[i]<='f'||str[i]>='A'&&str[i]<='F')
//            zm[b++] = str[i];
            {
                if(str[i]>='A'&&str[i]<='F')
                    zm[b++] = str[i]+32;
                else zm[b++] = str[i];
            }

        else
            qt[c++] = str[i];
        i++;
    }
    sz[a] = '\0';
    zm[b] = '\0';
    qt[c] = '\0';//末尾添加串结束标志；

    //puts(sz); //输出所输入的数字字符；
  //  puts(zm); //输出所输入的字母字符；

   // puts(qt); //输出所输入的其他字符

    strcat(sz,zm);
    strcpy(p,sz);
    i=0;
     while (p[i]!= '\0')
    {
        putchar(p[i]);
        i++;
        putchar(p[i]);
        putchar('  ');
        i++;
    }

    return 0;

  //  puts(sz);
}
