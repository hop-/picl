

default: coco pll

coco:	
	mkdir -p output
	./Coco picl.atg -frames frames -o output
pll:
	g++ main.cpp output/Scanner.cpp output/Parser.cpp -o $@

clean:
	rm -rf output
	rm -rf pll
