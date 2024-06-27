BUILD_DIR := ./bin
SRC_DIR := ./src
LIB_DIR := ./lib
IMAGE_DIR := ./images
LIBS := $(wildcard $(LIB_DIR)/*.cpp)
LIB_OBJS := $(patsubst $(LIB_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(LIBS))

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
IMAGES := $(patsubst $(SRC_DIR)/image%.cpp, image%, $(SRCS))
PPMS := $(patsubst image%, $(IMAGE_DIR)/image%.ppm, $(IMAGES))

CXXFLAGS := -Iinclude -std=c++20

all: $(PPMS)

$(IMAGES): %: $(IMAGE_DIR)/%.ppm

$(IMAGE_DIR)/%.ppm: $(BUILD_DIR)/% | $(IMAGE_DIR)
	$< > $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%: $(BUILD_DIR)/%.o $(LIB_OBJS) | $(BUILD_DIR)
	$(CXX) $^ -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(IMAGE_DIR):
	mkdir $(IMAGE_DIR)

cleanppm:
	rm -f $(IMAGE_DIR)/*.ppm

cleanlib:
	rm -f $(LIB_OBJS)

cleansrc:
	rm -f $(SRC_OBJS)
	rm -f $(BUILD_DIR)/*

clean: cleanppm cleanlib cleansrc

.SECONDARY: # don't delete intermediate files 
