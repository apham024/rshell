#!/bin/sh
#tests for the test command

[ -e /home/ubuntu/workspace/cs100/rshell ] && echo exists
test -f /home/ubuntu/workspace/cs100/rshell/LICENSE && echo file exists

mkdir testdir
test -d /home/ubuntu/workspace/cs100/rshell/testdir && echo is a directory

touch poop.h
test -f /home/ubuntu/workspace/cs100/rshell/poop.h && echo file exists
rm poop.h
test -f /home/ubuntu/workspace/cs100/rshell/poop.h || echo file poop.h does not exist

rm -r testdir
[ -d /home/ubuntu/workspace/cs100/rshell/testdir ] || echo no such directory found



