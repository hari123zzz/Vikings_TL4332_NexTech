#include <reg51.h>

sbit MS_supply = P2^0;
sbit MS = P2^1;
sbit IR_SENSOR_1 = P1^0;
sbit IR_SENSOR_2 = P1^1;

unsigned int entryCount = 0;
unsigned int exitCount = 0;
unsigned int k;
unsigned int d;
unsigned char c,e;

void delay(unsigned int x)
{
	while(x--);
}

void main() {
  
	  SCON=0X50;
		TMOD=0x21;
		TH0=0x3C;
		TL0=0xAF;
		TH1=0xFD;
		TL1=0xFD;
		TR0=1;
		TR1=1;
	  P0 = 0x00;
    IR_SENSOR_1 = 1;
    IR_SENSOR_2 = 1;

    while(1) {
			
		if(RI==1)
		{
			e=SBUF;
			RI=0;
			if(e=='1')
			{
				P0=0xFF;
				TR0=0;
				TH0=0x3C;
				TL0=0xAF;
				TR0=1;
				c=1;
			}
			else if(e=='0')
			{
				P0=0x00;
				c=0;
			}
		}
        if (!IR_SENSOR_1) { // Entry detected
					delay(30000);
					if (!IR_SENSOR_2){
						MS_supply = 1;
            entryCount++;
            
        }
				}
        else if (!IR_SENSOR_2) {
						delay(30000);
						if(!IR_SENSOR_1){
            exitCount++;
        }
				}
				k = entryCount - exitCount;
				
				if (exitCount > entryCount)
				{
					k=0;
				}
				if(c==1)
			{
				while(!TF0);
				TF0=0;
				TR0=0;
				d=d+1;
//				if(MS==0)
//				{
//					d=0;
//				}
				TH0=0x3C;
				TL0=0xAF;
				TR0=1;
				
				if(d>=560)
				{
					d=0;
					c=5;
				}
			}
				
				if(c==0)
				{
				if (k==0)
				{
					MS_supply = 0;
					P0 = 0x00;
				}
				else if (k!=0)
				{
					MS_supply = 1;
					TR0=0;
					if(MS==0)
					{
						P0 = 0xff;
					}
				}
			}
			
							
			if(c==5)
			{
				P0 = 0x00;
			}
				
		}
	}