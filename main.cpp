/* Copyright (c) 2011 Kevin Wells */
/* Graphics Pong may be freely redistributed.  See license for details. */

#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "misc.h"
#include "ball.h"
#include "timer.h"
#include "screen_draw.h"
#include "game.h"
#include "paddles.h"
#include "ai.h"
#include "demo.h"
#include "input.h"

using namespace std;

void game(){
    Timer fps;
    game_in_progress=true;
    draw();
    while(game_in_progress==true){
        fps.start();
        input_check();
        move_ball();
        if((p1_score>=max_score && gametype==0 && demo==false) || (p2_score>=max_score && gametype==0 && demo==false))
            game_end();
        if(timer_minutes==max_timer && gametype==1 && demo==false)
            game_end();
        move_p1();
        move_p2();
        draw();
        if(fps.get_ticks()<1000/FRAMES_PER_SECOND)
            SDL_Delay((1000/FRAMES_PER_SECOND)-fps.get_ticks());
            timer_advance();
    }
}

int main(int argc, char *argv[]){
    srand((unsigned) time(NULL));
    /**Initiation of SDL stuff.*/
    if(init()==false){
        return 1;
    }
    if(load_files()==false){
        return 1;
    }
    char c;
    int options_temp=0;
    ifstream options_file ("options.cfg");
    if(options_file.is_open()){
        while(options_temp<6){
            options_file.get(c);
            if(options_temp==0){
                if(c=='0')
                singleplayer=false;
                if(c=='1')
                singleplayer=true;
            }
            if(options_temp==1){
                if(c=='0')
                difficulty=0;
                if(c=='1')
                difficulty=1;
                if(c=='2')
                difficulty=2;
                if(c=='3')
                difficulty=3;
            }
            if(options_temp==2){
                if(c=='0')
                theme=0;
                if(c=='1')
                theme=1;
                if(c=='2')
                theme=2;
                if(c=='3')
                theme=3;
                if(c=='4')
                theme=4;
            }
            if(options_temp==3){
                if(c=='1')
                speed=1;
                if(c=='2')
                speed=2;
                if(c=='3')
                speed=3;
                if(c=='4')
                speed=4;
                if(c=='5')
                speed=5;
            }
            if(options_temp==4){
                if(c=='1')
                paddle_size=1;
                if(c=='2')
                paddle_size=2;
                if(c=='3')
                paddle_size=3;
                if(c=='4')
                paddle_size=4;
                if(c=='5')
                paddle_size=5;
            }
            if(options_temp==5){
                if(c=='0')
                gametype=0;
                if(c=='1')
                gametype=1;
                if(c=='2')
                gametype=2;
            }
            options_temp++;
        }
        options_file.close();
    }
    else{
        singleplayer=true;
        difficulty=2;
        theme=0;
        speed=4;
        paddle_size=4;
        gametype=2;
        save_options();
    }
    Mix_FadeInMusic(menu_music,-1,1000);
    Mix_VolumeMusic(MIX_MAX_VOLUME/8);
    Mix_VolumeChunk(beep1,MIX_MAX_VOLUME/8);
    Mix_VolumeChunk(beep2,MIX_MAX_VOLUME/8);
    Mix_VolumeChunk(score,MIX_MAX_VOLUME/8);
    Mix_VolumeChunk(applause,MIX_MAX_VOLUME/8);
    Mix_VolumeChunk(boo,MIX_MAX_VOLUME/8);
    main_menu();
    clean_up();
    return 0;
}
