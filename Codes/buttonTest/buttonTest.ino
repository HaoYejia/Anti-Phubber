const int buttonPin = 10;


void setup()
{
  pinMode(buttonPin, INPUT);
}

void loop(){
  int rslt = checkButtonState(buttonPin);
  if(rslt == 0)
  {
    Serial.print("OFF");
    Serial.println();
  }
  else if(rslt == 1)
  {
    Serial.print("ON");
    Serial.println();
  }
  else
  {
    Serial.print("ERR");
    Serial.println();
  }
}
