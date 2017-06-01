CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic
DIRECT = bin
SRCS = src
EXEC = a.out
SRC := $(wildcard src/*.cpp) #list of source files
#object file list
OBJS := $(addprefix bin/, $(notdir $(SRC:.cpp=.o))) 

# @ puts all outputs of compilation in the file on the left of the :
#  < is first item in dependencies list
#  input   output
	# $(CC) $(OBJS) -o $(DIRECT)/$(EXEC)
rshell: $(DIRECT)/rshell

all: $(DIRECT)/ $(OBJS)

$(DIRECT)/rshell: $(DIRECT)/ $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)


$(DIRECT)/%.o: $(SRCS)/%.cpp #rule for building objects
	$(CC) $(CFLAGS) -c -o $@ $<


$(DIRECT)/:
	mkdir -p $@

clean:
	rm -r $(DIRECT)
	