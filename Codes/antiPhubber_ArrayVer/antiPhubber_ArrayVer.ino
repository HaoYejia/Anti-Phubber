// Create by Yejia Hao
// 20190424

#include <DFRobot_BMI160.h>
#include <math.h>

DFRobot_BMI160 bmi160;
const int8_t i2c_addr = 0x69;
const static int buttonPin = 10; //This is the pin number of button
const static int motorPin = 11;
static float initPosition[3] = {0};
float currentPosition[3] = {0};

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
  pinMode(buttonPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void loop(){  
  int i = 0;
  int rslt;
  int16_t accelGyro[6]={0}; 
  float accelRaw[3] = {0};
  float accelCorrected[3] = {0};
  //get both accel and gyro data from bmi160
  //parameter accelGyro is the pointer to store the data
  rslt = bmi160.getAccelGyroData(accelGyro);
  
  if(rslt == 0)
  {
   accelRaw[0] = accelGyro[3]/16384.0;
   accelRaw[1] = accelGyro[4]/16384.0;
   accelRaw[2] = accelGyro[5]/16384.0;
  }
  else
  {
    Serial.println("err");
  }
  
//  Serial.print(accelRaw[0]);
//  Serial.print(accelRaw[1]);
//  Serial.print(accelRaw[2]);
//  Serial.println();
  

 //Recording the initial position of head
 if (checkButtonState(buttonPin) == 1)
 {
  delay(50);
  if (checkButtonState(buttonPin) == 1)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    initPosition[0]=accelRaw[0];
    initPosition[1]=accelRaw[1];
    initPosition[2]=accelRaw[2];
    digitalWrite(LED_BUILTIN, LOW);
  }
  else{}
 }
 else{}
 
  delay(100);
}
