#include "field.h"
#include "ip.h"
#include "port.h"
#include <iostream>
#include <cstring>

//defult constractor
Field::Field(String pattern, field_type type){
	this->pattern = pattern;
	this->type = type;
}
//copy constractor
Field::Field(String pattern){
	this->pattern = pattern;
	this->type = GENERIC;
}

//destractor.
Field::~Field(){
}

field_type Field::get_type() const{
	return type;
}

//next 2 func. check type and call func. accordenly. return true on success.
bool Field::set_value(String val){
	if(this->get_type() == IP){
		return ((Ip*)this)->set_value(val);
	}
	if(this->get_type() == PORT){
		return ((Port*)this)->set_value(val);
	}
	return false;
}

bool Field::match_value(String val) const{

	if(this->get_type() == IP){
		return ((Ip*)this)->match_value(val);
	}
	if(this->get_type() == PORT){
		return ((Port*)this)->match_value(val);
	}
	return false;
}

//Get packet and clasify to the rlrvant type
bool Field::match(String packet){

	String *sub_pack;
	String *sub_fields;
	size_t size = 0;
	size_t size_of_field = 0;
	bool ret = false;

	packet.split(",",&sub_pack,&size);

	if(!size){
		return false;
	}
	//for every field of pack check which type is it.
	for(unsigned int i = 0; i < size; i++){
		sub_pack[i].split("=",&sub_fields,&size_of_field);
		if(!size_of_field){
			continue;
		}
		if(size_of_field == 2 && pattern.trim().equals(sub_fields[0].trim())){
			ret = match_value(sub_fields[1].trim());
		}
		delete[] sub_fields;
	}
	delete[] sub_pack;
	return ret;
}
