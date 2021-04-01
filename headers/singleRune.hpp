#ifndef SINGLERUNE_HPP
#define SINGLERUNE_HPP

#include <SFML/Graphics.hpp>

const int STATUS_INITIALIZED=0;
const int STATUS_FIXED=1;
const int STATUS_FINALIZING=2;
const int STATUS_DONE=3;

struct position{
    int x;
    int y;
};

class SingleRune{

    public:
        SingleRune(int start_x, int start_y, int left_limit);
        void setPosition(int x, int y);
        position getPosition();
        sf::RectangleShape getRune();
        void setStatus(int status);
        int getStatus();
        bool getReverse();
        int getSelected();
    private:
        position pos;
        sf::RectangleShape rune;
        sf::Texture singleRuneTexture;
        int status=0;
        int rev=0;
        bool rotated=false;
        int left;
        int selected;
};

#endif