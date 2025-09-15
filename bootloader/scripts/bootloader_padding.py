#!/bin/python3
import os
my_absolute_dirpath = os.path.abspath(os.path.dirname(__file__))
BOOTLOADER_SIZE=0x8000
BIN_FILE=f"{my_absolute_dirpath}/../Bootloader.bin"
with open(BIN_FILE,'rb') as f:
    raw_file = f.read(); 
bytes_to_pad = BOOTLOADER_SIZE - len(raw_file) 
padding = bytes([0xff for _ in range(bytes_to_pad)])
with open(BIN_FILE,"wb") as f: 
    f.write(raw_file + padding)