#include <iostream>
#include <cstdio>
#include "string.h"
#include <cstring>
#include <bits/stdc++.h>
#include "ip.h"
using namespace std;

#define BYTE_SIZE 8
#define NUM_OF_BYTES 4
#define TOTAL_BITS BYTE_SIZE*NUM_OF_BYTES*BYTE_SIZE - 1

//defult constractor
String::String(): data(NULL), length(0){
};

//copy constractor
String::String(const String &str){

	length=str.length;
	if (!length){
		data=NULL;
	}else{
		data=new char[length+1];
		if(data){
			strcpy(data,str.data);
		}else{
			length=0;
		}
	}
}

//constractor
String::String(const char *str){
	length=strlen(str);
	if (!length){
		data=NULL;
	}else{
		data=new char[length+1];
		if(data){
			strcpy(data,str);
		}else{
			length=0;
		}
	}
}

//destractor.
String::~String(){
	if (data){
		delete[] data;
	}
}

//placment operator - input String &
String& String::operator=(const String &rhs){
	
	//if input length=0 update data & length to NULL/0.
	if(!rhs.length){
		data=NULL;
		length=0;
		return *this;
	}

	char *data_tmp=new char[rhs.length+1];
	int len_tmp = 0;
	if(data_tmp){
		strcpy(data_tmp,rhs.data);
		len_tmp=rhs.length;
	}

	if (data){
		delete[] data;
	}

	//allocate place in memory and update the relevant fields.
	data=new char[len_tmp+1];
	if(data){
		strcpy(data,data_tmp);
		length=len_tmp;
	}else{
		length=0;
	}
	if (data_tmp){
		delete[] data_tmp;
	}

	return *this;
}

//placment operator same as previous func. Only the input is char *
String& String::operator=(const char *str){

	if (data){
		delete[] data;
	}
	length=strlen(str);
	if(!length){
		data=NULL;
		length=0;
		return *this;
	}
	data=new char[length+1];
	if(data){
		strcpy(data,str);
	}else{
		length=0;
	}

	return *this;
}

//next 2 func. check if strings are equals (char* and String).
bool String::equals(const char *rhs) const{

	if(!rhs||strlen(rhs)!=length||strcmp(rhs,data)){
		return false;
	}
	return true;
}

bool String::equals(const String &rhs) const{
	if(rhs.length!=length||strcmp(rhs.data,data)){
		return false;
	}
	return true;
}

//The func. get delimiters and split a String to sub-Strings.
void String::split(const char *delimiters, String **output, size_t *size) const{
	//check input.
	if( !delimiters || !data || !size){
		return;
	}

	//declear on varibles needed
	*size = 0;
	char data_tmp[length+1]={0};
	char data_out[length+1]={0};
	strcpy(data_tmp,data);
	strcpy(data_out,data);
	int num_of_strings = 0;
	char *token_tmp = strtok(data_tmp, delimiters);

	//count how many sub Strings there are.
	while (token_tmp) {
		num_of_strings++;
        token_tmp = strtok(NULL,delimiters);
    }

    *size = num_of_strings;
    //check output before use.
    if(!output){
    	return;
    }

    char *token = strtok(data_out, delimiters);
    int sub_str = 0; 
	*output = new String[num_of_strings];
	//Placement the sub-Strings in output array.
	while (token) {
        (*output)[sub_str++] = String(token);
        token = strtok(NULL, delimiters);
    }
}

//Trimming all spaces befor and after a String.
String String::trim() const{

	int begin = 0;
	int end = length - 1;
	if (!data){
		return String();
	}

	while(data[begin]==' '){
		begin++;
	}
	while(data[end]==' '){
		end--;
	}
	if (begin > end){
		return String();
	}

	char data_free_spaces[end + 2 - begin];
	strncpy(data_free_spaces, &data[begin],end - begin + 1);
	data_free_spaces[end - begin + 1] = '\0';
	return String(data_free_spaces);
}


//The func. get string and return int
int String::to_integer() const{
	int ip_num = 0;
	String *str_arr;
	size_t size = 0;
	//if the input is IP
	split(".", &str_arr,&size);
	//when we get a string that is not IP
	if (size != SEGMENTS){
		if(!str_arr){
			return 0;
		}
		int ret = atoi(str_arr[0].trim().data);
		//releast the mem. bofore return.
		delete[] str_arr;
		return ret;
	}
	//when we get a string that is IP. for every SEGMENT
	for(int i=0; i<SEGMENTS;i++){
		int sub_str_num = atoi(str_arr[i].trim().data);
		//check if it leagal.
		if(sub_str_num > TOTAL_BITS || sub_str_num < 0){
			delete[] str_arr;
			return 0;
		}
		//convert the int to the IP int
		ip_num |= sub_str_num<<(BYTE_SIZE*(NUM_OF_BYTES - 1) - BYTE_SIZE*i);
	}
	//releast the mem. bofore return.
	if(str_arr){
		delete[] str_arr;
	}
	return ip_num;
}
