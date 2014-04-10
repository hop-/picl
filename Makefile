
CXX ?= g++
COCO ?= ./Coco

opts ?=


atgName = picl.atg

exe = pcl

cocoOut = 	Parser.cpp \
		Parser.h \
		Scanner.cpp\
		Scanner.h

objs = 	Scanner.o\
	Parser.o\
	symbolTable.o 

default: $(exe)

debug: setDebug $(exe)

$(cocoOut): $(atgName)
	$(COCO) $(atgName) 

$(exe): $(cocoOut) $(objs) main.o
	$(CXX) $(opts) $(objs) main.o -o $@

%.o: %.cpp
	$(CXX) $(opts) -c $< -o $@

setDebug:
	$(eval opts += -g)

clean:
	rm -rf *.o
	rm -rf Scanner.h Parser.h
	rm -rf Scanner.cpp Parser.cpp
	rm -rf Scanner.*.old Parser.*.old
	rm -rf $(exe)
