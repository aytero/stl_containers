NAME		=	out
CPPC		=	clang++
FLAGS		=	-std=c++98 -Wall -Werror -Wextra -Wshadow -g #-Wno-shadow

SRCS_DIR	=	.
SRCS_LIST	=	main.cpp
SRCS		=	$(addprefix $(SRCS_DIR)/, $(SRCS_LIST))
HEADERS		=	.
OBJS_DIR	=	./build
OBJS		=	$(SRCS:%.cpp=$(OBJS_DIR)/%.o)
DEPS		=	$(SRCS:%.cpp=$(OBJS_DIR)/%.d)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp Makefile
	@mkdir -p $(@D)
	$(CPPC) $(FLAGS) -MMD -c $< -o $@ -I$(HEADERS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPPC) $(FLAGS) $(OBJS) -o $(NAME) -I$(HEADERS)

#st: $(OBJS)
#	$(CPPC) $(FLAGS) -D ST $(OBJS) -o $(NAME) -I$(HEADERS)

l:
	leaks -atExit -- ./$(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(DEPS)
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "fclean"
-include $(DEPS)
endif
endif
