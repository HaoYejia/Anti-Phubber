const int buttonPin = 10;
const int motorPin = 11;
int buttonState = 0;

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(motorPin, OUTPUT);
}
void loop()
{
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW)
  {
    digitalWrite(motorPin, HIGH);
  }
  else
  {
    digitalWrite(motorPin, LOW);
  }
}
