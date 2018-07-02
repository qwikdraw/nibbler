# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: logan  <logan@42.us.org>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
#    Updated: 2018/06/20 22:45:48 by lkaser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ncurses.dylib
LIST = Ncurses

SRC_DIR = src
OBJ_DIR = obj

OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST)))
DEP = $(OBJ:%.o=%.d)
CC = clang++

CPPFLAGS = -std=c++14 -Wall -Wextra -Werror \
$(shell pkg-config --cflags glm) \
-O3 -march=native -flto -fPIC \
#-g -fsanitize=address -fsanitize=undefined

LDFLAGS = -flto -lncurses -dynamiclib \
$(shell pkg-config --libs glm) \
#-fsanitize=address -fsanitize=undefined

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@printf "\e[32;1mLinking.. \e[0m\n"
	@$(CC) $(LDFLAGS) -o $@ $^
	@printf "\e[32;1mCreated:\e[0m %s\n" $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@printf "\e[34;1mCompiling: \e[0m%s\n" $<
	@$(CC) $(CPPFLAGS) -MMD -c $< -o $@

clean:
	@printf "\e[31;1mCleaning..\e[0m\n"
	@rm -f $(OBJ) $(DEP)

fclean:
	@printf "\e[31;1mFull Cleaning..\e[0m\n"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re:	fclean all

.PHONY: clean fclean all re
