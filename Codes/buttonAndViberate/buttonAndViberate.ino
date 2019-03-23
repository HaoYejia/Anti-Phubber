const int buttonPin = 9; //the number of button pin
const int motorPin = 10; //teh number of motor pin

int buttonState = 0;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;  //For Debounce
unsigned long debounceDelay = 50;    //For Debounce

void setup() {
  // put your setup code here, to run once:
  pinMode (buttonPin, INPUT);
  pinMode (motorPin, OUTPUT);
  pinMode (LED_BUILTIN, OUTPUT);


}

void loop() {
  nowButtonState = digitalRead (buttonPin);

  if (nowButtonState != lastButtonState) {  //when it's TRUE, the button is bouncing
    lastDebounceTime = millis(); //reset the timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) { //check again the state of the button  
    if (nowButtonState != buttonState) {
      buttonState = nowButtonState;
      
      if (buttonState == HIGH){
        digitalWrite (motorPin, HIGH);
      }
      else if (buttonState == LOW){
        digitalWrite (motorPin, LOW);
      }
      else { //to alaert if there is anything unexcepted
        digitalWrite(LED_BUILTIN, HIGH);   
        delay(1000);                       
        digitalWrite(LED_BUILTIN, LOW);    
        delay(1000);
      }
     }
    }
  }
  
  

}
