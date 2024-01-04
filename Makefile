CC = cc
CFLAGS = -Wall -Wextra -Wextra

CLIENT_SRC = client.c
SERVER_SRC = server.c
CLIENT_BSRC = client_bonus.c
SERVER_BSRC = server_bonus.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_BOBJ = $(CLIENT_BSRC:.c=.o)
SERVER_BOBJ = $(SERVER_BSRC:.c=.o)

CLIENT_TARGET = client
SERVER_TARGET = server
CLIENT_BTARGET = client_bonus
SERVER_BTARGET = server_bonus

all: $(CLIENT_TARGET) $(SERVER_TARGET)

bonus: $(CLIENT_BTARGET) $(SERVER_BTARGET)

$(CLIENT_BTARGET): $(CLIENT_BOBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER_BTARGET): $(SERVER_BOBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_TARGET): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER_TARGET): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o

fclean: clean
	rm -f $(CLIENT_TARGET) $(SERVER_TARGET) $(CLIENT_BTARGET) $(SERVER_BTARGET)

re: fclean all

.PHONY: all clean fclean re bonus