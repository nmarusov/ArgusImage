TARGET=ArgusImage.out

CXX=g++
MKDIR=mkdir
RM=rm

SRC_DIR=src
BUILD_DIR=build
IM_DIR=./ImageMagick

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CXXFLAGS=-g3 -gdwarf-2 -DDEBUG
else
	CXXFLAGS=-DNDEBUG
endif

LDFLAGS+=$(shell pkg-config --libs Magick++)
LDFLAGS+=-lgomp -pthread
CXXFLAGS+=$(shell pkg-config --cflags Magick++)

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o))

ImageMagick:
	echo "Building ImageMagick..."
	git submodule update
	cd ./ImageMagick && ./configure --enable-delegate-build --disable-shared
	make clean && make -C $(IM_DIR) && make -C $(IM_DIR) install
	echo "ImageMagick installed."

all: purge ImageMagick $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(BUILD_DIR)

purge:
	$(RM) -rf $(BUILD_DIR) $(TARGET) $(IM_DIR)

test:
	echo "Building tests..."

.PHONY: all clean purge test ImageMagick
