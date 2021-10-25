CXX=g++
CPPFLAGS=-I./include -I./include/glad
LDFLAGS=-lglfw -lX11 -lpthread -lXrandr -lXi -ldl

SOURCE=\
       src/main.cpp \
       src/glad/glad.cpp
OBJECTS=$(SOURCE:src/%.cpp=obj/%.o)

SHADERS =\
	 default.vert

default: clean main test

include/%.h: src/%.h
	@mkdir -p $(dir $@)
	cp $< $@

obj/%.o: src/%.cpp
	@echo "Compiling $< > $@"
	@mkdir -p $(dir $@)
	@scripts/extract_headers $< | xargs make -s
	@$(CXX) $(CPPFLAGS) -o $@ -c $<

main: $(OBJECTS)
	@$(CXX) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

test: main
	@./main

clean:
	@rm -rf obj include
	@rm -f main *.d *.o

.PHONY: test clean default