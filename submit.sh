#!/bin/bash
# submit exec.x to slurm
for ((i = 101; i <= 102; ++i))
do
    printf "#!/bin/sh\necho ${i}.sh | ./exec.x > ${i}.out\n" > ${i}.slurm
    sbatch --gres=killable:0 --time=72:0:0 --mem-per-cpu=1536M --cpus-per-task=16 --ntasks=1 --nodes=1 ./${i}.slurm
done
