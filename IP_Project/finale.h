#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#define FPS 60

typedef enum GameScreen2 {CUTSCENE = 0, FINAL} GameScreen2;

typedef struct
{
    int x, y, largura, altura, velocidade, alive_flag;
    Texture2D textura;
    Animation anim;

} Player;

typedef struct
{
    int x, y, comportamento, vida;
    Texture2D textura, tiro, c, python;
    Sound alerta, disparo, colisao, impacto;
} Boss;

typedef struct
{
    int x, y, velocidade_x, velocidade_y, flag_ativo;
} Projetil_1;

typedef struct
{
    int x, y;
    float altura;
    int estado; //0 - Inativo; 1 - Caindo; 2 - No chao; 3 - Sendo Empurrado (Exclusivo pro tipo Python)
    int hitbox; //0 - nao dah dano, 1 -  dah dano.
    int vx, vy; //So importam pro Python no estado 3
} Bloco;

void desenhaMapa(int mapa[23][32], int largura_matriz, int altura_matriz, int tile);
void movimentaJogador(Player *pJogador);
void checaColisaoJogador2(int mapa[23][32], Player *pJogador, int tile);
void posicionaCamera2(Player *pJogador, Camera2D *pCamera, int largura_tela, int altura_tela);
void introCamera(Camera2D *pCamera, float *zoom, float timer);
void comportamentoBoss(Boss *ACM, float *timer, Player *jogador, Projetil_1 centrais[30], Projetil_1 esquerda[30], Projetil_1 direita[30], Bloco blocos[30], Bloco *python, int mapa[23][32]);
void movimentaProjetil(Texture2D textura,Projetil_1 centrais[30], Projetil_1 esquerda[30], Projetil_1 direita[30], Player *jogador);
void comportamentoBloco(Bloco blocos[30], Bloco *python, Player *jogador, Boss *ACM, int mapa[23][32]);
void desenhaVidaBoss(Boss *ACM);


void unldFinale(Projetil_1 **centrais, Projetil_1 **esquerda, Projetil_1 **direita, Texture *LugarVazio, Boss *ACM, Player *jogador, TextMenuP *textmenu, Music *musicaFim){

    free(*centrais);
    free(*esquerda);
    free(*direita);

    UnloadTexture(*LugarVazio);
    UnloadTexture(ACM->textura);
    UnloadTexture(ACM->tiro);
    UnloadTexture(ACM->c);
    UnloadTexture(ACM->python);
    UnloadTexture(jogador->textura);
    UnloadSound(ACM->alerta);
    UnloadSound(ACM->disparo);
    UnloadSound(ACM->colisao);
    UnloadSound(ACM->impacto);
    UnloadMusicStream(*musicaFim);

    unldTexturesMenuP(textmenu);

}


int finale(int largura_tela, int altura_tela)
{
    int mapa[23][32] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    int flagSomH = 1;
    int contadorH2 = 0;
    int PauseFlagH = 0;
    int menuFlag = 0;
    int delay = 0;

    Vector2 mousPointH = {0, 0};

    TextMenuP textmenu;
    ldTexturesMenuP(&textmenu);


    float timer = 0.0, zoom = 1.0, timer_boss = 0.0;

    int fim_da_intro = 0; //flag


    //InitWindow(largura_tela, altura_tela, "projeto IP");
    //InitAudioDevice();

    SetTargetFPS(60);

    Music musicaFim = LoadMusicStream("resources/Megalovania.mp3");
    UpdateMusicStream(musicaFim);
    PlayMusicStream(musicaFim);

    Player jogador;
    jogador.textura = BoiH;
    jogador.alive_flag = 1;
    jogador.anim = initAnimStandard(jogador.textura);
    jogador.x = largura_tela/2 - 16;
    jogador.y = altura_tela/2 - 24;
    jogador.largura = 32;
    jogador.altura = 32;
    jogador.velocidade = 3;



    Boss ACM = {largura_tela/2 - 39, altura_tela/4 - 57, 0, 100, (Texture2D)LoadTexture("resources/ACM.png"),
            (Texture2D)LoadTexture("resources/Projetil1.png"),(Texture2D)LoadTexture("resources/CLogo.png"),
            (Texture2D)LoadTexture("resources/PythonLogo.png"), (Sound)LoadSound("resources/Alerta.wav"),
            (Sound)LoadSound("resources/Tiro.wav"), (Sound)LoadSound("resources/Colisao.wav"),
            (Sound)LoadSound("resources/Impacto.wav")};
    SetSoundVolume(ACM.disparo, 0.05);
    SetSoundVolume(ACM.alerta, 0.1);
    Projetil_1 *centrais;
    Projetil_1 *esquerda;
    Projetil_1 *direita;
    Bloco *blocos;
    Bloco bpython = {0, 0, 0.0, 0, 0, 0, 0};
    centrais = (Projetil_1 *) calloc(30, sizeof(Projetil_1));
    esquerda = (Projetil_1 *) calloc(30, sizeof(Projetil_1));
    direita = (Projetil_1 *) calloc(30, sizeof(Projetil_1));
    blocos = (Bloco *) calloc(30, sizeof(Bloco));
    Texture LugarVazio = LoadTexture("resources/LugarVazio.png");
    Texture FundoVazio = LoadTexture("resources/Background.png");
    Texture AcmH = LoadTexture("resources/ACM2.png");
    int contadorH = 0;
    int flagFinalH = 0;



    Camera2D camera = { 0 };
    camera.target = (Vector2){ jogador.x + jogador.largura/2, jogador.y + jogador.largura/2 };
    camera.offset = (Vector2){ largura_tela/2.0f, altura_tela/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    GameScreen2 currentScreen = CUTSCENE;


    while (!WindowShouldClose())
    {
        if (!IsMusicStreamPlaying(musicaFim) && flagSomH%2 != 0) {
            PlayMusicStream(musicaFim);
        }
        UpdateMusicStream(musicaFim);
        mousPointH = GetMousePosition();

        if (CheckCollisionPointRec(mousPointH, PauseRetH) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                PauseFlagH = 1;
        }
        if (PauseFlagH == 1) {
            //test2 -> velocity = (Vector2) {0.0 , 0.0};
            contadorH2++;

            if (CheckCollisionPointRec(mousPointH, FecharPauseRecH) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                PauseFlagH = 0;
            }
            if (CheckCollisionPointRec(mousPointH, ColocarTirarSomRecH) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && contadorH2 > 5) {
                flagSomH++;
                if (flagSomH % 2 != 0) {ResumeMusicStream(musicaFim);}
                else PauseMusicStream(musicaFim);
                contadorH2 = 0;
            }
            if (CheckCollisionPointRec(mousPointH, IrParaMenuH)) {
                menuFlag = 1;
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

                    unldFinale(&centrais, &esquerda, &direita, &LugarVazio, &ACM, &jogador, &textmenu, &musicaFim);
                    return 2;
                }
            }
            else menuFlag = 0;
        }


        if(!jogador.alive_flag){
            delay++;
            if(delay >= FPS*4){
                return 0;
            }
        }

        if(!ACM.vida){
            delay++;
            if(delay >= FPS*4){
                return 1;
            }
        }

        if(PauseFlagH == 0){

            switch (currentScreen) {
                case CUTSCENE:
                    if (IsKeyPressed(KEY_SPACE)) {
                        contadorH++;
                        if (contadorH == 5) {
                            currentScreen = FINAL;
                        }
                    }
                    break;
                case FINAL:
                    timer += GetFrameTime();
                    timer_boss += GetFrameTime();
                    if(timer >= 3.0) fim_da_intro = 1;
                    if(!fim_da_intro) introCamera(&camera, &zoom, timer);

                    movimentaJogador(&jogador);
                    checaColisaoJogador2(mapa, &jogador, 32);
                    posicionaCamera2(&jogador, &camera, largura_tela, altura_tela);

                    break;

                default:
                    break;
            }
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (currentScreen == FINAL && flagFinalH == 0) {
                    BeginMode2D(camera);
                    flagFinalH = 1;
                }
        if (currentScreen == CUTSCENE) {
                    DrawTexture(FundoVazio, 0, 0, RAYWHITE);
                    DrawTexture(AcmH, 100, 350, RAYWHITE);
                    DrawRectangle(300, 80, 600, 150, GRAY);
                    DrawRectangleLines(300, 80, 600, 150, GREEN);
                    if (contadorH == 1) {
                        DrawText("ouvi dizer que voce nunca\nesquece o free()...", 310, 95, 40, GREEN);
                    }
                    if (contadorH == 2) {
                        DrawText("quero ver se voce se\ngarante na porrada", 310, 95, 40, GREEN);
                    }
                    if (contadorH == 3) {
                        DrawText("mas antes, este lugar nao\n eh digno de meu poder", 310, 95, 40, GREEN);
                    }
                    if (contadorH == 4) {
                        DrawText("vamos lutar em um lugar mais\nvazio...", 310, 95, 40, GREEN);
                    }

                    DrawFPS(largura_tela - 90, largura_tela - 30);
                    DrawTexture(textmenu.pause, 970, 5, RAYWHITE);

                    if (PauseFlagH == 1) {   // INTERFACE PAUSE

                        menuP(menuFlag, flagSomH, &textmenu);
                    }
        }
        if (currentScreen == FINAL) {
            BeginMode2D(camera);
            DrawTexture(LugarVazio, 0, 0, RAYWHITE);
            desenhaMapa(mapa, 32, 23, 32);

        if(PauseFlagH == 0){
            comportamentoBoss(&ACM, &timer_boss, &jogador, centrais, esquerda, direita, blocos, &bpython, mapa);
            movimentaProjetil(ACM.tiro, centrais, esquerda, direita, &jogador);
            comportamentoBloco(blocos, &bpython, &jogador, &ACM, mapa);
        }
            if(jogador.alive_flag)
            {
                //DrawRectangle(jogador.x, jogador.y, jogador.largura, jogador.altura, RED);
                DrawTextureRec(jogador.textura, jogador.anim.rec, (Vector2){jogador.x-16, jogador.y-25}, RAYWHITE);
            }
            EndMode2D();
            desenhaVidaBoss(&ACM);
            if(!jogador.alive_flag)
            {
                DrawText("Free (o Boi) morreu...\nF.", 300, 450, 50, GREEN);
            }

            DrawFPS(largura_tela - 90, largura_tela - 30);
            DrawTexture(textmenu.pause, 970, 5, RAYWHITE);

            if (PauseFlagH == 1) {   // INTERFACE PAUSE

                menuP(menuFlag, flagSomH, &textmenu);
            }
        }
        EndDrawing();

    }

unldFinale(&centrais, &esquerda, &direita, &LugarVazio, &ACM, &jogador, &textmenu, &musicaFim);


    return 2;
}

void movimentaJogador(Player *jogador)
//Self Explanatory
{
    int speed = jogador->velocidade;

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {jogador->x += speed; jogador->anim.count++; jogador->anim.choselist = jogador->anim.RightSprites;}
    if (IsKeyDown(KEY_LEFT)|| IsKeyDown(KEY_A)) {jogador->x -= speed; jogador->anim.count++; jogador->anim.choselist = jogador->anim.LeftSprites;}
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {jogador->y -= speed; jogador->anim.count++; jogador->anim.choselist = jogador->anim.UpSprites;}
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {jogador->y += speed; jogador->anim.count++; jogador->anim.choselist = jogador->anim.DownSprites;}



    jogador->anim.rec.y = jogador->anim.frameheight*jogador->anim.choselist;

    if(jogador->anim.count >= (FPS/jogador->anim.framespeed)){

        jogador->anim.count = 0;
        jogador->anim.frame++;
        if(jogador->anim.frame >= jogador->anim.framesnumx){jogador->anim.frame = 0;}
        jogador->anim.rec.x = jogador->anim.frame*jogador->anim.framewidth;

        }
}

void desenhaMapa(int mapa[23][32], int largura_matriz, int altura_matriz, int tile)
//Constr�i o mapa com retangulos pretos nas paredes
{
    int i = 0, j = 0;
    for(i = 0; i < altura_matriz; i++)
    {
        for(j = 0; j < largura_matriz; j++)
        {
            if(mapa[i][j] == 1)
            {
                DrawRectangle(j*tile, i*tile, tile, tile, BLACK);
            }
        }
    }
}

void checaColisaoJogador2(int mapa[23][32], Player *pJogador, int tile)
//Reposiciona o jogador numa posicao correta quando ele entra mais do que devia numa parede.
{
    int ponto_1[2] = {(pJogador->x )+(pJogador->largura/2), pJogador->y};
    int ponto_2[2] = {(pJogador->x)+(pJogador->largura), (pJogador->y)+(pJogador->altura/2)};
    int ponto_3[2] = {(pJogador->x)+(pJogador->largura/2), (pJogador->y)+(pJogador->altura)};
    int ponto_4[2] = {pJogador->x, (pJogador -> y)+(pJogador->altura/2)};

    /*           ponto_1
          ----------O----------
          |                   |
          |                   |
          |                   |
  ponto_4 O                   O ponto_2
          |                   |
          |                   |
          |                   |
          ----------O----------
                 ponto_3              */


    int colisao[4] = {0, 0, 0, 0};

    if(mapa[ponto_1[1]/tile][ponto_1[0]/tile] == 1) colisao[0] = 1;
    if(mapa[ponto_2[1]/tile][ponto_2[0]/tile] == 1) colisao[1] = 1;
    if(mapa[ponto_3[1]/tile][ponto_3[0]/tile] == 1) colisao[2] = 1;
    if(mapa[ponto_4[1]/tile][ponto_4[0]/tile] == 1) colisao[3] = 1;

    if(colisao[0] == 1 && colisao[1] == 1 && colisao[2] == 1 && colisao[3] == 1)
    //Caso improvavel em que o quadrado entra totalmente dentro de uma parede.
    //Arbitrariamente decidi que a reacao seria empurra-lo pra diagonal superior esquerda.
    {
        pJogador->x -= (pJogador->x % tile);
        pJogador->y -= (pJogador->y % tile);
    }
    else
    {
        if(colisao[0] == 1)
        //colidindo em cima.
        {
            pJogador->y += (tile - 1);
            pJogador->y -= (pJogador->y % tile);
        }
        if(colisao[1] == 1)
        //colidindo na direita
        {
            pJogador->x -= (pJogador->x % tile);
        }
        if(colisao[2] == 1)
        //colidindo embaixo
        {
            pJogador->y -= (pJogador->y % tile);
        }
        if(colisao[3] == 1)
        //colidindo na esquerda
        {
            pJogador->x += (tile - 1);
            pJogador->x -= (pJogador->x % tile);
        }
    }
}

void posicionaCamera2(Player *pJogador, Camera2D *pCamera, int largura_tela, int altura_tela)
{
    int cameraX, cameraY;
    if(pJogador->x + pJogador->largura/2 >= (largura_tela*3)/ 4) cameraX = (largura_tela*3)/ 4;
    else if(pJogador->x + pJogador->largura/2 <= largura_tela/4) cameraX = largura_tela/4;
    else cameraX = pJogador->x + pJogador->largura/2;

    if(pJogador->y + pJogador->altura/2 >= (altura_tela*3)/ 4) cameraY = (altura_tela*3)/ 4;
    else if(pJogador->y + pJogador->altura/2 <= altura_tela/ 4) cameraY = altura_tela/4;
    else cameraY = pJogador->y + pJogador->altura/2;


    pCamera->target = (Vector2){cameraX, cameraY};
}

void introCamera(Camera2D *pCamera, float *zoom, float timer)
{
    *zoom += 0.02 - timer/150;
    if(*zoom > 2.0) *zoom = 2.0;
    pCamera->zoom = *zoom;
}

void comportamentoBoss(Boss *ACM, float *timer, Player *jogador, Projetil_1 centrais[30], Projetil_1 esquerda[30], Projetil_1 direita[30], Bloco blocos[30], Bloco *python, int mapa[23][32])
{
    DrawTexture(ACM->textura, ACM->x, ACM->y, RAYWHITE);
    if(sqrt(pow((float)(ACM->x + 38 - jogador->x - 16), 2)+pow((float)(ACM->y + 57 - jogador->y - 16), 2)) < 45)
    {
        jogador->alive_flag = 0;
    }

    if(ACM -> comportamento == 0 && ACM->vida > 0)
    //Retornar para o centro e se preparar pro proximo ataque.
    {
        if(abs(ACM->x - 473) > 3)
        {
            if(ACM->x - 473 > 0) ACM->x -= 3;
            if(ACM->x - 473 < 0) ACM->x += 3;
        }
        else
        {
            ACM->x = 473;
        }


        if(abs(ACM->y - 155) > 3)
        {
            if(ACM->y - 155 > 0) ACM->y -= 3;
            if(ACM->y - 155 < 0) ACM->y += 3;
        }
        else
        {
            ACM->y = 155;
        }



        if(*timer >= 3.0 && !IsSoundPlaying(ACM->alerta))
        {
            PlaySound(ACM->alerta);
        }
        if(*timer >= 5.0)
        {
            *timer = 0.0;
            ACM->comportamento = GetRandomValue(1, 2);
        }
    }
    else if(ACM -> comportamento == 1 && ACM->vida > 0)
    //Modo Bullet Hell.
    {
        ACM->y += (int) (3 * cos(3.14 *(*timer)));
        ACM->x += (int) (3.5 * cos(3.14 *(*timer)/5));

        int i = (int)fmod(((*timer) * 10), 30);

        if(centrais[i].flag_ativo == 0)
        {
            PlaySound(ACM->disparo);
            float dx_centrais = (float)(jogador->x - (ACM->x + 40));
            float dy_centrais = (float)(jogador->y - (ACM->y + 40));
            centrais[i].x = (ACM->x + 40);
            centrais[i].y = (ACM->y + 40);
            centrais[i].velocidade_x = (int)(dx_centrais*8 / sqrt(pow(dx_centrais, 2)+pow(dy_centrais, 2)));
            centrais[i].velocidade_y = (int)(dy_centrais*8 / sqrt(pow(dx_centrais, 2)+pow(dy_centrais, 2)));
            centrais[i].flag_ativo = 1;
        }
        if(esquerda[i].flag_ativo == 0)
        {
            PlaySound(ACM->disparo);
            float modulo_desvio_lateral = (float) sqrt(pow(jogador->y - (ACM->y + 52), 2)+pow((ACM->x + 56) - jogador->x, 2));
            float desvio_lateral_x = (float) (128*(jogador->y - (ACM->y + 52))/ modulo_desvio_lateral);
            float desvio_lateral_y = (float) (128*((ACM->x + 56) - jogador->x)/modulo_desvio_lateral);
            float dx_esquerda = (float)(jogador->x - desvio_lateral_x - (ACM->x + 22));
            float dy_esquerda = (float)(jogador->y - desvio_lateral_y - (ACM->y + 52));
            esquerda[i].x = (ACM->x + 22);
            esquerda[i].y = (ACM->y + 52);
            esquerda[i].velocidade_x = (int)(dx_esquerda*8 / sqrt(pow(dx_esquerda, 2)+pow(dy_esquerda, 2)));
            esquerda[i].velocidade_y = (int)(dy_esquerda*8 / sqrt(pow(dx_esquerda, 2)+pow(dy_esquerda, 2)));
            esquerda[i].flag_ativo = 1;
        }
        if(direita[i].flag_ativo == 0)
        {
            PlaySound(ACM->disparo);
            float modulo_desvio_lateral = (float) sqrt(pow(jogador->y - (ACM->y + 52), 2)+pow((ACM->x + 56) - jogador->x, 2));
            float desvio_lateral_x = (float) (128*(jogador->y - (ACM->y + 52))/ modulo_desvio_lateral);
            float desvio_lateral_y = (float) (128*((ACM->x + 56) - jogador->x)/modulo_desvio_lateral);
            float dx_direita = (float)(jogador->x + desvio_lateral_x - (ACM->x + 56));
            float dy_direita = (float)(jogador->y + desvio_lateral_y - (ACM->y + 52));
            direita[i].x = (ACM->x + 56);
            direita[i].y = (ACM->y + 52);
            direita[i].velocidade_x = (int)(dx_direita*8 / sqrt(pow(dx_direita, 2)+pow(dy_direita, 2)));
            direita[i].velocidade_y = (int)(dy_direita*8 / sqrt(pow(dx_direita, 2)+pow(dy_direita, 2)));
            direita[i].flag_ativo = 1;
        }


        if(*timer >= 10.0)
        {
            *timer = 0.0;
            ACM->comportamento = 0;
        }
    }
    else if(ACM -> comportamento == 2 && ACM->vida > 0)
    //Blocos caindo.
    {
        int i, j = 0, k = 0;
        if((int)((*timer) * 3) <= 30)
        {
            i = (int)((*timer) * 3);
        }
        if(blocos[i].estado == 0)
        {
            if(i % 2 == 0)
            {
                do
                {
                    j = GetRandomValue(1, 21);
                    k = GetRandomValue(1, 30);
                } while(mapa[j][k] != 0);
                blocos[i].x = k * 32;
                blocos[i].y = j * 32;
                blocos[i].altura = 704.0;
                blocos[i].estado = 1;
                mapa[j][k] = 4;
            }
            else
            {
                k = (jogador->x + 16) / 32;
                j = (jogador->y + 16) / 32;
                blocos[i].x = k * 32;
                blocos[i].y = j * 32;
                blocos[i].altura = 704.0;
                blocos[i].estado = 1;
                mapa[j][k] = 4;
            }
        }
        if(i == 30 && python->estado == 0)
        {
            do
            {
                j = GetRandomValue(1, 21);
                k = GetRandomValue(1, 30);
            } while(mapa[j][k] != 0);
            python->x = k * 32;
            python->y = j * 32;
            python->altura = 704.0;
            python->estado = 1;
            mapa[j][k] = 4;
        }

        if(*timer >= 12.0)
        {
            *timer = 0.0;
            ACM->comportamento = 0;
        }

    }
}

void movimentaProjetil(Texture2D textura,Projetil_1 centrais[30], Projetil_1 esquerda[30], Projetil_1 direita[30], Player *jogador)
{
    int i = 0;
    for(i = 0; i < 30; i++)
    {
        if(centrais[i].flag_ativo != 0)
        {
            DrawTexture(textura, centrais[i].x - 6, centrais[i].y - 6, RAYWHITE);
            if(sqrt(pow(centrais[i].x - jogador->x - 16, 2) + pow(centrais[i].y - jogador->y - 16, 2)) < 6)
            {
                jogador-> alive_flag = 0;
            }
            centrais[i].x += centrais[i].velocidade_x;
            centrais[i].y += centrais[i].velocidade_y;
            if(abs(centrais[i].x - jogador->x) > 800 || abs(centrais[i].y - jogador->y) > 500)
            {
                centrais[i].flag_ativo = 0;
            }
        }
        if(esquerda[i].flag_ativo != 0)
        {
            DrawTexture(textura, esquerda[i].x - 6, esquerda[i].y - 6, RAYWHITE);
            if(sqrt(pow(esquerda[i].x - jogador->x - 16, 2) + pow(esquerda[i].y - jogador->y - 16, 2)) < 6)
            {
                jogador-> alive_flag = 0;
            }
            esquerda[i].x += esquerda[i].velocidade_x;
            esquerda[i].y += esquerda[i].velocidade_y;
            if(abs(esquerda[i].x - jogador->x) > 800 || abs(esquerda[i].y - jogador->y) > 500)
            {
                esquerda[i].flag_ativo = 0;
            }
        }
        if(direita[i].flag_ativo != 0)
        {
            DrawTexture(textura, direita[i].x - 6, direita[i].y - 6, RAYWHITE);
            if(sqrt(pow(direita[i].x - jogador->x - 16, 2) + pow(direita[i].y - jogador->y - 16, 2)) < 6)
            {
                jogador-> alive_flag = 0;
            }
            direita[i].x += direita[i].velocidade_x;
            direita[i].y += direita[i].velocidade_y;
            if(abs(direita[i].x - jogador->x) > 800 || abs(direita[i].y - jogador->y) > 500)
            {
                direita[i].flag_ativo = 0;
            }
        }
    }
}

void comportamentoBloco(Bloco blocos[30], Bloco *python, Player *jogador, Boss *ACM, int mapa[23][32])
{
    int i;
    for(i = 0; i < 30; i++)
    {
        if(blocos[i].estado == 1)
        {
            DrawEllipse(blocos[i].x + 16, blocos[i].y + 23, 15.0, 9.0, BLACK);
            DrawTexture(ACM->c, blocos[i].x, blocos[i].y - (int)blocos[i].altura, RAYWHITE);
            blocos[i].altura -= 2800 * GetFrameTime();
            //if(i == 0) printf("%f\n", blocos[i].altura);
            if(blocos[i].altura < 32.0 && blocos[i].altura > 0.0)
            {
                blocos[i].hitbox = 1;
            }
            else if(blocos[i].altura < 0.0)
            {
                PlaySound(ACM->disparo);
                blocos[i].altura = 0;
                blocos[i].hitbox = 0;
            }
            if(blocos[i].altura == 0.0)
            {
                blocos[i].estado = 2;
            }

        }
        else if(blocos[i].estado == 2)
        {
            DrawTexture(ACM->c, blocos[i].x, blocos[i].y, RAYWHITE);
            if(jogador->x + 16 > blocos[i].x && jogador->x + 16 < blocos[i].x + 32 &&
               jogador->y > blocos[i].y && jogador->y < blocos[i].y + 32)
            //colisao com a parte superior do player
            {
                jogador->y += 31;
                jogador->y -= jogador->y %32;
            }
            if(jogador->x + 32 > blocos[i].x && jogador->x + 32 < blocos[i].x + 32 &&
               jogador->y + 16 > blocos[i].y && jogador->y + 16 < blocos[i].y + 32)
            //colisao com a parte direita do player
            {
                jogador->x -= jogador->x % 32;
            }
            if(jogador->x + 16 > blocos[i].x && jogador->x + 16 < blocos[i].x + 32 &&
               jogador->y + 32 > blocos[i].y && jogador->y + 32 < blocos[i].y + 32)
            //colisao com a parte inferior do player
            {
                jogador->y -= jogador->y % 32;
            }
            if(jogador->x > blocos[i].x && jogador->x < blocos[i].x + 32 &&
               jogador->y + 16 > blocos[i].y && jogador->y + 16 < blocos[i].y + 32)
            //colisao com a parte esquerda do player
            {
                jogador->x += 31;
                jogador->x -= jogador->x % 32;
            }
            blocos[i].altura += 140 * GetFrameTime();
            if(blocos[i].altura > 704.0)
            {
                blocos[i].altura = 704.0;
                blocos[i].estado = 0;
                mapa[blocos[i].y/32][blocos[i].x/32] = 0;
            }
        }
        else if(blocos[i].estado == 3)
        {
            blocos[i].estado = 0;
            mapa[blocos[i].y/32][blocos[i].x/32] = 0;
        }


        if(blocos[i].hitbox == 1 && sqrt(pow(jogador->x - blocos[i].x, 2) + pow(jogador->y - blocos[i].y, 2)) <  30)
        {
            jogador->alive_flag = 0;
        }
    }

    if(python->estado == 1)
    {
        DrawEllipse(python->x + 16, python->y + 23, 15.0, 9.0, BLACK);
        DrawTexture(ACM->python, python->x, python->y - (int)python->altura, RAYWHITE);
        python->altura -= 2800 * GetFrameTime();
        if(python->altura < 32.0 && python->altura > 0.0)
        {
            python->hitbox = 1;
        }
        else if(python->altura < 0.0)
        {
            PlaySound(ACM->colisao);
            python->altura = 0;
            python->hitbox = 0;
        }
        if(python->altura == 0.0)
        {
            python->estado = 2;
        }

    }
    else if(python->estado == 2)
    {
        DrawTexture(ACM->python, python->x, python->y, RAYWHITE);
        python->altura += 120 * GetFrameTime();
        if(python->altura >= 704.0)
        {
            python->altura = 704.0;
            python->estado = 0;
            mapa[python->y/32][python->x/32] = 0;
        }
        if(sqrt(pow(jogador->x - python->x, 2) + pow(jogador->y - python->y, 2)) <  32)
        {
            float dx = (float)(ACM->x + 39 - python->x);
            float dy = (float)(ACM->y + 57 - python->y);
            float modulo = sqrt(pow(dx, 2) + pow(dy, 2));
            python->vx = (int) 10*(dx / modulo);
            python->vy = (int) 10*(dy / modulo);
            python->estado = 3;
            mapa[python->y/32][python->x/32] = 0;
        }
    }
    else if(python->estado == 3)
    {
        DrawTexture(ACM->python, python->x, python->y, RAYWHITE);
        python->x += python->vx;
        python->y += python->vy;
        if(sqrt(pow(ACM->x + 39 - python->x - 16, 2) + pow(ACM->y + 57 - python->y - 16, 2)) <  40)
        {
            PlaySound(ACM->impacto);
            ACM->vida -= 20;
            if(ACM->vida < 0) ACM->vida = 0;
            python->estado = 0;
        }
        if(sqrt(pow(jogador->x - python->x, 2) + pow(jogador->y - python->y, 2)) >  800)
        {
            python->estado = 0;
        }

    }

    if(python->hitbox == 1 && sqrt(pow(jogador->x - python->x, 2) + pow(jogador->y - python->y, 2)) <  34)
    {
        jogador->alive_flag = 0;
    }
}

void desenhaVidaBoss(Boss *ACM)
{
    DrawText("ACM", 40, 670, 30, BLACK);
    DrawRectangle(108, 670, 810, 38, BLACK);
    DrawRectangle(112, 674, ACM->vida*8, 30, GREEN);
}
