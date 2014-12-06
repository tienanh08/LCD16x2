// http://tienanh.info
// Tien Anh
 void LCD_Enable(void)
{
 output_high(LCD_EN);
 delay_us(3);
 output_low(LCD_EN);
 delay_us(50); 
}

//Ham Gui 4 Bit Du Lieu Ra LCD
 void LCD_Send4Bit( unsigned char Data )
{
 output_bit(LCD_D4,Data&0x01);
 output_bit(LCD_D5,(Data>>1)&1);
 output_bit(LCD_D6,(Data>>2)&1);
 output_bit(LCD_D7,(Data>>3)&1);
}

// Ham Gui 1 Lenh Cho LCD
 void LCD_SendCommand (unsigned char command )
{
LCD_Send4Bit  ( command >>4 );/* Gui 4 bit cao */
LCD_Enable () ;
LCD_Send4Bit  ( command  );   /* Gui 4 bit thap*/
LCD_Enable () ;
}

void LCD_Init (void)
{

output_low(LCD_RS);
output_low(LCD_RW);
delay_ms(20);


LCD_Send4Bit(0x03);
LCD_Enable();
delay_ms(10);

LCD_Send4Bit(0x03);
LCD_Enable();
delay_ms(10);

LCD_Send4Bit(0x03);
LCD_Enable();
delay_ms(10);

LCD_Send4Bit(0x02);
LCD_Enable();
delay_ms(10);


LCD_SendCommand( 0x28 );      // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8   
                                 //Function Set: 8-bit, 1 Line, 5x7 Dots   0x30
                                 //Function Set: 8-bit, 2 Line, 5x7 Dots   0x38
                                 //Function Set: 4-bit, 1 Line, 5x7 Dots   0x20
                                 //Function Set: 4-bit, 2 Line, 5x7 Dots   0x28

LCD_SendCommand( 0x0C);    //Display on Cursor on: 0x0E   0x0F 
                               //Display on Cursor off: 0x0C
                               //Display on Cursor blinking: 0x0F
LCD_SendCommand( 0x06 );   // tang ID, khong dich khung hinh         Entry Mode

LCD_SendCommand( 0x01 );   //  Clear Display  (also clear DDRAM content)

}
 
void LCD_PutChar ( unsigned char Data )
{
 output_high(LCD_RS);
 LCD_SendCommand( Data );
 output_low(LCD_RS);
}

void LCD_Puts (char *s)
{
   while (*s)
   {
      LCD_PutChar(*s);
      s++;
   }
}
void LCD_Clear()
{
  LCD_SendCommand(0x01);  
  delay_ms(10);
}
void LCD_Gotoxy(unsigned char row, unsigned char col)
{
  unsigned char address;
  if(!row)
  address = (0x80 + col);
  else
  address = (0xC0 + col);
  delay_us(500);
  LCD_SendCommand(address);
  delay_us(50);
}
