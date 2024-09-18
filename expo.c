#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

int iterativa(int base, int expo);
long int expo(int n, int k);

// Estrutura para armazenar o tempo de execução
typedef struct{
    clock_t start;
    clock_t end;
}Timer; 

// Inicializa o timer
void start_timer(Timer *timer) {
    timer->start = clock();
}

// Para o timer e calcula o tempo decorrido
double stop_timer(Timer *timer) {
    timer->end = clock();
    return ((double) (timer->end - timer->start)) / CLOCKS_PER_SEC;
}

int main(void){
    int n, k; 
    scanf("%d %d", &n, &k); 
    Timer t1;
    Timer t2;
    start_timer(&t1);
    printf("A versão iterativa:%d\n", iterativa(n, k));
    double tempo = stop_timer(&t1);
    printf("O tempo de execução da iterativa foi de %lf\n", tempo);
    start_timer(&t2);
    printf("A versão por divisão e conquista:%ld\n", expo(n, k));
    double tempo2 = stop_timer(&t2);
    printf("O tempo de execução da por divisão e conquista foi de %lf\n", tempo2);
    

}

int iterativa(int base, int exp){
    int res = 1; 
    for (int i = 0; i < exp; i++){
        res *= base; 
        res = res % 10000;
    }
    return res; 
}

long int expo(int n, int k){
    if(k==0)
        return 1;
    if(k==1)
        return n;
    if(k%2)
        return (expo(n, k/2)*expo(n, k/2)*n)%10000;
    else
        return (expo(n, k/2)*expo(n, k/2))%10000;
}

