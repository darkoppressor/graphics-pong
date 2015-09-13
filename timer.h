/* Copyright (c) 2011 Kevin Wells */
/* Graphics Pong may be freely redistributed.  See license for details. */

#ifndef timer_h
#define timer_h

using namespace std;

void timer_advance(){
    timer++;
    if(timer==25){
        timer=0;
        timer_seconds++;
    }
    if(timer_seconds>59){
        timer_seconds=0;
        timer_minutes++;
    }
}

class Timer{
    private:
    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;
    public:
    Timer();
    void start();
    void stop();
    void pause();
    void unpause();
    int get_ticks();
    bool is_started();
    bool is_paused();
};

Timer::Timer(){
    startTicks=0;
    pausedTicks=0;
    paused=false;
    started=false;
}

void Timer::start(){
    started=true;
    paused=false;
    startTicks=SDL_GetTicks();
}

void Timer::stop(){
    started=false;
    paused=false;
}

int Timer::get_ticks(){
    if(started==true){
        if(paused==true){
            return pausedTicks;
        }
        else{
            return SDL_GetTicks()-startTicks;
        }
    }
    return 0;
}

void Timer::pause(){
    if(started==true && paused==false){
        paused=true;
        pausedTicks=SDL_GetTicks()-startTicks;
    }
}

void Timer::unpause(){
    if(paused==true){
        paused=false;
        startTicks=SDL_GetTicks()-pausedTicks;
        pausedTicks=0;
    }
}

bool Timer::is_started(){
    return started;
}

bool Timer::is_paused(){
    return paused;
}

#endif
