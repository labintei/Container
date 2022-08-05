# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: labintei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 15:22:59 by labintei          #+#    #+#              #
#    Updated: 2022/08/04 15:29:01 by labintei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_V	= ./test/vector.cpp
#SRCS_V = ./test/newvector.cpp
SRCS_ST = ./test/stack.cpp
SRCS_M	= ./test/map.cpp
SRCS_S  = ./test/set.cpp
SRCS_T  = ./test/test.cpp

STD = -D STD=1 #va definir STD comme egale a un et tout compiler

CCP		= c++

RM		= rm -fr

CFLAGS	= -Wall -std=c++98 -Werror -Wextra
CSTD = -D STD=1


#all:
#	vector map stack set

test:
	@$(CCP) $(CFLAGS) $(SRCS_T) -o test.out

vector:
	@$(CCP) $(CFLAGS) $(SRCS_V) -o ft_vector.out
	@$(CCP) $(CFLAGS) $(CSTD) $(SRCS_V) -o std_vector.out

map:
	@$(CCP) $(CFLAGS) $(SRCS_M) -o map.out

stack:
	@$(CCP) $(CFLAGS) $(SRCS_ST) -o stack.out

set:
	@$(CCP) $(CFLAGS) $(SRCS_S) -o set.out

clean:
					$(RM) ${OBJS}

all:
	vector map stack set
