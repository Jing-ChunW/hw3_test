import paho.mqtt.client as paho
import time
import serial
serdev = '/dev/ttyACM1'
s = serial.Serial(serdev, 9600)
# https://os.mbed.com/teams/mqtt/wiki/Using-MQTT#python-client

# MQTT broker hosted on local machine
mqttc = paho.Client()

# Settings for connection
# TODO: revise host to your IP
host = "192.168.0.6"
topic = "Mbed"

# Callbacks
def on_connect(self, mosq, obj, rc):
    print("Connected rc: " + str(rc))


def on_message(mosq, obj, msg):
    print("[Received] Topic: " + msg.topic + ", Message: " + str(msg.payload) + "\n")
    check = str(msg.payload)
    if (check[2] == "4" or check[2] == "3"):
        #print("hi")
        s.write(bytes("/doGesture/run 0\r", 'UTF-8'))
            #confirmla = int(check[2])*10+int(check[3])
    if (check[2] == "o"):
        if (int(check[6]) == int("1") and int(check[7]) == int("0")):
            s.write(bytes("/doAngledetect/run 0\r", 'UTF-8'))
        
    #print(check)
    #if (check[2] == "4" or check[2] == "3"):
        #print("hi")
        #s.write(bytes("/doGesture/run 0\r", 'UTF-8'))
        #confirmla = int(check[2])*10+int(check[3])
        #if (check[2] == "4"):
        #    if (check[3] == "5"):
        #        confirmla = 45
        #    if (check[3] == "0"):
        #        confirmla = 40
        #if (check[2] == "3"):
        #    confirmla = 30
        #line=s.readline() # Read an echo string from mbed terminated with '\n' (putc())
        #print(line)
        #line=s.readline() # Read an echo string from mbed terminated with '\n' (RPC reply)
        #print(line)
        #time.sleep(1)
    

def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed OK")

def on_unsubscribe(mosq, obj, mid, granted_qos):
    print("Unsubscribed OK")

# Set callbacks
mqttc.on_message = on_message
mqttc.on_connect = on_connect
mqttc.on_subscribe = on_subscribe
mqttc.on_unsubscribe = on_unsubscribe

# Connect and subscribe
print("Connecting to " + host + "/" + topic)
mqttc.connect(host, port=1883, keepalive=60)
mqttc.subscribe(topic, 0)

# Publish messages from Python
num = 0
while num != 5:
    ret = mqttc.publish(topic, "Message from Python!\n", qos=0)
    if (ret[0] != 0):
            print("Publish failed")
    mqttc.loop()
    time.sleep(1.5)
    num += 1

# Loop forever, receiving messages
mqttc.loop_forever()
