/*DS1307.h - Simple  Arduino Library For Interdacing DS1307 RTC Module With Arduino Using I2C protocol

*/

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "Wire.h"
#include "DS1307.h"
#define DS1307_ADDRESS 0x68

DS1307::DS1307(){
MODE = false;
}
void DS1307::begin(){
Wire::begin();
Wire::beginTransmission(DS1307_ADDRESS);
Wire::write(0); 
Wire::endTransmission();
}
byte DS1307::Dec_To_BCD(byte dec){
      return( (dec/10*16) + (dec%10) );
    }
byte DS1307::BCD_To_Dec(byte BCD){
      return( (BCD/16*10) + (BCD%16) );
    }

void DS1307::setTime(byte SEC, byte MIN, byte HOUR, byte DOW, byte DOM, byte MONTH, byte YEAR)
    {
    
      Wire::beginTransmission(DS1307_ADDRESS);
      Wire::write(0);
      Wire::write(Dec_To_BCD(SEC)); 
      Wire::write(Dec_To_BCD(MIN)); 
      Wire::write(Dec_To_BCD(HOUR)); 
      Wire::write(Dec_To_BCD(DOW)); 
      Wire::write(Dec_To_BCD(DOM)); 
      Wire::write(Dec_To_BCD(MONTH)); 
      Wire::write(Dec_To_BCD(YEAR));  
      Wire::endTransmission();
    }
void DS1307::getAll(byte *SEC, byte *MIN, byte *HOUR,byte *DOW,byte *DOM, byte *MONTH, byte *YEAR)
    {
      Wire::beginTransmission(DS1307_ADDRESS);
      Wire::write(0); 
      Wire::endTransmission();
      Wire::requestFrom(DS1307_ADDRESS, 7);
     
      *SEC   = BCD_To_Dec(Wire.read()&0x7f);
      *MIN   = BCD_To_Dec(Wire.read());
      *HOUR  = BCD_To_Dec(Wire.read()&0x3f);
      *DOW   = BCD_To_Dec(Wire.read());
      *DOM   = BCD_To_Dec(Wire.read());
      *MONTH = BCD_To_Dec(Wire.read());
      *YEAR  = BCD_To_Dec(Wire.read());
    }

void DS1307::getTime(byte *SEC, byte *MIN, byte *HOUR)
    {
      Wire::beginTransmission(DS1307_ADDRESS);
      Wire::write(0); 
      Wire::endTransmission();
      Wire::requestFrom(DS1307_ADDRESS, 7);
     
      *SEC   = BCD_To_Dec(Wire.read()&0x7f);
      *MIN   = BCD_To_Dec(Wire.read());
      *HOUR  = BCD_To_Dec(Wire.read()&0x3f);
    }


void DS1307::getDate(byte *DOM, byte *MONTH, byte *YEAR)
    {
      Wire.beginTransmission(DS1307_ADDRESS);
      Wire.write(4); 
      Wire.endTransmission();
      Wire.requestFrom(DS1307_ADDRESS, 7);
     
      *DOM   = BCD_To_Dec(Wire.read());
      *MONTH = BCD_To_Dec(Wire.read());
      *YEAR  = BCD_To_Dec(Wire.read());
    }

 byte DS1307::getSecond()
    {
      Wire::beginTransmission(DS1307_ADDRESS);
      Wire::write(0); 
      Wire::endTransmission();
      Wire::requestFrom(DS1307_ADDRESS, 7);
     
      return(BCD_To_Dec(Wire.read()&0x7f));
    }

 byte DS1307::getMinute()
    {
      Wire::beginTransmission(DS1307_ADDRESS);
      Wire::write(1); 
      Wire::endTransmission();
      Wire::requestFrom(DS1307_ADDRESS, 7);
     
      return(BCD_To_Dec(Wire.read()));
    }

 byte DS1307::getHour()
    {
      Wire::beginTransmission(DS1307_ADDRESS);
      Wire::write(2); 
      Wire::endTransmission();
      Wire::requestFrom(DS1307_ADDRESS, 7);
     
      return(BCD_To_Dec(Wire.read()&0x3f));
    }

 byte DS1307::getWeek()
    {
      Wire::beginTransmission(DS1307_ADDRESS);
      Wire::write(3); 
      Wire::endTransmission();
      Wire::requestFrom(DS1307_ADDRESS, 7);
     
      return(BCD_To_Dec(Wire.read()));
    }

 byte DS1307::getDay()
    {
      Wire::beginTransmission(DS1307_ADDRESS);
      Wire::write(4); 
      Wire::endTransmission();
      Wire::requestFrom(DS1307_ADDRESS, 7);
     
      return(BCD_To_Dec(Wire.read()));
    }

 byte DS1307::getMonth()
    {
      Wire::beginTransmission(DS1307_ADDRESS);
      Wire::write(5); 
      Wire::endTransmission();
      Wire::requestFrom(DS1307_ADDRESS, 7);
     
      return(BCD_To_Dec(Wire.read()));
    }

 byte DS1307::getYear()
    {
      Wire::beginTransmission(DS1307_ADDRESS);
      Wire::write(6); 
      Wire::endTransmission();
      Wire::requestFrom(DS1307_ADDRESS, 7);
     
      return(BCD_To_Dec(Wire.read()));
    }

    

 String DS1307::getAllStr()
    {
      String ALL;
      byte SEC, MIN, HOUR,AM_PM,DOW, DOM, MONTH, YEAR;
      
      getAll(&SEC, &MIN, &HOUR,&DOW,&DOM, &MONTH,&YEAR);
      if(!MODE)
      {
      if (HOUR<10)
      ALL=String('0')+String(HOUR, DEC)+String(':');
      else
      ALL=String(HOUR, DEC)+String(':');
      if (MIN<10)
      ALL+=String('0');ALL+=String(MIN, DEC);
      ALL+=String(':');
      if (SEC<10)
      ALL+=String('0');ALL+=String(SEC, DEC);
      }
      else 
      {
      AM_PM=HOUR;
      if(HOUR>12)
      HOUR-=12;
      if (HOUR<10)
      ALL=String('0')+String(HOUR, DEC)+String(':');
      else
      ALL=String(HOUR, DEC)+String(':');
      if (MIN<10)
      ALL+=String('0');ALL+=String(MIN, DEC);
      ALL+=String(':');
      if (SEC<10)
      ALL+=String('0');ALL+=String(SEC, DEC);
      ALL+=String(' ');
      if(AM_PM>12)ALL+=String("PM");
      else ALL+=String("AM"); 
      }
      ALL+=String(' ');
      if (DOM<10)
      ALL+=String('0');ALL+=String(DOM, DEC);
      ALL+=String('/');
      if (MONTH<10)
      ALL+=String('0');ALL+=String(MONTH, DEC);
      ALL+=String('/');ALL+=String(YEAR, DEC);
      ALL+=String(' ');
      
      switch(DOW)
      {
      case 1:ALL+=String("Sunday");break;
      case 2:ALL+=String("Monday");break;
      case 3:ALL+=String("Tuesday");break;
      case 4:ALL+=String("Wednesday");break;
      case 5:ALL+=String("Thursday");break;
      case 6:ALL+=String("Friday");break;
      case 7:ALL+=String("Saturday");break;    
      }
      return(ALL);
    }



String DS1307::getTimeStr()
    {
      String ALL;
      byte SEC, MIN, HOUR,AM_PM;
      
      getTime(&SEC, &MIN, &HOUR);
      if(!MODE)
      {
      if (HOUR<10)
      ALL=String('0')+String(HOUR, DEC)+String(':');
      else
      ALL=String(HOUR, DEC)+String(':');
      if (MIN<10)
      ALL+=String('0');ALL+=String(MIN, DEC);
      ALL+=String(':');
      if (SEC<10)
      ALL+=String('0');ALL+=String(SEC, DEC);
      }
      else 
      {
      AM_PM=HOUR;
      if(HOUR>12)
      HOUR-=12;
      if (HOUR<10)
      ALL=String('0')+String(HOUR, DEC)+String(':');
      else
      ALL=String(HOUR, DEC)+String(':');
      if (MIN<10)
      ALL+=String('0');ALL+=String(MIN, DEC);
      ALL+=String(':');
      if (SEC<10)
      ALL+=String('0');ALL+=String(SEC, DEC);
      ALL+=String(' ');
      if(AM_PM>12)ALL+=String("PM");
      else ALL+=String("AM"); 
      }
      
      return(ALL);
    }
        



String DS1307::getDateStr()
    {
      String ALL;
      byte DOM, MONTH, YEAR;
      
      getDate(&DOM, &MONTH,&YEAR);
    
      if (DOM<10)
      ALL+=String('0');ALL+=String(DOM, DEC);
      ALL+=String('/');
      if (MONTH<10)
      ALL+=String('0');ALL+=String(MONTH, DEC);
      ALL+=String('/');ALL+=String(YEAR, DEC);
      ALL+=String(' ');
      
      return(ALL);
    }


String DS1307::getWeekStr()
    {
      String ALL;
         
      switch(getWeek())
      {
      case 1:ALL+=String("Sunday");break;
      case 2:ALL+=String("Monday");break;
      case 3:ALL+=String("Tuesday");break;
      case 4:ALL+=String("Wednesday");break;
      case 5:ALL+=String("Thursday");break;
      case 6:ALL+=String("Friday");break;
      case 7:ALL+=String("Saturday");break;    
      }
      return(ALL);
    }  

