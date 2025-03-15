#include <iostream>
#include <vector>

// 二维图像类
class Image2D
{
  private:
    static constexpr int width = 512, height = 512;
    std::vector<std::vector<int>> img_;
    int kernel_[3][3];    
  public:
    Image2D() : img_(height, std::vector<int>(width, 0)), kernel_{} {}
    
    ~Image2D();
    // 输入流中读取二维图像坐标，初始化img_
    void InitImg();

    // 初始化kernel_为1，做均值滤波
    void SetKernel();

    // 均值滤波过程
    void MeanFilter();

    // 向输出流中输出图像
    void ShowImg();
};

Image2D::~Image2D()
{
  img_.clear();
}

void Image2D::InitImg()
{ 
  for (int i = 0;i < height;i ++) {
    for (int j = 0;j < width;j ++) {
      std::cin >> img_[i][j];
    }
  }
}

void Image2D::SetKernel()
{
  for (int i = 0;i < 3;i ++) {
    for (int j = 0;j < 3;j ++) {
      kernel_[i][j] = 1;
    }
  }
}

void Image2D::MeanFilter() {
  std::vector<std::vector<int>> tmp_img(img_);
  for (int x = 0; x < height; x++) {
      for (int y = 0; y < width; y++) {
          float avg = 0;
          int cnt = 0;
          for (int i = -1; i <= 1; i++) {
              for (int j = -1; j <= 1; j++) {
                  int u = x + i;
                  int v = y + j;
                  if (u >= 0 && u < height && v >= 0 && v < width) {
                      avg += 1.0 * tmp_img[u][v] * kernel_[i+1][j+1];
                      cnt ++;
                  }
              }
          }
          img_[x][y] = static_cast<int>(avg / cnt);
      }
  }
}

void Image2D::ShowImg()
{
  std::cout << height << " " << width << std::endl;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      std::cout << img_[i][j] << " "; 
    }
    std::cout << '\n';
  }
}


int main()
{
  Image2D img2d;
  img2d.InitImg();
  img2d.SetKernel();
  img2d.MeanFilter();
  img2d.ShowImg();

  return 0;
}
