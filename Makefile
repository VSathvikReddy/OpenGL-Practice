TARGET_EXEC := game

BUILD_DIR := build
SRC_DIR := src
INC_DIR := include external/glfw/include external/glew/include

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_FLAGS := $(addprefix -I,$(INC_DIR))
CPPFLAGS := $(INC_FLAGS) -MMD -MP

LDFLAGS := \
	external/glew/lib/libGLEW.a \
	external/glfw/lib/libglfw3.a \
	-lGL -lX11 -lXrandr -lXi -lXcursor -lXinerama \
	-ldl -pthread

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

setup:
	@mkdir -p external

	@# ---- GLEW ----
	@if [ ! -d external/glew ]; then \
		echo "Cloning GLEW..."; \
		git clone https://github.com/nigels-com/glew.git external/glew; \
	else \
		echo "GLEW already cloned"; \
	fi
	cd external/glew && \
	make extensions && \
	make

	@# ---- GLFW ----
	@if [ ! -d external/glfw ]; then \
		echo "Cloning GLFW..."; \
		git clone https://github.com/glfw/glfw.git external/glfw; \
	else \
		echo "GLFW already cloned"; \
	fi
	cd external/glfw && \
	cmake -S . -B build \
		-DBUILD_SHARED_LIBS=OFF \
		-DGLFW_BUILD_WAYLAND=OFF \
		-DGLFW_BUILD_EXAMPLES=OFF \
		-DGLFW_BUILD_TESTS=OFF \
		-DGLFW_BUILD_DOCS=OFF && \
	cmake --build build && \
	mkdir -p lib && \
	cp build/src/libglfw3.a lib/

-include $(DEPS)
