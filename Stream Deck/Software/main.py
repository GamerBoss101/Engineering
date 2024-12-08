import time

import bleSerial
import lifxapi

bleSer = bleSerial.BleSerial(1)

lifx = lifxapi.LifxAPI("c5f68089efa4a980c3169277803d1a85c58a4c16a80c1e7fa1dafce6043aed5a")
light = lifx.get_light_name("Blob")

def button_seven(event):
    if event == "p":
        req = light.toggle_power()
        print("Turned light", req["results"][0]["label"], "to", req["results"][0]["power"])
        
def button_six(event):
    if event == "p":
        global lightState
        if lightState:
            light.set_color("kelvin:3500")
            lightState = False
        else:
            light.set_color("red")
            lightState = True
        print(light)

lightState = False
# False = white light and True = red light         

def button_five(event):
    if event == "p":
        bleSer.close()
        print("Closed connection to HC-06")
        exit()

def main():
    
    bleSer.connect()
    
    # while True:
    #     if not bleSer.is_connected():
    #         bleSer.connect()
            
    #     data = bleSer.read()
    #     if data:
    #         print(data)
    
    while True:
        data = bleSer.read()
        if data:
            button = data.split("-")[1]     
            if button == "7":
                button_seven(data.split("-")[2])
            if button == "6":
                button_six(data.split("-")[2])
            if button == "5":
                button_five(data.split("-")[2])
        time.sleep(0.1) # sleep for 100ms to avoid high cpu usage

main()

