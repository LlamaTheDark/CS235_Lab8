all:
	g++ -std=c++11 -o lab9 *.cpp
win:
	cl /EHsc main.cpp Hashmap.cpp WordCounter.cpp

clean:
	rm -f details.txt
	rm -f turnin.txt
	rm -f out_file*.txt
	rm -f lab9
