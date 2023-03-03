# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwesley <lwesley@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 13:34:47 by igoraleksee       #+#    #+#              #
#    Updated: 2022/05/29 14:02:44 by lwesley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC =		srcs/cmds/cd.c\
			srcs/cmds/echo.c\
			srcs/cmds/env.c\
			srcs/cmds/export.c\
			srcs/cmds/pwd.c\
			srcs/cmds/unset.c\
			srcs/exec/builtins.c\
			srcs/exec/exec_utils.c\
			srcs/exec/exec.c \
			srcs/exec/exit.c \
			srcs/free/free.c \
			srcs/free/free_utils.c \
			srcs/main/count_argv.c \
			srcs/main/heredoc.c \
			srcs/main/minishell.c \
			srcs/redirect/redirect.c \
			srcs/parse/parse_3.c \
			srcs/parse/parse_4.c \
			srcs/parse/parse_5.c \
			srcs/parse/parse_line.c \
			srcs/redirect/add_redirect.c \
			srcs/redirect/redirect_utils.c \
			srcs/utils/args_utils.c \
			srcs/utils/find_utils.c \
			srcs/libft/libft_utils.c \
			srcs/libft/libft_utils_fs.c \
			srcs/libft/libft_utils_sc.c \
			srcs/libft/libft_utils_th.c \
			srcs/libft/ft_itoa.c \
			srcs/libft/ft_split.c \
			srcs/utils/list_utils.c \
			srcs/utils/str_utils.c \
			srcs/utils/utils_export.c \
			srcs/utils/utils.c \
			srcs/utils/var_utils.c \
			srcs/utils/utils_1.c \

OBJ = $(patsubst %.c, %.o, $(SRC))
INCLUDE = srcs/minishell.h
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(INCLUDE) $(SRC) Makefile
	gcc $(FLAGS) $(SRC) -g -lreadline -L /Users/lwesley/.brew/Cellar/readline/8.1.2/lib -I /Users/lwesley/.brew/Cellar/readline/8.1.2/include -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re