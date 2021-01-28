#!/bin/bash


out_list=""

while read packet
do
	while read masks
	do
		temp_list=""

		#Trimming spaces and comments 
		masks=`echo "$masks" | tr -d ' ' | sed -e 's/#.*//'`

		if [[ "$masks" == "" ]]; then
			continue
		fi

		#create array per ','.
		readarray -d , -t rule_masks <<< "$masks"
		#for every filter insert to temo list
		for rule_mask in "${rule_masks[@]}"
		do
			temp_list+=`echo "$packet" | ./firewall.exe "$rule_mask"`
			temp_list+="\n"
		done
		#remove empty lines and count the lines
		number_of_line=`echo -e "${temp_list}" | sed '/^$/d' | wc -l`
		#if all conditions are met
		if [[ $number_of_line == ${#rule_masks[@]} ]]; then
				out_list+=`echo -e "${temp_list}" | uniq`
				out_list+="\n"
			break
		fi

	 done < "$1"

done
	#print w/o empty lines remove spaces
	echo -e "${out_list}" | sed '/^$/d' | tr -d ' ' | sort | uniq
