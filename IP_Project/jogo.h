#include "basic.h"
#include "texturas.h"
#include "objetos.h"
#include "mapas.h"
#include "finale.h"

#define FPS 60




int jogo(int screenWidth, int screenHeight, int mapaNum)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    int i, j;

    int flagSomH = 1;
    int contadorH = 0;
    int PauseFlagH = 0;
    int menuFlag = 0;
    int delay = 0;

    Vector2 mousPointH = {0, 0};

    TextMenuP textmenu;
    ldTexturesMenuP(&textmenu);

    int tamx = 23, tamy = 32;
    int mapa[tamx][tamy];

    for(i = 0; i < tamx; i++){
        for(j = 0; j < tamy; j++){
            mapa[i][j] = mapas[mapaNum][i][j];
        }
    }

    TextMap textmap;
    ldTexturesMap(&textmap);
    Music musicaJogo = LoadMusicStream("resources/BreakFree.mp3");
    UpdateMusicStream(musicaJogo);
    PlayMusicStream(musicaJogo);

    int tile = 32;



    Character jogador, monitor[num_monitores];


    ldTexturesChars(&jogador, monitor);

    jogador.alive_flag = 1;
    jogador.anim = initAnimStandard(jogador.textura);
    jogador.pos = (Vector2){(float)screenWidth/2, (float)screenHeight/2 +10};
    jogador.largura = tile;
    jogador.altura = tile;



    for(i=0; i<num_monitores;i++) {
        monitor[i].altura = tile;
        monitor[i].largura = tile;
        monitor[i].anim = initAnimStandard(monitor[i].textura);
        spread3(tile, screenWidth, screenHeight, &monitor[i], mapa, jogador);
    }


    Food trash1, trash2[MaxTrash], trash3;

    trash1.size = (Vector2){tile, tile};
    trash1.color = BLUE;
    trash1.active = false;

    for(i = 0; i < MaxTrash; i++){
        trash2[i].size = (Vector2){tile, tile};
        trash2[i].color = RED;
        trash2[i].active = false;
    }

    trash3.size = (Vector2){tile, tile};
    trash3.color = LIME;
    trash3.active = false;

    int points = 0, maxpoint = 15;

    for(i = 0; i < MaxTrash; i++){
        spread2 (tile, screenWidth, screenHeight, &trash2[i], mapa);
    }

    spread2 (tile, screenWidth, screenHeight, &trash3, mapa);


    TextLloc textlloc;
    ldTexturesLloc(&textlloc);


    //float wallWidth = tile, wallHeight = tile;

    float timer = 0.0, zoom = 1.0;
    Camera2D camera = initCamera(jogador, screenWidth, screenHeight);

    int FramesM=0, SegPassados=0, MinPassados=0;
    int countCalloc=2;

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        FramesM++;

        if(FramesM==60)
        {
            SegPassados++;
            FramesM=0;
        }

        if(SegPassados==60)
        {
            MinPassados++; //passou um min
            SegPassados=1;
        }

        if(MinPassados>=1)
            jogador.alive_flag=false;

        if (!IsMusicStreamPlaying(musicaJogo) && flagSomH%2 != 0) {
            PlayMusicStream(musicaJogo);
        }
        UpdateMusicStream(musicaJogo);
        timer += GetFrameTime();
        //introzinha camera muito bala.
        if(timer < 3.0)zoom += 0.02 - timer/150;
        if(zoom > 2.0) zoom = 2.0;
        camera.zoom = zoom;

        posicionaCamera(&jogador, &camera, screenWidth, screenHeight);


        mousPointH = GetMousePosition();

        if (CheckCollisionPointRec(mousPointH, PauseRetH) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                PauseFlagH = 1;
        }
        if (PauseFlagH == 1) {
            //test2 -> velocity = (Vector2) {0.0 , 0.0};
            contadorH++;

            if (CheckCollisionPointRec(mousPointH, FecharPauseRecH) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                PauseFlagH = 0;
            }
            if (CheckCollisionPointRec(mousPointH, ColocarTirarSomRecH) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && contadorH > 5) {
                flagSomH++;
                if (flagSomH % 2 != 0) {ResumeMusicStream(musicaJogo);}
                else PauseMusicStream(musicaJogo);
                contadorH = 0;
            }
            if (CheckCollisionPointRec(mousPointH, IrParaMenuH)) {
                menuFlag = 1;
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

                    unldTexturesGame (&textmenu, &jogador, monitor, &textmap, &textlloc);

                    return 2;
                }
            }
            else menuFlag = 0;
        }

        if(!jogador.alive_flag){
            delay++;
            if(delay >= FPS*4){
                unldTexturesGame (&textmenu, &jogador, monitor, &textmap, &textlloc);
                return 0;
            }
        }

        if(points >= maxpoint){
            PauseFlagH = 2;
            delay++;
            if(delay >= FPS*4){
                unldTexturesGame (&textmenu, &jogador, monitor, &textmap, &textlloc);
                return finale(screenWidth, screenWidth);
            }
        }

        // Update
        //----------------------------------------------------------------------------------

        if (PauseFlagH == 0) {


            if(jogador.alive_flag){
                moveJogador(&jogador);
                checaColisaoJogador(mapa, &jogador, 32);
            }

            for(i = 0; i < num_monitores; i++){
                inimigoSegue(&monitor[i], &jogador);
                checaColisaoJogador(mapa, &monitor[i], 32);
            }

                for(i = 0; i < MaxTrash; i++){
                    check2 (tile, screenWidth, screenHeight, jogador, &points, &trash2[i], mapa);
                }

                check2(tile, screenWidth, screenHeight, jogador, &points, &trash3, mapa);

        }

        spread1 (tile, screenWidth, screenHeight, jogador, &points, &trash1, mapa);


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

            drawMap(mapa, screenWidth, screenHeight, &textmap);




        DrawTexture(textlloc.realloc, trash1.position.x, trash1.position.y, RAYWHITE);

        for(i = 0; i < MaxTrash; i++){
            if(trash2[i].active){

                DrawTexture(textlloc.malloc, trash2[i].position.x, trash2[i].position.y, RAYWHITE);
            }
        }
        if(trash3.active==true)
            DrawTexture(textlloc.calloc, trash3.position.x, trash3.position.y, RAYWHITE);

        if(jogador.alive_flag){
            DrawTextureRec(jogador.textura, jogador.anim.rec, (Vector2){jogador.pos.x-16, jogador.pos.y-25}, RAYWHITE);
        }

        for(i = 0; i < num_monitores; i++){
            DrawTextureRec(monitor[i].textura, monitor[i].anim.rec, (Vector2){monitor[i].pos.x-16, monitor[i].pos.y-25}, RAYWHITE);
        }

        EndMode2D();


        DrawFPS(screenWidth - 90, screenHeight - 30);
        DrawTexture(textmenu.pause, 970, 5, RAYWHITE);
        DrawText(TextFormat("SCORE %4i", points), 10, 10, 40, GREEN);


        if(trash3.active==false && countCalloc>0)
        {
            SegPassados=1; countCalloc--;
            spread2 (tile, screenWidth, screenHeight, &trash3, mapa);
            DrawText(TextFormat("TIME 00:%02d", 60-SegPassados), screenWidth-400, 10, 40, GREEN);
        }

        else  DrawText(TextFormat("TIME 00:%02d", 60-SegPassados), screenWidth-400, 10, 40, GREEN);


        if(!jogador.alive_flag){
            DrawText("Free (o Boi) morreu...\nF.", 300, 450, 50, GREEN);
        }


        if (PauseFlagH == 1) {   // INTERFACE PAUSE

                menuP(menuFlag, flagSomH, &textmenu);
        }

        if(points >= maxpoint){
            DrawText("Os Llocs estao Free(tos)!", 300, 450, 50, GREEN);
        }


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    unldTexturesGame (&textmenu, &jogador, monitor, &textmap, &textlloc);
    UnloadMusicStream(musicaJogo);
    //CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 2;
}
