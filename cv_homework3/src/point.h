#include <vector>
#include <algorithm>
#include <cmath>

struct Point {
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  Point operator - (const Point& p) const { return {x - p.x, y - p.y}; }
  Point operator + (const Point& p) const { return {x + p.x, y + p.y}; }
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  bool operator < (const Point& p) const { return x < p.x || (x == p.x && y < p.y); }
  bool operator == (const Point& p) const { return x == p.x && y == p.y; }
};

class Geometry {
public:

  // 计算外接盒
  static std::vector<Point> BoundingBox(const std::vector<Point>& pts) {
    if (pts.empty()) return {};
    double min_x = pts[0].x, max_x = pts[0].x;
    double min_y = pts[0].y, max_y = pts[0].y;
    
    for (const auto& p : pts) {
      if (p.x < min_x) min_x = p.x;
      if (p.x > max_x) max_x = p.x;
      if (p.y < min_y) min_y = p.y;
      if (p.y > max_y) max_y = p.y;
    }
    
    return {Point(min_x, min_y), Point(max_x, min_y), Point(max_x, max_y), Point(min_x, max_y)};
  }

  // 计算凸包 (Andrew算法)
  static std::vector<Point> ConvexHull(std::vector<Point> pts) {
      if (pts.size() <= 1) return pts;
      
      sort(pts.begin(), pts.end());
      auto it = unique(pts.begin(), pts.end());
      pts.erase(it, pts.end());
      
      int n = pts.size(), k = 0;
      std::vector<Point> hull(n*2);
      
      // 下凸壳
      for (int i = 0; i < n; hull[k++] = pts[i++]) 
          while (k >= 2 && cross(hull[k-2], hull[k-1], pts[i]) <= 0) k--;
      
      // 上凸壳
      for (int i = n-2, t = k+1; i >= 0; hull[k++] = pts[i--])
          while (k >= t && cross(hull[k-2], hull[k-1], pts[i]) <= 0) k--;
      
      hull.resize(k - (n > 1));
      return hull;
  }

  struct Box {
      double area;
      std::vector<Point> pts;
  };

  // 计算最小包围盒 (旋转卡壳法)
  static Box MinBox(const std::vector<Point>& hull) {
    if (hull.empty()) return {0, {}};
    if (hull.size() == 1) return {0, {hull[0], hull[0], hull[0], hull[0]}};

    double min_area = INFINITY;
    std::vector<Point> best;
    int n = hull.size();

    for (int i = 0, j = 1; i < n; ++i) {
      Point a = hull[i], b = hull[(i + 1) % n];
      Point vec = b - a;
      double base = sqrt(vec.x * vec.x + vec.y * vec.y);
      
      // 计算当前边方向
      double dx = vec.x / base, dy = vec.y / base;
      
      // 收集极值投影
      double min_x = 0, max_x = 0, max_y = 0;
      for (int k = 0; k < n; ++k) {
        Point v = hull[k] - a;
        double proj = v.x * dx + v.y * dy;
        double perp = v.x * (-dy) + v.y * dx;
        
        if (k == 0 || proj < min_x) min_x = proj;
        if (k == 0 || proj > max_x) max_x = proj;
        if (k == 0 || perp > max_y) max_y = perp;
      }

      // 计算当前包围盒面积
      double area = (max_x - min_x) * max_y;
      if (area >= min_area) continue;

      // 计算四个顶点坐标
      Point p1 = a + Point{dx * min_x, dy * min_x};
      Point p2 = a + Point{dx * max_x, dy * max_x};
      best = {
        p1 + Point{-dy * max_y, dx * max_y},
        p2 + Point{-dy * max_y, dx * max_y},
        p2,
        p1
      };
      min_area = area;
    }
    
    return {min_area, best};
  }

private:
  // 叉积辅助函数
  static double cross(const Point& a, const Point& b, const Point& c) {
      return (b - a).cross(c - a);
  }
};