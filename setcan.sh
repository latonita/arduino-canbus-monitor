#!/usr/bin/env bash

setup()
{
	if [ -z "$*" ];then
		spd='6'
		br=500000
		echo "set to 500K Baudrate CAN Adapter as default option!"
	else
		case $1 in
			1000[Kk]* | 1[M]* )
				spd='8'
				br=1000000
				echo "set to 1M Baudrate CAN Adapter!"
				;;
			125[Kk]* )
				spd='4'
				br=125000
				echo "set to 125K Baudrate CAN Adapter!"
				;;
			500[Kk]* )
				spd='6'
				br=500000
				echo "set to 500K Baudrate CAN Adapter!"
				;;
			800[Kk]* )
				spd='7'
				br=800000
				echo "set to 800K Baudrate CAN Adapter!"
				;;
			100[Kk]* )
				spd='3'
				br=100000
				echo "set to 100K Baudrate CAN Adapter!"
				;;
			*)
				echo "wrong canspeed config!"
				echo "choose in 100k 125k 500k 800k 1000k and 500k by default"
				exit 0
		esac
	fi
	dev=$(readlink -f /dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_55731323935351715112-if00)
	slcan_attach -f -s${spd} -o ${dev}
	slcand -S 115200 $(echo ${dev} | sed -e 's/\/dev\///') CAN_UNO
	ip link set CAN_UNO up
	ip link show | ack CAN_UNO
}

setdown()
{
	ip link set CAN_UNO down
	killall slcand
	echo "CAN_UNO down!"
}

main()
{

	if [ -z "$(ip link show | ack CAN_UNO)" ];then
		if [ -e /dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_55731323935351715112-if00 ];then
			setup $@
		else
			echo "Arduino UNO havn't been connected!"
		fi
	else
		setdown
	fi

	exit 0
}

main
