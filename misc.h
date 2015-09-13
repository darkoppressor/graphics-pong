/* Copyright (c) 2011 Kevin Wells */
/* Graphics Pong may be freely redistributed.  See license for details. */

#ifndef misc_h
#define misc_h

using namespace std;

void quitgame();
void options();
void game_end();
void draw();

SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;
SDL_Surface *menu = NULL;
SDL_Surface *ball_1 = NULL;
SDL_Surface *ball_2 = NULL;
SDL_Surface *ball_half = NULL;
SDL_Surface *paddle_1 = NULL;
SDL_Surface *paddle_2 = NULL;
SDL_Surface *net = NULL;
TTF_Font *font = NULL;
TTF_Font *font_medium = NULL;
TTF_Font *font_big = NULL;
Mix_Music *game_music_1 = NULL;
Mix_Music *credits_music = NULL;
Mix_Music *menu_music = NULL;
Mix_Music *crowd = NULL;
Mix_Chunk *beep1 = NULL;
Mix_Chunk *beep2 = NULL;
Mix_Chunk *score = NULL;
Mix_Chunk *applause = NULL;
Mix_Chunk *boo = NULL;
SDL_Color text_color;
SDL_Color white={255,255,255};
SDL_Color black={0,0,0};
SDL_Color icy={0,0,160};
SDL_Color fiery={160,0,0};
SDL_Color pingpong={0,160,0};
SDL_Color girly={255,90,255};
SDL_Event event;/**Used when polling for key events.*/
int SCREEN_WIDTH=1000;
int SCREEN_HEIGHT=600;
int SCREEN_BPP=0;/**We set the screen's bpp to 0 to make it set to the current screen bpp of the computer.*/
int BALL_HEIGHT=20;
int BALL_WIDTH=20;
int PADDLE_WIDTH=10;
int PADDLE_HEIGHT=80;
const int FRAMES_PER_SECOND=30;

/**Global variables used for various purposes throughout the game.*/
bool paddle=false;/**Did a paddle just hit the ball?*/
int menu_item=0;/**0=New game. 1=Options. 2=Credits. 3=Quit game.*/
int options_menu_item=0;/**0=Singleplayer/multiplayer. 1=Difficulty. 2=Theme. 3=Back.*/
bool singleplayer;/**True=Singleplayer mode, and an AI control player 2. False=Multiplayer mode; no AI, and a player must control player 2 as well as player 1.*/
int difficulty;/**0=Very easy. 1=Easy. 2=Normal. 3=Impossible.*/
int theme;/**0=Classic Pong. 1=Icy Waters. 2=Fiery Wastes. 3=Ping Pong. 4=Girly.*/
int paddle_size;/**1=One tile. 2=Two tiles. 3=Three tiles. 4=Default size(four tiles). 5=Five tiles.*/
int speed;/**This variable is used to save and load settings from the options file. 5=Slow. 4=Default speed. 3=Fast. 2=Faster. 1=Fastest.*/
int gametype;/**Reflects what gametype the game is currently set to. 0=Standard. 1=Timed.*/
bool demo=false;/**Used to turn demo mode on and off(currently starts demo mode if the user remains inactive for  seconds on the main menu.*/
bool game_in_progress;
int p1_x;
int p1_y;
int p1_x_vel;
int p1_y_vel;
int p2_x;
int p2_y;
int p2_x_vel;
int p2_y_vel;
int p1_score;
int p2_score;
int p1_hits;
int p2_hits;
int p1_misses;
int p2_misses;
int max_score;
int timer;
int timer_minutes;
int timer_seconds;
int max_timer;
int ball_x_vel;
int ball_y_vel;
int ball_x;
int ball_y;
int ball_speed_x;/**This is the actual ball speed variable used by the engine.*/
int ball_speed_y;
int highest_ball_speed;/**A stat kept throughout the game that gives the fastest speed the ball reached during the game.*/
int paddle_accel;
int wall_accel;

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL){
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source,clip,destination,&offset);
}

void msg_write(int a,int b,int font_size,string msg){
    if(font_size==0){
        message=TTF_RenderText_Solid(font,msg.c_str(),text_color);
    }
    if(font_size==1){
        message=TTF_RenderText_Solid(font_big,msg.c_str(),text_color);
    }
    if(font_size==2){
        message=TTF_RenderText_Solid(font_medium,msg.c_str(),text_color);
    }
    apply_surface(a,b,message,screen);
    SDL_FreeSurface(message);
}

void int_write(int a,int b,int font_size,int msg_int){
    char msg[3];
    itoa(msg_int,msg,10);
    if(font_size==0){
        message=TTF_RenderText_Solid(font,msg,text_color);
    }
    if(font_size==1){
        message=TTF_RenderText_Solid(font_big,msg,text_color);
    }
    if(font_size==2){
        message=TTF_RenderText_Solid(font_medium,msg,text_color);
    }
    apply_surface(a,b,message,screen);
    SDL_FreeSurface(message);
}

bool init(){
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1){
        printf("Unable to init SDL: %s\n",SDL_GetError());
        return false;
    }
    if(TTF_Init()==-1){
        printf("Unable to init SDL_ttf: %s\n",TTF_GetError());
        return false;
    }
    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if(!screen){
        printf("Unable to set video mode: %s\n",SDL_GetError());
        return false;
    }
    if(Mix_OpenAudio(22050,AUDIO_S16,2,4096)==-1){
        return false;
    }
    SDL_WM_SetCaption("Graphics Pong",NULL);
    SDL_ShowCursor(0);
    return true;
}

bool load_files(){
    font=TTF_OpenFont("Vera.ttf",12);
    if(!font){
        printf("Unable to load font: %s\n",TTF_GetError());
        return false;
    }
    font_medium=TTF_OpenFont("Vera.ttf",16);
    if(!font_medium){
        printf("Unable to load font: %s\n",TTF_GetError());
        return false;
    }
    font_big=TTF_OpenFont("Vera.ttf",22);
    if(!font_big){
        printf("Unable to load font: %s\n",TTF_GetError());
        return false;
    }
    ball_1=IMG_Load("ball.png");
    if(!ball_1){
        printf("IMG_Load: %s\n", IMG_GetError());
        return false;
    }
    ball_2=IMG_Load("ball.png");
    if(!ball_2){
        printf("IMG_Load: %s\n", IMG_GetError());
        return false;
    }
    ball_half=IMG_Load("ball_half.png");
    if(!ball_half){
        printf("IMG_Load: %s\n", IMG_GetError());
        return false;
    }
    paddle_1=IMG_Load("paddle.png");
    if(!paddle_1){
        printf("IMG_Load: %s\n", IMG_GetError());
        return false;
    }
    paddle_2=IMG_Load("paddle.png");
    if(!paddle_2){
        printf("IMG_Load: %s\n", IMG_GetError());
        return false;
    }
    net=IMG_Load("net.png");
    if(!net){
        printf("IMG_Load: %s\n", IMG_GetError());
        return false;
    }
    game_music_1 = Mix_LoadMUS("music/1.ogg");
    if(game_music_1==NULL){
        return false;
    }
    credits_music = Mix_LoadMUS("music/credits.ogg");
    if(credits_music==NULL){
        return false;
    }
    menu_music = Mix_LoadMUS("music/menu.ogg");
    if(menu_music==NULL){
        return false;
    }
    crowd = Mix_LoadMUS("music/crowd.ogg");
    if(crowd==NULL){
        return false;
    }
    beep1=Mix_LoadWAV("sounds/beep1.wav");
    if(beep1==NULL){
        return false;
    }
    beep2=Mix_LoadWAV("sounds/beep2.wav");
    if(beep2==NULL){
        return false;
    }
    score=Mix_LoadWAV("sounds/score.wav");
    if(score==NULL){
        return false;
    }
    applause=Mix_LoadWAV("sounds/applause.wav");
    if(applause==NULL){
        return false;
    }
    boo=Mix_LoadWAV("sounds/boo.wav");
    if(boo==NULL){
        return false;
    }
    return true;
}

void clean_up(){
    SDL_FreeSurface(message);
    SDL_FreeSurface(ball_1);
    SDL_FreeSurface(ball_2);
    SDL_FreeSurface(ball_half);
    SDL_FreeSurface(paddle_1);
    SDL_FreeSurface(paddle_2);
    SDL_FreeSurface(net);
    Mix_FreeChunk(beep1);
    beep1=NULL;
    Mix_FreeChunk(beep2);
    beep2=NULL;
    Mix_FreeChunk(score);
    score=NULL;
    Mix_FreeChunk(applause);
    applause=NULL;
    Mix_FreeChunk(boo);
    boo=NULL;
    while(!Mix_FadeOutMusic(1000) && Mix_PlayingMusic()){
    SDL_Delay(100);
    }
    Mix_HaltMusic();
    Mix_FreeMusic(game_music_1);
    game_music_1=NULL;
    Mix_FreeMusic(credits_music);
    credits_music=NULL;
    Mix_FreeMusic(menu_music);
    menu_music=NULL;
    Mix_FreeMusic(crowd);
    crowd=NULL;
    TTF_CloseFont(font);
    font=NULL;
    TTF_CloseFont(font_medium);
    font_medium=NULL;
    TTF_CloseFont(font_big);
    font_big=NULL;
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    printf("Exited cleanly!\n");
}

void set_color(){
    text_color=white;
}

/**This function randomly selects a number from lownum to highnum and then returns it to where it was called.
Using this we can randomly generate numbers anywhere in the game whenever we need them.*/
int random_range(int lownum, int highnum){
	if(lownum > highnum)
	swap(lownum, highnum);
	int range = highnum - lownum + 1;
	return lownum + int(range * rand()/(RAND_MAX + 1.0));
}

/**Sets the console window's size(this is currently used in 'int Main()' to set the console window to the Windows default).*/
int setConsoleSize(int width, int height){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD scr_dim;
    scr_dim.X = width;
    scr_dim.Y = height;
    SetConsoleScreenBufferSize(hOut, scr_dim);
}

#endif
