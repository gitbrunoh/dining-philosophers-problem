CC = cc

NAME = philo

CFLAGS = -Wall -Wextra -Werror -g -Iphilo

LDFLAGS = -lpthread

SRC = src/main.c \
src/utils.c \
src/utils2.c \
src/threads.c \
src/args_validation.c \
src/init_data.c \
src/init_mutexes.c \
src/prints.c \
src/error.c \
src/philosophers.c \
src/checks.c \
src/getters.c \
src/lifecycle.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

sanitize_thread: CFLAGS += -fsanitize=thread
sanitize_thread: LDFLAGS += -fsanitize=thread
sanitize_thread: fclean $(NAME)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
