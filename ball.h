#ifndef ball_h
#define ball_h

using namespace std;

void reset_speed(){
    if(speed==1){
        ball_speed_x=20;
        ball_speed_y=20;
    }
    if(speed==2){
        ball_speed_x=16;
        ball_speed_y=16;
    }
    if(speed==3){
        ball_speed_x=12;
        ball_speed_y=12;
    }
    if(speed==4){
        ball_speed_x=8;
        ball_speed_y=8;
    }
    if(speed==5){
        ball_speed_x=4;
        ball_speed_y=4;
    }
}

void reset_ball(){
    reset_speed();
    ball_x_vel=0;
    ball_y_vel=0;
    ball_x=random_range((SCREEN_WIDTH/2)-10,(SCREEN_WIDTH/2)+10);
    int x=random_range(0,1);
    if(x==0)
        ball_y=SCREEN_HEIGHT-BALL_HEIGHT;
    if(x==1)
        ball_y=0;
    x=random_range(0,1);
    if(x==0 && ball_y==0){
        ball_x_vel-=ball_speed_x;
        ball_y_vel+=ball_speed_y;
    }
    if(x==1 && ball_y==0){
        ball_x_vel+=ball_speed_x;
        ball_y_vel+=ball_speed_y;
    }
    if(x==0 && ball_y==SCREEN_HEIGHT-BALL_HEIGHT){
        ball_x_vel-=ball_speed_x;
        ball_y_vel-=ball_speed_y;
    }
    if(x==1 && ball_y==SCREEN_HEIGHT-BALL_HEIGHT){
        ball_x_vel+=ball_speed_x;
        ball_y_vel-=ball_speed_y;
    }
}

bool paddle_check(){
    bool paddle_vel_was_neg=false;
    /**If ball hits middle of player 1's paddle moving upwards, bump it away.*/
    if(ball_x<=20+PADDLE_WIDTH && ball_x+BALL_WIDTH>=20 && ball_y>=p1_y && ball_y+BALL_HEIGHT<=p1_y+PADDLE_HEIGHT && ball_y_vel<0){
        Mix_PlayChannel(-1,beep1,0);
        if(p1_y_vel<0){
            paddle_vel_was_neg=true;
            p1_y_vel*=-1;
        }
        if(p1_y_vel!=0)
            paddle_accel=paddle_accel+p1_y_vel/5;
        if(paddle_vel_was_neg==true){
            paddle_vel_was_neg=false;
            p1_y_vel*=-1;
        }
        ball_speed_x+=paddle_accel;
        ball_speed_y+=paddle_accel;
        p1_hits++;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel+=ball_speed_x;
        ball_y_vel-=ball_speed_y;
        ball_x=20+PADDLE_WIDTH+1;
        return true;
    }
    /**If ball hits middle of player 1's paddle moving downwards, bump it away.*/
    if(ball_x<=20+PADDLE_WIDTH && ball_x+BALL_WIDTH>=20 && ball_y>=p1_y && ball_y+BALL_HEIGHT<=p1_y+PADDLE_HEIGHT && ball_y_vel>0){
        Mix_PlayChannel(-1,beep1,0);
        if(p1_y_vel<0){
            paddle_vel_was_neg=true;
            p1_y_vel*=-1;
        }
        if(p1_y_vel!=0)
            paddle_accel=paddle_accel+p1_y_vel/5;
        if(paddle_vel_was_neg==true){
            paddle_vel_was_neg=false;
            p1_y_vel*=-1;
        }
        ball_speed_x+=paddle_accel;
        ball_speed_y+=paddle_accel;
        p1_hits++;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel+=ball_speed_x;
        ball_y_vel+=ball_speed_y;
        ball_x=20+PADDLE_WIDTH+1;
        return true;
    }
    /**If ball hits the bottom corner of player 1's paddle moving upwards, bump it back the way it came.*/
    if(ball_x<=20+PADDLE_WIDTH && ball_x+BALL_WIDTH>=20 && ball_y>p1_y+PADDLE_HEIGHT && ball_y<=p1_y+PADDLE_HEIGHT+1 && ball_y_vel<0){
        Mix_PlayChannel(-1,beep1,0);
        if(p1_y_vel<0){
            paddle_vel_was_neg=true;
            p1_y_vel*=-1;
        }
        if(p1_y_vel!=0)
            paddle_accel=paddle_accel+p1_y_vel/5;
        if(paddle_vel_was_neg==true){
            paddle_vel_was_neg=false;
            p1_y_vel*=-1;
        }
        ball_speed_x+=paddle_accel;
        ball_speed_y+=paddle_accel;
        p1_hits++;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel+=ball_speed_x;
        ball_y_vel+=ball_speed_y;
        ball_x=20+PADDLE_WIDTH+1;
        ball_x+=ball_x_vel;
        ball_y+=ball_y_vel;
        return true;
    }
    /**If ball hits the top corner of player 1's paddle moving downwards, bump it back the way it came.*/
    if(ball_x<=20+PADDLE_WIDTH && ball_x+BALL_WIDTH>=20 && ball_y+BALL_HEIGHT<p1_y && ball_y+BALL_HEIGHT>=p1_y-1 && ball_y_vel>0){
        Mix_PlayChannel(-1,beep1,0);
        if(p1_y_vel<0){
            paddle_vel_was_neg=true;
            p1_y_vel*=-1;
        }
        if(p1_y_vel!=0)
            paddle_accel=paddle_accel+p1_y_vel/5;
        if(paddle_vel_was_neg==true){
            paddle_vel_was_neg=false;
            p1_y_vel*=-1;
        }
        ball_speed_x+=paddle_accel;
        ball_speed_y+=paddle_accel;
        p1_hits++;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel+=ball_speed_x;
        ball_y_vel-=ball_speed_y;
        ball_x=20+PADDLE_WIDTH+1;
        ball_x+=ball_x_vel;
        ball_y+=ball_y_vel;
        return true;
    }
    /**If ball hits middle of player 2's paddle moving upwards, bump it away.*/
    if(ball_x+BALL_WIDTH>=SCREEN_WIDTH-20-PADDLE_WIDTH && ball_x<=SCREEN_WIDTH-20 && ball_y>=p2_y && ball_y+BALL_HEIGHT<=p2_y+PADDLE_HEIGHT && ball_y_vel<0){
        Mix_PlayChannel(-1,beep1,0);
        if(p2_y_vel<0){
            paddle_vel_was_neg=true;
            p2_y_vel*=-1;
        }
        if(p2_y_vel!=0)
            paddle_accel=paddle_accel+p2_y_vel/5;
        if(paddle_vel_was_neg==true){
            paddle_vel_was_neg=false;
            p2_y_vel*=-1;
        }
        ball_speed_x+=paddle_accel;
        ball_speed_y+=paddle_accel;
        p2_hits++;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel-=ball_speed_x;
        ball_y_vel-=ball_speed_y;
        ball_x=SCREEN_WIDTH-20-PADDLE_WIDTH-BALL_WIDTH-1;
        return true;
    }
    /**If ball hits middle of player 2's paddle moving downwards, bump it away.*/
    if(ball_x+BALL_WIDTH>=SCREEN_WIDTH-20-PADDLE_WIDTH && ball_x<=SCREEN_WIDTH-20 && ball_y>=p2_y && ball_y+BALL_HEIGHT<=p2_y+PADDLE_HEIGHT && ball_y_vel>0){
        Mix_PlayChannel(-1,beep1,0);
        if(p2_y_vel<0){
            paddle_vel_was_neg=true;
            p2_y_vel*=-1;
        }
        if(p2_y_vel!=0)
            paddle_accel=paddle_accel+p2_y_vel/5;
        if(paddle_vel_was_neg==true){
            paddle_vel_was_neg=false;
            p2_y_vel*=-1;
        }
        ball_speed_x+=paddle_accel;
        ball_speed_y+=paddle_accel;
        p2_hits++;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel-=ball_speed_x;
        ball_y_vel+=ball_speed_y;
        ball_x=SCREEN_WIDTH-20-PADDLE_WIDTH-BALL_WIDTH-1;
        return true;
    }
    /**If ball hits the bottom corner of player 2's paddle moving upwards, bump it back the way it came.*/
    if(ball_x+BALL_WIDTH>=SCREEN_WIDTH-20-PADDLE_WIDTH && ball_x<=SCREEN_WIDTH-20 && ball_y>p2_y+PADDLE_HEIGHT && ball_y<=p2_y+PADDLE_HEIGHT+1 && ball_y_vel<0){
        Mix_PlayChannel(-1,beep1,0);
        if(p2_y_vel<0){
            paddle_vel_was_neg=true;
            p2_y_vel*=-1;
        }
        if(p2_y_vel!=0)
            paddle_accel=paddle_accel+p2_y_vel/5;
        if(paddle_vel_was_neg==true){
            paddle_vel_was_neg=false;
            p2_y_vel*=-1;
        }
        ball_speed_x+=paddle_accel;
        ball_speed_y+=paddle_accel;
        p2_hits++;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel-=ball_speed_x;
        ball_y_vel+=ball_speed_y;
        ball_x=SCREEN_WIDTH-20-PADDLE_WIDTH-BALL_WIDTH-1;
        ball_x+=ball_x_vel;
        ball_y+=ball_y_vel;
        return true;
    }
    /**If ball hits the top corner of player 2's paddle moving downwards, bump it back the way it came.*/
    if(ball_x+BALL_WIDTH>=SCREEN_WIDTH-20-PADDLE_WIDTH && ball_x<=SCREEN_WIDTH-20 && ball_y+BALL_HEIGHT<p2_y && ball_y+BALL_HEIGHT>=p2_y-1 && ball_y_vel>0){
        Mix_PlayChannel(-1,beep1,0);
        if(p2_y_vel<0){
            paddle_vel_was_neg=true;
            p2_y_vel*=-1;
        }
        if(p2_y_vel!=0)
            paddle_accel=paddle_accel+p2_y_vel/5;
        if(paddle_vel_was_neg==true){
            paddle_vel_was_neg=false;
            p2_y_vel*=-1;
        }
        ball_speed_x+=paddle_accel;
        ball_speed_y+=paddle_accel;
        p2_hits++;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel-=ball_speed_x;
        ball_y_vel-=ball_speed_y;
        ball_x=SCREEN_WIDTH-20-PADDLE_WIDTH-BALL_WIDTH-1;
        ball_x+=ball_x_vel;
        ball_y+=ball_y_vel;
        return true;
    }
    return false;
}

bool wall_check(){
    if(ball_y<0 && ball_x_vel<0){
        Mix_PlayChannel(-1,beep2,0);
        ball_speed_x-=wall_accel;
        ball_speed_y-=wall_accel;
        ball_y=0;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel-=ball_speed_x;
        ball_y_vel+=ball_speed_y;
        return true;
    }
    if(ball_y<0 && ball_x_vel>0){
        Mix_PlayChannel(-1,beep2,0);
        ball_speed_x-=wall_accel;
        ball_speed_y-=wall_accel;
        ball_y=0;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel+=ball_speed_x;
        ball_y_vel+=ball_speed_y;
        return true;
    }
    if(ball_y+BALL_HEIGHT>SCREEN_HEIGHT && ball_x_vel<0){
        Mix_PlayChannel(-1,beep2,0);
        ball_speed_x-=wall_accel;
        ball_speed_y-=wall_accel;
        ball_y=SCREEN_HEIGHT-BALL_HEIGHT;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel-=ball_speed_x;
        ball_y_vel-=ball_speed_y;
        return true;
    }
    if(ball_y+BALL_HEIGHT>SCREEN_HEIGHT && ball_x_vel>0){
        Mix_PlayChannel(-1,beep2,0);
        ball_speed_x-=wall_accel;
        ball_speed_y-=wall_accel;
        ball_y=SCREEN_HEIGHT-BALL_HEIGHT;
        ball_x_vel=0;
        ball_y_vel=0;
        ball_x_vel+=ball_speed_x;
        ball_y_vel-=ball_speed_y;
        return true;
    }
    return false;
}

void set_accel(){
    paddle_accel=3;
    wall_accel=1;
}

bool score_check(){
    if(ball_x+BALL_WIDTH<0){
        Mix_PlayChannel(-1,score,0);
        p2_score++;
        p1_misses++;
        reset_ball();
        return true;
    }
    if(ball_x>SCREEN_WIDTH){
        Mix_PlayChannel(-1,score,0);
        p1_score++;
        p2_misses++;
        reset_ball();
        return true;
    }
    return false;
}

void demo_ai_move();
void ai_move();

void move_ball(){
    set_accel();
    int temp_x=0;
    int temp_y=0;
    while(temp_x!=ball_x_vel && temp_y!=ball_y_vel){
        if(singleplayer==true && ball_x_vel>0)
            ai_move();
        if(demo==true && ball_x_vel<0)
            demo_ai_move();
        if(ball_x_vel<0)
            ball_x--;
        if(ball_x_vel>0)
            ball_x++;
        if(ball_y_vel<0)
            ball_y--;
        if(ball_y_vel>0)
            ball_y++;
        if(paddle_check()==true)
            break;
        if(wall_check()==true)
            break;
        if(score_check()==true)
            break;
        if(ball_x_vel<0)
            temp_x--;
        if(ball_x_vel>0)
            temp_x++;
        if(ball_y_vel<0)
            temp_y--;
        if(ball_y_vel>0)
            temp_y++;
        }
    if(ball_speed_x+ball_speed_y>highest_ball_speed)
        highest_ball_speed=ball_speed_x+ball_speed_y;
}

#endif
