import cv2
import numpy as np
import sys
import os

sys.stdout.reconfigure(encoding='gbk')

# 获取当前脚本所在目录
script_dir = os.path.dirname(os.path.abspath(__file__))
# 获取项目根目录（当前目录的父目录）
root_dir = os.path.dirname(script_dir)
# print(root_dir)
# 读取图像
image = cv2.imread(os.path.join(root_dir, 'origin_img', 'lena.jpg'))
if image is None:
    print("Error: Could not read image.")
    exit(1)

# 调整大小并转换为灰度图
resized_image = cv2.resize(image, (512, 512))
gray_image = cv2.cvtColor(resized_image, cv2.COLOR_BGR2GRAY)

#
for i in range(512):
    for j in range(512):
        if gray_image[i][j] < 128:
            gray_image[i][j] = 0
        else:
            gray_image[i][j] = 255
        print(int(gray_image[i][j]), end=' ')
    print()
