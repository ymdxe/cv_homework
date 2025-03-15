#!/bin/bash
WORK_DIR="/home/ymdxe/code/cpp/cv_homework/work1"
cd $WORK_DIR
g++ cv_work1.cpp -o cv_work1
python get_img.py > img.txt
./cv_work1 < img.txt > out.txt
python show_img.py < out.txt
rm -f cv_work1
rm img.txt
rm out.txt