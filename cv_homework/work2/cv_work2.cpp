#include <iostream>
#include <vector>

class Image3D {
  private:
      static constexpr int width = 512, height = 512, depth = 200;
      std::vector<std::vector<std::vector<int>>> img_;
      int kernel_[3][3][3];
  
  public:
    Image3D() : img_(height, std::vector<std::vector<int>>(width, std::vector<int>(depth, 0))),
                  kernel_{} {}

    ~Image3D();

    // 输入流中读取三维图像坐标，初始化img_
    void InitImg();

    // 初始化kernel_为-5，效果更明显些
    void SetKernel();

    // 遍历过程
    void Filter();

    // 向输出流中输出图像
    void ShowImg();
};

Image3D::~Image3D()
{
  img_.clear();
}

void Image3D::InitImg()
{ 
  for (int i = 0;i < height;i ++) {
    for (int j = 0;j < width;j ++) {
      for (int k = 0;k < depth;k ++) {
        std::cin >> img_[i][j][k];
      }
    }
  }
}

void Image3D::SetKernel()
{
  for (int i = 0;i < 3;i ++) {
    for (int j = 0;j < 3;j ++) {
      for (int k = 0;k < 3;k ++) {
        kernel_[i][j][k] = -5;
      }
    }
  }
}

void Image3D::Filter() {
  std::vector<std::vector<std::vector<int>>> tmp_img(img_);

  for (int x = 0; x < height; x++) {
      for (int y = 0; y < width; y++) {
          for (int z = 0; z < depth; z++) {
              float avg = 0;
              int cnt = 0;
              for (int i = -1; i <= 1; i++) {
                  for (int j = -1; j <= 1; j++) {
                      for (int k = -1; k <= 1; k++) {
                          int u = x + i;
                          int v = y + j;
                          int w = z + k;
                          if (u >= 0 && u < height && v >= 0 && v < width && w >= 0 && w < depth) {
                              avg += 1.0 * tmp_img[u][v][w] * kernel_[i+1][j+1][k+1];
                              cnt ++;
                          }
                      }
                  }
              }
              img_[x][y][z] = static_cast<int>(avg / cnt);
          }
      }
  }
}

void Image3D::ShowImg()
{
  std::cout << height << " " << width << " " << depth << std::endl;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      for (int k = 0; k < depth; k++) {
        std::cout << img_[i][j][k] << " "; 
      }
      std::cout << '\n';
    }
  }
}

int main()
{
  Image3D img;
  img.InitImg();
  img.SetKernel();
  img.Filter();
  img.ShowImg();
  return 0;
}
