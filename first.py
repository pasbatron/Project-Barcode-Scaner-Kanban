#!/usr/bin/env python

import serial
from time import sleep
import os, json
import requests

url = "http://local.otics.co.id:8081/ovis/validasiScaner"
files=[]
headers={'Authorization':'Basic b3RpY3NPVklTOm90aWNzT1ZJU0luZG9uZXNpYQ=='}


#setup
item_count=0
counter=0
scan_1=""
scan_2=""
perangkat=""

'''curl is used to make a http request'''
cmd="curl -s " + url
print(cmd)
print("\n")


ser_arduino = serial.Serial(
    port='/dev/ttyUSB0', #Replace ttyS0 with ttyAM0 for Pi1,Pi2,Pi0
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

while 1:
    scan_1= str(input())
    sleep(0.5)
    scan_2= str(input())
    item_count=item_count+1
    IC=str(item_count)
    item_count = 0
    payload = {
        'scan1':scan_1,
        'scan2':scan_2,
        'perangkat':"Barcode-Line"
    }
    response = requests.request("POST", url, headers=headers, data=payload, files=files)

    data_hasil = response.json()
    data2_hasil = data_hasil['messages']
    data3_hasil = data2_hasil['kembalian']
    hasil = data3_hasil['hasil']
    print(hasil)
    
    data_status = response.json()
    data2_status = data_status['messages']
    data3_status = data2_status['kembalian']
    status = data3_status['status']
    ser_arduino.write(status.encode())
    print(status)
