#include <iostream>
#include <cstring>
#include "port.h"
#include "string.h"
#include "ip.h"

//defult constractor
Port::Port(String pattern):Field(pattern, PORT){
}

//set the limits of PORT mask
bool Port::set_value(String val){

	String *str_arr;
	size_t size = 0;
	val.trim().split("-",&str_arr,&size);

	if (size != MASK_SEGMENT){
		if (size){
			delete[] str_arr;
		}
		return false;
	}
	range[0] = str_arr[0].trim().to_integer();
	range[1] = str_arr[1].trim().to_integer();
	delete[] str_arr;
	if (range[1] < range[0] ){
		return false;
	}
	return true;
}

//check if limits are valid
bool Port::match_value(String val) const{
	int mask_port = val.trim().to_integer();
	if (mask_port >= range[0] && mask_port <= range[1]){
		return true;
	}
	return false;
}


