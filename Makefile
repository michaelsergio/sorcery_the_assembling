CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
# LDLIBS=-L/usr/local/include/opencv2
LDLIBS=-lopencv_core -lopencv_highgui -lopencv_imgproc

SRCS=detect.cc
OBJS=$(subst .cc,.o,$(SRCS))
EXE=mtg.exe

all: mtg

mtg: $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(LDLIBS)

detect.o: detect.cc

clean:
	$(RM) $(OBJS) $(EXE)
run: mtg
	./$(EXE)
