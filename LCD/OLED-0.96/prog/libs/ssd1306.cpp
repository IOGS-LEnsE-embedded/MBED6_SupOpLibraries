/**
 * FILENAME :        ssd1306.cpp          
 *
 * DESCRIPTION :
 *       LCD Joy-It OLED-0.96 - 0.96' LCD display - Library
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    29/feb/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */


#include "font.h"
#include "ssd1306.h"
#include "ssd1306_constants.h"


SSD1306::SSD1306(I2C *i2c, uint16_t width, uint16_t height){
	this->__width = width;
	this->__height = height;
    /// Set the good size for the data buffer
    this->__buff_size = this->__height * this->__width / 8;
    this->__buffer.resize(this->__buff_size);
	/// Initialization of the SPI interface
	if(i2c){delete this->__i2c;}
	this->__i2c = i2c;
	this->__i2c->frequency(SSD_I2C_FREQ);
	wait_us(1000);
}


/**************************************************************
 *	Initialization
 **************************************************************/

bool	SSD1306::init(void){

    bool ack = true;
    ack = ack && this->send_command(SSD1306_DISPLAYOFF);
    ack = ack && this->send_command(SSD1306_SETDISPLAYCLOCKDIV);
    ack = ack && this->send_command(0x80);  // the suggested ratio 0x80

    ack = ack && this->send_command(SSD1306_SETMULTIPLEX);
    ack = ack && this->send_command(this->__height-1);

    // No Offset
    ack = ack && this->send_command(SSD1306_SETDISPLAYOFFSET);
    ack = ack && this->send_command(0x00);   // no offset

    // Start Line - 0 
    ack = ack && this->send_command(SSD1306_SETSTARTLINE | 0x0);

    // External Power VCC
    ack = ack && this->send_command(SSD1306_CHARGEPUMP);
    ack = ack && this->send_command(0x14);   // or 0x14 ??

    ack = ack && this->send_command(SSD1306_SEGREMAP | 0x1); 
    ack = ack && this->send_command(SSD1306_COMSCANDEC); 

    ack = ack && this->send_command(SSD1306_SETCOMPINS); 
    ack = ack && this->send_command(0x12);  
        // 0x12 if 64pix height or 0x02 if 32pix

    ack = ack && this->send_command(SSD1306_SETCONTRAST); 
    ack = ack && this->send_command(0xCF);  // 0x8F if 32 pix

    ack = ack && this->send_command(SSD1306_SETPRECHARGE); 
    ack = ack && this->send_command(0xF1);  

    ack = ack && this->send_command(SSD1306_SETVCOMDETECT); 
    ack = ack && this->send_command(0x40);  

    ack = ack && this->send_command(SSD1306_DISPLAYALLON_RESUME); 
    
    ack = ack && this->send_command(SSD1306_NORMALDISPLAY); 
    
    ack = ack && this->send_command(SSD1306_DISPLAYON);  
    return ack;
}

void SSD1306::clear_screen(void)
{
    for(int i = 0; i < this->__buff_size; i++){
        this->__buffer[i] = 0;
    }
    this->display();
}


/**************************************************************
 *	Display On and Off
 **************************************************************/

void 	SSD1306::display_on(void)
{
    this->send_command(SSD1306_DISPLAYON); 
}

void 	SSD1306::display_off(void)
{
    this->send_command(SSD1306_DISPLAYOFF); 
}

void    SSD1306::invertDisplay(bool i)
{
    this->send_command(i ? SSD1306_INVERTDISPLAY : SSD1306_NORMALDISPLAY); 
}

/**************************************************************
 *	Commands and data transmission
 **************************************************************/

bool 	SSD1306::send_command (uint8_t cmd)
{
    char buff[2];
    int ack;
	buff[0] = 0; // Command Mode
	buff[1] = cmd;
	ack = this->__i2c->write(SSD_I2C_ADDRESS, buff, sizeof(buff));
    return  (ack == 0) ? SSD1306_SUCCESS : SSD1306_ERROR;
}

bool 	SSD1306::send_data (std::vector<uint8_t> data, uint16_t size)
{
    char *buff = new char[size+1];
    int ack;
	buff[0] = 0x40; // Data Mode
    for(int i = 0; i < size; i++)
        buff[i+1] = data[i];
	ack = this->__i2c->write(SSD_I2C_ADDRESS, buff, size+1);
    return  (ack == 0) ? SSD1306_SUCCESS : SSD1306_ERROR;
}

bool    SSD1306::display(){
    bool ack = true;
    /// Set memory addressing mode
    ack = ack && this->send_command(SSD1306_MEMORYMODE);  
    // Horizontal addressing mode
    ack = ack && this->send_command(SSD1306_SETLOWCOLUMN | 0x0);
    // Set column start and end addresses
    ack = ack && this->send_command(SSD1306_MEMORYMODE | 0x1);
    ack = ack && this->send_command(0x0);
    ack = ack && this->send_command(this->__width-1);
    // Set page start and end addresses
    ack = ack && this->send_command(SSD1306_MEMORYMODE | 0x2);
    ack = ack && this->send_command(0x0);
    ack = ack && this->send_command(0x7);
    
    this->send_data(this->__buffer, this->__buff_size);
    return  ack;
}

std::vector<uint8_t> SSD1306::get_buffer(void){
    return this->__buffer;
}

/**************************************************************
 *	Windows and position
 **************************************************************/

bool    SSD1306::check_range(uint16_t x, uint16_t y)
{
	// check if coordinates is out of range
	if ((x > this->__width)  ||	(x < 0) ||
		(y > this->__height)  ||	(y < 0)){
		// out of range
		return SSD1306_ERROR;
	}
	// success
	return SSD1306_SUCCESS;
}

bool    SSD1306::check_value_range(uint16_t val, uint16_t min, uint16_t max)
{
	// check if coordinates is out of range
	if ((val > max)  ||	(val < min)){	return SSD1306_ERROR; }
	// success
	return SSD1306_SUCCESS;
}

/**************************************************************
 *	Drawings
 **************************************************************/

bool 	SSD1306::draw_pixel (uint16_t x, uint16_t y, uint16_t color)
{
    // check if coordinates is out of range
    if (!this->check_range(x, y)) { return SSD1306_ERROR; }

    // x is which column
    if (color == SSD1306_WHITE) 
        this->__buffer[x+ (y/8) * this->__width] |= (1 << (y%8));  
    else // else black
        this->__buffer[x+ (y/8) * this->__width] &= (0 << (y%8));

	return SSD1306_SUCCESS;
}



