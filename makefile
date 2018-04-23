all:
		g++  Brute_Force.cpp -o bruteforce
		g++  Naive_Divide_And_Conquer.cpp -o divideandconquer
		g++  Enhanced_Divide_And_Conquer.cpp -o enhanceddnc

brute:
		rm -f  execution_time_Brute.txt
		rm -f  bruteforce output_bruteforce.txt
		g++  Brute_Force.cpp -o bruteforce

divide:
		rm -f  execution_time_divide.txt
		rm -f  divideandconquer output_divideandconquer.txt
		g++  Naive_Divide_And_Conquer.cpp -o divideandconquer

enhance:
		rm -f  execution_time_enhanced.txt
		rm -f  enhanceddnc output_enhanceddnc.txt
		g++  Enhanced_Divide_And_Conquer.cpp -o enhanceddnc

		
testBrute:

	./bruteforce 20e4.input
	./bruteforce 40e4.input
	./bruteforce 60e4.input
	./bruteforce 80e4.input
	./bruteforce 10e5.input
	
testDivide:

	./divideandconquer 10e5.input
	./divideandconquer 20e5.input
	./divideandconquer 30e5.input
	./divideandconquer 40e5.input
	./divideandconquer 50e5.input
	
testEnhanced:

	./enhanceddnc 10e5.input
	./enhanceddnc 20e5.input
	./enhanceddnc 30e5.input
	./enhanceddnc 40e5.input
	./enhanceddnc 50e5.input

clean:
		rm -f enhanceddnc divideandconquer bruteforce random
