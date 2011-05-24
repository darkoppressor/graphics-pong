/* Copyright (c) 2011 Kevin Wells */
/* Graphics Pong may be freely redistributed.  See license for details. */

#ifndef input_h
#define input_h

using namespace std;

void press_any_key(){
    bool menu_done=false;
    while(!menu_done){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                quitgame();
                break;
                case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    default:
                    menu_done=true;
                    break;
                }
                break;
            }
        }
    }
}

void input_check(){
    while(SDL_PollEvent(&event)){
    switch(event.type){
        case SDL_QUIT:
        if(demo==false){
            game_in_progress=false;
            game_end();
        }
        if(demo==true)
            quitgame();
        break;
        case SDL_KEYUP:
        switch(event.key.keysym.sym){
            default:
            break;
            case SDLK_UP:
            if(demo==false)
            p1_y_vel=0;
            break;
            case SDLK_DOWN:
            if(demo==false)
            p1_y_vel=0;
            break;
            case SDLK_KP8:
            if(singleplayer==false)
            p2_y_vel=0;
            break;
            case SDLK_KP2:
            if(singleplayer==false)
            p2_y_vel=0;
            break;
        }
        break;
        case SDL_KEYDOWN:
        switch(event.key.keysym.sym){
            /**default encompasses all keys not covered by the cases below.*/
            default:
            demo_return_to_menu();
            break;
            case SDLK_UP:
            if(demo==false){
                p1_y_vel-=PADDLE_HEIGHT/8;
                move_p1();
            }
            demo_return_to_menu();
            break;
            case SDLK_KP8:
            if(singleplayer==false){
                p2_y_vel-=PADDLE_HEIGHT/8;
                move_p2();
            }
            demo_return_to_menu();
            break;
            case SDLK_DOWN:
            if(demo==false){
                p1_y_vel+=PADDLE_HEIGHT/8;
                move_p1();
            }
            demo_return_to_menu();
            break;
            case SDLK_KP2:
            if(singleplayer==false){
                p2_y_vel+=PADDLE_HEIGHT/8;
                move_p2();
            }
            demo_return_to_menu();
            break;
            case SDLK_ESCAPE:
            Mix_HaltMusic();
            Mix_FadeInMusic(menu_music,-1,3000);
            options();
            break;
            case SDLK_q:
            game_in_progress=false;
            game_end();
            break;
            case SDLK_p: case SDLK_SPACE:
            set_color();
            msg_write(SCREEN_WIDTH/2-50,SCREEN_HEIGHT/2-10,2,"Game   paused.");
            SDL_Flip(screen);
            press_any_key();
            draw();
            break;
        }
        break;
    }
    }
}

#endif
