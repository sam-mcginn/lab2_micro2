# pyserial-test.py
# test serial communication with Arduino
#
# require pip install pyserial
#
# Usage: python3 pyserial-test.py
#
# yluo
#
import serial
import numpy
import string

# serial port dev file name
# need to change based on the particular host machine
serialDevFile = '/dev/cu.usbmodem141101'
ser=serial.Serial(serialDevFile, 9600, timeout=1)

while True:
    read = (ser.readline().decode())
    # print(read)
    read_arr = numpy.array(read.split())
    # print(read_arr)

    read_mask = [False]*len(read_arr)
    for i in range(len(read_arr)):
        if read_arr[i].isnumeric():
            read_mask[i] = True
        elif read_arr[i][0] == '-':
            if read_arr[i][1:].isnumeric():
                read_mask[i] = True
    
    read_xy = read_arr[read_mask].astype(int)
    # print(read_xy)

    if len(read_xy) < 2:
        gyrx_read = 0
        gyry_read = 0
    else:
        gyrx_read = read_xy[0]
        gyry_read = read_xy[1]

    #gyrx_read = read_xy[0]
    #gyry_read = read_xy[1]
    
    # gyrx_read = ser.readline()
    # gyry_read = ser.readline()
    # ser.write(bytearray('Read: ', 'ascii'))
    print("x = "+str(gyrx_read))
    print("y = "+str(gyry_read))
    print()
