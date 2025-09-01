SRCS_FILES = main.c init.c monitor.c routine.c threads.c utils.c
SRCS_DIR = sources/
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS_DIR = objects/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_FILES:.c=.o))

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -Iincludes

HEADER = includes/philo.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
