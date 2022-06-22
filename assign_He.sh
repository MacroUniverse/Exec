#!/bin/bash
# assign jobs for exec.x

for ((i = 1563; i <= 1580; i+=1))
do
    test=$((i+0))
    exec=$((i+0))
    echo "test ${test} -> ${exec}.in"
    echo "cd ../FEDVR-TDSE/He_prop/ && ./main.x < inputs/${test}.inp >> ${test}.out 2>&1" > ${exec}.in
done
