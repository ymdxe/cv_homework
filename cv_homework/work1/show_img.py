import sys
import numpy as np
import cv2

def main():
    # 从标准输入读取 height 和 width
    height, width = map(int, input().split())
    
    # 创建一个空的列表来存储矩阵数据
    image_data = []
    
    # 读取 height 行数据
    for _ in range(height):
        row = list(map(int, input().split()))
        image_data.append(row)

    # 将数据转换为 NumPy 数组，数据类型为 uint8，因为图像数据通常是无符号8位整数
    image_array = np.array(image_data, dtype=np.uint8)

    # 确保图像数据大小符合要求
    if image_array.shape != (height, width):
        print("输入的矩阵大小与height和width不匹配")
        return

    # 保存图像
    # cv2.imwrite('MiddleFilter.jpg', image_array)
    cv2.imwrite('MeanFilter.jpg', image_array)

    # # 显示图像
    # cv2.imshow('Output Image', image_array)

    # # 按任意键关闭窗口
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
