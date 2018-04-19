#!/bin/bash
path_script=`dirname $0`
my_binary="$path_script/ft_otool"
real_binary="otool -t"
path_tests=$1
echo -e "Test all files (except .c and .py) in "$path_tests": \n"

for file in $( find $path_tests -type f )
do
	if [ "${file: -2}" != ".c" ] && [ "${file: -3}" != ".py" ]
	then
		ft_otool="$my_binary $file > my_otool"
		echo "$ft_otool"
		eval "$ft_otool"
		otool_t="$real_binary $file > real_otool"
		echo "$otool_t"
		eval "$otool_t"
		diff="diff my_otool real_otool"
		echo "$diff"
		eval "$diff"
		echo ""
	fi
done
