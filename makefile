CXX = g++
CXXFLAGS = -Wall -std=c++11
IFLAGS = -I include
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
TARGET = demigod
SRCSDIR = src
OBJSDIR = obj
SRCS = $(wildcard $(SRCSDIR)/*.cpp)
OBJS = $(patsubst $(SRCSDIR)/%.cpp,$(OBJSDIR)/%.o,$(SRCS))

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(OBJS) -o $(TARGET)

$(OBJSDIR)/%.o : $(SRCSDIR)/%.cpp
	mkdir -p $(OBJSDIR)
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf obj
	rm $(TARGET)
