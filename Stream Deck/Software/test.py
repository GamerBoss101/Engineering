import lifxapi

lifx = lifxapi.LifxAPI("c5f68089efa4a980c3169277803d1a85c58a4c16a80c1e7fa1dafce6043aed5a")
light = lifx.get_light_name("Blob")

def main():
    light.set_color("red")
    print(light)
    light.set_color("kelvin:3500")
    
main()