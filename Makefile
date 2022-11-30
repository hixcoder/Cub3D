# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 10:29:55 by hboumahd          #+#    #+#              #
#    Updated: 2022/11/30 13:29:46 by lahammam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BONUS = cub3D_bonus

# madatory
SRC_FOLDER = ./src/
SRC = main.c error.c check_map/map.c check_map/map_check.c check_map/ft_verifie_utils.c check_map/ft_verifie.c check_map/fill_data.c \
		draw/draw_map.c draw/draw_player.c rays_casting/ray_cast.c \
		hook.c wall_rendring/wall_render.c texture_fct/color.c wall_rendring/texture.c
		
SRCS = $(addprefix $(SRC_FOLDER), $(SRC))
SRCOBJ = ${SRCS:.c=.o}

GET_NEXT_LINE_FOLDER = ./src/get_next_line/
GET_NEXT_LINE_FILES = get_next_line.c get_next_line_utils.c
SRCS_GET_NEXT_LINE = $(addprefix $(GET_NEXT_LINE_FOLDER), $(GET_NEXT_LINE_FILES))

LIBFT_FOLDER = ./src/libft/
LIBFT_FILES =	ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_isprint.c\
					ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_itoa.c ft_atoi.c ft_putendl_fd.c\
					ft_strlcpy.c ft_tolower.c ft_bzero.c  ft_putnbr_fd.c ft_strlen.c\
					ft_toupper.c ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c\
					ft_memcmp.c ft_split.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c\
					ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c ft_striteri.c
SRCS_LIBFT = $(addprefix $(LIBFT_FOLDER), $(LIBFT_FILES))

OTHER_SRCS = $(SRCS_FT_PRINTF) $(SRCS_GET_NEXT_LINE) $(SRCS_LIBFT)
OTHER_OBJ = ${OTHER_SRCS:.c=.o}

LIBS = ./src/get_next_line.a ./src/libft.a

INCLUDES = ./src/cub3D.h ./src/get_next_line/get_next_line.h ./src/libft/libft.h

# -g for the debugger
FLAGS = -Wall -Wextra -Werror -g
CC = cc 

%.o : %.c ${INCLUDES}
	$(CC) ${FLAGS} -Imlx -c $< -o $@ 
	
$(NAME) : ${SRCOBJ} $(OTHER_SRCS) ${INCLUDES}
	@$(MAKE) -C $(GET_NEXT_LINE_FOLDER)
	@$(MAKE) -C $(LIBFT_FOLDER)
	@$(CC) ${FLAGS} $(SRCOBJ) $(LIBS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "|+| make the get_next_line.a [${GREEN}DONE${RESET}]"
	@echo "|+| make the libft.a         [${GREEN}DONE${RESET}]"
	@echo "|+| make the $(NAME) program   [${GREEN}DONE${RESET}]"
	# clear

# @$(CC) ${FLAGS} $(SRCOBJ) $(LIBS) -o $(NAME)

bonus:
	@echo "did not make it yet!"

all : $(NAME)  

clean :
	@rm -f $(LIBS) $(OTHER_OBJ) $(SRCOBJ) $(SRCOBJ_B)

fclean : clean
	@rm -f ${NAME}

re : fclean all




# colors used
GREEN = \033[0;92m
RED = \033[0;91m
RESET = \033[0m