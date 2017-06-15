#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780
#define MAX_WBRIQUE 16
#define MAX_HBRIQUE 4



//Option de build dans les linker setting mettre les libSDL2main.a libSDL2.dll.a
//Dans search directory
//Option de build compiler mettre les include
//Option de build linker mettre les lib

//mettre dans build linker -lmingw32

typedef enum Bool {True = 1, False = 0}Bool;

typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_texture;
     SDL_Surface *g_surface;


}game;

typedef struct gameState{

    int g_bRunning;
    int left;
    int right;


}gameState;

typedef struct coordonnees{

    double x;
    double y;



}coordonnees;

typedef struct taille{

    int h;
    int w;

}taille;

typedef struct balle {

    coordonnees position;
    char *imgpath1;
    taille tBalle;
    int vitesse;
    Bool init;

}balle;

typedef struct brique {

    coordonnees position;
    char* imgpath;
    taille tBrique;
    Bool etat;
    int ID;

}brique;

typedef struct raquette {

    coordonnees position;
    char* imgpath2;
    taille tRaquette;

}raquette;


int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame);
void handleEvents(game *myGame, gameState *state, raquette *mRaquette, balle *mBalle);
void cutBitmapTexture(game *myGame,gameState state, char* imgpath,taille mTaille, coordonnees mPosition);
void delay(unsigned int frameLimit);
void destroyTexture(game *myGame);
void destroy(game *myGame);
void collisionTest(coordonnees *mPosition1, coordonnees *mPosition2);
void initbrique(brique * maBrique, brique * Board[][MAX_WBRIQUE], int i, int j);




int main(int argc, char *argv[])
{

     game myGame;
     gameState state;
     balle mBalle;
     raquette mRaquette;
     brique mBrique;
     brique MonBoard[MAX_WBRIQUE][MAX_HBRIQUE];
     int i=0,j = 0;



     mBalle.imgpath1 = "./assetsBreakout/ball.png";
     mBalle.init = 0;
     mBalle.tBalle.h = 24;
     mBalle.tBalle.w = 24;
     mBalle.position.x = 500;
     mBalle.position.y = 724;

     mRaquette.imgpath2 = "./assetsBreakout/paddle.png";
     mRaquette.tRaquette.h = 32;
     mRaquette.tRaquette.w = 128;
     mRaquette.position.x = 448;
     mRaquette.position.y = 748;

     mBrique.imgpath = "./assetsBreakout/bricks.png";
     mBrique.tBrique.h = 23;
     mBrique.tBrique.w = 64;
     mBrique.position.x = 0;
     mBrique.position.y = 0;
     mBrique.etat = 1;

    //Pour les 60 fps
    unsigned int frameLimit = SDL_GetTicks() + 16;


    if(init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame)){

                state.g_bRunning=1;


    }else{

            return 1;//something's wrong

    }

    initbrique(&mBrique, &MonBoard, i ,j);



    while(state.g_bRunning){

           handleEvents(&myGame, &state, &mRaquette, &mBalle);

           cutBitmapTexture(&myGame,state, mBalle.imgpath1, mBalle.tBalle, mBalle.position);
           cutBitmapTexture(&myGame, state, mRaquette.imgpath2, mRaquette.tRaquette, mRaquette.position);

            for( i = 0; i < MAX_HBRIQUE; i++){

                for(j = 0; j < MAX_WBRIQUE; j++){

              // cutBitmapTexture(&myGame, state, MonBoard[i][j].imgpath, MonBoard[i][j].tBrique, MonBoard[i][j].position);

                }
            }





           if(mBalle.init == 1){
                mBalle.position.x += 5;
                mBalle.position.y -= 5;
            }


            SDL_RenderPresent(myGame.g_pRenderer);

          //  SDL_RenderPresent(myGame.g_pRenderer);
            //


        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;

        SDL_RenderClear(myGame.g_pRenderer);

    }

        destroy(&myGame);

        SDL_Quit();




  return 0;
}


int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame){


    //initialize SDL

    if(SDL_Init(SDL_INIT_VIDEO)==0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);
                SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, 0);
                SDL_RenderClear(myGame->g_pRenderer);
            }
    }

    else
    {
        return 0;
    }





    return 1;




}

void handleEvents(game *myGame, gameState *state, raquette *mRaquette, balle *mBalle){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:



                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:
                                    mRaquette->position.x -= 5;
                                    mBalle->init = 1;
                                break;

                                case SDLK_RIGHT:
                                    mRaquette->position.x += 5 ;
                                    mBalle->init = 1;
                                 break;

                                case SDLK_UP:    ; break;
                                case SDLK_DOWN:  ; break;
                            }
                            break;

        case SDL_KEYUP:;break;

        default:break;

        }
    }


}



void cutBitmapTexture(game *myGame,gameState state, char *imgpath, taille mTaille, coordonnees mPosition){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        myGame->g_surface = IMG_Load(imgpath);//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){

                    rectangleSource.x= 0;
                    rectangleSource.y= 0;
                    rectangleSource.w= mTaille.w;
                    rectangleSource.h= mTaille.h;

                    SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x= mPosition.x;//debut x
                    rectangleDest.y= mPosition.y;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);




                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }


   // destroyTexture(myGame);

}



void delay(unsigned int frameLimit){
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}

void collisionTest(coordonnees *mPosition1, coordonnees *mPosition2){

}


void destroy(game *myGame){

    //Destroy render
    if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}



void destroyTexture(game *myGame){

    //Destroy texture
    if(myGame->g_texture!=NULL)
            SDL_DestroyTexture(myGame->g_texture);


}

void initbrique(brique * maBrique, brique * Board[MAX_HBRIQUE][MAX_WBRIQUE], int i, int j){

    for( i = 0; i < MAX_HBRIQUE; i++)
    {
        for(j = 0; j < MAX_WBRIQUE; j++)
        {
            Board[i][j] = maBrique;
        }
    }


    for(i =0; i < MAX_HBRIQUE; i++){

        for( j = 0; j < MAX_WBRIQUE; j++){

            Board[i][j]->position.x += 64;
            Board[i][j]->etat = 1;
        }

        Board[i][j]->position.y += 23;
        Board[i][j]->position.x = 0;
    }
}
