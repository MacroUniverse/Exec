#!/bin/bash
# assign jobs for exec.x

for ((i = 300; i <= 340; ++i))
do
    test=$((i+0))
    exec=$((i+0))
    echo "test ${test} -> ${exec}.in"
    echo "cd ../FEDVR-TDSE/H_prop/ && ./main.x < inputs/${test}.inp >> ${test}.out 2>&1" > ${exec}.in
done
