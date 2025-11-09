CC ?= clang
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -O2
SRCS = $(wildcard mental/*.c mental/*/*.c)
OBJS = $(SRCS:.c=.o)
TARGET = mental

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@test -f $(TARGET) && rm -f $(TARGET) || true

analyze:
	clang-tidy $(SRCS) --checks='-*,clang-analyzer-*,performance-*,portability-*'

memcheck: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

