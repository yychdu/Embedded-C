#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
unsigned short *fbmem;
int w, h;
void set_pixel(int x, int y, char r, char g, char b)
{
    r = (r % 101) * 0x1F / 100;
    g = (g % 101) * 0x3F / 100;
    b = (b % 101) * 0x1F / 100;
    fbmem[y * w + x] = (r << 11) + (g << 5) + b;
}// 屏幕打点函数，r、g、b为颜色分量，上限100，x、y为屏幕点坐标

int main()
{
    int fb, bits, i, j;
    struct fb_var_screeninfo fbv;
    fb = open("/dev/fb0", O_RDWR); // 打开设备文件fb0
    if(fb < 0)
    {
        printf("open fb0 error!\n");
        exit(0);
    }
// 获取设备信息(屏幕点阵大小、颜色位数)
    ioctl(fb, FBIOGET_VSCREENINFO, &fbv);
    w = fbv.xres;
    h = fbv.yres;
    bits = fbv.bits_per_pixel;
    printf("Framebuffer:%d * %d\n", w, h);
    printf("Bits:%d\n", bits);
    fbmem = mmap(0, w * h * bits/8, PROT_READ |
                 PROT_WRITE, MAP_SHARED, fb, 0); // 映射空间
    memset(fbmem, 0, w * h * bits / 8); // 清屏
    for (i = 0; i < 100; ++i) // 画红色正方形
        for (j = 0; j < 100; ++j)
            set_pixel(i, j, 100, 0, 0);
    return 0;
}
