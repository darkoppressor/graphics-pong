/* Copyright (c) 2011 Kevin Wells */
/* Graphics Pong may be freely redistributed.  See license for details. */

#ifndef game_h
#define game_h

using namespace std;

void game();
void press_any_key();

void save_options(){
    ofstream options_file ("options.cfg");
    if(options_file.is_open()){
        if(singleplayer==false)
            options_file << "0";
        if(singleplayer==true)
            options_file << "1";
        if(difficulty==0)
            options_file << "0";
        if(difficulty==1)
            options_file << "1";
        if(difficulty==2)
            options_file << "2";
        if(difficulty==3)
            options_file << "3";
        if(theme==0)
            options_file << "0";
        if(theme==1)
            options_file << "1";
        if(theme==2)
            options_file << "2";
        if(theme==3)
            options_file << "3";
        if(theme==4)
            options_file << "4";
        if(speed==1)
            options_file << "1";
        if(speed==2)
            options_file << "2";
        if(speed==3)
            options_file << "3";
        if(speed==4)
            options_file << "4";
        if(speed==5)
            options_file << "5";
        if(paddle_size==1)
            options_file << "1";
        if(paddle_size==2)
            options_file << "2";
        if(paddle_size==3)
            options_file << "3";
        if(paddle_size==4)
            options_file << "4";
        if(paddle_size==5)
            options_file << "5";
        if(gametype==0)
            options_file << "0";
        if(gametype==1)
            options_file << "1";
        if(gametype==2)
            options_file << "2";
        options_file.close();
    }
}

void quitgame(){
    clean_up();
    exit(EXIT_SUCCESS);
}

void game_end(){
    Mix_HaltMusic();
    if((singleplayer==true && p1_score>=p2_score) || (singleplayer==false && p1_score>=p2_score) || (singleplayer==false && p1_score<p2_score))
    Mix_PlayChannel(-1,applause,0);
    if(singleplayer==true && p1_score<p2_score)
    Mix_PlayChannel(-1,boo,0);
    Mix_FadeInMusic(crowd,-1,1000);
    fill_screen();
    set_color();
    msg_write(SCREEN_WIDTH/2-40,5,1,"Game Over");
    msg_write(SCREEN_WIDTH/2-10,SCREEN_HEIGHT/2-110,2,"Winner:");
    if(p1_score<p2_score)
    msg_write(SCREEN_WIDTH/2-10,SCREEN_HEIGHT/2-90,0,"Player 2");
    if(p1_score>p2_score)
    msg_write(SCREEN_WIDTH/2-10,SCREEN_HEIGHT/2-90,0,"Player 1");
    if(p1_score==p2_score)
    msg_write(SCREEN_WIDTH/2+10,SCREEN_HEIGHT/2-90,0,"Tie");
    msg_write(SCREEN_WIDTH/2-125,SCREEN_HEIGHT/2-70,2,"Player 1");
    msg_write(SCREEN_WIDTH/2+100,SCREEN_HEIGHT/2-70,2,"Player 2");
    msg_write(SCREEN_WIDTH/2-125,SCREEN_HEIGHT/2-50,0,"Score:");
    msg_write(SCREEN_WIDTH/2+100,SCREEN_HEIGHT/2-50,0,"Score:");
    msg_write(SCREEN_WIDTH/2-125,SCREEN_HEIGHT/2-30,0,"Hits:");
    msg_write(SCREEN_WIDTH/2+100,SCREEN_HEIGHT/2-30,0,"Hits:");
    msg_write(SCREEN_WIDTH/2-125,SCREEN_HEIGHT/2-10,0,"Misses:");
    msg_write(SCREEN_WIDTH/2+100,SCREEN_HEIGHT/2-10,0,"Misses:");
    msg_write(SCREEN_WIDTH/2-60,SCREEN_HEIGHT/2+30,0,"Fastest Ball Speed Reached:");
    int_write(SCREEN_WIDTH/2-75,SCREEN_HEIGHT/2-50,0,p1_score);
    int_write(SCREEN_WIDTH/2+150,SCREEN_HEIGHT/2-50,0,p2_score);
    int_write(SCREEN_WIDTH/2-75,SCREEN_HEIGHT/2-30,0,p1_hits);
    int_write(SCREEN_WIDTH/2+150,SCREEN_HEIGHT/2-30,0,p2_hits);
    int_write(SCREEN_WIDTH/2-75,SCREEN_HEIGHT/2-10,0,p1_misses);
    int_write(SCREEN_WIDTH/2+150,SCREEN_HEIGHT/2-10,0,p2_misses);
    int_write(SCREEN_WIDTH/2+15,SCREEN_HEIGHT/2+50,0,highest_ball_speed);
    SDL_Flip(screen);
    press_any_key();
    quitgame();
}

void newgame(){
    SDL_EnableKeyRepeat(10,100);
    p1_x=20;
    p1_y=0;
    p1_x_vel=0;
    p1_y_vel=0;
    p2_x=SCREEN_WIDTH-PADDLE_WIDTH-20;
    p2_y=0;
    p2_x_vel=0;
    p2_y_vel=0;
    p1_score=0;
    p2_score=0;
    timer=0;
    max_timer=2;
    max_score=10;
    highest_ball_speed=0;
    ball_1=IMG_Load("ball.png");
    reset_ball();
    Mix_HaltMusic();
    Mix_FadeInMusic(game_music_1,-1,1000);
    game();
}

void draw_main_menu(){
    fill_screen();
    set_color();
    msg_write(SCREEN_WIDTH/2-55,5,1,"Graphics Pong");
    msg_write(SCREEN_WIDTH/2-80,40,2,"A Kevin Wells Production");
    msg_write(SCREEN_WIDTH/2-30,SCREEN_HEIGHT/2-110,0,"Start New Game");
    msg_write(SCREEN_WIDTH/2-5,SCREEN_HEIGHT/2-90,0,"Options");
    msg_write(SCREEN_WIDTH/2-4,SCREEN_HEIGHT/2-70,0,"Credits");
    msg_write(SCREEN_WIDTH/2+2,SCREEN_HEIGHT/2-50,0,"Quit");
    if(menu_item==0){
        apply_surface(SCREEN_WIDTH/2-40,SCREEN_HEIGHT/2-107,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+67,SCREEN_HEIGHT/2-107,ball_half,screen);
    }
    if(menu_item==1){
        apply_surface(SCREEN_WIDTH/2-40,SCREEN_HEIGHT/2-87,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+67,SCREEN_HEIGHT/2-87,ball_half,screen);
    }
    if(menu_item==2){
        apply_surface(SCREEN_WIDTH/2-40,SCREEN_HEIGHT/2-67,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+67,SCREEN_HEIGHT/2-67,ball_half,screen);
    }
    if(menu_item==3){
        apply_surface(SCREEN_WIDTH/2-40,SCREEN_HEIGHT/2-47,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+67,SCREEN_HEIGHT/2-47,ball_half,screen);
    }
    SDL_Flip(screen);
}

void draw_options_menu(){
    fill_screen();
    set_color();
    msg_write(SCREEN_WIDTH/2-20,5,1,"Options");
    msg_write(SCREEN_WIDTH/2-300,SCREEN_HEIGHT/2-110,0,"Game Type: ");
    if(gametype==0)
        msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-110,0,"Standard");
    if(gametype==1)
        msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-110,0,"Timed");
    if(gametype==2)
        msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-110,0,"Unending Fun");
        msg_write(SCREEN_WIDTH/2-300,SCREEN_HEIGHT/2-90,0,"Human Players: ");
        if(singleplayer==false)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-90,0,"Two");
        if(singleplayer==true)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-90,0,"One");
        msg_write(SCREEN_WIDTH/2-300,SCREEN_HEIGHT/2-70,0,"AI Personality: ");
        if(difficulty==0)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-70,0,"Slow and stupid (Very easy)");
        if(difficulty==1)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-70,0,"Slow to react (Easy)");
        if(difficulty==2)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-70,0,"A worthy opponent (Normal)");
        if(difficulty==3)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-70,0,"You will not win (Impossible)");
        msg_write(SCREEN_WIDTH/2-300,SCREEN_HEIGHT/2-50,0,"Starting Speed: ");
        if(speed==1)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-50,0,"Use the force (Fastest)");
        if(speed==2)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-50,0,"Test your reflexes (Faster)");
        if(speed==3)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-50,0,"Speeding up (Fast)");
        if(speed==4)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-50,0,"Default speed (A reasonable speed)");
        if(speed==5)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-50,0,"Slow as molasses (Slow)");
        msg_write(SCREEN_WIDTH/2-300,SCREEN_HEIGHT/2-30,0,"Paddle Size: ");
        if(paddle_size==1)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-30,0,"What are you trying to prove? (One tile)");
        if(paddle_size==2)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-30,0,"Think you're tough? (Two tiles)");
        if(paddle_size==3)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-30,0,"Sharpened senses (Three tiles)");
        if(paddle_size==4)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-30,0,"Default size (Four tiles)");
        if(paddle_size==5)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-30,0,"Hard to miss (Five tiles)");
        msg_write(SCREEN_WIDTH/2-300,SCREEN_HEIGHT/2-10,0,"Theme: ");
        if(theme==0)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-10,0,"Classic Pong");
        if(theme==1)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-10,0,"Icy Waters");
        if(theme==2)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-10,0,"Fiery Wastes");
        if(theme==3)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-10,0,"Ping Pong");
        if(theme==4)
            msg_write(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-10,0,"Girly");
        msg_write(SCREEN_WIDTH/2-250,SCREEN_HEIGHT/2+10,0,"Quit Game");
        msg_write(SCREEN_WIDTH/2-250,SCREEN_HEIGHT/2+30,0,"Back");
    if(options_menu_item==0){
        apply_surface(SCREEN_WIDTH/2-310,SCREEN_HEIGHT/2-107,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+92,SCREEN_HEIGHT/2-107,ball_half,screen);
    }
    if(options_menu_item==1){
        apply_surface(SCREEN_WIDTH/2-310,SCREEN_HEIGHT/2-87,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+92,SCREEN_HEIGHT/2-87,ball_half,screen);
    }
    if(options_menu_item==2){
        apply_surface(SCREEN_WIDTH/2-310,SCREEN_HEIGHT/2-67,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+92,SCREEN_HEIGHT/2-67,ball_half,screen);
    }
    if(options_menu_item==3){
        apply_surface(SCREEN_WIDTH/2-310,SCREEN_HEIGHT/2-47,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+92,SCREEN_HEIGHT/2-47,ball_half,screen);
    }
    if(options_menu_item==4){
        apply_surface(SCREEN_WIDTH/2-310,SCREEN_HEIGHT/2-27,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+92,SCREEN_HEIGHT/2-27,ball_half,screen);
    }
    if(options_menu_item==5){
        apply_surface(SCREEN_WIDTH/2-310,SCREEN_HEIGHT/2-7,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+92,SCREEN_HEIGHT/2-7,ball_half,screen);
    }
    if(options_menu_item==6){
        apply_surface(SCREEN_WIDTH/2-310,SCREEN_HEIGHT/2+13,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+92,SCREEN_HEIGHT/2+13,ball_half,screen);
    }
    if(options_menu_item==7){
        apply_surface(SCREEN_WIDTH/2-310,SCREEN_HEIGHT/2+33,ball_half,screen);
        apply_surface(SCREEN_WIDTH/2+92,SCREEN_HEIGHT/2+33,ball_half,screen);
    }
    SDL_Flip(screen);
}

void credits(){
    bool menu_done=false;
    fill_screen();
    set_color();
    msg_write(SCREEN_WIDTH/2-25,5,1,"Credits");
    msg_write(SCREEN_WIDTH/2-37,SCREEN_HEIGHT/2-210,2,"Programming");
    msg_write(SCREEN_WIDTH/2-20,SCREEN_HEIGHT/2-190,0,"Kevin Wells");
    msg_write(SCREEN_WIDTH/2-30,SCREEN_HEIGHT/2-170,2,"Playtesters");
    msg_write(SCREEN_WIDTH/2-25,SCREEN_HEIGHT/2-150,0,"Aneissa Wells");
    msg_write(SCREEN_WIDTH/2-20,SCREEN_HEIGHT/2-130,0,"Kevin Wells");
    msg_write(SCREEN_WIDTH/2-65,SCREEN_HEIGHT-20,0,"Press any key to continue.");
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
                    draw_main_menu();
                    break;
                }
                break;
            }
        }
        SDL_Flip(screen);
    }
    Mix_HaltMusic();
    Mix_FadeInMusic(menu_music,-1,1000);
}

void options(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);
    bool menu_done=false;
    options_menu_item=0;
    draw_options_menu();
    while(!menu_done){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                default:
                break;
                case SDL_QUIT:
                    quitgame();
                break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_DOWN || event.key.keysym.sym==SDLK_KP2){
                        options_menu_item++;
                        if(options_menu_item>7)
                            options_menu_item=0;
                        draw_options_menu();
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_UP || event.key.keysym.sym==SDLK_KP8){
                        options_menu_item--;
                        if(options_menu_item<0)
                            options_menu_item=7;
                        draw_options_menu();
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_RIGHT || event.key.keysym.sym==SDLK_KP6){
                        if(options_menu_item==0){
                            gametype++;
                        if(gametype>2)
                            gametype=0;
                        draw_options_menu();
                        save_options();
                        break;
                        }
                        if(options_menu_item==1 && singleplayer==false){
                            singleplayer=true;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        if(options_menu_item==1 && singleplayer==true){
                            singleplayer=false;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        if(options_menu_item==2){
                            difficulty++;
                            if(difficulty>3)
                                difficulty=0;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        if(options_menu_item==3){
                            speed--;
                            if(speed<1)
                                speed=5;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        if(options_menu_item==4){
                            paddle_size--;
                            if(paddle_size<1)
                                paddle_size=5;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        if(options_menu_item==5){
                            theme++;
                            if(theme>4)
                                theme=0;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_LEFT || event.key.keysym.sym==SDLK_KP4){
                        if(options_menu_item==0){
                            gametype--;
                            if(gametype<0)
                                gametype=2;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        if(options_menu_item==1 && singleplayer==false){
                            singleplayer=true;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        if(options_menu_item==1 && singleplayer==true){
                            singleplayer=false;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        if(options_menu_item==2){
                            difficulty--;
                            if(difficulty<0)
                                difficulty=3;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        if(options_menu_item==3){
                            speed++;
                            if(speed>5)
                                speed=1;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        if(options_menu_item==4){
                            paddle_size++;
                            if(paddle_size>5)
                                paddle_size=1;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        if(options_menu_item==5){
                            theme--;
                            if(theme<0)
                                theme=4;
                            draw_options_menu();
                            save_options();
                            break;
                        }
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_q){
                        if(game_in_progress==true)
                            game_end();
                        if(game_in_progress==false)
                            quitgame();
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_RETURN){
                        if(options_menu_item==6){
                            if(game_in_progress==true)
                                game_end();
                            if(game_in_progress==false)
                                quitgame();
                        }
                        if(options_menu_item==7)
                            menu_done=true;
                            break;
                        }
                    if(event.key.keysym.sym==SDLK_ESCAPE || event.key.keysym.sym==SDLK_SPACE){
                        menu_done=true;
                        break;
                    }
            }
            break;
        }
    }
    if(menu_done==true && game_in_progress==true){
        SDL_EnableKeyRepeat(10,100);
        Mix_HaltMusic();
        Mix_FadeInMusic(game_music_1,-1,1000);
        draw();
    }
    if(menu_done==true && game_in_progress==false){
        Mix_HaltMusic();
        Mix_FadeInMusic(menu_music,-1,1000);
        menu_done=false;
        draw_main_menu();
    }
}

void main_menu(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);
    game_in_progress=false;
    int menu_tick=0;
    draw_main_menu();
    bool main_menu_done=false;
    while(!main_menu_done){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quitgame();
                break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_DOWN || event.key.keysym.sym==SDLK_KP2){
                        menu_tick=0;
                        menu_item++;
                        if(menu_item>3)
                        menu_item=0;
                        draw_main_menu();
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_UP || event.key.keysym.sym==SDLK_KP8){
                        menu_tick=0;
                        menu_item--;
                        if(menu_item<0)
                        menu_item=3;
                        draw_main_menu();
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_RETURN){
                        menu_tick=0;
                        if(menu_item==0)
                            newgame();
                        if(menu_item==1)
                            options();
                        if(menu_item==2){
                            Mix_HaltMusic();
                            Mix_FadeInMusic(credits_music,-1,1000);
                            credits();
                        }
                        if(menu_item==3)
                            quitgame();
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_ESCAPE || event.key.keysym.sym==SDLK_q){
                        quitgame();
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_n || event.key.keysym.sym==SDLK_s){
                        menu_tick=0;
                        newgame();
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_o){
                        menu_tick=0;
                        options();
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_c){
                        menu_tick=0;
                        Mix_HaltMusic();
                        Mix_FadeInMusic(credits_music,-1,1000);
                        credits();
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_d){
                        menu_tick=0;
                        demo=true;
                        newgame();
                        break;
                    }
            }
        }
        SDL_Delay(1);
        menu_tick++;
        /**If there is no input for ~30 seconds, start the demo. 1000 ticks=~2 second.*/
        if(menu_tick==15000){
            menu_tick=0;
            demo=true;
            newgame();
        }
    }
}

#endif
