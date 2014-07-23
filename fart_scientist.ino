//Fart Scientist

//Variables
int fartSounds|| = {}; //Arduino will select a random track number from this array
int excuseSounds|| = {}; //Arduino will select a random track number from this array
int digestionSound;
int alarmSound;
int gulpSound;

unsigned long prevTime;
unsigned long intervalTime;
unsigned long currentTime;
int counterTick;
boolean flagNewTick;

boolean smallBallDetected;
boolean largeBallDetected;

boolean threeTick;

int smallSensorValue = 0;
int largeSensorValue = 0;

int esoLED = 12;
int stoLED = 9;
int sIntLED = 15;
int lIntLED = 12;

boolean eso;
boolean sto;
boolean sInt;
boolean lInt;

boolean gulpFlag;

int detectionThreshold; //Value that sensor output needs to fall below to trigger the ball detection flag

//Pins

const int smallBallDetector;
const int largeBallDetector;

void setup(){
  
  //Time setup
  prevTime = millis();
  intervalTime = 125;
  counterTick = 0;
  
  //Variable setup
  threeTick = false;
  smallBallDetected = false;
  largeBallDetected = false;
  
  eso = false;
  sto = false;
  sInt = false;
  lInt = false;
  
  gulpFlag = false;
  
  //Pinmode setup
  
  
  //Serial setup
  Serial.begin(9600);
}

void loop(){
  //Detect Balls
  
  if(!smallBallDetected && !largeBallDetected){
    smallSensorValue = analogRead(smallBallDetector);
    largeSensorValue = analogRead(largeBallDetector);
  }
  
  if(smallSensorValue < detectionThreshold){  //Small Ball conditional
    smallBallDetected = true;
    largeBallDetected = false;
  }
  
  if(largeSensor < detectionThreshold && !smallBallDetected){  //Large Ball conditional, only runs if the small ball has not been detected yet (safety mechanism)
    smallBallDetected = false;
    largeBallDetected = true;
  }
  
  if(smallBallDetected || largeBallDetected){
    currentTime = millis();
    flagNewTick = false;
  
    if(currentTime - prevTime >= intervalTime)
    {
      counterTick++;
      threeTick = false;
      prevTime = currentTime;
      flagNewTick = true;
    }
    
    // This part of the program will run for both types of balls
    closeMouth();
    
    if(esoLED > 0 && !eso){   //Conditional to make sure all the LEDs are not complete, flag is just a precaution
      runEso(); //Runs immediately after ball is dropped and mouth closed
    }else{
      eso = true;
    }
    
    if(counterTick == 8 && !gulpFlag){
      //Play gulp sound
      playSound(gulpSound);
      gulpFlag = true;
    }
    
    if(counterTick == 24){
      //Digestion MP3
      playSound(digestionSound);
      
      //Stomach LEDs
      sto = true;
    }
    
    if(sto){
      //Currently the Stomach LED string is being run
      runSto();
      
      if(stoLED == 0){
        sto = false;
      }
    }
    
    //This is where the program breaks into two
    
    if(smallBallDetected){
      //Small ball sequence -> Fart
      
      if(counterTick == 51){
        //Small Intestine LEDs
        sInt = true;
      }
      if(sInt){
        runSInt();
        if(sIntLED == 0){
          sInt = false;
        }
      }
      
      if(counterTick == 96){
        //Alarm MP3
        playSound(alarmSound);
        
        //Turn Large Intestine Red LEDs on until 104 ticks
        onLInt();
      }
      
      if(counterTick == 104){
        //Turn off Large Intestine Red LEDs
        offLInt();
      }
      
      if(counterTick == 132){
        //Play a random fart sound
        playRandomSound('f');
        
        //Turn the carousel
        turnCarousel();
      }
      
      if(counterTick == 136){
        turnCarousel();
      }
      
      if(counterTick == 140){
        turnCarousel();
      }
      if(counterTick == 144){
        //Play random excuse me sound
        playRandomSound('e');
        
        //Reset flags so that the program starts from the beginning of the loop
        resetFlags();
      }
        
    }else{
      //Large ball sequence -> Non Fart
      
      
    }
  }
 
}

//MP3 Shield Transient Noise Reducing Script

void killTrans(){
  //Procedure goes here - detailed in the Line Out PDF on Sparkfun
}


//Subroutines - Blank for now

void closeMouth(){
  
}

void runEso(){
  /* Code goes here
     use the variable esoLED to find out how many LEDs are left to activate
  */
  
  /* Code ends here */
  
  esoLED--;
}

void runSto(){
  /* Code goes here
  use the variable stoLED to find out how many LEDs are left to activate*/
  
  stoLED--;
}

void runSInt(){
  /* Code goes here
  use the variable stoLED to find out how many LEDs are left to activate*/
  
  sIntLED--;
}

void onLInt(){
  //Turn on all of the large intestine LEDs
}

void offLInt(){
  //Turn off all of the large intestine LEDs
}

void playSound(int file){
  killTrans();   //Required before every MP3 sound
  
  /* Sound playing code goes here */
  
  /* Code ends here */
  
}

void playRandomSound(char type){  //Type: e - excuse me sounds, f - fart sounds
  killTrans();
  
  if(type == 'e'){
    //Select and play random sound from array
  }else if(type == 'f'){
    //select and play random sound from array
  }
}

void turnCarousel(){
  /*Turn the carousel to drop the balls
  Stepper motor code goes here */
  
  /* End Code */
}

void resetFlags(){
  //Code to reset all flags goes here
  threeTick = false;
  smallBallDetected = false;
  largeBallDetected = false;
  
  eso = false;
  sto = false;
  sInt = false;
  lInt = false;
  
  gulpFlag = false;
}
