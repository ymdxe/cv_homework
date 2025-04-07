#include "image.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
  Image2D img;
  img.InitImg();  // 初始化图像
  img.SaveBox("box.txt");  // 保存最大外接矩形
  img.SaveHull("hull.txt");  // 保存凸包
  img.SaveMinBox("minbox.txt");  // 保存最小包围盒
  return 0;
}