#!/bin/bash

#-----ARCHITECTURE---------

Arch=$(uname -a)

#-----CPU_PHYSICAL--------

CPU_PHY=$(lscpu | grep socket | awk '{print $4}')

#-----CPU_VIRTUAL---------

CPU_VIR=$(nproc)

#----MEMORY_USAGE--------

MEMORY_USAGE=$(free --mega | awk 'NR==2' | awk '{printf("%d/%dMB (%.2f%%)", $3, $2, ($3/$2) * 100)}')

#-----DISK_USAGE---------

DISK_TOTAL=$(df -h --total | grep "total" | awk '{printf("%d/%dGb (%d%%)", $2, $3, ($3/$2) *100)}')

#-----CPU_LOAD-----------

CPU=$(grep 'cpu ' /proc/stat | awk '{printf("%.2f%%",100-($5*100/($2+$3+$4+$5+$6+$7+$8)))}')

#-----LAST_BOOT----------

LAST_BOOT=$(uptime -s)

#------LVM_USE----------

LVM_USE=$(lsblk | grep -q "LVM" && echo "yes" || echo "no")

#------CONNECTION_TCP---

CONNEC_TCP=$(netstat | grep ESTABLISHED | wc -l | awk '{printf "%d ESTABLISHED", $1}')

#-------USER_LOG--------

USER=$(users | tr " " "\n" |uniq | wc -l)

#-------NETWORK_IP------

HOSTNAME=$(echo "(IP $(hostname -I | awk '{print $1}') (08:00:27:55:ee:aa))")

#-------SUDO------------

SUDO=$(journalctl _COMM=sudo | grep COMMAND | wc -l)

wall "

#Architecture: $Arch
#CPU physical : $CPU_PHY
#vCPU : $CPU_VIR
#Memory Usage: $MEMORY_USAGE
#Disk Usage: $DISK_TOTAL
#CPU load: $CPU
#Last boot: $LAST_BOOT
#LVM use: $LVM_USE
#Connections TCP : $CONNEC_TCP
#User log: $USER
#Network: $HOSTNAME
#Sudo : $SUDO cmd"
