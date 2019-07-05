void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write("CLR(1);\r\n");
  delay(100);
  Serial.write("CLR(15);\r\n");
}
