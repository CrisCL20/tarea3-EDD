all:
	g++ tarea4-LosNaufragos.cpp -o tarea4 -Wall -Wextra -Wpedantic
run:
	./tarea4 input.hubert
clean:
	rm tarea4