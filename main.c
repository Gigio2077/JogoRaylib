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

int haveraColisao (Rectangle player, Rectangle parede, int delta, int direcao){
    switch(direcao){
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

void gravidade(int *posY, float *g, int R, int C,int pulou)
{
/*R refere a Repouso de main() */
    if(R){return;}
    if (!(R)&&pulou)//não está em repouso e pulou
    {
        //g é a velocidade com que a gravidade aumenta
        *g+=GRAVIDADE;
        *posY-=SPEED*2;
        *posY+=*g;

        //usando função haveracolisão da main()
    }

    if(!(R)&&!pulou)//não está em repouso e não pulou(queda livre ou bateu no teto)
    {
        *g+=GRAVIDADE;
        *posY+=*g;
    }




}

void movimento(int *posX, int *posY, int E, int D, int S, int *R, int *pulou){

    if((IsKeyDown(KEY_LEFT)) && !E )    {*posX-=SPEED;}
    if((IsKeyDown(KEY_UP)) && !S && *R )      {*R = 0;*pulou=1;}
    if( (IsKeyDown(KEY_RIGHT)) && !D )    {*posX+=SPEED;}

}

int main()
{

    int colisaoSuperior,colisaoDireita,colisaoEsquerda,Repouso,i = 0;
    int index;
    int ajuste,pulou = 0;
    SetRandomSeed(time(NULL));
    float g = 0;
    int qtdBlocosGrama = 0;
    int qtdBlocosTerra = 0;
    char mapa[30][61];

    //-------------------------
    //recebera o "J" da função carrega mapa
    int posX = 416;
    int posY = 288;
    //-------------------------

    float update = 0;






//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//carrega mapa
        FILE *fp;
        fp = fopen("mapas/mapa1.txt" , "r");
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

    for( int i=0; i<30; i++){
        for( int j=0; j<61; j++){
            currentchar = mapa[i][j];

            if( currentchar==hashatag ){
                    qtdBlocosGrama++;
            }
        }
    }
     for( int i=0; i<30; i++){
        for( int j=0; j<61; j++){
            currentchar = mapa[i][j];

            if( currentchar==T ){
                    qtdBlocosTerra++;
            }
        }
    }
    printf("\n\n\n%d\n\n",qtdBlocosGrama);
Rectangle BlocoTerra[qtdBlocosTerra];
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
Rectangle BlocoGrama[qtdBlocosGrama];
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
    Texture2D grama = LoadTexture("texturas/grama.png");
    Texture2D terra = LoadTexture("texturas/terra.png");

//----------------------------------------------------------------------------------
    SetTargetFPS(60);
//--------------------------------------------------------------------------------------

// LOOP PRINCIPAL DO JOGO

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Atualiza as variáveis aqui
            colisaoSuperior = 0;
            colisaoDireita = 0;
            colisaoEsquerda = 0;

        //----------------------------------------------------------------------------------

// DESENHO
//----------------------------------------------------------------------------------
        BeginDrawing();


            ClearBackground(RAYWHITE);

        //FUNDOS
            DrawTexture(BG1, 0, 0, WHITE);
            DrawTexture(BG3, 0, 0, WHITE);
        //----------------------------------------------------------------------------------
            Rectangle player = {(double)posX, (double) posY, SPRITESIZE, SPRITESIZE};
            /*
            //printa posição
            //printf("posicao x :%f e y:%f \n",player.x,player.y);
            //printa coordenadas
            //printf("%d %d \n", (int)player.x/16, (int)player.y/16);
            */
            //aqui será substituido por uma função com DrawTexture() periódico para adicionar texturas ao player, moeda e inimigos
            DrawRectangleRec( player, RED);
            //------------------------------------------------------------------------------
            // sera substituido por uma funçao que desenha todos blocos sem animacao .
            for(int k = 0; k<qtdBlocosGrama; k++){
                DrawTexture(grama,
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
            //------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//loop colisoes
    for (i = 0; i<qtdBlocosGrama; i++)
{
                colisaoDireita += haveraColisao(player,BlocoGrama[i],SPEED,3);
                colisaoEsquerda += haveraColisao(player,BlocoGrama[i],SPEED,1);
                colisaoSuperior+= haveraColisao(player,BlocoGrama[i],abs(SPEED*2-(g+GRAVIDADE)),2);
    //colisão com o teto
            if(haveraColisao(player,BlocoGrama[i],abs(SPEED*2-(g+GRAVIDADE)),2)&&!Repouso)
                {
                ajuste = player.y-(BlocoGrama[i].y+BlocoGrama[i].height) ;
                //posY-=ajuste;
                printf("\najuste teto");
                ajuste = 0;
                pulou=0;
                Repouso = 0;
                break;
                }

                Repouso+= haveraColisao(player,BlocoGrama[i],g+GRAVIDADE,4);

    //colisão com o solo
            if(haveraColisao(player,BlocoGrama[i],g+GRAVIDADE,4))
                {
                ajuste = BlocoGrama[i].y - (player.y+player.height) ;
                printf("R: %d\n",Repouso );
                posY+=ajuste;
                ajuste = 0;
                pulou = 0;
                g = 0;

                break;
                }


}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------




movimento(&posX, &posY, colisaoEsquerda ,colisaoDireita,colisaoSuperior, &Repouso,&pulou);
gravidade(&posY,&g,Repouso,colisaoSuperior,pulou);
Repouso = 0;

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
    }
