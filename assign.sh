#!/bin/bash
# assign jobs for exec.x

for ((i = 107; i <= 117; ++i))
do
    echo "cd ../FEDVR-TDSE/He_prop/ && ./main.x < inputs/${i}.inp > ${i}.out" > $((i-106)).sh
done
