#include <pthread.h>
#include <stdio.h>

int count = 0; // Contador global
pthread_mutex_t mut; // Mutex para proteger o contador

// Estrutura para passar o número de vezes que cada thread deve trabalhar
struct thread_arg {
    int vezes;
};

// Função work, a ser implementada pelo usuário
int work(int id) {
    // Simula um trabalho que leva tempo, por exemplo, um sleep
    printf("Trabalhando no id %d\n", id);
    return 0;
}

// Função que será executada pelas threads
void *thread_func(void *arg) {
    struct thread_arg *targ = (struct thread_arg *)arg;
    
    for (int i = 0; i < targ->vezes; i++) {
        // Incrementa o contador, protegendo com o mutex
        pthread_mutex_lock(&mut);
        int id = count;
        count++;
        pthread_mutex_unlock(&mut);
        
        // Chama a função work com o id gerado
        work(id);
    }
    
    return NULL;
}

// Função que paraleliza o trabalho
void do_all_work(int n) {
    // Inicializa o mutex
    pthread_mutex_init(&mut, NULL);
    
    // Número de threads a serem criadas
    int num_threads = 4; // Por exemplo, 4 threads
    pthread_t threads[num_threads];
    struct thread_arg args[num_threads];
    
    // Divide o trabalho entre as threads
    for (int i = 0; i < num_threads; i++) {
        args[i].vezes = n / num_threads; // Divide o trabalho igualmente
        if (i < n % num_threads) {
            args[i].vezes++; // Distribui o restante
        }
        
        // Cria a thread
        pthread_create(&threads[i], NULL, thread_func, (void *)&args[i]);
    }
    
    // Espera todas as threads terminarem
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Destroi o mutex
    pthread_mutex_destroy(&mut);
}

int main() {
    // Teste da função
    do_all_work(10); // Vamos chamar do_all_work com 10 trabalhos
    return 0;
}
