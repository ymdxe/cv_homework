#include "extract.h"

Image2D::~Image2D()
{
  img_.clear();
  Gx_.clear();
  Gy_.clear();
  f_.clear();
  phi_.clear();
}

void Image2D::InitImg()
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      std::cin >> img_[i][j];
    }
  }
}

void Image2D::SetKernel()
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      kernel_[i][j] = 1;
    }
  }
}

void Image2D::MeanFilter()
{
  std::vector<std::vector<int>> tmp_img(img_);
  for (int x = 0; x < height; x++)
  {
    for (int y = 0; y < width; y++)
    {
      float avg = 0;
      int cnt = 0;
      for (int i = -1; i <= 1; i++)
      {
        for (int j = -1; j <= 1; j++)
        {
          int u = x + i;
          int v = y + j;
          if (u >= 0 && u < height && v >= 0 && v < width)
          {
            avg += 1.0 * tmp_img[u][v] * kernel_[i + 1][j + 1];
            cnt++;
          }
        }
      }
      img_[x][y] = static_cast<int>(avg / cnt);
    }
  }
}

void Image2D::ShowImg()
{
  std::cout << height << " " << width << '\n';

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      std::cout << img_[i][j] << " ";
    }
    std::cout << '\n';
  }
}

void Image2D::ShowF()
{
  std::cout << height << " " << width << '\n';
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      std::cout << f_[i][j] << " ";
    }
    std::cout << '\n';
  }
}

void Image2D::ShowPhi(int op)
{
  std::cout << height << " " << width << '\n';
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (op == 1)
      {
        // 将角度归一化到 0-255 范围
        double normalized_phi = ((phi_[i][j] + M_PI) / (2 * M_PI)) * 255;
        std::cout << static_cast<int>(normalized_phi) << " ";
      }
      else if (op == 2)
      {
        std::cout << Gx_[i][j] << " ";
      }
      else if (op == 3)
      {
        std::cout << Gy_[i][j] << " ";
      }
    }
    std::cout << '\n';
  }
}

void Image2D::ComputeGrad()
{
  for (int x = 0; x < height; x++)
  {
    for (int y = 0; y < width; y++)
    {
      int Gx = 0, Gy = 0;
      for (int i = -1; i <= 1; i++)
      {
        for (int j = -1; j <= 1; j++)
        {
          int u = x + i, v = y + j;
          if (u >= 0 && u < height && v >= 0 && v < width)
          {
            Gx += img_[u][v] * sobel_x[i + 1][j + 1];
            Gy += img_[u][v] * sobel_y[i + 1][j + 1];
          }
        }
      }
      Gx_[x][y] = Gx;
      Gy_[x][y] = Gy;
    }
  }
}

void Image2D::ComputeF()
{
  for (int x = 0; x < height; x++)
  {
    for (int y = 0; y < width; y++)
    {
      f_[x][y] = std::hypot(Gx_[x][y], Gy_[x][y]);
      if (f_[x][y] > 130)
      {
        f_[x][y] = 255;
      }
      else
      {
        f_[x][y] = 0;
      }
    }
  }
}

void Image2D::ComputePhi()
{
  for (int x = 0; x < height; x++)
  {
    for (int y = 0; y < width; y++)
    {
      phi_[x][y] = std::atan2(Gy_[x][y], Gx_[x][y]);
    }
  }
}

void Image2D::ComputeOutline()
{

  this->ComputeGrad();
  this->ComputeF();
  this->ComputePhi();

  std::queue<std::pair<int, int>> q;
  std::vector<std::vector<bool>> vis(height, std::vector<bool>(width, false));

  for (int x = 0; x < height; x++)
  {
    for (int y = 0; y < width; y++)
    {
      if (!vis[x][y])
      {
        vis[x][y] = true;
        q.push({x, y});
        while (q.size())
        {
          auto t = q.front();
          q.pop();
          int u = t.first, v = t.second;
          for (int i = -1; i <= 1; i++)
          {
            for (int j = -1; j <= 1; j++)
            {
              int s = u + i, t = v + j;
              if (s >= 0 && s < height && t >= 0 && t < width && !vis[s][t])
              {
                if (fabs(f_[x][y] - f_[s][t]) <= T_ && fabs(phi_[x][y] - phi_[s][t]) <= A_)
                {
                  vis[s][t] = true;
                  q.push({s, t});
                  outline_[s][t] = f_[x][y];
                }
              }
            }
          }
        }
      }
    }
  }
}

void Image2D::ShowOutline()
{
  std::cout << height << " " << width << '\n';
  for (int i = 0; i < height; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      std::cout << outline_[i][j] << " ";
    }
    std::cout << '\n';
  }
  // this->ShowF();
  // this->ShowPhi(1);
  // this->ShowPhi(2);
  // this->ShowPhi(3);
}
