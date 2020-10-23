BIN = main
CALC = tools/precalculator

CXXFLAGS = -std=c++17 -O2 -Wall -g

# SDL
CXXFLAGS += `sdl2-config --cflags`
LDFLAGS += `sdl2-config --libs`

# Control the build verbosity
ifeq ("$(VERBOSE)","1")
    Q :=
    VECHO = @true
else
    Q := @
    VECHO = @printf
endif

GIT_HOOKS := .git/hooks/applied
.PHONY: all clean

all: $(GIT_HOOKS) $(BIN)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo
	
OBJS := \
	game.o \
	raycaster_fixed.o \
	raycaster_float.o \
	renderer.o \
	main.o
deps := $(OBJS:%.o=.%.o.d)

raycaster_fixed.o: raycaster_fixed.cpp raycaster_tables.h
	$(VECHO) "  CXX\t$@\n"
	$(Q)$(CXX) -o $@ $(CXXFLAGS) -c -MMD -MF .$@.d raycaster_fixed.cpp

%.o: %.cpp
	$(VECHO) "  CXX\t$@\n"
	$(Q)$(CXX) -o $@ $(CXXFLAGS) -c -MMD -MF .$@.d $<

$(BIN): $(OBJS)
	$(Q)$(CXX)  -o $@ $^ $(LDFLAGS)

$(CALC): defs.h tools/precalculator.cpp tools/precalculator.h
	$(VECHO) "  CXX\t$@\n"
	$(Q)$(CXX) -o $@ $(CXXFLAGS) tools/precalculator.cpp


raycaster_tables.h: $(CALC)
	echo "#pragma once" > $@
	$^ >> $@

clean:
	$(RM) $(BIN) $(OBJS) $(deps) $(CALC) raycaster_tables.h

-include $(deps)
