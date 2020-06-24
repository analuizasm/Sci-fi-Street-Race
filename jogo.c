#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PLAYER_WIDTH 181
#define PLAYER_HEIGHT 235
#define LARGURA_MAPA 1280
#define ALTURA_MAPA 2160
#define LIMITE 4
#define INICIO_PLAYERX 1280
#define INICIO_PLAYERY 720
#define INICIO_CAMERAX 1280
#define INICIO_CAMERAY 720
#define BLOCOS 6

typedef struct{
    SDL_Rect imagem;
	SDL_Rect destino;
	SDL_Surface *objtsurface;
	SDL_Texture *objttexture;
} OBJETO;

bool iniciar_jogo();
void renderizar_screen();
int finaliza_sdl();
void jogo_menu();
void Musicas();
void tutorial_tela();
void renderizar_menu();
void menu_destroy();
void renderizar_selecao_personagem();
void selecao_personagem_destroy();
void menu_selecao_personagem();
void renderizar_player();
void menu_selecao_mapa();
void tela_credito();
void selecao_mapa_destroy();
void renderizar_mapa();
void renderizar_confirmar();
void confirmar_selecao();
void confirmar_selecao_destroy();
void carregar_jogo();
void jogo();
void liberar();
void movimentacao_teclas();
void player_animacao();
void movimentacao_camera();
void aceleracao();
void gerar_objetos();
void renderizar_objetos();
void move_obstaculo();
void randomizar_posicao();
bool colisao(OBJETO jogador, OBJETO objeto);
void posiciona_objetos();
void score();
void score_novamente();
void jogar_novamente();
void renderizar_jogarnovamente();
void jogar_novamente_destroy();
TTF_Font *gFont;

FILE *pontos;

SDL_Rect lscore;
//EVENTO
SDL_Event event;
//VARI�VEIS DE TELA
SDL_Window* screen = NULL;
SDL_Renderer* renderer;

//VARIAVEIS DE IMAGEM

int speed = 12;
//SELE��ES
int player_selecionado;
//SCORE
SDL_Surface* pontuacao_image;
SDL_Texture* pontuacao_texture;
SDL_Surface* pontuacao_novamente;
SDL_Texture* pontuacaoagain_texture;

Mix_Music* musica;
SDL_Color textColor = { 255, 255, 255, 0 };
SDL_Color textColorpreto = { 0, 0, 0, 0 };
int startTime = 0;
int pontuacao_player = 0;
int pontuacao_velha = -1;

//MENUS;
SDL_Texture* bkg_jogaragain;
SDL_Surface* image_jogaragain;
SDL_Texture* Background_Menu;
SDL_Surface* Image_Menu;
SDL_Texture* bkg_tutorial;
SDL_Surface* Image_Tutorial;
SDL_Texture* bkg_creditos;
SDL_Surface* Image_Creditos;
SDL_Texture* bkg_menu_personagem;
SDL_Surface* fundo_selecao_personagem;
SDL_Texture* bkg_menu_mapa;
SDL_Surface* fundo_selecao_mapa;
SDL_Texture* bkg_confirmar;
SDL_Surface* fundo_confirmar;
SDL_Surface* caixa_selecao;
SDL_Texture* Text_Options_Box;
SDL_Surface* caixa_selecao_personagem;
SDL_Texture* Options_Box_personagem;
SDL_Surface* caixa_selecao_mapa;
SDL_Texture* Options_Box_mapa;
SDL_Surface* caixa_selecao_confirmar;
SDL_Texture* Options_Box_confirmar;
SDL_Surface* caixa_selecao_again;
SDL_Texture* Options_Box_again;
SDL_Rect sBox = {0, 0, 483, 104};
SDL_Rect dBox = {415, 190, 483, 104};
SDL_Rect sBoxp = {0, 0, 196, 306};
SDL_Rect dBoxp = {125, 240, 196, 306};
SDL_Rect sBoxm = {0, 0, 579, 98};
SDL_Rect dBoxm = {350, 222, 579, 98};
SDL_Rect sBoxc = {0, 0, 199, 93};
SDL_Rect dBoxc = {288, 351, 199, 93};
SDL_Rect sBoxag = {0, 0, 196, 91};
SDL_Rect dBoxag = {288, 542, 196, 91};
int menu, menu_personagem, menu_mapa, confirmar, tutorial, creditos, ranking, menu_again;

OBJETO jogador, oponente1, oponente2, pista0, pista1, pt2pista, obstaculo1, obstaculo2, obstaculo3, obstaculo4, obstaculo5, obstaculo6, obstaculo7, obstaculo8;
bool seta_up, seta_dwn, seta_lf, seta_rg, lshift;
int Limitador = 0, selectmenu = 0, selectp = 0, selectm = 0, selectc = 0, selectagain = 0, jogar;

int main(int argc, char* args[]){
    //SDL INICIANDO
    SDL_Init(SDL_INIT_EVERYTHING);
    //IMG iniciando
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0){
        printf("Error: %s\n", Mix_GetError());
    }
   gFont = TTF_OpenFont("resources/fonts/batman.ttf", 28);
   if(!gFont) printf("fonte nao inicializada\n");

    pista0.imagem.x=0;
	pista0.imagem.y=0;
	pista0.imagem.w=1280;
	pista0.imagem.h=720;
	pista0.destino.x=0;
	pista0.destino.y=-715;
	pista0.destino.w=1280;
	pista0.destino.h=727;

	pista1.imagem.x=0;
	pista1.imagem.y=0;
	pista1.imagem.w=1280;
	pista1.imagem.h=720;
	pista1.destino.x=0;
	pista1.destino.y=0;
	pista1.destino.w=1280;
	pista1.destino.h=727;

	jogador.imagem.x= 0;
	jogador.imagem.y= 0;
	jogador.imagem.w= PLAYER_WIDTH;
	jogador.imagem.h= PLAYER_HEIGHT;
	jogador.destino.x= 650;
	jogador.destino.y= 650;
	jogador.destino.w= 55;
	jogador.destino.h= 65;

	obstaculo1.imagem.w = 161;
    obstaculo1.imagem.h = 191;
    obstaculo1.imagem.x = 0;
    obstaculo1.imagem.y = 0;
    obstaculo1.destino.x = 650;
    obstaculo1.destino.y = -685;
    obstaculo1.destino.h = 55;
    obstaculo1.destino.w = 65;

    obstaculo2.imagem.w = 279;
    obstaculo2.imagem.h = 277;
    obstaculo2.imagem.x = 0;
    obstaculo2.imagem.y = 0;
    obstaculo2.destino.x = 700;
    obstaculo2.destino.y = -600;
    obstaculo2.destino.h = 55;
    obstaculo2.destino.w = 65;

    obstaculo3.imagem.w = 279;
    obstaculo3.imagem.h = 277;
    obstaculo3.imagem.x = 0;
    obstaculo3.imagem.y = 0;
    obstaculo3.destino.x = 450;
    obstaculo3.destino.y = -150;
    obstaculo3.destino.h = 55;
    obstaculo3.destino.w = 65;

    obstaculo4.imagem.w = 279;
    obstaculo4.imagem.h = 277;
    obstaculo4.imagem.x = 0;
    obstaculo4.imagem.y = 0;
    obstaculo4.destino.x = 650;
    obstaculo4.destino.y = -100;
    obstaculo4.destino.h = 55;
    obstaculo4.destino.w = 65;

    obstaculo5.imagem.w = 279;
    obstaculo5.imagem.h = 277;
    obstaculo5.imagem.x = 0;
    obstaculo5.imagem.y = 0;
    obstaculo5.destino.x = 650;
    obstaculo5.destino.y = 680;
    obstaculo5.destino.h = 55;
    obstaculo5.destino.w = 65;

    obstaculo6.imagem.w = 279;
    obstaculo6.imagem.h = 277;
    obstaculo6.imagem.x = 0;
    obstaculo6.imagem.y = 0;
    obstaculo6.destino.x = 659;
    obstaculo6.destino.y = 700;
    obstaculo6.destino.h = 55;
    obstaculo6.destino.w = 65;

    obstaculo7.imagem.w = 279;
    obstaculo7.imagem.h = 277;
    obstaculo7.imagem.x = 0;
    obstaculo7.imagem.y = 0;
    obstaculo7.destino.x = 647;
    obstaculo7.destino.y = 2000;
    obstaculo7.destino.h = 55;
    obstaculo7.destino.w = 65;

    obstaculo8.imagem.w = 279;
    obstaculo8.imagem.h = 277;
    obstaculo8.imagem.x = 0;
    obstaculo8.imagem.y = 0;
    obstaculo8.destino.x = 670;
    obstaculo8.destino.y = 450;
    obstaculo8.destino.h = 55;
    obstaculo8.destino.w = 65;

    //INICIAR JOGO
    if(!iniciar_jogo()) printf("Ocorreu um erro ao inicializar o jogo.\n");
    else{
        printf("SDL INICIALIZANDO\n");
        renderizar_screen();
        jogo_menu();
    }

    finaliza_sdl();

    return 0;
}

void desenha_pista(){
    if(pista0.destino.y>720)
	{
		pista0.destino.y=-715;
	}
	if(pista1.destino.y>720)
	{
		pista1.destino.y=-710;
	}
	pista0.destino.y+=speed;
	pista1.destino.y+=speed;
	SDL_RenderCopy(renderer,pista0.objttexture,&pista0.imagem,&pista0.destino);
	SDL_RenderCopy(renderer,pista1.objttexture,&pista1.imagem,&pista1.destino);
}

bool iniciar_jogo(){
 bool success = true;
 Uint32 FlagsCreateWindow = SDL_WINDOW_FULLSCREEN;
    screen = SDL_CreateWindow ("SCI-FI STREET RACING", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, FlagsCreateWindow);
	return success;
}

void renderizar_screen(void){
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    if(!renderer){
        printf("Erro! N�o foi poss�vel criar o renderer\n");
        finaliza_sdl();
    }
}

int finaliza_sdl(){ //SDL FINALIZANDO
    SDL_DestroyWindow(screen); //APAGA JANELA
    screen = NULL;
    printf("SDL FINALIZANDO\n");
    IMG_Quit();
    TTF_CloseFont(gFont);
    TTF_Quit();
    Mix_Quit();
    SDL_Quit(); //FECHA SDL
    return 0;
}

void jogo_menu(){ //MENU PRINCIPAL DO JOGO;
   renderizar_menu();
   menu = 1;
   musica = Mix_LoadMUS("resources/musicas/musica1.mp3");
   Mix_PlayMusic(musica, -1);
   while(menu){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, Background_Menu, NULL, NULL);
        SDL_RenderCopy (renderer, Text_Options_Box, &(sBox), &(dBox));
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(1000/30);

        while(SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT) menu = 0;
			if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                    menu = 0;
                    finaliza_sdl();
                    }
                if (event.key.keysym.scancode == SDL_SCANCODE_DOWN){
                    selectmenu++;
                    if (selectmenu > 2) selectmenu = 0;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_UP){
                    selectmenu--;
                    if (selectmenu < 0) selectmenu = 2;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){ // Return = Tecla ENTER
                    if (selectmenu == 0){
                        menu = 0;
                        SDL_RenderClear(renderer);
                        menu_selecao_personagem();
                    }
                    if (selectmenu == 1){
                        SDL_RenderClear(renderer);
                        tutorial = 1;
                        SDL_Delay(1000/30);
                        while (tutorial){
                            tutorial_tela();
                        }
                    }
                    if (selectmenu == 2){
                        SDL_RenderClear(renderer);
                        creditos = 1;
                        SDL_Delay(1000/30);
                        while (creditos){
                            tela_credito();
                        }
                    }
                }
			}
        }
				if (selectmenu == 0) dBox.y = 250;
				if (selectmenu == 1) dBox.y = 415;
				if (selectmenu == 2) dBox.y = 545;
    }

    menu_destroy();
}

void tutorial_tela(){ //TELA DE CONTROLES
    SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bkg_tutorial, NULL, NULL);
	SDL_RenderPresent(renderer);

	while(SDL_PollEvent(&event)){

		if (event.type == SDL_QUIT){ //Fechar e acabar com Geral
			tutorial = 0;
			menu = 0;
			menu_destroy();
			finaliza_sdl();
		}

		if (event.type == SDL_KEYDOWN){

			if (event.key.keysym.sym == SDLK_ESCAPE){
				tutorial = 0;
				selectmenu = 0;
			}
		}
	}
}

void tela_credito(){ //TELA DE CREDITO
    SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bkg_creditos, NULL, NULL);
	SDL_RenderPresent(renderer);

	while(SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){ //Fechar e acabar com Geral
			creditos = 0;
			menu = 0;
			menu_destroy();
			finaliza_sdl();
		}

		if (event.type == SDL_KEYDOWN){

			if (event.key.keysym.sym == SDLK_ESCAPE){
				creditos = 0;
				selectmenu = 0;
			}
		}
	}
}


void renderizar_menu(void){ //RENDERIZAR TEXTURA DOS MENUS
    Image_Menu = IMG_Load("resources/images/menu.png");
    if(!Image_Menu){
        printf("renderizar_menu() failed: Falha ao carregar a imagem menu.png");
    }
    Background_Menu = SDL_CreateTextureFromSurface(renderer, Image_Menu);
    caixa_selecao = IMG_Load("resources/images/borda.png");
	Text_Options_Box = SDL_CreateTextureFromSurface(renderer, caixa_selecao);
    Image_Tutorial = IMG_Load("resources/images/controles.png");
    bkg_tutorial = SDL_CreateTextureFromSurface(renderer, Image_Tutorial);
    Image_Creditos = IMG_Load("resources/images/creditos.png");
    bkg_creditos = SDL_CreateTextureFromSurface(renderer, Image_Creditos);
}

void menu_destroy(){ //LIBERA TEXTURAS DO MENU
    SDL_FreeSurface(Image_Menu);
    SDL_DestroyTexture(Background_Menu);
    SDL_FreeSurface(caixa_selecao);
    SDL_DestroyTexture(Text_Options_Box);
    SDL_FreeSurface(Image_Tutorial);
    SDL_DestroyTexture(bkg_tutorial);
    SDL_FreeSurface(Image_Creditos);
    SDL_DestroyTexture(bkg_creditos);
}

void renderizar_selecao_personagem(){ //RENDERIZAR SELECAO DE PERSONAGEM
    fundo_selecao_personagem = IMG_Load("resources/images/selecaopersonagem.png");
    if(!fundo_selecao_personagem){
    printf("renderizar_selecao_personagem() failed: Falha ao carregar a imagem selecaopersonagem.png");
    }
    bkg_menu_personagem = SDL_CreateTextureFromSurface(renderer, fundo_selecao_personagem);
    caixa_selecao_personagem = IMG_Load("resources/images/borda_personagem.png");
    if(!caixa_selecao_personagem){
    printf("renderizar_selecao_personagem() failed: Falha ao carregar a imagem borda_personagem.png");
    }
    Options_Box_personagem = SDL_CreateTextureFromSurface(renderer, caixa_selecao_personagem);
}

void renderizar_confirmar(){ //RENDERIZAR TELA DE CONFIRMA��O
    fundo_confirmar = IMG_Load("resources/images/confirmar.png");
    if(!fundo_confirmar){
        printf("renderizar_confirmar() failed: Falha ao carregar a imagem confirmar.png");
    }
    bkg_confirmar = SDL_CreateTextureFromSurface(renderer, fundo_confirmar);
    caixa_selecao_confirmar = IMG_Load("resources/images/confirmarborda.png");
    Options_Box_confirmar = SDL_CreateTextureFromSurface(renderer, caixa_selecao_confirmar);
}

void selecao_personagem_destroy(){ //LIBERA TEXTURAS DA TELA DE SELE��O DE PERSONAGENS
    SDL_FreeSurface(fundo_selecao_personagem);
    SDL_DestroyTexture(bkg_menu_personagem);
    SDL_FreeSurface(caixa_selecao_personagem);
    SDL_DestroyTexture(Options_Box_personagem);
}

void confirmar_selecao_destroy(){ //LIBERA TEXTURAS DA TELA DE CONFIRMAR SELE��O
    SDL_FreeSurface(fundo_confirmar);
    SDL_DestroyTexture(bkg_confirmar);
    SDL_FreeSurface(caixa_selecao_confirmar);
    SDL_DestroyTexture(Options_Box_confirmar);
}

void menu_selecao_personagem(){ //MENU DE SELE��O DE PERSONAGEM
    SDL_RenderClear(renderer);
    renderizar_selecao_personagem();
    menu_personagem = 1;
    while(menu_personagem){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bkg_menu_personagem, NULL, NULL);
        SDL_RenderCopy (renderer, Options_Box_personagem, &(sBoxp), &(dBoxp));
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        SDL_Delay(1000/30);

        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) menu_personagem = 0;
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                    selecao_personagem_destroy();
                    jogo_menu();
                }
				if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
					selectp++;
					if (selectp > 3) selectp = 0;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
                    selectp--;
					if (selectp < 0) selectp = 3;
				}
				if(event.key.keysym.scancode == SDL_SCANCODE_RETURN){
                    if (selectp == 0){
                        menu_personagem = 0;
                        player_selecionado = 0;
                        SDL_RenderClear(renderer);
                        renderizar_player();
                        confirmar_selecao();

                    }
                    if (selectp == 1){

                        menu_personagem = 0;
                        player_selecionado = 1;
                        SDL_RenderClear(renderer);
                        renderizar_player();
                        confirmar_selecao();

                    }
                    if (selectp == 2){

                        menu_personagem = 0;
                        player_selecionado = 2;
                        SDL_RenderClear(renderer);
                        renderizar_player();
                        confirmar_selecao();

                    }
                    if (selectp == 3){

                        menu_personagem = 0;
                        player_selecionado = 3;
                        SDL_RenderClear(renderer);
                        renderizar_player();
                        confirmar_selecao();

                    }
                }
            }
        }
        if (selectp == 0) dBoxp.x = 125;
        if (selectp == 1) dBoxp.x = 416;
        if (selectp == 2) dBoxp.x = 670;
        if (selectp == 3) dBoxp.x = 955;
    }
    selecao_personagem_destroy();
}


void renderizar_player(){ //RENDERIZAR PERSONAGENS
    if(player_selecionado == 0){
        jogador.objtsurface = IMG_Load("resources/images/car1.png");
        if(!jogador.objtsurface){
        printf("renderizar_PLAYER() failed: Falha ao carregar a imagem car1_up.png");
        }
        jogador.objttexture = SDL_CreateTextureFromSurface(renderer, jogador.objtsurface);
        printf("Personagem renderizado!\n");
    }
    if(player_selecionado == 1){
        jogador.objtsurface = IMG_Load("resources/images/car2.png");
        if(!jogador.objtsurface){
        printf("renderizar_PLAYER() failed: Falha ao carregar a imagem car2.png");
        }
        jogador.objttexture = SDL_CreateTextureFromSurface(renderer, jogador.objtsurface);
        printf("Personagem renderizado!\n");
    }
    if(player_selecionado == 2){
        jogador.objtsurface = IMG_Load("resources/images/car3.png");
        if(!jogador.objtsurface){
        printf("renderizar_PLAYER() failed: Falha ao carregar a imagem car3.png");
        }
        jogador.objttexture = SDL_CreateTextureFromSurface(renderer, jogador.objtsurface);
        printf("Personagem renderizado!\n");
    }
    if(player_selecionado == 4){
        jogador.objtsurface = IMG_Load("resources/images/car4.png");
        if(!jogador.objtsurface){
        printf("renderizar_PLAYER() failed: Falha ao carregar a imagem car4.png");
        }
        jogador.objttexture = SDL_CreateTextureFromSurface(renderer, jogador.objtsurface);
        printf("Personagem renderizado!\n");
    }

}

void renderizar_mapa(){ //RENDERIZAR MAPAS
        pista0.objtsurface = IMG_Load("resources/images/pista1.jpg");
        pista0.objttexture = SDL_CreateTextureFromSurface(renderer, pista0.objtsurface);
        pista1.objtsurface = IMG_Load("resources/images/pista1.jpg");
        pista1.objttexture = SDL_CreateTextureFromSurface(renderer, pista0.objtsurface);
}

void confirmar_selecao(){ //TELA DE CONFIRMA��O
    SDL_RenderClear(renderer);
    renderizar_confirmar();
    confirmar = 1;
    while(confirmar){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bkg_confirmar, NULL, NULL);
        SDL_RenderCopy (renderer, Options_Box_confirmar, &(sBoxc), &(dBoxc));
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        SDL_Delay(1000/30);

        if(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) confirmar = 0;
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
                    selectc++;
                    if(selectc > 1) selectc = 0;
                }
                if(event.key.keysym.scancode == SDL_SCANCODE_LEFT){
                    selectc--;
                    if(selectc < 0) selectc = 1;
                }
                    if(event.key.keysym.scancode == SDL_SCANCODE_RETURN){
                        if(selectc == 0){
                            confirmar = 0;
                            SDL_RenderClear(renderer);
                            printf("Limpando render\n");
                            jogar = 1;
                            jogo();
                        }
                        if(selectc == 1){
                            confirmar = 0;
                            jogo_menu();
                        }
                    }
                }
        }
        if(selectc == 0) dBoxc.x = 288;
        if(selectc == 1) dBoxc.x = 800;

    }
    confirmar_selecao_destroy();
}

void renderizar_jogo(){ //RENDERIZA��O DO JOGO
    SDL_RenderClear(renderer);//limpando buffer
    desenha_pista();
    move_obstaculo();
    SDL_RenderCopy(renderer, jogador.objttexture,&jogador.imagem,&jogador.destino);
    score();
	SDL_RenderPresent(renderer);//exibindo
}

void jogo(){

    const float FPS = 60;
	const float FrameDelay = 1000/FPS;
	unsigned long FrameStart;
	float FrameTime;
	renderizar_player();
	renderizar_mapa();
	renderizar_objetos();

	jogador.imagem.x= 0;
	jogador.imagem.y= 0;
	jogador.imagem.w= PLAYER_WIDTH;
	jogador.imagem.h= PLAYER_HEIGHT;
	jogador.destino.x= 650;
	jogador.destino.y= 650;
	jogador.destino.w= 55;
	jogador.destino.h= 65;

	obstaculo1.imagem.w = 300;
    obstaculo1.imagem.h = 300;
    obstaculo1.imagem.x = 0;
    obstaculo1.imagem.y = 0;
    obstaculo1.destino.x = 650;
    obstaculo1.destino.y = -685;
    obstaculo1.destino.h = 55;
    obstaculo1.destino.w = 65;

    obstaculo2.imagem.w = 279;
    obstaculo2.imagem.h = 277;
    obstaculo2.imagem.x = 0;
    obstaculo2.imagem.y = 0;
    obstaculo2.destino.x = 700;
    obstaculo2.destino.y = -600;
    obstaculo2.destino.h = 55;
    obstaculo2.destino.w = 65;

    obstaculo3.imagem.w = 279;
    obstaculo3.imagem.h = 277;
    obstaculo3.imagem.x = 0;
    obstaculo3.imagem.y = 0;
    obstaculo3.destino.x = 450;
    obstaculo3.destino.y = -150;
    obstaculo3.destino.h = 55;
    obstaculo3.destino.w = 65;

    obstaculo4.imagem.w = 279;
    obstaculo4.imagem.h = 277;
    obstaculo4.imagem.x = 0;
    obstaculo4.imagem.y = 0;
    obstaculo4.destino.x = 650;
    obstaculo4.destino.y = -100;
    obstaculo4.destino.h = 55;
    obstaculo4.destino.w = 65;

    obstaculo5.imagem.w = 279;
    obstaculo5.imagem.h = 277;
    obstaculo5.imagem.x = 0;
    obstaculo5.imagem.y = 0;
    obstaculo5.destino.x = 625;
    obstaculo5.destino.y = -200;
    obstaculo5.destino.h = 55;
    obstaculo5.destino.w = 65;

    obstaculo6.imagem.w = 279;
    obstaculo6.imagem.h = 277;
    obstaculo6.imagem.x = 0;
    obstaculo6.imagem.y = 0;
    obstaculo6.destino.x = 445;
    obstaculo6.destino.y = -252;
    obstaculo6.destino.h = 55;
    obstaculo6.destino.w = 65;

    obstaculo7.imagem.w = 279;
    obstaculo7.imagem.h = 277;
    obstaculo7.imagem.x = 0;
    obstaculo7.imagem.y = 0;
    obstaculo7.destino.x = 560;
    obstaculo7.destino.y =-585;
    obstaculo7.destino.h = 55;
    obstaculo7.destino.w = 65;
    pontuacao_player = 0;


    while(jogar){
        FrameStart = SDL_GetTicks();

        renderizar_jogo();




        while(SDL_PollEvent(&event)){

			movimentacao_teclas();

        }
        movimentacao_camera();

        if(colisao(obstaculo1, jogador)){
            jogar = 0;
            jogar_novamente();
		}
		if(colisao(obstaculo2, jogador)){
			jogar = 0;
			jogar_novamente();
		}
		if(colisao(obstaculo3, jogador)){
			jogar = 0;
			jogar_novamente();
		}
		if(colisao(obstaculo4, jogador)){
			jogar = 0;
			jogar_novamente();
		}
		if(colisao(obstaculo5, jogador)){
			jogar = 0;
			jogar_novamente();
		}
		if(colisao(obstaculo6, jogador)){
			jogar = 0;
			jogar_novamente();
		}
		if(colisao(obstaculo7, jogador)){
			jogar = 0;
			jogar_novamente();
		}
		if(colisao(obstaculo1, obstaculo2)){
            if(obstaculo1.destino.x > 430) obstaculo1.destino.x +=5;
            else obstaculo1.destino.x -=5;
		}
		if(colisao(obstaculo1, obstaculo3)){
            if(obstaculo1.destino.x > 430) obstaculo1.destino.x +=5;
            else obstaculo1.destino.x -=5;
		}
		if(colisao(obstaculo1, obstaculo4)){
            if(obstaculo1.destino.x > 430) obstaculo1.destino.x +=5;
            else obstaculo1.destino.x -=5;
		}
		if(colisao(obstaculo1, obstaculo5)){
            if(obstaculo1.destino.x > 430) obstaculo1.destino.x +=5;
            else obstaculo1.destino.x -=5;
		}
		if(colisao(obstaculo1, obstaculo6)){
            if(obstaculo1.destino.x > 430) obstaculo1.destino.x +=5;
            else obstaculo1.destino.x -=5;
		}
		if(colisao(obstaculo1, obstaculo7)){
            if(obstaculo1.destino.x > 430) obstaculo1.destino.x +=5;
            else obstaculo1.destino.x -=5;
		}
		if(colisao(obstaculo2, obstaculo3)){
            if(obstaculo2.destino.x > 430) obstaculo2.destino.x +=5;
            else obstaculo2.destino.x -=5;
		}
		if(colisao(obstaculo2, obstaculo4)){
            if(obstaculo2.destino.x > 430) obstaculo2.destino.x +=5;
            else obstaculo2.destino.x -=5;
		}
		if(colisao(obstaculo2, obstaculo5)){
            if(obstaculo2.destino.x > 430) obstaculo2.destino.x +=5;
            else obstaculo2.destino.x -=5;
		}
		if(colisao(obstaculo2, obstaculo6)){
            if(obstaculo2.destino.x > 430) obstaculo2.destino.x +=5;
            else obstaculo2.destino.x -=5;
		}
		if(colisao(obstaculo2, obstaculo7)){
            if(obstaculo2.destino.x > 430) obstaculo2.destino.x +=5;
            else obstaculo2.destino.x -=5;
		}
		if(colisao(obstaculo3, obstaculo4)){
            if(obstaculo3.destino.x > 430) obstaculo3.destino.x +=5;
            else obstaculo3.destino.x -=5;
		}
		if(colisao(obstaculo3, obstaculo5)){
            if(obstaculo3.destino.x > 430) obstaculo3.destino.x +=5;
            else obstaculo3.destino.x -=5;
		}
		if(colisao(obstaculo3, obstaculo6)){
            if(obstaculo3.destino.x > 430) obstaculo3.destino.x +=5;
            else obstaculo3.destino.x -=5;
		}
		if(colisao(obstaculo3, obstaculo7)){
            if(obstaculo3.destino.x > 430) obstaculo3.destino.x +=5;
            else obstaculo3.destino.x -=5;
		}
		if(colisao(obstaculo4, obstaculo5)){
            if(obstaculo4.destino.x > 430) obstaculo4.destino.x +=5;
            else obstaculo4.destino.x -=5;
		}
		if(colisao(obstaculo4, obstaculo6)){
            if(obstaculo4.destino.x > 430) obstaculo4.destino.x +=5;
            else obstaculo4.destino.x -=5;
		}
		if(colisao(obstaculo4, obstaculo7)){
            if(obstaculo4.destino.x > 430) obstaculo4.destino.x +=5;
            else obstaculo4.destino.x -=5;
		}
		if(colisao(obstaculo5, obstaculo6)){
            if(obstaculo5.destino.x > 430) obstaculo5.destino.x +=5;
            else obstaculo5.destino.x -=5;
		}
		if(colisao(obstaculo5, obstaculo7)){
            if(obstaculo5.destino.x > 430) obstaculo5.destino.x +=5;
            else obstaculo5.destino.x -=5;
		}
		if(colisao(obstaculo6, obstaculo7)){
            if(obstaculo6.destino.x > 430) obstaculo6.destino.x +=5;
            else obstaculo6.destino.x -=5;
		}

        if(Limitador == 10){
            pontuacao_player++;
            Limitador = 0;
        }

        Limitador++;
        FrameTime = SDL_GetTicks() - FrameStart;

		if (FrameDelay > FrameTime){
			SDL_Delay(FrameDelay - FrameTime);
		}
    }

    liberar();
}


void movimentacao_teclas(){ //DETEC��O DE TECLAS
    if (event.type == SDL_KEYDOWN){ //TECLA PRESSIONADA

		if (event.key.keysym.sym == SDLK_UP) seta_up = true;
        else if (event.key.keysym.sym == SDLK_DOWN) seta_dwn = true;
        else if (event.key.keysym.sym == SDLK_LEFT) seta_lf = true;
		else if (event.key.keysym.sym == SDLK_RIGHT) seta_rg = true;
		else if (event.key.keysym.sym == SDLK_LSHIFT) lshift = true;
		else if (event.key.keysym.sym == SDLK_ESCAPE){
            jogar = 0;
            finaliza_sdl();
		}

	}

    else if (event.type == SDL_KEYUP){
		if (event.key.keysym.sym == SDLK_UP) seta_up = false;
        else if (event.key.keysym.sym == SDLK_DOWN) seta_dwn = false;
        else if (event.key.keysym.sym == SDLK_LEFT) seta_lf = false;
		else if (event.key.keysym.sym == SDLK_RIGHT) seta_rg = false;
	}
}

void movimentacao_camera(){

	if (seta_rg == true && seta_up == false && seta_dwn == false){
		if(jogador.destino.x <= 776) jogador.destino.x +=6;
    }

	if (seta_lf == true && seta_up == false && seta_dwn == false){
        if(jogador.destino.x >= 440) jogador.destino.x -=6;
	}
}

void renderizar_objetos(){
    //SURFACES
    obstaculo1.objtsurface = IMG_Load("resources/images/obstacles/car1.png");
    if(!obstaculo1.objtsurface){
        printf("renderizar_objetos() failed: Falha ao carregar a imagem obstacle1.png");
    }
    obstaculo2.objtsurface = IMG_Load("resources/images/obstacles/car1.png");
    obstaculo3.objtsurface = IMG_Load("resources/images/obstacles/car3.png");
    obstaculo4.objtsurface = IMG_Load("resources/images/obstacles/car3.png");
    obstaculo5.objtsurface = IMG_Load("resources/images/obstacles/car3.png");
    obstaculo6.objtsurface = IMG_Load("resources/images/obstacles/car1.png");
    obstaculo7.objtsurface = IMG_Load("resources/images/obstacles/car1.png");
    obstaculo8.objtsurface = IMG_Load("resources/images/obstacles/obstacle1.png");
    //TEXTURES
    obstaculo1.objttexture = SDL_CreateTextureFromSurface(renderer, obstaculo1.objtsurface);
    obstaculo2.objttexture = SDL_CreateTextureFromSurface(renderer, obstaculo2.objtsurface);
    obstaculo3.objttexture = SDL_CreateTextureFromSurface(renderer, obstaculo3.objtsurface);
    obstaculo4.objttexture = SDL_CreateTextureFromSurface(renderer, obstaculo4.objtsurface);
    obstaculo5.objttexture = SDL_CreateTextureFromSurface(renderer, obstaculo5.objtsurface);
    obstaculo6.objttexture = SDL_CreateTextureFromSurface(renderer, obstaculo6.objtsurface);
    obstaculo7.objttexture = SDL_CreateTextureFromSurface(renderer, obstaculo7.objtsurface);
    obstaculo8.objttexture = SDL_CreateTextureFromSurface(renderer, obstaculo8.objtsurface);
}

void move_obstaculo(){
    srand(time(0));
        obstaculo1.destino.y+=2;
		obstaculo2.destino.y+=2;
		obstaculo3.destino.y+=3;
		obstaculo4.destino.y+=2;
		obstaculo5.destino.y+=2;
		obstaculo6.destino.y+=2;
		obstaculo7.destino.y+=3;
		if(rand()%9 == 1){
            if(obstaculo1.destino.x < 699) obstaculo1.destino.x+=2;
		}
		if(rand()%9 == 1){
            if(obstaculo2.destino.x < 699) obstaculo2.destino.x+=3;
		}
        if(rand()%9 == 1){
            if(obstaculo3.destino.x > 404 && obstaculo3.destino.x < 600) obstaculo3.destino.x+=2;
        }
        if(rand()%9 == 1){
            if(obstaculo4.destino.x > 430 && obstaculo4.destino.x < 600) obstaculo4.destino.x+=3;
        }
		if(rand()%9 == 1){
            if(obstaculo5.destino.x > 430 && obstaculo5.destino.x < 600) obstaculo5.destino.x+=1;;
		}
		if(rand()%9 ==1){
            if(obstaculo6.destino.x < 699) obstaculo6.destino.x+=2;
		}
		if(rand()%9 == 1){
            if(obstaculo7.destino.x > 404 && obstaculo7.destino.x < 700) obstaculo7.destino.x+=3;
		}
		if(rand()%9 == 1){
            if(obstaculo5.destino.x < 699 && obstaculo5.destino.x < 700) obstaculo5.destino.x+=2;
		}
		if(rand()%9 == 1){
            if(obstaculo6.destino.x < 699) obstaculo6.destino.x+=2;
		}

		if(obstaculo1.destino.x < 420){
            obstaculo1.destino.x++;
		}
		if(obstaculo2.destino.x < 420){
            obstaculo2.destino.x++;
		}
		if(obstaculo3.destino.x < 420){
            obstaculo3.destino.x++;
		}
		if(obstaculo4.destino.x < 420){
            obstaculo4.destino.x++;
		}
		if(obstaculo5.destino.x < 420){
            obstaculo5.destino.x++;
		}
		if(obstaculo6.destino.x < 420){
            obstaculo6.destino.x++;
		}
		if(obstaculo7.destino.x < 420){
            obstaculo7.destino.x++;
		}
		if(obstaculo1.destino.x > 650){
            obstaculo1.destino.x--;
		}
		if(obstaculo2.destino.x > 650){
            obstaculo2.destino.x--;
		}
		if(obstaculo3.destino.x > 650){
            obstaculo3.destino.x--;
		}
		if(obstaculo4.destino.x > 650){
            obstaculo4.destino.x--;
		}
		if(obstaculo5.destino.x > 650){
            obstaculo5.destino.x--;
		}
		if(obstaculo6.destino.x > 650){
            obstaculo6.destino.x--;
		}
		if(obstaculo7.destino.x > 650){
            obstaculo7.destino.x--;
		}



		if(obstaculo1.destino.y>720){
			obstaculo1.destino.y=-250;
		}
		if(obstaculo2.destino.y>720){
			obstaculo2.destino.y=-350;
		}
		if(obstaculo3.destino.y>720){
            obstaculo3.destino.y=-400;
		}
		if(obstaculo4.destino.y>720){
			obstaculo4.destino.y=-198;
		}
		if(obstaculo5.destino.y>720){
			obstaculo5.destino.y=-170;
		}
		if(obstaculo6.destino.y>720){
            obstaculo6.destino.y=-150;
		}
		if(obstaculo7.destino.y>720){
			obstaculo7.destino.y=-210;
		}
			SDL_RenderCopy(renderer,obstaculo1.objttexture,&obstaculo1.imagem,&obstaculo1.destino);
			SDL_RenderCopy(renderer,obstaculo2.objttexture,&obstaculo2.imagem,&obstaculo2.destino);
			SDL_RenderCopy(renderer,obstaculo3.objttexture,&obstaculo3.imagem,&obstaculo3.destino);
			SDL_RenderCopy(renderer,obstaculo4.objttexture,&obstaculo4.imagem,&obstaculo4.destino);
			SDL_RenderCopy(renderer,obstaculo5.objttexture,&obstaculo5.imagem,&obstaculo5.destino);
			SDL_RenderCopy(renderer,obstaculo6.objttexture,&obstaculo6.imagem,&obstaculo6.destino);
			SDL_RenderCopy(renderer,obstaculo7.objttexture,&obstaculo7.imagem,&obstaculo7.destino);
}

bool colisao(OBJETO objeto, OBJETO jogador){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = objeto.destino.x;
    rightA = objeto.destino.x + jogador.destino.w;
    topA = objeto.destino.y;
    bottomA = objeto.destino.y + jogador.destino.h;

    leftB = jogador.destino.x;
    rightB = jogador.destino.x + objeto.destino.w;
    topB = jogador.destino.y;
    bottomB = jogador.destino.y + objeto.destino.h;

     if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    else return true;
}

void score(){
  char pontuacao[100];
  sprintf(pontuacao, "Score: %d", pontuacao_player);
  SDL_Surface* pontuacao_image = TTF_RenderText_Solid(gFont, pontuacao, textColor);
  SDL_Rect text_rect = {0, 0, 100, 50};
  SDL_Texture *pontuacao_texture = SDL_CreateTextureFromSurface(renderer, pontuacao_image);
  SDL_RenderCopy(renderer, pontuacao_texture, NULL, &text_rect);

}

void renderizar_jogarnovamente(){
  image_jogaragain = IMG_Load("resources/images/score.png");
  if(!image_jogaragain) printf("nao foi possivel abrir a imagem score.png\n");
  bkg_jogaragain = SDL_CreateTextureFromSurface(renderer, image_jogaragain);
  caixa_selecao_again = IMG_Load("resources/images/bordaselecaoagain.png");
  Options_Box_again = SDL_CreateTextureFromSurface(renderer, caixa_selecao_again);
}

void score_novamente(){
  char pontuacao2[100];
  sprintf(pontuacao2, "%d", pontuacao_player);
 pontuacao_novamente = TTF_RenderText_Solid(gFont, pontuacao2, textColorpreto);
  SDL_Rect score_rect = {775, 210, 50, 70};

  pontuacaoagain_texture = SDL_CreateTextureFromSurface(renderer, pontuacao_novamente);

  SDL_RenderCopy(renderer, pontuacaoagain_texture, NULL, &score_rect);
}

void jogar_novamente(){
    SDL_RenderClear(renderer);
    renderizar_jogarnovamente();
    menu_again = 1;
    while(menu_again){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bkg_jogaragain, NULL, NULL);
        SDL_RenderCopy (renderer, Options_Box_again, &(sBoxag), &(dBoxag));
        score_novamente();
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        SDL_Delay(1000/30);

        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) menu_personagem = 0;
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                    menu_again = 0;
                    finaliza_sdl();
                }
				if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
					selectagain++;
					if (selectagain > 1) selectagain = 0;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
                    selectagain--;
					if (selectagain < 0) selectagain = 1;
				}
				if(event.key.keysym.scancode == SDL_SCANCODE_RETURN){
                    if (selectagain == 0){
                        menu_again = 0;
                        jogo_menu();
                    }
                    if (selectagain == 1){
                        menu_again = 0;
                        jogo_menu();
                    }
                }
            }
        }
        if (selectagain == 0) dBoxag.x = 225;
        if (selectagain == 1) dBoxag.x = 865;
    }
    jogar_novamente_destroy();
}

void jogar_novamente_destroy(){
    SDL_FreeSurface(image_jogaragain);
    SDL_FreeSurface(caixa_selecao_again);
    SDL_DestroyTexture(bkg_jogaragain);
    SDL_DestroyTexture(Options_Box_again);
    SDL_FreeSurface(pontuacao_novamente);
    SDL_DestroyTexture(pontuacaoagain_texture);
}

void liberar(){ //FECHAR JOGO
    SDL_FreeSurface(jogador.objtsurface);
    SDL_FreeSurface(pista0.objtsurface);
    SDL_FreeSurface(pista1.objtsurface);
    SDL_FreeSurface(obstaculo1.objtsurface);
    SDL_FreeSurface(obstaculo2.objtsurface);
    SDL_FreeSurface(obstaculo3.objtsurface);
    SDL_FreeSurface(obstaculo4.objtsurface);
    SDL_FreeSurface(obstaculo5.objtsurface);
    SDL_FreeSurface(obstaculo6.objtsurface);
    SDL_FreeSurface(obstaculo7.objtsurface);
    SDL_DestroyTexture(pista0.objttexture);
    SDL_DestroyTexture(pista1.objttexture);
    SDL_DestroyTexture(jogador.objttexture);
    SDL_DestroyTexture(obstaculo1.objttexture);
    SDL_DestroyTexture(obstaculo2.objttexture);
    SDL_DestroyTexture(obstaculo3.objttexture);
    SDL_DestroyTexture(obstaculo4.objttexture);
    SDL_DestroyTexture(obstaculo5.objttexture);
    SDL_DestroyTexture(obstaculo6.objttexture);
    SDL_DestroyTexture(obstaculo7.objttexture);
}
