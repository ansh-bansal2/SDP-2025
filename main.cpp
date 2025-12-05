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
FEHImage rockGuy;
FEHImage treeGirl;

void MainMenu(){
   
    FEHImage MainMenuBack; // Declare background image
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
    LCD.Update(); 

    LCD.SetFontColor(LIGHTGOLDENRODYELLOW); // Statistics button
    LCD.FillRectangle(45, 50, 240, 40);
    LCD.SetFontColor(DARKGOLDENROD);
    LCD.FillRectangle(45, 85, 240, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Statistics", 105, 60);

    LCD.SetFontColor(LIGHTGOLDENRODYELLOW); // Instructions button
    LCD.FillRectangle(45, 95, 240, 40);
    LCD.SetFontColor(DARKGOLDENROD);
    LCD.FillRectangle(45, 130, 240, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Instructions", 95, 105);

    LCD.SetFontColor(LIGHTGOLDENRODYELLOW); // Instructions button
    LCD.FillRectangle(45, 140, 240, 40);
    LCD.SetFontColor(DARKGOLDENROD);
    LCD.FillRectangle(45, 175, 240, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Credits", 127, 150);
    
    LCD.SetFontColor(BLUE);
    LCD.WriteAt("TITLE", 140, 195);
    LCD.Update();
}

void StatsButton(){
float x, y, trash1, trash2;
bool b=true;
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Statistics:", 0, 0);
    LCD.WriteAt("Time to Complete:", 0, 20);
    LCD.WriteAt("100 Seconds", 0, 40);
    LCD.FillRectangle(250, 5, 60, 35); // Back button
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
    bool a=true, level1Select = true;
    LCD.Clear(BLACK);
    FEHImage MainMenuBack; // Declare background image
    MainMenuBack.Open("MainMenuBack_resized.png"); // Open Image
    MainMenuBack.Draw(0, 0);
    // Close the image
    MainMenuBack.Close();

    LCD.SetFontColor(LIGHTGOLDENRODYELLOW);
    LCD.FillRectangle(4, 5, 90, 35);
    LCD.SetFontColor(DARKGOLDENROD);
    LCD.FillRectangle(4, 35, 90, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Level 1", 7, 12);
    LCD.SetFontColor(DARKGRAY);
    LCD.FillRectangle(250, 5, 60, 35); // Back button
    LCD.SetFontColor(GRAY);
    LCD.FillRectangle(250, 35, 60, 5);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Back", 255, 12);

    while (level1Select){  // ADD LEVEL 1 INFO HERE
        while(!LCD.Touch(&x, &y)){};
    while(LCD.Touch(&trash1, &trash2)){};
    if (x >= 4 && y >= 5 && x <= 94 && y <= 40){
        FEHImage Level1Background;
        Level1Background.Open("level1Background.png");
        Level1Background.Draw(0, 0); 
        Level1Background.Close();
        LCD.SetFontColor(WHITE);
        LCD.Write("LEVEL 1 HERE");
        level1Select = false;
    }
    }
    
    while(a){
    while(!LCD.Touch(&x, &y)){};
    while(LCD.Touch(&trash1, &trash2)){};
    if (x >= 250 && y >= 5){
                if (x <= 280 && y <= 40){
                    MainMenu();
                    a=false;
                }
            }
        }
}

void InstructionsButton(){
float y1, z, ytrash, ztrash;
bool c = true;
    LCD.Clear(BLACK); // Draw instructions screen
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Instructions:", 0, 0);
    LCD.WriteAt("Use WASD to control character 1,", 0, 20); // Write instructions here
    LCD.WriteAt(" arrow keys to control character 2.", 0, 40);
    LCD.WriteAt("Both players must", 0, 60);
    LCD.WriteAt("press one of the two buttons", 0, 80);
    LCD.WriteAt("Buttons must be pressed at", 0, 100);
    LCD.WriteAt("the same time to win.", 0 ,120);
    LCD.FillRectangle(250, 5, 60, 35); // Back button
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
    LCD.Clear(BLACK); // Draw play game screen
    LCD.WriteAt("Credits:", 0, 0); // Write credits here
    LCD.WriteAt("Ben Choma and Ansh Bansal", 0, 40);
    LCD.FillRectangle(250, 5, 60, 35); 
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
while(true){
    //LCD.ClearBuffer();
    LCD.SetFontColor(WHITE);
    while(!LCD.Touch(&x_pos,&y_pos)) {}; // Register touch
    while(LCD.Touch(&x_trash,&y_trash)) {}; // Register touch release

    if((x_pos >= 45) && (y_pos >= 5)){ // Play game button pressed
        if (x_pos <= 310 && y_pos <= 45){
           PlayButton();

        }
    }
    if((x_pos >= 45) && (y_pos >= 50)){ // Statistics button pressed
       if (x_pos <= 310 && y_pos <= 90){
       StatsButton();}
    }


    if((x_pos >= 45) && (y_pos >= 95)){ // Instructions button pressed
        if (x_pos <= 310 && y_pos <= 135){
                InstructionsButton();
        }
    }

    if((x_pos >= 45) && (y_pos >= 140)){ // Credits button pressed
        if (x_pos <= 310 && y_pos <= 180){
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

void PlayerOneMovement(int *x1,int *y1);
    bool playerOneJump = false;
    bool playerOneFall = false;
void PlayerTwoMovement(int *x2, int *y2);
    bool playerTwoJump = false;
    bool playerTwoFall = false;
void createPlayers(int p1startx, int p1starty, int p2startx, int p2starty);

void collison(int *xpos, int *ypos, int *origHeight,bool jumpStatus,bool *fallStatus);

bool onPlatform = false;

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
    
void createPlayers(int x1, int y1, int x2, int y2){
    //Creates players at location, should be called in the level select function.
    //50 x 60 pixels
    rockGuy.Open("Rock_guy_front.png");
    treeGirl.Open("Tree_Girl_Front.png");
    rockGuy.Draw(x1,y1);
    treeGirl.Draw(x2,y2);
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
    //starting positions 
    int x1 = 100, y1 = 180;
    int x2 = 150, y2 = 180;
    int r = 10;
    player p1; //rockguy
    player p2; //treegirl
    //Creates players
    createPlayers(x1,y1,x2,y2);
    while(1){
        LCD.Clear(BLACK); //will need to be changed once the new backgeround is added 
        PlayerOneMovement(&x1,&y1);
        PlayerTwoMovement(&x2,&y2);
        rockGuy.Draw(x1,y1);
        treeGirl.Draw(x2,y2);
        //Rectangle to test collision function
        LCD.SetFontColor(BLUE);
        LCD.DrawRectangle(100,200,50,1);
        LCD.DrawRectangle(100,160,50,1);
        LCD.DrawRectangle(160,140,50,1);
        LCD.Update();
    }




}