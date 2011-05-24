#ifndef screen_draw_h
#define screen_draw_h

using namespace std;

void fill_screen(){
    if(theme==0)
        SDL_FillRect(screen,0,SDL_MapRGB(screen->format,0,0,0));
    if(theme==1)
        SDL_FillRect(screen,0,SDL_MapRGB(screen->format,0,0,160));
    if(theme==2)
        SDL_FillRect(screen,0,SDL_MapRGB(screen->format,160,0,0));
    if(theme==3)
        SDL_FillRect(screen,0,SDL_MapRGB(screen->format,0,160,0));
    if(theme==4)
        SDL_FillRect(screen,0,SDL_MapRGB(screen->format,255,90,255));
}

void draw(){
    fill_screen();
    for(int y=0;y<SCREEN_HEIGHT;y+=8)
        apply_surface(SCREEN_WIDTH/2,y,net,screen);
    int_write(SCREEN_WIDTH/4,SCREEN_HEIGHT/12,2,p1_score);
    int_write(SCREEN_WIDTH/2+SCREEN_WIDTH/12,SCREEN_HEIGHT-SCREEN_HEIGHT/14,2,timer_minutes);
    msg_write(SCREEN_WIDTH/2+SCREEN_WIDTH/12+10,SCREEN_HEIGHT-SCREEN_HEIGHT/14,2,":");
    if(timer_seconds<10){
        msg_write(SCREEN_WIDTH/2+SCREEN_WIDTH/12+20,SCREEN_HEIGHT-SCREEN_HEIGHT/14,2,"0");
        int_write(SCREEN_WIDTH/2+SCREEN_WIDTH/12+30,SCREEN_HEIGHT-SCREEN_HEIGHT/14,2,timer_seconds);
    }
    else{
    int_write(SCREEN_WIDTH/2+SCREEN_WIDTH/12+20,SCREEN_HEIGHT-SCREEN_HEIGHT/14,2,timer_seconds);
    }
    int_write(SCREEN_WIDTH-SCREEN_WIDTH/4,SCREEN_HEIGHT/12,2,p2_score);
    apply_surface(ball_x,ball_y,ball_1,screen);
    apply_surface(p1_x,p1_y,paddle_1,screen);
    apply_surface(p2_x,p2_y,paddle_2,screen);
    SDL_Flip(screen);
}

#endif
