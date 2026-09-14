#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA  600
#define MAX_ENTIDADES  32

typedef enum {
    ENTIDADE_JOGADOR,
    ENTIDADE_INIMIGO,
    ENTIDADE_ITEM
} TipoEntidade;

typedef struct {
    TipoEntidade tipo;
    Vector2      pos;
    float        raio;
    Color        cor;
    int          vida;
} Entidade;

Entidade *criarEntidade(TipoEntidade tipo, Vector2 pos) {
    Entidade *e = (Entidade *)malloc(sizeof(Entidade));
    if (e == NULL) return NULL;

    e->tipo = tipo;
    e->pos = pos;

    switch (tipo) {
        case ENTIDADE_JOGADOR:
            e->raio = 20.0f;
            e->cor = BLUE;
            e->vida = 100;
            break;
        case ENTIDADE_INIMIGO:
            e->raio = 15.0f;
            e->cor = MAROON;
            e->vida = 60;
            break;
        case ENTIDADE_ITEM:
            e->raio = 10.0f;
            e->cor = GREEN;
            e->vida = 1;
            break;
    }

    return e;
}

void adicionarEntidade(Entidade **vetor, int *total, Entidade *nova) {
    if (*total < MAX_ENTIDADES && nova != NULL) {
        vetor[*total] = nova;
        (*total)++;
    }
}

void ordenarPorDistancia(Entidade **vetorEntidades, int totalEntidades) {
    if (totalEntidades <= 2) return;

    Entidade *jogador = vetorEntidades[0];

    for (int i = 1; i < totalEntidades - 1; i++) {
        for (int j = 1; j < totalEntidades - 1; j++) {
            float dx1 = vetorEntidades[j]->pos.x - jogador->pos.x;
            float dy1 = vetorEntidades[j]->pos.y - jogador->pos.y;
            float dist1 = sqrtf(dx1 * dx1 + dy1 * dy1);

            float dx2 = vetorEntidades[j + 1]->pos.x - jogador->pos.x;
            float dy2 = vetorEntidades[j + 1]->pos.y - jogador->pos.y;
            float dist2 = sqrtf(dx2 * dx2 + dy2 * dy2);

            if (dist1 > dist2) {
                Entidade *tmp = vetorEntidades[j];
                vetorEntidades[j] = vetorEntidades[j + 1];
                vetorEntidades[j + 1] = tmp;
            }
        }
    }
}

void desenharEntidade(Entidade *e) {
    if (e == NULL) return;
    DrawCircleV(e->pos, e->raio, e->cor);
    if (e->tipo == ENTIDADE_INIMIGO) {
        DrawText(TextFormat("%d", e->vida), e->pos.x - 8, e->pos.y - 26, 14, BLACK);
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 5 - Exercicios 1 e 2");
    SetTargetFPS(60);

    Entidade *vetorEntidades[MAX_ENTIDADES];
    int totalEntidades = 0;

    adicionarEntidade(vetorEntidades, &totalEntidades,
                      criarEntidade(ENTIDADE_JOGADOR, (Vector2){ LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f }));

    for (int i = 0; i < 5; i++) {
        Vector2 posIni = { (float)GetRandomValue(40, LARGURA_JANELA - 40),
                           (float)GetRandomValue(40, ALTURA_JANELA - 40) };
        adicionarEntidade(vetorEntidades, &totalEntidades, criarEntidade(ENTIDADE_INIMIGO, posIni));
    }

    while (!WindowShouldClose()) {
        Entidade *jogador = vetorEntidades[0];
        float vel = 250.0f * GetFrameTime();

        if (IsKeyDown(KEY_RIGHT)) jogador->pos.x += vel;
        if (IsKeyDown(KEY_LEFT))  jogador->pos.x -= vel;
        if (IsKeyDown(KEY_UP))    jogador->pos.y -= vel;
        if (IsKeyDown(KEY_DOWN))  jogador->pos.y += vel;

        if (IsKeyPressed(KEY_N)) {
            if (totalEntidades < MAX_ENTIDADES) {
                Vector2 posItem = { (float)GetRandomValue(30, LARGURA_JANELA - 30),
                                    (float)GetRandomValue(30, ALTURA_JANELA - 30) };
                adicionarEntidade(vetorEntidades, &totalEntidades, criarEntidade(ENTIDADE_ITEM, posItem));
            }
        }

        ordenarPorDistancia(vetorEntidades, totalEntidades);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < totalEntidades; i++) {
                desenharEntidade(vetorEntidades[i]);
            }

            if (totalEntidades > 1) {
                DrawCircleLines(vetorEntidades[1]->pos.x, vetorEntidades[1]->pos.y, vetorEntidades[1]->raio + 4.0f, RED);
            }

            DrawText("Setas movem o jogador | N gera um item | ESC sai", 10, 10, 20, DARKGRAY);
            DrawText(TextFormat("Entidades: %d/%d", totalEntidades, MAX_ENTIDADES), 10, ALTURA_JANELA - 25, 16, GRAY);

        EndDrawing();
    }

    for (int i = 0; i < totalEntidades; i++) {
        free(vetorEntidades[i]);
    }

    CloseWindow();
    return 0;
}