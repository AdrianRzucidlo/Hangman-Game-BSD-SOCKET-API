CC=g++
CPPFLAGS=-Wall -Wextra -c

all: hangman

hangman: sources/server.o \
sources/newPlayerHandler.o \
sources/lobby.o \
sources/letterPollEvent.o \
sources/informAboutStart.o \
sources/hangman.o \
sources/globalVariables.o \
sources/createServer.o \
sources/confirmName.o \
sources/confirmConnection.o \
sources/announceWinner.o \
sources/acceptLetters.o
	$(CC) $^ -pthread -o $@

sources/%.o: sources/%.cpp
	$(CC) $(CPPFLAGS) -lpthread $< -o $@

clean:
	rm sources/*.o

cleanall:
	rm sources/*.o hangman