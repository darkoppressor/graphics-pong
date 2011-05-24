/* Copyright (c) 2011 Kevin Wells */
/* Graphics Pong may be freely redistributed.  See license for details. */

#ifndef demo_h
#define demo_h

using namespace std;

/**Checks to see if there is any input(ch!=ERR) and if demo mode is on. If these are true, turn off demo mode and return to the main menu.*/
void demo_return_to_menu(){
    if(demo==true){
        demo=false;
        main_menu();
    }
}

void demo_ai_move_properly(){
    if(p1_y>ball_y+BALL_HEIGHT)
        p1_y_vel-=PADDLE_HEIGHT/8;
    if(p1_y+PADDLE_HEIGHT<ball_y)
        p1_y_vel+=PADDLE_HEIGHT/8;
    if(ball_y>=p1_y && ball_y<=p1_y+PADDLE_HEIGHT)
        p1_y_vel=0;
}

void demo_ai_move_perfectly(){
    if(ball_y_vel<0)
        p1_y=ball_y-1;
    if(ball_y_vel>0)
        p1_y=ball_y+1;
}

void demo_ai_move(){
    int x;
    switch(difficulty){
        case 0:
        x=random_range(1,100);
        if(x>=1 && x<=10)
            demo_ai_move_properly();
        break;
        case 1:
        x=random_range(1,100);
        if(x>=1 && x<=15)
            demo_ai_move_properly();
        break;
        case 2:
        x=random_range(1,100);
        if(x>=1 && x<=30)
            demo_ai_move_properly();
        break;
        case 3:
        demo_ai_move_perfectly();
        break;
    }
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

#endif
