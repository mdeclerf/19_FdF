NAME	=	fdf

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror 

INCLUDE = -I./includes
LIBRARIES = -lmlx -L ./minilibx_macos/ -framework OpenGL -framework AppKit

SRCS_PS	=	free_array.c				\
			ft_atoi.c					\
			ft_split.c					\
			get_next_line_utils.c		\
			get_next_line.c				\
			matrice_rotation.c			\
			error_check.c				\
			parsing.c					\
			pixel_segment.c				\
			printing.c					\
			printing_black.c			\
			main.c						\
			keys.c						\
			len_height.c				\
			menu.c						\
			gradient.c 					\
			min_max.c					\

OBJS	=	$(SRCS_PS:.c=.o)

$(NAME):	$(OBJS) $(MINILIBX)
			@$(CC) $(CFLAGS) $(LIBRARIES) $(INCLUDES) $(OBJS) -o $(NAME)

all :		$(NAME)

clean:		
			@rm -f $(OBJS)
			
fclean:		clean
			@rm -f $(NAME)

re:			fclean all