# !/bin/bash
WORK_DIR="/home/ymdxe/code/cpp/cv_homework/work2"
cd $WORK_DIR
g++ cv_work2.cpp -o cv_work2
python get_img3D.py 
./cv_work2 < img.txt > out.txt
python show_img3D.py
rm -f cv_work2
rm img.txt
rm out.txt