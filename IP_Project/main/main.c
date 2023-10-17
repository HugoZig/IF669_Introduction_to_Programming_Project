#include <math.h>
#include "raylib.h"
#include "jogo.h"
#include "funcaoMapa.h"
#include "reset.h"

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { ABERTURA = 0, TITULO, INICIO, MAPAS, JOGO, FIM} GameScreen;

//------------------------------------------------------------------------------------------
// Main entry point
//------------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1024;
    const int screenHeight = 736;

    Rectangle comoJograH = {700, 10, 360, 128};

    InitWindow(screenWidth, screenHeight, "FREE THE LLOCS'S");

    InitAudioDevice();

    Texture2D CIn = CInH;       // Texture loading

    GameScreen currentScreen = ABERTURA;

    // TODO: Initialize all required variables and load all required data here!

    int framesCounterH = 0;

    float zoomInH = 0.0f, deslocamentoH = 512.0f;
    int flagH =  0, printaH = 0;
    Vector2 mousPointH = {0.0f, 0.0f};
    Vector2 reallocH = {170, 150}, origemH = {75, 50};
    Vector2 mallocH = {170, 550};
    Vector2 callocH = {800, 500};
    int mapa = -1;
    int ganhou = -1;
    int resetH = -1;
    int delayH = 0;
    float tempoTocado = 0;
    Music musicaInicio = LoadMusicStream("resources/crazyfrog.mp3");

    float rotacao = 0.0f;

    PlayMusicStream(musicaInicio);

    Font fonte = GetFontDefault();

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        mousPointH = GetMousePosition();
        UpdateMusicStream(musicaInicio);
        switch(currentScreen)
        {
            case ABERTURA:
            {
                /*if (IsKeyPressed(KEY_SPACE)) {
                    currentScreen = INICIO;
                }*/
                framesCounterH++;

                if (framesCounterH > 420)
                {
                    currentScreen = TITULO;
                }
            } break;
            case TITULO:
            {
                framesCounterH++;

                zoomInH += 0.55f;
                deslocamentoH -= 2.56f;
                if (framesCounterH > 780)
                {
                    currentScreen = INICIO;
                }
            } break;
            case INICIO:
            {
                if (!IsMusicStreamPlaying(musicaInicio)) {
                    SeekMusicStream(musicaInicio, tempoTocado);
                    PlayMusicStream(musicaInicio);
                }
                framesCounterH++;
                if (framesCounterH % 45 == 0) {
                    flagH++;
                }
                if (IsKeyPressed(KEY_SPACE))
                {
                    PauseMusicStream(musicaInicio);
                    tempoTocado = GetMusicTimePlayed(musicaInicio);
                    currentScreen = MAPAS;
                }

                if (CheckCollisionPointRec(mousPointH, comoJograH)) {
                    printaH = 1;
                }
                else printaH = 0;
            } break;
            case MAPAS:
                mapa = funcaoMapa(tempoTocado);
                currentScreen = JOGO;
                break;

            case JOGO:

            {
                ganhou = jogo(screenWidth, screenHeight, mapa);
                if (ganhou == 1) {
                    currentScreen = FIM;
                }
                else if (ganhou == 2){
                    currentScreen = INICIO;
                }
                else{
                    resetH = reset();
                    if (resetH == 0) {
                        currentScreen = JOGO;
                    }
                    else currentScreen = FIM;
                }
            } break;

            case FIM:{
                delayH++;
                if (delayH >= 240) {
                    return 0;
                }
            }



            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            switch(currentScreen)
            {
                case ABERTURA:
                {
                    ClearBackground(BLUE);
                    DrawText("UMA PRODUCAO\nGRUPO 1 DE IP - E.C. 2021.1", 30, 200, 60, BLACK);
                    DrawTexture(CIn, 0, 0, RAYWHITE);
                    DrawText("Hugo Medeiros\nMarcela Asfora\nOtavio Baudel\nPaulo Oliveira\nPedro Nascimento\nRoberto Albuquerque\nThiago Magalhaes\n", 30, 400, 30, RAYWHITE);

                } break;
                case TITULO:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
                    if (deslocamentoH <= 0 || zoomInH >= 110) {
                        deslocamentoH = 0;
                        zoomInH = 110;
                    }
                    rotacao += 4;
                    DrawText("FREE THE LLOC'S ", deslocamentoH+25, 250, zoomInH-5, WHITE);
                    DrawTextPro(fonte, "REALLOC", reallocH, origemH, -15+rotacao, 40, 10, BLUE);
                    DrawTextPro(fonte, "MALLOC", mallocH, origemH, -15+rotacao, 40, 10, GREEN);
                    DrawTextPro(fonte, "CALLOC", callocH, origemH, 15+rotacao, 40, 10, RED);
                } break;
                case INICIO:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
                    DrawText("FREE THE LLOC'S", deslocamentoH+25, 250, zoomInH-5, WHITE);
                    if (flagH % 2 == 0) {
                        DrawText("APERTE BARRA DE ESPACO PARA INICIAR O JOGO!", 225, 650, 20, MAROON);
                    }
                    if (printaH == 0) {
                        DrawText("COMO JOGAR\n(PASSE O MOUSE)", 700, 10, 30, ORANGE);
                        DrawTextPro(fonte, "REALLOC", reallocH, origemH, -5, 40, 10, BLUE);
                        DrawTextPro(fonte, "MALLOC", mallocH, origemH, -15, 40, 10, GREEN);
                        DrawTextPro(fonte, "CALLOC", callocH, origemH, 15, 40, 10, RED);
                    }
                    if (printaH == 1) {
                        DrawText("FREE (O BOI) DEVE LIMPAR TODOS OS TIPOS DE LLOC DO CHAO\nUSE WASD OU AS SETAS PARA SE MOVER\nBOA SORTE!!!", 10, 10, 20, YELLOW);
                        DrawTextPro(fonte, "MALLOC", mallocH, origemH, -15, 40, 10, GREEN);
                        DrawTextPro(fonte, "CALLOC", callocH, origemH, 15, 40, 10, RED);
                        DrawText("DA O FREE!!!!", 800, 10, 30, PINK);
                    }

                } break;
                case FIM:
                    {
                    if (ganhou == 1) {DrawText("\nPARABENS, VC FOI\n APROVADO EM IP!", 65, 100, 90, YELLOW);}
                    else DrawText("DESISTIU???\nFRACO.", 120, 200, 100, RED);
                } break;
                default: break;
            }

        EndDrawing();
    }


    UnloadTexture(CIn);

    UnloadMusicStream(musicaInicio);
    CloseAudioDevice();
    CloseWindow();


    return 0;
}
