NAME = minitalk
CLIENT_NAME = client
SERVER_NAME = server
CC = cc
CFLAGS = -Wall -Wextra -Werror
CLIENT_SRCS = client.c 
SERVER_SRCS = server.c 
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
FT_PRINTF_PATH = ./ft_printf
FT_PRINTF = $(FT_PRINTF_PATH)/libftprintf.a

all: $(FT_PRINTF) $(CLIENT_NAME) $(SERVER_NAME) 

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_PATH)

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(FT_PRINTF) -o $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(FT_PRINTF) -o $(SERVER_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(CLIENT_OBJS)
	rm -f $(SERVER_OBJS)
	$(MAKE) -C $(FT_PRINTF_PATH) clean

fclean: clean
	rm -f $(CLIENT_NAME)
	rm -f $(SERVER_NAME)
	$(MAKE) -C $(FT_PRINTF_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
