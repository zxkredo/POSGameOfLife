CC = g++
CFLAGS = -Wall -Isource_files
LDFLAGS = -lws2_32

# Directories
SRC_DIR = source_files
BUILD_DIR = build

# List all source files excluding main.cpp
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS := $(filter-out $(SRC_DIR)/main.cpp, $(SRCS))

# Output executable name
EXECUTABLE = client.exe
TARGET = $(BUILD_DIR)/$(EXECUTABLE)

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SRCS) main.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)
