#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <time.h>
#include <math.h>

#define SPRITESIZE 32
#define ALTURA 480
#define LARGURA 960
#define TILE 16


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------





//função haveraColisao(Bloco, Player,int delta x, delta y, sentido){}
int haveraColisao (Rectangle player, Rectangle parede, int delta, int a){

    switch(a){

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




/*modificar função movimento
para que ela permita o movimento desde que haveraColisao seja falso
haveraColisao ( player, blocosProximos);


*/

void movimento(int *posX, int *posY, int E, int D, int S, int R){

    if((IsKeyDown(KEY_LEFT)) && !E )    {*posX-=4;}
    if((IsKeyDown(KEY_UP)) && !S )      {*posY-=15;}
    if( (IsKeyDown(KEY_RIGHT)) && !D )    {*posX+=4;}
    if ( !R)    {*posY+=5;}

}







int main()
{
    int colisaoSuperior = 0;
    int colisaoDireita = 0;
    int colisaoEsquerda = 0;
    int Repouso = 0;
    int index;
    SetRandomSeed(time(NULL));
    float g = 0;
    int i= 0;
    int qtdBlocosGrama = 0;
    int qtdBlocosTerra = 0;

    int posX = 450;
    int posY = 450;
    char mapa[30][61];

    float update = 0;




//--------------------------------------------------------------------------------------
//carrega mapa
        FILE *fp;
        fp = fopen("mapa1.txt" , "r");
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





    InitWindow(LARGURA, ALTURA, "Tua mae ");


//----------------------------------------------------------------------------------
//TEXTURAS
    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)


    Texture2D BG3 = LoadTexture("BG3.png");        // Texture loading
    Texture2D BG1 = LoadTexture("BG1.png");
    Texture2D grama = LoadTexture("grama.png");
    Texture2D terra = LoadTexture("terra.png");


//----------------------------------------------------------------------------------


    SetTargetFPS(60);

//--------------------------------------------------------------------------------------

// LOOP PRINCIPAL DO JOGO




    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
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
            //printf("posicao x :%f e y:%f \n",player.x,player.y);

            Rectangle bordaSuperior = {0,  0, LARGURA, 1};
            Rectangle bordaEsquerda = {1,  1, 1, ALTURA};
            Rectangle bordaInferior = {1,  ALTURA-1, LARGURA, 1};
            Rectangle bordaDireita = {LARGURA-1,  1, 1,ALTURA};


            DrawRectangleRec(bordaSuperior,RED);
            DrawRectangleRec(bordaEsquerda,RED);
            DrawRectangleRec(bordaInferior,RED);
            DrawRectangleRec(bordaDireita,RED);

           // printf("%d \n", haveraColisao(bordaSuperior,player,5,5,2));


           //printf("%d \n", haveraColisao(player,BlocoTerra[3],50,3));

          // printf("%d %d \n", (int)player.x/16, (int)player.y/16);



            //DrawTexture(BG1, 0, 0, WHITE);
           // DrawTexture(BG3, 0, 0, WHITE);

            DrawRectangleRec( player, RED);                        // Draw a color-filled rectangle


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







int delta = 0;



for (i = 0; i<qtdBlocosGrama; i++){

        /*
        remover tantas variaveis, tentar passar o numero da direcao apenas
         retornar distancia precisa para que quase encoste

        */
        if(haveraColisao(player,BlocoGrama[i],5,3))
        {
            delta = BlocoGrama[i].x - player.x-player.width-1;
            printf("delta %d\n",delta );

        }


        colisaoDireita += haveraColisao(player,BlocoGrama[i],5,3);




        if(haveraColisao(player,BlocoGrama[i],5,1))
        {
            delta = player.x-BlocoGrama[i].x -BlocoGrama[i].width-1 ;
            printf("delta %d\n",delta );

        }
        colisaoEsquerda += haveraColisao(player,BlocoGrama[i],5,1);




        if(haveraColisao(player,BlocoGrama[i],5,2))
        {
            delta = player.y-BlocoGrama[i].y -BlocoGrama[i].height+1 ;
            printf("delta %d\n",delta );

        }

        colisaoSuperior += haveraColisao(player,BlocoGrama[i],5,2);




        //mudar o 10 para g posteriormente
        if(haveraColisao(player,BlocoGrama[i],5,2))
        {
            delta = BlocoGrama[i].y -BlocoGrama[i].height+1 ;
            printf("delta %d\n",delta );

        }
        Repouso += haveraColisao(player,BlocoGrama[i],5,4);

}

movimento(&posX, &posY, colisaoEsquerda ,colisaoDireita,colisaoSuperior, Repouso);

//printf("%d",Repouso);

            printf("delta %d\n",delta );


colisaoSuperior = 0;
colisaoDireita = 0;
colisaoEsquerda = 0;
//Repouso = 0;













Repouso = 0;




//----------------------------------------------------------------------------------
//MOVIMENTO
/*
        if(IsKeyDown(KEY_LEFT)&& (podemover(1,&posX,&posY)) ){posX-=5;}
        if(IsKeyPressed(KEY_UP)&& (podemover(2,&posX,&posY)) && (g==0)) {posY-=20;}
        if(IsKeyDown(KEY_RIGHT)&& (podemover(3,&posX,&posY)) ){posX+=5;}
        if(IsKeyDown(KEY_DOWN)&& (podemover(4,&posX,&posY)) ) {posY+=5;}

//----------------------------------------------------------------------------------
// RELOGIO  --ajustar o segundo

        update += (GetFrameTime()*4);
        i = (int)update;
        if (update>=4){update = 0;}
*/
//----------------------------------------------------------------------------------
//GRAVIDADE







//----------------------------------------------------------------------------------

        //colisao_parede(parede,player);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }




    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------




    return 0;
    }
