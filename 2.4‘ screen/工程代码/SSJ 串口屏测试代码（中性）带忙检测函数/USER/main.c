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
	SystemInit();//��ʼ��RCC ����ϵͳ��ƵΪ72MHZ
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
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
		UartSend("DC32(0,0,'ϵͳ���ڿ���',1);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC24(0,32,'ģ���ͺ�JC22-V02',2);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("SBC(4);DCV24(0,56,'2.2��176X220�ֱ���',0);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,80,'֧�ֺ������л�',3);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,96,'��ʵ��ͼ����ӹ���',1);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("SBC(0);DCV16(0,112,'�������ȿ��Ե���',15);\r\n"); 
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
		UartSend("DC16(0,0,'ϵͳ���ڿ���',1);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,16,'ģ���ͺ�JC22-V02',2);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,32,'2.2��176X220�ֱ���',4);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,48,'֧�ֺ������л�',3);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("DC16(0,64,'��ʵ��ͼ����ӹ���',1);\r\n");
		CheckBusy();
		delay_ms(100);
		UartSend("SBC(15);DCV16(0,80,'�������ȿ��Ե���',0);\r\n"); 
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
		UartSend("CLR(0);DCV24(10,10,'BTN���ԣ�',0);BTN(10,40,48,24,'�¶�',0,1,1,4);BTN(10,72,48,24,'�¶�',1,1,1,4);BTN(10,112,48,24,'�¶�',2,1,1,4);BTN(10,152,48,24,'�¶�',4,1,1,4);BTN(10,192,48,24,'�¶�',12,3,1,4);\r\n"); 
		CheckBusy();
		
		UartSend("BTN(58,40,60,24,' 26��C',0,15,15,0);BTN(58,72,60,24,' 26��C',0,15,15,0);BTN(58,112,60,24,' 26��C',0,15,15,0);BTN(58,152,60,24,' 26��C',0,15,15,0);BTN(58,192,60,24,' 26��C',0,15,15,0);\r\n"); 
		CheckBusy();
		for(i=0;i<10;i++)
			delay_ms(6000);		
		UartSend("CLR(15);DIR(1);SBC(1);DC16(0,20,'д��flash��ֵ:44 55 66 79',1);\r\n");//100 is the start address
		CheckBusy();
		delay_ms(500);
		UartSend("PUT_VAR(110,44,55,66,79);DIR(1);\r\n");//100 is the start address
		CheckBusy();
		UartSend("GET_VAR(110);\r\n");//100 is the start address
		GetValue();
		CheckBusy();	
		sprintf(buf,"SBC(1);DIR(1);DCV16(0,58,'����flash��ֵ:%d %d %d %d',15);\r\n",val[0],val[1],val[2],val[3]);
		UartSend(buf);
		CheckBusy();
	for(i=0;i<3;i++)
			delay_ms(6000);

	}
	
	
 }

