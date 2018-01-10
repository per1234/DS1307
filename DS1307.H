/*DS1307.h - Simple  Arduino Library For Interdacing DS1307 RTC Module With Arduino Using I2C protocol

*/

#ifndef DS1307_h
#define DS1307_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif
#define DS1307_ADDRESS 0x68

class DS1307
{



 public:
   boolean MODE;
   DS1307();
   void begin();
   byte Dec_To_BCD(byte dec);
   byte BCD_To_Dec(byte BCD);   
   void setTime(byte SEC, byte MIN, byte HOUR, byte DOW, byte DOM, byte MONTH, byte YEAR);
   void getAll(byte *SEC, byte *MIN, byte *HOUR,byte *DOW,byte *DOM, byte *MONTH, byte      *YEAR);
   void getTime(byte *SEC, byte *MIN, byte *HOUR);
   void getDate(byte *DOM, byte *MONTH, byte *YEAR);
   byte getSecond();
   byte getMinute();
   byte getHour();
   byte getWeek();
   byte getDay();
   byte getMonth();
   byte getYear();
   String getAllStr();
   String getTimeStr();
   String getDateStr();
   String getWeekStr();
   void Mode12();
   void Mode24();

};
#endif
