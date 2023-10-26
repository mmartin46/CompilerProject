#!/bin/bash

# Where to put it: copy this in a text editor and save this under
# testlab in the directory your labs are located (e.g. 2336)
# then cd into said directory in a terminal run: chmod u+x testlab
# To use: ./testlab labnumber (or testlab labnumber if testlab in PATH)
# Gisted at: https://gist.github.com/zenforic/d890d820451529addee0127a1bf14805/

ask()
{
	prompt=""
	if [ "$2" -eq 1 ]
	then
		prompt="There is 1 difference. Would you like to see it"
	else
		prompt="There are $2 differences. Would you like to see them"
	fi
	echo -en "\e[1;31m$prompt? [yN] "
	[ "$3" == "-y" ] || read -n 1 -p "" -r ans
	echo -e "\e[0;36m"
	if [[ "$ans" == "y" || "$3" == "-y" ]]
	then
		echo -e "\e[3;31m"
		diff "$1" my.out
		echo -e "\e[0;36m"
	fi
}

echo -e "\e[1;36m==Testlab for CS Labs at ASU via dat-out files by Jason Cervantes==\e[0m"
echo ""

if [ ! -d "$1" ]
then
	echo -e "\e[1;31mNon-existent lab, Usage: testlab labnumber [-y]\e[0m"
	echo "-y: Answer yes to diff prompts if any"
	exit 1
fi

cd "$1" || exit 3
make || exit 2

if [ ! "$(find ./ -iname '[0-9][0-9].dat' | wc -l)" -eq 0 ]
then
	for dat in $(find ./ -iname '[0-9][0-9].dat')
	do
		doask=0
		echo ""
		echo -e "\e[0;36m*******************************"
		echo -e "***        \e[1;33m$dat\e[0;36m         ***"
		echo -e "* \e[1;34mFetching outfile    ...     \e[0;36m*"
		out=$(echo "$dat" | sed 's/.dat/.out/')
		echo -e "* \e[1;34mGenerating my.out   ...     \e[0;36m*"
		
		if [ -e "lab$1main" ]
		then
			touch "lab$1main.C"
			./lab"$1"main < "$dat" > my.out || (./lab"$1"main "$dat" > my.out && echo "^^^ above is NOT an error in this case, arguments '$dat' were passed by testlab ^^^")
		else
			./lab"$1" < "$dat" > my.out
		fi
		
		echo -e "* \e[1;34mGetting differences ...     \e[0;36m*"
		dif=$(diff -y --suppress-common-lines "$out" my.out | sed -e '1!b' -e '/Your Name/d')
		echo -e "* \e[1;34mCounting diffs      ...     \e[0;36m*"
		num=$(echo -n "$dif" | grep -c "^")
		
		if [ "$num" -gt 0 ]
		then
			doask=1
			echo -e "*** \e[1;31mFiles aren't identical. \e[0;36m***"
		else
			echo -e "*** \e[1;32mFiles are identical.    \e[0;36m***"
		fi
		
		echo -e "\e[0;36m*******************************"
		
		if [ $doask -eq 1 ]
		then
			ask "$out" "$num" "$2"
		fi
	done
else
	for out in $(find ./ -iname '[0-9][0-9].out')
	do
		doask=0
		echo ""
		echo -e "\e[0;36m*******************************"
		echo -e "***        \e[1;33m$out\e[0;36m         ***"
		echo -e "* \e[1;33mNo input/dat files  ...     \e[0;36m*"
		echo -e "* \e[1;34mGenerating my.out   ...     \e[0;36m*"
		
		if [ -e lab"$1"main ]
		then
			touch lab"$1"main.C
			if [ -e lab34main ]
			then
				./lab34main > my.out 2>&1
			else
			./lab"$1"main > my.out
			fi
		else
			./lab"$1" > my.out
		fi
		
		echo -e "* \e[1;34mGetting differences ...     \e[0;36m*"
		dif=$(diff -y --suppress-common-lines "$out" my.out | sed -e '1!b' -e '/Your Name/d')
		echo -e "* \e[1;34mCounting diffs      ...     \e[0;36m*"
		num=$(echo -n "$dif" | grep -c "^")
		
		if [ "$num" -gt 0 ]
		then
			doask=1
			echo -e "*** \e[1;31mFiles aren't identical. \e[0;36m***"
		else
			echo -e "*** \e[1;32mFiles are identical.    \e[0;36m***"
		fi
		
		echo -e "\e[0;36m*******************************"
		
		if [ $doask -eq 1 ]
		then
			ask "$out" "$num" "$2"
		fi
	done
fi
echo -e "\e[0m"
