NAME = fractol
INCLUDE = include
CC = cc
#CFLAGS = -Wall -Wextra -Werror -Ofast
CFLAGS = -Wall -Wextra -Werror -g -O3
FSANITIZE := -fsanitize=address
LIBMLX = ./lib/minilibx-linux
LIB_PRINTF = ./lib/ft_printf
HEADERS = -I./include -I$(LIBMLX) -I$(LIB_PRINTF)/includes
LIBS = $(LIB_PRINTF)/libftprintf.a $(LIBMLX)/libmlx.a -L$(LIBMLX) -lmlx -lXext -lX11 -lm
SRCS_DIR = ./srcs
SRCS = $(addprefix $(SRCS_DIR)/, main.c color.c render.c hooks.c utils.c \
	   console.c init.c)
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIB_PRINTF)
	$(MAKE) -C $(LIBMLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(HEADERS)

%.o: %.c
	$(CC) $(CFLAGS) -c $(HEADERS) -o $@ $<

clean:
	$(MAKE) clean -C $(LIB_PRINTF)
	$(MAKE) clean -C $(LIBMLX)
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) clean -C $(LIB_PRINTF)
	rm -f $(LIB_PRINTF)/libftprintf.a
	rm -f $(NAME)

re: fclean all
