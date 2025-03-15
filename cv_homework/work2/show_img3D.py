import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def load_data(filename):
    """读取 C++ 处理后的 3D 数据"""
    with open(filename, "r") as f:
        lines = f.readlines()

    width, height, depth = map(int, lines[0].split())
    data = np.zeros((height, width, depth), dtype=int)

    index = 1
    for i in range(height):
        for j in range(width):
            data[i, j, :] = list(map(int, lines[index].split()))
            index += 1
    return data

# 读取数据
data = load_data("/home/ymdxe/code/cpp/cv_homework/work2/out.txt")

# 3D 可视化（展示截面）
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')

# 选择一个深度切片
z_slice = 100
X, Y = np.meshgrid(np.arange(data.shape[1]), np.arange(data.shape[0]))
Z = data[:, :, z_slice]

ax.plot_surface(X, Y, Z, cmap='viridis')

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()
