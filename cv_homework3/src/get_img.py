import cv2
import numpy as np
import sys
import os

sys.stdout.reconfigure(encoding='gbk')

# 获取当前脚本所在目录
script_dir = os.path.dirname(os.path.abspath(__file__))
# 获取项目根目录（当前目录的父目录）
root_dir = os.path.dirname(script_dir)

# 读取图像
image = cv2.imread(os.path.join(root_dir, 'origin_img', 'hammer.png'))
if image is None:
    print("Error: Could not read image.")
    exit(1)

# 转换为灰度图
gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 二值化处理
_, binary_image = cv2.threshold(gray_image, 128, 255, cv2.THRESH_BINARY_INV)

# 输出图像尺寸
height, width = binary_image.shape
print(height, width)

# 输出二值化后的图像数据
for i in range(height):
    for j in range(width):
        print(int(binary_image[i][j]), end=' ')
    print()
