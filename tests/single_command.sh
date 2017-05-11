#!/bin/sh
# single command test #

$ cd rshell
$ ./a.out

"echo hello world" >> output.txt
"ls" >> output.txt
"cat README.MD" >> output.txt
"mkdir test_directory" >> output.txt
"echo "This is a test"" >> output.txt
"pwd" >> output.txt
"ls -a" >> output.txt
"echo" >> output.txt
"echo "Hello World!"" 