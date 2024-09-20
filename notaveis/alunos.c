#include <stdio.h>

int main(void){
    FILE* fp=fopen("in.txt", "r");
    char nome[10];
    float n1, n3;

    fscanf(fp, "%[^,],%f,%*f,%f", nome, &n1, &n3);
    printf("%s, %f %f\n", nome, n1, n3);

    fclose(fp);
}
