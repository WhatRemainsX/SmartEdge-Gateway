
CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror -Icommon/include

DAY1_TARGET = test_buffer_utils.exe
DAY2_TARGET = test_day2.exe
CRC_TARGET = test_crc16.exe
RING_BUFFER_TARGET = test_ring_buffer.exe
PROTOCOL_TARGET = test_protocol.exe


DAY1_SOURCES = common/src/buffer_utils.c \
               tests/test_buffer_utils.c

DAY2_SOURCES = common/src/bit_utils.c \
               common/src/byte_order.c \
               tests/test_day2.c

CRC_SOURCES = common/src/crc16.c \
              tests/test_crc16.c


RING_BUFFER_SOURCES = common/src/ring_buffer.c \
                      tests/test_ring_buffer.c


PROTOCOL_SOURCES = common/src/protocol.c \
				   common/src/byte_order.c \
				   common/src/crc16.c \
				   tests/test_protocol.c




all: $(DAY1_TARGET) $(DAY2_TARGET) $(CRC_TARGET) $(RING_BUFFER_TARGET) $(PROTOCOL_TARGET)

$(DAY1_TARGET): $(DAY1_SOURCES)
	$(CC) $(CFLAGS) $(DAY1_SOURCES) -o $(DAY1_TARGET)

$(DAY2_TARGET): $(DAY2_SOURCES)
	$(CC) $(CFLAGS) $(DAY2_SOURCES) -o $(DAY2_TARGET)

$(CRC_TARGET): $(CRC_SOURCES)
	$(CC) $(CFLAGS) $(CRC_SOURCES) -o $(CRC_TARGET)

$(RING_BUFFER_TARGET): $(RING_BUFFER_SOURCES)
	$(CC) $(CFLAGS) $(RING_BUFFER_SOURCES) -o $(RING_BUFFER_TARGET)

$(PROTOCOL_TARGET): $(PROTOCOL_SOURCES)
	$(CC) $(CFLAGS) $(PROTOCOL_SOURCES) -o $(PROTOCOL_TARGET)

run: all
	./$(DAY1_TARGET)
	./$(DAY2_TARGET)
	./$(CRC_TARGET)
	./$(RING_BUFFER_TARGET)
	./$(PROTOCOL_TARGET)

run-day1: $(DAY1_TARGET)
	./$(DAY1_TARGET)

run-day2: $(DAY2_TARGET)
	./$(DAY2_TARGET)

run-crc: $(CRC_TARGET)
	./$(CRC_TARGET)

run-ring-buffer: $(RING_BUFFER_TARGET)
	./$(RING_BUFFER_TARGET)

run-protocol: $(PROTOCOL_TARGET)
	./$(PROTOCOL_TARGET)

clean:
	rm -f $(DAY1_TARGET) $(DAY2_TARGET) $(CRC_TARGET) $(RING_BUFFER_TARGET) $(PROTOCOL_TARGET)

.PHONY: all run run-day1 run-day2 run-crc run-ring-buffer run-protocol clean