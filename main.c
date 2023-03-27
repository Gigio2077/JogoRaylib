#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <time.h>
#include <math.h>

#define SPRITESIZE 16
#define ALTURA 480
#define LARGURA 960
#define TILE 16
#define SPEED 4
#define GRAVIDADE 0.2


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------



typedef struct entidade //podendo ser jogador ou inimigos
    {
        int delta,Repouso,Pulou,ColisaoEsq,ColisaoDir,ColisaoSup,spawnX,spawnY;
        Rectangle retangulo;
        Texture2D texturaatual;
        float g;
        char Estado[10];

    }ENTIDADE;

void respawna(ENTIDADE *player)
    {
        (*player).retangulo.x=player->spawnX;
        (*player).retangulo.y=player->spawnY;
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
            (player->retangulo.x) -= (double)SPEED;
            printf("%f \n\n",(player->retangulo.x));
        }

    if ((IsKeyDown(KEY_UP)) && !(player->ColisaoSup) && player->Repouso)
        {
            player->Repouso = 0;
            player->Pulou = 1;
        }

    if ((IsKeyDown(KEY_RIGHT)) && !(player->ColisaoDir))
        {
            player->retangulo.x += SPEED;
        }
}

void gravidade(ENTIDADE *player) {

    if (player->Repouso)
        {
            return;
        }
    //pulo
    if (!(player->Repouso) && player->Pulou)
        {
            player->g += GRAVIDADE;
            player->retangulo.y -= SPEED * 2;
            player->retangulo.y += player->g;
        }
    //queda-livre: bateu no teto ou caiu
    if (!(player->Repouso) && !player->Pulou)
        {
            player->g += GRAVIDADE;
            player->retangulo.y += player->g;
        }

}


int main()
{

    int i = 0;
    int index;
    int ajuste;
    SetRandomSeed(time(NULL));
    int qtdBlocosGrama = 0;
    int qtdCoins = 0;
    int qtdBlocosTerra = 0;
    int qtdArmadilhas = 0;
    char mapa[30][61];



    float update = 0;

    ENTIDADE player;




//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//carrega mapa
        FILE *fp;
        fp = fopen("mapas/mapa6.txt" , "r");
        if(fp == NULL) {
          perror("Error opening file");
          return(-1);
       }
       else {
        for(int i = 0; i<30; i++)
            {
            fgets(mapa[i], 99 ,fp);
            }
        }
        fclose(fp);
    char currentchar;
    char hashatag = '#';
    char T = 'T';
    char X = 'X';
    char J = 'J';
    char C = 'C';

for( int i=0; i<30; i++){
    for( int j=0; j<61; j++){
        currentchar = mapa[i][j];

        switch (currentchar) {
            case 'J':


                player.spawnX = TILE*j;
                player.spawnY = TILE*i;

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
Rectangle BlocoTerra[qtdBlocosTerra];
Rectangle BlocoGrama[qtdBlocosGrama];
Rectangle Armadilhas[qtdArmadilhas];
Rectangle Coins[qtdCoins];

index = 0;
    for( int i=0; i<30; i++){
        for( int j=0; j<61; j++){
            currentchar = mapa[i][j];
            if( currentchar==T ){
        BlocoTerra[index].width = TILE ;
        BlocoTerra[index].height = TILE ;
        BlocoTerra[index].x = TILE*j ;
        BlocoTerra[index].y = TILE*i ;
        index++;
    }}}
index = 0;
    for( int i=0; i<30; i++){
        for( int j=0; j<61; j++){
            currentchar = mapa[i][j];
            if( currentchar==hashatag ){
        BlocoGrama[index].width = TILE ;
        BlocoGrama[index].height = TILE ;
        BlocoGrama[index].x = TILE*j ;
        BlocoGrama[index].y = TILE*i ;
        index++;
    }}}
index = 0;
    for( int i=0; i<30; i++){
        for( int j=0; j<61; j++){
            currentchar = mapa[i][j];
            if( currentchar==X ){
        Armadilhas[index].width = TILE+1 ;
        Armadilhas[index].height = TILE+1 ; //esses +1 e menos 1 é pra ajustar a colisao com o espinho
        Armadilhas[index].x = (TILE*j)-1 ;
        Armadilhas[index].y = (TILE*i)-1 ;
        index++;
    }}}
index = 0;
    for( int i=0; i<30; i++){
        for( int j=0; j<61; j++){
            currentchar = mapa[i][j];
            if( currentchar==C ){
        Coins[index].width = TILE ;
        Coins[index].height = TILE ;
        Coins[index].x = (TILE*j) ;
        Coins[index].y = (TILE*i) ;
        index++;
    }}}
index = 0;

    printf("\n\n\nspawnx:%f spawny:%f",(double)player.spawnX,player.spawnY);
    Rectangle player_rect = {(double)player.spawnX, (double)player.spawnY, SPRITESIZE, SPRITESIZE};
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

    Texture2D BG3 = LoadTexture("texturas/BG3.png");        // Carregando Texturas
    Texture2D BG1 = LoadTexture("texturas/BG1.png");
    Texture2D grama_textura = LoadTexture("texturas/grama.png");
    Texture2D terra = LoadTexture("texturas/terra.png");
    Texture2D frame = LoadTexture("texturas/frame.png");
    Texture2D trap = LoadTexture("texturas/trap.png");
    Texture2D coin_texture = LoadTexture("texturas/coin.png");



//----------------------------------------------------------------------------------
    SetTargetFPS(60);
//--------------------------------------------------------------------------------------

// LOOP PRINCIPAL DO JOGO

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Atualiza as variáveis aqui
            player.ColisaoDir = 0;
            player.ColisaoEsq = 0;
            player.ColisaoSup = 0;



        //----------------------------------------------------------------------------------

// DESENHO
//----------------------------------------------------------------------------------
        BeginDrawing();


            ClearBackground(RAYWHITE);

        //FUNDOS
            DrawTexture(BG1, 0, 0, WHITE);
            DrawTexture(BG3, 0, 0, WHITE);
        //----------------------------------------------------------------------------------
            DrawRectangle((int)player.retangulo.x, (int)player.retangulo.y, player.retangulo.width, player.retangulo.height, RED);
            DrawRectangleRec( (player.retangulo), RED);


            //printf("posx:%d,posy:%d\n ",(int)player.retangulo.x,(int)player.retangulo.y);

            DrawTexture(frame,0,480,WHITE);

            //------------------------------------------------------------------------------
            // sera substituido por uma funçao que desenha todos blocos sem animacao .
            for(int k = 0; k<qtdBlocosGrama; k++){
                DrawTexture(grama_textura,
                            BlocoGrama[k].x,
                            BlocoGrama[k].y,
                            WHITE);
                            }

            for(int k = 0; k<qtdBlocosTerra; k++){
                            DrawTexture(terra,
                                        BlocoTerra[k].x,
                                        BlocoTerra[k].y,
                                        WHITE);
                                        }
            for(int k = 0; k<qtdCoins; k++){
                            DrawTexture(coin_texture,
                                        Coins[k].x,
                                        Coins[k].y,
                                        WHITE);
                            if(CheckCollisionRecs(Coins[k], player.retangulo))
                            {
                                Coins[k].x = -32;
                                Coins[k].y = -32;
                            }
                                        }
            for(int k = 0; k<qtdArmadilhas; k++){
                            DrawTexture(trap,
                                        Armadilhas[k].x,
                                        Armadilhas[k].y,
                                        WHITE);
                            if(CheckCollisionRecs(Armadilhas[k], player.retangulo))
                            {
                                player.g=0;
                                player.Repouso=1;
                                respawna(&player);
                            }
                        }
            //------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//transformar em uma função também

//loop colisoes
    for (i = 0; i<qtdBlocosGrama; i++)
{
                player.ColisaoDir += haveraColisao(player.retangulo,BlocoGrama[i],SPEED,3);

                player.ColisaoEsq += haveraColisao(player.retangulo,BlocoGrama[i],SPEED,1);

                player.ColisaoSup+= haveraColisao(player.retangulo,BlocoGrama[i],abs(SPEED*2-(player.g+GRAVIDADE)),2);

                player.Repouso+= haveraColisao(player.retangulo,BlocoGrama[i],player.g+GRAVIDADE,4);

    //colisão com o teto
         if(haveraColisao(player.retangulo,BlocoGrama[i],abs(SPEED*2-(player.g+GRAVIDADE)),2))
            {
                player.Pulou = 0;


            }
    //colisão com o solo
        if(haveraColisao(player.retangulo,BlocoGrama[i],player.g+GRAVIDADE,4))
            {
                ajuste = BlocoGrama[i].y - (player.retangulo.y+player.retangulo.height) ;
                printf("R: %d\n",player.Repouso );

                player.retangulo.y+=ajuste;

                ajuste = 0;

;
                player.Pulou = 0;

                player.g=0;

                break;
            }

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

movimento(&player);
gravidade(&player);




player.Repouso=0;

if((player.retangulo.x>960||player.retangulo.x<0)||(player.retangulo.y>480||player.retangulo.y<0)) {respawna(&player);}
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
    }
