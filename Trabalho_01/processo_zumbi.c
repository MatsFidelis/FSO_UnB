#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Variáveis globais
pid_t zombie_pid = 0; // Armazena o PID do processo zumbi
int signal_count = 0; // Contador de sinais recebidos

// Manipulador de sinais
void signal_handler(int sig) {
    signal_count++;

    if (signal_count == 1) {
        // Primeiro sinal: criar processo zumbi
        zombie_pid = fork();

        if (zombie_pid == 0) {
            // Processo filho: sai imediatamente para se tornar zumbi
            exit(0);
        }
    } else if (signal_count == 2) {
        // Segundo sinal: eliminar o processo zumbi
        if (zombie_pid > 0) {
            waitpid(zombie_pid, NULL, 0); // Recolhe o status de saída do processo zumbi
            zombie_pid = 0; // Redefine o PID do zumbi
        }
    } else if (signal_count == 3) {
        // Terceiro sinal: encerrar o programa
        exit(0);
    }
}

int main() {
    // Instala os tratadores de sinal para SIGUSR1 e SIGUSR2
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    // Aguarda sinais indefinidamente
    while (1) {
        pause(); // Suspende o processo até receber um sinal
    }

    return 0;
}
