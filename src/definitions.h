#define tilt_1 0
#define pan_1 1
#define tilt_2 2
#define pan_2 3
#define tilt_3 14
#define pan_3 15
#define tilt_4 6
#define pan_4 7

const int numLeds = 4;
const int numberOfChannels = numLeds * 3;
const int startUniverse = 0;
const int maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
bool universesReceived[maxUniverses];
bool sendFrame = 1;

#define effects_num 10
unsigned long start_time = millis();

const int freq = 5000;
const int resolution = 8;

//values to be added to pos to correct the servos pos
const int Yservo_1_offset = 20;
const int Yservo_2_offset = 25;
const int Yservo_3_offset = 15;
const int Yservo_4_offset = 15;

int speed_raw = 50;
int speed = 1000;
//int effect_played = 1;

bool power = false;
int effect = 0;

bool reset = false;

int x_circle = 0;
bool reversing = false;

int last_random_num = 0;

int fixture_1_phase = 1;
int fixture_2_phase = 2;
int fixture_3_phase = 3;
int fixture_4_phase = 1;
/*
int last_random_num = 0;
int uni_pos = 100;
int max_reached = false;

bool power = false;
bool artnet_on = false;
int effect = 0;
bool automatic_fog = false;
int led_effect = 0; //todo

//program mode
bool programMode = false;
int selected_fixture = 1;
int x_pos = 0;
int y_pos = 0;

int x_pos_1;
int y_pos_1;
int x_pos_2;
int y_pos_2;
int x_pos_3;
int y_pos_3; 
int x_pos_4;
int y_pos_4;*/

unsigned long preset_started_at = 0;

//----------------------------------------- Wifi stuff

#define NUM_SLOTS 5               //number of slots in eeprom to save wifi networks
#define WIFI_SCAN_DELAY 60000     //delay in between scans

unsigned long last_scan;          //time of last scan
bool shouldscan = false;          //if true, scan will start
bool scan_complete = false;       //true if last scan was successful
bool connect_now;                 //if true, then connect to new network

String _ssid = "";                //new sta ssid from wifi handler page
String _pass = "";                //new sta password from wifi handler page

class WiFiResult
{
  public:
    bool duplicate;
    String SSID;
    uint8_t encryptionType;
    int32_t RSSI;
    uint8_t *BSSID;
    int32_t channel;
    bool isHidden;

  WiFiResult()
  {
  }
};

typedef int16_t wifi_ssid_count_t;
WiFiResult *wifiSSIDs;
wifi_ssid_count_t wifiSSIDCount;  //number of scanned ssids

//-----------------------------------------UDP/App stuff

#define UDP_TX_PACKET_MAX_SIZE 32
bool apActive = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];  // buffer to hold incoming packet,
bool phone_connected = false;

//-----------------------------------------Pins

#define Red1    18
#define Green1  16
#define Blue1   5

#define Red2    13
#define Green2  14
#define Blue2   27

#define Red3    33
#define Green3  25
#define Blue3   26

#define Red4    32
#define Green4  23
#define Blue4   19

#define LED_BUILTIN 2

int redPin[]   = {18, 13, 33, 32};
int greenPin[] = {16, 14, 25, 23};
int bluePin[]  = {5, 27, 26, 19};


/*

  ESP32 DEVKIT Pinout:

  GPIO 36 :                           GPIO 23 : GREEN 4 LED
  GPIO 39 :                           GPIO 22 : I2C SCL
  GPIO 34 :                           GPIO 1  : UART MAIN
  GPIO 35 :                           GPIO 3  : UART MAIN
  GPIO 32 : RED 4 LED                 GPIO 21 : I2C SDA
  GPIO 33 : RED 3 LED                 GPIO 19 : BLUE 4 LED
  GPIO 25 : GREEN 3 LED               GPIO 18 : RED 1 LED
  GPIO 26 : BLUE 3 LED                GPIO 5  : BLUE 1 LED
  GPIO 27 : BLUE 2 LED                GPIO 17 : 
  GPIO 14 : GREEN 2 LED               GPIO 16 : GREEN 1 LED
  GPIO 12 :                           GPIO 4  : 
  GPIO 13 : RED 2 LED                 GPIO 2  : 
  GPIO 9  : CAN'T USE                 GPIO 15 : 
  GPIO 10 : CAN'T USE                 GPIO 0  : 
  GPIO 11 : CAN'T USE                 GPIO 8  : CAN'T USE
  GND PIN                             GPIO 7  : CAN'T USE
  VIN PIN                             GPIO 6  : CAN'T USE
*/