NAME = server
CLIENT = client
INCLUDE = include
CC = cc
CFLAGS = -Wall -Wextra -Werror -O2
LIB_DIR = ./lib
PRINTF_DIR = $(LIB_DIR)/ft_printf
HEADERS = -I./$(INCLUDE) -I$(PRINTF_DIR)/$(INCLUDE)s
LIBS = $(PRINTF_DIR)/libftprintf.a
SRCS_DIR = ./srcs
SERVER_DIR = $(SRCS_DIR)/$(NAME)
CLIENT_DIR = $(SRCS_DIR)/$(CLIENT)
SRCS_SERVER = $(addprefix $(SERVER_DIR)/, main.c)
SRCS_CLIENT = $(addprefix $(CLIENT_DIR)/, main.c)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

all: $(NAME)

$(NAME): $(OBJS_SERVER) $(OBJS_CLIENT)
	$(MAKE) -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_SERVER) $(LIBS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLIENT) $(LIBS) $(HEADERS)

%.o: %.c
	$(CC) $(CFLAGS) -c $(HEADERS) -o $@ $<

clean:
	$(MAKE) clean -C $(PRINTF_DIR)
	rm -rf $(OBJS_SERVER)
	rm -rf $(OBJS_CLIENT)

fclean:
	$(MAKE) fclean -C $(PRINTF_DIR)
	rm -rf $(OBJS_SERVER)
	rm -rf $(OBJS_CLIENT)
	rm -rf $(NAME)
	rm -rf $(CLIENT)

re: fclean all
