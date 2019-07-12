// Create by Yejia Hao
// 20190424

#include <DFRobot_BMI160.h>
#include <math.h>
#include <MsTimer2.h>

DFRobot_BMI160 bmi160;
const int8_t i2c_addr = 0x69;
int buttonPin = 10; //This is the pin number of button
int motorPin = 11;  //The pin of motor
static float initPosition[3] = {0};
float currentPosition[3] = { 0 };
int timeDura = 0;
int timeInit = 0;
int overLoadTime = 5*1000;  //In milliseconds. The maximum time that is allowed to overcome the lowering head degree
float overLoadDegree = 30; //The warning degree of lowering the head
int overLoadCounter = 0;
float degree = 0;
boolean buttonPressed = false;

static const int interruptPeriod = 2000; //The frequency of executing the interrupt. In unit ms.
static float overLoadKey = overLoadDegree * overLoadTime;
static float accumulateKey = 0;
int interruptCounter = 0;
int interruptTimel = 1000;

void setup()
{
	Serial.begin(115200);
	delay(100);
  
	//init the hardware bmin160  
	if (bmi160.softReset() != BMI160_OK)
	{
		Serial.println("reset false");
		while(1);
	}
  
	//set and init the bmi160 i2c address
	if (bmi160.I2cInit(i2c_addr) != BMI160_OK)
	{
		Serial.println("init false");
		while(1);
	}

	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(buttonPin, INPUT);
	pinMode(motorPin, OUTPUT);
	pinMode(9, OUTPUT);
}

void loop(){  
	digitalWrite(9, HIGH); // The LED on pin 9 as "working" LED
	int i = 0;
	int rslt;
	int16_t accelGyro[6]={0}; 
	float accel[3] = {0}; //Use accel[3] to store accleration data for now. It's possible it needs to reconstruct if I failed to let a function return array. In this worst case, I have to write all the correction algorithm in the mian file. 
	float accelCorrected[3] = {0};
	int buttonState = 0;
	rslt = bmi160.getAccelGyroData(accelGyro);
	

  //Extract the acceleration data from the gyroscope
	if(rslt == 0)
	{
		/*
		16384 is the number that is required to covert the binary 
		data into the unit of "g", or "gravatational acceleration"
		*/
		accel[0] = accelGyro[3]/16384.0;  
		accel[1] = accelGyro[4]/16384.0;
		accel[2] = accelGyro[5]/16384.0;
	}
	else
	{
		Serial.println("err");
	}
 
	//Print test for the acceldata
	Serial.print(accel[0]);Serial.print("\t");
	Serial.print(accel[1]);Serial.print("\t");
	Serial.print(accel[2]);Serial.print("\t");
	Serial.println();
  

	//Recording the initial position of head
	buttonState = digitalRead(buttonPin);  //this button acts like soft reset
	if (buttonState == LOW)  //Activate the recording if the button is pressed
	{
		digitalWrite(LED_BUILTIN, HIGH);
		initPosition[0]=accel[0];
		initPosition[1]=accel[1];
		initPosition[2]=accel[2];
		delay(50);
		Serial.println("initposition Recorded");
		digitalWrite(LED_BUILTIN, LOW);
	
		timeDura = 0;
		buttonPressed = true;
	}
	else {}


	//Calculate the degree of lowering head
	degree = calcLoweringDeg(initPosition, accel);
	Serial.print(degree);Serial.print("\t");
	Serial.println();


	//Decide whether to vibrate to set a caution
	while (buttonPressed == true)
	{
		MsTimer2::set(interruptTimel,judgment);
		MsTimer2::start();
	}
	
	delay(100);
}

