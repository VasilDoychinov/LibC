# Build, etc. the set of Libraries
#  - BUILD_DIR: build/<target_library>/
#  - SOURCE_DIR: <target_library>


BUILD_DIR  = ../build

TARGET = dll
TARGET_LIB = ../bin/lib$(TARGET).a
TARGET_OBJ_DIR = $(BUILD_DIR)/$(TARGET)


$(TARGET_LIB) : $(TARGET_OBJ_DIR)/dll.o $(TARGET_OBJ_DIR)/dll_util.o
	ar rs $@ $(TARGET_OBJ_DIR)/dll.o $(TARGET_OBJ_DIR)/dll_util.o


$(TARGET_OBJ_DIR)/dll.o : dll.c _dll_.h dll.h
	mkdir -p $(TARGET_OBJ_DIR)
	gcc -g -c dll.c -I . -o $@


$(TARGET_OBJ_DIR)/dll_util.o : dll_util.c
	gcc -g -c dll_util.c -o $@


.PHONY: clean
clean:
	rm -rf $(TARGET_OBJ_DIR) 

.PHONY: clean-all
clean-all:
	rm -rf $(TARGET_OBJ_DIR)
	rm $(TARGET_LIB)

