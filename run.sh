#!/bin/sh
sudo make
sudo insmod bank.ko
sudo mknod $(shell cat /proc/devices | grep bank) 128
python pytest.py
sudo rm /dev/bank
sudo rmmod bank
make clean
