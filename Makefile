# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 15:53:28 by welee             #+#    #+#              #
#    Updated: 2024/09/18 16:56:01 by welee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = $(BINS_DIR)/pipex
SRCS = $(wildcard $(SRCS_DIR)/*.c) \
	   $(wildcard $(SRCS_DIR)/here_doc/*.c) \
	   $(wildcard $(SRCS_DIR)/pipex/*.c) \
	   $(wildcard $(SRCS_DIR)/utils/*.c)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
INCS = $(wildcard $(INCS_DIR)/*.h)

# Directory Variables -------------------------------------------------------- #
SRCS_DIR = srcs
OBJS_DIR = objs
INCS_DIR = includes
TEST_DIR = tests
DIST_DIR = dist
LIBS_DIR = libs
BINS_DIR = bin
DOCS_DIR = docs
# ---------------------------------------------------------------------------- #

# Library Variables ---------------------------------------------------------- #
LIBFT_DIR = $(LIBS_DIR)/libft
LIBFT = $(LIBFT_DIR)/bin/libft.a
LIBFT_LIB = -L$(LIBFT_DIR)/bin -lft
LIBFT_INC = $(LIBFT_DIR)/includes

GET_NEXT_LINE_DIR = $(LIBS_DIR)/get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/bin/libgnl.a
GET_NEXT_LINE_LIB = -L$(GET_NEXT_LINE_DIR)/bin -lgnl
GET_NEXT_LINE_INC = $(GET_NEXT_LINE_DIR)/includes
# ---------------------------------------------------------------------------- #

# Macros Variables ----------------------------------------------------------- #
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR) -I$(LIBFT_INC) -I$(GET_NEXT_LINE_INC)
LIBC = ar rcs
RM = rm -f
MKDIR = mkdir -p
MAKE = make
CD = cd
CP = cp -r
ECHO = echo
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	SED := sed -i
else ifeq ($(UNAME_S),Darwin)
	SED := sed -i ''
else
	$(error Unsupported OS)
endif
WHOAMI = $(shell whoami)
# ---------------------------------------------------------------------------- #

# Tools Variables -------------------------------------------------------------#
NORM = norminette
NORM_FLAGS = -R CheckForbiddenSourceHeader -R CheckDefine

DOXYGEN = doxygen
DOXYGEN_CONFIG = Doxyfile
# ---------------------------------------------------------------------------- #

# Rules Definitions -----------------------------------------------------------#
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

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCS) | $(OBJS_DIR)
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	@$(ECHO) "\033[33m$@\033[0m"

$(OBJS_DIR):
	$(MKDIR) $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GET_NEXT_LINE_DIR) clean
	@$(ECHO) "\033[31m$(NAME) object files removed\033[0m"

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(DIST_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GET_NEXT_LINE_DIR) fclean
	@$(ECHO) "\033[31m$(NAME) removed\033[0m"

re: fclean all

norm:
	$(NORM) $(NORM_FLAGS) $(SRCS_DIR) $(INCS_DIR)
	@$(ECHO) "\033[32mNorm check completed\033[0m"

tests: $(NAME)
	$(TEST_DIR)/test_pipex.sh
	@$(ECHO) "\033[32mTest completed\033[0m"

doxygen:
	$(DOXYGEN) $(DOXYGEN_CONFIG)
	@$(ECHO) "\033[32mDoxygen generated\033[0m"

dist: fclean
	$(MKDIR) $(DIST_DIR)
	$(CP) $(SRCS_DIR) $(INCS_DIR) $(LIBS_DIR) $(DIST_DIR)
	$(CP) Makefile $(DIST_DIR)
	$(SED) 's|^NAME = $$(BINS_DIR)/pipex$$|NAME = pipex|' $(DIST_DIR)/Makefile
	$(SED) '/^\$$(NAME):/ s/ | $$(BINS_DIR)//' $(DIST_DIR)/Makefile
	@$(ECHO) "\033[32mDistribution files copied\033[0m"

.PHONY: all clean fclean re norm test doxygen dist
# ---------------------------------------------------------------------------- #
