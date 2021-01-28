#include <iostream>
#include <cstdio>
#include "string.h"
#include <cstring>
#include <bits/stdc++.h>
#include "ip.h"
#include "port.h"
#include "field.h"
using namespace std;

extern int check_args(int, char **);
extern void parse_input(Field &);

#if 1
//The func. check the type of the input
int check_type(String &type_of_mask){
	if(type_of_mask.trim().equals(String("src-ip")) ||
	 	type_of_mask.trim().equals(String("dst-ip"))){
		return IP;
	}
	if(type_of_mask.trim().equals(String("src-port")) ||
	 	type_of_mask.trim().equals(String("dst-port"))){
		return PORT;
	}
	return GENERIC;
}

int main(int argc, char **argv){
	

	if (check_args(argc, argv)){
		return 1;
	}

	String masks_law(argv[1]);
	String *sub_arr;
	size_t size = 0;

	masks_law.split("=",&sub_arr,&size);
	//If the mask is IP filtter the pack accordenly
	if(check_type(sub_arr[0]) == IP){
		Ip ip_mask(sub_arr[0].trim());
		ip_mask.set_value(sub_arr[1].trim());
		parse_input(ip_mask);
	}
	//If the mask is PORT filtter the pack accordenly
	if(check_type(sub_arr[0]) == PORT){
		Port port_mask(sub_arr[0].trim());
		port_mask.set_value(sub_arr[1].trim());
		parse_input(port_mask);
	}

	delete[] sub_arr;

}

#endif
