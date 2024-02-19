/**
 * FILENAME :        st7735.cpp          
 *
 * DESCRIPTION :
 *       TFT Joy-It RB-TFT1.8 - 1.8' LCD display - Library
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    17/feb/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 *
 *  @see : https://github.com/Matiasus/ST7735
 *  @see : https://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
 */


#include "font.h"
#include "st7735.h"
#include <cstdint>


ST7735::ST7735(SPI *spi, PinName cs, PinName rs_dc, PinName reset):
	__cs(cs), __rs_dc(rs_dc), __reset(reset)
{
	/// Set the CS pin 
	this->__cs = 1;
	/// Initialization of the SPI interface
	if(spi){delete this->__spi;}
	this->__spi = spi;
	this->__spi->frequency(ST7735_SPI_FREQ);
    this->__spi->format(8, 0);
	wait_us(1000);
	/// Background color
	this->__bg_color = ST7735_BLACK;
}


/**************************************************************
 *	Initialization and reset
 **************************************************************/

void 	ST7735::reset(void)
{
	// Reset the device.
	this->__reset = 1;
	wait_us(200000);	// 200 ms
	this->__reset = 0;
	wait_us(200000);	// 200 ms
	this->__reset = 1;
}

void	ST7735::init(void){
	/// Hardware Reset
	this->reset();
	
	// Software reset - no arguments
	this->send_command(SWRESET);
	wait_us(150000);	// 150 ms
	
	// Out of sleep mode - no arguments
	this->send_command(SLPOUT);
	wait_us(200000);	// 200 ms
	
	
	// Set color mode - 1 argument
	this->send_command(COLMOD);
	this->send_data_8bits(0x05);
	wait_us(10000);		// 10 ms
		
	// D7  D6  D5  D4  D3  D2  D1  D0
	// MY  MX  MV  ML RGB  MH   -   -
	// ------------------------------
	// ------------------------------
	// MV  MX  MY -> {MV (row / column exchange) MX (column address order), MY (row address order)}
	// ------------------------------
	//  0   0   0 -> begin left-up corner, end right-down corner / left-right (normal view) 
	//  0   0   1 -> begin left-down corner, end right-up corner / left-right (Y-mirror)
	//  0   1   0 -> begin right-up corner, end left-down corner / right-left (X-mirror)
	//  0   1   1 -> begin right-down corner, end left-up corner / right-left (X-mirror, Y-mirror)
	//  1   0   0 -> begin left-up corner, end right-down corner / up-down (X-Y exchange)  
	//  1   0   1 -> begin left-down corner, end right-up corner / down-up (X-Y exchange, Y-mirror)
	//  1   1   0 -> begin right-up corner, end left-down corner / up-down (X-Y exchange, X-mirror)  
	//  1   1   1 -> begin right-down corner, end left-up corner / down-up (X-Y exchange, X-mirror, Y-mirror)
	// ------------------------------
	//  ML: vertical refresh order 
	//      0 -> refresh top to bottom 
	//      1 -> refresh bottom to top
	// ------------------------------
	// RGB: filter panel
	//      0 -> RGB 
	//      1 -> BGR        
	// ------------------------------ 
	//  MH: horizontal refresh order 
	//      0 -> refresh left to right 
	//      1 -> refresh right to left
	// 0xA0 = 1010 0000
	this->send_command(MADCTL);
	this->send_data_8bits(0xA0);	
	// Main screen turn on
	this->send_command(DISPON);
	wait_us(200000);	// 200 ms
	// Clear screen
	this->clear_screen(this->__bg_color);
}

void ST7735::clear_screen(uint16_t color)
{
	this->__bg_color = color;
	this->set_window(0, SIZE_X, 0, SIZE_Y);
	// draw individual pixels
	this->set_color(this->__bg_color, CACHE_SIZE_MEM);
}


/**************************************************************
 *	Display On and Off
 **************************************************************/

void 	ST7735::display_on(void)
{
	// display content on
	this->send_command(DISPON);
	wait_us(200000);	// 200 ms
}

void 	ST7735::display_off(void)
{
	// display content on
	this->send_command(DISPOFF);
	wait_us(200000);	// 200 ms
}


/**************************************************************
 *	Commands and data transmission
 **************************************************************/

void 	ST7735::send_command (uint8_t cmd)
{
	// chip enable - active low
	this->__cs = 0;
	// command (active low)
	this->__rs_dc = 0;
	// transmitting data
	this->__spi->write(cmd);
	// chip disable - idle high
	this->__cs = 1;
	return;
}

void 	ST7735::send_data_8bits (uint8_t data)
{
	// chip enable - active low
	this->__cs = 0;
	// data (active high)
	this->__rs_dc = 1;
	// transmitting data
	this->__spi->write(data);
	// chip disable - idle high
	this->__cs = 1;
	return;
}


void 	ST7735::send_data_16bits (uint16_t data)
{
	// chip enable - active low
	this->__cs = 0;
	// data (active high)
	this->__rs_dc = 1;
	// transmitting data
	this->__spi->write(data >> 8);
	this->__spi->write(data);
	// chip disable - idle high
	this->__cs = 1;
	return;
}


/**************************************************************
 *	Windows and position
 **************************************************************/


bool 	ST7735::set_window(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1){
	// check if coordinates is out of range
	if ((x0 > x1)     ||	(y0 > y1)){ return ST7735_ERROR; }  
    // check if coordinates is out of range
    if (!this->check_range(x0, y0)) { return ST7735_ERROR; } 
    // check if coordinates is out of range
    if (!this->check_range(x1, y1)) { return ST7735_ERROR; } 
	// column address set
	this->send_command(CASET);
	// send start x position
	this->send_data_16bits(0x0000 | x0);
	// send end x position
	this->send_data_16bits(0x0000 | x1);
	
	// row address set
	this->send_command(RASET);
	// send start y position
	this->send_data_16bits(0x0000 | y0);
	// send end y position
	this->send_data_16bits(0x0000 | y1);

	// success
	return ST7735_SUCCESS;
}


void 	ST7735::set_screen_size(uint16_t width, uint16_t height){
	this->__width = width;
	this->__height = height;
}

bool    ST7735::check_range(uint16_t x, uint16_t y)
{
	// check if coordinates is out of range
	if ((x > this->__width)  ||	(x < 0) ||
		(y > this->__height)  ||	(y < 0)){
		// out of range
		return ST7735_ERROR;
	}
	// success
	return ST7735_SUCCESS;
}

bool    ST7735::check_value_range(uint16_t val, uint16_t min, uint16_t max)
{
	// check if coordinates is out of range
	if ((val > max)  ||	(val < min)){	return ST7735_ERROR; }
	// success
	return ST7735_SUCCESS;
}

/**************************************************************
 *	Drawings
 **************************************************************/

void 	ST7735::set_color(uint16_t color, uint16_t nb_pixels)
{
	// access to RAM
	this->send_command(RAMWR);
	
	while (nb_pixels--) {
		// write color
		this->send_data_16bits(color);
	}
}

bool 	ST7735::draw_pixel (uint16_t x, uint16_t y, uint16_t color)
{
    // check if coordinates is out of range
    if (!this->check_range(x, y)) { return ST7735_ERROR; }
	// set window
	this->set_window(x, x, y, y);
	// draw pixel by 565 mode
	this->set_color(color, 1);
	return ST7735_SUCCESS;
}



