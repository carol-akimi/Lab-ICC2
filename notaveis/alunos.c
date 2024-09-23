/*
queria usar merge sort mas o shell tava pronto já então quis testar com ele
*/

#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct aluno_{
    char* nome;
    int aumento;
}Aluno;

Aluno* ler_alunos(FILE* fp, int qtd);
int contar_alunos(FILE* fp);
void shell_sort(Aluno* lista, int n);
void print_alunos(Aluno* lista, int k);
void print_todos(Aluno* lista, int n);     //temporaria

int main(void){
    char arquivo[20];
    int k;

    scanf("%s %d", arquivo, &k);
    FILE* fp=fopen(arquivo, "r");
    // char* s=malloc(200);
    // fgets(s, sizeof(s), fp);
    // free(s);
    int qtd=contar_alunos(fp);
    Aluno* alunos=ler_alunos(fp, qtd);
    fclose(fp);

    shell_sort(alunos, qtd);
    //printf("\nprint todos:\n");
    //print_todos(alunos, qtd);
    //printf("\nprint alunos:\n");
    print_alunos(alunos, k);
    free(alunos);
    
    return 0;
}

Aluno* ler_alunos(FILE* fp, int qtd){
    char nome[50];
    float n1, n3;
    Aluno* lista=malloc(qtd*sizeof(Aluno));
    fseek(fp, 24, SEEK_SET);

    for(int i=0; i<qtd; i++){
        fscanf(fp, " %[^,],%f,%*f,%f", nome, &n1, &n3);
        lista[i].nome=strdup(nome);
        lista[i].aumento=(int)(n3*10)-(int)(n1*10);
    }

    return lista;
}

int contar_alunos(FILE* fp){
    char s[999];
    int n=0;

    while(fgets(s, sizeof(s), fp)!=NULL)
        n++;
    rewind(fp);

    return n-1;
}

void shell_sort(Aluno* lista, int n){
    for(int tam=n/2; tam>0; tam/=2){
        for(int i=tam; i<n; i++){
            Aluno temp=lista[i];
            int j;
            for(j=i; j>=tam && (lista[j-tam].aumento<temp.aumento||(lista[j-tam].aumento==temp.aumento && strcmp(temp.nome, lista[j-tam].nome)<0)); j-=tam) //strcmp retorna número negativo se a primeira string for menor que a segunda quanto à ordem lexicográfica
                lista[j]=lista[j-tam];

            lista[j]=temp;
        }
    }
}

void print_alunos(Aluno* lista, int k){
    for(int i=0; i<k||(lista[k].aumento==lista[i+1].aumento); i++){
        printf("%s\n", lista[i].nome);
    }
}

void print_todos(Aluno* lista, int n){
    for(int i=0; i<n; i++)
        printf("%s", lista[i].nome);
}