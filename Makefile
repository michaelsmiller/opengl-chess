CXX=g++
CPPFLAGS=-I./include
LDFLAGS=-lglfw -lX11 -lpthread -lXrandr -lXi -ldl

# automatically copy every header file in the source directory into the include/ directory
HEADERS=$(subst src/,include/,$(shell find src -type f -name "*.h"))

SOURCE=\
       src/main.cpp \
       src/graphics/triangles.cpp \
       src/graphics/glad/glad.cpp
OBJECTS=$(SOURCE:src/%.cpp=obj/%.o)

default: clean main test

include/%.h: src/%.h
	@echo "Copying $< > $@"
	@mkdir -p $(dir $@)
	@cp $< $@

headers: $(HEADERS)

obj/%.o: src/%.cpp headers
	@echo "Compiling $< > $@"
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) -o $@ -c $<

main: $(OBJECTS)
	@$(CXX) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

test: main
	@clear
	@./main

clean:
	@rm -rf obj include
	@rm -f main *.d *.o

.PHONY: test clean default
