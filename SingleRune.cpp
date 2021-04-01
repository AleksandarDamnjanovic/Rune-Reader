#include "headers/singleRune.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <string.h>

SingleRune::SingleRune(int start_x, int start_y, int left_limit){

    SingleRune::rune=sf::RectangleShape(sf::Vector2f(80,130));

    pos.x=start_x;
    pos.y=start_y;

    left=left_limit;

    status=0;
    rev=0;
    rotated=false;

    time_t t;
    srand((unsigned)time(&t));
    int ff=rand()%24;
    ff++;
    SingleRune::selected=ff;
    rev=rand()%2;

    int num=1;
    if(ff>9)
        num=2;

    char buf[num];
    sprintf(buf,"%d",ff);

    char buf2[10+num];

    strcpy(buf2,"front/");
    strcat(buf2,buf);
    strcat(buf2,".png");

    singleRuneTexture.loadFromFile(buf2);
    rune.setTexture(&singleRuneTexture);
    rune.setPosition(getPosition().x,getPosition().y);

    rune.setOrigin(40,65);
    status=STATUS_INITIALIZED;
}

int SingleRune::getSelected(){
    return selected;
}

sf::RectangleShape SingleRune::getRune(){
    return rune;
}

void SingleRune::setPosition(int x, int y){
    pos.x=x;
    pos.y=y;
    rune.setPosition(x,y);

    if(pos.x>left && status==STATUS_INITIALIZED){
        status=STATUS_FIXED;
        if(getReverse() && !rotated){
            rune.rotate(180);
            rotated=!rotated;
        }     
    }

    if(pos.x>1200 && status==STATUS_FINALIZING)
        status=STATUS_DONE;
        
}

position SingleRune::getPosition(){
    return pos;
}

void SingleRune::setStatus(int stat){
    status=stat;
}

int SingleRune::getStatus(){
    return status;
}

bool SingleRune::getReverse(){
    if(rev==0)
        return false;
    else
        return true;
}