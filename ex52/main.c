#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE *fp = fopen("4011.txt" , "r");
   if (fp)
   {
      int i, sel = 0;
      char buf[1024];
      double vstart[18], vend[18] , td;
      int time_sec, time_start=999 , time_end=0;
      while (fgets(buf ,1024 , fp))
      {
         char str[128];
         char *pb = buf;
         int len = strlen(buf);
         int idx = 0;

         while (pb< buf + len && sscanf(pb ,"%s"  , str))
         {
            while( *pb && *pb != ' ' && *pb!= '\t')
                ++pb;
            while( *pb == ' ' || *pb == '\t')
                ++pb;
            printf("%s\n", str);
                ++idx;

            if (2 == idx )
            {
               int step = atoi(str);
               if (step != 2)
               break;
            }
            if (4 == idx)
            {
               int hh = atoi(str);
               int mm = atoi(str + 3);
               int ss = atoi(str + 6);
               time_sec = hh * 3600 + mm * 60 + ss;
               if(time_sec>1200)
               break;
               if (time_sec < time_start)
               {
                  time_start=time_sec;
               }
               if (time_sec>time_end)
               {
                  time_end=time_sec;
               }
            }
            if (idx >= 11 && idx < 29)
            {
               if (time_sec == time_start)
                  vstart[idx-11] = atof (str);
                  else if (time_sec == time_end)
                  vend[idx - 11] = atof (str);
            }
         }
      }

      printf("time : %d\n", time_end - time_start);
      td = vstart[0] - vend[0];
      for(i=0;i<18;i++)
      {
        double tt = vstart[i] - vend[i];
        if(tt < td)
         {
            td = tt;
            sel = i;
         }
         printf("No. %d : %.3f - %.3f ,  dv = %.3f\n", i+1, vstart[i], vend[i], tt);
      }
      printf("slow bettery : No. %d  ,  speed : %.3f mVc\n",sel+1 , 1000*td/(time_end - time_start));
      fclose (fp);
   }
    return 0;
}
