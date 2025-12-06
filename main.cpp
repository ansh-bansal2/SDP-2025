#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHKeyboard.h"
#include "FEHImages.h"
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
int x1 = 100, y1 = 180;
int x2 = 150, y2 = 180;
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

class player { //Class which tracks player stats
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


#include <time.h>
FEHImage MainMenuBack;
int level1Time;
void MenuTouch();

void MainMenu(){
   
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








void Level1Select(){
    time_t start = time(NULL);
    bool level1 = true;
        while(level1){
        //Level1Background.Open("level1Background_resized.png");
        Level1Background.Draw(0, 0);
        //Level1Background.Close();
        //CloudBase.Open("CloudBase.png");
        CloudBase.Draw(0, 0);
        //CloudBase.Close();
        //Platform.Open("CloudPlat1.png");
        Platform.Draw(20, 60);
        //Platform.Close();
        //Platform2.Open("CloudPlat2.png");
        Platform2.Draw(185, 50);
        //Platform2.Close(); // Add wall and arrow to show characters wrap around and encourage teamwork
       // Pillar.Open("CloudPillar.png");
        Pillar.Draw(180, 82);
        //Pillar.Close();
        //Button.Open("Button.png");
        Button.Draw(110, 137);
        //Button.Close();
       // Button.Open("Button.png");
        Button.Draw(278, 137);
        //Button.Close();
        //Arrow.Open("Arrow.png");
        Arrow.Draw(-15, 80);
        //Arrow.Close();
        Spike.Draw(30,205);
        
        level1 = false;
        }
        createPlayers(&x1,&y1,&x2,&y2);
        

        

time_t end = time(NULL); // Timer to compute time spend on level 1
level1Time = end - start;
//printf("%i", level1Time); // print to check timer is working
        
}

void Level2Select(){
    bool level2 = true;
    /*FEHImage level2Background;
    FEHImage CloudBase;
    FEHImage Platform, Platform2;
    FEHImage Pillar, Button;*/
   
    while (level2){
         Level1Background.Draw(0, 0);
       
        Platform.Draw(-50, 85); //Spawn rock guy on this platform
       
        Platform2.Draw(162, 105); // Spawn tree girl on this platform
        Platform.Draw(162, 45);
        Platform2.Draw(-52, -20);
        Platform2.Draw(162, -55);
        Platform.Draw(-50, -75);
       
        Button.Draw(41, 0);
       
        Button.Draw(255, 28);


        level2 = false;
    }
}

void StatsButton(){
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

   /* LCD.SetFontColor(BLACK);
    LCD.WriteAt("Time to Complete:", 1, 20);  // Add object for updating stats here
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Time to Complete:", 0, 19); */

    /*LCD.SetFontColor(BLACK);
    LCD.WriteAt("100 Seconds", 1, 40);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("100 Seconds", 0, 39); */
    //LCD.WriteLine(level1Time); // Add timer result here

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

void PlayButton(){ // Function to create a stats screen with back button
    float x, y, trash1, trash2;
    bool a=true, level1Select = true, level2Select = true;
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

    
    while (level1Select){  // ADD LEVEL 1 INFO HERE
        while(!LCD.Touch(&x, &y)){};
    while(LCD.Touch(&trash1, &trash2)){};
    if (x >= 4 && y >= 5 && x <= 94 && y <= 40){ // Check level 1 pressed
        a = false;
        currentLevel = 1;
        Level1Select(); // Call level select function to create level 1

        level1Select = false;
    }

    if (x >= 4 && y >= 45 && x <= 94 && y <= 80){ // Check level 2 pressed
        a = false;
        currentLevel = 2;
        Level2Select();

        level2Select = false;
}

    while(a){
        printf("b");

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

void InstructionsButton(){
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

void CreditsButton(){
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

void MenuTouch(){

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


void PlayerOneMovement(int *x1,int *y1){

    //Modify to change player movement
    int movementSpeed = 5;

    //failsafe
    if(*y1 > 180){
    *y1 = 180;
    playerOneFall = false;
    playerOneJump = false;
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


       // rockGuy.Draw(*x1, *y1);
    }
    //Right
    if(Keyboard.isPressed(KEY_D)){
        *x1 += movementSpeed;
        collison(x1,y1,&p1originalHeight,playerOneJump,&playerOneFall);



        //rockGuy.Draw(*x1, *y1);
    }
    
    if(playerOneJump && *y1 > p1targetHeight){

        *y1 -= jumpSpeed;

        //rockGuy.Draw(*x1, *y1);

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

        //rockGuy.Draw(*x1, *y1);


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
void PlayerTwoMovement(int *x2,int *y2){

    //Modify to change player movement
    int movementSpeed = 5;

    //failsafe
    if(*y2 > 180){
    *y2 = 180;
    playerTwoFall = false;
    playerTwoJump = false;
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


        treeGirl.Draw(*x2, *y2);
    }
    //Right
    if(Keyboard.isPressed(KEY_RIGHT)){
        *x2 += movementSpeed;
        collison(x2,y2,&p2originalHeight,playerTwoJump,&playerTwoFall);



        treeGirl.Draw(*x2, *y2);
    }
    
    if(playerTwoJump && *y2 > p2targetHeight){

        *y2 -= jumpSpeed;

        treeGirl.Draw(*x2, *y2);

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

        treeGirl.Draw(*x2, *y2);


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



void createPlayers(int *x1, int *y1, int *x2, int *y2){
    //Creates players at location, should be called in the level select function.
    //50 x 60 pixels
    rockGuy.Open("Rock_guy_front.png");
    treeGirl.Open("Tree_Girl_Front.png");
    rockGuy.Draw(*x1,*y1);
    treeGirl.Draw(*x2,*y2);


    
    
    LCD.Update();
}



void collison(int *x, int *y, int *originalHeight, bool isJumping, bool *fallStatus) {
    int groundHeight = 180;
    int nearestPlatform = groundHeight;      
    
    int l1xpos[2] = {97, 265};
    int l1ypos = 175 - 50; 

    bool currentlyOverPlatform = false;
    //Check to see if we are on a platform
    printf("X: %d      ", *x);
    printf("Y: %d\n",*y);
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

const int BTN_SIZE = 30;
bool isOnButton(int px, int py, int btnX, int btnY) {
    // Player sprite is 50×60, and (px,py) is top-left.
    int playerFeetY = py + 60;   // feet position
    int playerCenterX = px + 25; // horizontally centered
    
    bool xOverlap = (playerCenterX >= btnX) && (playerCenterX <= btnX + BTN_SIZE);
    bool yOverlap = (playerFeetY >= btnY) && (playerFeetY <= btnY + BTN_SIZE);

    return xOverlap && yOverlap;
}

int BTN1_X = 116; //Button positions for hitboxes
int BTN1_Y = 163;
int BTN2_X = 284;
int BTN2_Y = 163;
// Returns true if movement is blocked by a wall
void wallCollision(int *x, int *y) {
    int wallXLeft = 165;
    int wallXRight = 215;
    int wallY = 50;
    int wallHeight = 100;
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


int main(){
    //MainMenu();    //starting positions 
    int deathMessageTimer = 1000;
    
    Level1Background.Open("level1Background_resized.png"); // Level 1 files
    CloudBase.Open("CloudBase.png");
    Platform.Open("CloudPlat1.png");
    Platform2.Open("CloudPlat2.png");
    Pillar.Open("CloudPillar.png");
    Button.Open("Button.png");
    Arrow.Open("Arrow.png"); 
    Spike.Open("Crystal_Shard.png");
    // Level 2 Files, breaks if ran currently
    //Platformlvl2.Open("CloudPlat1.png");
    //Lvl1Complete.Open("Level 1 Complete_resized.png")
    MainMenu();

    while(currentLevel = 1){
        //printf("Y: %d\n", y1);
        Level1Select();
        wallCollision(&x1,&y1);
        wallCollision(&x2, &y2);

        PlayerOneMovement(&x1,&y1);
        PlayerTwoMovement(&x2,&y2);

        bool p1OnBtn = isOnButton(x1, y1, BTN1_X, BTN1_Y); // Check position
        bool p2OnBtn = isOnButton(x2, y2, BTN2_X, BTN2_Y);

        if(p1OnBtn && p2OnBtn) { // If 2 buttons pressed, level won
            LCD.Clear(BLACK);
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("YOU WIN!", 100, 120);
            printf("You Win");
            p1.AddWin();
            p2.AddWin();
            Lvl1Complete.Open("Level 1 Complete_resized.png");
            Lvl1Complete.Draw(0,0);
            Lvl1Complete.Close();
            LCD.Update();

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