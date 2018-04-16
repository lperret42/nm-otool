#!/bin/bash
path_script=`dirname $0`
binary="$path_script/nm/ft_nm"
#path_tests="$path_script""/tests/"
#path_tests="/bin/"
path_tests=$1
echo -e "Test all files (except .c and .py) in "$path_tests": \n"

for file in $( find $path_tests -type f )
do
	if [ "${file: -2}" != ".c" ] && [ "${file: -3}" != ".py" ]
	then
		ft_nm="$binary $file > my_nm"
		echo "$ft_nm"
		eval "$ft_nm"
		nm="nm $file > real_nm"
		echo "$nm"
		eval "$nm"
		diff="diff my_nm real_nm"
		echo "$diff"
		eval "$diff"
		echo ""
	fi
done
