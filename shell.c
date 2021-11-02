//Name: Rayan Bouamrane
//ID: 260788250

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "shell.h"

#define PROMPT "$ "

char rawString[STRING_LENGTH];
char processedString[STRING_LENGTH];
char *parsedString[3];

int parse();
void printError(int e);

int main() {

	printf("Welcome to Rayan's Shell\n");
	printf("Version 1.0 Created January 2020\n");

	while (1) {

		memset(rawString, 0, STRING_LENGTH);

		printf(PROMPT);

		char ch;
		for (int i = 0; i < STRING_LENGTH; i++) {
			ch = getchar();

			if (ch == '\n')
				break;

			rawString[i] = ch;

		}

		while (ch != '\n') {
			ch = getchar(); 		//consume rest of stdin
		}

		parse(rawString);
	}
}

int parse(char rawStr[]) {

	memset(processedString, 0, STRING_LENGTH);

	if (rawStr[0] == '\0') {
		return 0;
	}

	if (rawStr[STRING_LENGTH - 1] != '\0') {
		return 6;
	}

	int p = 0;
	for (int r = 0; r < STRING_LENGTH; r++) {
		if (rawStr[r] != '\r') {
			processedString[p] = rawStr[r];
			p++;
		}
	}

	parsedString[0] = strtok(processedString, " " "\n");
	parsedString[1] = strtok(NULL, " " "\n");
	parsedString[2] = strtok(NULL, "\n" "\0");

	int errCode = (interpreter(parsedString));
	printError(errCode);
	return errCode;
}

void printError(int e) {
	if (e == 1)
		printf("Unknown command\n");
	else if (e == 2)
		printf("Too few arguments\n");
	else if (e == 3)
		printf("Too many arguments\n");
	else if (e == 4)
		printf("Variable does not exist\n");
	else if (e == 5)
		printf("Low Disk Space\n");
	else if (e == 6)
		printf("Max String length exceeded\n");
	else if (e == 7)
		printf("Script not found\n");
	else if (e == 8) {
		printf("Too many open files, shell terminated\n");
		exit(24);
	} else if (e == 9) {
		printf("Script Terminated\n");
	}
}
