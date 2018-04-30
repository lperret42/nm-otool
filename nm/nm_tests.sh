#!/bin/bash
path_script=`dirname $0`
flag=$1
my_binary="$path_script/ft_nm"
my_binary="$my_binary$flag"
real_binary="nm"
real_binary="$real_binary$flag"
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

ft_nm="$my_binary ft_nm ft_nm obj/main.o obj/nm.o ft_nm ../libft/libft.a > my_nm"
echo "$ft_nm"
eval "$ft_nm"
nm="$real_binary ft_nm ft_nm obj/main.o obj/nm.o ft_nm ../libft/libft.a > real_nm"
echo "$nm"
eval "$nm"
diff="diff my_nm real_nm"
echo "$diff"
eval "$diff"
echo ""

ft_nm="$my_binary ft_nm ft_nm obj/main.o src/main.c ft_nm > my_nm"
echo "$ft_nm"
eval "$ft_nm"
nm="$real_binary ft_nm ft_nm obj/main.o src/main.c ft_nm > real_nm"
echo "$nm"
eval "$nm"
diff="diff my_nm real_nm"
echo "$diff"
eval "$diff"
echo ""
