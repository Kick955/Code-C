#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define MAX_MESSAGE_LENGTH 1024

volatile int bit_count = 0;
volatile char message[MAX_MESSAGE_LENGTH];
volatile int current_bit = 0;
volatile int current_char_index = 0;

void handle_signal(int signum) {
    //Ajouter un bit au caractère courant basé sur le signal reçu
if (signum == SIGUSR1) {
// Ajouter un bit '0'
current_bit = 0;
} else if (signum == SIGUSR2) {
// Ajouter un bit '1'
current_bit = 1;
}
// Décaler le caractère courant et ajouter le nouveau bit
message[current_char_index] = (message[current_char_index] << 1) | current_bit;
bit_count++;

// Si nous avons reçu 8 bits, passer au caractère suivant
if (bit_count == 8) {
    bit_count = 0;
    current_char_index++;

    // Si le caractère courant est le terminateur nul, imprimer le message
    if (message[current_char_index - 1] == '\0') {
        printf("Message reçu: %s\n", message);
        // Réinitialiser pour le prochain message
        memset((void *)message, 0, MAX_MESSAGE_LENGTH);
        current_char_index = 0;
    }
}
}

int main() {
printf("Serveur PID: %d\n", getpid());
// Configuration des gestionnaires de signaux pour SIGUSR1 et SIGUSR2
struct sigaction sa;
memset(&sa, 0, sizeof(sa));
sa.sa_flags = SA_RESTART; // Pour redémarrer les appels système si interrompus
sa.sa_handler = handle_signal;

sigaction(SIGUSR1, &sa, NULL);
sigaction(SIGUSR2, &sa, NULL);

// Boucle infinie pour attendre les signaux
while (1) {
    pause(); // Attendre le prochain signal
}

return EXIT_SUCCESS; // Cette ligne ne sera jamais atteinte

