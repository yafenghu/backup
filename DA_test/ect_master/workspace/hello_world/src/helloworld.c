#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xiomodule.h"
#define adlen 66
u32 var;
u16 addb[adlen];
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
	microblaze_enable_interrupts();//ʹ���жϹ���
	XIOModule_Initialize(&iomodule, XPAR_IOMODULE_0_DEVICE_ID);
	XIOModule_Start(&iomodule);
	u16 var;
	u16 din;
	u16 din1;
	for (var = 0; var<adlen; var++){
		din=XIOModule_IoReadHalfword(&iomodule, 0x1020);//0x1020��AD�ĵ�ַ
		//din=XIOModule_IoReadHalfword(&iomodule, 0x1020);//0x1020��AD�ĵ�ַ
		//addb[var]=din;
		//addb[var]=din;
		//addb[var]=din;
		//addb[var]=din;
		addb[var]=din;
		//din1=XIOModule_IoReadHalfword(&iomodule, 0x1040);//0x1020��AD�ĵ�ַ
		//addn[var]=din1;
//		XIOModule_IoWriteHalfword(&iomodule, 0x1000, addb[10]);
	}
}
void Uart_SendWord(Xint16 data)
{
    init_platform();
	XIOModule iomodule;
	microblaze_enable_interrupts();//ʹ���жϹ���
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


int main()
{

    init_platform();
	XIOModule iomodule;
	microblaze_enable_interrupts();//ʹ���жϹ���
	XIOModule_Initialize(&iomodule, XPAR_IOMODULE_0_DEVICE_ID);
	XIOModule_Start(&iomodule);
	//while(1){
    readAD();//ִ��һ�Σ�����ֵΪadlen��
    //}
/*//////////////////////////////////////////////////////////�߶��߷�����XXXXXXX///////////////////////////////////////////////////////
		u16 var;
		u16 din;
		u16 din1;
		for (var = 0; var<adlen; var++){
			din=XIOModule_IoReadHalfword(&iomodule, 0x1020);//0x1020��AD�ĵ�ַ
		     Uart_SendWord(din);
		     Uart_SendWord(0xffff);
		}
	    Uart_SendWord(0xf0ff);
	    Uart_SendWord(0xf0ff);
	    Uart_SendWord(0xf0ff);
	    Uart_SendWord(0xf0ff);


*///////////////////////////////////////////////////�߶��߷�����XXXXXXXXXXXXX////////////////////////////////////////////////////////////


    u16 data;
    int j;
    Uart_SendWord(0xabab);
   for(j = 0; j < adlen; j++){
     Uart_SendWord(addb[j]);
     //Uart_SendWord(addn[j]);
     Uart_SendWord(0xffff);
//     Uart_SendWord(0);
     }
    Uart_SendWord(0xf0ff);
    Uart_SendWord(0xf0ff);//}
	cleanup_platform();
	return 0;
}