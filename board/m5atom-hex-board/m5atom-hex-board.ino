/*
*******************************************************************************
* Board Control via wifi
*******************************************************************************
*/

/*******************************************/
#include <M5Atom.h>
#include <WebServer.h>       
#include <ArduinoJson.h>  
/*******************************************/
#include "Utils.h"
#include "HexRGB.h"
#include "Configuration.h"


uint8_t nextConfId=0;


WebServer httpServer(80);

HexRGB hexRGB(NUM_HEX,BRIGTHNESS);

MyUtils utils(&Serial);

const char hexURI[] = "/hexagons/";

StaticJsonDocument<1000> doc; // Buffer to decode json

struct Hexagon
{
  CRGB colors[HexRGB::HEXRGB_NUM_LEDS];
  String effect;
} hexagons[NUM_HEX];

void init_hexagons()
{
  for (uint8_t hex=0;hex<NUM_HEX; hex++)
  {
    for (int c=0;c<HexRGB::HEXRGB_NUM_LEDS;c++)
    {
      hexagons[hex].colors[c]=CRGB::Black;
    }
    hexagons[hex].effect="plain";
  }
}

uint8_t findNextConfId()
{
  uint8_t i=0;
  String path="/conf";
  path+=i;
  path+=".json";
  while (utils.SPIFFS_exist((char *)path.c_str()))
  {
    i++;
    path="/conf";
    path+=i;
    path+=".json";
  }
  return i;
}

void start_web_server()
{  
  httpServer.onNotFound([]()  
  {   
      if (!utils.HTTP_handleFileRead(&httpServer,httpServer.uri())) // send file corresponding to URI if it exists in SPIFFS
      httpServer.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });

  for (uint8_t hexId=0;hexId<NUM_HEX;hexId++)
  {
    String id=String(hexId);
    httpServer.on(hexURI+id, HTTP_PUT, handleHexUpdate);
  }

  httpServer.on("/upload", HTTP_POST, []() { httpServer.send(201); }, handleFileUpload);
  httpServer.on("/configurations", HTTP_POST, handleConfigSave);  

  httpServer.begin();
  Serial.println("Web Server Started");
}

void handleConfigSave()
{
  // Allocate the JSON document
  JsonDocument doc;

  // Add an array.
  JsonArray board = doc["hexagons"].to<JsonArray>();

  uint8_t max=0;
  for (uint8_t hex=0;hex<NUM_HEX; hex++)
  {
    board[hex]["effect"]=hexagons[hex].effect;

    JsonArray colors=board[hex]["colors"].to<JsonArray>();

    if (hexagons[hex].effect=="plain")
    {
      max=1;
    }
    if (hexagons[hex].effect=="border")
    {
      max=2;
    }    
    for (int c=0;c<max;c++)
    {
      colors[c]["red"]=hexagons[hex].colors[c].r;
      colors[c]["green"]=hexagons[hex].colors[c].g;
      colors[c]["blue"]=hexagons[hex].colors[c].b;      
    }
  }
  //serializeJsonPretty(doc, Serial);
  String path="/conf";
  path+=nextConfId;
  path+=".json";

  utils.SPIFFS_writeFileJSON((char *)path.c_str(),doc);
  nextConfId++;
  httpServer.send(201);
}

void handleFileUpload()
{
  utils.HTTP_handleFileUpload(&httpServer);
}

void updateHexagon(uint8_t hex)
{
  if (hexagons[hex].effect=="plain")
  {
    hexRGB.color(hex, hexagons[hex].colors[0]);
  } 
  else if (hexagons[hex].effect=="border")
  {
    hexRGB.color(hex, hexagons[hex].colors[0]);
    hexRGB.border(hex, hexagons[hex].colors[1],0);
  }
}

void handleHexUpdate()
{  
  CRGB c;
  String uri=String(httpServer.uri());
  uint8_t id=uri.substring(strlen(hexURI)).toInt();
  uint8_t index=0;
  Serial.print("processing hegagon: ");
  Serial.println(id);
 
  deserializeJson(doc, httpServer.arg("plain"));

  hexagons[id].effect=String(doc["effect"]);

  // Get the colors array
  JsonArray colors = doc["colors"];
  
  // Loop through each color object
  for (JsonObject color : colors) {
    // Get the red, green, and blue values
    hexagons[id].colors[index++].setRGB(color["red"], color["green"], color["blue"]);    
  }
    
  // Get the effect and display values
  String display = doc["display"];
 
  httpServer.send(201, "", "");

  updateHexagon(id);

  if (display == "now")
  {
    hexRGB.show();
  }
}

void loadConfiguration(String config)
{
  CRGB c;
  deserializeJson(doc, config);
  uint8_t id=0;

  for (JsonObject hexagon : doc["hexagons"].as<JsonArray>()) {

    hexagons[id].effect = (String)hexagon["effect"];

    uint8_t color_id=0;    
    for (JsonObject color : hexagon["colors"].as<JsonArray>()) {        
      c.setRGB(color["red"], color["green"], color["blue"]);
      hexagons[id].colors[color_id++] = c;
    }
    updateHexagon(id++);
  }  
  hexRGB.show();
}

void activity_led(bool active)
{
  if (active)
  {
    M5.dis.drawpix(0, 0x0000ff);   // Blue on active
  }
  else
  {
    M5.dis.drawpix(0, 0x000000);   // Off on passive
  }
}

void setup() {

  init_hexagons();

  M5.begin(true, false, true);              // Init M5Stack.
  delay(1000);                              // Waiting for init

  Serial.begin(115200);
  Serial.println();
  Serial.println("M5Atom initializing...");

  hexRGB.show();
  utils.SPIFFS_start();

  utils.wifi_start(AccesPoint,SSID_name,SSID_pass,activity_led);
  utils.mdns_start(hostname);
  start_web_server();
  utils.SPIFFS_files();
  nextConfId=findNextConfId();
  Serial.print("Last Configuration ID: ");
  Serial.println(nextConfId);
  //loadConfiguration(utils.SPIFFS_readFile("/conf0.json"));
  M5.dis.drawpix(0, 0x00ff00);              // Green when running
}

void loop(){  
    httpServer.handleClient();
    delay(2);
}
