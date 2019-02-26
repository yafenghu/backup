#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xiomodule.h"
#define adlen 10
u32 var;
//u16 addb[adlen];
u32 addb[adlen];
u16 addn[adlen];
void testAD(void)
{	u16 din;
XIOModule iomodule;
XIOModule_Initialize(&iomodule, XPAR_IOMODULE_0_DEVICE_ID);
XIOModule_Start(&iomodule);
	din=XIOModule_IoReadHalfword(&iomodule, 0x1020);
	XIOModule_IoWriteHalfword(&iomodule, 0x1000, din);
}

void readAD(void)
{
	XIOModule iomodule;
	microblaze_enable_interrupts();//使能中断功能
	XIOModule_Initialize(&iomodule, XPAR_IOMODULE_0_DEVICE_ID);
	XIOModule_Start(&iomodule);
	u16 var;
	//u16 din;
	u32 din;
	u32 din1;
	for (var = 0; var<adlen; var++){
		//din=XIOModule_IoReadHalfword(&iomodule, 0x1020);//0x1020是AD的地址读16位数据
		din=XIOModule_IoReadWord(&iomodule, 0x1020);//0x1020是AD的地址，，，32位数据
		//addb[var]=din;
		//addb[var]=din;
		//addb[var]=din;
		//addb[var]=din;
		addb[var]=din;
		//din1=XIOModule_IoReadHalfword(&iomodule, 0x1050);//0x1050是Asagain的地址
		//addn[var]=din1;
//		XIOModule_IoWriteHalfword(&iomodule, 0x1000, addb[10]);
	}
}
void Uart_SendWord(Xint16 data)
{
    init_platform();
	XIOModule iomodule;
	microblaze_enable_interrupts();//使能中断功能
	XIOModule_Initialize(&iomodule, XPAR_IOMODULE_0_DEVICE_ID);
	XIOModule_Start(&iomodule);

	Xuint8 sdata[2]={0};
	*sdata=data>>8;
	*(sdata+1)=data;
	Xuint8 index=0;
	Xuint8 count;
	while (index < 2)
	{
		count = XIOModule_Send(&iomodule, &sdata[index], 2 - index);
		index += count;
	}
}

void Uart_SendDWord(Xint32 data1)
{
    init_platform();
	XIOModule iomodule;
	microblaze_enable_interrupts();//使能中断功能
	XIOModule_Initialize(&iomodule, XPAR_IOMODULE_0_DEVICE_ID);
	XIOModule_Start(&iomodule);

	Xuint8 sdata1[4]={0};
	*sdata1=data1>>24;
	*(sdata1+1)=data1>>16;
	*(sdata1+2)=data1>>8;
	*(sdata1+3)=data1;
	Xuint8 index=0;
	Xuint8 count;
	while (index < 4)
	{
		count = XIOModule_Send(&iomodule, &sdata1[index], 4 - index);
		index += count;
	}
}




int main()
{

    init_platform();
	XIOModule iomodule;
	microblaze_enable_interrupts();//使能中断功能
	XIOModule_Initialize(&iomodule, XPAR_IOMODULE_0_DEVICE_ID);
	XIOModule_Start(&iomodule);
	u32 din1;
	int k;
	//while(1)
	for(k=0;k<10;k++)
	{
    readAD();//执行一次，采样值为adlen个
	din1=XIOModule_IoReadHalfword(&iomodule, 0x1050);//0x1050是Asagain的地址

    //}
/*//////////////////////////////////////////////////////////边读边发测试XXXXXXX///////////////////////////////////////////////////////
		u16 var;
		u16 din;
		u16 din1;
		for (var = 0; var<adlen; var++){
			din=XIOModule_IoReadHalfword(&iomodule, 0x1020);//0x1020是AD的地址
		     Uart_SendWord(din);
		     Uart_SendWord(0xffff);
		}
	    Uart_SendWord(0xf0ff);
	    Uart_SendWord(0xf0ff);
	    Uart_SendWord(0xf0ff);
	    Uart_SendWord(0xf0ff);

*///////////////////////////////////////////////////边读边发测试XXXXXXXXXXXXX////////////////////////////////////////////////////////////
    int j;

    //if(j<adlen)
    //{
    //	Uart_SendDWord(addb[j]);

    //	j++;
    //}
    //if(din1 == 0xaaaaaaaa)
    //{
    //	j=0;
    //	din1=0;
    //}
   for(j = 0; j <adlen ; j++){//
     Uart_SendDWord(addb[j]);
     //Uart_SendWord(addn[j]);
     Uart_SendDWord(0xABCDefab);
//     Uart_SendWord(0)
      }
    Uart_SendWord(0xf0ff);
    Uart_SendWord(0xf0ff);
    Uart_SendWord(0xf0ff);
    Uart_SendWord(0xf0ff);
	}
	cleanup_platform();
	return 0;
}
