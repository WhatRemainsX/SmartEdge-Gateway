CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror -Icommon/include

TARGET = test_buffer_utils.exe

SOURCES = common/src/buffer_utils.c \
          tests/test_buffer_utils.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean