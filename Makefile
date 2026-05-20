all:
	g++ app/main.cpp -o main

run: all
	./main app/data.txt

clean:
	rm -f main