
/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU Programme Demo ----------------------------*/
/* --- Fax: 86-755-82944243 ----------------------------------------*/
/* --- Tel: 86-755-82948412 ----------------------------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/

/*      本程序经过测试完全正常, 不提供电话技术支持, 如不能理解, 请自行补充相关基础.  */


/*************	本程序功能说明	**************
	测试方法：
	根据您的主时钟和波特率修改下面的相关定义，编译后下载到MCU。
	通过串口助手向MCU发送数据，MCU收到后原样返回。
	发单个字符'i'，将返回唯一ID号。
	发单个字符'r'，将返回内部震荡频率。
*/

 #include "stdio.h"
 #include "stdlib.h"
 #include "string.h"
// #include "cstdlib.h"
/*************** 用户定义参数 *****************************/

#define MAIN_Fosc	11059200L	//22118400L	//define main clock

#define Baudrate0		115200//9600//9600		//define the baudrate,
									//12T mode: 600~115200 for 22.1184MHZ, 300~57600 for 11.0592MHZ
									//1T  mode: 7200~1382400 for 22.1184MHZ, 3600~691200 for 11.0592MHZ

/**********************************************************/


#include	<reg51.h>

sfr	AUXR = 0x8E;

bit		B_TI;

unsigned char id[7];
unsigned long Rosc,RoscZ;
unsigned char Command;

void	uart0_init(void);


/****************** 编译器自动生成，用户请勿修改 ************************************/

//#define T1_TimerReload		(256 - MAIN_Fosc / 192 / Baudrate0)		//Calculate the timer1 reload value	at 12T mode
#define T1_TimerReload	(256 - MAIN_Fosc / 16 / Baudrate0)		//Calculate the timer1 reload value ar 1T mode

/**********************************************************/

void 	TxByte(unsigned char dat);
unsigned char HEX2DEC(unsigned char dat);
void	PrintStrings(unsigned char  *sts);

 #define name_to_str(name)  (#name)



  char *pstr[256]={"00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19",	
						"20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39",
						"40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59",
						"60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79",
						"80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99",	
						"100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116",
						"117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133",
						"134","135","136","137","138","139","140","141","142","143","144","145","146","147","148","149","150",
						"151","152","153","154","155","156","157","158","159","160","161","162","163","164","165","166","167",
						"168","169","170","171","172","173","174","175","176","177","178","179","180","181","182","183","184",
						"185","186","187","188","189","190","191","192","193","194","195","196","197","198","199","200","201",
						"202","203","204","205","206","207","208","209","210","211","212","213","214","215","216","217","218",
						"219","220","221","222","223","224","225","226","227","228","229","230","231","232","233","234","235",
						"236","237","238","239","240","241","242","243","244","245","246","247","248","249","250","251","252",
						"253","254","255",};


void	main(void)
{
	unsigned char i;
	unsigned int  j;
	unsigned char idata *p;
	char cmd[128]={0};
	unsigned char x=100;
	unsigned char y=40;
	unsigned char tdata=10;
	int number=1234;
//	char cmd[25];
	char ch[3];
	int k=345;

	p = 0xf1;
	for(i=0; i<7; i++)
	{
		id[i] = *p;
		p++;
	}
	
	Rosc = 0;
	for(p=0xf8; p<=0xfb; p++)	Rosc = (Rosc << 8) + *p;
	RoscZ = 0;
	for(p=0xfc; p>0; p++)	RoscZ = (RoscZ << 8) + *p;
	
	uart0_init();
   	PrintStrings("CLR(1);DCV24(10,10,'尚视界科技有限公司',3);\r\n");

	for(i=0;i<255;i++) 
	{
    	sprintf(cmd,"DCV32(%2d,%2d,\'%s\',3);\r\n",(int)x,(int)y,(char* )pstr[i]);
    	PrintStrings(cmd);
		for(j=0;j<16000;j++);
	
	}
//	 PrintStrings(ch);
	

	
}


unsigned char HEX2DEC(unsigned char dat)
{
	dat &= 0x0f;
	if(dat <= 9)	return (dat+'0');
	else			return (dat+55);
}

void TxByte(unsigned char dat)
{
	B_TI = 0;
	SBUF = dat;
	while(!B_TI)	;
	B_TI = 0;
}

/**********************************************/
void	PrintStrings(unsigned char  *sts)
{
    for (; *sts != 0; sts++)	TxByte(*sts);
}

void	uart0_init(void)
{
	PCON |= 0x80;		//UART0 Double Rate Enable
	SCON = 0x50;		//UART0 set as 10bit , UART0 RX enable
//	TMOD &= ~(1<<6);		//Timer1 Set as Timer, 12T
	TMOD = (TMOD & ~0x30) | 0x20;	//Timer1 set as 8 bits auto relaod
	AUXR |=  (1<<6);		//Timer1 set as 1T mode
	TH1 = T1_TimerReload;		//Load the timer
	TR1  = 1;
	ES  = 1;
	EA = 1;
}


/**********************************************/
void UART0_RCV (void) interrupt 4
{
	if(RI)
	{
		RI = 0;
		Command = SBUF;
	}

	if(TI)
	{
		TI = 0;
		B_TI = 1;
	}
}
