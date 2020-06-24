#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
//Variaveis-------------------
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
TTF_Font *gFont; //FONTE DO TEXTO
SDL_Window *screen = NULL; //TELA

//Functions---------------------
int libs_init();
void screen_init();

int main(int argc, char* args[]){
    //Iniciar as bibliotecas do sdl
    libs_init();
    //Criar tela
    screen_init();

}
int libs_init(){
    bool success = true;
    // Iniciando os subsystem do SDL2 
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Erro! (SDL_Init): %s\n", SDL_GetError());
        return 1
    }
    else{
        printf("SDL INICIALIZADO!\n");
    }
    //Biblioteca de Imagem
    int flags = IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if((initted&flags) != flags){
        printf("Erro! (IMG_Init): %s\n", IMG_GetError());
        return 1;
    }
    else{
        printf("BIBLIOTECA DE IMAGENS INICIALIZADA\n");
    }
    //Biblioteca de Fontes
    if(TFF_Init() != 0){
        printf("Erro! (TTF_Init): %s\n", TTF_GetError());
        return 1;
    }
    gFont = TTF_OpenFont("resources/fonts/batman.ttf", 28);
    if(!gFont){
        printf("Erro! (TTF_OpenFont): %s\n", TTF_GetError());
        return 1;
    }
    //Biblioteca de mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0){
        printf("Erro! (Mix_OpenAudio): %s\n", Mix_GetError());
        return 1;
    }
    else{
        printf("MIXER INICIALIZADO!\n");
    }
    return 0;
}

void screen_init(){
    //Tela que será renderizada
    Uint32 FlagsCreateWindow = SDL_WINDOW_FULLSCREEN_DESKTOP;
	screen = SDL_CreateWindow ("SCI-FI STREET RACING", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, FlagsCreateWindow);
}

int sdl_quit(){
    SDL_DestroyWindow(screen);
    screen = NULL;
    printf("SDL FINALIZANDO\n");
    IMG_Quit();
    TTF_CloseFont(gFont);
    TTF_Quit();
    Mix_Quit();
    SDL_Quit(); //FECHA SDL
}  