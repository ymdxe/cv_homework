#!/bin/bash

cd src
for img_path in ../origin_img/*; do
  filename=$(basename "$img_path" | cut -d. -f1)
  
  # 生成输出文件路径
  img_txt="${filename}_img.txt"
  points_txt="points.txt"
  hull_txt="hull.txt"
  minbox_txt="minbox.txt"
  box_txt="box.txt"
  geometry_img="../result_img/${filename}_Geometry.png"

  # 步骤1：使用get_img.py生成灰度图数据
  python get_img.py "$img_path" > "$img_txt"

  # 步骤2：编译运行C++程序，将灰度图数据作为输入
  g++ main.cpp image.cpp -o main || exit
  ./main < "$img_txt"

  # 步骤3：使用vis_geometry.py进行可视化，分别可视化点、凸包、最小包围盒和最大外接矩形
  # 可视化凸包
  python vis_geometry.py "$img_path" "$hull_txt" --output "../result_img/${filename}_hull.png"
  # 可视化最小包围盒
  python vis_geometry.py "$img_path" "$minbox_txt" --output "../result_img/${filename}_minbox.png"
  # 可视化最大外接矩形
  python vis_geometry.py "$img_path" "$box_txt" --output "../result_img/${filename}_box.png"

  # 清理临时文件
  rm -f main "$img_txt" "$points_txt" "$hull_txt" "$minbox_txt" "$box_txt"
done

cd ..

ls -lh result_img/ 