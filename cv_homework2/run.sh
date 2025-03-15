#!/bin/bash

cd src
for img_path in ../origin_img/*; do
  filename=$(basename "$img_path" | cut -d. -f1)

  img_txt="${filename}_img.txt"
  outline_txt="${filename}_outline.txt"
  output_img="../result_img/${filename}_Outline.png"
  overlay_img="../result_img/${filename}_Overlay.png"

  # 步骤1：生成图像数据
  python get_img.py "$img_path" > "$img_txt"

  # 步骤2：编译运行C++程序
  g++ main.cpp extract.cpp -o main || exit
  ./main < "$img_txt" > "$outline_txt"

  # 步骤3：生成轮廓图像
  python visualize.py "$outline_txt" -o "$output_img"
  
  # 步骤4：生成叠加了轮廓的原图
  python visualize.py "$outline_txt" -o "$overlay_img" --overlay --original "$img_path"

  # 清理临时文件
  rm -f "$img_txt" "$outline_txt" main
done

cd ..

ls -lh result_img/