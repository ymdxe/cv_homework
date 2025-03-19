#!/bin/bash

CURRENT_DIR=$(pwd)
WORK_DIR="$CURRENT_DIR/work1"
cd $WORK_DIR

PARAMETR=$1

g++ cv_work1.cpp -o cv_work1
python get_img.py > img.txt
./cv_work1 $PARAMETR < img.txt > out.txt
python show_img.py $PARAMETR < out.txt
rm -f cv_work1
rm img.txt
rm out.txt