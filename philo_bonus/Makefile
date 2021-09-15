#Name
NAME =			philo_bonus

#Compiler
CC = 			gcc
CFLAGS = 		-Wall -Wextra -Werror
LIBRARIES =		-lpthread
CFLAG = 		-c
OFLAG =			-o
IFLAG =			-I

#Make
MAKE = 			make -s -C
MAKE_CLEAN = 	make clean -s -C
MAKE_FCLEAN = 	make fclean -s -C

#Unzip
UNZIP =			unzip -X -o -q

#Norm
NORM =			norminette

#Shell
MKDIR =			mkdir -p
CP =			cp
RM =			rm -rf

#Directories
SOURCES_DIR =	./src
OBJECTS_DIR =	./objs
HEADERS_DIR =	./headers

#Files
FILES =			logger.c \
				philosophers.c \
				routines.c \
				utils.c \
				main.c

#Srcs
SRCS =			$(foreach FILE, $(FILES), $(shell find $(SOURCES_DIR) -name $(FILE)))

#Objs
OBJS =			$(patsubst $(SOURCES_DIR)/%, $(OBJECTS_DIR)/%, $(SRCS:.c=.o))

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(IFLAG) $(HEADERS_DIR) $(CFLAG) $(OFLAG) $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBRARIES) $(OFLAG) $(NAME)
	@echo "Done!"

norminette:
	@$(NORM) $(shell find $(SOURCES_DIR) -name *.c)
	@$(NORM) $(shell find $(HEADERS_DIR) -name *.h)

clean:
	@$(RM) $(OBJECTS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all norminette clean fclean re