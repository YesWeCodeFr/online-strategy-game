CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lprotobuf-c

SRCS = src/main.c \
       src/game_server.c \
	   src/player.c \
       src/protocol/protocol.c \
       src/protocol/generated/message_types.pb-c.c \
       src/protocol/generated/message_envelope.pb-c.c \
       src/protocol/generated/messages.pb-c.c \
       src/network/server.c

OBJS = $(SRCS:.c=.o)
TARGET = game-server

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) 