#include "extract.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
  Image2D img;
  img.InitImg();
  img.ComputeOutline();
  // img.ShowPhi(1);
  img.ShowOutline(); // 输出轮廓数据
  return 0;
}