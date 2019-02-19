#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jan 30 00:21:59 2019

@author: fionn
"""
import tkinter
from tkinter import*
import bluetooth
import rtmidi
import os
import subprocess

server_sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )

deviceList=[]
nearby_devices = bluetooth.discover_devices()

top = tkinter.Tk()
top.configure(background='gray19')
top.title('MIDI Glove')


for col in range(5):
    top.grid_columnconfigure(col, minsize=20)
###############################################################################
def SearchBT():
	i = 0
	varwrite="No devices found"
	deviceList = list(bluetooth.discover_devices(lookup_names=True))
	return deviceList 		
	T.insert(END,deviceList)
###############################################################################
def ConnectBT(sock=server_sock):

	TargetDevice=Select.get("1.0","end-1c")
	print(TargetDevice)
	for bdaddr in nearby_devices:
		if TargetDevice == bluetooth.lookup_name( bdaddr ):
			target_address = bdaddr
			if target_address is not None:
				sock.connect((bdaddr,1))
				sock.send("Hello World!")

###############################################################################
def SynthStart(sock=server_sock):
	subprocess.Popen(["C:\Program Files (x86)\\Tobias Erichsen\loopMIDI\loopMIDI.exe"])
	subprocess.Popen(["C:\Program Files\\vmpk\\vmpk.exe"])
	midiout = rtmidi.MidiOut()
	available_ports = midiout.get_ports()
	
	if available_ports:
		midiout.open_port(2) # loopMIDI Port
	else:
		midiout.open_virtual_port("loopMIDI Port")

	while 1:
		sock.send("2")
		currentNote = [0,0,0]
		for byte in range(3):
				data = sock.recv(1)
				currentNote[byte] = int.from_bytes(data,byteorder='big')
				#currentNote[byte] = server_sock.recv(1)
				print(currentNote)
				midiout.send_message(currentNote)
###############################################################################

Search = tkinter.Button(top,text="Search Devices",fg="black",activebackground="DeepSkyBlue4",
						bg="deep sky blue",command=SearchBT, relief=FLAT,
						width=12,highlightthickness=0)
Search.grid(row=1, column=3)

Connect = tkinter.Button(top,text="   Connect    ",fg="black",activebackground="DeepSkyBlue4",
						bg="deep sky blue",command=ConnectBT, relief=FLAT,
						width=12,highlightthickness=0)
Connect.grid(row=3, column=3)

Synth = tkinter.Button(top,text="Synth",fg="black",activebackground="DeepSkyBlue4",
						bg="deep sky blue",command=SynthStart, relief=FLAT,
						width=12,highlightthickness=0)
Synth.grid(row=5, column=3)
###############################################################################

Scroll = Scrollbar(top)

T = Text(top, height=4, width=25)

Scroll.grid(row=0, column=1)
T.grid(row = 0, column=1)
T.config(yscrollcommand=Scroll.set)

varwrite= SearchBT()

T.insert(END,varwrite)

Select = Text(top, height=1, width=25)
Select.grid(row = 1, column = 1)
###############################################################################
top.mainloop()
