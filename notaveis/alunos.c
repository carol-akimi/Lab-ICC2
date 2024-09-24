#include <stdio.h>
#include<string.h>
#include <stdlib.h>

//struct Aluno armazena o nome do aluno e a taxa de aumento
typedef struct aluno_{
    char* nome;
    int aumento;
}Aluno;

Aluno* ler_alunos(FILE* fp, int qtd);
int contar_alunos(FILE* fp);
void shell_sort(Aluno* lista, int n);
void print_alunos(Aluno* lista, int k);


int main(void){
    char arquivo[20];
    int k; 

    //Leitura dos dados
    scanf("%s %d", arquivo, &k);

    FILE* fp; 
    if (fopen(arquivo, "r") == NULL){
        printf("ERRO ao abrir o arquivo\n"); 
        exit(1); 
    }

    //Adquire a quantidade de alunos 
    int qtd=contar_alunos(fp);
    //Lê as informações dos alunos que são armazenadas no vetor "alunos"
    Aluno* alunos=ler_alunos(fp, qtd);

    fclose(fp);

    //Ordenação do vetor "alunos" 
    shell_sort(alunos, qtd);
    //Printa os alunos escolhidos 
    print_alunos(alunos, k);

    free(alunos);
    
    return 0;
}

/**
 * Função que lê as informações de cada aluno do arquivo 
 * e coloca essas informações no vetor "lista"
 * @param nome -> Nome do aluno
 * @param n1 -> Primeira nota
 * @param n3 -> Terceira nota 
 * @param lista -> Lista de alunos 
 * @param qtd -> Quantidade de alunos
 */
Aluno* ler_alunos(FILE* fp, int qtd){
    char nome[50];
    float n1, n3;
    Aluno* lista=malloc(qtd*sizeof(Aluno));
    //pula a primiera linha do arquivo
    fseek(fp, 24, SEEK_SET);
    //le as informacões nome e notas
    //armazena apenas o nome e o aumento (n3-n1)
    for(int i=0; i<qtd; i++){
        fscanf(fp, " %[^,],%f,%*f,%f", nome, &n1, &n3);
        lista[i].nome=strdup(nome);
        lista[i].aumento=(int)(n3*10)-(int)(n1*10);
    }

    return lista;
}

/**
 * Função que conta a quantidade de aluno por meio da quantidade de linhas 
 * @param nome -> Nome do aluno
 * @param s -> Armazena as linhas lidas do arquivo
 * @param n -> Quantidade de linhas 
 */
int contar_alunos(FILE* fp){
    char s[999];
    int n=0;
    //A cada quebra de linha, n é incrementado, a função fgets 
    //retorna NULL quando o arquivo chega ao fim 
    while(fgets(s, sizeof(s), fp)!=NULL)
        n++;
    //volta o ponteiro fp para o início do arquivo
    rewind(fp);

    return n-1;
}

/**
 * Função de ordenação do algortimo shell sort 
 * @param lista -> Lista de alunos 
 * @param n -> Quantudade de alunos 
 */

void shell_sort(Aluno* lista, int n){
    for(int tam=n/2; tam>0; tam/=2){
        for(int i=tam; i<n; i++){
            Aluno temp=lista[i];
            int j;
            for(j=i; j>=tam && (lista[j-tam].aumento<temp.aumento||(lista[j-tam].aumento==temp.aumento && strcmp(temp.nome, lista[j-tam].nome)<0)); j-=tam)
                lista[j]=lista[j-tam];

            lista[j]=temp;
        }
    }
}

/**
 * Função que printa os k alunos com maiores aumentos, se houver empates 
 * na última posição, todos com aquela nota são printados
 * @param lista -> Lista de alunos 
 * @param k -> Quantidade de alunos escolhidos com maiores aumentos 
 */

void print_alunos(Aluno* lista, int k){
    int i=0;
    while(i<k ||(lista[i].aumento==lista[i-1].aumento)){
        printf("%s\n", lista[i].nome);
        i++;
    }
}