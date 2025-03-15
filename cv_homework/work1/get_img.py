import cv2
import numpy as np
import sys
import os

sys.stdout.reconfigure(encoding='gbk')

os_dir = os.path.dirname(os.path.abspath(__file__))  
# print(os_dir)
# 读取图像
image = cv2.imread(os_dir + '/lena.jpg')
if image is None:
    print("Error: Could not read image.")
    exit(1)

# 调整大小并转换为灰度图
resized_image = cv2.resize(image, (512, 512))
gray_image = cv2.cvtColor(resized_image, cv2.COLOR_BGR2GRAY)

# （接上述代码的读取和灰度转换部分）

# ------------------- 添加椒盐噪声 -------------------
prob = 0.08  # 噪声比例（如 8% 的像素点被噪声覆盖）
noisy_image = gray_image.copy()

# 生成随机掩膜
salt = np.random.rand(*gray_image.shape) < prob/2  # 盐噪声（白点）
pepper = np.random.rand(*gray_image.shape) < prob/2 # 椒噪声（黑点）

noisy_image[salt] = 255
noisy_image[pepper] = 0

# 保存带噪声的图像
cv2.imwrite('noisy_salt.jpg', noisy_image)

# 输出带噪声的像素值
for i in range(512):
    for j in range(512):
        print(int(noisy_image[i][j]), end=' ')
    print()

# ------------------- 添加高斯噪声 -------------------
# mean = 0        # 均值
# sigma = 8      # 标准差（控制噪声强度，建议范围 10-50）
# noise = np.random.normal(mean, sigma, gray_image.shape).astype(np.int16)
# noisy_image = cv2.add(gray_image.astype(np.int16), noise)
# noisy_image = np.clip(noisy_image, 0, 255).astype(np.uint8)

# # 保存带噪声的图像
# cv2.imwrite('noisy_gaussian.jpg', noisy_image)

# # 输出带噪声的像素值
# for i in range(512):
#     for j in range(512):
#         print(int(noisy_image[i][j]), end=' ')
#     print()