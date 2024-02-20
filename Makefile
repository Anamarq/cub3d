# //= Variables =//

NAME	= cub3d
CFLAGS	= -Wall -Werror -Wextra
LIBMLX	= ./MLX42

HEADERS	= -I ./include -I $(LIBMLX)
LIBS	= -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ $(LIBMLX)/libmlx42.a
SRCS	=	cub3d.c parser_init.c parser_error.c parser_utils.c false_main.c \
			parser_txure_info.c parser_color_info.c parser_map.c \
			parser_map2.c
OBJS	= ${SRCS:.c=.o}

LIBFT_PATH		= libft/libft.a

all: libmlx $(NAME)

libmlx:
	@$(MAKE) -C $(LIBMLX)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT_PATH)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(LIBFT_PATH) -o $(NAME)

$(LIBFT_PATH):
		make -C libft all

clean:
	@rm -f $(OBJS)
	make -C libft clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBMLX) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx