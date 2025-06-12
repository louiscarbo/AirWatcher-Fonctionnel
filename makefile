# --------------------------
# CONFIGURATION
# --------------------------
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

SRC_DIRS = Data Model Services Presentation
BUILD_DIR = bin
TARGET    = $(BUILD_DIR)/airwatcher

# --------------------------
# AUTO-DETECTION DES .cpp
# --------------------------
SOURCES = main.cpp $(wildcard $(foreach dir,$(SRC_DIRS),$(dir)/*.cpp))
OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.cpp=.o)))

# --------------------------
# REGLES
# --------------------------
all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: Data/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: Model/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: Services/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: Presentation/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

reset: clean
	rm -rf $(BUILD_DIR)

.PHONY: all clean