#include "DFRobot_BMI160.h"

DFRobot_BMI160 bmi160;
const int8_t i2c_addr = 0x69;
int ledPin=9;
float Gyro_abs[3][35]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//accelX/Y/Z,GyroX/Y/Z
float Gyro_buf[3][35]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
float accel_abs[3][5]={{0,0,0,0,0},
                       {0,0,0,0,0},
                       {0,0,0,0,0}};
float aG_step[6]={0,0,0,0,0,0};
float aG_now[6]={0,0,0,0,0,0};
float aG_last[6]={0,0,0,0,0,0};
float aG_ave[6]={0,0,0,0,0,0};
boolean shakeFlag=0;
boolean singleFlag=0;
boolean doubleFlag=0;
boolean doubleState=0;
boolean count_begin=0;
boolean noState=1;
boolean ledState=1;
byte count_times=0;
byte state=0b00000000;

void setup(){
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
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

float* readDat()
{
   int i = 0;
  int rslt;
  int16_t accelGyro[6]={0}; 
  float dat[6]={0};
  //get both accel and gyro data from bmi160
  //parameter accelGyro is the pointer to store the data
  rslt = bmi160.getAccelGyroData(accelGyro);
  if(rslt == 0){
    for(i=0;i<6;i++){
      if (i<3){
        //the first three are gyro datas
        dat[i]=accelGyro[i]*3.14/180.0;
        Serial.print(dat[i]);Serial.print("\t");
      }else{
        //the following three data are accel datas
        dat[i]=accelGyro[i]/16384.0;
        Serial.print(dat[i]);Serial.print("\t");
      }
    }
    Serial.println();
  }else{
    Serial.println("err");
  }
  return dat;
}

void processingDat(float *addr)
{
  byte x,y,z;
  //Serial.print("step:");
  for(x=0;x<6;x++)
  {
    aG_now[x]=addr[x];
    aG_step[x]=aG_now[x]-aG_last[x];
    aG_step[x]=abs(aG_step[x]);
    //Serial.print(aG_step[x]);
    //Serial.print("\t");
    aG_last[x]=aG_now[x];
   }
   //Serial.println();
  for(x=0;x<3;x++)
  {
    for(y=0;y<34;y++)
    {
      Gyro_abs[x][y]=Gyro_abs[x][y+1];
      Gyro_buf[x][y]=Gyro_abs[x][y+1];
      }
    }
  for(x=0;x<3;x++)
  {
    Gyro_abs[x][34]=aG_step[x];
    Gyro_buf[x][34]=aG_step[x];
   }

  for(x=0;x<3;x++)
  {
    for(y=0;y<4;y++)
    {
      accel_abs[x][y]=accel_abs[x][y+1];
      }
    }
  for(x=0;x<3;x++)
  {
    accel_abs[x][4]=aG_step[x+3];
    }
    
  for(x=0;x<3;x++)
  {
    for(y=0;y<35;y++)
    {
      if(Gyro_buf[x][y]>=0.35)
      {
        Gyro_buf[x][y]=0.35;
        }
      }
    aG_ave[x]=(Gyro_buf[x][0]+Gyro_buf[x][1]+Gyro_buf[x][2]+Gyro_buf[x][3]+Gyro_buf[x][4]+
               Gyro_buf[x][5]+Gyro_buf[x][6]+Gyro_buf[x][7]+Gyro_buf[x][8]+Gyro_buf[x][9]+
               Gyro_buf[x][10]+Gyro_buf[x][11]+Gyro_buf[x][12]+Gyro_buf[x][13]+Gyro_buf[x][14]+
               Gyro_buf[x][15]+Gyro_buf[x][16]+Gyro_buf[x][17]+Gyro_buf[x][18]+Gyro_buf[x][19]+
               Gyro_buf[x][20]+Gyro_buf[x][21]+Gyro_buf[x][22]+Gyro_buf[x][23]+Gyro_buf[x][24]+
               Gyro_buf[x][25]+Gyro_buf[x][26]+Gyro_buf[x][27]+Gyro_buf[x][28]+Gyro_buf[x][29]+
               Gyro_buf[x][30]+Gyro_buf[x][31]+Gyro_buf[x][32]+Gyro_buf[x][33]+Gyro_buf[x][34])/35;
    }
}

void checkShake()
{
  if(aG_ave[0]>=0.30||aG_ave[1]>=0.30||aG_ave[2]>=0.30)
  {
    shakeFlag=1;
    clearBeat();
    }
  else
  {
    shakeFlag=0;
    }

  if(shakeFlag==1)
  {
    digitalWrite(ledPin,LOW);
    ledState=0;
    }
  else
  {
    if(doubleState==0)
    {
      digitalWrite(ledPin,HIGH);
      ledState=1;
      }
    } 
}

void doubleAction()
{
  if(doubleFlag==1)
  {
    doubleFlag=0;
    if(ledState)
    {
      ledState=0;
      }
    else
    {
     ledState=1;    
      }
    digitalWrite(ledPin,ledState);
    }
  }

void checkBeat()
{
  if(shakeFlag==0)
  {
    if((((aG_step[0]>=0.2)||(aG_step[1]>=0.2)||(aG_step[2]>=0.2))
        &&((aG_step[3]>=0.04)||(aG_step[4]>=0.04)||(aG_step[5]>=0.04)))
        ||((aG_step[3]>=0.05)||(aG_step[4]>=0.05)||(aG_step[5]>=0.05)))
        {
          state=state<<1;
          state=state|0b00000001;

          if((noState==1)&&(singleFlag==0))
          {
            singleFlag=1;
            count_begin=1;
            noState=0;
            }

          else if((noState==1)&&(singleFlag==1))
          {
            doubleFlag=1;
            doubleState=~doubleState;
            singleFlag=0;
            doubleAction();
            count_begin=0;
            count_times=0;
            noState=0;
            }
          }
    else
    {
      state=state<<1;
      if((state&0b00001111)==0b00000000)
      {
        noState=1;
        }
      }
    }
//Serial.println("beat"); 
  }

void clearBeat()
{
  doubleFlag=0;
  singleFlag=0;
  count_begin=0;
  count_times=0;
  }

boolean checkGyro()
{
  float a=0.0,b=0.0,c=0.0;
  byte x=0;
  boolean flag=0;
  for(x=0;x<3;x++)
  {
    aG_ave[x]=(accel_abs[x][3]+accel_abs[x][2]+accel_abs[x][1]+accel_abs[x][0])/4;
    }
    a=accel_abs[0][4]-aG_ave[0];
    b=accel_abs[1][4]-aG_ave[1];
    c=accel_abs[2][4]-aG_ave[2];
  if((a>=0.5)||(b>=0.5)||(c>=0.5))
  {
    flag=1;
    }
  return flag;
  }

void countPlus()
{
  if(count_begin==1)
  {
    count_times++;
    if((count_times>=4)&&(count_times<=20))
    {
      if((noState==0)&&(singleFlag==1)&&(checkGyro()))
      {
        doubleFlag=1;
        if(doubleState)
        {
          doubleState=0;
          }
        else
        {
          doubleState=1;
          }
        doubleAction();
        singleFlag=0;
        count_begin=0;
        count_times=0;
        noState=0;
        }
      }
     if(count_times>20)
     {
      clearBeat();
      }
    }
    //Serial.println("plus"); 
  }

void loop(){  
  processingDat(readDat());
  checkShake();
  checkBeat();
  countPlus();
}
