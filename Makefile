# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 15:53:28 by welee             #+#    #+#              #
#    Updated: 2024/09/09 16:42:32 by welee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = $(BINS_DIR)/pipex
SRCS = $(shell find $(SRCS_DIR) -name "*.c")
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

GET_NEXT_LINE_DIR = $(LIBS_DIR)/get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/bin/libgnl.a
GET_NEXT_LINE_LIB = -L$(GET_NEXT_LINE_DIR)/bin -lgnl
GET_NEXT_LINE_INC = $(GET_NEXT_LINE_DIR)/includes

PUBLIC_DIR = public
SRCS_DIR = srcs
OBJS_DIR = objs
INCS_DIR = includes
TEST_DIR = tests
DIST_DIR = dist
LIBS_DIR = libs
BINS_DIR = bin
DOCS_DIR = docs

INCLUDES = -I ${INCLUDES_DIR}
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR) -I$(LIBFT_INC) -I$(GET_NEXT_LINE_INC)
LIBC = ar rcs
RM = rm -f
MKDIR = mkdir -p
MAKE = make
CD = cd
CP = cp -r
ECHO = echo
WHOAMI = $(shell whoami)

NORM = norminette
NORM_FLAGS = -R CheckForbiddenSourceHeader -R CheckDefine

DOXYGEN = doxygen
DOXYGEN_CONFIG = Doxyfile

all: $(NAME)

$(NAME): $(LIBFT) $(GET_NEXT_LINE) $(OBJS) | $(BINS_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(GET_NEXT_LINE_LIB) $(LIBFT_LIB)
	@$(ECHO) "\033[32m$(NAME) compiled\033[0m"

$(BINS_DIR):
	$(MKDIR) $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GET_NEXT_LINE):
	$(MAKE) -C $(GET_NEXT_LINE_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	@$(ECHO) "\033[33m$@\033[0m"

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	@$(ECHO) "\033[31m$(NAME) object files removed\033[0m"

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@$(ECHO) "\033[31m$(NAME) removed\033[0m"

re: fclean all

norm:
	$(NORM) $(NORM_FLAGS) $(SRCS_DIR) $(INCLUDES_DIR)
	@$(ECHO) "\033[32mNorm check completed\033[0m"

tests: all
	$(TEST_DIR)/test_pipex.sh
	@$(ECHO) "\033[32mTest completed\033[0m"

doxygen:
	@$(DOXYGEN) $(DOXYGEN_CONFIG)
	@$(ECHO) "\033[32mDoxygen generated\033[0m"

.PHONY: all clean fclean re norm test doxygen
