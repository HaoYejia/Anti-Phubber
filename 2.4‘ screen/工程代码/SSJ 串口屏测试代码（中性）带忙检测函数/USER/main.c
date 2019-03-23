#include "delay.h"
#include "sys.h"
#include "usart.h"

						
extern unsigned char val[];
int main(void)
{	
	unsigned char i,k;
	unsigned char ret;
	char buf[128];
	unsigned char key=0xff;
	SystemInit();//初始化RCC 设置系统主频为72MHZ
	delay_init(72);	     //延时初始化
	uart_init(115200);	 //串口初始化为115200
	delay_ms(500);
	for(;;)
	{		
				for(k=255;k>0;k--)
		{
			sprintf(buf,"CLR(15);BL(%2d);\r\n",k);
			UartSend(buf);
			CheckBusy();	
			delay_ms(1);
		}	
		
		UartSend("BL(10);\r\n");
		CheckBusy();
		delay_ms(100);
	//	UartSend("CLR(0);SBC(15);DIR(1);FSIMG(2097152,0,0,220,176,0);FSIMG(2174592,0,0,220,176,0);DIR(1);SBC(10);\r\n");
		UartSend("CLR(0);SBC(15);DIR(1);FSIMG(2174592,0,0,220,176,0);DIR(1);SBC(10);\r\n");
		CheckBusy();
		UartSend("DC32(0,0,'系统正在开机',1);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC24(0,32,'模组型号JC22-V02',2);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("SBC(4);DCV24(0,56,'2.2寸176X220分辨率',0);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,80,'支持横竖屏切换',3);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,96,'能实现图层叠加功能',1);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("SBC(0);DCV16(0,112,'背光亮度可以调节',15);\r\n"); 
		CheckBusy();
		delay_ms(100);
		//UartSend("PS(10,10,14);\r\n");
	//	CheckBusy();		
		UartSend("PL(0,128,150,128,1);\r\n");
		CheckBusy();
		UartSend("BOXF(140,140,160,160,3);\r\n");
		CheckBusy();
		UartSend("BOX(150,150,170,170,1);\r\n");
		CheckBusy();		
		UartSend("CIRF(70,150,15,1);\r\n"); 
		CheckBusy();
		UartSend("CIRF(80,160,15,2);\r\n"); 
		CheckBusy();
		for(i=0;i<10;i++)
		delay_ms(60000);
	//	delay_ms(60000);
		UartSend("SBC(15);DIR(0);FSIMG(2097152,0,0,176,220,0);SBC(10);DIR(0);\r\n");
		CheckBusy();	
		UartSend("DC16(0,0,'系统正在开机',1);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,16,'模组型号JC22-V02',2);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,32,'2.2寸176X220分辨率',4);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,48,'支持横竖屏切换',3);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,64,'能实现图层叠加功能',1);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("SBC(15);DCV16(0,80,'背光亮度可以调节',0);\r\n"); 
		UartSend("PS(10,10,14);\r\n");
		CheckBusy();		
		UartSend("PL(0,100,150,100,1);\r\n");
		CheckBusy();
		UartSend("BOXF(130,130,150,150,3);\r\n");
		CheckBusy();
		UartSend("BOX(140,140,160,160,1);\r\n");
		CheckBusy();		
		UartSend("CIRF(70,150,15,1);\r\n"); 
		CheckBusy();
		UartSend("CIRF(80,160,15,2);\r\n"); 
		CheckBusy();
		for(i=0;i<10;i++)
		delay_ms(6000);
		UartSend("CLR(0);DCV24(10,10,'BTN测试：',0);BTN(10,40,48,24,'温度',0,1,1,4);BTN(10,72,48,24,'温度',1,1,1,4);BTN(10,112,48,24,'温度',2,1,1,4);BTN(10,152,48,24,'温度',4,1,1,4);BTN(10,192,48,24,'温度',12,3,1,4);\r\n"); 
		CheckBusy();
		
		UartSend("BTN(58,40,60,24,' 26°C',0,15,15,0);BTN(58,72,60,24,' 26°C',0,15,15,0);BTN(58,112,60,24,' 26°C',0,15,15,0);BTN(58,152,60,24,' 26°C',0,15,15,0);BTN(58,192,60,24,' 26°C',0,15,15,0);\r\n"); 
		CheckBusy();
		for(i=0;i<10;i++)
			delay_ms(6000);		
		UartSend("CLR(15);DIR(1);SBC(1);DC16(0,20,'写入flash的值:44 55 66 79',1);\r\n");//100 is the start address
		CheckBusy();
		delay_ms(500);
		UartSend("PUT_VAR(110,44,55,66,79);DIR(1);\r\n");//100 is the start address
		CheckBusy();
		UartSend("GET_VAR(110);\r\n");//100 is the start address
		GetValue();
		CheckBusy();	
		sprintf(buf,"SBC(1);DIR(1);DCV16(0,58,'读出flash的值:%d %d %d %d',15);\r\n",val[0],val[1],val[2],val[3]);
		UartSend(buf);
		CheckBusy();
	for(i=0;i<3;i++)
			delay_ms(6000);

	}
	
	
 }

