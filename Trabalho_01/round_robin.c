#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100
#define MAX_PID 200
#define MAX_EXEC_TIME 60000
#define MAX_TIME_QUANTUM 1000
#define MIN_TIME_QUANTUM 1

typedef struct {
    int pid;
    int remaining_time;
    int turnaround_time;
} Process;

void quicksort(Process processes[], int low, int high) {
    if (low < high) {
        int pivot = processes[high].turnaround_time;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (processes[j].turnaround_time <= pivot) {
                i++;
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }

        Process temp = processes[i + 1];
        processes[i + 1] = processes[high];
        processes[high] = temp;

        int pi = i + 1;
        quicksort(processes, low, pi - 1);
        quicksort(processes, pi + 1, high);
    }
}

void round_robin_scheduler(int n, int time_quantum, Process processes[]) {
    int time = 0;
    int completed = 0;
    int queue[MAX_PROCESSES];
    int front = 0, rear = n - 1;

    // Inicializar a fila circular com os índices dos processos
    for (int i = 0; i < n; i++) {
        queue[i] = i;
    }

    while (completed < n) {
        int index = queue[front];
        front = (front + 1) % n; // Avança na fila circular

        if (processes[index].remaining_time > 0) {
            if (processes[index].remaining_time <= time_quantum) {
                time += processes[index].remaining_time;
                processes[index].remaining_time = 0;
                processes[index].turnaround_time = time;
                completed++;
            } else {
                time += time_quantum;
                processes[index].remaining_time -= time_quantum;
                rear = (rear + 1) % n;
                queue[rear] = index; // Reinsere o processo na fila
            }
        }
    }
}

int main() {
    int n, time_quantum;

    // Leitura do número de processos
    scanf("%d", &n);
    if (n < 1 || n > MAX_PROCESSES) {
        return 1;
    }

    // Leitura do tempo de janela (em milissegundos)
    scanf("%d", &time_quantum);
    if (time_quantum < MIN_TIME_QUANTUM || time_quantum > MAX_TIME_QUANTUM) {
        return 1;
    }

    // Criação do vetor de processos
    Process processes[n];

    // Leitura dos processos
    for (int i = 0; i < n; i++) {
        int pid, exec_time;
        scanf("%d %d", &pid, &exec_time);
        if (pid < 1 || pid > MAX_PID) {
            return 1;
        }
        if (exec_time < 1 || exec_time > MAX_EXEC_TIME) {
            return 1;
        }
        processes[i].pid = pid;
        processes[i].remaining_time = exec_time * 1000; // Convertendo para milissegundos
        processes[i].turnaround_time = 0;
    }

    // Chamada ao escalonador round-robin
    round_robin_scheduler(n, time_quantum, processes);

    // Ordenação dos processos pela ordem de término
    quicksort(processes, 0, n - 1);

    // Impressão dos resultados
    for (int i = 0; i < n; i++) {
        printf("%d (%d)\n", processes[i].pid, processes[i].turnaround_time);
    }

    return 0;
}
