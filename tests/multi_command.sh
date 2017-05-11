#!/bin/sh
# multiple command tests #
$ cd rshell
$ ./a.out

# chmod u+x program_name

echo hello world || ls -a >> output.txt
ls -a && mkdir test_directory >> output.txt
# echo || ls -m && echo test1 || mkdir rshell_test
# echo "this is a test" || echo "the first test failed" && ls
# mkdir test_dir && echo made test_dir
# echo testing clear; clear
# echo || mkdir || ls
# ls -a || ls && ls