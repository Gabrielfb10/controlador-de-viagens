CXX = g++
CXXFLAGS = -I headers -Wall -Wextra -std=c++17
SRC = $(wildcard sources/*.cpp)
TARGET = controlador_viagens

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) $(TARGET).exe
	@echo "Se o comando rm falhar no Windows, use: del /Q /F $(TARGET).exe"

run: $(TARGET)
	./$(TARGET)
