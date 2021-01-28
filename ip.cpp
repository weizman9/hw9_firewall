#include <iostream>
#include <cstring>
#include "ip.h"
#include "string.h"

#define BYTE_SIZE 8
#define NUM_OF_BYTES 4

//defult constractor
Ip::Ip(String pattern):Field(pattern, IP){
}

//set the limits of IP mask
bool Ip::set_value(String val){

	String *str_arr;
	size_t size = 0;
	val.trim().split("/",&str_arr,&size);

	if (size != MASK_SEGMENT){
		if (size){
			delete[] str_arr;
		}
		return false;
	}

	int ip = str_arr[0].trim().to_integer();
	int mask = str_arr[1].trim().to_integer();
	delete[] str_arr;
	//check if mask is legal
	if (mask < 0 || mask > BYTE_SIZE*NUM_OF_BYTES){
		return false;
	}
	unsigned int hex_mask;
	//mask=0 => NO mask. else the creat mask on LSB
	if (!mask){
		hex_mask = 0xFFFFFFFF;
	}else{
		hex_mask = (((unsigned int)1 << (BYTE_SIZE*NUM_OF_BYTES - mask)) - 1);
	}

	low = ip & (~hex_mask);
	high = ip | hex_mask;

	return true;
}

//check if limits are valid
bool Ip::match_value(String val) const{
	unsigned int mask_ip = (unsigned int)val.trim().to_integer();
	if (mask_ip >= low && mask_ip <= high){
		return true;
	}
	return false;
}
