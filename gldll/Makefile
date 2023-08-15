# Build, etc. the set of Libraries
#  - BUILD_DIR: build/<target_library>/
#  - SOURCE_DIR: <target_library>


BUILD_DIR  = ../build

TARGET = gldll
TARGET_LIB = ../bin/lib$(TARGET).a
TARGET_OBJ_DIR = $(BUILD_DIR)/$(TARGET)


$(TARGET_LIB) : $(TARGET_OBJ_DIR)/gldll.o $(TARGET_OBJ_DIR)/gldll_util.o
	ar rs $@ $(TARGET_OBJ_DIR)/gldll.o $(TARGET_OBJ_DIR)/gldll_util.o


$(TARGET_OBJ_DIR)/gldll.o : gldll.c _gldll_.h gldll.h
	mkdir -p $(TARGET_OBJ_DIR)
	gcc -g -c gldll.c -I . -o $@

$(TARGET_OBJ_DIR)/gldll_util.o : gldll_util.c _gldll_.h gldll.h
	mkdir -p $(TARGET_OBJ_DIR)
	gcc -g -c gldll_util.c -I . -o $@


.PHONY: clean
clean:
	rm -rf $(TARGET_OBJ_DIR) 

.PHONY: clean-all
clean-all:
	rm -rf $(TARGET_OBJ_DIR)
	rm $(TARGET_LIB)

