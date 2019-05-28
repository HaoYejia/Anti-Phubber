// Create by Yejia Hao
// 20190420

#include <DFRobot_BMI160.h>

DFRobot_BMI160 bmi160;
const int8_t i2c_addr = 0x69;
const int buttonPin = 10; //Define number of pin of the button
int loopCount = 0; //A counter for the number of loops
const int loopCountPre = 5; //The loop number that collect the 

void setup(){
  pinMode(buttonPin,INPUT);
  Serial.begin(115200);
  delay(100);
  
  //init the hardware bmin160  
  if (bmi160.softReset() != BMI160_OK){
    Serial.println("reset false");
    while(1);
  }
  
  //set and init the bmi160 i2c address
  if (bmi160.I2cInit(i2c_addr) != BMI160_OK){
    Serial.println("init false");
    while(1);
  }
}

void loop(){  
  int i = 0;
  int rslt;
  int16_t accelGyro[6]={0}; //cpp文件533行，规定传入参数格式为int16_t
  float accelRaw [3] = {0};float gyroRaw [3] = {0}; 
  float accelDelta [3] = {0};float gyroDelta [3] = {0}; //Zero-point deflection of IMU
  float accelCorrected [3] = {0}; float gyroCorrected [3] = {0}; //Corrected value of angle and accel
  
  //get both accel and gyro data from bmi160
  //parameter accelGyro is the pointer to store the data
  rslt = bmi160.getAccelGyroData(accelGyro); //wtf?
  
  if(rslt == 0){
    Serial.print(millis());Serial.print("\t"); //Serial print the timestamp, in milliseconds
    
    // Check the state of button and print it 
    if(digitalRead(buttonPin)==HIGH){
      Serial.print("OFF");Serial.print("\t"); 
   }
    if(digitalRead(buttonPin)==LOW){
      Serial.print("ON");Serial.print("\t"); //Check Apr 20th,2019 in the journal for the reason why HIGH for off and LOW for on
   }

       gyroRaw[0]=accelGyro[0]*3.14/180.0; //Don't know why, but this cannot be down with "for()", otherwise the accel data would never be got
       gyroRaw[1]=accelGyro[1]*3.14/180.0;
       gyroRaw[2]=accelGyro[2]*3.14/180.0;
       accelRaw[0] = accelGyro[3]/16384.0;
       accelRaw[1] = accelGyro[4]/16384.0;
       accelRaw[2] = accelGyro[5]/16384.0;

       

//print test of my version of output
       Serial.print(gyroRaw[0]); Serial.print("\t"); //DO NOT USE for(), or it'll not output sucessfully
       Serial.print(gyroRaw[1]); Serial.print("\t");
       Serial.print(gyroRaw[2]); Serial.print("\t");
       Serial.print(accelRaw[0]);Serial.print("\t");
       Serial.print(accelRaw[1]);Serial.print("\t");
       Serial.print(accelRaw[2]);Serial.print("\t");

      Serial.println();
      }

   else{
    Serial.println("err");
  }

  if(loopCount < loopCountPre){  //The first few loops are collecting the zero drift
    Serial.print("KEEP THE IMU STATIC");
  }

  delay(100);

  loopCount = loopCount +1;
  /*
   * //only read accel data from bmi160
   * int16_t onlyAccel[3]={0};
   * bmi160.getAccelData(onlyAccel);
   */

  /*
   * ////only read gyro data from bmi160
   * int16_t onlyGyro[3]={0};
   * bmi160.getGyroData(onlyGyro);
   */
}
