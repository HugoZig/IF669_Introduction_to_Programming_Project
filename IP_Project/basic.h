#define FPS 60

typedef struct{

    Rectangle rec;
    int framesnumx, framesnumy, choselist;
    int DownSprites, UpSprites, LeftSprites, RightSprites;
    float framewidth, frameheight;
    int frame, count, framespeed;

} Animation;


typedef struct{
    int alive_flag;
    int largura, altura;
    Vector2 pos;
    Texture2D textura;
    Animation anim;

} Character;

typedef struct{
    Rectangle rec;
    Color cor;
    Vector2 pos;
    float x , y, altura, largura;
}Inimigo;



Camera2D initCamera(Character pers, int largura_tela, int altura_tela){

    Camera2D camera = { 0 };
    camera.target = (Vector2){ pers.pos.x + pers.largura/2, pers.pos.y + pers.largura/2 };
    camera.offset = (Vector2){ largura_tela/2.0f, altura_tela/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    return camera;

}


void posicionaCamera(Character *pJogador, Camera2D *pCamera, int largura_tela, int altura_tela)
{
    int cameraX, cameraY;
    if(pJogador->pos.x + pJogador->largura/2 >= (largura_tela*3)/ 4) cameraX = (largura_tela*3)/ 4;
    else if(pJogador->pos.x + pJogador->largura/2 <= largura_tela/4) cameraX = largura_tela/4;
    else cameraX = pJogador->pos.x + pJogador->largura/2;

    if(pJogador->pos.y + pJogador->altura/2 >= (altura_tela*3)/ 4) cameraY = (altura_tela*3)/ 4;
    else if(pJogador->pos.y + pJogador->altura/2 <= altura_tela/ 4) cameraY = altura_tela/4;
    else cameraY = pJogador->pos.y + pJogador->altura/2;


    pCamera->target = (Vector2){cameraX, cameraY};
}



Animation initAnimStandard(Texture2D textura){

    Animation anim;

    //Altere dependendo do numero de frames da animacao
    anim.framesnumx = 9;
    anim.framesnumy = 4;


    anim.choselist = 0;

    //Altere para o (numero da linha)-1 da sequencia de animacao desejada na Sprite sheet
    anim.DownSprites = 2;
    anim.UpSprites = 0;
    anim.LeftSprites = 1;
    anim.RightSprites = 3;


    anim.framewidth = ((float)textura.width)/((float)anim.framesnumx);
    anim.frameheight = ((float)textura.height)/((float)anim.framesnumy);

    Rectangle rec = {0.0f, 0.0f, anim.framewidth, anim.frameheight};
    anim.rec = rec;

    anim.frame = 0;
    anim.count = 0;

    //Aumente o valor para acelerar a animacï¿½o do movimento
    anim.framespeed = 10;

    return anim;
}


void moveJogador(Character *jogador){

    float speed = 2.0f;

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {jogador->pos.x += speed; jogador->anim.count++; jogador->anim.choselist = jogador->anim.RightSprites;}
    if (IsKeyDown(KEY_LEFT)|| IsKeyDown(KEY_A)) {jogador->pos.x -= speed; jogador->anim.count++; jogador->anim.choselist = jogador->anim.LeftSprites;}
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {jogador->pos.y -= speed; jogador->anim.count++; jogador->anim.choselist = jogador->anim.UpSprites;}
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {jogador->pos.y += speed; jogador->anim.count++; jogador->anim.choselist = jogador->anim.DownSprites;}



    jogador->anim.rec.y = jogador->anim.frameheight*jogador->anim.choselist;

    if(jogador->anim.count >= (FPS/jogador->anim.framespeed)){

        jogador->anim.count = 0;
        jogador->anim.frame++;
        if(jogador->anim.frame >= jogador->anim.framesnumx){jogador->anim.frame = 0;}
        jogador->anim.rec.x = jogador->anim.frame*jogador->anim.framewidth;

        }
}


void inimigoSegue(Character* inimigo, Character* jogador){

    float speed = 1.25f;

    if(fabs(jogador->pos.x - inimigo->pos.x) < 192 && fabs(jogador->pos.y - inimigo->pos.y) < 192 && jogador->alive_flag == 1){

    if(jogador->pos.x > inimigo->pos.x){
        inimigo->pos.x += speed;
        inimigo->anim.choselist = inimigo->anim.RightSprites;
        inimigo->anim.count++;
    }
    if(jogador->pos.y > inimigo->pos.y){
        inimigo->pos.y += speed;
        inimigo->anim.choselist = inimigo->anim.DownSprites;
        inimigo->anim.count++;
        }
    if(jogador->pos.x < inimigo->pos.x){
        inimigo->pos.x -= speed;
        inimigo->anim.choselist = inimigo->anim.LeftSprites;

        inimigo->anim.count++;
    }
    if(jogador->pos.y < inimigo->pos.y){
        inimigo->pos.y -= speed;
        inimigo->anim.choselist = inimigo->anim.UpSprites;
        inimigo->anim.count++;
    }

    if(fabs(inimigo->pos.y - jogador->pos.y) <= 5){
        if(jogador->pos.x > inimigo->pos.x){
            inimigo->anim.choselist = inimigo->anim.RightSprites;
        }
        else{
            inimigo->anim.choselist = inimigo->anim.LeftSprites;
        }
    }

    inimigo->anim.rec.y = inimigo->anim.frameheight*inimigo->anim.choselist;

    if(inimigo->anim.count >= (FPS/inimigo->anim.framespeed)){

        inimigo->anim.count = 0;
        inimigo->anim.frame++;
        if(inimigo->anim.frame >= inimigo->anim.framesnumx){inimigo->anim.frame = 0;}
        inimigo->anim.rec.x = inimigo->anim.frame*inimigo->anim.framewidth;
        }
    }

    if(fabs(inimigo->pos.x - jogador->pos.x) <= 20 && fabs(inimigo->pos.y - jogador->pos.y) <= 20 ){
        jogador->alive_flag = 0;
    }
}


void checaColisaoJogador(int mapa[23][32], Character *pJogador, int tile)
//Reposiciona o jogador numa posicao correta quando ele entra mais do que devia numa parede.
{
    int ponto_1[2] = {(pJogador->pos.x )+(pJogador->largura/2), pJogador->pos.y};
    int ponto_2[2] = {(pJogador->pos.x)+(pJogador->largura), (pJogador->pos.y)+(pJogador->altura/2)};
    int ponto_3[2] = {(pJogador->pos.x)+(pJogador->largura/2), (pJogador->pos.y)+(pJogador->altura)};
    int ponto_4[2] = {pJogador->pos.x, (pJogador->pos.y)+(pJogador->altura/2)};

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
                 ponto_3                 */


    int colisao[4] = {0, 0, 0, 0};

    if(mapa[ponto_1[1]/tile][ponto_1[0]/tile] == 1) colisao[0] = 1;
    if(mapa[ponto_2[1]/tile][ponto_2[0]/tile] == 1) colisao[1] = 1;
    if(mapa[ponto_3[1]/tile][ponto_3[0]/tile] == 1) colisao[2] = 1;
    if(mapa[ponto_4[1]/tile][ponto_4[0]/tile] == 1) colisao[3] = 1;

    if(colisao[0] == 1 && colisao[1] == 1 && colisao[2] == 1 && colisao[3] == 1)
    //Caso improvavel em que o quadrado entra totalmente dentro de uma parede.
    //Arbitrariamente decidi que a reacao seria empurra-lo pra diagonal superior esquerda.
    {
        pJogador->pos.x -= ((int)pJogador->pos.x % tile);
        pJogador->pos.y -= ((int)pJogador->pos.y % tile);
    }
    else
    {
        if(colisao[0] == 1)
        //colidindo em cima.
        {
            pJogador->pos.y += (tile - 1);
            pJogador->pos.y -= ((int)pJogador->pos.y % tile);
        }
        if(colisao[1] == 1)
        //colidindo na direita
        {
            pJogador->pos.x -= ((int)pJogador->pos.x % tile);
        }
        if(colisao[2] == 1)
        //colidindo embaixo
        {
            pJogador->pos.y -= ((int)pJogador->pos.y % tile);
        }
        if(colisao[3] == 1)
        //colidindo na esquerda
        {
            pJogador->pos.x += (tile - 1);
            pJogador->pos.x -= ((int)pJogador->pos.x % tile);
        }
    }
}
