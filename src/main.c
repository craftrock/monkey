#include "repl.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
	struct passwd *pw = getpwuid(getuid());
	if (pw == NULL) {
		fprintf(stderr, "Error: Could not get current user\n");
		return EXIT_FAILURE;
	}

	printf("Hello %s! This is the Monkey programming language!\n", pw->pw_name);
	printf("Feel free to type in commands\n");

	repl_start(stdin, stdout);

	return EXIT_SUCCESS;
}
