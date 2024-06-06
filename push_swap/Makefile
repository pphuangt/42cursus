NAME = push_swap
BONUS_NAME = checker
INCLUDES = includes
PRINTF_DIR = ft_printf
PRINTF_FLAG = -L$(PRINTF_DIR) -lftprintf
LIBFTPRINTF = $(PRINTF_DIR)/libftprintf.a
CFLAGS = -Wall -Wextra -Werror
CC = cc
SRCS_DIR = ./srcs
SRCS = $(addprefix $(SRCS_DIR)/, analyze.c chunk_a.c chunk_b.c chunk_utils.c \
	   main.c push.c r_rotate.c sort.c swap.c cmd_utils.c print.c rotate.c setup.c \
	   stack_utils.c input_utils.c is_sort.c)
SRCS_BONUS = $(addprefix $(SRCS_DIR)/, checker.c setup.c stack_utils.c \
			 input_utils.c print.c cmd_utils.c \
			 get_next_line_bonus.c get_next_line_utils_bonus.c \
			 swap.c push.c rotate.c r_rotate.c is_sort.c)
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(LIBFTPRINTF) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PRINTF_FLAG)

$(BONUS_NAME): $(LIBFTPRINTF) $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(OBJS_BONUS) $(PRINTF_FLAG)

$(LIBFTPRINTF):
	$(MAKE) -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c -I $(INCLUDES) -I$(PRINTF_DIR)/$(INCLUDES) -o $@ $<

clean:
	$(MAKE) -C $(PRINTF_DIR) clean
	rm -f $(OBJS_BONUS)
	rm -f $(OBJS)

fclean:
	$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all
