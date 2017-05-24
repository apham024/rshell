## CS 100 RShell
This is a command shell. Programmed in C++ and makes use of execvp, waitpid, and fork.
Has the same functionality as a regular terminal.

## Introduction
We will be creating a project that allows us to take in commands from the 
command line in bash and we will be using connectors to execute them. By using a composite
design pattern consisting of Connector class as the composite and a command class as a leaf,
we are able to accomplish this

";" = The following command will always be executed.<br />
"||" = If the current command fails, the following command will be executed.<br />
"&&" = If the current command succeeds, the following command will be executed.<br />
"#" = Everything after "#" will be a comment.<br />

## Can support commands such as
"exit" = Will exit the entire command line and program.<br />
"mkdir" = Creates a directory from the terminal.<br />
"pwd" = Displays the pathname of the current directory. <br />

## Install Instructions
    $ git clone https://github.com/apham024/rshell.git
    $ cd rshell
    $ git checkout hw2
    $ make
    $ bin/rshell
    
## Authors
Annie Pham <br />
Sabrina Wong
    
## Bugs/Limitations
Commands cannot take in the second argument after connectors <br />
Commands cannot implement cd <br />
