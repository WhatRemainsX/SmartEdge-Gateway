
CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror -Icommon/include

DAY1_TARGET = test_buffer_utils.exe
DAY2_TARGET = test_day2.exe

DAY1_SOURCES = common/src/buffer_utils.c \
               tests/test_buffer_utils.c

DAY2_SOURCES = common/src/bit_utils.c \
               common/src/byte_order.c \
               tests/test_day2.c

all: $(DAY1_TARGET) $(DAY2_TARGET)

$(DAY1_TARGET): $(DAY1_SOURCES)
	$(CC) $(CFLAGS) $(DAY1_SOURCES) -o $(DAY1_TARGET)

$(DAY2_TARGET): $(DAY2_SOURCES)
	$(CC) $(CFLAGS) $(DAY2_SOURCES) -o $(DAY2_TARGET)

run: all
	./$(DAY1_TARGET)
	./$(DAY2_TARGET)

run-day1: $(DAY1_TARGET)
	./$(DAY1_TARGET)

run-day2: $(DAY2_TARGET)
	./$(DAY2_TARGET)

clean:
	rm -f $(DAY1_TARGET) $(DAY2_TARGET)

.PHONY: all run run-day2 clean