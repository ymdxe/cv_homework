import numpy as np
import cv2
import matplotlib.pyplot as plt
import os
import sys
import argparse

def read_gradient_data(filename):
    """读取梯度或角度数据"""
    with open(filename, 'r') as file:
        # 读取第一行的高度和宽度
        height, width = map(int, file.readline().split())
        
        # 读取数据
        data = np.zeros((height, width), dtype=float)
        for i in range(height):
            row = list(map(float, file.readline().strip().split()))
            data[i, :] = row
    
    return data

def normalize_data(data, is_angle=False):
    """归一化数据用于显示"""
    if is_angle:
        # 角度数据从[-pi, pi]映射到[0, 255]
        normalized = ((data + np.pi) / (2 * np.pi) * 255).astype(np.uint8)
        return normalized  # 直接返回灰度图
    else:
        # 梯度幅值归一化到[0, 255]
        min_val = data.min()
        max_val = data.max()
        if max_val > min_val:
            normalized = ((data - min_val) / (max_val - min_val) * 255).astype(np.uint8)
        else:
            normalized = np.zeros_like(data, dtype=np.uint8)
        return normalized

def overlay_outline_on_original(outline_data, original_img_path, output_path):
    """将轮廓叠加到原始图像上"""
    # 读取原始图像
    original_img = cv2.imread(original_img_path)
    if original_img is None:
        print(f"无法读取原始图像: {original_img_path}")
        return False
    
    # 调整原始图像大小
    original_img = cv2.resize(original_img, (outline_data.shape[1], outline_data.shape[0]))
    
    # 创建轮廓掩码 - 将非零像素作为轮廓
    outline_mask = (outline_data > 0).astype(np.uint8) * 255
    
    # 创建彩色轮廓 
    red_outline = np.zeros_like(original_img)
    red_outline[:, :, 1] = outline_mask 
    
    # 叠加轮廓到原始图像
    alpha = 1  # 轮廓透明度
    result_img = cv2.addWeighted(original_img, 1, red_outline, alpha, 0)
    
    # 保存结果
    cv2.imwrite(output_path, result_img)
    print(f"带轮廓的图像已保存为 {output_path}")
    return True

def main():
    parser = argparse.ArgumentParser(description='Visualize gradient magnitude or angle data')
    parser.add_argument('input_file', help='Input file containing gradient data')
    parser.add_argument('--angle', action='store_true', help='Input contains angle data')
    parser.add_argument('--output', '-o', default='output.png', help='Output image filename')
    parser.add_argument('--overlay', action='store_true', help='Overlay outline on original image')
    parser.add_argument('--original', default='', help='Original image path for overlay')
    args = parser.parse_args()

    # 读取数据
    data = read_gradient_data(args.input_file)
    
    # 归一化数据
    image = normalize_data(data, is_angle=args.angle)
    
    # 保存图像
    cv2.imwrite(args.output, image)
    print(f"图像已保存为 {args.output}")
    
    # 如果需要叠加轮廓到原图
    if args.overlay and args.original:
        overlay_output = args.output.replace('.png', '.png')
        overlay_outline_on_original(data, args.original, overlay_output)
    
if __name__ == "__main__":
    main()