CXX=g++
CPPFLAGS=-I./include -std=c++17 -O3
LDFLAGS=-lglfw -lX11 -lpthread -lXrandr -lXi -ldl

# automatically copy every header file in the source directory into the include/ directory
HEADERS=$(subst src/,include/,$(shell find src -type f -name "*.h"))

SOURCE=\
       src/main.cpp \
       src/graphics/triangles.cpp \
       src/graphics/glad/glad.cpp \
       src/graphics/shader.cpp
OBJECTS=$(SOURCE:src/%.cpp=obj/%.o)

default: all

all: clean main test



include/%.h: src/%.h clean
	@echo "Copying $< > $@"
	@mkdir -p $(dir $@)
	@cp $< $@

headers: $(HEADERS) clean

obj/%.o: src/%.cpp headers
	@echo "Compiling $< > $@"
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) -o $@ -c $<

main: $(OBJECTS) clean
	@$(CXX) $(CPPFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

test: main clean
	@clear
	@./main

clean:
	@rm -rf obj include
	@rm -f main *.d *.o

.PHONY: all test clean default
