#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

class Image2D
{
public:
  Image2D() : img_(height, std::vector<int>(width, 0)), outline_(height, std::vector<int>(width, 0)), kernel_{}, f_(height, std::vector<double>(width, 0)), phi_(height, std::vector<double>(width, 0)), Gx_(height, std::vector<int>(width, 0)), Gy_(height, std::vector<int>(width, 0)), T_(30), A_(M_PI / 6)
  {
  }

  Image2D(double T, double A) : img_(height, std::vector<int>(width, 0)), outline_(height, std::vector<int>(width, 0)), kernel_{}, f_(height, std::vector<double>(width, 0)), phi_(height, std::vector<double>(width, 0)), Gx_(height, std::vector<int>(width, 0)), Gy_(height, std::vector<int>(width, 0)), T_(T), A_(A)
  {
  }
  ~Image2D();

  // 输入流中读取二维图像坐标，初始化img_
  void InitImg();

  // 初始化kernel_
  void SetKernel();

  // 均值滤波过程
  void MeanFilter();

  // 向输出流中输出图像
  void ShowImg();

  // 显示梯度幅值图
  void ShowF();

  // 显示方向角图
  // op = 1 显示方向角图
  // op = 2 显示水平梯度图
  // op = 3 显示垂直梯度图
  void ShowPhi(int op);

  // 计算梯度
  void ComputeGrad();

  // 计算梯度幅值
  void ComputeF();

  // 计算方向角
  void ComputePhi();

  // 计算轮廓
  void ComputeOutline();

  // 显示轮廓
  void ShowOutline();

private:
  static constexpr int width = 512, height = 512;
  int kernel_[3][3];
  double T_, A_;                                // 幅度阈值和角度阈值
  std::vector<std::vector<int>> img_, outline_; // 图像和轮廓
  std::vector<std::vector<int>> Gx_, Gy_;       // 梯度
  std::vector<std::vector<double>> f_;          // 梯度幅值
  std::vector<std::vector<double>> phi_;        // 角度
  std::vector<std::vector<int>> sobel_x = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  std::vector<std::vector<int>> sobel_y = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
};
