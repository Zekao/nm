# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 03:21:58 by emaugale          #+#    #+#              #
#    Updated: 2023/03/15 23:56:35 by emaugale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	ft_nm

SRCS = main.c 
SRCS += utils.c
SRCS += print.c
SRCS += parsing.c
SRCS += free.c
SRCS += content_flag.c

NAME_BONUS	=		ft_nm_bonus
SRCS_BONUS =  bonus/main.c 
SRCS_BONUS += bonus/utils.c
SRCS_BONUS += bonus/print.c
SRCS_BONUS += bonus/parsing.c
SRCS_BONUS += bonus/free.c
SRCS_BONUS += bonus/content_flag.c


OBJS		=		$(SRCS:.c=.o)
OBJS_BONUS	=		$(SRCS_BONUS:.c=.o)
INCLUDE		= 		include
RM		=		rm -f
CC		=		cc
CFLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address #-fsanitize=undefined -fsanitize=leak

%.o:				%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

all:	$(NAME)

bonus:	$(NAME_BONUS)

$(NAME):		$(OBJS)
	@echo "									"
	@echo "Project name : $(NAME)"
	@echo "\n\033[1;32mCompilation en cours... ⌛\033[0;m\n"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re:		fclean all

.PHONY: all clean fclean re bonus