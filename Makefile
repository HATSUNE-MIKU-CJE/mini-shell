CFLAGS = -Wall -g
SRCS = main.c parser.c executor.c builtin.c readline.c
OBJS = $(SRCS:.c=.o)
TARGET = mini-shell

$(TARGET): $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
