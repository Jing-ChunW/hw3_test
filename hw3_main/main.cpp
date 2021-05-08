#include "mbed.h"
#include "mbed_rpc.h"
#include "math.h"
#include "uLCD_4DGL.h"
#include "stm32l475e_iot01_accelero.h"
/*#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"*/

//DigitalOut myled(LED3);
RpcDigitalOut myled1(LED1, "myled1"); // for gesture indicate
RpcDigitalOut myled2(LED2, "myled2"); // for detection indicate
RpcDigitalOut myled3(LED3, "myled3");
void doGesture(Arguments *in, Reply *out);
void doAngledetect(Arguments *in, Reply *out);
//void getAcc(Arguments *in, Reply *out);
//RPCFunction rpcAcc(&getAcc, "getAcc");
RPCFunction rpcgesture(&doGesture, "doGesture");
RPCFunction rpcangledetect(&doAngledetect, "doAngledetect");
BufferedSerial pc(USBTX, USBRX);
Thread gesturethread;
Thread anglethread;
uLCD_4DGL uLCD(D1, D0, D2);

/*AnalogIn up(A0);
AnalogIn down(A1);
AnalogIn sel(A2);
*/
Thread RPC_mqtt_half;
/*
WiFiInterface *wifi;
InterruptIn btn2(USER_BUTTON);
volatile int message_num = 0;
volatile int arrivedcount = 0;
volatile bool closed = false;

const char* topic = "Mbed";

Thread mqtt_thread(osPriorityHigh);
EventQueue mqtt_queue;


void messageArrived(MQTT::MessageData& md) {
    MQTT::Message &message = md.message;
    char msg[300];
    sprintf(msg, "Message arrived: QoS%d, retained %d, dup %d, packetID %d\r\n", message.qos, message.retained, message.dup, message.id);
    printf(msg);
    ThisThread::sleep_for(1000ms);
    char payload[300];
    sprintf(payload, "Payload %.*s\r\n", message.payloadlen, (char*)message.payload);
    printf(payload);
    ++arrivedcount;
}

void publish_message(MQTT::Client<MQTTNetwork, Countdown>* client) {
    message_num++;
    MQTT::Message message;
    char buff[100];
    sprintf(buff, "/doGesture/run 0");
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*) buff;
    message.payloadlen = strlen(buff) + 1;
    int rc = client->publish(topic, message);

    printf("rc:  %d\r\n", rc);
    printf("%s\r\n", buff);
}

void close_mqtt() {
    closed = true;
}
*/
void halfcode() {
    char buf[256], outbuf[256];

    FILE *devin = fdopen(&pc, "r");
    FILE *devout = fdopen(&pc, "w");
    while(1) {
        memset(buf, 0, 256);
        for (int i = 0; ; i++) {
            char recv = fgetc(devin);
            if (recv == '\n') {
                printf("\r\n");
                break;
            }
            buf[i] = fputc(recv, devout);
        }
        RPC::call(buf, outbuf);
        printf("%s\r\n", outbuf);
    }
}
///////////////////////////////////////
float S, D, U;

int main() {
    RPC_mqtt_half.start(halfcode);
        /*char buf[256], outbuf[256];

    FILE *devin = fdopen(&pc, "r");
    FILE *devout = fdopen(&pc, "w");
    while(1) {
        memset(buf, 0, 256);
        for (int i = 0; ; i++) {
            char recv = fgetc(devin);
            if (recv == '\n') {
                printf("\r\n");
                break;
            }
            buf[i] = fputc(recv, devout);
        }
        RPC::call(buf, outbuf);
        printf("%s\r\n", outbuf);
    }*/
    /////////////////////////////////////////////
    /*wifi = WiFiInterface::get_default_instance();
    if (!wifi) {
            printf("ERROR: No WiFiInterface found.\r\n");
            return -1;
    }


    printf("\nConnecting to %s...\r\n", MBED_CONF_APP_WIFI_SSID);
    int ret = wifi->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
            printf("\nConnection error: %d\r\n", ret);
            return -1;
    }


    NetworkInterface* net = wifi;
    MQTTNetwork mqttNetwork(net);
    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork);

    //TODO: revise host to your IP
    const char* host = "192.168.50.173";
    printf("Connecting to TCP network...\r\n");

    SocketAddress sockAddr;
    sockAddr.set_ip_address(host);
    sockAddr.set_port(1883);

    printf("address is %s/%d\r\n", (sockAddr.get_ip_address() ? sockAddr.get_ip_address() : "None"),  (sockAddr.get_port() ? sockAddr.get_port() : 0) ); //check setting

    int rc = mqttNetwork.connect(sockAddr);//(host, 1883);
    if (rc != 0) {
            printf("Connection error.");
            return -1;
    }
    printf("Successfully connected!\r\n");
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = "Mbed";

    if ((rc = client.connect(data)) != 0){
            printf("Fail to connect MQTT\r\n");
    }
    if (client.subscribe(topic, MQTT::QOS0, messageArrived) != 0){
            printf("Fail to subscribe\r\n");
    }

    mqtt_thread.start(callback(&mqtt_queue, &EventQueue::dispatch_forever));
    btn2.rise(mqtt_queue.event(&publish_message, &client));
    //btn3.rise(&close_mqtt);

    int num = 0;
    while (num != 5) {
            client.yield(100);
            ++num;
    }

    while (1) {
            if (closed) break;
            client.yield(500);
            ThisThread::sleep_for(500ms);
    }

    printf("Ready to close MQTT Network......\n");

    if ((rc = client.unsubscribe(topic)) != 0) {
            printf("Failed: rc from unsubscribe was %d\n", rc);
    }
    if ((rc = client.disconnect()) != 0) {
    printf("Failed: rc from disconnect was %d\n", rc);
    }

    mqttNetwork.disconnect();
    printf("Successfully closed!\n");

    return 0;*/
    ///////////////////////////////////////////

/////////////////////////////////////////////////

    ////////////////////

}

void gesture_mode()
{
    uLCD.printf("\nHello uLCD World\n");
    ThisThread::sleep_for(30s);
    /*myled = 1;
    ThisThread::sleep_for(500ms);*/
    /*int done = 0;
    int angle[3];
    int f = 0;
    angle[0] = 30;
    angle[1] = 40;
    angle[2] = 45;
    uLCD.printf("\nSelect an angle.\n");
    uLCD.text_height(4);
    uLCD.text_height(4);
    uLCD.locate(2, 2);
    uLCD.printf("%3d Hz", angle[f]);
    while (!done) {
        S = ceil(sel);
        U = ceil(up);
        D = ceil(down);     
        if (S) {
            uLCD.cls();
            
            uLCD.locate(2, 2);
            uLCD.text_height(4);
            uLCD.text_height(4);
            uLCD.printf("%3d Hz", angle[f]);
            done = 1;
        } else if (U) {
            if (f + 1 < 3) {
                f++;
                uLCD.cls();
                uLCD.text_height(1);
                uLCD.text_height(1);
                uLCD.printf("\nSelect an angle.");
                uLCD.locate(2, 2);
                uLCD.text_height(4);
                uLCD.text_height(4);
                uLCD.printf("%3d Hz", angle[f]);
            } else {
                uLCD.locate(0, 1);
                uLCD.text_height(1);
                uLCD.text_height(1);
                uLCD.printf("Can't be larger.\n");
                uLCD.locate(2, 2);
                uLCD.text_height(4);
                uLCD.text_height(4);
                uLCD.printf("%3d Hz", angle[f]);
            }
        } else if (D) {
            if (f - 1 >= 0) {
                f--;
                uLCD.cls();
                uLCD.text_height(1);
                uLCD.text_height(1);
                uLCD.printf("\nSelect an angle.");
                uLCD.locate(2, 2);
                uLCD.text_height(4);
                uLCD.text_height(4);
                uLCD.printf("%3d Hz", angle[f]);
            } else {
                uLCD.locate(0, 1);
                uLCD.text_height(1);
                uLCD.text_height(1);
                uLCD.printf("Can't be smaller.\n");
                uLCD.locate(2, 2);
                uLCD.text_height(4);
                uLCD.text_height(4);
                uLCD.printf("%3d Hz", angle[f]);
            }
        }
        ThisThread::sleep_for(50ms);
    }*/
}
//int ledangle = 0;
int16_t pDataXYZ[3] = {0};
int16_t refXYZ[3] = {0};
double_t lengthr;
void angle_mode()
{
    int16_t mDataXYZ[3] = {0};
    double_t lengtha;
    //double_t lengthb;
    double_t dot;
    double_t theta;
    double_t confirmangle = 1.0/2; /////////////////////
    int i = 0;///////////
    while(10) {
        BSP_ACCELERO_AccGetXYZ(pDataXYZ);
        mDataXYZ[0] = pDataXYZ[0];
        mDataXYZ[1] = pDataXYZ[1];
        mDataXYZ[2] = pDataXYZ[2];
        dot = mDataXYZ[0] * refXYZ[0] + mDataXYZ[1] * refXYZ[1] + mDataXYZ[2] * refXYZ[2];
        lengtha = sqrt(mDataXYZ[0] * mDataXYZ[0] + mDataXYZ[1] * mDataXYZ[1] + mDataXYZ[2] * mDataXYZ[2]);
        if (lengtha < 0) lengtha = -lengtha;
        theta = dot/lengtha/lengthr;
        if (theta > confirmangle) {
            uLCD.cls();
            uLCD.printf("hello %d", ++i);
            //////////////////////////////////////////////////////mqtt
        }
        uLCD.cls();
        uLCD.printf("hello %d", i);
        //uLCD.printf("\n%d %d %d\n", mDataXYZ[0], mDataXYZ[1], mDataXYZ[2]);
        uLCD.printf("\n%f\n", confirmangle);
        uLCD.printf("\n%f\n", dot);
        ThisThread::sleep_for(10000ms);
        /*BSP_ACCELERO_AccGetXYZ(pDataXYZ);
        lengthb = sqrt(pDataXYZ[0] * pDataXYZ[0] + pDataXYZ[1] * pDataXYZ[1] + pDataXYZ[2] * pDataXYZ[2]);
        if (lengthb < 0) lengthb = -lengthb;
        mDataXYZ[0] = pDataXYZ[0]/lengthb - refXYZ[0];
        mDataXYZ[1] = pDataXYZ[1]/lengthb - refXYZ[1];
        mDataXYZ[2] = pDataXYZ[2]/lengthb - refXYZ[2];
        dot = mDataXYZ[0] + mDataXYZ[1]  + mDataXYZ[2];
        lengtha = sqrt(mDataXYZ[0] * mDataXYZ[0] + mDataXYZ[1] * mDataXYZ[1] + mDataXYZ[2] * mDataXYZ[2]);
        if (lengtha < 0) lengtha = -lengtha;
        theta = dot/lengtha/sqrt(3);
        if (theta > confirmangle) {
            uLCD.cls();
            uLCD.printf("hello %d", ++i);
            //////////////////////////////////////////////////////mqtt
        }
        uLCD.cls();
        uLCD.printf("hello %d", i);
        //uLCD.printf("\n%d %d %d\n", mDataXYZ[0], mDataXYZ[1], mDataXYZ[2]);
        uLCD.printf("\n%f\n", confirmangle);
        uLCD.printf("\n%f\n", dot);
        ThisThread::sleep_for(10000ms);*/
    }
}

void doGesture(Arguments *in, Reply *out) {
    bool success = true;
    char strings[20];
    char buffer[200], outbuf[256];
    int z = in->getArg<int>();
    if (z) {
        sprintf(strings, "/myled2/write 0");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control");
        }
        sprintf(strings, "/myled1/write 1");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control");
        }
        gesturethread.start(gesture_mode);
    }

    if (!z) { ////////////////////////////////////////
        sprintf(strings, "/myled2/write 0");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control");
        }
        sprintf(strings, "/myled1/write 0");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control");
        }
        gesturethread.join();
    }

}

void doAngledetect(Arguments *in, Reply *out) {
    bool success = true;
    char strings[20];
    char buffer[200], outbuf[256];
    int z = in->getArg<int>();
    BSP_ACCELERO_Init();
    
    if (z) {
        sprintf(strings, "/myled1/write 0");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control");
        }
        sprintf(strings, "/myled2/write 1");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control");
        }
        sprintf(strings, "/myled3/write 1");
        strcpy(buffer, strings);
        //ledangle = 1;
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control");
        }
        //sprintf(strings, "/getAcc/run");
        //strcpy(buffer, strings);
        //RPC::call(buffer, outbuf);
        //out->putData(buffer);
        //if (ledangle) {
        BSP_ACCELERO_AccGetXYZ(pDataXYZ);
        ThisThread::sleep_for(1000ms);
        BSP_ACCELERO_AccGetXYZ(pDataXYZ);
        refXYZ[0] = pDataXYZ[0];
        refXYZ[1] = pDataXYZ[1];
        refXYZ[2] = pDataXYZ[2];
        lengthr = sqrt(refXYZ[0] * refXYZ[0] + refXYZ[1] * refXYZ[1] + refXYZ[2] * refXYZ[2]);
        if (lengthr < 0) lengthr = -lengthr;
        //}
        //ledangle = 0;
        ThisThread::sleep_for(1000ms);
        sprintf(strings, "/myled3/write 0");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control");
        }
        anglethread.start(angle_mode);
        /*while (10) {
            //sprintf(strings, "/getAcc/run");
            //strcpy(buffer, strings);
            //RPC::call(buffer, outbuf);
            //out->putData(buffer);
            BSP_ACCELERO_AccGetXYZ(pDataXYZ);
            ThisThread::sleep_for(100ms);
        }*/
    } else {
        sprintf(strings, "/myled1/write 0");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control");
        }
        sprintf(strings, "/myled2/write 0");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control");
        }
        anglethread.join();
    }
}
/*
void getAcc(Arguments *in, Reply *out) {
    //int16_t pDataXYZ[3] = {0};
    //int16_t refXYZ[3] = {0};
    //char buffer[200];
    BSP_ACCELERO_Init();
    BSP_ACCELERO_AccGetXYZ(pDataXYZ);
    //sprintf(buffer, "Accelerometer values: (%d, %d, %d)", pDataXYZ[0], pDataXYZ[1], pDataXYZ[2]);
    //out->putData(buffer);
}
*/