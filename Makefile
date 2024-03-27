# Kompilator
CXX = g++

# Flagi kompilacji
CXXFLAGS = -std=c++11 -Wall

# Biblioteki
LIBS = -lGLEW -lglfw -lGL -lX11 -lXrandr -lXi -lXinerama -lXxf86vm -lXcursor -ldl -lpthread

# Katalog z plikami źródłowymi
SRC_DIR = app
MOD_DIR = $(SRC_DIR)/mod

# Pliki źródłowe
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(MOD_DIR)/**/*.cpp)

# Pliki nagłówkowe
HDRS = $(wildcard $(SRC_DIR)/*.hpp) $(wildcard $(MOD_DIR)/**/*.hpp)

# Pliki obiektowe
OBJS = $(SRCS:.cpp=.o)

# Nazwa programu
TARGET = main.out

# Domyślne polecenie make
all: $(TARGET)

# Cel główny
$(TARGET): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)

# Reguła kompilacji plików źródłowych do obiektowych
%.o: %.cpp $(HDRS)
		$(CXX) $(CXXFLAGS) -c $< -o $@

# Czyszczenie plików tymczasowych
clean:
		rm -f $(OBJS) $(TARGET)
