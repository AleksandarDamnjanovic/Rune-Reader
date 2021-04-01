#include "headers/wyrdRune.hpp"
#include "headers/singleRune.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <string.h>

WyrdRune::WyrdRune(){

    WyrdRune::rune=sf::RectangleShape(sf::Vector2f(80,130));

    pos.x=0;
    pos.y=0;
    status=0;

    time_t t;
    srand((unsigned)time(&t));
    int ff=rand()%24;
    ff++;
    WyrdRune::selected=ff;
    
    left=rand()%750;
    if(left<150)
        left=150;

    move_x=rand()%50;
    if(move_x<10)
        move_x=10;

    move_y=rand()%50;
    if(move_y<10)
        move_y=10;

    rotation=rand()%25;
    if(rotation<1)
        rotation=1;

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

int WyrdRune::getSelected(){
    return selected;
}

sf::RectangleShape WyrdRune::getRune(){
    return rune;
}

void WyrdRune::move(){
    pos.x+=move_x;
    pos.y+=move_y;
    rune.setPosition(pos.x,pos.y);
    rune.rotate(rotation);

    if(pos.x>left && status==STATUS_INITIALIZED)
        status=STATUS_FIXED; 

    if(pos.x>1200 || pos.y>1200)
        status=STATUS_DONE;
        
}

position WyrdRune::getPosition(){
    return pos;
}

void WyrdRune::setStatus(int stat){
    status=stat;
}

int WyrdRune::getStatus(){
    return status;
}