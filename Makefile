# //= Variables =//

NAME	= cub3d
CFLAGS	= -Wall -Werror -Wextra
LIBMLX	= ./MLX42

HEADERS	= -I ./include -I $(LIBMLX)
LIBS	= -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ $(LIBMLX)/libmlx42.a
SRCS	= cub3d.c parser.c parser_error.c
OBJS	= ${SRCS:.c=.o}

LIBFT_PATH		= libft/libft.a

all: libmlx $(NAME)

libmlx:
	@$(MAKE) -C $(LIBMLX)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT_PATH)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT_PATH):
		make -C libft all

clean:
	@rm -f $(OBJS) $(LIBFT_PATH)
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -f $(NAME) $(LIBFT_OBJS) $(LIBFT)
	@$(MAKE) -C $(LIBMLX) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx