/*
queria usar merge sort mas o shell tava pronto já então quis testar com ele (ainda noa funcionou)
*/

#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct aluno_{
    char* nome;
    int aumento;
}Aluno;

Aluno* ler_alunos(FILE* fp);
int contar_alunos(FILE* fp);
void shell_sort(Aluno* lista, int n);
void print_alunos(Aluno* lista, int k);
void print_todos(Aluno* lista);     //temporaria

int main(void){
    char arquivo[20];
    int k;

    scanf("%s %d", arquivo, &k);
    FILE* fp=fopen(arquivo, "r");

    Aluno* alunos=ler_alunos(fp);
    fclose(fp);

    shell_sort(alunos, sizeof(alunos)/sizeof(Aluno));
    print_todos(alunos);    //testando a ordenação, tá errada
    print_alunos(alunos, k);
    free(alunos);
    
    return 0;
}

Aluno* ler_alunos(FILE* fp){
    char nome[50];
    float n1, n3;
    int qtd=contar_alunos(fp);
    Aluno* lista=malloc(qtd*sizeof(Aluno));

    // if(lista==NULL)
    //     printf("nao conseguiu alocar o vetor\n");

    for(int i=0; i<qtd; i++){
        fscanf(fp, "%[^,],%f,%*f,%f", nome, &n1, &n3);
        lista[i].nome=strdup(nome);
        (lista[i].nome)[strlen(lista[i].nome)]='\0';    //arrumar
        lista[i].aumento=(int)(n3*10)-(int)(n1*10);
    }

    return lista;
}

int contar_alunos(FILE* fp){
    char s[999];
    int n=0;

    while(fgets(s, sizeof(s), fp)!=NULL)
        //printf("linha %d\n", n+1);
        n++;
    rewind(fp);

    return n;
}

/*void inserir_aluno(Aluno* ini, Aluno* fim, Aluno aluno, int tam){
    //  Insertion sort 
        if(tam==1){

        }
        if(aluno.aumento<ini[tam/2].aumento)
            inserir_aluno(ini+(tam/2), fim, aluno, tam/2);
        else if(aluno.aumento>lista[tam/2].aumento)
            inserir_aluno(ini, tam/2, aluno, tam/2);
        else if(aluno.aumento==ini[tam/2].aumento){
            j=tam/2;
            while(strcmp(aluno.nome, ini[j].nome)<0){
                j--;
            }
            for(int i=tam; i>j; i--)
                ini[i]=ini[i-1];
            ini[j]=aluno;
        }
    

}*/

/*  conferir se isso tá certo */
void shell_sort(Aluno* lista, int n){
    for(int tam=n/2; tam>0; tam/=2){
        for(int i=tam; i<n; i++){
            Aluno temp=lista[i];
            int j;
            for(j=i; j>=tam && (lista[j-tam].aumento>temp.aumento||(lista[j-tam].aumento==temp.aumento && strcmp(lista[j-tam].nome, temp.nome)<0)); j-=tam) //strcmp retorna número negativo se a primeira string for menor que a segunda quanto à ordem lexicográfica
                lista[j]=lista[j-tam];

            lista[j]=temp;
        }
    }
}

void print_alunos(Aluno* lista, int k){
    for(int i=0; i<k||(lista[k].aumento==lista[i].aumento); i++)
        printf("%s", lista[i].nome);
}

void print_todos(Aluno* lista){
    for(int i=0; i<3; i++)
        printf("%s", lista[i].nome);
}