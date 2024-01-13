#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void send_bit_as_signal(int bit, pid_t server_pid) {
    if (bit == 0) {
        kill(server_pid, SIGUSR1);
    } else {
        kill(server_pid, SIGUSR2);
    }
    usleep(100); // Délai pour s'assurer que le serveur gère le signal
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Utilisation: %s <Server PID> <Message>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t server_pid = (pid_t)atoi(argv[1]);
    char *message = argv[
// Envoyer le message bit par bit
for (size_t i = 0; message[i] != '\0'; ++i) {
    for (int bit = 7; bit >= 0; --bit) {
        send_bit_as_signal((message[i] >> bit) & 1, server_pid);
    }
}

// Envoyer un caractère nul comme terminateur de message
for (int bit = 7; bit >= 0; --bit) {
    send_bit_as_signal(0, server_pid);
}

printf("Message envoyé au serveur avec PID %d\n", server_pid);

return EXIT_SUCCESS;
}
