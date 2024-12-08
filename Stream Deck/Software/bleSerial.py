import bluetooth
import socket

from time import sleep


class BleSerial:
    def __init__(self, port):
        self.port = port
        self.sock = None
        self.connected = False
        
    def is_connected(self):
        return self.connected
    
    def find_device(self):
        nearby_devices = bluetooth.discover_devices(lookup_names=True)
        
        hc06_address = None

        for addr, name in nearby_devices:
            if "HC-06" in name:
                hc06_address = addr
                print("Found HC-06 device:", hc06_address)
                break
                
        return hc06_address

    def connect(self):
        print("Waiting for connection on RFCOMM channel", self.port)
        hc06_address = self.find_device()
        
        try:
            self.sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)

            print("Connecting to HC-06 device on port", self.port)
            self.sock.connect((str(hc06_address), int(self.port)))        
            #self.sock.settimeout(10) # 10 second timeout
        except bluetooth.btcommon.BluetoothError as e:
            print("Error connecting to HC-06 device:", e)
            sleep(2)
            self.connect()
        finally:
            print("Connected to HC-06 device on port", self.port)
            self.connected = True
            return

    def read(self):
        return self.sock.recv(1024).decode('utf-8').strip()
        # try:
        #     return self.sock.recv(1024).decode('utf-8').strip()
        # except bluetooth.btcommon.BluetoothError as e:
        #     print("Timeout reading from HC-06 device:", e)
        #     self.connected = False
        #     print("connection lost... reconnecting")
    
    def get_socket(self):
        return self.sock

    def write(self, data):
        self.sock.send(data)

    def close(self):
        self.sock.close()