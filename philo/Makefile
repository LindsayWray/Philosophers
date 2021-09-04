# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lwray <lwray@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/20 08:01:17 by lwray         #+#    #+#                  #
#    Updated: 2021/08/20 14:44:32 by lwray         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := philo
HEADERFILES :=	includes/philosophers.h
SRCS :=			srcs/philosophers.c \
				srcs/parsing.c \
				srcs/create_forks.c \
				srcs/thread_activity.c \
				srcs/print.c \
				srcs/timing.c \
				srcs/monitoring.c \
				srcs/cleanup.c \
				srcs/error_handler.c

FLAGS := -Wall -Wextra -Werror
OBJFILES := $(SRCS:srcs/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJFILES) 
	gcc -o $@ $^

obj/%.o: srcs/%.c $(HEADERFILES)
	@mkdir -p $(dir $@)
	gcc -c $(FLAGS) -o $@ $<

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette $(SRCS) $(HEADERFILES)

.PHONY: all clean fclean re norm
