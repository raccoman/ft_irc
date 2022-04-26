#Name
NAME =			ircbot

#Compiler
CC = 			clang++
CFLAGS = 		-Wall -Werror -Wextra -std=c++11
LIBRARIES =
CFLAG = 		-c
OFLAG =			-o
IFLAG =			-I

#Make
MAKE = 			make -s -C
MAKE_CLEAN = 	make clean -s -C
MAKE_FCLEAN = 	make fclean -s -C

#Shell
MKDIR =			mkdir -p
CP =			cp
RM =			rm -rf

#Directories
SOURCES_DIR =	./src
OBJECTS_DIR =	./objs
HEADERS_DIR =	./include

#Files
FILES =		main.cpp \
			IrcBot.cpp

#Srcs
SRCS =			$(foreach FILE, $(FILES), $(shell find $(SOURCES_DIR) -name $(FILE)))

#Objs
OBJS =			$(patsubst $(SOURCES_DIR)/%, $(OBJECTS_DIR)/%, $(SRCS:.cpp=.o))

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(IFLAG) $(HEADERS_DIR) $(CFLAG) $(OFLAG) $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBRARIES) $(OFLAG) $(NAME)
	@echo "Done!"

clean:
	@$(RM) $(OBJECTS_DIR)

fclean: clean
	@$(RM) $(NAME)

run: re
	./$(NAME) "127.0.0.1" 3000 password

re: fclean all clean

.PHONY: all clean fclean re