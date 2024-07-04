# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 15:53:28 by welee             #+#    #+#              #
#    Updated: 2024/07/04 16:29:05 by welee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = $(shell find $(SRCS_DIR) -name '*.c')
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

LIBFT_DIR = libft
LIBFT = -L $(LIBFT_DIR)/bin -lft
LIBFT_INC = -I $(LIBFT_DIR)/bin

PUBLIC_DIR = public
SRCS_DIR = srcs
OBJS_DIR = objs
INCLUDES_DIR = includes
TEST_DIR = tests
DIST_DIR = dist
BIN_DIR = bin
DOCS_DIR = docs

INCLUDES = -I ${INCLUDES_DIR}
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBC = ar rcs
RM = rm -f
MKDIR = mkdir -p
MAKE = make -C
CD = cd
CP = cp -r
ECHO = echo
FRANCINETTE = francinette
FRANCINETTE_FLAGS = -s
WHOAMI = $(shell whoami)

NORM = norminette
NORM_FLAGS = -R CheckForbiddenSourceHeader -R CheckDefine

DOXYGEN = doxygen
DOXYGEN_CONFIG = Doxyfile

all: $(NAME)
$(NAME): $(OBJS)
	@$(MAKE) $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT_INC) $(OBJS) -o $(NAME) $(LIBFT)
	@$(ECHO) "\033[32m$(NAME) compiled\033[0m"
