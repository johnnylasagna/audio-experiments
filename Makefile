CXX      = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS  = -lraylib -lopengl32 -lgdi32 -lwinmm
PROJECTS = piano filters waves

.PHONY: all clean $(PROJECTS)

all: $(PROJECTS)

$(PROJECTS):
	@echo === Building $@ ===
	$(CXX) $(CXXFLAGS) \
		$@/src/*.cpp \
		-o $@/bin/program.exe \
		$(LDFLAGS)

clean:
	@for %%p in ($(PROJECTS)) do del /Q %%p\bin\*.exe 2>nul