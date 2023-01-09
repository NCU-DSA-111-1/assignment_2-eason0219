
johnchi: src/main.c johnchi.o timer.o
	gcc src/main.c build/johnchi.o build/timer.o -lev -o bin/johnchi

johnchi.o: src/johnchi.c
	gcc -c src/johnchi.c -o build/johnchi.o

timer.o: src/timer.c
	gcc -c src/timer.c -o build/timer.o

run:
	./bin/johnchi -n -s new_game.txt

review:
	./bin/johnchi -l new_game.txt
clean:
	rm *.o main
