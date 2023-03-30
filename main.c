#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <time.h>
#include <math.h>

#define SPRITESIZE 16
#define ALTURA 530
#define LARGURA 960
#define TILE 16
#define SPEED 4
#define GRAVIDADE 0.2


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

typedef struct texturas{

    Texture2D BG3;       // Carregando Texturas
    Texture2D BG1;
    Texture2D grama_textura ;
    Texture2D terra ;
    Texture2D frame;
    Texture2D trap ;
    Texture2D coin_texture;
    Texture2D spriterunright ;
    Texture2D spriterunleft;
    Texture2D coin_grande;
    Texture2D heart;




}TEXTURAS;

typedef struct entidade{

        int frame,currentframe,Repouso,Pulou,ColisaoEsq,ColisaoDir,ColisaoSup,spawnX,spawnY;
        Rectangle retangulo;
        Texture2D texturaatual;
        Rectangle framerec;
        float g;
        char Estado[10];
        /*

        J - Jump
        R - run right
        r - idle right
        L - run left
        l - idle left
        a - attack1
        A - Attack2
        f - fall
        m - mortal
        s - estático

        */
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

    int posinimigos[15][1][1];
    }MAPA;

void hud (MAPA *mapalido,ENTIDADE *player,TEXTURAS texturas){
//rawRectangle(int posX, int posY, int width, int height, Color color);
DrawRectangle(0,480,960,50,DARKGRAY);
DrawText((TextFormat("x %d", mapalido->qtdCoins)), 80, 490, 35, RED);
DrawTexture(texturas.coin_grande,0,473,WHITE);
DrawText((TextFormat("x %d", mapalido->qtdCoins)), 250, 490, 35, RED);
DrawTexture(texturas.heart,170,473,WHITE);


}

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


        for(int i = 0; i<30; i++) {
            fgets(mapalido->matriz[i], 70, fp);
            printf("%s", mapalido->matriz[i]);

        }


        fclose(fp);

        char currentchar;
        char hashatag = '#';
        char T = 'T';
        char X = 'X';
        char J = 'J';
        char C = 'C';

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
                    default:
                        // caso não seja nenhum dos caracteres desejados, não faz nada
                        break;
                }
            }
        }
        printf("Coins %d",qtdCoins);
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
    char aux[18] = "mapas/";
    int i;

    for (i = 0; i < 7; i++) {
        sprintf(nome_mapas[i], "mapa%d.txt", i + 1);
        strcat(aux, nome_mapas[i]);
        strcpy(nome_mapas[i], aux);
        strcpy(aux, "mapas/");
        }

    for (i = 0; i < 7; i++) {
        printf("O valor de mapa[%d] is: %s\n", i, nome_mapas[i]);
        }

}

void renderiza_mapa(MAPA *mapalido,ENTIDADE *player,TEXTURAS texturas){

                DrawTexture(texturas.BG1, 0, 0, WHITE);
                for(int k = 0; k<(mapalido->qtdBlocosGrama); k++){
                                DrawTexture(texturas.grama_textura,
                                            mapalido->BlocoGrama[k].x,
                                            mapalido->BlocoGrama[k].y,
                                            WHITE);
                                }

                for(int k = 0; k<(mapalido->qtdBlocosTerra); k++){
                                DrawTexture(texturas.terra,
                                            mapalido->BlocoTerra[k].x,
                                            mapalido->BlocoTerra[k].y,
                                            WHITE);
                                            }
                for(int k = 0; k<(mapalido->qtdCoins); k++){
                                DrawTexture(texturas.coin_texture,
                                            mapalido->Coins[k].x,
                                            mapalido->Coins[k].y,
                                            WHITE);
                                if(CheckCollisionRecs(mapalido->Coins[k], player->retangulo))
                                        {
                                            mapalido->Coins[k].x = -100;
                                            mapalido->qtdCoins--;
                                            printf("\nmoedas restantes:%d",mapalido->qtdCoins);
                                        }
                                            }
                for(int k = 0; k<mapalido->qtdArmadilhas; k++){
                                DrawTexture(texturas.trap,
                                            mapalido->Armadilhas[k].x,
                                            mapalido->Armadilhas[k].y,
                                            WHITE);
                                if(CheckCollisionRecs(mapalido->Armadilhas[k], player->retangulo))
                                {
                                    player->g=0;
                                    player->Repouso=1;
                                    respawna(player);
                                }
                            }

            Vector2 position = {player->retangulo.x,player->retangulo.y};
            DrawTextureRec(texturas.spriterunleft, player->framerec, position, WHITE);


}

void atualizaPlayer(ENTIDADE *player){
//atualiza sprites e estados para default
        player->frame++;

        if (player->frame >= (8))
        {
            player->frame = 0;
            player->currentframe++;

            if (player->currentframe > 4) player->currentframe = 0;

            player->framerec.x = (float)player->currentframe*SPRITESIZE;
        }
        player->ColisaoDir = 0;
        player->ColisaoEsq = 0;
        player->ColisaoSup = 0;
        player->Repouso = 0;
}

void respawna(ENTIDADE *player){
        printf("respawn\n");
        player->g=0;
        player->Repouso=0;
        player->retangulo.x = player->spawnX;
        player->retangulo.y = player->spawnY;
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
            if(player->g >0.8){
                player->retangulo.y += player->g;
            }
        }

}

void checacolisoes(MAPA *mapalido,ENTIDADE *player)
{

    float ajuste = 0;
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
                    break;
                }
            //colisão com o solo
            if(haveraColisao(player->retangulo,mapalido->BlocoGrama[i],player->g+GRAVIDADE,4))
                {
                    ajuste = mapalido->BlocoGrama[i].y - (player->retangulo.y+player->retangulo.height) ;
                    player->retangulo.y+=ajuste;
                    ajuste = 0;
                    player->Pulou = 0;
                    player->g=0;
                    break;
                }
    }
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// MAIN()
    int main(){
            SetRandomSeed(time(NULL));
            char nome_mapas[7][18];
            init_nome_mapas(nome_mapas);
            int index;
            float ajuste;
            Rectangle player_frame_rect = {0, 0, SPRITESIZE, SPRITESIZE};
            TEXTURAS texturas;
            ENTIDADE player;
            MAPA mapas[7];

    leMapa(nome_mapas[0], &mapas[1], &player);

    Rectangle player_rect = {((double)player.spawnX), ((int)player.spawnY), SPRITESIZE, SPRITESIZE};
    player.framerec = player_frame_rect;
    player.retangulo = player_rect;

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
        texturas.coin_texture = LoadTexture("texturas/coin.png");
        texturas.spriterunright = LoadTexture("texturas/spriterunright.png");
        texturas.spriterunleft = LoadTexture("texturas/spriterunleft.png");
        texturas.coin_grande = LoadTexture("texturas/coingrande.png");
        texturas.heart= LoadTexture("texturas/heart.png");

//----------------------------------------------------------------------------------
    SetTargetFPS(60);
//--------------------------------------------------------------------------------------
//MOEDAS E PORTAL X++;

// LOOP PRINCIPAL DO JOGO

    while (!WindowShouldClose())
    {

        BeginDrawing();

            ClearBackground(RAYWHITE);

                    printf("%d",player.Repouso);


renderiza_mapa(&mapas[1],&player,texturas);
checacolisoes(&mapas[1],&player);
hud(&mapas[1],&player,texturas);
movimento(&player);
atualizaPlayer(&player);
gravidade(&player);

if(IsKeyDown(KEY_R) ||((player.retangulo.x>960||player.retangulo.x<0)||(player.retangulo.y>480||player.retangulo.y<0)) )
    {respawna(&player);}

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
    }
