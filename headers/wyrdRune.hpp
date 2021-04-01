#ifndef WYRDRUNE_HPP
#define WYRDRUNE_HPP

#include <SFML/Graphics.hpp>
#include "singleRune.hpp"

class WyrdRune{

    public:
        WyrdRune();
        void move();
        position getPosition();
        sf::RectangleShape getRune();
        void setStatus(int status);
        int getStatus();
        int getSelected();
    private:
        position pos;
        sf::RectangleShape rune;
        sf::Texture singleRuneTexture;
        int status=0;
        int rotation;
        int top;
        int left;
        int selected;
        int move_x;
        int move_y;
};

#endif