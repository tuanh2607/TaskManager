ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE = .exe
else
    RM = rm -f
    EXE =
endif

all:
	g++ app/main.cpp -o TaskManager$(EXE)

run: all
	./TaskManager$(EXE) app/data.txt

clean:
	$(RM) TaskManager$(EXE)