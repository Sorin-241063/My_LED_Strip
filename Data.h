
void SPIFF_Sketch_Setup(){
  message_.reserve(50);
}

//*******************************************************************************
//****
File inifile;
bool SetupIniEmpty = false; 
#define AnimNumber 4

int Strip_Num = 0;
struct LED_Anim {
  uint8_t STRIP_Mode;       // 0-3 ___ 0=Effekt, 1=RGB, 2=GRB, 3=byOne 
  uint8_t BRIGHTNESS;       // 0-255
  uint8_t RED_Colour;       // 0-255 ___ Effekt Number
  uint8_t GREEN_Colour;     // 0-255
  uint8_t BLUE_Colour;      // 0-255
} STRIP_Data [AnimNumber];   // 1-3
//********************************************************************************
void writeSetupIni(){
  for ( int wsi = 0; wsi <= AnimNumber; wsi++){

    STRIP_Data[wsi].STRIP_Mode = 1;
    STRIP_Data[wsi].BRIGHTNESS = 100;
    STRIP_Data[wsi].RED_Colour = 255;
    STRIP_Data[wsi].GREEN_Colour = 255;
    STRIP_Data[wsi].BLUE_Colour = 255;
  }
}

void write_Setup_file(){
  inifile = SPIFFS.open("/setup.ini", "w");
  inifile.close();
  String buffer_1 = "";
  for (uint8_t wsf = 0; wsf <= AnimNumber; wsf++){
    buffer_1 += wsf;
    buffer_1 += "&";
    buffer_1 += STRIP_Data[wsf].STRIP_Mode;
    buffer_1 += "&";
    buffer_1 += STRIP_Data[wsf].BRIGHTNESS;
    buffer_1 += "&";
    buffer_1 += STRIP_Data[wsf].RED_Colour;
    buffer_1 += "&";
    buffer_1 += STRIP_Data[wsf].GREEN_Colour;
    buffer_1 += "&";
    buffer_1 += STRIP_Data[wsf].BLUE_Colour;
    buffer_1 += "$";
    buffer_1 += '\n';
    inifile = SPIFFS.open("/setup.ini", "a");
    inifile.print(buffer_1);
    inifile.close();
    buffer_1 = "";
  }
}
//********************************************************************************
//****************************************
void analyzeZeile (String str){
  String message_ = "";
  int index = 0;

  if (debug)  Serial.println(str);
  
  int Strip_Num = str.toInt();

  index = str.indexOf("&");
  if(index < 0) return;
    
  message_ = str.substring(index+1);
  STRIP_Data[Strip_Num].STRIP_Mode = message_.toInt();
  
  index = message_.indexOf("&");
  message_ = message_.substring(index+1);
  STRIP_Data[Strip_Num].BRIGHTNESS = message_.toInt();
  
  index = message_.indexOf("&");
  message_ = message_.substring(index+1);
  STRIP_Data[Strip_Num].RED_Colour = message_.toInt();
  
  index = message_.indexOf("&");
  message_ = message_.substring(index+1);
  STRIP_Data[Strip_Num].GREEN_Colour = message_.toInt();

  index = message_.indexOf("&");
  message_ = message_.substring(index+1);
  STRIP_Data[Strip_Num].BLUE_Colour = message_.toInt();
  
}
//********************************************
void read_Setup_file(){

  String      line ;                              // Zeile von .ini Datei

  if ( SPIFFS.exists("/setup.ini")){              // setup.ini  vorchanden?
  
    if (debug) Serial.println("File setup.ini exist");

    inifile = SPIFFS.open ("/setup.ini", "r") ;     // WiFiManager INI-Datei offnen
    if (debug) Serial.println("Read setup.ini");

    if (!inifile.available()) {
      if (debug) Serial.println("File setup.ini is empty");
      SetupIniEmpty = true;
      return;
    }
    while (inifile.available()){
      line = inifile.readStringUntil ('\n') ;      // Zeilenweise lesen
      int i = line.length();
      if (i > 4) analyzeZeile (line.c_str()) ;                  // und in der Funktion analyzeZeile bearbeiten
    }
    inifile.close() ;
    if (debug)  Serial.println("Setup end");

    for (uint8_t rs = 1; rs <= AnimNumber; rs++) {
      Serial.print(rs);
      Serial.print(" - ");
      Serial.print(STRIP_Data[rs].STRIP_Mode);
      Serial.print(" - ");
      Serial.print(STRIP_Data[rs].BRIGHTNESS);
      Serial.print(" - ");
      Serial.print(STRIP_Data[rs].RED_Colour);
      Serial.print(" - ");
      Serial.println(STRIP_Data[rs].GREEN_Colour);
      Serial.print(" - ");
      Serial.println(STRIP_Data[rs].BLUE_Colour);
    }
  }
  else SetupIniEmpty = true;
}

//****************************************************************************
//**** Check Message come from App (must be "x&x&x&x&x&x$", x = number from 0 to 255, max length 20 byte)
void CheckMessage(){
  if (debug) Serial.println("Check Message");
  int MessageLength = message.length()-1;
  if (MessageLength < 29){
    int index = message.indexOf("$");
    if (debug) Serial.printf("Message legth: %i\n", MessageLength);
    if (debug) Serial.printf("Index of $: %i\n", index);
    if (MessageLength == index){
      BLE_messageOK = true;
      if (debug) Serial.println("Message OK");
      BLE_receive = false;
    }
    else {
      BLE_messageOK = false;
      if (debug) Serial.println("Message NOK");
      BLE_receive = false;
    }
  }
}

//******************************************************************************
void ReadMessage(){

  String message_ = "";
  int index = 0;

  Strip_Num = message.toInt();

  index = message.indexOf("&");
  if(index < 0) return;
    
  message_ = message.substring(index+1);
  STRIP_Data[Strip_Num].STRIP_Mode = message_.toInt();
  
  index = message_.indexOf("&");
  message_ = message_.substring(index+1);
  STRIP_Data[Strip_Num].BRIGHTNESS = message_.toInt();
  
  index = message_.indexOf("&");
  message_ = message_.substring(index+1);
  STRIP_Data[Strip_Num].RED_Colour = message_.toInt();
  
  index = message_.indexOf("&");
  message_ = message_.substring(index+1);
  STRIP_Data[Strip_Num].GREEN_Colour = message_.toInt();

  index = message_.indexOf("&");
  message_ = message_.substring(index+1);
  STRIP_Data[Strip_Num].BLUE_Colour = message_.toInt();

  
    Serial.print(Strip_Num);
    Serial.print(" - ");
    Serial.print(STRIP_Data[Strip_Num].STRIP_Mode);
    Serial.print(" - ");
    Serial.print(STRIP_Data[Strip_Num].BRIGHTNESS);
    Serial.print(" - ");
    Serial.print(STRIP_Data[Strip_Num].RED_Colour);
    Serial.print(" - ");
    Serial.print(STRIP_Data[Strip_Num].GREEN_Colour);
    Serial.print(" - ");
    Serial.println(STRIP_Data[Strip_Num].BLUE_Colour);

    Serial.print("map() Value - ");
    Serial.print(map(STRIP_Data[Strip_Num].RED_Colour, 0, 255, 0, STRIP_Data[Strip_Num].BRIGHTNESS+1));
    Serial.print(" - ");
    Serial.print(map(STRIP_Data[Strip_Num].GREEN_Colour, 0, 255, 0, STRIP_Data[Strip_Num].BRIGHTNESS+1));
    Serial.print(" - ");
    Serial.println(map(STRIP_Data[Strip_Num].BLUE_Colour, 0, 255, 0, STRIP_Data[Strip_Num].BRIGHTNESS+1));
}
//****************************************************************************
void NewMessage(){

  //bool mess_equal_file = message.equals("Save");
  //if(debug) Serial.println(mess_equal_file);
  if(message.equals("Save") == true){
    if(debug) Serial.println("Save ");
    BLE_receive = false;

    write_Setup_file();

  }

  else {
    CheckMessage();
    if (BLE_messageOK) ReadMessage();
    BLE_receive = false;
  }
}