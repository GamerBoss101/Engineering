import requests

class Light:
    def __init__(self, headers, label, id, power, color):
        self.headers = headers
        self.label = label
        self.uuid = id
        self.power = power
        self.color = color
        
    def toggle_power(self):
        url = f'https://api.lifx.com/v1/lights/{self.uuid}/toggle'
        response = requests.post(url, headers=self.headers)
        return response.json()
        
    def set_color(self, color):
        url = f'https://api.lifx.com/v1/lights/{self.uuid}/state'
        data = {
            'color': color,
        }
        response = requests.put(url, headers=self.headers, json=data)
        return response.json()
    
    def set_power(self, power):
        url = f'https://api.lifx.com/v1/lights/{self.uuid}/state'
        data = {
            'power': power,
        }
        response = requests.put(url, headers=self.headers, json=data)
        return response.json()
    
    def __str__(self):
        return f'Light: {self.label} - Power: {self.power} - Color: {self.color}'

class LifxAPI:
    def __init__(self, token):
        self.token = token
        self.headers = {
            'Authorization': f'Bearer {self.token}',
        }
        
    def toggle_power(self, uuid):
        url = f'https://api.lifx.com/v1/lights/{uuid}/toggle'
        response = requests.post(url, headers=self.headers)
        return response.json()
        
    def get_lights(self):
        url = 'https://api.lifx.com/v1/lights/all'
        response = requests.get(url, headers=self.headers)
        return response.json()
    
    def get_light_name(self, name):
        lights = self.get_lights()
        for light in lights:
            if light['label'] == name:
                return Light(self.headers, light['label'], light['id'], light['power'], light['color'])
        
    