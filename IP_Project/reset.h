#define FPS 60


int reset(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    Rectangle opcao[2] = {{150, 375, 280, 100}, {614.4, 375, 210, 100}}; // MENU == 0     SAIR == 1

    Vector2 mousePointH = {0.0f, 0.0f};
    int flags[2];


    while (!WindowShouldClose())
    {
    mousePointH = GetMousePosition();
        for (int i = 0; i < 2; i++) {
            if (CheckCollisionPointRec(mousePointH, opcao[i])) {
                     flags[i]= 1;
                     if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                         return  i;
                     }
                 }
                 else flags[i] = 0;
        }


        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("VOCE PERDEU KKKK", 70, 100, 85, RED);
        if (flags[0] == 1) DrawText("   JOGAR\nNOVAMENTE", 160, 375, 45, PINK);
        else DrawText("   JOGAR\nNOVAMENTE", 160, 375, 40, PURPLE);
        if (flags[1] == 1) DrawText("SAIR DO\n  JOGO", 630, 375, 45, DARKBLUE);
        else DrawText("SAIR DO\n  JOGO", 630, 375, 40, DARKGREEN);

        EndDrawing();
    }

    return -1;
}
