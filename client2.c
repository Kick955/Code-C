#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define DELAY 500 // 0.5 seconds delay

void send_signal(pid_t server_pid, int signal) {
    if (kill(server_pid, signal) == -1) {
        perror("kill");
        exit(EXIT_FAILURE);
    }
    usleep(DELAY);
}

void send_char_as_signals(char c, pid_t server_pid) {
    for (int i = 7; i >= 0; --i) {
        int bit = (c >> i) & 1;
        send_signal(server_pid, bit ? SIGUSR2 : SIGUSR1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Server PID> <Message>\n", argv[0]);
       
return 1;
}
pid_t server_pid = (pid_t)atoi(argv[1]);
char *message = argv[2];

// Send message to server
while (*message) {
    send_char_as_signals(*message++, server_pid);
}

// Send termination signal (NULL character)
send_char_as_signals('\0', server_pid);

printf("Message sent to server with PID %d\n", server_pid);
return 0;
}
