/*
  Sorin Dean
  Complete project details at 

  3x LED RGB Stripe, Bluetooth App

  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
/*
From App will receive:
1-3     -Strip Number
&
1-3     -Connected Sripe Mode (1=RGB, 2=GRB, 3= ByOne)
&
0-255   -Brightness in RGB and GRB Mode 
&
0-255   -Red colour
&
0-255   -Green colour
&
0-255   -Blue colour
$
*/
//**** Debug Serial ************************************************************
bool debug = true;
//**************** Library required for Scketch ********************************
#include "SPIFFS.h"
#include "WiFi.h"


String message;
bool BLE_receive = false;
bool BLE_receive_file = false;
bool BLE_messageOK = false;

String message_;

//******************************************************************************

int currentMillis = 0;
int previousMillis = 0;

int stripMillis = 0;
//******************************************************************************
int connectMillis = 0;


//******************************************************************************
#include "Bluetooth.h"
#include "Data.h"

#include "LEDShow.h"

//******************************************************************************
//**** Subroutines
//******************************************************************************


//******************************************************************************
//******************************************************************************

//******************************************************************************
// SETUP
//******************************************************************************
void setup(){
//**** Serial port for debugging purposes
  Serial.begin(115200);
//**** Ini SPIFFS
  if(!SPIFFS.begin(true)){
    if (debug) Serial.println("SPIFFS Mount Failed");
    return;
  }
  else if (debug) Serial.println("SPIFFS mounting = OK");
//**** Read setup.ini
  SPIFF_Sketch_Setup();
  read_Setup_file();
  
  if (SetupIniEmpty) {
    writeSetupIni();
    //write_Setup_file();
    SetupIniEmpty = false;
  } 
//******* for BLE **************
  BLE_Sketch_Setup();
//******* for LEDShow **********
  LED_Sketch_Setup();



//******************************************************************************

//******************************************************************************


}
//******************************************************************************
// end of SETUP
//******************************************************************************

//******************************************************************************
// LOOP
//******************************************************************************
void loop(){

//*********************************
  if (!deviceConnected){
    currentMillis = millis();
    if (currentMillis - connectMillis > 2000){
      connectMillis = currentMillis;
      pServer->getAdvertising()->start();
    }
  }
//*********************************
  if (BLE_receive) NewMessage();
//*********************************
  if (Strip_Num == 0 && STRIP_Data[0].STRIP_Mode == 0) Show_effects();
  else Show_manual();
//*********************************

  

}
//******************************************************************************
// end of LOOP
//******************************************************************************