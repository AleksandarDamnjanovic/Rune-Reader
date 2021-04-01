#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include "headers/singleRune.hpp"
#include "headers/wyrdRune.hpp"

int pause=250;
long counter=0;
int scene=0;
const int ENTRY_SCENE=0;
const int INFO_SCENE=1;
const int SELECTION_SCENE=2;
const int SINGLE_RUNE_SCENE=3;
const int DOUBLE_RUNE_SCENE=4;
const int NORNS_SCENE=5;
const int SMALL_CROSS_SCENE=6;
const int SEVEN_PATHS_SCENE=7;
const int YGGDRASIL_SCENE=8;
const int WYRD_SCENE=9;

void buttonHover(sf::RectangleShape *rec, sf::Texture *normal, sf::Texture *hover, sf::Window *win);
void buttonExitHandler(sf::RectangleShape *rec, sf::Window *win);
bool hovering(sf::RectangleShape *rec, sf::Window *win);
void changeScene(sf::RectangleShape *rec, sf::Window *win, sf::Event *event, int new_scene);
void backToSelection(sf::RectangleShape *rec, sf::Window *win, sf::Event *event, int new_scene);
void castButtonHandler(sf::RectangleShape *rec, sf::Window *win, sf::Event *event, int curent_scene);
void clearObjects();
void initalizeWyrd();
void initalizeYggdrasil();
void initializeSevenPaths();
void initializeSmallCross();
void initializeNorns();
void initializeDoubleRune();
void renewWyrd(int index);
void renewRune(int index, int start_x, int start_y, int left_limit);

sf::Font font;

sf::RenderWindow window(sf::VideoMode(1000,1000),"Rune Reader", sf::Style::Close);

sf::RectangleShape background(sf::Vector2f(1000.f,1000.f));
sf::RectangleShape loadingCircle(sf::Vector2f(200.f,200.f));

sf::RectangleShape title(sf::Vector2f(400.f,200.f));
sf::RectangleShape start_button(sf::Vector2f(125.f,50.f));
sf::RectangleShape info_button(sf::Vector2f(125.f,50.f));
sf::RectangleShape exit_button(sf::Vector2f(125.f,50.f));

sf::RectangleShape blackPaper(sf::Vector2f(1000.f,1000.f));
sf::RectangleShape back_button(sf::Vector2f(125.f,50.f));

sf::RectangleShape single_rune_button(sf::Vector2f(220.f,50.f));
sf::RectangleShape double_rune_button(sf::Vector2f(220.f,50.f));
sf::RectangleShape norns_button(sf::Vector2f(140.f,50.f));
sf::RectangleShape small_cross_button(sf::Vector2f(220.f,50.f));
sf::RectangleShape seven_paths_button(sf::Vector2f(220.f,50.f));
sf::RectangleShape yggdrasil_button(sf::Vector2f(160.f,50.f));
sf::RectangleShape wyrd_button(sf::Vector2f(120.f,50.f));
sf::RectangleShape back_from_selection_button(sf::Vector2f(120.f,50.f));

sf::RectangleShape cast_button(sf::Vector2f(120.f,50.f));
sf::RectangleShape back_from_reading_button(sf::Vector2f(120.f,50.f));

SingleRune *SR[9];
WyrdRune *WR[9];

bool toClear=false;

int main(int argc, char** argv){

    window.setFramerateLimit(30);
    font.loadFromFile("support/SyneMono-Regular.ttf");

    blackPaper.setFillColor(sf::Color::Black);
    sf::Image icon;
    icon.loadFromFile("support/icon.png");
    window.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

    sf::Text bottomText;
    bottomText.setFont(font);
    bottomText.setCharacterSize(20);
    bottomText.setFillColor(sf::Color::White);
    bottomText.setStyle(sf::Text::Italic);
    bottomText.setPosition(150,950);
    bottomText.setString("Rune Reader is free and open source software. It's published under\n \
    Apache-2.0 License. Author: Aleksandar Damnjanovic.");

    sf::Text infoTitle;
    infoTitle.setFont(font);
    infoTitle.setCharacterSize(50);
    infoTitle.setFillColor(sf::Color::White);
    infoTitle.setStyle(sf::Text::Bold);
    infoTitle.setPosition(370,100);
    infoTitle.setString("Info Page");

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(100,175);
    infoText.setString("\tRUNE READER PROVIDES USER WITH THE WAY TO CAST RUNES.\n\
    THIS SOFTWARE CAN'T BE USED TO INTERPRET MEANING OF RUNES.\n\
    SOFTWARE AUTHOR WILL HOLD NO\n\
    RESPONSIBILITY FOR ANY EFFECTS OF CASTING OR INTERPRETATION OF RUNES.\n\n\
    This software gives its users ability to cast runes in varieties\n\
    of ways.\n\
    You can cast single rune, double rune, norns, small cross, \n\
    seven paths, yggdrasil and wyrd.\n\
    Those are the most popular ways rune readers use to ask for\n\
    answers through this noble method.\n\
    For more infromations, please, check README");

    DIR *dir;
    dir=opendir("background/");
    dirent *file;
    int num=0;
    while((file=readdir(dir))!=NULL){
        if(strcmp(file->d_name,".")!=0 && strcmp(file->d_name,"..")!=0)
            num++;
    }

    closedir(dir);
    opendir("background/");

    time_t t;
    srand((unsigned)time(&t));
    int ff=rand()%num;
    num=0;

    char *bn;
    while((file=readdir(dir))!=NULL){

        if(strcmp(file->d_name,".")!=0 && strcmp(file->d_name,"..")!=0){
            if(num==ff){
                bn=file->d_name;
                goto exit;
            }
        
            num++;
        }

    }
    exit:

    char path[strlen(bn)+11];
    strcpy(path,"background/");
    strcat(path,bn);
        
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile(path);
    background.setTexture(&backgroundTexture);

    /*Elements of ENTRY SCENE*/

    sf::Texture titleTexture;
    titleTexture.loadFromFile("support/title.png");
    title.setTexture(&titleTexture);
    title.setPosition(300,100);

    sf::Texture loadingCircleTexture;
    loadingCircleTexture.loadFromFile("support/loading.png");
    loadingCircle.setTexture(&loadingCircleTexture);
    loadingCircle.setPosition(80,80);
    loadingCircle.setOrigin(100,100);

    sf::Texture startButtonTexture;
    startButtonTexture.loadFromFile("buttons/start_button.png");
    sf::Texture startButtonTexture_hover;
    startButtonTexture_hover.loadFromFile("buttons/start_button_hover.png");
    start_button.setTexture(&startButtonTexture);
    start_button.setPosition(425,325);

    sf::Texture infoButtonTexture;
    infoButtonTexture.loadFromFile("buttons/info_button.png");
    sf::Texture infoButtonTexture_hover;
    infoButtonTexture_hover.loadFromFile("buttons/info_button_hover.png");
    info_button.setTexture(&infoButtonTexture);
    info_button.setPosition(425,400);

    sf::Texture exitButtonTexture;
    exitButtonTexture.loadFromFile("buttons/exit_button.png");
    sf::Texture exitButtonTexture_hover;
    exitButtonTexture_hover.loadFromFile("buttons/exit_button_hover.png");
    exit_button.setTexture(&exitButtonTexture);
    exit_button.setPosition(425,475);

    /*Elements of INFO SCENE*/

    sf::Texture backButtonTexture;
    backButtonTexture.loadFromFile("buttons/back_button.png");
    sf::Texture backButtonTexture_hover;
    backButtonTexture_hover.loadFromFile("buttons/back_button_hover.png");
    back_button.setTexture(&backButtonTexture);
    back_button.setPosition(425,500);

    /*Elements of SELECTION SCENE*/

    sf::Texture singleRuneButtonTexture;
    singleRuneButtonTexture.loadFromFile("buttons/single_rune_button.png");
    sf::Texture singleRuneButtonTexture_hover;
    singleRuneButtonTexture_hover.loadFromFile("buttons/single_rune_button_hover.png");
    single_rune_button.setTexture(&singleRuneButtonTexture);
    single_rune_button.setPosition(380, 130);

    sf::Texture doubleRuneButtonTexture;
    doubleRuneButtonTexture.loadFromFile("buttons/double_rune_button.png");
    sf::Texture doubleRuneButtonTexture_hover;
    doubleRuneButtonTexture_hover.loadFromFile("buttons/double_rune_button_hover.png");
    double_rune_button.setTexture(&doubleRuneButtonTexture);
    double_rune_button.setPosition(380,200);

    sf::Texture nornsButtonTexture;
    nornsButtonTexture.loadFromFile("buttons/norns_button.png");
    sf::Texture nornsButtonTexture_hover;
    nornsButtonTexture_hover.loadFromFile("buttons/norns_button_hover.png");
    norns_button.setTexture(&nornsButtonTexture);
    norns_button.setPosition(420,270);

    sf::Texture smallCrossButtonTexture;
    smallCrossButtonTexture.loadFromFile("buttons/small_cross_button.png");
    sf::Texture smallCrossButtonTexture_hover;
    smallCrossButtonTexture_hover.loadFromFile("buttons/small_cross_button_hover.png");
    small_cross_button.setTexture(&smallCrossButtonTexture);
    small_cross_button.setPosition(380,340);

    sf::Texture sevenPathsButtonTexture;
    sevenPathsButtonTexture.loadFromFile("buttons/seven_paths_button.png");
    sf::Texture sevenPathsButtonTexture_hover;
    sevenPathsButtonTexture_hover.loadFromFile("buttons/seven_paths_button_hover.png");
    seven_paths_button.setTexture(&sevenPathsButtonTexture);
    seven_paths_button.setPosition(380,410);

    sf::Texture yggdrasilButtonTexture;
    yggdrasilButtonTexture.loadFromFile("buttons/yggdrasil_button.png");
    sf::Texture yggdrasilButtonTexture_hover;
    yggdrasilButtonTexture_hover.loadFromFile("buttons/yggdrasil_button_hover.png");
    yggdrasil_button.setTexture(&yggdrasilButtonTexture);
    yggdrasil_button.setPosition(410,480);

    sf::Texture wyrdButtonTexture;
    wyrdButtonTexture.loadFromFile("buttons/wyrd_button.png");
    sf::Texture wyrdButtonTexture_hover;
    wyrdButtonTexture_hover.loadFromFile("buttons/wyrd_button_hover.png");
    wyrd_button.setTexture(&wyrdButtonTexture);
    wyrd_button.setPosition(430,550);

    sf::Texture backFromSelectionButtonTexture;
    backFromSelectionButtonTexture.loadFromFile("buttons/back_button.png");
    sf::Texture backFromSelectionButtonTexture_hover;
    backFromSelectionButtonTexture_hover.loadFromFile("buttons/back_button_hover.png");
    back_from_selection_button.setTexture(&backFromSelectionButtonTexture);
    back_from_selection_button.setPosition(430,620);

    /*Elements of CASTING SCENE*/

    sf::Texture castButtonTexture;
    castButtonTexture.loadFromFile("buttons/cast_button.png");
    sf::Texture castButtonTexture_hover;
    castButtonTexture_hover.loadFromFile("buttons/cast_button_hover.png");
    cast_button.setTexture(&castButtonTexture);
    cast_button.setPosition(350,900);

    sf::Texture backFromReadingButtonTexture;
    backFromReadingButtonTexture.loadFromFile("buttons/back_button.png");
    sf::Texture backFromReadingButtonTexture_hover;
    backFromReadingButtonTexture_hover.loadFromFile("buttons/back_button_hover.png");
    back_from_reading_button.setTexture(&backFromReadingButtonTexture);
    back_from_reading_button.setPosition(530,900);


    /*****************************/

    while(window.isOpen()){
        counter++;
        loadingCircle.rotate(1);

        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                break;
            }
        }

        window.clear();

        switch (scene){
            
            case ENTRY_SCENE:

            window.draw(background);

            buttonHover(&start_button,&startButtonTexture,&startButtonTexture_hover,&window);
            buttonHover(&info_button,&infoButtonTexture,&infoButtonTexture_hover,&window);
            buttonHover(&exit_button,&exitButtonTexture,&exitButtonTexture_hover,&window);

            if(counter>45){
              buttonExitHandler(&exit_button,&window);
                changeScene(&start_button, &window, &event, SELECTION_SCENE);
                changeScene(&info_button, &window, &event, INFO_SCENE);  
            }

            window.draw(title);
            window.draw(start_button);
            window.draw(info_button);
            window.draw(exit_button);
            window.draw(bottomText);

            break;

            case INFO_SCENE:

            buttonHover(&back_button,&backButtonTexture,&backButtonTexture_hover,&window);
            
            if(counter>30)
                changeScene(&back_button,&window, &event, ENTRY_SCENE);

            window.draw(blackPaper);
            window.draw(infoTitle);
            window.draw(infoText);
            window.draw(back_button);
            window.draw(bottomText);

            break;

            case SELECTION_SCENE:

            if(toClear)
                clearObjects();

            window.draw(background);

            buttonHover(&single_rune_button, &singleRuneButtonTexture, 
            &singleRuneButtonTexture_hover,&window);
            buttonHover(&double_rune_button, &doubleRuneButtonTexture, 
            &doubleRuneButtonTexture_hover,&window);
            buttonHover(&norns_button, &nornsButtonTexture, 
            &nornsButtonTexture_hover,&window);
            buttonHover(&small_cross_button, &smallCrossButtonTexture, 
            &smallCrossButtonTexture_hover,&window);
            buttonHover(&seven_paths_button, &sevenPathsButtonTexture, 
            &sevenPathsButtonTexture_hover,&window);
            buttonHover(&yggdrasil_button, &yggdrasilButtonTexture, 
            &yggdrasilButtonTexture_hover,&window);
            buttonHover(&wyrd_button, &wyrdButtonTexture, 
            &wyrdButtonTexture_hover,&window);
            buttonHover(&back_from_selection_button, &backFromSelectionButtonTexture, 
            &backFromSelectionButtonTexture_hover,&window);

            if(counter>30){
                changeScene(&single_rune_button,&window, &event, SINGLE_RUNE_SCENE);
                changeScene(&double_rune_button,&window, &event, DOUBLE_RUNE_SCENE);
                changeScene(&norns_button,&window, &event, NORNS_SCENE);
                changeScene(&small_cross_button,&window, &event, SMALL_CROSS_SCENE);
                changeScene(&seven_paths_button,&window, &event, SEVEN_PATHS_SCENE);
                changeScene(&yggdrasil_button,&window, &event, YGGDRASIL_SCENE);
                changeScene(&wyrd_button,&window, &event, WYRD_SCENE);
                changeScene(&back_from_selection_button,&window, &event, ENTRY_SCENE);
            }

            window.draw(single_rune_button);
            window.draw(double_rune_button);
            window.draw(norns_button);
            window.draw(small_cross_button);
            window.draw(seven_paths_button);
            window.draw(yggdrasil_button);
            window.draw(wyrd_button);
            window.draw(back_from_selection_button);
            window.draw(bottomText);

            break;

            case SINGLE_RUNE_SCENE:

                window.draw(background);

                if(SR[0]!=NULL){

                    if(SR[0]->getStatus()==STATUS_INITIALIZED)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[0]->getStatus()==STATUS_FINALIZING)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[0]->getStatus()==STATUS_DONE)
                        SR[0]=new SingleRune(0,425,479);

                    window.draw(SR[0]->getRune());

                }

                buttonHover(&cast_button, &castButtonTexture, 
                &castButtonTexture_hover,&window);
                buttonHover(&back_from_reading_button, &backFromReadingButtonTexture, 
                &backFromReadingButtonTexture_hover,&window);

                if(counter>30){
                    castButtonHandler(&cast_button, &window, &event, SINGLE_RUNE_SCENE);
                    backToSelection(&back_from_reading_button,&window, &event, SELECTION_SCENE);
                }
                
                window.draw(cast_button);
                window.draw(back_from_reading_button);
                window.draw(bottomText);

                if((SR[0]!=NULL && SR[0]->getStatus()!=STATUS_FIXED) || SR[0]==NULL)
                    window.draw(loadingCircle);

            break;

            case DOUBLE_RUNE_SCENE:

                window.draw(background);

                if(SR[0]!=NULL && SR[1]!=NULL){

                    if(SR[0]->getStatus()==STATUS_INITIALIZED)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[0]->getStatus()==STATUS_FINALIZING)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[1]->getStatus()==STATUS_INITIALIZED)
                        SR[1]->setPosition(SR[1]->getPosition().x+25,425);

                    if(SR[1]->getStatus()==STATUS_FINALIZING)
                        SR[1]->setPosition(SR[1]->getPosition().x+25,425);

                    if(SR[0]->getStatus()==STATUS_DONE && SR[1]->getStatus()==STATUS_DONE){
                        clearObjects();
                        initializeDoubleRune();
                    }

                    window.draw(SR[0]->getRune());
                    window.draw(SR[1]->getRune());

                }

                buttonHover(&cast_button, &castButtonTexture, 
                &castButtonTexture_hover,&window);
                buttonHover(&back_from_reading_button, &backFromReadingButtonTexture, 
                &backFromReadingButtonTexture_hover,&window);

                if(counter>30){
                    castButtonHandler(&cast_button, &window, &event, DOUBLE_RUNE_SCENE);
                    backToSelection(&back_from_reading_button,&window, &event, SELECTION_SCENE);
                }
                
                window.draw(cast_button);
                window.draw(back_from_reading_button);
                window.draw(bottomText);

                if((SR[0]!=NULL && SR[0]->getStatus()!=STATUS_FIXED) || SR[0]==NULL)
                    window.draw(loadingCircle);

            break;

            case NORNS_SCENE:

                window.draw(background);

                if(SR[0]!=NULL && SR[1]!=NULL && SR[2]!=NULL){

                    if(SR[0]->getStatus()==STATUS_INITIALIZED)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[0]->getStatus()==STATUS_FINALIZING)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[1]->getStatus()==STATUS_INITIALIZED)
                        SR[1]->setPosition(SR[1]->getPosition().x+25,425);

                    if(SR[1]->getStatus()==STATUS_FINALIZING)
                        SR[1]->setPosition(SR[1]->getPosition().x+25,425);

                    if(SR[2]->getStatus()==STATUS_INITIALIZED)
                        SR[2]->setPosition(SR[2]->getPosition().x+25,425);

                    if(SR[2]->getStatus()==STATUS_FINALIZING)
                        SR[2]->setPosition(SR[2]->getPosition().x+25,425);

                    if(SR[0]->getStatus()==STATUS_DONE && SR[1]->getStatus()==STATUS_DONE
                    && SR[2]->getStatus()==STATUS_DONE){
                        clearObjects();
                        initializeNorns();
                    }

                    for(int i=0;i<3;i++)
                        window.draw(SR[i]->getRune());

                }

                buttonHover(&cast_button, &castButtonTexture, 
                &castButtonTexture_hover,&window);
                buttonHover(&back_from_reading_button, &backFromReadingButtonTexture, 
                &backFromReadingButtonTexture_hover,&window);

                if(counter>30){
                    castButtonHandler(&cast_button, &window, &event, NORNS_SCENE);
                    backToSelection(&back_from_reading_button,&window, &event, SELECTION_SCENE);
                }
                
                window.draw(cast_button);
                window.draw(back_from_reading_button);
                window.draw(bottomText);

                if((SR[0]!=NULL && SR[0]->getStatus()!=STATUS_FIXED) || SR[0]==NULL)
                    window.draw(loadingCircle);

            break;

            case SMALL_CROSS_SCENE:

                window.draw(background);

                if(SR[0]!=NULL && SR[1]!=NULL && SR[2]!=NULL
                && SR[3]!=NULL && SR[4]!=NULL){

                    if(SR[0]->getStatus()==STATUS_INITIALIZED)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[0]->getStatus()==STATUS_FINALIZING)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[1]->getStatus()==STATUS_INITIALIZED)
                        SR[1]->setPosition(SR[1]->getPosition().x+25,425);

                    if(SR[1]->getStatus()==STATUS_FINALIZING)
                        SR[1]->setPosition(SR[1]->getPosition().x+25,425);

                    if(SR[2]->getStatus()==STATUS_INITIALIZED)
                        SR[2]->setPosition(SR[2]->getPosition().x+25,425);

                    if(SR[2]->getStatus()==STATUS_FINALIZING)
                        SR[2]->setPosition(SR[2]->getPosition().x+25,425);

                    if(SR[3]->getStatus()==STATUS_INITIALIZED)
                        SR[3]->setPosition(SR[3]->getPosition().x+25,275);

                    if(SR[3]->getStatus()==STATUS_FINALIZING)
                        SR[3]->setPosition(SR[3]->getPosition().x+25,275);

                    if(SR[4]->getStatus()==STATUS_INITIALIZED)
                        SR[4]->setPosition(SR[4]->getPosition().x+25,575);

                    if(SR[4]->getStatus()==STATUS_FINALIZING)
                        SR[4]->setPosition(SR[4]->getPosition().x+25,575);

                    if(SR[0]->getStatus()==STATUS_DONE && SR[1]->getStatus()==STATUS_DONE
                    && SR[2]->getStatus()==STATUS_DONE && SR[3]->getStatus()==STATUS_DONE
                    && SR[4]->getStatus()==STATUS_DONE){
                        clearObjects();
                        initializeSmallCross();
                    }

                    for(int i=0; i<5;i++)
                        window.draw(SR[i]->getRune());

                }

                buttonHover(&cast_button, &castButtonTexture, 
                &castButtonTexture_hover,&window);
                buttonHover(&back_from_reading_button, &backFromReadingButtonTexture, 
                &backFromReadingButtonTexture_hover,&window);

                if(counter>30){
                    castButtonHandler(&cast_button, &window, &event, SMALL_CROSS_SCENE);
                    backToSelection(&back_from_reading_button,&window, &event, SELECTION_SCENE);
                }
                
                window.draw(cast_button);
                window.draw(back_from_reading_button);
                window.draw(bottomText);

                if((SR[0]!=NULL && SR[0]->getStatus()!=STATUS_FIXED) || SR[0]==NULL)
                    window.draw(loadingCircle);

            break;

            case SEVEN_PATHS_SCENE:

                window.draw(background);

                if(SR[0]!=NULL && SR[1]!=NULL && SR[2]!=NULL
                && SR[3]!=NULL && SR[4]!=NULL
                && SR[5]!=NULL && SR[6]!=NULL){

                    if(SR[0]->getStatus()==STATUS_INITIALIZED)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[0]->getStatus()==STATUS_FINALIZING)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[1]->getStatus()==STATUS_INITIALIZED)
                        SR[1]->setPosition(SR[1]->getPosition().x+25,425);

                    if(SR[1]->getStatus()==STATUS_FINALIZING)
                        SR[1]->setPosition(SR[1]->getPosition().x+25,425);

                    if(SR[2]->getStatus()==STATUS_INITIALIZED)
                        SR[2]->setPosition(SR[2]->getPosition().x+25,425);

                    if(SR[2]->getStatus()==STATUS_FINALIZING)
                        SR[2]->setPosition(SR[2]->getPosition().x+25,425);

                    if(SR[3]->getStatus()==STATUS_INITIALIZED)
                        SR[3]->setPosition(SR[3]->getPosition().x+25,425);

                    if(SR[3]->getStatus()==STATUS_FINALIZING)
                        SR[3]->setPosition(SR[3]->getPosition().x+25,425);

                    if(SR[4]->getStatus()==STATUS_INITIALIZED)
                        SR[4]->setPosition(SR[4]->getPosition().x+25,425);

                    if(SR[4]->getStatus()==STATUS_FINALIZING)
                        SR[4]->setPosition(SR[4]->getPosition().x+25,425);

                    if(SR[5]->getStatus()==STATUS_INITIALIZED)
                        SR[5]->setPosition(SR[5]->getPosition().x+25,425);

                    if(SR[5]->getStatus()==STATUS_FINALIZING)
                        SR[5]->setPosition(SR[5]->getPosition().x+25,425);

                    if(SR[6]->getStatus()==STATUS_INITIALIZED)
                        SR[6]->setPosition(SR[6]->getPosition().x+25,605);

                    if(SR[6]->getStatus()==STATUS_FINALIZING)
                        SR[6]->setPosition(SR[6]->getPosition().x+25,605);

                    if(SR[0]->getStatus()==STATUS_DONE && SR[1]->getStatus()==STATUS_DONE
                    && SR[2]->getStatus()==STATUS_DONE && SR[3]->getStatus()==STATUS_DONE
                    && SR[4]->getStatus()==STATUS_DONE && SR[5]->getStatus()==STATUS_DONE
                    && SR[6]->getStatus()==STATUS_DONE){
                        clearObjects();
                        initializeSevenPaths();
                    }

                    for(int i=0;i<7;i++)
                        window.draw(SR[i]->getRune());

                }

                buttonHover(&cast_button, &castButtonTexture, 
                &castButtonTexture_hover,&window);
                buttonHover(&back_from_reading_button, &backFromReadingButtonTexture, 
                &backFromReadingButtonTexture_hover,&window);

                if(counter>30){
                    castButtonHandler(&cast_button, &window, &event, SEVEN_PATHS_SCENE);
                    backToSelection(&back_from_reading_button,&window, &event, SELECTION_SCENE);
                }
                
                window.draw(cast_button);
                window.draw(back_from_reading_button);
                window.draw(bottomText);

                if((SR[0]!=NULL && SR[0]->getStatus()!=STATUS_FIXED) || SR[0]==NULL)
                    window.draw(loadingCircle);

            break;

            case YGGDRASIL_SCENE:

                window.draw(background);

                if(SR[1]!=NULL && SR[2]!=NULL && SR[3]!=NULL
                && SR[4]!=NULL && SR[5]!=NULL
                && SR[6]!=NULL && SR[7]!=NULL
                && SR[8]!=NULL && SR[0]!=NULL){

                    if(SR[0]->getStatus()==STATUS_INITIALIZED)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[0]->getStatus()==STATUS_FINALIZING)
                        SR[0]->setPosition(SR[0]->getPosition().x+25,425);

                    if(SR[1]->getStatus()==STATUS_INITIALIZED)
                        SR[1]->setPosition(SR[1]->getPosition().x+25,275);

                    if(SR[1]->getStatus()==STATUS_FINALIZING)
                        SR[1]->setPosition(SR[1]->getPosition().x+25,275);

                    if(SR[2]->getStatus()==STATUS_INITIALIZED)
                        SR[2]->setPosition(SR[2]->getPosition().x+25,579);

                    if(SR[2]->getStatus()==STATUS_FINALIZING)
                        SR[2]->setPosition(SR[2]->getPosition().x+25,579);

                    if(SR[3]->getStatus()==STATUS_INITIALIZED)
                        SR[3]->setPosition(SR[3]->getPosition().x+25,325);

                    if(SR[3]->getStatus()==STATUS_FINALIZING)
                        SR[3]->setPosition(SR[3]->getPosition().x+25,325);

                    if(SR[4]->getStatus()==STATUS_INITIALIZED)
                        SR[4]->setPosition(SR[4]->getPosition().x+25,525);

                    if(SR[4]->getStatus()==STATUS_FINALIZING)
                        SR[4]->setPosition(SR[4]->getPosition().x+25,525);

                    if(SR[5]->getStatus()==STATUS_INITIALIZED)
                        SR[5]->setPosition(SR[5]->getPosition().x+25,525);

                    if(SR[5]->getStatus()==STATUS_FINALIZING)
                        SR[5]->setPosition(SR[5]->getPosition().x+25,525);

                    if(SR[6]->getStatus()==STATUS_INITIALIZED)
                        SR[6]->setPosition(SR[6]->getPosition().x+25,325);

                    if(SR[6]->getStatus()==STATUS_FINALIZING)
                        SR[6]->setPosition(SR[6]->getPosition().x+25,325);

                    if(SR[7]->getStatus()==STATUS_INITIALIZED)
                        SR[7]->setPosition(SR[7]->getPosition().x+25,125);

                    if(SR[7]->getStatus()==STATUS_FINALIZING)
                        SR[7]->setPosition(SR[7]->getPosition().x+25,125);

                    if(SR[8]->getStatus()==STATUS_INITIALIZED)
                        SR[8]->setPosition(SR[8]->getPosition().x+25,725);

                    if(SR[8]->getStatus()==STATUS_FINALIZING)
                        SR[8]->setPosition(SR[8]->getPosition().x+25,725);

                    if(SR[0]->getStatus()==STATUS_DONE && SR[1]->getStatus()==STATUS_DONE
                    && SR[2]->getStatus()==STATUS_DONE && SR[3]->getStatus()==STATUS_DONE
                    && SR[4]->getStatus()==STATUS_DONE && SR[5]->getStatus()==STATUS_DONE
                    && SR[6]->getStatus()==STATUS_DONE && SR[7]->getStatus()==STATUS_DONE
                    && SR[8]->getStatus()==STATUS_DONE){
                        clearObjects();
                        initalizeYggdrasil();
                    }

                    for(int i=0;i<9;i++)
                        window.draw(SR[i]->getRune());

                }

                buttonHover(&cast_button, &castButtonTexture, 
                &castButtonTexture_hover,&window);
                buttonHover(&back_from_reading_button, &backFromReadingButtonTexture, 
                &backFromReadingButtonTexture_hover,&window);

                if(counter>30){
                    castButtonHandler(&cast_button, &window, &event, YGGDRASIL_SCENE);
                    backToSelection(&back_from_reading_button,&window, &event, SELECTION_SCENE);
                }
                
                window.draw(cast_button);
                window.draw(back_from_reading_button);
                window.draw(bottomText);

                if((SR[0]!=NULL && SR[0]->getStatus()!=STATUS_FIXED) || SR[0]==NULL)
                    window.draw(loadingCircle);

            break;

            case WYRD_SCENE:

                window.draw(background);

                if(WR[0]!=NULL && WR[1]!=NULL && WR[2]!=NULL
                && WR[3]!=NULL && WR[4]!=NULL
                && WR[5]!=NULL && WR[6]!=NULL
                && WR[7]!=NULL && WR[8]!=NULL){

                    for(int i=0;i<9;i++)
                        if(WR[i]->getStatus()==STATUS_INITIALIZED)
                            WR[i]->move();

                    for(int i=0;i<9;i++)
                        if(WR[i]->getStatus()==STATUS_FINALIZING)
                            WR[i]->move();

                    if(WR[0]->getStatus()==STATUS_DONE && WR[1]->getStatus()==STATUS_DONE
                    && WR[2]->getStatus()==STATUS_DONE && WR[3]->getStatus()==STATUS_DONE
                    && WR[4]->getStatus()==STATUS_DONE && WR[5]->getStatus()==STATUS_DONE
                    && WR[6]->getStatus()==STATUS_DONE && WR[7]->getStatus()==STATUS_DONE
                    && WR[8]->getStatus()==STATUS_DONE){
                        clearObjects();
                        initalizeWyrd();
                    }
                    
                    for(int i=0;i<9;i++)
                        window.draw(WR[i]->getRune());

                }

                buttonHover(&cast_button, &castButtonTexture, 
                &castButtonTexture_hover,&window);
                buttonHover(&back_from_reading_button, &backFromReadingButtonTexture, 
                &backFromReadingButtonTexture_hover,&window);

                if(counter>30){
                    castButtonHandler(&cast_button, &window, &event, WYRD_SCENE);
                    backToSelection(&back_from_reading_button,&window, &event, SELECTION_SCENE);
                }
                
                window.draw(cast_button);
                window.draw(back_from_reading_button);
                window.draw(bottomText);

                if((WR[0]!=NULL && WR[0]->getStatus()!=STATUS_FIXED) || WR[0]==NULL)
                    window.draw(loadingCircle);

            break;

        }

        window.display();

    }

    return 0;
}

void buttonHover(sf::RectangleShape *rec, sf::Texture *normal, sf::Texture *hover, sf::Window *win){
    if(hovering(rec,win)){
        rec->setTexture(hover);
        rec->setScale(1.05,1.05);
    }else{
        rec->setTexture(normal);
        rec->setScale(1,1);
    }
}

void buttonExitHandler(sf::RectangleShape *rec, sf::Window *win){
    if(hovering(rec,win))
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            if(scene==ENTRY_SCENE)
                win->close();
}

bool hovering(sf::RectangleShape *rec, sf::Window *win){
    int x=sf::Mouse::getPosition().x;
    int y=sf::Mouse::getPosition().y;
    int x1=rec->getPosition().x + win->getPosition().x;
    int y1=rec->getPosition().y + win->getPosition().y+25;
    int x2=rec->getSize().x;
    int y2=rec->getSize().y;

    if(x>x1 && x<x1+x2 && y>y1 && y<y1+y2)
        return true;
    else
        return false;
}

void changeScene(sf::RectangleShape *rec, sf::Window *win, sf::Event *event, int new_scene){
    if(hovering(rec,win))
        if(event->mouseButton.button==sf::Mouse::Left)
            if(event->type==sf::Event::MouseButtonReleased){
                scene=new_scene;
                counter=0;
            }
}

void castButtonHandler(sf::RectangleShape *rec, sf::Window *win, sf::Event *event, int curent_scene){
    if(hovering(rec,win))
        if(event->mouseButton.button==sf::Mouse::Left)
            if(event->type==sf::Event::MouseButtonPressed){
                switch (curent_scene){
                    case SINGLE_RUNE_SCENE:

                        if(SR[0]==NULL)
                            SR[0]=new SingleRune(0, 425, 479);

                        if(SR[0]->getStatus()==STATUS_FIXED)
                            SR[0]->setStatus(STATUS_FINALIZING);

                    break;

                    case DOUBLE_RUNE_SCENE:

                        initializeDoubleRune();

                        for(int i=0;i<2;i++)
                            if(SR[i]->getStatus()==STATUS_FIXED)
                                SR[i]->setStatus(STATUS_FINALIZING);

                    break;

                    case NORNS_SCENE:

                        initializeNorns();

                        for(int i=0;i<3;i++)
                            if(SR[i]->getStatus()==STATUS_FIXED)
                                SR[i]->setStatus(STATUS_FINALIZING);

                    break;

                    case SMALL_CROSS_SCENE:

                        initializeSmallCross();

                        for(int i=0;i<5;i++)
                            if(SR[i]->getStatus()==STATUS_FIXED)
                                SR[i]->setStatus(STATUS_FINALIZING);

                    break;

                    case SEVEN_PATHS_SCENE:

                        initializeSevenPaths();

                        for(int i=0;i<7;i++)
                            if(SR[i]->getStatus()==STATUS_FIXED)
                                SR[i]->setStatus(STATUS_FINALIZING);

                    break;

                    case YGGDRASIL_SCENE:

                        initalizeYggdrasil();

                        for(int i=0;i<9;i++)
                            if(SR[i]->getStatus()==STATUS_FIXED)
                                SR[i]->setStatus(STATUS_FINALIZING);

                    break;

                    case WYRD_SCENE:

                        initalizeWyrd();

                        for(int i=0;i<9;i++)
                            if(WR[i]->getStatus()==STATUS_FIXED)
                                WR[i]->setStatus(STATUS_FINALIZING);
                            
                    break;

                }
                counter=0;
            }
}

void clearObjects(){

    for(int i=0;i<9;i++)
        if(SR[i]!=NULL){
            delete SR[i];
            SR[i]=NULL;
        }
            

    for(int i=0;i<9;i++)
        if(WR[i]!=NULL){
            delete WR[i];
            WR[i]=NULL;
        }
            
        
    toClear=false;
}

void backToSelection(sf::RectangleShape *rec, sf::Window *win, sf::Event *event, int new_scene){
    changeScene(&back_from_reading_button,&window, event, SELECTION_SCENE);
    toClear=true;
}

void renewWyrd(int index){
    delete WR[index];
    WR[index]=NULL;
    sf::sleep(sf::milliseconds(pause));
    WR[index]=new WyrdRune();
}

void renewRune(int index, int start_x, int start_y, int left_limit){
    delete SR[index];
    SR[index]=NULL;
    sf::sleep(sf::milliseconds(pause));
    SR[index]=new SingleRune(start_x, start_y, left_limit);
}

void initializeDoubleRune(){

    if(SR[0]==NULL)
        SR[0]=new SingleRune(0, 425, 429);

    if(SR[1]==NULL){
        SR[1]=new SingleRune(0, 425, 529);
        while (SR[1]->getSelected()==SR[0]->getSelected())
            renewRune(1, 0, 425, 529);
    }

}

void initializeNorns(){

    if(SR[0]==NULL)
        SR[0]=new SingleRune(0, 425, 379);

    if(SR[1]==NULL){
        SR[1]=new SingleRune(0, 425, 479);
        while (SR[1]->getSelected()==SR[0]->getSelected())
            renewRune(1, 0, 425, 479);
    }

    if(SR[2]==NULL){
        SR[2]=new SingleRune(0, 425, 579);
        while (SR[2]->getSelected()==SR[0]->getSelected() ||
        SR[2]->getSelected()==SR[1]->getSelected())
            renewRune(2, 0, 425, 579);
    }

}

void initializeSmallCross(){

    if(SR[0]==NULL)
        SR[0]=new SingleRune(0, 425, 379);

    if(SR[1]==NULL){
        SR[1]=new SingleRune(0, 425, 479);
        while (SR[1]->getSelected()==SR[0]->getSelected())
            renewRune(1, 0, 425, 479);
    }

    if(SR[2]==NULL){
        SR[2]=new SingleRune(0, 425, 579);
        while (SR[2]->getSelected()==SR[0]->getSelected() ||
        SR[2]->getSelected()==SR[1]->getSelected())
            renewRune(2, 0, 425, 579);
    }

    if(SR[3]==NULL){
        SR[3]=new SingleRune(0, 275, 479);
        while (SR[3]->getSelected()==SR[0]->getSelected() ||
        SR[3]->getSelected()==SR[1]->getSelected() ||
        SR[3]->getSelected()==SR[2]->getSelected())
            renewRune(3, 0, 275, 479);
    }

    if(SR[4]==NULL){
        SR[4]=new SingleRune(0, 575, 479);
        while (SR[4]->getSelected()==SR[0]->getSelected() ||
        SR[4]->getSelected()==SR[1]->getSelected() ||
        SR[4]->getSelected()==SR[2]->getSelected() ||
        SR[4]->getSelected()==SR[3]->getSelected())
            renewRune(4, 0, 575, 479);
    }

}

void initializeSevenPaths(){

    if(SR[0]==NULL)
        SR[0]=new SingleRune(0, 425, 429);

    if(SR[1]==NULL){
        SR[1]=new SingleRune(0, 425, 529);
        while (SR[1]->getSelected()==SR[0]->getSelected())
            renewRune(1, 0, 425, 529);
    }

    if(SR[2]==NULL){
        SR[2]=new SingleRune(0, 425, 279);
        while (SR[2]->getSelected()==SR[0]->getSelected() ||
        SR[2]->getSelected()==SR[1]->getSelected())
            renewRune(2, 0, 425, 279);
    }

    if(SR[3]==NULL){
        SR[3]=new SingleRune(0, 425, 179);
        while (SR[3]->getSelected()==SR[0]->getSelected() ||
        SR[3]->getSelected()==SR[1]->getSelected() ||
        SR[3]->getSelected()==SR[2]->getSelected())
            renewRune(3, 0, 425, 179);
    }

    if(SR[4]==NULL){
        SR[4]=new SingleRune(0, 425, 679);
        while (SR[4]->getSelected()==SR[0]->getSelected() ||
        SR[4]->getSelected()==SR[1]->getSelected() ||
        SR[4]->getSelected()==SR[2]->getSelected() ||
        SR[4]->getSelected()==SR[3]->getSelected())
            renewRune(4, 0, 425, 679);
    }

    if(SR[5]==NULL){
        SR[5]=new SingleRune(0, 425, 779);
        while (SR[5]->getSelected()==SR[0]->getSelected() ||
        SR[5]->getSelected()==SR[1]->getSelected() ||
        SR[5]->getSelected()==SR[2]->getSelected() ||
        SR[5]->getSelected()==SR[3]->getSelected() ||
        SR[5]->getSelected()==SR[4]->getSelected())
            renewRune(5, 0, 425, 779);
    }

    if(SR[6]==NULL){
        SR[6]=new SingleRune(0, 605, 479);
        while (SR[6]->getSelected()==SR[0]->getSelected() ||
        SR[6]->getSelected()==SR[1]->getSelected() ||
        SR[6]->getSelected()==SR[2]->getSelected() ||
        SR[6]->getSelected()==SR[3]->getSelected() ||
        SR[6]->getSelected()==SR[4]->getSelected() ||
        SR[6]->getSelected()==SR[5]->getSelected())
            renewRune(6, 0, 605, 479);
    }

}

void initalizeYggdrasil(){

    if(SR[0]==NULL)
        SR[0]=new SingleRune(0, 425, 479);

    if(SR[1]==NULL){
        SR[1]=new SingleRune(0, 275, 479);
        while (SR[1]->getSelected()==SR[0]->getSelected())
            renewRune(1, 0, 425, 479);
    }

    if(SR[2]==NULL){
        SR[2]=new SingleRune(0, 575, 479);
        while (SR[2]->getSelected()==SR[0]->getSelected() ||
        SR[2]->getSelected()==SR[1]->getSelected())
            renewRune(2,0,575,479);
    }

    if(SR[3]==NULL){
        SR[3]=new SingleRune(0, 325, 605);
        while (SR[3]->getSelected()==SR[0]->getSelected() ||
        SR[3]->getSelected()==SR[1]->getSelected() ||
        SR[3]->getSelected()==SR[2]->getSelected())
            renewRune(3, 0, 325, 605);
        
    }

    if(SR[4]==NULL){
        SR[4]=new SingleRune(0, 525, 355);
        while (SR[4]->getSelected()==SR[0]->getSelected() ||
        SR[4]->getSelected()==SR[1]->getSelected() ||
        SR[4]->getSelected()==SR[2]->getSelected() ||
        SR[4]->getSelected()==SR[3]->getSelected())
            renewRune(4, 0, 525, 355);
    }

    if(SR[5]==NULL){
        SR[5]=new SingleRune(0, 525, 605);
        while (SR[5]->getSelected()==SR[0]->getSelected() ||
        SR[5]->getSelected()==SR[1]->getSelected() ||
        SR[5]->getSelected()==SR[2]->getSelected() ||
        SR[5]->getSelected()==SR[3]->getSelected() ||
        SR[5]->getSelected()==SR[4]->getSelected())
            renewRune(5, 0, 525, 605);
    }

    if(SR[6]==NULL){
        SR[6]=new SingleRune(0, 325, 355);
        while (SR[6]->getSelected()==SR[0]->getSelected() ||
        SR[6]->getSelected()==SR[1]->getSelected() ||
        SR[6]->getSelected()==SR[2]->getSelected() ||
        SR[6]->getSelected()==SR[3]->getSelected() ||
        SR[6]->getSelected()==SR[4]->getSelected() ||
        SR[6]->getSelected()==SR[5]->getSelected())
            renewRune(6, 0, 325, 355);
    }

    if(SR[7]==NULL){
        SR[7]=new SingleRune(0, 125, 479);
        while (SR[7]->getSelected()==SR[0]->getSelected() ||
        SR[7]->getSelected()==SR[1]->getSelected() ||
        SR[7]->getSelected()==SR[2]->getSelected() ||
        SR[7]->getSelected()==SR[3]->getSelected() ||
        SR[7]->getSelected()==SR[4]->getSelected() ||
        SR[7]->getSelected()==SR[5]->getSelected() ||
        SR[7]->getSelected()==SR[6]->getSelected())
            renewRune(7, 0, 125, 479);
    }

    if(SR[8]==NULL){
        SR[8]=new SingleRune(0, 725, 479);
        while (SR[8]->getSelected()==SR[0]->getSelected() ||
        SR[8]->getSelected()==SR[1]->getSelected() ||
        SR[8]->getSelected()==SR[2]->getSelected() ||
        SR[8]->getSelected()==SR[3]->getSelected() ||
        SR[8]->getSelected()==SR[4]->getSelected() ||
        SR[8]->getSelected()==SR[5]->getSelected() ||
        SR[8]->getSelected()==SR[6]->getSelected() ||
        SR[8]->getSelected()==SR[7]->getSelected()){
            renewRune(8, 0, 725, 479);
        }
    }

}

void initalizeWyrd(){

    if(WR[0]==NULL)
        WR[0]=new WyrdRune();

    if(WR[1]==NULL){
        WR[1]=new WyrdRune();
        while (WR[1]->getSelected()==WR[0]->getSelected())
            renewWyrd(1);
    }

    if(WR[2]==NULL){
        WR[2]=new WyrdRune();
        while (WR[2]->getSelected()==WR[0]->getSelected() ||
        WR[2]->getSelected()==WR[1]->getSelected())
            renewWyrd(2);
    }

    if(WR[3]==NULL){
        WR[3]=new WyrdRune();
        while (WR[3]->getSelected()==WR[0]->getSelected() ||
        WR[3]->getSelected()==WR[1]->getSelected() ||
        WR[3]->getSelected()==WR[2]->getSelected())
            renewWyrd(3);
    }

    if(WR[4]==NULL){
        WR[4]=new WyrdRune();
        while (WR[4]->getSelected()==WR[0]->getSelected() ||
        WR[4]->getSelected()==WR[1]->getSelected() ||
        WR[4]->getSelected()==WR[2]->getSelected() ||
        WR[4]->getSelected()==WR[3]->getSelected())
            renewWyrd(4);
    }

    if(WR[5]==NULL){
        WR[5]=new WyrdRune();
        while (WR[5]->getSelected()==WR[0]->getSelected() ||
        WR[5]->getSelected()==WR[1]->getSelected() ||
        WR[5]->getSelected()==WR[2]->getSelected() ||
        WR[5]->getSelected()==WR[3]->getSelected() ||
        WR[5]->getSelected()==WR[4]->getSelected())
            renewWyrd(5);
    }

    if(WR[6]==NULL){
        WR[6]=new WyrdRune();
        while (WR[6]->getSelected()==WR[0]->getSelected() ||
        WR[6]->getSelected()==WR[1]->getSelected() ||
        WR[6]->getSelected()==WR[2]->getSelected() ||
        WR[6]->getSelected()==WR[3]->getSelected() ||
        WR[6]->getSelected()==WR[4]->getSelected() ||
        WR[6]->getSelected()==WR[5]->getSelected())
            renewWyrd(6);
    }

    if(WR[7]==NULL){
        WR[7]=new WyrdRune();
        while (WR[7]->getSelected()==WR[0]->getSelected() ||
        WR[7]->getSelected()==WR[1]->getSelected() ||
        WR[7]->getSelected()==WR[2]->getSelected() ||
        WR[7]->getSelected()==WR[3]->getSelected() ||
        WR[7]->getSelected()==WR[4]->getSelected() ||
        WR[7]->getSelected()==WR[5]->getSelected() ||
        WR[7]->getSelected()==WR[6]->getSelected())
            renewWyrd(7);
    }

   if(WR[8]==NULL){
       WR[8]=new WyrdRune();
       while (WR[8]->getSelected()==WR[0]->getSelected() ||
       WR[8]->getSelected()==WR[1]->getSelected() ||
       WR[8]->getSelected()==WR[2]->getSelected() ||
       WR[8]->getSelected()==WR[3]->getSelected() ||
       WR[8]->getSelected()==WR[4]->getSelected() ||
       WR[8]->getSelected()==WR[5]->getSelected() ||
       WR[8]->getSelected()==WR[6]->getSelected() ||
       WR[8]->getSelected()==WR[7]->getSelected())
           renewWyrd(8);
   }

}