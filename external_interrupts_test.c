#include <lpc21xx.h>
#include "pin_function_defines.h"
#include "defines.h"
//#include "lcd_defines.h"
#include "lcd.h"
#include "kpm.h"
#include "global.h"
#include "i2c.h"
#include "i2c_eeprom.h"
#include "delay.h"
#define I2C_EEPROM_SA 0x50
extern int i_flag;
void SetPoint(void);


void eint0_isr(void) __irq
{
//	IODIR0|=1<<LED;
//	IOSET0=1<<LED;
	delay_ms(1000);
    //i_flag=1;
	SetPoint();
	SCLRBIT(EXTINT,0);//clear flag
	VICVectAddr=0;//dummy write;
}	

void Enable_EINT0(void)
{
	CFGPIN(PINSEL1,16,FUNC2);
//	CFGPIN(PINSEL1,0,FUNC2);
	SSETBIT(VICIntEnable,14);
	VICVectCntl1=0x20|14;
	VICVectAddr1=(unsigned)eint0_isr;
	
	//Enable EINT0 
	//SSETBIT(EXTINT,0) //default
	
	//EINT0 as EDGE_TRIG
  SETBIT(EXTMODE,0);
	//EINT0 as REDGE
  //SETBIT(EXTPOLAR,0);	
}	

void SetPoint(void)
{
    u32 num;
		u8 key;;
	  //setpoint=31;
	//i2c_eeprom_write(0x50,0x0000,setpoint);
	  Write_CMD_LCD(0x01);
	  Write_CMD_LCD(0x80);
      Write_str_LCD("Enter setpoint");
	  Write_CMD_LCD(0XC0);
	  ReadNum(&num,&key);
	  setpoint=num;	
	  Write_CMD_LCD(0x01);
	  i2c_eeprom_write(0x50,0x0000,setpoint);	 // i2c_eeprom_page_write(I2C_EEPROM_SA,0x00,&setpoint,8);
}
