// Edit by Yejia Hao
// 20190420

#include <DFRobot_BMI160.h>

DFRobot_BMI160 bmi160;
const int8_t i2c_addr = 0x69;
void setup(){
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
  int16_t accelGyro[6]={0}; 
  
  //get both accel and gyro data from bmi160
  //parameter accelGyro is the pointer to store the data
  rslt = bmi160.getAccelGyroData(accelGyro); //wtf?
  
  if(rslt == 0){
    Serial.print(millis());Serial.print("\t"); //Serial print the timestamp, in milliseconds
//    for(i=0;i<6;i++){
//      Serial.print 
//    }
    for(i=0;i<6;i++){
      if (i<3){
        //the first three are gyro datas
        Serial.print(accelGyro[i]*3.14/180.0);Serial.print("\t");
      }
      else{
        //the following three data are accel datas
        Serial.print(accelGyro[i]/16384.0);Serial.print("\t");
      }
    }
    Serial.println();
  }else{
    Serial.println("err");
  }
  delay(100);
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
