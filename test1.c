#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <termcap.h>

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_interrupt(int signal) {
    printf("\nCtrl+C pressed, executing code...\n");
    // Your code to execute after Ctrl+C
}

int main() {
    // Register the signal handler
    signal(SIGINT, handle_interrupt);

    char input[100];
    char *termtype = getenv("TERM");
    if (termtype == NULL) {
        fprintf(stderr, "TERM environment variable not set.\n");
        return 1;
    }

    // Initialize termcap
    if (tgetent(NULL, termtype) != 1) {
        fprintf(stderr, "Could not initialize termcap.\n");
        return 1;
    }

    while (1) {
        printf(">");
        ssize_t bytes_read = read(STDIN_FILENO, input, sizeof(input));
		write(1, "Asd", 3);
        if (bytes_read == -1) {
            perror("read");
            return 1;
        }

        input[bytes_read - 1] = '\0'; // Remove newline character

        // Your code here
        printf("Input received: %s\n", input);
    }

    return 0;
}