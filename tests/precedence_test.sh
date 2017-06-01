#!/bin/sh
#tests for precedence operators

(echo hello world)
(echo A && echo B) || (echo C && echo D)
(echo hello world && ls) || echo poop
echo poop1 || (ls && pwd) || echo poop2
((echo A && echo B) || (echo C && echo D)) && pwd
((ls) || (ps)) && mkdir testdir && echo created test directory
(mkdir testdir && ls) && echo made testdir directory

