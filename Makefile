CXX = g++
CXXFLAGS = -std=c++17 -Wall -I
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

PROJECTS = piano filters

.PHONY: all clean $(PROJECTS)

$(PROJECTS):
	@echo Building $@
	$(CXX) $(CXXFLAGS)$@/include \
		$@/src/*.cpp \
		-o $@/bin/program.exe \
		$(LDFLAGS)

all: $(PROJECTS)

clean:
	@for %%p in ($(PROJECTS)) do del /Q %%p\bin\*.exe 2>nul