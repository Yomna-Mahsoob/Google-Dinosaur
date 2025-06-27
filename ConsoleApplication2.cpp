#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

//WINDOW DIMENSIONS : 
const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 900;

//the game
Sprite Ground;
Sprite Cactus[12];
Sprite Cloud;
Font font;
Sprite dinoRun;
Sprite dinoJump;
Sprite Dinosaur;

//ALL VARIABLES THAT ARE USED IN WHOLE PROGRAM ARE HERE : -

int page;
int pageBack;
int pageAni;

//FOR MOVEMENTS : 
//OF DINOSAUR
Vector2f Velocity;
float movementSpeed= 150.f;
double DeltaTime;
Clock DeltaTime_Clock;
//FOR JUMP : 
float gravity = -1.f;
//0.1
float jumpHeight = 0.1f;
//cactus
int cactusindex;
int position_cac;
// 400
int dist = 400;
//SCORE
int score = 0;

View cameraView(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

//Collsion
bool Stop;
bool onGround;
FloatRect DinosaurBounds;
FloatRect CactusBounds[12];

struct Menu {
    Sprite sprite[3];
    Text title[5];
}
mainmenu , pausemenu , gameover;

struct sr {
    Sprite spr;
   
} Background[4];

//ALL FUNCTIONS DECLARATIONS THAT ARE USED IN WHOLE PROGRAM ARE HERE

Text drawText(const String& text, Font& font, int size, const Color& color, float positionX, float positionY);
void CollisionScreenAndGround();
void CollisionWithCactus();
void Movements(RenderTarget& window);
void bringthePositionsBack(double&, int&, int&);
void Draw(RenderTarget & window);
void gameLoopDraw(RenderTarget& window);

int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GOOGLE DINOSAUR!");
    window.setFramerateLimit(120);

    Texture texMainMenuBackground;
    Texture texFirstMainMenuButton;
    Texture texSecondMainMenuButton;

    Texture texPauseBackground;
    Texture texpauseMenuButtons;

    Texture texRestartButton;
    Texture texExitDoor;

    Texture texBackground[4];
    Texture texGround;
    Texture texCactus[3];
    Texture texCloud;

    Texture texRun;
    Texture texJump;

    //MAIN MENU INFORMATION
    
    //details of MAIN MENU PICs : - 
    //BACKGROUND OF MAIN MENU
    texMainMenuBackground.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Main Menu\\background.png");
    mainmenu.sprite[0].setTexture(texMainMenuBackground);
    mainmenu.sprite[0].setScale(2.5f, 1.6f);

    //FIRST PIC OF BUTTONS
    texFirstMainMenuButton.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Main Menu\\first buttons.png");
    mainmenu.sprite[1].setTexture(texFirstMainMenuButton);
    mainmenu.sprite[1].setScale(1, 1);
    mainmenu.sprite[1].setPosition(450, 400);

    //SECOND PIC OF BUTTONS
    texSecondMainMenuButton.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Main Menu\\second button.png");
    mainmenu.sprite[2].setTexture(texSecondMainMenuButton);
    mainmenu.sprite[2].setScale(1.f, 0.8f);
    mainmenu.sprite[2].setPosition(890, 500);
   
    font.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Others\\PixCon.ttf");

    // MAIN MENU TEXTs
    mainmenu.title[0] = drawText("Google Dinasaur", font, 40, Color::White, 450, 400);
    mainmenu.title[1] = drawText("Start", font, 40, Color::White, 620, 530);
    mainmenu.title[2] = drawText("Exit", font, 40, Color::White, 640, 630);
    mainmenu.title[3] = drawText("Mute", font, 40, Color::White, 1030, 640);

    //PAUSE MENU INFORMATION

    //BUTTONS OF PAUSE MENU
    texpauseMenuButtons.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\PAUSE MENU\\pause.png");
    pausemenu.sprite[0].setTexture(texpauseMenuButtons);
    pausemenu.sprite[0].setScale(0.7f, 0.5f);
    pausemenu.sprite[0].setPosition(420, 480);

    //BACKGROUND OF PAUSE MENU
    texPauseBackground.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\PAUSE MENU\\pause_background.png");
    pausemenu.sprite[1].setTexture(texPauseBackground);
    pausemenu.sprite[1].setScale(2.3f, 1.6f);

    // PAUSE MENU TEXTs
    pausemenu.title[0] = drawText("RESUME", font, 25, Color::White, 600, 590);
    pausemenu.title[1] = drawText("MAIN MENU", font, 24, Color::White, 585, 690);

    //GAME OVER TEXT AND SYMBOLS
    texExitDoor.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\GAME OVER\\door_button.png");
    gameover.sprite[0].setTexture(texExitDoor);
    gameover.sprite[0].setPosition(290, 390);
    gameover.sprite[0].setScale(0.4f, 0.4f);

    texRestartButton.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\GAME OVER\\restart_button.png");
    gameover.sprite[1].setTexture(texRestartButton);
    gameover.sprite[1].setPosition(650, 350);
    gameover.sprite[1].setScale(0.6, 0.6);

    gameover.title[0] = drawText("GAME OVER", font, 70, Color::White, WINDOW_WIDTH / 2 - 300, 200);
    gameover.title[1] = drawText("Score :" + to_string(score), font, 40, Color::White,WINDOW_WIDTH - (gameover.title[1].getScale().x + 600), 50);


    //GAME AFTER PRESSING "START" : -

    //BACKGROUNDs DETAILS
    //1
    texBackground[0].loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Background\\1.png");
    Background[0].spr.setTexture(texBackground[0]);
    Background[0].spr.setScale(.7, .7);
    Background[0].spr.setPosition(0, 0);
    //2
    texBackground[1].loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Background\\2.png");
    Background[1].spr.setTexture(texBackground[1]);
    Background[1].spr.setScale(.433, .433);
    //3
    texBackground[2].loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Background\\3.png");
    Background[2].spr.setTexture(texBackground[2]);
    Background[2].spr.setScale(1.3, 1.2);
    //4
    texBackground[3].loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Background\\4.png");
    Background[3].spr.setTexture(texBackground[3]);
    Background[3].spr.setScale(.677, .8);

    //////DINOSAUR DETAILS
    //ANIMATION
    //run
    texRun.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\ANIMATION\\walk-removebg-preview.png");
    dinoRun.setTexture(texRun);
    dinoRun.setPosition(30, 700);
    dinoRun.setTextureRect(IntRect(0, 0, 1124 / 9, 121));
    //jump
    texJump.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\ANIMATION\\din_anim__1_-removebg-preview (1).png");
    dinoJump.setTexture(texJump);
    dinoJump.setPosition(30, 700);
    dinoJump.setTextureRect(IntRect(0, 0, 1565 / 13, 110));

    texGround.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Basics\\ground2.png");
    Ground.setTexture(texGround);
    Ground.setScale(1.01, 1);
    Ground.setPosition(0, 740);

    //CLOUD DETAILS
    texCloud.loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Basics\\clouds_l2.png");
    Cloud.setTexture(texCloud);
    Cloud.setPosition(0, 80);
    Cloud.setScale(1, 1);

    //CACTUSs DETAILS
    //1
    texCactus[0].loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Cactus\\c1.png");
    Cactus[0].setTexture(texCactus[0]);
    Cactus[3].setTexture(texCactus[0]);
    Cactus[6].setTexture(texCactus[0]);
    Cactus[9].setTexture(texCactus[0]);
    Cactus[0].setScale(1.5, 1.5);
    Cactus[3].setScale(1.5, 1.5);
    Cactus[6].setScale(1.5, 1.5);
    Cactus[9].setScale(1.5, 1.5);
    Cactus[0].setPosition(dist, 650);
    Cactus[3].setPosition((dist * 3) + dist, 650);
    Cactus[6].setPosition((dist * 6) + dist, 650);
    Cactus[9].setPosition((dist * 9) + dist, 650);
    //2
    texCactus[1].loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Cactus\\2.png");
    Cactus[1].setTexture(texCactus[1]);
    Cactus[4].setTexture(texCactus[1]);
    Cactus[7].setTexture(texCactus[1]);
    Cactus[10].setTexture(texCactus[1]);
    Cactus[1].setPosition((dist * (0+1)) + dist, 700);
    Cactus[4].setPosition((dist * (3 + 1)) + dist, 700);
    Cactus[7].setPosition((dist * (6 + 1)) + dist, 700);
    Cactus[10].setPosition((dist * (9 + 1)) + dist, 700);
    //3
    texCactus[2].loadFromFile("F:\\ConsoleApplication2\\MATERIALS\\Cactus\\3.png");
    Cactus[2].setTexture(texCactus[2]);
    Cactus[5].setTexture(texCactus[2]);
    Cactus[8].setTexture(texCactus[2]);
    Cactus[11].setTexture(texCactus[2]);
    Cactus[2].setScale(1.5, 1.5);
    Cactus[5].setScale(1.5, 1.5);
    Cactus[8].setScale(1.5, 1.5);
    Cactus[11].setScale(1.5, 1.5);
    Cactus[2].setPosition((dist * (0 + 2)) + dist, 590);
    Cactus[5].setPosition((dist * (3 + 2)) + dist, 590);
    Cactus[8].setPosition((dist * (6 + 2)) + dist, 590);
    Cactus[11].setPosition((dist * (9 + 2)) + dist, 590);

    //animation
    double timerOfAnimation = 0;
    Clock clockAni;

    double Delay_jump = 3000.f,
        delay_motion = 1.9f,
        Delay_die = 0.15,
        delay_bird = 0.15;

    int position_run = 0;
    int position_jump = 0;
    int position_die = 0;
    int position_fly = 0;

    int TimerRun = 0;
    int TimerJump = 0;

    page = 0;
    pageBack = 0;
    pageAni = 0;

    position_cac = 0;
    cactusindex = 0;

    DeltaTime = 0;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {
                page = 3;
            }

            //CONTROL BY USING MOUSE ON MAIN MENU & PAUSE MENU

            //two dimensional vector retrieves the positin of mouse and store it in variable mousepos (x ,y)
            Vector2i mousePos = Mouse::getPosition(window);
            if (event.type == Event::MouseButtonPressed) {

                //START GAME BUTTON
                if (mainmenu.title[1].getGlobalBounds().contains(mousePos.x, mousePos.y) && page == 0) {
                    page = 1;
                }
                //EXIT GAME BUTTON
                if (mainmenu.title[2].getGlobalBounds().contains(mousePos.x, mousePos.y) && page == 0) {
                    window.close(); // Close the window
                }
                //MUSIC GAME BUTTON "TO MUTE IF YOU WANT"
                if (mainmenu.title[3].getGlobalBounds().contains(mousePos.x, mousePos.y) && page == 0) {
                    // menuMusic.setVolume(0); //handle the music stop
                }
                //RESTART THE GAME
                if (gameover.sprite[1].getGlobalBounds().contains(mousePos.x, mousePos.y) && page == 4) {
                    page = 1;
                }
                //EXIT DOOR
                if (gameover.sprite[0].getGlobalBounds().contains(mousePos.x, mousePos.y) && page == 4) {
                    page = 0;
                }
                //RESUME BUTTON
                if (pausemenu.title[0].getGlobalBounds().contains(mousePos.x, mousePos.y) && page == 3) {
                    page = 1;
                }
                //MAIN MENU BUTTON
                if (pausemenu.title[1].getGlobalBounds().contains(mousePos.x, mousePos.y) && page == 3) {
                    page = 0;
                }

            }
            //COLOR OF TEXT WILL CHANGE INTO BLACK IF I STAND ON IT
            else {
                if (pausemenu.title[0].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    pausemenu.title[0].setFillColor(Color::Black);
                }
                else {
                    pausemenu.title[0].setFillColor(Color::White);
                }

                if (pausemenu.title[1].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    pausemenu.title[1].setFillColor(Color::Black);
                }
                else {
                    pausemenu.title[1].setFillColor(Color::White);
                }

                if (gameover.sprite[1].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    gameover.sprite[1].setScale(0.7, 0.7);
                }
                else {
                    gameover.sprite[1].setScale(0.6, 0.6);
                }

                if (gameover.sprite[0].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    gameover.sprite[0].setScale(0.5, 0.5);
                }
                else {
                    gameover.sprite[0].setScale(0.4, 0.4);
                }

                if (mainmenu.title[1].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    mainmenu.title[1].setFillColor(Color::Black);
                }
                else {
                    mainmenu.title[1].setFillColor(Color::White);
                }
                if (mainmenu.title[2].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    mainmenu.title[2].setFillColor(Color::Black);
                }
                else {
                    mainmenu.title[2].setFillColor(Color::White);
                }
                if (mainmenu.title[3].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    mainmenu.title[3].setFillColor(Color::Red);
                }
                else {
                    mainmenu.title[3].setFillColor(Color::White);
                }
            }
        }

        //JUMP VARIABLE
        onGround = true;

        //COLLISION VARIABLE
        Stop = false;

        if (page == 1) {

            //COLLISION SECTION
            CollisionScreenAndGround();
            CollisionWithCactus();

            ////run
            if (pageAni == 0) {
                if (TimerRun < 0) {
                    dinoRun.setScale(1.5, 1.5);
                    position_run++;
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8 
                    position_run %= 9;
                    dinoRun.setTextureRect(IntRect(position_run * (1124 / 9), 0, 1124 / 9, 121));
                    TimerRun = delay_motion / DeltaTime;
                }
                else {
                    TimerRun -= timerOfAnimation;
                }
            }
            //jump
            else if (pageAni == 1) {
                if (TimerJump < 0) {
                    dinoJump.setScale(1.5, 1.5);
                    position_jump++;
                    position_jump %= 13;
                    dinoJump.setTextureRect(IntRect(position_jump * (1565 / 13), 0, 1565 / 13, 110));
                    TimerJump = Delay_jump;
                }
                else
                {
                    TimerJump -= timerOfAnimation;
                }
            }

            ////MOVEMENTS SECTION
            Movements(window);

            // cac always appears
            if (score >= 600) {
                if (score % 600 == 0) {
                    Cactus[cactusindex].setPosition(Cactus[cactusindex].getPosition().x + 12 * 400
                                                   ,Cactus[cactusindex].getPosition().y);
                    cactusindex++;
                    cactusindex %= 12;
                }
            }

        }

        window.clear();

        // CAMERA TO FOLLOW THE DINOSAUR
        window.setView(cameraView);

        if (page == 3) {
            cameraView.setCenter(650, 460);
            window.draw(pausemenu.sprite[1]);
            window.draw(pausemenu.sprite[0]);
            window.draw(pausemenu.title[0]);
            window.draw(pausemenu.title[1]);
        }
        else {
            if (page == 0) {
                timerOfAnimation = 0;
                cameraView.setCenter(WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2);
                Draw(window);
                bringthePositionsBack(timerOfAnimation, TimerJump, TimerRun);
            }
            else if (page == 1) {
                if (onGround) {
                    pageAni = 0;
                }
                gameLoopDraw(window);
            }
            else if (page == 4)
            {
                cameraView.setCenter(WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2);
                bringthePositionsBack(timerOfAnimation, TimerJump, TimerRun);
                window.draw(gameover.title[0]);
                window.draw(gameover.sprite[0]);
                window.draw(gameover.sprite[1]);

            }
        }
            window.display();

            //CONTROL THE DINOSAUR MOVEMENTS' SPEED
            DeltaTime = DeltaTime_Clock.restart().asSeconds();
            timerOfAnimation = clockAni.getElapsedTime().asSeconds();
    }

    return 0;

}

//ALL FUNCTION DEFINITIONS THAT ARE USED IN WHOLE PROGRAM ARE HERE

Text drawText(const String& text, Font& font, int size, const Color& color, float positionX, float positionY) {
    // int v(5); equivalent to int v = 5; 
    Text title(text, font, size);  
    title.setPosition(positionX, positionY);
    title.setFillColor(color);
    return title;

}

void Movements(RenderTarget& window) {

    //GOOD
    if (Keyboard::isKeyPressed(Keyboard::Space) && onGround) {

        Velocity.y -= jumpHeight;
        onGround = false;
    }

   /* if (!onGround) {
        pageAni = 1;
    }*/

    if (Stop) {
        page = 4;
        Velocity = { 0 , 0 };
    }
    else {
        Ground.move(Velocity.x , 0);

        //Dinosaur
        Velocity.x = movementSpeed * DeltaTime;
        dinoRun.move(Velocity);
        dinoJump.move(Velocity);

        //Backgrounds
        for (int i = 0; i < 4; i++) {
            Background[i].spr.move(Velocity.x, 0);
        }

        ////cloud
        Cloud.move(Velocity.x, 0);

        //Score movemets and the calculation
        score++;
        gameover.title[1].move(Velocity.x, 0);
        gameover.title[1].setString("Score: " + to_string(score));
        cameraView.move(Velocity.x , 0);
    }

}

void CollisionScreenAndGround() {

    //left screen
    if (dinoRun.getPosition().x <= 0) {
        dinoRun.setPosition(0.f, dinoRun.getPosition().y);
    }
    //jump height
    if (dinoJump.getPosition().y <= 350) {
        Velocity.y *= gravity;
    }
    //ground collision
    if (dinoJump.getPosition().y >= 700) {
        pageAni = 0;
        dinoRun.setPosition(dinoJump.getPosition().x, 700);
        onGround = true;
    }
    if (dinoRun.getPosition().y == 700) {
        onGround = true;
    }
    //turn on the animation of jump
    else if (dinoRun.getPosition().y < 700) {
        pageAni = 1;
        // i found a way to make the animation of jump work
        // but it is so stupid to do , SoOOoOoO StUpId AND KARAF
       // onGround = false;
    }

}

void CollisionWithCactus() {

    //if (pageAni == 0) {
    //    DinosaurBounds = dinoRun.getGlobalBounds();
    //    Dinosaur = dinoRun;
    //}
    //else if (pageAni == 1) {
    //    DinosaurBounds = dinoJump.getGlobalBounds();
    //    Dinosaur = dinoJump;
    //}
    //// to fix the Collision
    //DinosaurBounds.left -= 90.f;

    //for (int i = 0; i < 12; i++) {

    //    CactusBounds[i] = Cactus[i].getGlobalBounds();
    //    CactusBounds[i].top += 60.f;

    //    if (DinosaurBounds.intersects(CactusBounds[i])) {

    //        //right
    //        if (Dinosaur.getScale().x + DinosaurBounds.left >= CactusBounds[i].left) {
    //            Stop = true;
    //        }

    //        //left
    //        // - 100
    //        if (DinosaurBounds.left <= (CactusBounds[i].left - 100) + Cactus[i].getScale().x) {
    //            Stop = true;
    //        }

    //        //top
    //        if (DinosaurBounds.top + Dinosaur.getScale().y <= CactusBounds[i].top) {
    //            Stop = true;
    //        }


    //    }

    //}

}

void bringthePositionsBack(double& T , int& y , int& u) {


    // bring the postions back
    Background[0].spr.setScale(.7, .7);
    Background[0].spr.setPosition(0, 0);
    Background[1].spr.setScale(.433, .433);
    Background[2].spr.setScale(1.3, 1.2);
    Background[3].spr.setScale(.677, .8);

    dinoRun.setPosition(30, 700);
    dinoJump.setPosition(30, 700);

    Ground.setScale(1.01, 1);
    Ground.setPosition(0, 740);

    Cloud.setPosition(0, 80);
    Cloud.setScale(1, 1);

    //1
    Cactus[0].setPosition(dist, 650);
    Cactus[3].setPosition((dist * 3) + dist, 650);
    Cactus[6].setPosition((dist * 6) + dist, 650);
    Cactus[9].setPosition((dist * 9) + dist, 650);
    //2
    Cactus[1].setPosition((dist * (0 + 1)) + dist, 700);
    Cactus[4].setPosition((dist * (3 + 1)) + dist, 700);
    Cactus[7].setPosition((dist * (6 + 1)) + dist, 700);
    Cactus[10].setPosition((dist * (9 + 1)) + dist, 700);
    //3
    Cactus[2].setPosition((dist * (0 + 2)) + dist, 590);
    Cactus[5].setPosition((dist * (3 + 2)) + dist, 590);
    Cactus[8].setPosition((dist * (6 + 2)) + dist, 590);
    Cactus[11].setPosition((dist * (9 + 2)) + dist, 590);

    score = 0;
    gameover.title[1].setPosition(WINDOW_WIDTH - (gameover.title[1].getScale().x + 600), 50);

    Velocity.x = 0;
    Velocity.y = 0;

    T = 0;
    y = 0;
    u = 0;
}

void Draw(RenderTarget& window) {

        window.draw(mainmenu.sprite[0]);
        window.draw(mainmenu.sprite[1]);
        window.draw(mainmenu.sprite[2]);
        window.draw(mainmenu.title[0]);
        window.draw(mainmenu.title[1]);
        window.draw(mainmenu.title[2]);
        window.draw(mainmenu.title[3]);
}

void gameLoopDraw(RenderTarget& window) {

    // MAKE SURE BETWEEN EVERY BACK. THE LAST SCORE - THE PREVIOUS SCORE "REACHES 2000 * NUMBER" = 2000
    //SO THE LAST % THE PREVIOUS = 0
    if (score == 0) {
        pageBack = 0;
    }
    else if (score >= 2000) {
        if (score % 2000 == 0) {
            pageBack++;
        }
    }
    // BACKGROUNDS OF INDEX [0,3] AFTER GET SCORE
    if (pageBack == 0) {
        window.draw(Background[0].spr);
    }
    else if (pageBack == 1) {
        window.draw(Background[1].spr);
    }
    else if (pageBack == 2) {
        window.draw(Background[2].spr);
    }
    else if (pageBack == 3) {
        window.draw(Background[3].spr);
    }
    else {
        pageBack = 0;
    }

    window.setView(cameraView);
    cameraView.setCenter(dinoRun.getPosition().x + 620, WINDOW_HEIGHT / 2);

    window.draw(Ground);

    for (int i = 0; i < 12; i++) {
        window.draw(Cactus[i]);
    }

    if (pageAni == 0) {
        window.draw(dinoRun);
    }
    if (pageAni == 1) {
        window.draw(dinoJump);
    }

    window.draw(Cloud);
    window.draw(gameover.title[1]);

}

/*.
page 0 -> main menue
page 1 -> game
page 3 -> pause
page 4 -> game over

pageBack 0 -> back 1
pageBack 1 -> back 2
pageBack 2 -> back 3
pageBack 3 -> back 4

pageAni 0 -> dino_run
pageAni 1 -> dino_jump
pageAni 2 -> dino_die
*/

/*
 game over
   text
      0 game over, 1 score
   sprite
      0 exit , 1 restart
 pause menu
   text
      0 resume, 1 main menu
   sprite
      0 button , 1 background
 main menu
   text    
      0 google dinosaur , 1 start , 2 exit , 3 mute
   sprite
      0 background , 1 first button , 2 second button

*/

//problems : -
           //  1 - collision 
           //  2 - jump animation 



