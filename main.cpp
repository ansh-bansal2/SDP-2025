#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHKeyboard.h"
#include "FEHImages.h"
int jumpSpeed = 3;
int fallSpeed = 4;
int originalHeight = 0;
int targetHeight = 0;
FEHImage rockGuy;
FEHImage treeGirl;
//hi

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

void collison(int *xpos, int *ypos);



   



void PlayerOneMovement(int *x1,int *y1){

    //Modify to change player movement
    
    int jumpHeight = 50;
    int movementSpeed = 2;


    //left
    if(Keyboard.isPressed(KEY_A)){
        LCD.SetFontColor(BLACK);
       // LCD.FillRectangle(*x1, *y1, 50, 60);

        *x1 -= movementSpeed;

        rockGuy.Draw(*x1, *y1);
    }
    //Right
    if(Keyboard.isPressed(KEY_D)){
        LCD.SetFontColor(BLACK);
       // LCD.FillRectangle(*x1, *y1, 50, 60);

        *x1 += movementSpeed;

        rockGuy.Draw(*x1, *y1);
    }
    //Jump
    if(Keyboard.isPressed(KEY_W) && !playerOneJump && !playerOneFall){
        playerOneJump = true;
        targetHeight = *y1 - jumpHeight;
        originalHeight = *y1;
    }
    if(playerOneJump && *y1 > targetHeight){
         LCD.SetFontColor(BLACK);
       // LCD.FillRectangle(*x1, *y1, 50, 60);

        *y1 -= jumpSpeed;

        rockGuy.Draw(*x1, *y1);

    }
    else if(playerOneJump && *y1 <= targetHeight){
        playerOneJump = false;
        //Call collsion here to determine if playerOneFall needs to change ig otherwiae ill change to code to not use this boolean
        playerOneFall = true;
    }
    //Falling
    if(playerOneFall && *y1 < originalHeight){
        LCD.SetFontColor(BLACK);
       // LCD.FillRectangle(*x1, *y1, 50, 60);

        *y1 += fallSpeed;

        rockGuy.Draw(*x1, *y1);


    }
    else if(playerOneFall && *y1 >= originalHeight){
        playerOneFall = false;
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
    int jumpHeight = 50;
    int movementSpeed = 2;
   

    //left
    if(Keyboard.isPressed(KEY_LEFT)){
         LCD.SetFontColor(BLACK);
       // LCD.FillRectangle(*x2, *y2, 50, 60);

        *x2 -= movementSpeed;

        treeGirl.Draw(*x2, *y2);
    }
    //Right
    if(Keyboard.isPressed(KEY_RIGHT)){
        LCD.SetFontColor(BLACK);
       // LCD.FillRectangle(*x2, *y2, 50, 60);

        *x2 += movementSpeed;

        treeGirl.Draw(*x2, *y2);
    }
    //Jump
    if(Keyboard.isPressed(KEY_UP) && !playerTwoJump && !playerTwoFall){
        targetHeight = *y2 - jumpHeight;
        originalHeight = *y2;
        playerTwoJump = true;
    }
    if(playerTwoJump && *y2 > targetHeight){
       LCD.SetFontColor(BLACK);
       // LCD.FillRectangle(*x2, *y2, 50, 60);

        *y2 -= jumpSpeed;

        treeGirl.Draw(*x2, *y2);

    }
    else if(playerTwoJump && *y2 <= targetHeight){
        playerTwoJump = false;
        //Call collsion here to determine if playerTwoFall needs to change ig otherwiae ill change to code to not use this boolean
        playerTwoFall = true;
    }

    //fall
    if(playerTwoFall && *y2 < originalHeight){
        LCD.SetFontColor(BLACK);
       // LCD.FillRectangle(*x2, *y2, 50, 60);


        treeGirl.Draw(*x2, *y2);


    }
    else if(playerTwoFall && *y2 >= originalHeight){
        playerTwoFall = false;
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
  //  LCD.DrawRectangle(x1 + 19,y1 + 15,12,36);
    //LCD.DrawRectangle(x2 + 20,y2 + 16,9,32);

    //might need to close the image with .Close()
    LCD.Update();
}

void collison(int *x, int *y){

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
        LCD.Update();
    }




}