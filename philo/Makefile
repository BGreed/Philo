# **************************************************************************** #
#			                                                                  #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: braugust <braugust@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/08 19:21:07 by braugust          #+#    #+#              #
#    Updated: 2025/04/15 15:36:32 by braugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror

NAME = philo
OBJDIR = obj

SRC = $(shell find . -type f -name "*.c")

OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

$(shell mkdir -p $(OBJDIR))

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline
	@echo "*----------------------*"
	@echo "\033[1;32mCompilation completed 🎉\033[0m"
	@echo "*----------------------*"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re