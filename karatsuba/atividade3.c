#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    char *inferior, *superior;
} metades;

metades separa_no(char *str, int meio);
char* karatsuba(char *str1, char *str2);
char* add(char *a, char *b);
char* sub(char *a, char *b);
char* multiplicacao(char *a, char *b);
char* potencia_de_10(char *str, int exp);
char* tirar_zero(char *res);



// Função principal do algoritmo de Karatsuba
char* karatsuba( char* str1,  char* str2);

int main() {
    char n1[1001], n2[1001];
    scanf("%s %s", n1, n2);
    
    char *res = karatsuba(n1, n2);
    res = tirar_zero(res);
    
    printf("%s\n", res);
    
    //free(res);
    return 0;
}

char* karatsuba( char* str1,  char* str2) {
    int len1 = strlen(str1), len2 = strlen(str2);

    // Caso base: se uma das strings for de comprimento 1, faz a multiplicação básica
    if (len1 == 1 || len2 == 1) {
        return multiplicacao(str1, str2);
    }

    int meio = max(len1, len2) / 2;

    metades s1 = separa_no(str1, len1 - meio);
    metades s2 = separa_no(str2, len2 - meio);

    // Recursão para z0, z1, z2
    char* z0 = karatsuba(s1.inferior, s2.inferior);
    char* z1 = karatsuba(add(s1.inferior, s1.superior), add(s2.inferior, s2.superior));
    char* z2 = karatsuba(s1.superior, s2.superior);

    // Calculando o resultado final
    char* resultado = add(
        add(potencia_de_10(z2, 2 * meio),
            potencia_de_10(sub(sub(z1, z2), z0), meio)),
        z0
    );

    // Limpeza de memória
   /* free(s1.inferior);
    free(s1.superior);
    free(s2.inferior);
    free(s2.superior);
    free(z0);
    free(z1);
    free(z2);*/

    return resultado;
}

metades separa_no( char* str, int meio) {
    metades m;
    m.superior = strndup(str, meio);
    m.inferior = strdup(str + meio);
    return m;
}

char* tirar_zero(char* str) {
    while (*str == '0' && *(str + 1)) str++;
    return strdup(str);
}

// Placeholder para outras funções que precisam ser implementadas:
// multiplicacao, add, sub, potencia_de_10

