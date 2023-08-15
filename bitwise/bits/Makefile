# Build, etc. the set of Libraries
#  - BUILD_DIR: build/<target_library>/
#  - TARGET Library: 
#

BUILD_DIR  = ../build

TARGET = bits
TARGET_LIB = ../bin/lib$(TARGET).a
TARGET_OBJ_DIR = $(BUILD_DIR)/$(TARGET)


$(TARGET_LIB) : $(TARGET_OBJ_DIR)/bitsop.o
	ar rs $@ $(TARGET_OBJ_DIR)/bitsop.o


$(TARGET_OBJ_DIR)/bitsop.o : bitsop.c bitsop.h
	mkdir -p $(TARGET_OBJ_DIR)
	gcc -g -c bitsop.c -I . -o $@


.PHONY: clean
clean:
	rm -rf $(TARGET_OBJ_DIR) 

.PHONY: clean-all
clean-all:
	rm -rf $(TARGET_OBJ_DIR)
	rm $(TARGET_LIB)

