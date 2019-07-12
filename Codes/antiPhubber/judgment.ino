void judgment()
{
	interruptCounter = interruptCounter + 1;
	Serial.print("Interrupt executed. This is interrupt number");Serial.print(interruptCounter);
	Serial.println();
	accumulateKey = accumulateKey + interruptTimel * degree;
	if (accumulateKey >= overLoadKey)
	{
		digitalWrite(motorPin, HIGH);
	}
	else
	{
		digitalWrite(motorPin, LOW);
	}
}
