#!/bin/bash
# submit exec.x to slurm
set +H
for ((i = 1571; i <= 1573; ++i))
# for i in {1350,1351}
do
    printf "#!/bin/sh\n./exec.x ${i}.in  > ${i}.out\n" > ${i}.slurm
    # minimum is 1024M/cpu
    # anything less than a week gets automatically flagged as killable (--gres=killable:0)
    sbatch --time=72:0:0 --mem-per-cpu=1024M --cpus-per-task=28 --ntasks=1 --nodes=1 ./${i}.slurm
done
