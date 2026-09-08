#include <stdio.h>
#include <string.h>

typedef struct funcionario {
    char nome[50];
    float salario;
    int identificador;
    char cargo[30];
} funcionario;

void preencherfuncionario(funcionario *funcionario) {
    printf("Nome: ");
    scanf(" %49[^\n]", funcionario->nome);

    printf("Salario: ");
    scanf(" %f", &funcionario->salario);

    printf("Identificador: ");
    scanf(" %d", &funcionario->identificador);

    printf("Cargo: ");
    scanf(" %29[^\n]", funcionario->cargo);
}

void imprimirFuncionario(const funcionario *funcionario) {
    printf("\nDados do funcionario:\n");
    printf("Nome: %s\n", funcionario->nome);
    printf("Salario: %.2f\n", funcionario->salario);
    printf("Identificador: %d\n", funcionario->identificador);
    printf("Cargo: %s\n", funcionario->cargo);
}

void altera_salario(funcionario *funcionario) {
    float novo_salario;

    printf("Digite o novo salario: ");
    scanf(" %f", &novo_salario);

    funcionario->salario = novo_salario;
}

void maiorMenorSalario(funcionario vetor[], int tamanho) {
    int i;
    int Maior = 0;
    int Menor = 0;

    for (i = 1; i < tamanho; i++) {
        if (vetor[i].salario > vetor[Maior].salario) {
            Maior = i;
        }
        if (vetor[i].salario < vetor[Menor].salario) {
            Menor = i;
        }
    }
    printf("\nMaior salario:\n");
    printf("Cargo: %s\n", vetor[Maior].cargo);
    printf("Salario: %.2f\n", vetor[Maior].salario);

    printf("\nMenor salario:\n");
    printf("Cargo: %s\n", vetor[Menor].cargo);
    printf("Salario: %.2f\n", vetor[Menor].salario);
}
int main(void) {
    funcionario funcionarios[2];
    int i;

    for (i = 0; i < 2; i++) {
        printf("Funcionario %d\n", i + 1);
        preencherfuncionario(&funcionarios[i]);
    }
    maiorMenorSalario(funcionarios, 2);
    return 0;
}