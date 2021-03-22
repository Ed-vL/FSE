#define I2C_ADDR   0x27 // I2C device address

// Define some device constants
#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

#define LCD_BACKLIGHT   0x08  // On
// LCD_BACKLIGHT = 0x00  # Off

#define ENABLE  0b00000100 // Enable bit

extern int fd;  // seen by all subroutines

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);
void setupI2C();

// added by Lewis
void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line); //move cursor
void ClrLcd(void); // clr LCD return home
void typeln(const char *s);
void typeChar(char val);

// float to string
void typeFloat(float myFloat);
// int to string
void typeInt(int i);
// clr lcd go home loc 0x80
void ClrLcd(void);
// go to location on LCD
void lcdLoc(int line);
// out char to LCD at current position
void typeChar(char val);
// this allows use of any size string
void typeln(const char *s);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);
void lcd_init();