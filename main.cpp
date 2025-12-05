#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHKeyboard.h"
#include "FEHImages.h"
int jumpSpeed = 3;
int fallSpeed = 4;
int jumpHeight = 50;
int p1originalHeight = 0;
int p1targetHeight = 0;
int p2originalHeight = 0;
int p2targetHeight = 0;
int x1 = 100, y1 = 180;
int x2 = 150, y2 = 180;
FEHImage rockGuy;
FEHImage treeGirl;

void PlayerOneMovement(int *x1,int *y1);
    bool playerOneJump = false;
    bool playerOneFall = false;
void PlayerTwoMovement(int *x2, int *y2);
    bool playerTwoJump = false;
    bool playerTwoFall = false;
void createPlayers(int *p1startx, int *p1starty, int *p2startx, int *p2starty);

void collison(int *xpos, int *ypos, int *origHeight,bool jumpStatus,bool *fallStatus);

bool onPlatform = false;

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
    FEHImage Level1Background;
    FEHImage CloudBase;
    FEHImage Platform, Platform2;
    FEHImage Pillar, Button, Arrow;
        while(level1){
        Level1Background.Open("level1Background.png");
        Level1Background.Draw(0, 0);
         LCD.Update();
        Level1Background.Close();
        CloudBase.Open("CloudBase.png");
        CloudBase.Draw(0, 0);
        LCD.Update();
        CloudBase.Close();
        Platform.Open("CloudPlat1.png");
        Platform.Draw(20, 40);
        Platform.Close();
        Platform2.Open("CloudPlat2.png");
        Platform2.Draw(185, 30);
        Platform2.Close(); // Add wall and arrow to show characters wrap around and encourage teamwork
        Pillar.Open("CloudPillar.png");
        Pillar.Draw(180, 82);
        Pillar.Close();
        Button.Open("Button.png");
        Button.Draw(110, 117);
        Button.Close();
        Button.Open("Button.png");
        Button.Draw(278, 117);
        Button.Close();
        Arrow.Open("Arrow.png");
        Arrow.Draw(-15, 80);
        Arrow.Close();
        
        level1 = false;
        }
        createPlayers(&x1,&y1,&x2,&y2);
        

time_t end = time(NULL); // Timer to compute time spend on level 1
level1Time = end - start;
printf("%i", level1Time); // print to check timer is working
        
}

void Level2Select(){
    bool level2 = true;
    FEHImage level2Background;
    FEHImage CloudBase;
    FEHImage Platform, Platform2;
    FEHImage Pillar, Button;
   
    while (level2){
        level2Background.Open("level1Background.png");
        level2Background.Draw(0, 0);
        LCD.Update();
        level2Background.Close();
        CloudBase.Open("CloudBase.png");
        CloudBase.Draw(0, 0);
        LCD.Update();
        CloudBase.Close();
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
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Time to Complete:", 1, 20);  // Add object for updating stats here
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("Time to Complete:", 0, 19);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("100 Seconds", 1, 40);
    LCD.SetFontColor(SLATEGRAY);
    LCD.WriteAt("100 Seconds", 0, 39);
    LCD.WriteLine(level1Time); // Add timer result here
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
        Level1Select(); // Call level select function to create level 1

        level1Select = false;
    }

    if (x >= 4 && y >= 45 && x <= 94 && y <= 80){ // Check level 2 pressed
        a = false;
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

class player{
    private:
    int deaths;
    int jumps;

    public:
    int getDeaths();
    int getJumps();
};


void PlayerOneMovement(int *x1,int *y1){

    //Modify to change player movement
    int movementSpeed = 2;

    //failsafe
    if(*y1 > 180){
    *y1 = 180;
    playerOneFall = false;
    playerOneJump = false;
   }
       //Jump

    if(Keyboard.isPressed(KEY_W) && !playerOneJump && !playerOneFall){
        playerOneJump = true;
        p1originalHeight = *y1;
        p1targetHeight = *y1 - jumpHeight;
    }

    //left
    if(Keyboard.isPressed(KEY_A)){
        *x1 -= movementSpeed;
        collison(x1,y1,&p1originalHeight,playerOneJump,&playerOneFall);


        rockGuy.Draw(*x1, *y1);
    }
    //Right
    if(Keyboard.isPressed(KEY_D)){
        *x1 += movementSpeed;
        collison(x1,y1,&p1originalHeight,playerOneJump,&playerOneFall);



        rockGuy.Draw(*x1, *y1);
    }
    
    if(playerOneJump && *y1 > p1targetHeight){

        *y1 -= jumpSpeed;

        rockGuy.Draw(*x1, *y1);

    }
    else if(playerOneJump && *y1 <= p1targetHeight){
        playerOneJump = false;
        playerOneFall = true;
    }
    //Falling
    if(playerOneFall && *y1 < p1originalHeight){
        collison(x1,y1,&p1originalHeight,playerOneJump,&playerOneFall);
        *y1 += fallSpeed;

        rockGuy.Draw(*x1, *y1);


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
    int movementSpeed = 2;

    //failsafe
    if(*y2 > 180){
    *y2 = 180;
    playerTwoFall = false;
    playerTwoJump = false;
   }
       //Jump

    if(Keyboard.isPressed(KEY_UP) && !playerTwoJump && !playerTwoFall){
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



void collison(int *x, int *y, int *originalHeight,bool isJumping,bool *fallStatus){
   //Level 1
    int nearestPlatform = 180;      
    int l1xpos[3] = {100,100,160};
   int l1ypos[3] = {200-50,160-50,140-50};
   for(int i = 0; i < 3; i++){
        //If we jump and there is a platform, land on it 
        if((*x < l1xpos[i] + 25 && *x > l1xpos[i] - 25) && ((*y > l1ypos[i] - 4) && (*y < l1ypos[i] + 4))){
            *originalHeight = l1ypos[i];
            nearestPlatform = l1ypos[i];
            onPlatform = true;
            break;
        }
        //If we walk off the platform, fall off of it 
        else if(((*x > l1xpos[i] + 25) || (*x < l1xpos[i] - 25)) && ((*y > l1ypos[i] - 4) && (*y < l1ypos[i] + 4))&& (!isJumping)){
            onPlatform = false;
           *fallStatus = true;
        }
   }
   *originalHeight = nearestPlatform;

}
int main(){
    MainMenu();    //starting positions 
    player p1; //rockguy
    player p2; //treegirl
    while(1){
       // LCD.Clear(BLACK); //will need to be changed once the new backgeround is added 
        PlayerOneMovement(&x1,&y1);
        PlayerTwoMovement(&x2,&y2);
        rockGuy.Draw(x1,y1);
        treeGirl.Draw(x2,y2);
        LCD.Update();
    }




}