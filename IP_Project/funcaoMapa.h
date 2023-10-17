#define FPS 60

int funcaoMapa(float tempoMusica){

    Texture2D Mapa1T = Mapa1H;
    Texture2D Mapa2T = Mapa2H;
    Texture2D Mapa3T = Mapa3H;
    Texture2D Mapa4T = Mapa4H;
    Texture2D Mapa5T = Mapa5H;
    Music musicaInicio = LoadMusicStream("resources/crazyfrog.mp3");
    SeekMusicStream(musicaInicio, tempoMusica);
    PlayMusicStream(musicaInicio);


    Rectangle Mapas[5] = {{204.8, 230, 229, 161}, {614.4, 230, 229, 161}, {74, 500, 229, 161}, {396, 500, 229, 161}, {720, 500, 229, 161}};
    Vector2 mousePointH = {0.0f, 0.0f};
    int flags[5];


    while (!WindowShouldClose())
    {
        UpdateMusicStream(musicaInicio);
        mousePointH = GetMousePosition();



        for (int i = 0; i < 5; i++) {
            if (CheckCollisionPointRec(mousePointH, Mapas[i])) {
                     flags[i]= 1;
                     if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                         UnloadTexture(Mapa1T);
                         UnloadTexture(Mapa2T);
                         UnloadTexture(Mapa3T);
                         UnloadTexture(Mapa4T);
                         UnloadTexture(Mapa5T);
                         return  i;
                     }
                 }
                 else flags[i] = 0;
        }


        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("ESCOLHA O MAPA", 290, 40, 50, PINK);
        DrawText("Ramalho de Oliveira", 185, 192, 30, RED);
        DrawText("BomberMan", 645, 192, 30, PURPLE);
        DrawText("PACMAN", 125, 467, 30, YELLOW);
        DrawText("BUBBLE BOBBLE", 385, 467, 30, BROWN);
        DrawText("DIG DUG", 770, 467, 30, DARKGREEN);
        DrawRectangle(204.8, 230, 229, 160, BLACK);
        DrawRectangle(614.4, 230, 229, 160, BLACK);
        DrawRectangle(74, 500, 229, 160, BLACK);
        DrawRectangle(396, 500, 229, 160, BLACK);
        DrawRectangle(720, 500, 229, 160, BLACK);
        DrawTexture(Mapa5T, 720, 505, RAYWHITE);
        DrawTexture(Mapa4T, 396, 500, RAYWHITE);
        DrawTexture(Mapa3T, 74, 505, RAYWHITE);
        DrawTexture(Mapa2T, 614.4, 233, RAYWHITE);
        DrawTexture(Mapa1T, 204.8, 233, RAYWHITE);


        if (flags[0] == 1) {DrawRectangleLines(204.8, 230, 229, 160, RED);}
        else DrawRectangleLines(204.8, 230, 229, 160, WHITE);
        if (flags[1] == 1) {DrawRectangleLines(614.4, 230, 229, 160, RED);}
        else DrawRectangleLines(614.4, 230, 229, 160, WHITE);
        if (flags[2] == 1) {DrawRectangleLines(74, 500, 229, 160, RED);}
        else DrawRectangleLines(74, 500, 229, 160, WHITE);
        if (flags[3] == 1) {DrawRectangleLines(396, 500, 229, 160, RED);}
        else DrawRectangleLines(396, 500, 229, 160, WHITE);
        if (flags[4] == 1) {DrawRectangleLines(720, 500, 229, 160, RED);}
        else DrawRectangleLines(720, 500, 229, 160, WHITE);


        EndDrawing();
    }

    UnloadTexture(Mapa1T);
    UnloadTexture(Mapa2T);
    UnloadTexture(Mapa3T);
    UnloadTexture(Mapa4T);
    UnloadTexture(Mapa5T);
    UnloadMusicStream(musicaInicio);

    CloseWindow();

    return -1;
}
