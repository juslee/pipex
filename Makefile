# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 15:53:28 by welee             #+#    #+#              #
#    Updated: 2024/09/06 12:23:19 by welee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# BONUS_SRCS_DIR = srcs/bonus
# BONUS_OBJS_DIR = objs/bonus
# BONUS_SRCS = $(filter-out
# 				$(SRCS_DIR)/main.c
# 				$(SRCS_DIR)/pipex.c
# 				$(SRCS_DIR)/fork_and_exec.c, $(wildcard $(SRCS_DIR)/*.c)) \
# 			 $(wildcard $(BONUS_SRCS_DIR)/*.c)

LIBFT_DIR = $(LIBS_DIR)/libft
LIBFT = $(LIBFT_DIR)/bin/libft.a
LIBFT_LIB = -L$(LIBFT_DIR)/bin -lft
LIBFT_INC = $(LIBFT_DIR)/includes

PUBLIC_DIR = public
SRCS_DIR = srcs/mandatory
OBJS_DIR = objs/mandatory
INCLUDES_DIR = includes
TEST_DIR = tests
DIST_DIR = dist
LIBS_DIR = libs
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
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT_INC) $(OBJS) -o $(BIN_DIR)/$(NAME) $(LIBFT)
	@$(ECHO) "\033[32m$(NAME) compiled\033[0m"
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT_INC) -c $< -o $@
	@$(ECHO) "\033[33m$@\033[0m"
clean:
	@$(MAKE) $(LIBFT_DIR) clean
	@$(RM) -r $(OBJS_DIR)
	@$(ECHO) "\033[31m$(NAME) object files removed\033[0m"
fclean: clean
	@$(MAKE) $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@$(ECHO) "\033[31m$(NAME) removed\033[0m"
re: fclean all
norm:
	@$(NORM) $(NORM_FLAGS) $(SRCS_DIR) $(INCLUDES_DIR)
test: all
	@$(CD) $(TEST_DIR) && ./test.sh
	@$(ECHO) "\033[32mTest completed\033[0m"
doxygen:
	@$(DOXYGEN) $(DOXYGEN_CONFIG)
	@$(ECHO) "\033[32mDoxygen generated\033[0m"
francinette:
	@$(FRANCINETTE) $(FRANCINETTE_FLAGS)
	@$(ECHO) "\033[32mFrancinette completed\033[0m"
.PHONY: all clean fclean re norm test doxygen francinette
