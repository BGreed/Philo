# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: braugust <braugust@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/08 19:21:07 by braugust          #+#    #+#              #
#    Updated: 2024/12/08 20:27:48 by braugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =      philo
CC =        @cc
CFLAGS =    -Wall -Werror -Wextra
AR =        ar rcs
RM =        rm -rf
SRCS =      main.c

OBJS =        $(SRCS:.c=.o)

GREEN =        \033[1;32m
YELLOW =    \033[1;33m
BLUE =        \033[1;34m
RED =        \033[1;31m
RESET =        \033[0m
BOLD =        \033[1m

$(NAME):     $(OBJS)
            @echo "$(BLUE)$(BOLD)\n\tCompiling ${NAME}... 🛠️\n$(RESET)"
            @$(AR) $(NAME) $(OBJS)
            @echo "$(GREEN)$(BOLD)\n\t${NAME} compiled 🚀\n$(RESET)"

all:         $(NAME)

clean:
            @echo "$(RED)$(BOLD)\n\tCleaning up object files 🧹\n$(RESET)"
            @$(RM) $(OBJS)
            @echo "$(GREEN)$(BOLD)\n\tObject files removed! ✅\n$(RESET)"

fclean:     clean
            @echo "$(RED)$(BOLD)\n\tDeleting ${NAME} 🗑️\n$(RESET)"
            @$(RM) $(NAME)
            @echo "$(GREEN)$(BOLD)\n\t${NAME} deleted! ❌\n$(RESET)"

re: 
            @echo "$(YELLOW)$(BOLD)\n\tRecompiling ${NAME} 🔄\n$(RESET)"
            @$(MAKE) -s fclean all
            @echo "$(YELLOW)$(BOLD)\n\tDone recompiling! ✅\n$(RESET)"

.PHONY:     all clean fclean re

