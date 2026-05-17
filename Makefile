all:
	g++ app/main.cpp -o main

run: all
	./main

clean:
	rm -f main