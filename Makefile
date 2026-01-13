TARGET_EXEC := game

BUILD_DIR := build
SRC_DIR := src
INC_DIR := include external/glfw/include

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_FLAGS := $(addprefix -I,$(INC_DIR))
CPPFLAGS := $(INC_FLAGS) -MMD -MP

LDFLAGS := external/glfw/lib/libglfw3.a -lGL -ldl -pthread

CXX := g++

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) -c $< -o $@

run: $(BUILD_DIR)/$(TARGET_EXEC)
	./$(BUILD_DIR)/$(TARGET_EXEC)

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
