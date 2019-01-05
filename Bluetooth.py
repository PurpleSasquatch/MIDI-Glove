import bluetooth

target_name = "FYP_GLOVE"
target_address = None
rfcomm_port=0

dataLine=[]# make byte array

print("Searching")

nearby_devices = bluetooth.discover_devices()

for bdaddr in nearby_devices:
    if target_name == bluetooth.lookup_name( bdaddr ):
        target_address = bdaddr
        break

if target_address is not None:
    print ("found target bluetooth device with address ", target_address)
    server_sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
    
    server_sock.connect((bdaddr,1))
    print ("Accepted connection from ",bdaddr)
    print ("Hello World")
    
    server_sock.send("Hello World")
    # proves loop to take 6 bytes(3 hex numbers) to play midi note
    while 1:
        dataLine.clear
        print("------------------------")
        for num in range(30):
            data = server_sock.recv(1)
            print (data)
            for num in range(5):#per finger
                  for num in range(3):#note pitch volume 
                       for num in range(2):#two bytes per hex
                        # change byte array to hexadecimal string
                        dataLine.append(data)
        
        
    server_sock.close()
else:
    print ("could not find target bluetooth device nearby")
    
