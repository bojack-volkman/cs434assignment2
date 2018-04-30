all:
		g++  part1.cpp -o part1
		g++  part1loo.cpp -o part1loo

clean:
		rm -f  part1 output.csv part1loo
