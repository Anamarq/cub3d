# //= Variables =//

NAME	= cub3d
CFLAGS	= -Wall -Werror -Wextra -g #-fsanitize=address
LIBFT_PATH = libft/libft.a

MLX42_PATH = MLX42/libmlx42.a

HEADERS = -I ./includes
LIBS	= -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ $(LIBMLX)/libmlx42.a
SRCS	=	parser_init.c parser_error.c parser_utils.c parser.c \
			parser_txure_info.c parser_color_info.c parser_map.c \
			parser_map2.c parser_map3.c parser_file.c \
			cub3d.c draw_3D.c draw_2D.c utils_graphics.c colisions.c \
			casting2.c casting.c render.c loop.c initialize.c \
			initialize2.c
OBJS	= ${SRCS:.c=.o}

libmlx:
	@$(MAKE) -C $(LIBMLX)

all:	$(NAME)


#	We cannot call (LIBFT) or (MLX42) in (NAME) because it would be searching for the
#	".a" files before creating them, resulting in an error. We 1st create the rules to
#	compile both libft and MLX42, and then we compile the .a files of both libraries
#	with the apropiate flags and frameworks.

$(OFILES): obj/%.o: %.c
		@mkdir -p obj
		@$(CC) $(FLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OFILES) $(LIBFT_PATH) $(MLX42_PATH)
		$(CC) $(FLAGS) $(EXTRA) $(OFILES) $(LIBFT_PATH) $(MLX42_PATH) $(HEADERS) -o $(NAME)
		clear

$(LIBFT_PATH):
		make -C libft all

$(MLX42_PATH):
		make -C MLX42 all

# If a debug with lldb is needed, do 'make' with this rule:
debug: $(LIBFT_PATH) $(MLX42_PATH)
		$(CC) $(FLAGS) $(EXTRA) $(SRC) $(LIBFT_PATH) $(MLX42_PATH) -o $(NAME) -g
		clear

clean:
		rm -rf obj
		make -C libft clean
		# make -C MLX42 clean

fclean: clean
		@make fclean -C libft/
		# @make fclean -C MLX42/
		@rm -rf $(NAME)

re:	fclean all


.PHONY: all clean fclean re
