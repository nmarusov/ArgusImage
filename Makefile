TARGET=ArgusImage.out

CXX=g++
MKDIR=mkdir
RM=rm

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CXXFLAGS=-g3 -gdwarf-2 -DDEBUG
else
	CXXFLAGS=-DNDEBUG
endif

LDFLAGS=
SRC_DIR=src
BUILD_DIR=build
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o))

# .PHONY: ImageMagick
# ImageMagick:
# 	echo "Building ImageMagick..."
# 	git submodule update
# 	cd ./ImageMagick && ./configure --enable-delegate-build --disable-shared --disable-installed --enable-static --without-modules --with-zero-configuration
# 	make
# 	echo "ImageMagick built."

all: clean $(TARGET)  #ImageMagick

$(TARGET): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(BUILD_DIR)
	
.PHONY: all clean
