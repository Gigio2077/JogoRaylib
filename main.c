#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <time.h>
#include <math.h>
#include <string.h>

#define SPRITESIZE 32
#define ALTURA 530
#define LARGURA 960
#define TILE 16
#define SPEED 4
#define GRAVIDADE 0.2

bool Paused = true;


typedef struct texturas{

    Texture2D BG3;       // Carregando Texturas
    Texture2D BG1;
    Texture2D grama_textura ;
    Texture2D terra ;
    Texture2D frame;
    Texture2D trap ;
    Texture2D coin;
    //JOGADOR
    Texture2D spriterunright ;
    Texture2D spriterunleft;
    Texture2D coin_grande;
    Texture2D heart;
    Texture2D portal;
    Texture2D idleright;
    Texture2D idleleft;
    Texture2D runright;
    Texture2D runleft;
    Texture2D jumpright;
    Texture2D jumpleft;
    Texture2D mortalright;
    Texture2D mortalleft;
    Texture2D fallright;
    Texture2D fallleft;
    Texture2D ataqueright;
    Texture2D ataqueleft;
    //TECLAS
    Texture2D C,Esc,N,Q,S,V,um,dois,tres;








}TEXTURAS;

typedef struct save {
    int fase,vidas,score,trocarmapa,menustate;
} SAVE;

typedef struct entidade{

        //variaveis da fisica
        int Repouso, Pulou, ColisaoEsq,ColisaoDir,ColisaoSup;
        int spawnX,spawnY;
        Rectangle retangulo;
        float g;

        //variaveis animacoes
        int frame,currentframe;
        int direita;
        Texture2D texturaatual;
        Rectangle framerec;
        Rectangle framerecportal;

        //variavies funcionais
        int fase;
        Rectangle ataque[5];
        int atacando;

    }ENTIDADE;

typedef struct bloco_tipo{

    Rectangle retangulo;
    Texture2D textura;

    }BLOCOS;

typedef struct mapalido{
    char matriz[30][61];
    int qtdBlocosGrama,qtdCoins,qtdBlocosTerra,qtdArmadilhas;
    Rectangle BlocoTerra[200];
    Rectangle BlocoGrama[700];
    Rectangle Armadilhas[50];
    Rectangle Coins[70];
    Rectangle portal;

    int posinimigos[15][1][1];
    }MAPA;

void HUD (MAPA *mapalido,ENTIDADE *player,TEXTURAS texturas,SAVE *saveatual){

//rawRectangle(int posX, int posY, int width, int height, Color color);
DrawRectangle(0,480,960,50,DARKGRAY);

DrawText((TextFormat("x %d", mapalido->qtdCoins)), 80, 490, 35, MAROON);
DrawTexture(texturas.coin_grande,0,473,WHITE);

DrawText((TextFormat("x %d", saveatual->vidas)), 250, 490, 35, MAROON);
DrawTexture(texturas.heart,170,473,WHITE);

DrawText((TextFormat("FASE: %d", saveatual->fase)), 450, 490, 35, MAROON);

DrawText((TextFormat("fps: %d", GetFPS())), 840, 490, 35, MAROON);


}




//FUNCOES MENU
void salva_save(const SAVE *save,  char nomearquivo[]) {
    FILE *fp;
    fp = fopen(nomearquivo, "wb"); //abrir arquivo modo escrita binario
    if (fp == NULL) {
        printf("falha ao abrir arquivo.\n");
        return;
    }
    fwrite(save, sizeof(SAVE), 1, fp);
    fclose(fp);
}

void carrega_save(SAVE *save, char filename[]) {
    FILE *fp;
    fp = fopen(filename, "rb");
        if (fp == NULL) {
            printf("Save nao encontrado\n");
            return;
        }

    fread(save, sizeof(SAVE), 1, fp);
    fclose(fp);
}

void GUI(TEXTURAS texturas,SAVE *saveatual,SAVE *save1,SAVE *save2,SAVE *save3,ENTIDADE*player){


        if(IsKeyPressed(KEY_V)&&saveatual->menustate==1){Paused = !Paused;}

        if(IsKeyPressed(KEY_V)){
                    saveatual->menustate=1;
                }


        if(IsKeyPressed(KEY_N)){
                    saveatual->fase=1;
                    saveatual->trocarmapa=1;
                    saveatual->vidas=2;
                    Paused = !Paused;
                }
        if(IsKeyPressed(KEY_C)){
                    saveatual->menustate=2;
                }
        if(IsKeyPressed(KEY_S)){
                    saveatual->menustate=3;
                }







       if(IsKeyPressed(KEY_KP_1)||IsKeyPressed(KEY_ONE)){
        if(saveatual->menustate==2){
            carrega_save(saveatual,"save1.bin");
            Paused = !Paused;
            saveatual->trocarmapa = 1;
            respawna(&player,1);
        }
        if(saveatual->menustate==3){
            salva_save(saveatual,"save1.bin");
            //carrega_save(saveatual,"save1.bin");

        }
    }

    if(IsKeyPressed(KEY_KP_2)||IsKeyPressed(KEY_TWO)){
        if(saveatual->menustate==2){
            carrega_save(saveatual,"save2.bin");
            Paused = !Paused;
            saveatual->trocarmapa = 1;
            respawna(&player,1);
        }
        if(saveatual->menustate==3){
            salva_save(saveatual,"save2.bin");
            //carrega_save(saveatual,"save1.bin");

        }
    }

    if(IsKeyPressed(KEY_KP_3)||IsKeyPressed(KEY_THREE)){
        if(saveatual->menustate==2){
            carrega_save(saveatual,"save3.bin");
            Paused = !Paused;
            saveatual->trocarmapa = 1;
            respawna(&player,1);
        }
        if(saveatual->menustate==3){
            salva_save(saveatual,"save3.bin");
        }
    }




        switch (saveatual->menustate){

            case 1:
                DrawRectangle(LARGURA/3, 50, LARGURA/3, 450 ,LIGHTGRAY);
                DrawText("Menu",405,100,60,MAROON);

                DrawTexture(texturas.N,358,185,WHITE);
                DrawText("ovo jogo",390,180,36,MAROON);

                DrawTexture(texturas.C,358,225,WHITE);
                DrawText("arregar jogo",390,220,36,MAROON);

                DrawTexture(texturas.S,358,265,WHITE);
                DrawText("alvar jogo",390,260,36,MAROON);

                DrawTexture(texturas.V,358,305,WHITE);
                DrawText("oltar",390,300,36,MAROON);

                DrawTexture(texturas.Q,358,425,WHITE);
                DrawText("uit",390,420,36,MAROON);


            break;


            case 2:
                DrawRectangle(LARGURA/3, 50, LARGURA/3, 450 ,LIGHTGRAY);
                DrawText("Menu",405,100,60,MAROON);

                DrawText("Carregar save:",370,180,36,MAROON);


                DrawTexture(texturas.um,358,225,WHITE);
                DrawText("slot1",390,220,36,MAROON);
                DrawText((TextFormat("vidas:%d\tfase:%d", save1->vidas,save1->fase)),485,230,16,MAROON);



                DrawTexture(texturas.dois,358,265,WHITE);
                DrawText("slot2",390,260,36,MAROON);
                DrawText((TextFormat("vidas:%d\tfase:%d", save2->vidas,save2->fase)),485,270,16,MAROON);


                DrawTexture(texturas.tres,358,305,WHITE);
                DrawText("slot3",390,300,36,MAROON);
                DrawText((TextFormat("vidas:%d\tfase:%d", save3->vidas,save3->fase)),485,310,16,MAROON);


                DrawTexture(texturas.V,358,425,WHITE);
                DrawText("voltar",390,420,36,MAROON);

            break;


            case 3:
                DrawRectangle(LARGURA/3, 50, LARGURA/3, 450 ,LIGHTGRAY);
                DrawText("Menu",405,100,60,MAROON);

                DrawText("Salvar save:",370,180,36,MAROON);


                DrawTexture(texturas.um,358,225,WHITE);
                DrawText("slot1",390,220,36,MAROON);
                DrawText((TextFormat("vidas:%d\tfase:%d", save1->vidas,save1->fase)),485,230,16,MAROON);



                DrawTexture(texturas.dois,358,265,WHITE);
                DrawText("slot2",390,260,36,MAROON);
                DrawText((TextFormat("vidas:%d\tfase:%d", save2->vidas,save2->fase)),485,270,16,MAROON);


                DrawTexture(texturas.tres,358,305,WHITE);
                DrawText("slot3",390,300,36,MAROON);
                DrawText((TextFormat("vidas:%d\tfase:%d", save3->vidas,save3->fase)),485,310,16,MAROON);


                DrawTexture(texturas.V,358,425,WHITE);
                DrawText("voltar",390,420,36,MAROON);

            break;


        }



}



//FUNCOES MAPA
void leMapa(char nomemapa[], MAPA *mapalido, ENTIDADE *player){

    FILE *fp;
    fp = fopen(nomemapa, "r");
    if(fp == NULL) {
        printf("Error opening file: no such file %s",nomemapa);
        exit(1);
    }
    else {
        int qtdBlocosGrama = 0;
        int qtdCoins = 0;
        int qtdBlocosTerra = 0;
        int qtdArmadilhas = 0;


        for(int i = 0; i<31; i++) {
            fgets((mapalido->matriz[i]), 70, fp);

        }
        fclose(fp);

        char currentchar;
        char hashatag = '#';
        char T = 'T';
        char X = 'X';
        char J = 'J';
        char C = 'C';
        char P = 'P';

        for(int i=0; i<30; i++) {
            for(int j=0; j<61; j++) {
                currentchar = mapalido->matriz[i][j];

                switch(currentchar) {
                    case 'J':
                        player->spawnX = TILE*j;
                        player->spawnY = TILE*i;
                        player->Repouso = 1;
                        player->ColisaoDir = 0;
                        player->ColisaoEsq = 0;
                        player->ColisaoSup = 0;
                        player->Pulou = 0;
                        player->direita = 1;
                        player->frame = 0;
                        for(int z = 0;z<5;z++){
                        player->ataque[z].x=-100;}

                        break;
                    case '#':
                        qtdBlocosGrama++;
                        break;
                    case 'C':
                        qtdCoins++;
                        break;
                    case 'X':
                        qtdArmadilhas++;
                        break;
                    case 'T':
                        qtdBlocosTerra++;
                        break;
                    case 'P':
                        mapalido->portal.x = TILE*j;
                        mapalido->portal.y = TILE*i;
                        mapalido->portal.width = 14;
                        mapalido->portal.height = 53;



                    default:
                        // caso não seja nenhum dos caracteres desejados, não faz nada
                        break;
                }
            }
        }
        printf("\nCoins %d\n",qtdCoins);
        mapalido->qtdBlocosGrama = qtdBlocosGrama;
        mapalido->qtdCoins = qtdCoins;
        mapalido->qtdBlocosTerra = qtdBlocosTerra;
        mapalido->qtdArmadilhas = qtdArmadilhas;

        int index = 0;
            for( int i=0; i<30; i++){
                for( int j=0; j<61; j++){
                    currentchar = mapalido->matriz[i][j];
                    if( currentchar==T ){
                mapalido->BlocoTerra[index].width = TILE ;
                mapalido->BlocoTerra[index].height = TILE ;
                mapalido->BlocoTerra[index].x = TILE*j ;
                mapalido->BlocoTerra[index].y = TILE*i ;
                index++;
            }}}
        index = 0;
            for( int i=0; i<30; i++){
                for( int j=0; j<61; j++){
                    currentchar = mapalido->matriz[i][j];
                    if( currentchar==hashatag ){
                mapalido->BlocoGrama[index].width = TILE ;
                mapalido->BlocoGrama[index].height = TILE ;
                mapalido->BlocoGrama[index].x = TILE*j ;
                mapalido->BlocoGrama[index].y = TILE*i ;
                index++;
            }}}
        index = 0;
            for( int i=0; i<30; i++){
                for( int j=0; j<61; j++){
                    currentchar = mapalido->matriz[i][j];
                    if( currentchar==X ){
                mapalido->Armadilhas[index].width = TILE+1 ;
                mapalido->Armadilhas[index].height = TILE+1 ; //esses +1 e menos 1 é pra ajustar a colisao com o espinho
                mapalido->Armadilhas[index].x = (TILE*j)-1 ;
                mapalido->Armadilhas[index].y = (TILE*i)-1 ;
                index++;
            }}}
        index = 0;
            for( int i=0; i<30; i++){
                for( int j=0; j<61; j++){
                    currentchar = mapalido->matriz[i][j];
                    if( currentchar==C ){
                mapalido->Coins[index].width = TILE ;
                mapalido->Coins[index].height = TILE ;
                mapalido->Coins[index].x = (TILE*j) ;
                mapalido->Coins[index].y = (TILE*i) ;
                index++;
            }}}
        index = 0;

    }
}

void init_nome_mapas(char nome_mapas[][18]) {
    for(int i = 1; i<10; i++){
        sprintf(nome_mapas[i], "mapas/mapa%d.txt", i);
    }

    for(int i = 1; i<10; i++){
        printf("\nA string em nome_mapas[%d] eh:%s",i,nome_mapas[i]);

    }
}

void renderiza_mapa(MAPA *mapalido,ENTIDADE *player,TEXTURAS texturas){

                //TROCAR BACKGROUND DE ACORDO COM player.fase
                //animar background

                Vector2 position_player = {player->retangulo.x,player->retangulo.y};
                Vector2 position_portal = {mapalido->portal.x,mapalido->portal.y};

                DrawTexture(texturas.BG1, 0, 0, WHITE);
                player->framerecportal.height = 42;

                //PORTAL
                DrawTextureRec(texturas.portal, player->framerecportal, position_portal, WHITE);


                player->framerecportal.height = 16;

                for(int k = 0; k<(mapalido->qtdCoins); k++){
                Vector2 position_portal = {mapalido->Coins[k].x,mapalido->Coins[k].y};
                      DrawTextureRec(texturas.coin,
                                     player->framerecportal,
                                     position_portal,
                                     WHITE);

                }
                for(int k = 0; k<(mapalido->qtdBlocosTerra); k++){
                                DrawTexture(texturas.terra,
                                            mapalido->BlocoTerra[k].x,
                                            mapalido->BlocoTerra[k].y,
                                            WHITE);
                                            }
                for(int k = 0; k<(mapalido->qtdBlocosGrama); k++){
                                DrawTexture(texturas.grama_textura,
                                            mapalido->BlocoGrama[k].x,
                                            mapalido->BlocoGrama[k].y,
                                            WHITE);

                                            }
                for(int k = 0; k<mapalido->qtdArmadilhas; k++){
                Vector2 position_portal = {mapalido->Armadilhas[k].x,mapalido->Armadilhas[k].y};
                        DrawTextureRec(texturas.trap,
                                     player->framerecportal,
                                     position_portal,
                                     WHITE);}


            //DrawTextureRec(texturas.spriterunright, player->framerec, position_player, WHITE);


    }



//--------------------------------------------------------------------------------------

//FUNCOES PLAYER

//--------------------------------------------------------------------------------------

void atualizaPlayer(ENTIDADE *player){
//atualiza frameccounter e estados para default
        player->ColisaoDir = 0;
        player->ColisaoEsq = 0;
        player->ColisaoSup = 0;
        player->Repouso = 0;
        player->frame++;

    if (player->frame >= (8))
        {
            player->frame = 0;
            player->currentframe++;
            if (player->currentframe > 4) player->currentframe = 0;

            player->framerec.x = (float)player->currentframe*SPRITESIZE;
            player->framerecportal.x = (float)player->currentframe*TILE;

        }

}

void spritesPlayer(ENTIDADE *player,TEXTURAS texturas){

    Texture2D textura_atual;
    Vector2 position_player = {player->retangulo.x+4,player->retangulo.y+4};
    if(!IsKeyDown(KEY_LEFT)&&!(IsKeyDown(KEY_RIGHT)&&player->Repouso)){
            if(player->direita){textura_atual=texturas.idleright;}
            else{textura_atual=texturas.idleleft;}
            }
    if(player->Pulou&&player->g<5){
            if(player->direita){textura_atual=texturas.jumpright;}
            else{textura_atual=texturas.jumpleft;}
            }
    if(player->Pulou&&player->g>5){
            if(player->direita){textura_atual=texturas.mortalright;}
            else{textura_atual=texturas.mortalleft;}
            }
    if(IsKeyDown(KEY_LEFT)&&!player->g<5&&!player->Pulou){
            textura_atual=texturas.runleft;}
    if(IsKeyDown(KEY_RIGHT)&&!player->g<5&&!player->Pulou){
            textura_atual=texturas.runright;}
    if(!player->Pulou&&player->g>3){
            if(player->direita){textura_atual=texturas.fallright;}
            else{textura_atual=texturas.fallleft;}
            }
    DrawTextureRec(textura_atual, player->framerec, position_player, WHITE);
}

void respawna(ENTIDADE *player,int morreu){
    if(IsKeyDown(KEY_R) ||
      ((player->retangulo.x>960||player->retangulo.x<0)||(player->retangulo.y>480||player->retangulo.y<0))||
       morreu==1)
        {
            printf("respawn\n");
            player->g=0;
            player->Pulou=0;
            player->Repouso=0;
            player->retangulo.x = player->spawnX;
            player->retangulo.y = player->spawnY;
        }

    }

int haveraColisao (Rectangle player, Rectangle parede, int delta, int direcao){
    switch(direcao)
        {
            case 1://ESQUERDA
                player.x-=delta;
                if(CheckCollisionRecs(parede, player)){return 1;}
                else{return 0;}
                break;

            case 2://CIMA
                player.y-=delta;
                if(CheckCollisionRecs(parede, player)){return 1;}
                else{return 0;}
                break;

            case 3:// DIREITA
                player.x+=delta;
                if(CheckCollisionRecs(parede, player)){return 1;}
                else{return 0;}
                break;

            case 4:// BAIXO
                player.y+=delta;
                if(CheckCollisionRecs(parede, player)){return 1;}
                else{return 0;}
                break;

            default:
                return 0;
        }


}

void movimento(ENTIDADE *player) {


    if ((IsKeyDown(KEY_LEFT)) && !(player->ColisaoEsq))
        {
            player->retangulo.x -= SPEED;
            player->Repouso=0;
            player->direita = 0;

        }

    if ((IsKeyDown(KEY_UP)) && !(player->ColisaoSup) && player->Repouso)
        {
            player->Repouso = 0;
            player->Pulou = 1;
        }

    if ((IsKeyDown(KEY_RIGHT)) && !(player->ColisaoDir))
        {
            player->retangulo.x += SPEED;
            player->Repouso=0;
            player->direita = 1;



        }
}

void gravidade(ENTIDADE *player) {

    if (player->Repouso)
        {
            player->g=0;
            return;
        }
    //pulo
    if (!(player->Repouso) && player->Pulou)
        {
            player->g += GRAVIDADE;
            if(player->g >0.7){
                player->retangulo.y -= SPEED * 2;
                player->retangulo.y += player->g;
            }
        }
    //queda-livre: bateu no teto ou caiu
    if (!(player->Repouso) && !player->Pulou)
        {
            player->g += GRAVIDADE;
            if(player->g >0.7){
                player->retangulo.y += player->g;
            }
        }

}

void checacolisoes(MAPA *mapalido, ENTIDADE *player, SAVE *saveatual){

    float ajuste = 0;

//pegar moedas
    for(int k = mapalido->qtdCoins-1; k >= 0; k--){
        if(CheckCollisionRecs(mapalido->Coins[k], player->retangulo))
            {
            mapalido->Coins[k] = mapalido->Coins[mapalido->qtdCoins-1];
            mapalido->qtdCoins--;
            }
    }
//morrer espinhos
    for(int k = 0; k<mapalido->qtdArmadilhas; k++){
        if(CheckCollisionRecs(mapalido->Armadilhas[k], player->retangulo))
            {
            saveatual->vidas--;
            player->g=0;
            player->Repouso=1;
            respawna(player,1);
            }
    }

//portal próxima fase
    if(CheckCollisionRecs(mapalido->portal, player->retangulo))
        {
        saveatual->fase++;
        saveatual->vidas++;
        saveatual->trocarmapa = 1;
        }

    for (int i = 0; i<mapalido->qtdBlocosGrama; i++)
        {
            player->ColisaoDir += haveraColisao(player->retangulo,mapalido->BlocoGrama[i],SPEED,3);
            player->ColisaoEsq += haveraColisao(player->retangulo,mapalido->BlocoGrama[i],SPEED,1);
            player->ColisaoSup+= haveraColisao(player->retangulo,mapalido->BlocoGrama[i],SPEED*2-(player->g+GRAVIDADE),2);
            player->Repouso+= haveraColisao(player->retangulo,mapalido->BlocoGrama[i],player->g+GRAVIDADE,4);

//colisão com o teto
            if(haveraColisao(player->retangulo,mapalido->BlocoGrama[i],abs(SPEED*2-(player->g+GRAVIDADE)),2))
                {
                    if(player->g>4){player->g=0;}

                    player->Pulou = 0;
                }
//colisão com o solo
            if(haveraColisao(player->retangulo,mapalido->BlocoGrama[i],player->g+GRAVIDADE,4))
                {
                ajuste = mapalido->BlocoGrama[i].y - (player->retangulo.y+player->retangulo.height) ;
                player->retangulo.y+=ajuste;
                ajuste = 0;
                player->Pulou = 0;
                player->g=0;

                }
    }
}

/*void ataques(ENTIDADE *player, TEXTURAS texturas){

    if(IsKeyDown(KEY_Q)){
            player->atacando=1;
            player->currentframe =0

    }


        while(player->atacando==1){
            if(player->currentframe!=4){
            Vector2 position_ataque = {(player->retangulo.x-5),player->retangulo.y-5};
            player->framerecportal.x = (float)player->currentframe*42;
            DrawTextureRec(texturas.ataqueright, player->framerecportal, position_ataque, WHITE);
            }
            else{player->atacando}
}
*/


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// MAIN()


    int main(){
            SetRandomSeed(time(NULL));
            char nome_mapas[10][18];
            init_nome_mapas(nome_mapas);

            Rectangle player_frame_rect = {0, 0, SPRITESIZE, SPRITESIZE};

            TEXTURAS texturas;
            ENTIDADE player;
                player.frame = 0;
                player.retangulo.width=SPRITESIZE;
                player.retangulo.height=SPRITESIZE;
            MAPA mapas[10];

            SAVE save1;SAVE save2; SAVE save3;



            SAVE saveatual;
                        saveatual.trocarmapa = 0;
                        saveatual.fase=0;
                        saveatual.menustate = 1;


    //leMapa(nome_mapas[1], &mapas[1], &player);

    //Rectangle player_rect = {((double)player.spawnX), ((int)player.spawnY), SPRITESIZE, SPRITESIZE};
            player.framerecportal = player_frame_rect;
            player.framerecportal.width = 16;
            player.framerec = player_frame_rect;
    //player.retangulo = player_rect;

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(LARGURA, ALTURA, "Jogo Raylib  ");

//----------------------------------------------------------------------------------
//TEXTURAS
    // NOTE: Texturas DEVEM ser carregadas depois da Window initialization (OpenGL context is required)
        texturas.BG3 = LoadTexture("texturas/BG3.png");        // Carregando Texturas
        texturas.BG1 = LoadTexture("texturas/BG1.png");
        texturas.grama_textura = LoadTexture("texturas/grama.png");
        texturas.terra = LoadTexture("texturas/terra.png");
        texturas.frame = LoadTexture("texturas/frame.png");
        texturas.trap = LoadTexture("texturas/trap.png");
        texturas.coin = LoadTexture("texturas/coin.png");
        texturas.spriterunright = LoadTexture("texturas/spriterunright.png");
        texturas.spriterunleft = LoadTexture("texturas/spriterunleft.png");
        texturas.coin_grande = LoadTexture("texturas/coingrande.png");
        texturas.heart= LoadTexture("texturas/heart.png");
        texturas.portal= LoadTexture("texturas/portal.png");


        //TEXTURAS PLAYER
        texturas.idleright = LoadTexture("texturas/idleright.png");
        texturas.idleleft = LoadTexture("texturas/idleleft.png");
        texturas.runright = LoadTexture("texturas/runright.png");
        texturas.runleft = LoadTexture("texturas/runleft.png");
        texturas.jumpright = LoadTexture("texturas/jumpright.png");
        texturas.jumpleft = LoadTexture("texturas/jumpleft.png");
        texturas.mortalright = LoadTexture("texturas/mortalright.png");
        texturas.mortalleft = LoadTexture("texturas/mortalleft.png");
        texturas.fallright = LoadTexture("texturas/fallright.png");
        texturas.fallleft = LoadTexture("texturas/fallleft.png");
        texturas.ataqueright = LoadTexture("texturas/ataqueright.png");
        texturas.ataqueleft = LoadTexture("texturas/ataqueleft.png");

        //TEXTURAS TECLAS
        texturas.C = LoadTexture("texturas/C-Key.png");
        texturas.Esc = LoadTexture("texturas/Esc-Key.png");
        texturas.N = LoadTexture("texturas/N-Key.png");
        texturas.Q = LoadTexture("texturas/Q-Key.png");
        texturas.S = LoadTexture("texturas/S-Key.png");
        texturas.V = LoadTexture("texturas/V-Key.png");

        texturas.um = LoadTexture("texturas/um.png");
        texturas.dois = LoadTexture("texturas/dois.png");
        texturas.tres = LoadTexture("texturas/tres.png");



//----------------------------------------------------------------------------------
    SetTargetFPS(60);
//--------------------------------------------------------------------------------------

// LOOP PRINCIPAL DO JOGO

    while (!WindowShouldClose())
    {

            carrega_save(&save1,"save1.bin");
            carrega_save(&save2,"save2.bin");
            carrega_save(&save3,"save3.bin");


        if(IsKeyPressed(KEY_ESCAPE)&& Paused==false) {
                Paused = !Paused;
                saveatual.menustate = 1;
        }



        BeginDrawing();

        ClearBackground(RAYWHITE);


        //se morrer, voltar tudo ao default(voltar ao menu inicial)
        if(saveatual.vidas==0 && Paused == false){
            saveatual.fase = 0;
            saveatual.menustate = 1;
            Paused = !Paused;
        }


        if(saveatual.trocarmapa==1)
            {
                saveatual.trocarmapa = 0;
                leMapa(nome_mapas[saveatual.fase], &mapas[saveatual.fase], &player);
                respawna(&player,1);
            }
        if(Paused){
                if(saveatual.menustate==1){SetExitKey(KEY_Q);}
                else{SetExitKey(0);}
                DrawTexture(texturas.BG1, 0, 0, WHITE);

                if(saveatual.fase>0){
                renderiza_mapa(&mapas[saveatual.fase],&player,texturas);
                spritesPlayer(&player, texturas);
                HUD(&mapas[saveatual.fase],&player,texturas,&saveatual);
                }


                GUI(texturas,&saveatual,&save1,&save2,&save3,&player);
            }

        if(!Paused){
            //funcoes principais

            SetExitKey(0);

            renderiza_mapa(&mapas[saveatual.fase],&player,texturas);

            spritesPlayer(&player, texturas);

            checacolisoes(&mapas[saveatual.fase],&player,&saveatual);

            HUD(&mapas[saveatual.fase],&player,texturas,&saveatual);


            movimento(&player);
            gravidade(&player);
            atualizaPlayer(&player);
            respawna(&player,0);
            //ataques(&player,texturas);
            }

        EndDrawing();

        //----------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
