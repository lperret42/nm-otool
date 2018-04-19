#!/bin/bash
path_script=`dirname $0`
option=$1
my_binary="$path_script/ft_nm"
my_binary="$my_binary$option"
real_binary="nm"
real_binary="$real_binary$option"
path_tests=$2
echo -e "Test all files (except .c and .py) in "$path_tests": \n"

for file in $( find $path_tests -type f )
do
	if [ "${file: -2}" != ".c" ] && [ "${file: -3}" != ".py" ]
	then
		ft_nm="$my_binary $file > my_nm"
		echo "$ft_nm"
		eval "$ft_nm"
		nm="$real_binary $file > real_nm"
		echo "$nm"
		eval "$nm"
		diff="diff my_nm real_nm"
		echo "$diff"
		eval "$diff"
		echo ""
	fi
done
