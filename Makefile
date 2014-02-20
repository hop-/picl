
CXX ?= g++
COCO ?= ./Coco


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

$(cocoOut): $(atgName)
	$(COCO) $(atgName) 

$(exe): $(cocoOut) $(objs) main.o
	$(CXX) $(objs) main.o -o $@

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf Scanner.h Parser.h
	rm -rf Scanner.cpp Parser.cpp
	rm -rf Scanner.*.old Parser.*.old
	rm -rf $(exe)
