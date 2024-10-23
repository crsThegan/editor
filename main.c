#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *file, *tempfile;
char tempfilename[64] = {0};

enum {
	NORMAL,
	INSERT
} mode = NORMAL;

void setup_files(char *filename) {
	file = fopen(filename, "r");
	char cmdbuf[128] = {0};
	strcpy(tempfilename, filename);
	sprintf(cmdbuf, "cp %s %s", filename, strcat(tempfilename, ".temp"));
	system(cmdbuf);
	tempfile = fopen(tempfilename, "a+");
}

void print_tempfile() {
	clrtobot();
	move(0, 0);

	char c;
	while ((c = getc(tempfile)) != EOF)
		addch(c);
	refresh();
}

void save_changes() {
	//todo
}

void exit_prog() {
	//todo
}

void check_kb() {
	char key = getch();
	if (mode == NORMAL) {
		switch(key) {
		case 'i':
			mode = INSERT;
			break;
		case 's':
			save_changes();
			break;
		case 'x':
			exit_prog();
			break;
		}
	} else if (mode == INSERT) {
		putc(tempfile, key);
		print_tempfile();
	}
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("usage: ./main <filename>\n");
		exit(1);
	}

	setup_files(argv[1]);

	initscr();
	noecho();

	print_tempfile();

	fclose(file);
	fclose(tempfile);
	remove(tempfilename);

	getch();
	endwin();

	return 0;
}
