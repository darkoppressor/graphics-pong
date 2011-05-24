#ifndef ai_h
#define ai_h

using namespace std;

void ai_move_properly(){
    if(p2_y>ball_y+BALL_HEIGHT)
        p2_y_vel-=PADDLE_HEIGHT/8;
    if(p2_y+PADDLE_HEIGHT<ball_y)
        p2_y_vel+=PADDLE_HEIGHT/8;
    if(ball_y>=p2_y && ball_y<=p2_y+PADDLE_HEIGHT)
        p2_y_vel=0;
}

void ai_move_perfectly(){
    if(ball_y_vel<0)
        p2_y=ball_y-1;
    if(ball_y_vel>0)
        p2_y=ball_y+1;
}

void ai_move(){
    int x;
    switch(difficulty){
        case 0:
        x=random_range(1,100);
        if(x>=1 && x<=10)
            ai_move_properly();
        break;
        case 1:
        x=random_range(1,100);
        if(x>=1 && x<=15)
            ai_move_properly();
        break;
        case 2:
        x=random_range(1,100);
        if(x>=1 && x<=30)
            ai_move_properly();
        break;
        case 3:
        ai_move_perfectly();
        break;
    }
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
