
#define CInH LoadTexture("resources/CIn.png")
#define SomH LoadTexture("resources/Som.png")
#define SemSomH LoadTexture("resources/FSom.png")
#define PauseH LoadTexture("resources/pause2.png")
#define FecharPauseH LoadTexture("resources/Fechar.png")

#define BoiH LoadTexture("resources/boi.png")
#define MuliroH LoadTexture("resources/Muliro.png")
#define MuliroH2 LoadTexture("resources/muliro3.png")
#define InimigoH LoadTexture("resources/spritexb-4896.png")
#define MarcondesH LoadTexture("resources/marcondes.png")
#define LuquetH LoadTexture("resources/luquet.png")
#define BoncH LoadTexture("resources/bonc.png")
#define DanielH LoadTexture("resources/daniel.png")
#define PFH LoadTexture("resources/pf.png")
#define RenatoH LoadTexture("resources/renato.png")

#define MallocH LoadTexture("resources/Malloc.png")
#define ReallocH LoadTexture("resources/Realloc.png")
#define CallocH LoadTexture("resources/Calloc.png")
#define MH LoadTexture("resources/M.png")
#define RH LoadTexture("resources/R.png")
#define CH LoadTexture("resources/C.png")

#define BackgroundH LoadTexture("resources/Background.png")
#define ParedeH LoadTexture("resources/parede.png")
#define BlocoH LoadTexture("resources/bloco.png")

#define Mapa1H LoadTexture("resources/Mapa1.png")
#define Mapa2H LoadTexture("resources/Mapa2.png")
#define Mapa3H LoadTexture("resources/Mapa3.png")
#define Mapa4H LoadTexture("resources/Mapa4.png")
#define Mapa5H LoadTexture("resources/Mapa5.png")

#define PauseRetH (Rectangle){970, 5, 50, 50}
#define ColocarTirarSomRecH (Rectangle){492, 330, 40, 40}
#define FecharPauseRecH (Rectangle){723, 189, 40, 40}
#define IrParaMenuH (Rectangle){300, 410, 364, 40}

#define num_monitores 7


typedef struct{

    Texture2D som;
    Texture2D semsom;
    Texture2D pause;
    Texture2D fecharP;

} TextMenuP;


typedef struct{

    Texture2D parede;
    Texture2D bloco;
    Texture2D background;

} TextMap;

typedef struct{

    Texture2D malloc;
    Texture2D realloc;
    Texture2D calloc;

} TextLloc;


void ldTexturesChars(Character *jogador, Character *monitor){

    jogador->textura = BoiH;
    monitor[0].textura = LuquetH;
    monitor[1].textura = MarcondesH;
    monitor[2].textura = BoncH;
    monitor[3].textura = DanielH;
    monitor[4].textura = PFH;
    monitor[5].textura = RenatoH;
    monitor[6].textura = MuliroH2;

}


void unldTexturesChars(Character *jogador, Character *monitor){

    UnloadTexture(jogador->textura);
    for(int i=0; i<num_monitores;i++){
        UnloadTexture(monitor[i].textura);
    }

}


void ldTexturesMenuP(TextMenuP *textmenu){

    textmenu->som = SomH;
    textmenu->semsom = SemSomH;
    textmenu->pause = PauseH;
    textmenu->fecharP = FecharPauseH;

}

void menuP(int menuFlag, int flagSomH, TextMenuP *textmenu){

        DrawRectangle(256, 184, 512, 300, BLUE);
        DrawTexture(textmenu->fecharP, 723, 189, RAYWHITE);
        DrawText("JOGO PAUSADO", 280, 240, 60, LIGHTGRAY);
        if (menuFlag == 1) {DrawText("IR PARA O MENU", 300, 410, 40, ORANGE);}
        else DrawText("IR PARA O MENU", 300, 410, 40, YELLOW);
        if (flagSomH % 2 != 0) {DrawTexture(textmenu->som, 492, 330, RAYWHITE);}
        else DrawTexture(textmenu->semsom, 492, 330, RAYWHITE);
}



void unldTexturesMenuP(TextMenuP *textmenu){

    UnloadTexture(textmenu->som);
    UnloadTexture(textmenu->semsom);
    UnloadTexture(textmenu->pause);
    UnloadTexture(textmenu->fecharP);

}


void ldTexturesMap(TextMap *textmap){

    textmap->parede = ParedeH;
    textmap->bloco = BlocoH;
    textmap->background = BackgroundH;
}


void unldTexturesMap(TextMap *textmap){

    UnloadTexture(textmap->parede);
    UnloadTexture(textmap->bloco);
    UnloadTexture(textmap->background);
}


void ldTexturesLloc(TextLloc *textlloc){

    textlloc->malloc = MH;
    textlloc->realloc = RH;
    textlloc->calloc = CH;

}

void unldTexturesLloc(TextLloc *textlloc){

    UnloadTexture(textlloc->malloc);
    UnloadTexture(textlloc->realloc);
    UnloadTexture(textlloc->calloc);

}

void unldTexturesGame (TextMenuP *textmenu, Character *jogador, Character *monitor, TextMap *textmap, TextLloc *textlloc){

    unldTexturesMenuP(textmenu);
    unldTexturesChars(jogador, monitor);
    unldTexturesMap(textmap);
    unldTexturesLloc(textlloc);
}
