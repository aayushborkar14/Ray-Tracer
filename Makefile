BUILD_DIR := ./bin
SRC_DIR := ./src
LIB_DIR := ./lib
LIBS := $(wildcard $(LIB_DIR)/*.cpp)
LIB_OBJS := $(patsubst $(LIB_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(LIBS))

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
IMAGES := $(patsubst $(SRC_DIR)/image%.cpp, image%, $(SRCS))
PPMS := $(IMAGES:%=%.ppm)

CXXFLAGS := -Iinclude

all: $(PPMS)

$(IMAGES): %: %.ppm

%.ppm: $(BUILD_DIR)/%.exe
	.\$(subst /,\,$<) > $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.exe: $(BUILD_DIR)/%.o $(LIB_OBJS) | $(BUILD_DIR)
	$(CXX) $^ -o $@

$(BUILD_DIR):
	mkdir $(subst /,\,$(BUILD_DIR))

cleanppm:
	rm -f *.ppm

cleanlib:
	rm -f $(LIB_OBJS)

cleansrc:
	rm -f $(SRC_OBJS)
	rm -f $(BUILD_DIR)/*.exe

clean: cleanppm cleanlib cleansrc

.SECONDARY: # don't delete intermediate files 
