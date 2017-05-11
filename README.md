This is a command shell. Programmed in C++ and makes use of execvp, waitpid, and fork.

Has the same functionality as a regular terminal.

Introduction : We will be creating a project that allows us to take in commands from the 
command line in bash and we will be using connectors to execute them. By using a composite
design pattern consisting of Connector class as the composite and a command class as a leaf,
we are able to accomplish this

";" = The following command will always be executed.
"||" = If the current command fails, the following command will be executed.
"&&" = If the current command succeeds, the following command will be executed.
"#" = Everything after "#" will be a comment.

Can support commands such as:
"exit" = Will exit the entire command line and program.
"mkdir" = Creates a directory from the terminal.
"pwd" = Displays the pathname of the current directory. 

Install Instructions: 

    $ git clone https://github.com/apham024/rshell.git
    $ cd rshell
    $ git checkout hw2
    $ make
    $ bin/rshell
    
Bugs/Limitations 

Commands cannot take in the second argument after connectors 
Command line cannot implement cd
