#define MaxTrash 10

#define FPS 60



typedef struct {
    Vector2 position;
    Vector2 size;
    bool active;
    Color color;
} Food;

//static Vector2 offset = { 0 };



void spread1 (int tile, int screenWidth, int screenHeight, Character jogador, int *points, Food *food, int mapa[23][32]){

    // food position calculation
        while (!food->active)
        {
            food->position = (Vector2){ GetRandomValue(0, (screenWidth/tile) - 1), GetRandomValue(0, (screenHeight/tile) - 1) };
            if (mapa[(int)food->position.y][(int)food->position.x] == 0){

                food->position.x *= tile;
                food->position.y *= tile;
                food->active = true;
            }

        }

    //Collision
        if ((jogador.pos.x < (food->position.x + food->size.x) && (jogador.pos.x + jogador.largura) > food->position.x) &&
            (jogador.pos.y < (food->position.y + food->size.y) && (jogador.pos.y + jogador.altura) > food->position.y))
        {
            food->active = false;
            (*points) +=5;
        }

}

void spread2 (int tile, int screenWidth, int screenHeight, Food *food, int mapa[23][32]){

            int f;
            f = 0;
            while(!f){
                food->position = (Vector2){ GetRandomValue(0, (screenWidth/tile) - 1), GetRandomValue(0, (screenHeight/tile) - 1) };
                if (mapa[(int)food->position.y][(int)food->position.x] == 0){

                    food->active = true;
                    food->position.x *= tile;
                    food->position.y *= tile;
                    f = 1;

                }
            }

}


void check2 (int tile, int screenWidth, int screenHeight, Character jogador, int *points, Food *food, int mapa[23][32]){
    //Collision

            if(food->active){
                if ((jogador.pos.x < (food->position.x + food->size.x) && (jogador.pos.x + jogador.largura) > food->position.x) &&
                    (jogador.pos.y < (food->position.y + food->size.y) && (jogador.pos.y + jogador.altura) > food->position.y))
                {
                    food->active = false;
                    (*points) +=1;
                }
            }

}


void spread3 (int tile, int screenWidth, int screenHeight, Character *monitor, int mapa[23][32], Character jogador){

            int f;
            f = 0;
            while(!f){
                monitor->pos = (Vector2){ GetRandomValue(0, (screenWidth/tile) - 1), GetRandomValue(0, (screenHeight/tile) - 1) };
                if ((mapa[(int)monitor->pos.y][(int)monitor->pos.x] == 0) ){

                    monitor->pos.x *= tile;
                    monitor->pos.y *= tile;

                    if(fabs(monitor->pos.x - jogador.pos.x) >= 192 && fabs(monitor->pos.y - jogador.pos.y)){
                        f = 1;
                    }

                }
            }

}
