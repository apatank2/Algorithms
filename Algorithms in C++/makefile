P=dynamic
Q=bruteForce
R=backtrack
S=huffman
all: $(P).out $(Q).out $(R).out $(S).out
$(P).out: $(P).cpp
	g++ $(P).cpp -o $(P).out
$(Q).out: $(Q).cpp
	g++ $(Q).cpp -o $(Q).out
$(R).out: $(R).cpp
	g++ $(R).cpp -o $(R).out
$(S).out: $(S).cpp
	g++ $(S).cpp -o $(S).out
clean:
	rm -rf $(P) $(Q) $(R) $(S) *.out