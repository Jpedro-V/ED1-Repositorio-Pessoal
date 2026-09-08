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

int main(void) {
    funcionario funcionario;

    preencherfuncionario(&funcionario);
    imprimirFuncionario(&funcionario);

    return 0;
}
