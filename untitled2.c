#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 100

typedef struct {
    char nomeAluno[TAM_MAX];
    char telefoneAluno[TAM_MAX];
    char nomeCurso[TAM_MAX];
    float nota1;
    float nota2;
} Aluno;


float calcularMedia(float nota1, float nota2) {
    return (nota1 + nota2) / 2.0;
}


const char* determinarSituacao(float media) {
    if (media >= 7.0) {
        return "APROVADO";
    } else {
        return "REPROVADO";
    }
}

int main() {
    FILE *arquivoEntrada;
    FILE *arquivoSaida;
    
    arquivoEntrada =  fopen("DadosEntrada.csv", "r");
    arquivoSaida = fopen("SituacaoFinal.csv", "w");

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    Aluno *aluno = (Aluno*)malloc(sizeof(Aluno));
	
	fscanf(arquivoEntrada, "%*[^\n]\n");
    
    char linha[TAM_MAX];
    while (fgets(linha, TAM_MAX, arquivoEntrada) != NULL) {
        // Separar os dados usando a vírgula como delimitador
        char *token = strtok(linha, ",");
        strcpy(aluno->nomeAluno, token);
        token = strtok(NULL, ",");
        strcpy(aluno->telefoneAluno, token);
        token = strtok(NULL, ",");
        strcpy(aluno->nomeCurso, token);
        token = strtok(NULL, ",");
        aluno->nota1 = atof(token);
        token = strtok(NULL, ",");
        aluno->nota2 = atof(token);

        float media = calcularMedia(aluno->nota1, aluno->nota2);

        const char* situacao = determinarSituacao(media);

        fprintf(arquivoSaida, "%s, %.2f, %s\n", aluno->nomeAluno, media, situacao);
    }

    fclose(arquivoEntrada);
    fclose(arquivoSaida);
    free(aluno); 

    printf("Processamento concluído. Verifique o arquivo SituacaoFinal.csv\n");

    return 0;
}


