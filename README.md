## Example
* open a shell, run
```
exec.x test.sh > test.out
```
now the program will monitor if there's anything in `test.sh`, you can name this file whatever you like, and it doesn't need to exist. Now the program will keep checking if the file exist, and if there is anything in the first line.

* open another shell, type
```
echo "ls -l > ls.out" > test.sh
```
now we create `test.sh` and put the command `ls -l > ls.out` into that file. After about 2 seconds, it will be executed by `exec`. After return, `test.sh` will be removed, and the program will keep monitoring if `test.sh` exist every 2 seconds.

Now if you check `test.out`, it will show something like
```
script file: test.sh

running: `ls -l > ls.out` ...
returned, time used: xxxx
```

* when the job is finished, the script file will be deleted. If it is remove by hand, the job will be killed.
