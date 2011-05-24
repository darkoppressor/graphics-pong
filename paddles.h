/* Copyright (c) 2011 Kevin Wells */
/* Graphics Pong may be freely redistributed.  See license for details. */

#ifndef paddles_h
#define paddles_h

using namespace std;

void move_p1(){
    if(p1_y_vel>20)
        p1_y_vel=20;
    if(p1_y_vel<-20)
        p1_y_vel=-20;
    p1_y+=p1_y_vel;
    if(p1_y<0){
        p1_y=0;
        p1_y_vel=0;
    }
    if(p1_y+PADDLE_HEIGHT>SCREEN_HEIGHT){
        p1_y=SCREEN_HEIGHT-PADDLE_HEIGHT;
        p1_y_vel=0;
    }
}

void move_p2(){
    if(p2_y_vel>20)
        p2_y_vel=20;
    if(p2_y_vel<-20)
        p2_y_vel=-20;
    p2_y+=p2_y_vel;
    if(p2_y<0){
        p2_y=0;
        p2_y_vel=0;
    }
    if(p2_y+PADDLE_HEIGHT>SCREEN_HEIGHT){
        p2_y=SCREEN_HEIGHT-PADDLE_HEIGHT;
        p2_y_vel=0;
    }
}

#endif
