#!/bin/sh
# commented command test #
$ cd rshell
$ ./a.out

echo hello #world
echo #test
ls -a || echo hello world #testing comments on multiple commands
echo test # || ls 
mkdir #test_directory
mkdir test_directory #create a test directory
echo test && echo test2 # echo both statements
echo #commented echo test 
echo mkdir test_dir # echo test 

