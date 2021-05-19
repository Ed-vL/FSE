import paho.mqtt.client as mqtt
import curses
import json
import time

MATRICULA = "170102343"
REGISTER_TOPIC = "fse2020/" + MATRICULA + "/dispositivos/+"
TEMPERATURE_TOPIC = "fse2020/" + MATRICULA + "/+/temperatura"
HUMIDITY_TOPIC = "fse2020/" + MATRICULA + "/+/umidade"
STATE_TOPIC = "fse2020/" + MATRICULA + "/+/estado"
client = 0

APP_DATA = {
    "pending_devices": [],
    "devices": [],
    "alarm": 0
}

def registerPendingDevice(data):
    json_data = json.loads(data)
    APP_DATA['pending_devices'].append({
        "ids": json_data["ids"],
        "room": "comodo"
    })

def registerDevice(device):
    room = str(device['room'])
    data = {"Tipo": "Registro", 
    "Comodo": room}
    json_data = json.dumps(data)
    ids = str(device['ids'])
    client.publish("fse2020/{}/dispositivos/{}".format(MATRICULA, ids), json_data)
    APP_DATA['devices'].append({
        "ids": ids,
        "room": room,
        "temperature": 0,
        "humidity": 0,
        "state": 0
    })
    
def toggleLED(device):
    data = {"Tipo": "saida"}
    json_data = json.dumps(data)
    print(json_data)
    client.publish("fse2020/{}/{}/saida".format(MATRICULA, device['room']),json_data)
    
def updateTemperature(data):
    json_data = json.loads(data)
    device = APP_DATA['devices'][json_data["ids"]]
    
    device['temperature'] = json_data.data
    
def updateHumidity(data):
    json_data = json.loads(data)
    device = APP_DATA['devices'][json_data["ids"]]
    
    device['humidity'] = json_data.data
    
def updateState(data):
    json_data = json.loads(data)
    print(json_data)
    device = APP_DATA['devices'][json_data["ids"]]
    
    device['state'] = json_data["estado"]
    
def checkInput(stdscr):
    user_input = stdscr.getch()
    
    if(user_input == 10):
        return True
    return False

def handleUserRegister(stdscr, index):
    stdscr.clear()
    
    auxList = APP_DATA['pending_devices']
    device = auxList[0]

    stdscr.addstr("Insira o comodo desejado: ")
    stdscr.refresh()
    curses.echo()
    entrada = stdscr.getstr(0,26,15)
    room = str(entrada)
    device['room'] = room
    registerDevice(device)
    
    del APP_DATA['pending_devices'][index]
    curses.noecho()
    stdscr.nodelay(True)

def handleUserAction(stdscr, user_input):
    stdscr.clear()
    curses.noecho()
    stdscr.nodelay(False)
    count = 49
    
    if(user_input == 49):
        stdscr.addstr("--DISPOSITIVOS PENDENTES--\n")
        for device in APP_DATA['pending_devices']:
            stdscr.addstr("{}. ID: {}\n\n".format(chr(count), device['ids']))
            count += 1
        
        action = stdscr.getch()
        index = action - 49
        handleUserRegister(stdscr, index)
        
    else:
        devices = APP_DATA['devices']
        for device in devices:
            stdscr.addstr("{}. ID: {}\nCOMODO: {}\n\n".format(chr(count), device['ids'], device['room']))
            count += 1
        
        action = stdscr.getch()
        index = action - 49
        toggleLED(devices[index])
    curses.noecho()
    stdscr.nodelay(True)

def handleUserInput(stdscr):
    curses.echo()
    stdscr.nodelay(False)
    
    stdscr.addstr("==============-CHOOSE ACTION-==============\n")
    stdscr.addstr("1. Register device\n")
    stdscr.addstr("2. Toggle LED\n")
    
    stdscr.addstr("================---- -----================\n")
    
    user_input = stdscr.getch()
    handleUserAction(stdscr, user_input)
    
    curses.noecho()
    stdscr.nodelay(True)
    
def displayInformation(stdscr):
    stdscr.clear()
    
    stdscr.addstr("--DISPOSITIVOS--\n")
    for device in APP_DATA['devices']:
        stdscr.addstr("ID: {}\nCOMODO: {}\nTEMPERATURA: {}\nUMIDADE: {}\nESTADO: {}\n\n".format(device['ids'], device['room'], device['temperature'], device['humidity'], device['state']))
    
    stdscr.addstr("--DISPOSITIVOS PENDENTES--\n")
    for device in APP_DATA['pending_devices']:
        stdscr.addstr("ID: {}\n\n".format(device['ids']))



    stdscr.addstr("Pressione Enter para acessar o menu...\n")

    
def interface_loop(stdscr):
    while(True):
        if(checkInput(stdscr)):
            handleUserInput(stdscr)
            continue
            
        displayInformation(stdscr)
        time.sleep(2)

def init_interface():
    stdscr = curses.initscr()
    curses.noecho()
    curses.cbreak()
    stdscr.nodelay(True)
    
    interface_loop(stdscr)
    

def init_client():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect("test.mosquitto.org")
    client.loop_start()
    
    return client

def on_connect(client, userdata, flags, rc):
    client.subscribe(REGISTER_TOPIC)
    client.subscribe(TEMPERATURE_TOPIC)
    client.subscribe(HUMIDITY_TOPIC)
    client.subscribe(STATE_TOPIC)
    
def on_message(client, userdata, msg):
    if('dispositivos' in msg.topic):
        registerPendingDevice(msg.payload)
    
    elif('temperatura' in msg.topic):
        updateTemperature(msg.payload)
    
    elif('umidade' in msg.topic):
        updateHumidity(msg.payload)
        
    elif('estado' in msg.topic):
        updateState(msg.payload)
    

print("Insira a matricula:\n")
MATRICULA = input()
client = init_client()
init_interface()