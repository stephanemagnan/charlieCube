/********************************** SIGNATURE *********************************\
|                                      ,,                                      |
|                     db             `7MM                                      |
|                    ;MM:              MM                                      |
|                   ,V^MM.    ,pP"Ybd  MMpMMMb.  .gP"Ya `7Mb,od8               |
|                  ,M  `MM    8I   `"  MM    MM ,M'   Yb  MM' "'               |
|                  AbmmmqMA   `YMMMa.  MM    MM 8M""""""  MM                   |
|                 A'     VML  L.   I8  MM    MM YM.    ,  MM                   |
|               .AMA.   .AMMA.M9mmmP'.JMML  JMML.`Mbmmd'.JMML.                 |
|                                                                              |
|                                                                              |
|                                  ,,    ,,                                    |
|                      .g8"""bgd `7MM    db        `7MM                        |
|                    .dP'     `M   MM                MM                        |
|                    dM'       `   MM  `7MM  ,p6"bo  MM  ,MP'                  |
|                    MM            MM    MM 6M'  OO  MM ;Y                     |
|                    MM.    `7MMF' MM    MM 8M       MM;Mm                     |
|                    `Mb.     MM   MM    MM YM.    , MM `Mb.                   |
|                      `"bmmmdPY .JMML..JMML.YMbmd'.JMML. YA.                  |
|                                                                              |
\******************************************************************************/
/*********************************** LICENCE **********************************\
| Copyright (c) 2012, Asher Glick                                              |
| All rights reserved.                                                         |
|                                                                              |
| Redistribution and use in source and binary forms, with or without           |
| modification, are permitted provided that the following conditions are met:  |
|                                                                              |
| * Redistributions of source code must retain the above copyright notice,     |
|   this list of conditions and the following disclaimer.                      |
| * Redistributions in binary form must reproduce the above copyright notice,  |
|   this list of conditions and the following disclaimer in the documentation  |
|   and/or other materials provided with the distribution.                     |
|                                                                              |
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  |
| AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    |
| IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   |
| ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE    |
| LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR          |
| CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         |
| SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS     |
| INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      |
| CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      |
| ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   |
| POSSIBILITY OF SUCH DAMAGE.                                                  |
\******************************************************************************/

#include "cubeplex.h"

int color = red;

const byte interruptPin = 2;
const byte colourPin = 25;
const byte speedPin = 26;

void setup() {
  initCube();

  Serial.begin(9600);
  
  pinMode(interruptPin, INPUT);
  //pinMode(interruptPin, INPUT);
  //pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
  // how many secconds until the animation is told to progress
  animationMax = 10000;
}
void loop() {
//  ledTest();
//extinction();
//  planarSpin2();
//  planarSpin();
//  fountian();
//  trifade();
//  shiftSquares();
//  tunnel();
//  chaseTheDot();
  planarFlop3D();
  
}
void blink(){
  continuePattern=false;
  Serial.println("pressed");
}

/******************************** CHASE THE DOT *******************************\
| A single point of light moves around the cube randomly and changes colors    |
| when it tries to go out of bounds                                            |
|                                                                              |
| Inspired By: Jonah Glick                                                     |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void ledTest() {
  continuePattern = true;
  int animationSpeed = 100;
  
  int xpos = 0;
  int ypos = 0;
  int zpos = 0;
  
  while (continuePattern) {
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        for (int k = 0; k <= 3; k++) {
          Serial.print(k+4*j+16*i);
          Serial.print(": i=");
          Serial.print(i);
          Serial.print(", j=");
          Serial.print(j);
          Serial.print(", k=");
          Serial.print(k);
          Serial.print(" ->");
          Serial.print(color);
          Serial.print(" ");
          Serial.print((((color)%3)*64)+(i*16)+(j*4)+k);
          Serial.println("");
          drawLed(color,i,j,k);
          flushBuffer();
          clearBuffer();
          delay(animationSpeed);
          delay(50);

          if(!continuePattern) {
            i=3;
            j=3;
            k=3;
          }
        }
      }
    }
    
    //color=nextPrimaryColor(color);
    color=nextColor(color);
    

  }
}


/********************************* PLANAR SPIN 2 ********************************\
| A plane of light spins around the virtical center of the cube and changes    |
| colors after a certian number of rotations   corrected for math                                |
|                                                                              |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void extinction() {
  continuePattern = true;
  int animationSpeed = 100;
  int steps = 10;
  int steps_1 = 30;

  int strike_order[] = {1,12,6,15,10,8,11,16,4,3,13,7,9,5,2,14};
  int ground_colour[] = {green,blue,green,green,green,blue,blue,green,green,green,blue,green,green,green,blue,blue};
  
  //while (continuePattern) {
    
    for (int turn = 0; turn < 64; turn++) {

      for (int i = 0; i<=3; i++){
        for (int j = 0; j<=3; j++){
          
          if(turn>=strike_order[4*i+j]*4){
            drawLed(red,i,j,3);
          }else if((turn+1)==strike_order[4*i+j]*4){
            drawLed(ground_colour[4*i+j],i,j,3);
            drawLed(white,i,j,2);
          }else if((turn+2)==strike_order[4*i+j]*4){
            drawLed(ground_colour[4*i+j],i,j,3);
            drawLed(white,i,j,1);
          }else if((turn+3)==strike_order[4*i+j]*4){
            drawLed(ground_colour[4*i+j],i,j,3);
            drawLed(white,i,j,0);
          }else{
            drawLed(ground_colour[4*i+j],i,j,3);
          }     
        }
      }

      flushBuffer();
      clearBuffer();
      delay(animationSpeed);

    }

    for (int turn = 0; turn <= 17; turn++) {

      for (int i = 0; i<=3; i++){
        for (int j = 0; j<=3; j++){
          drawLed(red,i,j,3);
        }
      }


      if(turn ==3){
       for (int i = 1; i<=2; i++){
         for (int j = 1; j<=2; j++){
           for (int k = 0; k<=0; k++){
             drawLed(white,i,j,k);
           }
         }
       }
      }else if(turn ==4){
       for (int i = 1; i<=2; i++){
         for (int j = 1; j<=2; j++){
           for (int k = 0; k<=1; k++){
             drawLed(white,i,j,k);
           }
         }
       }
      }else if(turn ==5){
       for (int i = 1; i<=2; i++){
         for (int j = 1; j<=2; j++){
           for (int k = 1; k<=2; k++){
             drawLed(white,i,j,k);
           }
         }
       }
      }else if(turn ==6){
       for (int i = 1; i<=2; i++){
         for (int j = 1; j<=2; j++){
           for (int k = 2; k<=3; k++){
             drawLed(white,i,j,k);
           }
         }
       }
      }else if(turn ==7){
       for (int i = 1; i<=2; i++){
         for (int j = 1; j<=2; j++){
           for (int k = 3; k<=3; k++){
             drawLed(white,i,j,k);
           }
         }
       }
      }else if(turn ==9){
       for (int i = 1; i<=2; i++){
         for (int j = 1; j<=2; j++){
           for (int k = 2; k<=3; k++){
             drawLed(red,i,j,k);
           }
         }
       }
      }else if(turn ==10){
       for (int i = 1; i<=2; i++){
         for (int j = 1; j<=2; j++){
           for (int k = 1; k<=3; k++){
             drawLed(red,i,j,k);
           }
         }
       }
      }else if(turn ==11){
       for (int i = 1; i<=2; i++){
         for (int j = 1; j<=2; j++){
           for (int k = 0; k<=3; k++){
             drawLed(red,i,j,k);
           }
         }
       }
      }else if(turn ==12){
       for (int i = 1; i<=2; i++){
         for (int j = 1; j<=2; j++){
           for (int k = 1; k<=3; k++){
             drawLed(red,i,j,k);
           }
         }
       }
       for (int i = 0; i<=3; i++){
         for (int j = 0; j<=3; j++){
           for (int k = 0; k<=0; k++){
             drawLed(red,i,j,k);
           }
         }
       }
      }else if(turn ==13){
       for (int i = 1; i<=2; i++){
         for (int j = 1; j<=2; j++){
           for (int k = 2; k<=3; k++){
             drawLed(red,i,j,k);
           }
         }
       }
       for (int i = 0; i<=3; i++){
         for (int j = 0; j<=3; j++){
           for (int k = 0; k<=1; k++){
             drawLed(red,i,j,k);
           }
         }
       }
      }else if(turn ==14){
       for (int i = 0; i<=3; i++){
         for (int j = 0; j<=3; j++){
           for (int k = 0; k<=3; k++){
             drawLed(red,i,j,k);
           }
         }
       }
      }else if(turn ==15){
       for (int i = 0; i<=3; i++){
         for (int j = 0; j<=3; j++){
           for (int k = 1; k<=3; k++){
             drawLed(red,i,j,k);
           }
         }
       }
      }else if(turn ==16){
       for (int i = 0; i<=3; i++){
         for (int j = 0; j<=3; j++){
           for (int k = 2; k<=3; k++){
             drawLed(red,i,j,k);
           }
         }
       }
      }else if(turn ==17){
       for (int i = 0; i<=3; i++){
         for (int j = 0; j<=3; j++){
           for (int k = 3; k<=3; k++){
             drawLed(red,i,j,k);
           }
         }
       }
      }

      flushBuffer();
      clearBuffer();
      delay(animationSpeed);

    }


  //}
}

/********************************* PLANAR SPIN 2 ********************************\
| A plane of light spins around the virtical center of the cube and changes    |
| colors after a certian number of rotations   corrected for math                                |
|                                                                              |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void planarSpin2() {
  continuePattern = true;
  int animationSpeed = 800;
  int t0 = animationSpeed/13.5; //0.0738888
  int t1 = animationSpeed/5.7; //0.176111
  int t2 = animationSpeed/6.8; //0.147777
  int spinsPerColor = 5; // a spin is actually half a revolution
  Serial.println(t0 );
  Serial.println(t1);
  Serial.println(t2);
  while (continuePattern) {
    for (int i = 0; i < spinsPerColor; i++) {
      
      //PART 1
      Serial.println("Part 1");
      for (int k = 0; k<=3; k++){
        drawLed(color,0,0,k);
        drawLed(color,1,1,k);
        drawLed(color,2,2,k);
        drawLed(color,3,3,k);
      }
      flushBuffer();
      clearBuffer();
      delay(t0);

      //PART 2
      Serial.println("Part 2");
      for (int k = 0; k<=3; k++){
        drawLed(color,0,1,k);
        drawLed(color,3,2,k);
      }
      flushBuffer();
      clearBuffer();
      delay(t1);

      //PART 3
      Serial.println("Part 3");
      for (int k = 0; k<=3; k++){
        drawLed(color,0,2,k);
        drawLed(color,3,1,k);
      }
      flushBuffer();
      clearBuffer();
      delay(t1);

      //PART 4
      Serial.println("Part 4");
      for (int k = 0; k<=3; k++){
        drawLed(color,0,3,k);
        drawLed(color,1,2,k);
        drawLed(color,2,1,k);
        drawLed(color,3,0,k);
      }
      flushBuffer();
      clearBuffer();
      delay(t2);

      //PART 5
      Serial.println("Part 5");
      for (int k = 0; k<=3; k++){
        drawLed(color,1,3,k);
        drawLed(color,2,0,k);
      }
      flushBuffer();
      clearBuffer();
      delay(t1);

      //PART 6
      Serial.println("Part 6");
      for (int k = 0; k<=3; k++){
        drawLed(color,1,0,k);
        drawLed(color,2,3,k);
      }
      flushBuffer();
      clearBuffer();
      delay(t1);

      //PART 7
      Serial.println("Part 7");
      for (int k = 0; k<=3; k++){
        drawLed(color,0,0,k);
        drawLed(color,1,1,k);
        drawLed(color,2,2,k);
        drawLed(color,3,3,k);
      }
      flushBuffer();
      clearBuffer();
      delay(t0);

      
    }

    
    color = nextColor(color);
  }
}

/********************************* PLANAR SPIN ********************************\
| A plane of light spins around the virtical center of the cube and changes    |
| colors after a certian number of rotations                                   |
|                                                                              |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void planarSpin() {
  continuePattern = true;
  int animationSpeed = 250;
  int spinsPerColor = 5; // a spin is actually half a revolution
  while (continuePattern) {
    int x = 0;
    int y = 0;
    for (int i = 0; i < spinsPerColor; i++) {
      for (int x = 0; x < 3; x++) {
        drawLine(color,x,0,0,3-x,3,0);
        drawLine(color,x,0,1,3-x,3,1);
        drawLine(color,x,0,2,3-x,3,2);
        drawLine(color,x,0,3,3-x,3,3);
        flushBuffer();
        clearBuffer();
        delay(animationSpeed);
      }
      for (int y = 0; y < 3; y++) {
        drawLine(color,3,y,0,0,3-y,0);
        drawLine(color,3,y,1,0,3-y,1);
        drawLine(color,3,y,2,0,3-y,2);
        drawLine(color,3,y,3,0,3-y,3);
        flushBuffer();
        clearBuffer();
        delay(animationSpeed);
      }
    }
    color = nextColor(color);
  }
}

/********************************** FOUNTIAN **********************************\
| Light shoots up the middle of the cube then once it reaches the top fall     |
| back down on the outside of the cube. After it hits the bottom it changes    |
| color and starts again                                                       |
|                                                                              |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void fountian() {
  continuePattern = true;
  int animationSpeed = 100;
  while (continuePattern) {
    for (int z = 0; z <= 3; z++) {
      drawBoxWalls(color,1,1,z,2,2,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int z = 3; z >= 0; z--) {
      drawBoxWalls(color,0,0,z,3,3,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    color=nextColor(color);
  }
}

/********************************** TRI-FADE **********************************\
| This animation fades through the red green and blue colors of the leds       |
| creating different mixtures of each of the colors.                           |
|                                                                              |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void trifade() {
  continuePattern = true;
  int animationSpeed = 100;
  while (continuePattern) {
    // blue fade out, red fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(blue,9-i,0,0,0,3,3,3);
      drawBox(red,i,0,0,0,3,3,3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    // red fade out, green fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(red,9-i,0,0,0,3,3,3);
      drawBox(green,i,0,0,0,3,3,3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    // green fade out, blue fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(green,9-i,0,0,0,3,3,3);
      drawBox(blue,i,0,0,0,3,3,3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
  }
}

/******************************** SHIFT SQUARES *******************************\
| Three 2x2x2 squares start on the cube each a red green or blue. then they    |
| randomly move around the cube one at a time, if they crash into each other   |
| then then both leds turn on and while they occupy the same space they apear  |
| a different color                                                            |
|                                                                              |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void shiftSquares() {
  int animationSpeed = 100;
  
  int blx = 2; // blue x
  int bly = 0; // blue y
  int blz = 0; // blue z
  
  int rdx = 0; // red x
  int rdy = 2; // red y
  int rdz = 0; // red z
  
  int gnx = 0; // green x
  int gny = 0; // green y
  int gnz = 2; // green z
  
  int * mover = &blx;
  continuePattern = true;
  
  while(continuePattern) {
    switch (random(0,9)) {
      case 0: mover = &blx; break;
      case 1: mover = &bly; break;
      case 2: mover = &blz; break;
      case 3: mover = &rdx; break;
      case 4: mover = &rdy; break;
      case 5: mover = &rdz; break;
      case 6: mover = &gnx; break;
      case 7: mover = &gny; break;
      case 8: mover = &gnz; break;
    }
    *mover = (((*mover)+2)%4)-1;
    drawBox(blue ,abs(blx),abs(bly),abs(blz),abs(blx)+1,abs(bly)+1,abs(blz)+1);
    drawBox(red  ,abs(gnx),abs(gny),abs(gnz),abs(gnx)+1,abs(gny)+1,abs(gnz)+1);
    drawBox(green,abs(rdx),abs(rdy),abs(rdz),abs(rdx)+1,abs(rdy)+1,abs(rdz)+1);
    flushBuffer();
    clearBuffer();
    delay(animationSpeed);
    *mover = (((*mover)+2)%4)-1;
    drawBox(blue ,abs(blx),abs(bly),abs(blz),abs(blx)+1,abs(bly)+1,abs(blz)+1);
    drawBox(red  ,abs(gnx),abs(gny),abs(gnz),abs(gnx)+1,abs(gny)+1,abs(gnz)+1);
    drawBox(green,abs(rdx),abs(rdy),abs(rdz),abs(rdx)+1,abs(rdy)+1,abs(rdz)+1);
    flushBuffer();
    clearBuffer();
    delay(animationSpeed*2);
  }
}

/*********************************** TUNNEL ***********************************\
|
\******************************************************************************/
void tunnel() {
  continuePattern = true;
  int animationSpeed =100;
  
  int color1[]  = {R,R,R,R,B,B,B,B};
  int bright1[] = {2,4,6,8,2,4,6,8};
  int color2[]  = {B,B,B,B,R,R,R,R};
//int bright2[] = {6,4,2,0,6,4,2,0};
  int bright2[] = {8,6,4,2,8,6,4,2};
  
  int index[]   = {0,1,2,3,4,5,6,7};
  
  while (continuePattern) {
    drawBoxWalls(color1[index[0]],bright1[index[0]],1,1,0,2,2,0);
    drawBoxWalls(color2[index[0]],bright2[index[0]],1,1,0,2,2,0);
    drawBoxWalls(color1[index[1]],bright1[index[1]],1,1,1,2,2,1);
    drawBoxWalls(color2[index[1]],bright2[index[1]],1,1,1,2,2,1);
    drawBoxWalls(color1[index[2]],bright1[index[2]],1,1,2,2,2,2);
    drawBoxWalls(color2[index[2]],bright2[index[2]],1,1,2,2,2,2);
    drawBoxWalls(color1[index[3]],bright1[index[3]],1,1,3,2,2,3);
    drawBoxWalls(color2[index[3]],bright2[index[3]],1,1,3,2,2,3);
    
    drawBoxWalls(color1[index[4]],bright1[index[4]],0,0,3,3,3,3);
    drawBoxWalls(color2[index[4]],bright2[index[4]],0,0,3,3,3,3);
    drawBoxWalls(color1[index[5]],bright1[index[5]],0,0,2,3,3,2);
    drawBoxWalls(color2[index[5]],bright2[index[5]],0,0,2,3,3,2);
    drawBoxWalls(color1[index[6]],bright1[index[6]],0,0,1,3,3,1);
    drawBoxWalls(color2[index[6]],bright2[index[6]],0,0,1,3,3,1);
    drawBoxWalls(color1[index[7]],bright1[index[7]],0,0,0,3,3,0);
    drawBoxWalls(color2[index[7]],bright2[index[7]],0,0,0,3,3,0);
    
    
    flushBuffer();
    clearBuffer();
    for (int i = 0; i < 8; i++){
      //index[i] = index[i]==7?0:index[i]+1;
      index[i] = (index[i]+1)%8;
    }
    delay(animationSpeed);
    
  }
}
/******************************** CHASE THE DOT *******************************\
| A single point of light moves around the cube randomly and changes colors    |
| when it tries to go out of bounds                                            |
|                                                                              |
| Inspired By: Jonah Glick                                                     |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void chaseTheDot() {
  continuePattern = true;
  int animationSpeed = 100;
  
  int xpos = 0;
  int ypos = 0;
  int zpos = 0;
  
  while (continuePattern) {
    switch(random(0,6)) {
      case 0:
        if (xpos > 0) {xpos--;break;}
        else color=nextColor(color);
      case 1:
        if (xpos < 3) {xpos++;break;}
        else color=nextColor(color);
        xpos--; break;
        
      case 2:
        if (ypos > 0) {ypos--;break;}
        else color=nextColor(color);
      case 3:
        if (ypos < 3) {ypos++;break;}
        else color=nextColor(color);
        ypos--; break;
      
      case 4:
        if (zpos > 0) {zpos--;break;}
        else color=nextColor(color);
      case 5:
        if (zpos < 3) {zpos++;break;}
        else color=nextColor(color);
        zpos--; break;
    }
    drawLed(color,xpos,ypos,zpos);
    flushBuffer();
    clearBuffer();
    delay(animationSpeed);
  }
}
/********************************* PLANAR FLOP ********************************\
| 
\******************************************************************************/
/******************************* PLANAR FLOP 3D *******************************\
| Version 2 of the planar flop, doing more complicated maths and 3D vectors    |
| 'n stuff. Making this function found the bug of reversed z axis line drawing |
\******************************************************************************/
void planarFlop3D() {
  continuePattern = true;
  int animationSpeed = 100;
  while (continuePattern) {
    
    for (int y = 3; y>0; y--){
      for (int z = 0; z < 4; z++) drawLine(color,0,3,z,3,y,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int x = 3; x > 0; x--) {
      for (int z = 0; z < 4; z++) drawLine(color,0,3,z,x,0,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    
    
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 4; y++) drawLine(color,0,y,0,x,y,3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int z = 3; z > 0; z--) {
      for (int y = 0; y < 4; y++) drawLine(color,0,y,0,3,y,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    
    for (int z = 0; z < 3; z++) {
      for (int x = 0; x < 4; x++) drawLine(color,x,0,0,x,3,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int y = 3; y > 0; y--) {
      for (int x = 0; x < 4; x++) drawLine(color,x,0,0,x,y,3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    
    for (int y = 0; y < 3; y++) {
      for (int z = 0; z < 4; z++) drawLine(color,3,0,z,0,y,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int x = 0; x < 3; x++) {
      for (int z = 0; z < 4; z++) drawLine(color,3,0,z,x,3,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    
    for (int x = 3; x > 0; x--) {
      for (int y = 0; y < 4; y++) drawLine(color,3,y,3,x,y,0);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int z = 0; z < 3; z++) {
      for (int y = 0; y < 4; y++) drawLine(color,3,y,3,0,y,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    
    for (int z = 3; z > 0; z--) {
      for (int x = 0; x < 4; x++) drawLine(color,x,3,3,x,0,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    } 
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 4; x++) drawLine(color,x,3,3,x,y,0);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    color = nextColor(color);


    
  }
}
