#include "PixelArray.h"


PixelArray::PixelArray(int nb_pixels, int nb_bits){
    this->__nb_pixels = nb_pixels;
    this->__nb_bits = nb_bits;
    this->_array = new int[nb_pixels];
}


void PixelArray::set_all_RGB(short r, short g, short b){
    for(int i = 0; i < this->__nb_pixels; i++){
        this->set_pix_RGB(i, r, g, b);
    }
}

void PixelArray::set_pix_RGB(int pix, short r, short g, short b){
    int val = (g << 16) + (r << 8) + b;
    this->_array[pix] = val;
}

int* PixelArray::get_array(void){
    return this->_array;
}

void PixelArray::set_black_all(){
    this->set_all_RGB(0, 0, 0);
}