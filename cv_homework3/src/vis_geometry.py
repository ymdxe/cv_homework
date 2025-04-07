import numpy as np
import cv2
import matplotlib.pyplot as plt

def read_points(filename):
    """读取点集数据"""
    with open(filename) as f:
        n = int(f.readline())
        points = []
        for _ in range(n):
            x, y = map(float, f.readline().split())
            points.append([x, y])
    return np.array(points, dtype=np.int32)

def draw_geometry(image_path, points_file, output_path):
    """绘制几何结构到图像上"""
    # 读取原始图像
    img = cv2.imread(image_path)
    if img is None:
        print(f"无法读取图像: {image_path}")
        return
    
    # 读取点集
    points = read_points(points_file)
    
    # 根据文件名判断要绘制的内容
    if "points" in points_file:
        # 绘制所有点（红色）
        for pt in points:
            cv2.circle(img, tuple(pt), 2, (0, 0, 255), -1)
    elif "hull" in points_file:
        # 绘制凸包（蓝色）
        if len(points) >= 3:
            cv2.polylines(img, [points], True, (255, 0, 0), 2)
    elif "minbox" in points_file:
        # 绘制最小包围盒（黄色）
        if len(points) >= 4:
            cv2.polylines(img, [points], True, (0, 255, 255), 2)
    elif "box" in points_file or "outline" in points_file:
        # 绘制最大外接矩形（绿色）
        if len(points) >= 4:
            cv2.polylines(img, [points], True, (0, 255, 0), 2)
    
    # 保存结果
    cv2.imwrite(output_path, img)
    print(f"可视化结果已保存到: {output_path}")
    
    # 显示结果
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    plt.title("Geometry Visualization")
    plt.axis('off')
    plt.show()

def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('image', help='Original image path')
    parser.add_argument('points', help='Points data file')
    parser.add_argument('--output', default='result.png', help='Output image path')
    args = parser.parse_args()
    
    draw_geometry(args.image, args.points, args.output)

if __name__ == "__main__":
    main()