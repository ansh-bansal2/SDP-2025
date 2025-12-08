#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHKeyboard.h"
#include "FEHImages.h"
//All global variables 
int jumpSpeed = 9;
int fallSpeed = 6;
int jumpHeight = 50;
int p1originalHeight = 0;
int p1targetHeight = 0;
int p2originalHeight = 0;
int p2targetHeight = 0;
int currentLevel = 0;
bool playerOneDeath = false;
bool playerTwoDeath = false;
//Initial starting positions
int x1 = 100, y1 = 180;
int x2 = 150, y2 = 180;
//Image pointers
FEHImage rockGuy;
FEHImage treeGirl;
FEHImage Level1Background;
FEHImage CloudBase;
FEHImage Platform, Platform2;
FEHImage Pillar, Button, Arrow;
FEHImage level2Background;
FEHImage Platformlvl2;
FEHImage Lvl1Complete;
FEHImage Spike;
int buttonX1 = 114;   // example position
int buttonY1 = 163;
int buttonX2 = 282;   // second button
int buttonY2 = 163;
int buttonX3 = 16;
int buttonY3 = 18;
int buttonX4 = 270;
int buttonY4 = 50;
int x3 = 20; 
int y3 = 15;
int x4 = 275; 
int y4 = 47;


class player { //Class which tracks player stats written by Ansh Bansal
private:
    int jumps;
    int deaths;
    int wins;

public:
    player() {
        jumps = 0;
        deaths = 0;
        wins = 0;
    }

    void AddJump(){ 
        jumps++; }
    void AddDeath(){ 
        deaths++; }
    void AddWin(){ 
        wins++; }

    int GetJumps(){ 
        return jumps; }
    int GetDeaths(){ 
        return deaths; }
    int GetWins(){ 
        return wins; }
};

player p1; //rock
player p2; //root

//Function prototypes
void Lvl1buttons();
void PlayerOneMovement(int *x1,int *y1);
    bool playerOneJump = false;
    bool playerOneFall = false;
void PlayerTwoMovement(int *x2, int *y2);
    bool playerTwoJump = false;
    bool playerTwoFall = false;
void createPlayers(int *p1startx, int *p1starty, int *p2startx, int *p2starty);

void collison(int *xpos, int *ypos, int *origHeight,bool jumpStatus,bool *fallStatus);

bool onPlatform = false;

void wallCollision(int *x, int *y);

void InitLevel1();

void InitLevel2();


#include <time.h>
FEHImage MainMenuBack;
int level1Time;
void MenuTouch();

void MainMenu(){ // Ben Choma
   
    FEHImage MainMenuBack, Logo; // Declare background image
    MainMenuBack.Open("MainMenuBack_resized.png"); // Open Image
    MainMenuBack.Draw(0, 0);
    // Close the image
    MainMenuBack.Close();

    LCD.SetFontColor(LIGHTGOLDENRODYELLOW); // Add level select button
    LCD.FillRectangle(45,5,240,40);
    LCD.SetFontColor(DARKGOLDENROD);
    LCD.FillRectangle(45, 40, 240, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Level Select (play)", 50, 15);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Level Select (play)", 49, 14);
    LCD.Update(); 

    LCD.SetFontColor(LIGHTGOLDENRODYELLOW); // Statistics button
    LCD.FillRectangle(45, 50, 240, 40);
    LCD.SetFontColor(DARKGOLDENROD);
    LCD.FillRectangle(45, 85, 240, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Statistics", 105, 60);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Statistics", 104, 59);

    LCD.SetFontColor(LIGHTGOLDENRODYELLOW); // Instructions button
    LCD.FillRectangle(45, 95, 240, 40);
    LCD.SetFontColor(DARKGOLDENROD);
    LCD.FillRectangle(45, 130, 240, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Instructions", 95, 105);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Instructions", 94, 104);

    LCD.SetFontColor(LIGHTGOLDENRODYELLOW); // Instructions button
    LCD.FillRectangle(45, 140, 240, 40);
    LCD.SetFontColor(DARKGOLDENROD);
    LCD.FillRectangle(45, 175, 240, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Credits", 127, 150);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Credits", 126, 149);
    
    Logo.Open("Logo.png");
    Logo.Draw(81, 178);
    Logo.Close();

    MenuTouch();
    
}








void Level1Select(){ //Ben Choma
    currentLevel = 1;
    bool level1 = true;
        while(level1){
        Level1Background.Draw(0, 0);
        CloudBase.Draw(0, 0);
        Platform.Draw(20, 60);
        Platform2.Draw(185, 50);
        Pillar.Draw(180, 82);
        Button.Draw(110, 137);
        Button.Draw(278, 137);
        Arrow.Draw(-15, 80);
        Spike.Draw(30,205);
        level1 = false;
        }
        createPlayers(&x1,&y1,&x2,&y2);
}

void Level2Select(){ // Ben Choma
    bool level2 = true;
    currentLevel = 2;
    while (level2){
        Level1Background.Draw(0, 0);
       
        Platform.Draw(-73, 85); //Spawn rock guy on this platform
       
        Platform2.Draw(180, 105); // Spawn tree girl on this platform
        Platform.Draw(180, 45);
        Platform2.Draw(-73, -10);
        Platform2.Draw(180, -55);
        Platform.Draw(-73, -75);
       
        Button.Draw(18, 0);
       
        Button.Draw(273, 28);
        
        level2 = false;
    }
    createPlayers(&x1,&y1,&x2,&y2);
}

void StatsButton(){ // Ben Choma & Ansh Bansal
float x, y, trash1, trash2;
bool b=true;
    LCD.Clear(BLACK);
    MainMenuBack.Open("MainMenuBack_resized.png"); // Open Image
    MainMenuBack.Draw(0, 0);
    // Close the image
    MainMenuBack.Close();
    LCD.SetFontColor(BLACK);      
    LCD.WriteAt("Statistics:", 1, 1);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Statistics:", 0, 0);

   

    //Player One Stats
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Player 1:", 1, 20);  // Add object for updating stats here
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Player 1:", 0, 19);

    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Deaths: ", 1, 39);
    int deaths = p1.GetDeaths();
    LCD.WriteAt(deaths, 91,39);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Deaths: ", 0, 38);
    LCD.WriteAt(deaths, 90,38);


    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Jumps: ", 1, 58);
    int jumps = p1.GetJumps();
    LCD.WriteAt(jumps, 81,58);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Jumps: ", 0, 57);
    LCD.WriteAt(jumps, 80,57);

    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Wins: ", 1, 77);
    int wins = p1.GetWins();
    LCD.WriteAt(wins, 66,77);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Wins: ", 0, 76);
    LCD.WriteAt(wins, 65,76);

    //Player Two Stats

    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Player 2:", 1, 96 + 19);  // Add object for updating stats here
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Player 2:", 0, 95 + 19);

    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Deaths: ", 1, 115 + 19);
    int deaths2 = p2.GetDeaths();
    LCD.WriteAt(deaths2, 91,115 + 19);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Deaths: ", 0, 114 + 19);
    LCD.WriteAt(deaths2, 90,114 + 19);


    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Jumps: ", 1, 134 + 19);
    int jumps2 = p2.GetJumps();
    LCD.WriteAt(jumps2, 81,134 + 19);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Jumps: ", 0, 133 + 19);
    LCD.WriteAt(jumps2, 80,133 + 19);

    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Wins: ", 1, 153 + 19);
    int wins2 = p2.GetWins();
    LCD.WriteAt(wins2, 66,153 + 19);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Wins: ", 0, 152 + 19);
    LCD.WriteAt(wins2, 65,152 + 19);




    LCD.SetFontColor(DARKGRAY);
    LCD.FillRectangle(250, 5, 60, 35); // Back button
    LCD.SetFontColor(GRAY);
    LCD.FillRectangle(250, 35, 60, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Back", 255, 12);
    
    while(b){
        while(!LCD.Touch(&x, &y)){};
        while(LCD.Touch(&trash1, &trash2)){}
        if (x >= 250 && y >= 5){
                if (x <= 280 && y <= 40){
                    MainMenu();
                    b=false;
                }
    }
}
}

void PlayButton(){ // Ben Choma
    float x, y, trash1, trash2;
    bool a=true, level1Select = false, level2Select = false;
    LCD.Clear(BLACK);
    FEHImage MainMenuBack; // Declare background image
    MainMenuBack.Open("MainMenuBack_resized.png"); // Open Image
    MainMenuBack.Draw(0, 0);
    // Close the image
    MainMenuBack.Close();

    LCD.SetFontColor(LIGHTGOLDENRODYELLOW); // Draws level 1 button
    LCD.FillRectangle(4, 5, 90, 35);
    LCD.SetFontColor(DARKGOLDENROD);
    LCD.FillRectangle(4, 35, 90, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Level 1", 7, 12);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Level 1", 6, 11);

LCD.SetFontColor(LIGHTGOLDENRODYELLOW); // Draws level 2 button
    LCD.FillRectangle(4, 45, 90, 35);
    LCD.SetFontColor(DARKGOLDENROD);
    LCD.FillRectangle(4, 75, 90, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Level 2", 7, 52);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Level 2", 6, 51);


    LCD.SetFontColor(DARKGRAY);
    LCD.FillRectangle(250, 5, 60, 35); // Back button
    LCD.SetFontColor(GRAY);
    LCD.FillRectangle(250, 35, 60, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Back", 255, 12);

    
    while (a){  // ADD LEVEL 1 INFO HERE
        while(!LCD.Touch(&x, &y)){};
    while(LCD.Touch(&trash1, &trash2)){};
    if (x >= 4 && y >= 5 && x <= 94 && y <= 40){ // Check level 1 pressed
        a = false;
        currentLevel = 1;
        InitLevel1();
        Level1Select(); // Call level select function to create level 1
        level1Select = false;
    }

    if (x >= 4 && y >= 45 && x <= 94 && y <= 80){ // Check level 2 pressed
        a = false;
        currentLevel = 2;
        x2 = 260;
        y2 = 180;
        x1 = 8;
        y1 = 150;
        InitLevel2();
        Level2Select();
        level2Select = false;
}

    while(a){
    while(!LCD.Touch(&x, &y)){};
    while(LCD.Touch(&trash1, &trash2)){};
    if (x >= 250 && y >= 5){
                if (x <= 280 && y <= 40){
                    
                    a = false;
                    level1Select = false;
                    MainMenu();
                    
                }
            }
        }
    }
    
    
}

void InstructionsButton(){ // Ben Choma
float y1, z, ytrash, ztrash;
bool c = true;
    LCD.Clear(BLACK); // Draw instructions screen
    MainMenuBack.Open("MainMenuBack_resized.png"); // Open Image
    MainMenuBack.Draw(0, 0);
    // Close the image
    MainMenuBack.Close();
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Instructions:", 1, 1);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Instructions:", 0, 0);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Use WASD to control", 1, 20); // Write instructions here
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Use WASD to control", 0, 19);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("character 1,", 1, 40);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("character 1,", 0, 39);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("arrow keys to control", 1, 60);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("arrow keys to control", 0, 59);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("character 2.", 1, 80);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("character 2.", 0, 79);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Both players must press", 1, 120);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Both players must press", 0, 119);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("one of the two buttons.", 1, 140);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("one of the two buttons.", 0, 139);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Buttons must be pressed at", 1, 160);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Buttons must be pressed at", 0, 159);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("the same time to win.", 1, 180);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("the same time to win.", 0, 179);
    LCD.SetFontColor(DARKGRAY);
    LCD.FillRectangle(250, 5, 60, 35); // Back button
    LCD.SetFontColor(GRAY);
    LCD.FillRectangle(250, 35, 60, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Back", 255, 12);

    while (c){
        while(!LCD.Touch(&y1, &z)){}
        while(LCD.Touch(&ytrash, &ztrash)){}
        if (y1 >= 250 && z >= 5){
                if (y1 <= 280 && z <= 40){
                    MainMenu();
                    c=false;
                }
            }
    }
}

void CreditsButton(){ // Ben Choma
    float y1, z, ytrash, ztrash;
    bool c = true;
    LCD.Clear(BLACK); // Draw credits game screen
    MainMenuBack.Open("MainMenuBack_resized.png"); // Open Image
    MainMenuBack.Draw(0, 0);
    // Close the image
    MainMenuBack.Close();
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Credits:", 1, 1); // Write credits here
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Credits:", 0, 0);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Ben Choma and Ansh Bansal", 1, 40);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Ben Choma and Ansh Bansal", 0, 39);
    LCD.SetFontColor(DARKGRAY);
    LCD.FillRectangle(250, 5, 60, 35); // Back button
    LCD.SetFontColor(GRAY);
    LCD.FillRectangle(250, 35, 60, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Back", 255, 12);
    
    while (c){
        while(!LCD.Touch(&y1, &z)){}
        while(LCD.Touch(&ytrash, &ztrash)){}
        if (y1 >= 250 && z >= 5){
                if (y1 <= 280 && z <= 40){
                    MainMenu();
                    c=false;
                }
            }
    }
}

void MenuTouch(){ // Ben Choma

float x_pos, y_pos;
float x_trash, y_trash;
bool FrontMenu, IntMenu;
bool onMenu = true;
while(onMenu){
    //LCD.ClearBuffer();
    LCD.SetFontColor(WHITE);
    while(!LCD.Touch(&x_pos,&y_pos)) {}; // Register touch
    while(LCD.Touch(&x_trash,&y_trash)) {}; // Register touch release

    if((x_pos >= 45) && (y_pos >= 5)){ // Play game button pressed
        if (x_pos <= 310 && y_pos <= 45){
            onMenu = false;
           PlayButton();

        }
    }
    if((x_pos >= 45) && (y_pos >= 50)){ // Statistics button pressed
       if (x_pos <= 310 && y_pos <= 90){
        onMenu = false;
       StatsButton();}
    }


    if((x_pos >= 45) && (y_pos >= 95)){ // Instructions button pressed
        if (x_pos <= 310 && y_pos <= 135){
                onMenu = false;
                InstructionsButton();
        }
    }

    if((x_pos >= 45) && (y_pos >= 140)){ // Credits button pressed
        if (x_pos <= 310 && y_pos <= 180){

        onMenu = false;
       CreditsButton();
    }
}

}

}

void InitLevel1() { //Ansh Bansal
    currentLevel = 1;

    //starting positions
    x1 = 100; 
    y1 = 180;
    x2 = 150; 
    y2 = 180;
}

void InitLevel2() { //Ansh Bansal
    currentLevel = 2;

    //starting positions
    x1 = 8; 
    y1 = 150;
    x2 = 260; 
    y2 = 180;
}


void PlayerOneMovement(int *x1,int *y1){ //Ansh Bansal

    //Modify to change player movement
    int movementSpeed = 5;

    //failsafe for level 1
    if(currentLevel == 1){
    if(*y1 > 180){
    *y1 = 180;
    playerOneFall = false;
    playerOneJump = false;
   }
}
       //Jump

    if(Keyboard.isPressed(KEY_W) && !playerOneJump && !playerOneFall){
        p1.AddJump();
        playerOneJump = true;
        p1originalHeight = *y1;
        p1targetHeight = *y1 - jumpHeight;
    }

    //left
    if(Keyboard.isPressed(KEY_A)){
        *x1 -= movementSpeed;
        collison(x1,y1,&p1originalHeight,playerOneJump,&playerOneFall);
    }
    //Right
    if(Keyboard.isPressed(KEY_D)){
        *x1 += movementSpeed;
        collison(x1,y1,&p1originalHeight,playerOneJump,&playerOneFall); 
    }
    
    if(playerOneJump && *y1 > p1targetHeight){
        *y1 -= jumpSpeed;
    }

    else if(playerOneJump && *y1 <= p1targetHeight){
        playerOneJump = false;
        playerOneFall = true;
        collison(x1,y1,&p1originalHeight,playerOneJump,&playerOneFall);

    }
    //Falling
    if(playerOneFall && *y1 < p1originalHeight){
        collison(x1,y1,&p1originalHeight,playerOneJump,&playerOneFall);
        *y1 += fallSpeed;
    }

    else if(playerOneFall && *y1 >= p1originalHeight){
        collison(x1,y1,&p1originalHeight,playerOneJump,&playerOneFall);
        playerOneFall = false;
        *y1-=1;
    }

    //have the character move to the other side of the screen if they walk off one side
    if(*x1 > 320){
        *x1 = -25;
    }
    else if(*x1 < -25){
        *x1 = 320;
    }
        
}
void PlayerTwoMovement(int *x2,int *y2){ //Ansh Bansal

    //Modify to change player movement
    int movementSpeed = 5;

    //failsafe for level 1
    if(currentLevel ==1){
    if(*y2 > 180){
    *y2 = 180;
    playerTwoFall = false;
    playerTwoJump = false;
   }
}
       //Jump

    if(Keyboard.isPressed(KEY_UP) && !playerTwoJump && !playerTwoFall){
        p2.AddJump();
        playerTwoJump = true;
        p2originalHeight = *y2;
        p2targetHeight = *y2 - jumpHeight;
    }

    //left
    if(Keyboard.isPressed(KEY_LEFT)){
        *x2 -= movementSpeed;
        collison(x2,y2,&p2originalHeight,playerTwoJump,&playerTwoFall);
    }
    //Right
    if(Keyboard.isPressed(KEY_RIGHT)){
        *x2 += movementSpeed;
        collison(x2,y2,&p2originalHeight,playerTwoJump,&playerTwoFall);
    }
    
    if(playerTwoJump && *y2 > p2targetHeight){
        *y2 -= jumpSpeed;
    }

    else if(playerTwoJump && *y2 <= p2targetHeight){
        playerTwoJump = false;
        playerTwoFall = true;
        collison(x2,y2,&p2originalHeight,playerTwoJump,&playerTwoFall);
    }
    //Falling
    if(playerTwoFall && *y2 < p2originalHeight){
        collison(x2,y2,&p2originalHeight,playerTwoJump,&playerTwoFall);
        *y2 += fallSpeed;
    }

    else if(playerTwoFall && *y2 >= p2originalHeight){
        collison(x2,y2,&p2originalHeight,playerTwoJump,&playerTwoFall);
        playerTwoFall = false;
        *y2-=1;
    }

    //have the character move to the other side of the screen if they walk off one side
    if(*x2 > 320){
        *x2 = -25;
    }
    else if(*x2 < -25){
        *x2 = 320;
    }
}



void createPlayers(int *x1, int *y1, int *x2, int *y2){ // Ansh Bansal
    //Creates players at location, should be called in the level select function.
    //50 x 60 pixels
    rockGuy.Draw(*x1,*y1);
    treeGirl.Draw(*x2,*y2);    
    
    LCD.Update();
}



void collison(int *x, int *y, int *originalHeight, bool isJumping, bool *fallStatus) { //Ansh Bansal
    //Checking collisons for level 1
    int groundHeight;
    int nearestPlatform;
    if(currentLevel ==1){
    groundHeight = 180;
    nearestPlatform = groundHeight;      
    
    int l1xpos[2] = {97, 265};
    int l1ypos = 175 - 50; 

    bool currentlyOverPlatform = false;
    //Check to see if we are on a platform
    for(int i = 0; i < 2; i++) {
        bool overPlatformX = (*x < l1xpos[i] + 25) && (*x > l1xpos[i] - 25);
        if (overPlatformX) {
            currentlyOverPlatform = true; 
            if ((*y > l1ypos - fallSpeed) && (*y <= l1ypos + fallSpeed)) {
                nearestPlatform = l1ypos; 
                *y = l1ypos; 
                *originalHeight = l1ypos; 
                *fallStatus = false;
                onPlatform = true;
                return; 
            }
        }
    }
    //if we are on a platform and not jumping then we are no longer on a platform and we fall
    if (onPlatform && !currentlyOverPlatform && !isJumping) {
        onPlatform = false;
        *fallStatus = true;
        *originalHeight = groundHeight; 
    }
    //If we are above the ground then we set location to the ground
    if (*y >= groundHeight) {
        *y = groundHeight; 
        *fallStatus = false;
        *originalHeight = groundHeight;
        onPlatform = false;
    }
}

    //Checking collisions for Level 2
    if(currentLevel ==2){

    groundHeight = 250;
    nearestPlatform = groundHeight;      
    
    int l2xpos[6] = {2,262,262,2,262,2};
    int l2ypos[6] = {200-50,230-50,162-50,115-50,70-50,41-50}; 

    bool currentlyOverPlatform = false;
    //Check to see if we are on a platform
    for(int j = 0; j < 6; j++) {
        bool overPlatformX = (*x < l2xpos[j] + 33) && (*x > l2xpos[j] - 25);
        if (overPlatformX) {
            currentlyOverPlatform = true; 
            if ((*y > l2ypos[j] - fallSpeed) && (*y <= l2ypos[j] + fallSpeed )) {
                nearestPlatform = l2ypos[j]; 
                *y = l2ypos[j]; 
                *originalHeight = l2ypos[j]; 
                *fallStatus = false;
                onPlatform = true;
                 return; 
            }
        }
    }
    //if we are on a platform and not jumping then we are no longer on a platform and we fall
    if (onPlatform && !currentlyOverPlatform && !isJumping) {
        onPlatform = false;
        *fallStatus = true;
        *originalHeight = groundHeight; 
    }
    //If we are above the ground then we set location to the ground
    if (*y >= groundHeight) {
        *y = groundHeight; 
        *fallStatus = false;
        *originalHeight = groundHeight;
        onPlatform = false;
    }

    //Check for user deaths
    if(*y >= 240){
        if(y1 >= 240){
            p1.AddDeath();
            playerOneDeath = true;
        }
        else{
            p2.AddDeath();
            playerTwoDeath = true;
        }
        x2 = 260;
        y2 = 180;
        x1 = 8;
        y1 = 150;
        }
    }

    }


const int BTN_SIZE = 30; //30
bool isOnButtonlvl1(int px, int py, int btn1X, int btn1Y, int btn2X, int btn2Y) { // Ben Choma
    // Player sprite is 50×60, (px,py) is top-left.
    int playerFeetY = py + 60;   // feet position
    int playerCenterX = px + 25; // horizontally centered
    
   
    // Check button 1
    bool onBtn1 =
        (playerCenterX >= btn1X && playerCenterX <= btn1X + BTN_SIZE) &&
        (playerFeetY  >= btn1Y && playerFeetY <= btn1Y + BTN_SIZE);

    // Check button 2
    bool onBtn2 =
        (playerCenterX >= btn2X && playerCenterX <= btn2X + BTN_SIZE) &&
        (playerFeetY  >= btn2Y && playerFeetY <= btn2Y + BTN_SIZE);

    // Either button counts as "on a button"
    return onBtn1 || onBtn2;

}

bool isOnButtonlvl2(int px2, int py2, int btn3X, int btn3Y, int btn4X, int btn4Y){ // Ben Choma
    int playerFeet2Y = py2 + 60;
    int playerCenter2X = px2 + 25;

    //Check button 1 of lvl 2
    bool onBtn3 = 
    (playerCenter2X >= btn3X && playerCenter2X <= btn3X + BTN_SIZE) &&
    (playerFeet2Y >= btn3Y && playerFeet2Y <= btn3Y + BTN_SIZE);

    // Check button 2 of lvl 2
    bool onBtn4 = 
    (playerCenter2X >= btn4X && playerCenter2X <= btn4X + BTN_SIZE) &&
    (playerFeet2Y >= btn4Y && playerFeet2Y <= btn4Y + BTN_SIZE);
    
    // Either button counts as "on a button"
    return onBtn3 || onBtn4;
}


void wallCollision(int *x, int *y) { //Ansh Bansal
    int wallXLeft = 165;
    int wallXRight = 215;
    int wallY = 50;
    int wallHeight = 100;
    //Checks which side of the screen the user is on and if they touch the wall, dont let them move past it
    if(*x < wallXLeft + 10 && *x >= 0){
        if(*x >= wallXLeft){
        *x = wallXLeft;
        }
    }
    else if(*x >= wallXLeft + 20 && *x <= 320){
        if(*x <= wallXRight){
        *x = wallXRight;
        }
    }
    

    //Check if player hits the spike
    if(*x >= 0 && *x <= 32 && *y >= 168){
        if(x1 >= 0 && x1 <= 32 && y1 >= 168 ){
            p1.AddDeath();
            playerOneDeath = true;
        }
        else{
            p2.AddDeath();
            playerTwoDeath = true;
        }
        x2 = 150;
        y2 = 180;
        x1 = 130;
        y1 = 180;

    }

}


int main(){ // Ben Choma & Ansh Bansal
    MainMenu();    //starting positions 
    int deathMessageTimer = 1000;
    
    //Open all the image files
    Level1Background.Open("level1Background_resized.png"); // Level 1 files
    CloudBase.Open("CloudBase.png");
    Platform.Open("CloudPlat1.png");
    Platform2.Open("CloudPlat2.png");
    Pillar.Open("CloudPillar.png");
    Button.Open("Button.png");
    Arrow.Open("Arrow.png"); 
    Spike.Open("Crystal_Shard.png");
    rockGuy.Open("Rock_guy_front.png");
    treeGirl.Open("Tree_Girl_Front.png");
    
    while(true){
    //If the level is level 1, start player movement, collisions, check for completion, and check for death
    while(currentLevel == 1){
        Level1Select();
        wallCollision(&x1,&y1);
        wallCollision(&x2, &y2);

        PlayerOneMovement(&x1,&y1);
        PlayerTwoMovement(&x2,&y2);

        
        bool p1OnButton = isOnButtonlvl1(x1, y1, buttonX1, buttonY1, buttonX2, buttonY2);
        bool p2OnButton = isOnButtonlvl1(x2, y2, buttonX1, buttonY1, buttonX2, buttonY2);

    // Both buttons must be pressed at the same time:
        bool leftPressed  = isOnButtonlvl1(x1, y1, buttonX1, buttonY1, buttonX1, buttonY1) ||
                    isOnButtonlvl1(x2, y2, buttonX1, buttonY1, buttonX1, buttonY1);

        bool rightPressed = isOnButtonlvl1(x1, y1, buttonX2, buttonY2, buttonX2, buttonY2) ||
                    isOnButtonlvl1(x2, y2, buttonX2, buttonY2, buttonX2, buttonY2);


        if(leftPressed && rightPressed) { // If 2 buttons pressed, level won
            LCD.Clear(BLACK);
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("YOU WIN!", 100, 120);
            
            p1.AddWin();
            p2.AddWin();
            Lvl1Complete.Open("Level 1 Complete_resized.png");
            Lvl1Complete.Draw(0,0);
            x1 = 130;
            y1 = 180;
            x2 = 150;
            y2 = 180;
            Lvl1Complete.Close();
            LCD.Update();
            playerOneJump = false;
            playerTwoJump = false;
            Sleep(3.0); // Pause so players see screen
            MainMenu(); // Go back to menu or load next level ADD LATER
        }
        if(playerOneDeath){
            LCD.WriteAt("Player One Died!",70,0);
            deathMessageTimer -= 20;
            if(deathMessageTimer <= 0){
                playerOneDeath = false;
                deathMessageTimer = 2000;
            }

        }
        else if(playerTwoDeath){
            LCD.WriteAt("Player Two Died!",70,0);
            deathMessageTimer -= 20;
            if(deathMessageTimer <= 0){
                playerTwoDeath = false;
                deathMessageTimer = 2000;
            }

        }
        
    LCD.Update();
    }

    //If the level is level 2, start player movement, collisions, check for completion, and check for death
    while(currentLevel == 2){

        Level2Select();
        PlayerOneMovement(&x1,&y1);
        PlayerTwoMovement(&x2,&y2);

        bool p1OnButton2 = isOnButtonlvl2(x1, y1, buttonX3, buttonY3, buttonX4, buttonY4);
        bool p2OnButton2 = isOnButtonlvl2(x2, y2, buttonX3, buttonY3, buttonX4, buttonY4);

        // Both buttons must be pressed at the same time:
        bool leftPressed2  = isOnButtonlvl2(x1, y1, buttonX3, buttonY3, buttonX3, buttonY3) ||
        isOnButtonlvl2(x2, y2, buttonX3, buttonY3, buttonX3, buttonY3);

        bool rightPressed2 = isOnButtonlvl2(x1, y1, buttonX4, buttonY4, buttonX4, buttonY4) ||
        isOnButtonlvl2(x2, y2, buttonX4, buttonY4, buttonX4, buttonY4);

        if(leftPressed2 && rightPressed2) { // If 2 buttons pressed, level won
            LCD.Clear(BLACK);
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("YOU WIN!", 100, 120);
            p1.AddWin();
            p2.AddWin();
            Lvl1Complete.Open("Level 1 Complete_resized.png");
            Lvl1Complete.Draw(0,0);
            x1 = 8;
            y1 = 150;
            x2 = 260;
            y2 = 180;
            Lvl1Complete.Close();
            LCD.Update();
            playerOneJump = false;
            playerTwoJump = false;
            Sleep(3.0); // Pause so players see screen
            MainMenu(); // Go back to menu or load next level ADD LATER
}
         if(playerOneDeath){
            LCD.WriteAt("Player One Died!",70,0);
            deathMessageTimer -= 20;
            if(deathMessageTimer <= 0){
                playerOneDeath = false;
                deathMessageTimer = 2000;
            }

        }
        else if(playerTwoDeath){
            LCD.WriteAt("Player Two Died!",70,0);
            deathMessageTimer -= 20;
            if(deathMessageTimer <= 0){
                playerTwoDeath = false;
                deathMessageTimer = 2000;
            }
        }

        LCD.Update();


    }



}
}