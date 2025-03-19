import numpy as np

width, height, depth = 512, 512, 200

def generate_wave():
    """生成波浪形 3D 图像"""
    img = np.zeros((height, width, depth), dtype=int)
    for x in range(height):
        for y in range(width):
            for z in range(depth):
                img[x, y, z] = int(100 + 50 * np.sin(0.05 * x) * np.cos(0.05 * y) * np.sin(0.05 * z))
    return img

# 生成 3D 数据
img = generate_wave()


# 保存到文件
with open("/home/ymdxe/code/cpp/cv_homework/work2/img.txt", "w") as f:
    for x in range(height):
        for y in range(width):
            for z in range(depth):
                f.write(f"{img[x, y, z]} ")
            f.write("\n")
