//Name: Rayan Bouamrane
//ID: 260788250

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shellmemory.h"
#include "shell.h"

char *parsedString[3];

int help();
int print(char *pVar);
int set(char *pVar, char *pValue);
int run(char *filename);
void quit();

int interpreter(char *parsedString[]) {

	if (parsedString[0] == NULL) {
		return 0;

	} else if (strcmp(parsedString[0], "help") == 0) {
		if (parsedString[1] != NULL || parsedString[2] != NULL)
			return 3;
		return help();

	} else if (strcmp(parsedString[0], "quit") == 0) {
		if (parsedString[1] != NULL || parsedString[2] != NULL)
			return 3;
		quit();

	} else if (strcmp(parsedString[0], "print") == 0) {
		if (parsedString[1] == NULL) {
			return 2;
		}
		if (parsedString[2] != NULL)
			return 3;

		return print(parsedString[1]);

	} else if (strcmp(parsedString[0], "set") == 0) {
		if (parsedString[1] == NULL || parsedString[2] == NULL) {
			return 2;
		}
		return set(parsedString[1], parsedString[2]);

	} else if (strcmp(parsedString[0], "run") == 0) {
		if (parsedString[1] == NULL) {
			return 2;
		}
		if (parsedString[2] != NULL)
			return 3;

		return run(parsedString[1]);

	}
	return 1;
}

int help() {
	printf("COMMAND\t\t\tDESCRIPTION\n"
			"help\t\t\tDisplays all the commands\n"
			"quit\t\t\tExits / terminates the shell with “Bye!”\n"
			"set VAR STRING\t\tAssigns a value to shell memory\n"
			"print VAR\t\tDisplays the STRING assigned to VAR\n"
			"run SCRIPT.TXT\t\tExecutes the file SCRIPT.TXT\n");
	return 0;
}

void quit() {
	printf("Bye!\n");

	exit(EXIT_SUCCESS);
}

int print(char *pVar) {
	char *temp = getValue(pVar);
	if (temp != NULL) {
		printf("%s\n", temp);
		return 0;
	}
	return 4;
}

int set(char *pVar, char *pValue) {
	return copyToMemory(pVar, pValue);
}

int run(char *filename) {

	FILE *pFile = fopen(filename, "r");
	if (pFile == NULL) {
		if (errno == 2)
			return 7;
		if (errno == 24)
			return 8;
	}
	char line[STRING_LENGTH];
	memset(line, 0, STRING_LENGTH);

	char c = '\0';

	while (1) {
		memset(line, 0, STRING_LENGTH);

		for (int i = 0; i < STRING_LENGTH; i++) {
			c = fgetc(pFile);
			if (c == '\n') {
				break;
			}
			line[i] = c;
		}
		if (parse(line) != 0)
			return 9;
	}

	fclose(pFile);
	return 0;

}
