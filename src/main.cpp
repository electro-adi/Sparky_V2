
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <Preferences.h>
#include <ArtnetWifi.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"

#define USE_PCA9685_SERVO_EXPANDER
#define MAX_EASING_SERVOS 8
#define PCA9685_ADDRESS 0x41

#define MINIMUM_PULSE_WIDTH 300
#define MAXIMUM_PULSE_WIDTH 2600

#define START_DEGREE_X 0
#define START_DEGREE_Y 0

#include "ServoEasing.hpp"

ServoEasing pan1(PCA9685_ADDRESS);
ServoEasing pan2(PCA9685_ADDRESS);
ServoEasing pan3(PCA9685_ADDRESS);
ServoEasing pan4(PCA9685_ADDRESS);
ServoEasing tilt1(PCA9685_ADDRESS);
ServoEasing tilt2(PCA9685_ADDRESS);
ServoEasing tilt3(PCA9685_ADDRESS);
ServoEasing tilt4(PCA9685_ADDRESS);

#include "credentials.h"
#include "definitions.h"
#include "led_effects.h"
  
void WIFI_CopySSIDs(wifi_ssid_count_t n);
uint8_t WIFI_Connect(String ssid, String pass);
bool WIFI_Scan(bool scan_now);
void Handle_Wifi(AsyncWebServerRequest * request);
void Handle_Wifi_List(AsyncWebServerRequest *request);
void second_core_functions(void * parameter);
void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data);
void setup();
void set_color(int led, int red, int green, int blue);
void play_effect(int effect_num);
void UDP_Handler();
void loop();

ArtnetWifi artnet;
Preferences preferences;
DNSServer DNS;
AsyncWebServer server(80);
IPAddress phoneIP;
WiFiUDP UDP;

#if SERIAL_DEBUG != 0
  #define DEBUG_PRINT(x) Serial.print(x)
#else
  #define DEBUG_PRINT(x)
#endif

/*
  Main controls:
    (rx) DISCOVER_SPARKY (returns SPARKY_ACK)
    (rx) POWER=[value] 1, 0
    (rx) ARTNET=[value] 1, 0
    (rx) SPEED=[value] 0 - 100
    (rx) EFFECT=[value] 0 - 15

  Set color for each rgb led

    (rx) R1=[value] 0 - 255
    (rx) G1=[value] 0 - 255
    (rx) B1=[value] 0 - 255

    (rx) R2=[value] 0 - 255
    (rx) G2=[value] 0 - 255
    (rx) B2=[value] 0 - 255

    (rx) R3=[value] 0 - 255
    (rx) G3=[value] 0 - 255
    (rx) B3=[value] 0 - 255

    (rx) R4=[value] 0 - 255
    (rx) G4=[value] 0 - 255
    (rx) B4=[value] 0 - 255

  Set the degrees of all 4 servos:

    (rx) X_ALL=[value] 0 - 180
    (rx) Y_ALL=[value] 0 - 180

  Set degree for each servo:

    (rx) X1=[value] 0 - 180
    (rx) X2=[value] 0 - 180
    (rx) X3=[value] 0 - 180
    (rx) X4=[value] 0 - 180
    (rx) Y1=[value] 0 - 180
    (rx) Y2=[value] 0 - 180
    (rx) Y3=[value] 0 - 180
    (rx) Y4=[value] 0 - 180
*/

#include "dances.h"

//========================================================================================================================================
void WIFI_CopySSIDs(wifi_ssid_count_t n) {

  if (n == WIFI_SCAN_FAILED)
  {
    DEBUG_PRINT("scanNetworks returned: WIFI_SCAN_FAIL\n");
  }
  else if (n == WIFI_SCAN_RUNNING)
  {
    DEBUG_PRINT("scanNetworks returned: WIFI_SCAN_RUNNING!\n");
  }
  else if (n < 0)
  {
    DEBUG_PRINT("scanNetworks failed with unknown error code!\n");
  }
  else if (n == 0)
  {
    DEBUG_PRINT("No networks found\n");
  }
  else
  {
    DEBUG_PRINT("Scan complete. Found " + String(n) + " networks\n");
  }

  if(n > 0)
  {
    if(wifiSSIDs) delete[] wifiSSIDs;
    
    wifiSSIDs = new WiFiResult[n];
    wifiSSIDCount = n;
    shouldscan = false;

    for(wifi_ssid_count_t i = 0; i < n; i++)
    {
      wifiSSIDs[i].duplicate = false;

      WiFi.getNetworkInfo(i,
                          wifiSSIDs[i].SSID,
                          wifiSSIDs[i].encryptionType,
                          wifiSSIDs[i].RSSI,
                          wifiSSIDs[i].BSSID,
                          wifiSSIDs[i].channel);
    }

    for(int i = 0; i < n; i++)
    {
      for(int j = i + 1; j < n; j++)
      {
        if(wifiSSIDs[j].RSSI > wifiSSIDs[i].RSSI)
        {
          std::swap(wifiSSIDs[i], wifiSSIDs[j]);
        }
      }
    }

    String cssid;
    for(int i = 0; i < n; i++)
    {
      if(wifiSSIDs[i].duplicate == true) continue;//skip if its a duplicate
      
      cssid = wifiSSIDs[i].SSID;

      DEBUG_PRINT("STA " + String(i) + " - " + cssid + "\n");

      for(int j = i + 1; j < n; j++)
      {
        if(cssid == wifiSSIDs[j].SSID)
        {
          DEBUG_PRINT("DUP AP: " + String(wifiSSIDs[j].SSID) + "\n");
          wifiSSIDs[j].duplicate = true; // set dup aps to NULL
        }
      }
    }
  }
}

//========================================================================================================================================
uint8_t WIFI_Connect(String ssid, String pass) {

  unsigned long started_at = millis();
  uint8_t _status = 0;
  bool connecting = false;
  bool sta_connected = false; 

  if(WiFi.SSID().length() > 0)//disconect from current network
  {
    DEBUG_PRINT("Disconnecting from current newtork\n");
    WiFi.disconnect(false);
  }

  if(ssid != "" && pass != "")//ssid and password provided
  {
    DEBUG_PRINT("SSID: " + _ssid + " and pass: " + _pass + "\n");
    connecting = true;
    WiFi.begin(ssid.c_str(), pass.c_str());
  }
  else//ssid and password NOT provided
  {
    DEBUG_PRINT("Searching for saved wifi networks\n");

    while(millis() - started_at < 10000) if(WIFI_Scan(true)) break;//start wifi scan

    if(wifiSSIDCount > 0)//if there is networks available
    {
      preferences.begin("wifi", false);

      for(int i = 0; i < NUM_SLOTS; i++)//check each slot to see if any of the available networks has been saved earlier
      {
        String ssid_key = "ssid_" + String(i);
        String pass_key = "pass_" + String(i);
        String stored_ssid = preferences.getString(ssid_key.c_str(), "");        
        String stored_pass = preferences.getString(pass_key.c_str(), "");

        DEBUG_PRINT("Saved network " + String(i) + " - SSID: " + stored_ssid + ", PSWD: " + stored_pass + "\n");

        for(int j = 0; j < wifiSSIDCount; j++)//go through the available networks
        {
          if(wifiSSIDs[j].duplicate) continue;
          String scanned_ssid = wifiSSIDs[j].SSID;

          if(stored_ssid == scanned_ssid)
          {
            DEBUG_PRINT("Connecting to saved network " + String(i) + " - SSID: " + stored_ssid + ", PSWD: " + stored_pass + "\n");
            WiFi.begin(stored_ssid.c_str(), stored_pass.c_str());
            connecting = true;
            break;
          }
        }
        if(connecting) break;
      }
      preferences.end();
    }
    else//no stations available to connect or scan failed
    {
      DEBUG_PRINT("No stations to connect\n");
    }
  } 

  if(connecting)//check if connection is successful
  {
    _status = WiFi.waitForConnectResult();

    DEBUG_PRINT("Connection result: " + String(_status) + "\n");

    if(_status == WL_CONNECTED) 
    {
      sta_connected = true;
      digitalWrite(LED_BUILTIN, HIGH);
      DEBUG_PRINT("WiFi connected, IP:" + WiFi.localIP().toString() + "\n");
    }
  }

  if(sta_connected && ssid != "" && pass != "")//connection was successful, save this network 
  {
    preferences.begin("wifi", false);

    int ssid_stored_at = -1;
    int emptySlot = -1;

    for(int i = 0; i < NUM_SLOTS; i++)//check each slot to see if the current wifi credentials has been saved
    {
      String key = "ssid_" + String(i);
      String stored_ssid = preferences.getString(key.c_str(), "");

      if(stored_ssid == "" && emptySlot == -1) emptySlot = i;//store the index of first empty slot

      DEBUG_PRINT("STORED SSID " + String(i) + " - " + stored_ssid + "\n");

      if(stored_ssid == ssid)
      {
        DEBUG_PRINT("Wifi already saved at " + String(i) +"\n");
        ssid_stored_at = i;
        break;
      }
    }

    if(ssid_stored_at == -1)//if not saved, then add the new wifi ssid and password to eeprom
    {
      if(emptySlot != -1)//there is an empty slot
      {
        String ssid_key = "ssid_" + String(emptySlot);
        String pass_key = "pass_" + String(emptySlot);

        preferences.putString(ssid_key.c_str(), ssid);
        preferences.putString(pass_key.c_str(), pass);

        DEBUG_PRINT("Wifi saved to empty slot at index " + String(emptySlot) + "\n");
      }
      else //if all slots are full then delete the first one and roll everything ahead
      {
        for (int i = 1; i < NUM_SLOTS; i++) {

          String ssid_key1 = "ssid_" + String(i - 1);
          String pass_key1 = "pass_" + String(i - 1);

          String ssid_key2 = "ssid_" + String(i);
          String pass_key2 = "pass_" + String(i);

          preferences.putString(ssid_key1.c_str(), preferences.getString(ssid_key2.c_str(), ""));
          preferences.putString(pass_key1.c_str(), preferences.getString(pass_key2.c_str(), ""));

          DEBUG_PRINT("NEW STORED SSID " + String(i - 1) + " - " + preferences.getString(ssid_key1.c_str(), "") + "\n");
        }

        //add the ssid and password into the last slot

        String ssid_key = "ssid_" + String(NUM_SLOTS - 1);
        String pass_key = "pass_" + String(NUM_SLOTS - 1);

        preferences.putString(ssid_key.c_str(), ssid);
        preferences.putString(pass_key.c_str(), pass);

        DEBUG_PRINT("NEW STORED SSID " + String(NUM_SLOTS - 1) + " - " + preferences.getString(ssid_key.c_str(), "") + "\n");

        DEBUG_PRINT("Wifi saved to last slot" + String(emptySlot) + "\n");
      }
    }
    preferences.end();
  }
  return _status;
}

//========================================================================================================================================
bool WIFI_Scan(bool scan_now) {

  wifi_ssid_count_t n = WiFi.scanComplete();

  //run scan if its not running and its been a while since last scan
  if((last_scan == 0 || millis() - last_scan >= WIFI_SCAN_DELAY) && scan_now && n != WIFI_SCAN_RUNNING && (WiFi.getMode() & WIFI_MODE_STA) && (WiFi.status() == WL_DISCONNECTED || WiFi.status() == WL_IDLE_STATUS)) 
  {
    last_scan = millis();
    scan_complete = false;
    DEBUG_PRINT("About to scan.\n");

    int scanResult = WiFi.scanNetworks(true);

    DEBUG_PRINT("scanNetworks() returned: " + String(scanResult) + "\n");

    if(scanResult == WIFI_SCAN_FAILED) {
      DEBUG_PRINT("WIFI SCAN FAILED!\n");
    }
  }

  if(n >= 0)//Scan finished
  {
    scan_complete = true;
    WIFI_CopySSIDs(n);
    WiFi.scanDelete();
    return true;
  }

  return false;
}

//========================================================================================================================================
void Handle_Wifi(AsyncWebServerRequest *request) {
  
  shouldscan = true;
  scan_complete = false;
  last_scan = 0;

  String page = R"rawliteral(
  <!DOCTYPE html>
  <html lang="en">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no">
      <title>Adi's Tracker</title>
      <style>
        :root {
            --primary-text: #eee;
            --bg-dark: rgba(38, 38, 38, 0.5);
            --highlight: rgba(255, 255, 255, 0.1);
            --highlight-hover: rgba(255, 255, 255, 0.3);
        }

        body {
            opacity: 0;
            transition: opacity 0.3s ease-in-out;
            font-family: Arial, Helvetica, sans-serif;
            font-size: 16px;
            color: #eeeeee;
            text-align: center;

            background: url('/background') center/cover no-repeat fixed;

            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh; 
            margin: 0;
        }
        body.fade-in { opacity: 1; }

        .wifi_box {
            background: var(--bg-dark);
            backdrop-filter: blur(5px);
            border-radius: 1em;
            padding: 1.5em;
            width: 300px;
            box-shadow: 0 4px 16px rgba(0, 0, 0, 0.5);
            animation: fadeIn 0.6s ease-out;
            text-align: center;
            margin: 0;
        }

        .wifi_input, .wifi_button {
            width: 100%;
            padding: 0.75em 1em;
            border-radius: 0.75em;
            border: none;
            box-sizing: border-box;
            font-size: 1em;
            margin-bottom: 1em;
        }

        .wifi_input {
            background-color: var(--highlight);
            color: white;
        }
        .wifi_input::placeholder {
            color: rgba(255, 255, 255, 0.7);
        }

        .wifi_button {
            background-color: var(--highlight);
            color: white;
            font-size: 1.1em;
            cursor: pointer;
            transition: background 0.3s, transform 0.2s;
        }
        .wifi_button:hover {
            background-color: var(--highlight-hover);
            transform: scale(1.02);
        }

        .wifi_network {
          display: flex;
          align-items: center;
          gap: 1em;
          margin: 1em 0;
          cursor: pointer;
          padding: 0.5em;
          border-radius: 0.75em;
          transition: background 0.3s, transform 0.2s;
        }
        .wifi_network:hover {
          background: rgba(255, 255, 255, 0.05);
          transform: scale(1.02);
        }

        .hidden { display: none; }

        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(20px); }
            to { opacity: 1; transform: translateY(0); }
        }
      </style>
      <script defer>
        document.addEventListener("DOMContentLoaded", () => {
          document.body.classList.add("fade-in");

          const ssidList = document.getElementById('ssid_list');
          const form = document.getElementById('wifi_form');
          const connectBtn = document.getElementById('connect_btn');
          const savedView = document.getElementById('saved_view');
          const mainView = document.getElementById('main_view');
          const ssidSaved = document.getElementById('ssid_saved');

          function renderNetworks(networks) {
          if (!networks.length) {
              ssidList.innerHTML = `<img src="/wifi_loading" width="120" height="90"><p>Scanning...</p>`;
              return;
          }

          ssidList.innerHTML = networks.map(net => {
              const iconStrength = net.rssi >= -60 ? "full" : "half";
              const lockStatus = net.open ? "unlocked" : "locked";
              const safeSSID = net.ssid.replace(/'/g, "\\'");
              return `
              <div class="wifi_network" onclick="document.getElementsByName('ssid')[0].value='${safeSSID}'">
                  <img src="/wifi_${lockStatus}_${iconStrength}" width="24" height="24">
                  <span>${net.ssid}</span>
              </div>
              `;
          }).join('');
          }

          function fetchSSIDList() {
          fetch('/wifi_list')
              .then(response => response.json())
              .then(data => {
              renderNetworks(data);
              if (data.length > 0) clearInterval(pollInterval);
              })
              .catch(() => {
              ssidList.innerHTML = "<p>Error scanning Wi-Fi</p>";
              });
          }

          const pollInterval = setInterval(fetchSSIDList, 2000);

          // Handle Wi-Fi form submission via AJAX
          form.addEventListener("submit", e => {
          e.preventDefault();
          connectBtn.disabled = true;
          connectBtn.innerText = "Connecting...";

          const formData = new FormData(form);
          const query = `ssid=${encodeURIComponent(formData.get("ssid"))}&password=${encodeURIComponent(formData.get("password"))}`;

          fetch(`/wifi_save?${query}`)
              .then(res => res.text())
              .then(() => {
              ssidSaved.innerText = formData.get("ssid");
              mainView.classList.add("hidden");
              savedView.classList.remove("hidden");
              })
              .catch(() => {
              alert("Failed to save Wi-Fi.");
              })
              .finally(() => {
              connectBtn.disabled = false;
              connectBtn.innerText = "Connect";
              });
          });

          document.getElementById('back_btn').addEventListener("click", () => {
          savedView.classList.add("hidden");
          mainView.classList.remove("hidden");
          });
        });
      </script>
    </head>
    <body>
        <!-- Main Wi-Fi Connect View -->
        <div class="wifi_box" id="main_view">
        <h2>Connect to Wi-Fi</h2>
        <div id="ssid_list">
            <img src="/wifi_loading" width="120" height="90" alt="Loading...">
            <p>Scanning...</p>
        </div>
        <form id="wifi_form" method="GET">
            <input class="wifi_input" type="text" name="ssid" placeholder="Enter SSID" autofocus>
            <input class="wifi_input" type="password" name="password" placeholder="Enter Password">
            <button type="submit" class="wifi_button" id="connect_btn">Connect</button>
        </form>
        </div>

        <!-- Wi-Fi Saved View -->
        <div class="wifi_box hidden" id="saved_view">
        <h2>Wi-Fi Credentials Saved</h2>
        <p>SSID: <span class="ssid_name" id="ssid_saved"></span></p>
        <button class="wifi_button" id="back_btn">Go Back</button>
        </div>
    </body>
  </html>
  )rawliteral";

  request->send(200, "text/html", page);
}

//========================================================================================================================================
void Handle_Wifi_List(AsyncWebServerRequest *request) {

  String json = "[";

  if(scan_complete) 
  {
    bool first = true;

    for(int i = 0; i < wifiSSIDCount; i++) 
    {
      if(wifiSSIDs[i].duplicate) continue;

      if(!first) json += ",";
      first = false;

      json += "{";
      json += "\"ssid\":\"" + String(wifiSSIDs[i].SSID) + "\",";
      json += "\"rssi\":" + String(wifiSSIDs[i].RSSI) + ",";
      json += "\"open\":" + String(wifiSSIDs[i].encryptionType == WIFI_AUTH_OPEN ? "true" : "false");
      json += "}";
    }
  }
  json += "]";

  request->send(200, "application/json", json);
}

//========================================================================================================================================
void WIFI_Init() {

  WiFi.disconnect(true, true);
  delay(100);
  WiFi.mode(WIFI_MODE_APSTA);
  delay(500); 

  delay(500);

  if(WIFI_Connect("", "") != WL_CONNECTED)
  {
    connect_now = false;
    last_scan = 0;

    delay(500);

    DEBUG_PRINT("Configuring access point: " + String(wifi_ap_ssid) + " with password: " + String(wifi_ap_pass) + "\n");
    WiFi.softAP(String(wifi_ap_ssid), String(wifi_ap_pass));

    DEBUG_PRINT("AP Started, IP:" +  WiFi.softAPIP().toString() + "\n");

    if(!SPIFFS.begin(true)) DEBUG_PRINT("An Error has occurred while mounting SPIFFS");

    DNS.setErrorReplyCode(DNSReplyCode::NoError);
    DNS.setTTL(3600);
    if(!DNS.start(53, "*", WiFi.softAPIP())) DEBUG_PRINT("Could not start Captive DNS Server!\n");

    if(MDNS.begin(server_name)) 
    {
      MDNS.addService("http", "tcp", 80);
    }
    else
    {
      DEBUG_PRINT("Error setting up MDNS responder!\n");
    }

    server.on("/connecttest.txt", [](AsyncWebServerRequest *request) { request->redirect("http://logout.net"); });	// windows 11 captive portal workaround
    server.on("/wpad.dat", [](AsyncWebServerRequest *request) { request->send(404); });	

    server.on("/generate_204", [](AsyncWebServerRequest *request) { // android captive portal redirect
      Handle_Wifi(request);
    });
          
    server.on("/redirect", [](AsyncWebServerRequest *request) { // microsoft redirect
      Handle_Wifi(request);
    });

    server.on("/hotspot-detect.html", [](AsyncWebServerRequest *request) { // apple call home
      Handle_Wifi(request);
    });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      Handle_Wifi(request);
    });

    server.on("/wifi_list", HTTP_GET, [](AsyncWebServerRequest * request) {
      Handle_Wifi_List(request);
    });

    server.on("/wifi_save", HTTP_GET, [](AsyncWebServerRequest * request) {
      _ssid = request->arg("ssid").c_str();
      _pass = request->arg("password").c_str();
      connect_now = true;
    });

    server.serveStatic("/background", SPIFFS, "/background.webp").setCacheControl("max-age=86400");
    server.serveStatic("/wifi_loading", SPIFFS, "/wifi_loading.webp").setCacheControl("max-age=86400");

    server.serveStatic("/wifi_locked_full", SPIFFS, "/wifi_locked_full.webp").setCacheControl("max-age=86400");
    server.serveStatic("/wifi_locked_half", SPIFFS, "/wifi_locked_half.webp").setCacheControl("max-age=86400");
    server.serveStatic("/wifi_unlocked_full", SPIFFS, "/wifi_unlocked_full.webp").setCacheControl("max-age=86400");
    server.serveStatic("/wifi_unlocked_half", SPIFFS, "/wifi_unlocked_half.webp").setCacheControl("max-age=86400");

    server.begin();

    while(true)
    {
      DNS.processNextRequest();	

      delay(20);

      WIFI_Scan(shouldscan);

      if(connect_now)
      {
        connect_now = false;
        DEBUG_PRINT("Connecting to new WiFi\n");
        WIFI_Connect(_ssid, _pass);
      }

      if(WiFi.status() == WL_CONNECTED)
      {
        server.end();
        SPIFFS.end();
        DNS.stop();
        MDNS.end();
        WiFi.softAPdisconnect(true);
        DEBUG_PRINT("Exiting Wifi Init\n");
        return;
      }
    }
  }
}

//========================================================================================================================================
void second_core_functions(void * parameter) {

  while(true)
  {
    UDP_Handler();
    if(power) artnet.read();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  } 
}

//========================================================================================================================================
void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data) {
  sendFrame = 1;

  // range check
  if (universe < startUniverse) {
    return;
  }
  uint8_t index = universe - startUniverse;
  if (index >= maxUniverses) {
    return;
  }

  // Store which universe has got in
  universesReceived[index] = true;

  for (int i = 0; i < maxUniverses; i++) {
    if (!universesReceived[i]) {
      sendFrame = 0;
      break;
    }
  }

  // read universe and put into the right part of the display buffer
  for (int i = 0; i < length / 3; i++) {

    int red;
    int green;
    int blue;

    red = data[i * 3];

    green = data[i * 3 + 1];

    blue = data[i * 3 + 2];

    if (i == 0) {
      set_color(1,red,green,blue);
    } else if (i == 1) {
      set_color(2,red,green,blue);
    } else if (i == 2) {
      set_color(3,red,green,blue);
    } else if (i == 3) {
      set_color(4,red,green,blue);
    }
  }
  if (sendFrame) {
    memset(universesReceived, 0, maxUniverses);
  }
}

//========================================================================================================================================
void setup() {

  #if SERIAL_DEBUG != 0 
    Serial.begin(115200);
  #endif

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Wire.begin();
               
  delay(500);

  xTaskCreatePinnedToCore(
    second_core_functions,/* Task function. */
    "SECOND_CORE",        /* String with name of task. */
    10000,                /* Stack size in bytes. */
    NULL,                 /* Parameter passed as input of the task */
    1,                    /* Priority of the task. */
    NULL,                 /* Task handle. */
    0                     /* pin task to core 0 */  
  );              
  delay(500);

  checkI2CConnection(PCA9685_ADDRESS, &Serial);

  pan1.attach(15, START_DEGREE_X);
  pan2.attach(6, START_DEGREE_X);
  pan3.attach(3, START_DEGREE_X);
  pan4.attach(0, START_DEGREE_X);

  tilt1.attach(14, START_DEGREE_Y + Yservo_1_offset);
  tilt2.attach(7, START_DEGREE_Y + Yservo_2_offset);
  tilt3.attach(2, START_DEGREE_Y + Yservo_3_offset);
  tilt4.attach(1, START_DEGREE_Y + Yservo_4_offset);

  //EASE_LINEAR

  int type = EASE_CUBIC_IN_OUT;
  pan1.setEasingType(type);
  pan2.setEasingType(type);
  pan3.setEasingType(type);
  pan4.setEasingType(type);

  tilt1.setEasingType(type);
  tilt2.setEasingType(type);
  tilt3.setEasingType(type);
  tilt4.setEasingType(type);

  ledcAttachChannel(Red1, freq, resolution, 0);
  ledcAttachChannel(Green1, freq, resolution, 1);
  ledcAttachChannel(Blue1, freq, resolution, 2);
  ledcAttachChannel(Red2, freq, resolution, 3);
  ledcAttachChannel(Green2, freq, resolution, 4);
  ledcAttachChannel(Blue2, freq, resolution, 5);
  ledcAttachChannel(Red3, freq, resolution, 6);
  ledcAttachChannel(Green3, freq, resolution, 7);
  ledcAttachChannel(Blue3, freq, resolution, 8);
  ledcAttachChannel(Red4, freq, resolution, 9);
  ledcAttachChannel(Green4, freq, resolution, 10);
  ledcAttachChannel(Blue4, freq, resolution, 11);

  set_color(1, 0, 0, 0);
  set_color(2, 0, 0, 0);
  set_color(3, 0, 0, 0);
  set_color(4, 0, 0, 0);

  WIFI_Init();

  artnet.begin();
  memset(universesReceived, 0, maxUniverses);
  artnet.setArtDmxCallback(onDmxFrame);

  UDP.begin(8888);

  //set default values
  speed_raw = 50;//50% speed
  speed = map(speed_raw, 1, 100, 3000, 300);
  start_up_movement();
}

//========================================================================================================================================
void set_color(int led, int red, int green, int blue) {

  if(led == 1)
  {
    ledcWrite(Red1, red);
    ledcWrite(Green1, green);
    ledcWrite(Blue1, blue);
  }
  else if(led == 2)
  {
    ledcWrite(Red2, red);
    ledcWrite(Green2, green);
    ledcWrite(Blue2, blue);
  }
  else if(led == 3)
  {
    ledcWrite(Red3, red);
    ledcWrite(Green3, green);
    ledcWrite(Blue3, blue);
  }
  else if(led == 4)
  {
    ledcWrite(Red4, red);
    ledcWrite(Green4, green);
    ledcWrite(Blue4, blue);
  }
}

//========================================================================================================================================
void play_effect(int effect_num) {

  if(!power) return;

  if(effect_num == 0)
  {
    if(reset)
    {
      pan1.startEaseToD(90, speed);
      pan2.startEaseToD(90, speed);
      pan3.startEaseToD(90, speed);
      pan4.startEaseToD(90, speed);

      tilt1.startEaseToD(90 + Yservo_1_offset, speed);
      tilt2.startEaseToD(90 + Yservo_2_offset, speed);
      tilt3.startEaseToD(90 + Yservo_3_offset, speed);
      tilt4.startEaseToD(90 + Yservo_4_offset, speed);

      updateAndWaitForAllServosToStop();
      reset = false;
    }
  }
  else if(effect_num == 1)
  {
    cross();
  }
  else if(effect_num == 2)
  {
    cross2();
  }
  else if(effect_num == 3)
  {
    random_twist(); 
  }
  else if(effect_num == 4)
  {
    backandfourth();
  }
  else if(effect_num == 5)
  {
    backandfourth2();
  }
  else if(effect_num == 6)
  {
    leftandright();
  }
  else if(effect_num == 7)
  {
    leftandright2();
  }
  else if(effect_num == 8)
  {
    leftandright3();
  }
  else if(effect_num == 9)
  {
    onebyone();
  }
  else if(effect_num == 10)
  {
    waves();
  }
  else if(effect_num == 11)
  {
    rotate1();
  }
  else if(effect_num == 12)
  {
    rotate2();
  }
  else if(effect_num == 13)
  {
    rotate3();
  }
  else if(effect_num == 14)
  {
    preset1();
  }
  else if(effect_num == 15)
  {
  }
}

//========================================================================================================================================
void UDP_Handler() {

  int packetSize = UDP.parsePacket();
  if(packetSize) 
  {
    // read the packet into packetBufffer
    int n = UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;

    DEBUG_PRINT("Received msg:");
    DEBUG_PRINT(packetBuffer);
    DEBUG_PRINT("\n");
    
    if(strcmp(packetBuffer, "DISCOVER_SPARKY") == 0)
    {
      phone_connected = true;
      phoneIP = UDP.remoteIP();

      delay(100);

      UDP.beginPacket(phoneIP, 8888);
      UDP.write((const uint8_t*)"SPARKY_ACK", strlen("SPARKY_ACK"));
      UDP.endPacket();
    }

    if(strncmp(packetBuffer, "POWER=1", 7) == 0)
    {
      power = true;
    }
    else if(strncmp(packetBuffer, "POWER=0", 7) == 0)
    {
      power = false;
    }

    if(strncmp(packetBuffer, "ARTNET=1", 8) == 0)
    {
      artnet = true;
    }
    else if(strncmp(packetBuffer, "ARTNET=0", 8) == 0)
    {
      artnet = false;
    }

    if(strncmp(packetBuffer, "SPEED=", 6) == 0)
    {
      speed_raw = atoi(packetBuffer + 6);
      //300 is fastest, 3000 is slowest
      speed = map(speed_raw, 1, 100, 3000, 300);
      DEBUG_PRINT("Speed set to ");
      DEBUG_PRINT(String(speed_raw));
      DEBUG_PRINT("% \n");
    }

    if(strncmp(packetBuffer, "EFFECT=", 7) == 0)
    {
      effect = atoi(packetBuffer + 7);
      reset = true;
      DEBUG_PRINT("Effect set to ");
      DEBUG_PRINT(String(effect));
      DEBUG_PRINT("\n");
    }

    if(strncmp(packetBuffer, "R1=", 3) == 0) ledcWrite(Red1, atoi(packetBuffer + 3));
    if(strncmp(packetBuffer, "G1=", 3) == 0) ledcWrite(Green1, atoi(packetBuffer + 3));
    if(strncmp(packetBuffer, "B1=", 3) == 0) ledcWrite(Blue1, atoi(packetBuffer + 3));

    if(strncmp(packetBuffer, "R2=", 3) == 0) ledcWrite(Red2, atoi(packetBuffer + 3));
    if(strncmp(packetBuffer, "G2=", 3) == 0) ledcWrite(Green2, atoi(packetBuffer + 3));
    if(strncmp(packetBuffer, "B2=", 3) == 0) ledcWrite(Blue2, atoi(packetBuffer + 3));

    if(strncmp(packetBuffer, "R3=", 3) == 0) ledcWrite(Red3, atoi(packetBuffer + 3));
    if(strncmp(packetBuffer, "G3=", 3) == 0) ledcWrite(Green3, atoi(packetBuffer + 3));
    if(strncmp(packetBuffer, "B3=", 3) == 0) ledcWrite(Blue3, atoi(packetBuffer + 3));

    if(strncmp(packetBuffer, "R4=", 3) == 0) ledcWrite(Red3, atoi(packetBuffer + 3));
    if(strncmp(packetBuffer, "G4=", 3) == 0) ledcWrite(Green3, atoi(packetBuffer + 3));
    if(strncmp(packetBuffer, "B4=", 3) == 0) ledcWrite(Blue3, atoi(packetBuffer + 3));
  }
}

//========================================================================================================================================
void loop() {

 if(effect == 0)
  {
    if(reset)
    {
      pan1.startEaseToD(90, speed);
      pan2.startEaseToD(90, speed);
      pan3.startEaseToD(90, speed);
      pan4.startEaseToD(90, speed);

      tilt1.startEaseToD(90 + Yservo_1_offset, speed);
      tilt2.startEaseToD(90 + Yservo_2_offset, speed);
      tilt3.startEaseToD(90 + Yservo_3_offset, speed);
      tilt4.startEaseToD(90 + Yservo_4_offset, speed);

      updateAndWaitForAllServosToStop();
      reset = false;
    }
  }
  else if(power && effect == 1)
  {
    cross();
  }
  else if(power && effect == 2)
  {
    cross2();
  }
  else if(power && effect == 3)
  {
    random_twist(); 
  }
  else if(power && effect == 4)
  {
    backandfourth();
  }
  else if(power && effect == 5)
  {
    backandfourth2();
  }
  else if(power && effect == 6)
  {
    leftandright();
  }
  else if(power && effect == 7)
  {
    leftandright2();
  }
  else if(power && effect == 8)
  {
    leftandright3();
  }
  else if(power && effect == 9)
  {
    onebyone();
  }
  else if(power && effect == 10)
  {
    waves();
  }
  else if(power && effect == 11)
  {
    rotate1();
  }
  else if(power && effect == 12)
  {
    rotate2();
  }
  else if(power && effect == 13)
  {
    rotate3();
  }
  else if(power && effect == 14)
  {
    preset1();
    //play_preset("A1,E9,S45,T12,E5,S50,T23,E12,S80,T48,E2,S80,T62,E7,S80,T73");
  }
  else if(power && effect == 15)
  {
  }
}
