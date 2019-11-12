## Example
* open a shell, run
```
make
echo "test.sh" | exec.x
```
now the program will monitor if there's anything in `test.sh`

* open another shell, run
```
echo "ls -l > 1.out" > test.sh
```
now we create `test.sh` and put the command `ls -l > 1.out` into that file. After about 2 seconds, it will be executed. After execution, `test.sh` will be removed, and the program will keep monitoring.
