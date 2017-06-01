#!/bin/sh
#tests for the test command

[ -e bin ] && echo exists
test -f LICENSE && echo file exists

mkdir testdir
test -d testdir && echo is a directory

touch poop.h
test -f poop.h && echo file exists
rm poop.h
test -f poop.h || echo file poop.h does not exist

rm -r testdir
[ -d testdir ] || echo no such directory found




