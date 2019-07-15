// Create by Yejia Hao
// 20190424
#include <DFRobot_BMI160.h>
#include <math.h>

DFRobot_BMI160 bmi160;
const int8_t i2c_addr = 0x69;
int buttonPin = 10; //This is the pin number of button
int motorPin = 11;  //The pin of motor
static float initPosition[3] = {0};
float currentPosition[3] = { 0 };
int timeDura = 0;
int timeInit = 0;
static float overLoadDegree = 30; //The warning degree of lowering the head
static float degree = 0;
boolean buttonPressed = false;

int interruptPeriod = 2000; //The frequency of executing the interrupt. In unit ms.
int interruptTime = 0;
int nowTime = 0;
int overLoadTime = 5 * interruptPeriod;  //In milliseconds. The maximum time that is allowed to overcome the lowering head degree
int overLoadCounter = 0; //The counter of the times of overloading the degree limit.

static float overLoadKey = overLoadDegree * overLoadTime;
static float accumulateKey = 0;

void setup()
{
	Serial.begin(115200);
	delay(100);
	interruptTime = interruptPeriod; //initiallize the first interrupt
  
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

void loop()
{  
	digitalWrite(9, HIGH); // The LED on pin 9 as "working" LED
	int i = 0;
	int rslt;
	int16_t accelGyro[6]={0}; 
	float accel[3] = {0}; //Use accel[3] to store accleration data for now. It's possible it needs to reconstruct if I failed to let a function return array. In this worst case, I have to write all the correction algorithm in the mian file. 
	float accelCorrected[3] = {0};
	int buttonState = 0;
	rslt = bmi160.getAccelGyroData(accelGyro);
	
  if (degree<overLoadDegree)
  {
    digitalWrite(motorPin,LOW);
  }
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
		initPosition[0] = accel[0];
		initPosition[1] = accel[1];
		initPosition[2] = accel[2];
		delay(50);
		Serial.println("initposition Recorded");
		digitalWrite(LED_BUILTIN, LOW);
		overLoadCounter = 0;
	}

	//Calculate the degree of lowering head
	degree = calcLoweringDeg(initPosition, accel);
	Serial.print(degree);Serial.print("\t");
	Serial.println();


	//Decide whether to vibrate to set a caution
	//Use millis() to simulate the function of timer interrupt
	//Check https://www.arduino.cn/thread-2890-1-1.html
	nowTime = millis();
	if (nowTime > interruptTime)
	{
		if (degree >= overLoadDegree) 
		{
			overLoadCounter = overLoadCounter + 1;
			if (overLoadCounter * interruptPeriod > overLoadTime) 
			{
				digitalWrite(motorPin, HIGH);
			}
			else {}
		}
		else
		{
			digitalWrite(motorPin, LOW);
		}
		interruptTime = nowTime + interruptPeriod;
	}
	
	
	//delay(100);
}

float calcLoweringDeg(float initAccel[3], float currentAccel[3])
{
	float dot = (initAccel[0] * currentAccel[0]) + (initAccel[1] * currentAccel[1]) + (initAccel[2] * currentAccel[2]);
	float mod1 = sqrt(initAccel[0] * initAccel[0] + initAccel[1] * initAccel[1] + initAccel[2] * initAccel[2]);
	float mod2 = sqrt(currentAccel[0] * currentAccel[0] + currentAccel[1] * currentAccel[1] + currentAccel[2] * currentAccel[2]);
	float rslt = acos(dot / (mod1*mod2))*(180 / 3.141592);

	if (rslt < 0)
	{
		rslt = -1 * rslt;
		return rslt;
	}
	else
	{
		return rslt;
	}
}
