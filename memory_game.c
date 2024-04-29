
#include <TimerOne.h>

#define DiodaZutaPin 13
#define DiodaZelena1Pin 12
#define DiodaZelena2Pin 11
#define DiodaZelena3Pin 10
#define DiodaZelena4Pin 9
#define DiodaZelena5Pin 8
#define DiodaCrvenaPin 7

#define ButtonPin1 2
#define ButtonPin2 3
#define ButtonPin3 4
#define ButtonPin4 5

int DiodaZutaStatus = LOW;
int DiodaZelena1Status = LOW;
int DiodaZelena2Status = LOW;
int DiodaZelena3Status = LOW;
int DiodaZelena4Status = LOW;
int DiodaZelena5Status = LOW;
int DiodaCrvenaStatus = LOW;

int Button3State;
int Button4State;
int OldStateButton1 = HIGH;
int OldStateButton2 = HIGH;
int OldStateButton3 = HIGH;
int OldStateButton4 = HIGH;

int errorCounter;
int sekvenca;
int sekvencaArray[100];
int currIndex;
bool crvenaShoudBlink;
unsigned long lastDebounceTime;
unsigned long debounceDelay;

typedef enum {
    presentation,
    playing,
    gameOver
  } GameState;

GameState state;


void setup()
{
 
  Serial.begin(9600);

  pinMode(DiodaZutaPin, OUTPUT);
  pinMode(DiodaZelena1Pin, OUTPUT);
  pinMode(DiodaZelena2Pin, OUTPUT);
  pinMode(DiodaZelena3Pin, OUTPUT);
  pinMode(DiodaZelena4Pin, OUTPUT);
  pinMode(DiodaZelena5Pin, OUTPUT);
  pinMode(DiodaCrvenaPin, OUTPUT);
  
  pinMode(ButtonPin1, INPUT);
  pinMode(ButtonPin2, INPUT);
  pinMode(ButtonPin3, INPUT);
  pinMode(ButtonPin4, INPUT);
  
  digitalWrite(DiodaZutaPin, DiodaZutaStatus);
  digitalWrite(DiodaZelena1Pin, DiodaZelena1Status);
  digitalWrite(DiodaZelena2Pin, DiodaZelena2Status);
  digitalWrite(DiodaZelena3Pin, DiodaZelena3Status);
  digitalWrite(DiodaZelena4Pin, DiodaZelena4Status);
  digitalWrite(DiodaZelena5Pin, DiodaZelena5Status);
  digitalWrite(DiodaCrvenaPin, DiodaCrvenaStatus);
  
  digitalWrite(ButtonPin1, OldStateButton1);
  digitalWrite(ButtonPin2, OldStateButton2);
  digitalWrite(ButtonPin3, OldStateButton3);
  digitalWrite(ButtonPin4, OldStateButton4);
  
 
  attachInterrupt(digitalPinToInterrupt(ButtonPin1), pressButton1, FALLING);
  attachInterrupt(digitalPinToInterrupt(ButtonPin2), pressButton2, FALLING);

  sekvenca = 2;
  currIndex = 0;
  errorCounter = 0;
  state = presentation;
  lastDebounceTime = 0;
  debounceDelay = 50;
  sekvencaArray[0] = random(9,13);
  sekvencaArray[1] = random(9,13);
}


void buttonPressedLogic(int i){
  
  if(state == playing){
    
   if(sekvencaArray[currIndex] != i)
      
    {
      //error happened
      if(errorCounter < 3){
      
        crvenaShoudBlink = true;
        currIndex = 0;
        errorCounter++;
        
      }
      else if(errorCounter >= 3){
       state = gameOver;       
      }
      
     
    }
    if (sekvencaArray[currIndex] == i){
      
      //right button is clicked

      blinkDioda(8);
      currIndex++;

      if(currIndex == sekvenca){
       state = presentation; 
       sekvenca ++;
       errorCounter = 0;
       currIndex = 0;
      }     
       
    }

     
    
  }
 
}


void blinkDioda(int dioda) {
 
digitalWrite(dioda,HIGH);
digitalWrite(dioda,LOW);
}

void pressButton1() {
  buttonPressedLogic(12);
  
}
void pressButton2() {
  buttonPressedLogic(11);
}

void loop()
{
  

  if (crvenaShoudBlink) {
    blinkDioda(7);
    crvenaShoudBlink = false;
  }
  
  
  Button3State = digitalRead(ButtonPin3);
  Button4State = digitalRead(ButtonPin4);

  if(state == playing && Button3State != OldStateButton3){
    if(millis() - lastDebounceTime > debounceDelay){
        lastDebounceTime = millis();

    	if(Button3State == LOW){
      	Button3State = HIGH;
      	buttonPressedLogic(10);
      
     }
     
    }
    
    
  }

  if(state == playing && Button4State != OldStateButton4){
    if(Button4State == LOW) {
      
      if(millis() - lastDebounceTime > debounceDelay){
      lastDebounceTime = millis();
      
      Button4State = HIGH;
      buttonPressedLogic(9);
      }
     
      
    }
            
    
  }
  
  
  
  
  switch (state) {
    case presentation:
      
      digitalWrite(DiodaZutaPin, LOW); 
      digitalWrite(DiodaCrvenaPin, LOW); 
      randomSeed(analogRead(A0));
      
     sekvencaArray[sekvenca] = random(9,13);
     static unsigned long previousMillis = 0;
    
      for(int i = 0; i < sekvenca; i++ )
    	{
        
        unsigned long currentMillis = millis();
       
        if(currentMillis - previousMillis >= 500){
         previousMillis = currentMillis;
   
      	blinkDioda(sekvencaArray[i]);
        
          
        }else{
         i--;   
        }
        
      	   
      
    	}
    
        
	  state = playing;
      
      break;
    case playing:
    	
     digitalWrite(DiodaZutaPin,HIGH);
        
   
    
    
      break;
    case gameOver:
    digitalWrite(DiodaCrvenaPin,HIGH);
    digitalWrite(DiodaZutaPin,LOW);


       currIndex = 0;
       errorCounter = 0;
       sekvenca = 2;
     
      break;
  }
	
  
      
}


  