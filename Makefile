CXX=g++-10
CPPFLAGS=-I./include -std=c++20 -O3 -fno-diagnostics-color -Werror=all
LDFLAGS=-lglfw -lX11 -lpthread -lXrandr -lXi -ldl

# Shader compilation happens in SPIR-V
GLSLC=glslc
GLSLFLAGS=--target-env=opengl -fauto-map-locations

# automatically copy every header file in the source directory into the include/ directory
HEADERS=$(subst src/,include/,$(shell find src -type f -name "*.h"))

SOURCE=\
       src/main.cpp \
       src/graphics/renderer.cpp \
       src/graphics/glad/glad.cpp \
       src/graphics/shader.cpp
OBJECTS=$(SOURCE:src/%.cpp=obj/%.o)

SHADERS=\
	shaders/default.vert \
	shaders/default.frag
# e.g. shaders/filename.frag => obj/shaders/filename.frag.spv
SHADEROBJECTS=$(SHADERS:%=obj/%.spv)

BINDIR=bin

default: all

all: clean main test



include/%.h: src/%.h clean
	@echo "Copying $< > $@"
	@mkdir -p $(dir $@)
	@cp $< $@

headers: $(HEADERS) clean

# Compiling requires already having /include populated for the project
obj/%.o: src/%.cpp headers
	@echo "Compiling $< > $@"
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) -o $@ -c $<

# For compiling shaders into the SPIR-V binary format
obj/shaders/%.spv: shaders/%
	@echo "Compiling $< > $@"
	@mkdir -p $(dir $@)
	@$(GLSLC) $(GLSLFLAGS) -o $@ $<

main: $(OBJECTS) $(SHADEROBJECTS) clean
	@$(CXX) $(CPPFLAGS) -o $(BINDIR)/$@ $(OBJECTS) $(LDFLAGS)

test: main clean
	@clear
	@$(BINDIR)/main

clean:
	@rm -rf obj include
	@rm -f main *.d *.o
	@rm -f $(BINDIR)/*

.PHONY: all test clean default main
