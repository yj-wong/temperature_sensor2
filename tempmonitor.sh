#!/bin/bash

check_tempread () {
	if [ $? == 1 ]
	then
		echo temperature reading error
		exit 1
	fi
}

initmode () {
counter=0
	while [ $counter -lt 3 ]
	do
		gpio mode $counter out
		gpio write $counter 0
		((counter++))
	done
}

lightpins () {
	counter=0
	while [ $counter -lt $1 ]
	do
		gpio write $counter 1
		((counter++))
	done
	while [ $counter -lt 3 ]
	do
		gpio write $counter 0
		((counter++))
	done
}

#read tempreature
initmode
initial=$(./tempread)
check_tempread
echo "Initial temperature:" $initial

light1=$((initial + 1000))
light2=$((initial + 2000))
light3=$((initial + 3000))

while [ 1 ]
do
	temp=$(./tempread)
	check_tempread
	echo $temp

	if [ $temp -lt $light1 ]
	then
		initmode
	elif [ $temp -gt $light1 ] && [ $temp -lt $light2 ]
	then
		lightpins 1
	elif [ $temp -gt $light2 ] && [ $temp -lt $light3 ]
	then
		lightpins 2
	else
		lightpins 3
	fi
done
