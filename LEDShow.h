
//******************************************************************************
//**** Setup
//******************************************************************************

const int freq = 500;
const int resolution = 8;
int dutyCycle = 0;
//**** LED RGB Strip Hardware definitionen *************************************
#define PinLED1_1  23         // Green Strip1
#define PinLED2_1  22         // Red Strip1
#define PinLED3_1  21         // Blue Strip1
#define PinLED1_2  19         // Green Strip2
#define PinLED2_2  18         // Red Strip2
#define PinLED3_2  5          // Blue Strip2
#define PinLED1_3  17         // Green Strip3
#define PinLED2_3  16         // Red Strip3
#define PinLED3_3  4          // Blue Strip3
//**** PWM Chanels *************************************************************
const int LED1_1 = 0;
const int LED2_1 = 1;
const int LED3_1 = 2;
const int LED1_2 = 3;
const int LED2_2 = 4;
const int LED3_2 = 5;
const int LED1_3 = 6;
const int LED2_3 = 7;
const int LED3_3 = 8;

//******************************************************************************
void LED_Sketch_Setup(){
  pinMode(PinLED1_1, OUTPUT);
  pinMode(PinLED2_1, OUTPUT);
  pinMode(PinLED3_1, OUTPUT);
  pinMode(PinLED1_2, OUTPUT);
  pinMode(PinLED2_2, OUTPUT);
  pinMode(PinLED3_2, OUTPUT);
  pinMode(PinLED1_3, OUTPUT);
  pinMode(PinLED2_3, OUTPUT);
  pinMode(PinLED3_3, OUTPUT);

  ledcSetup(LED1_1, freq, resolution);
  ledcSetup(LED2_1, freq, resolution);
  ledcSetup(LED3_1, freq, resolution);
  ledcSetup(LED1_2, freq, resolution);
  ledcSetup(LED2_2, freq, resolution);
  ledcSetup(LED3_2, freq, resolution);
  ledcSetup(LED1_3, freq, resolution);
  ledcSetup(LED2_3, freq, resolution);
  ledcSetup(LED3_3, freq, resolution);

  ledcAttachPin(PinLED1_1, LED1_1);
  ledcAttachPin(PinLED2_1, LED2_1);
  ledcAttachPin(PinLED3_1, LED3_1);
  ledcAttachPin(PinLED1_2, LED1_2);
  ledcAttachPin(PinLED2_2, LED2_2);
  ledcAttachPin(PinLED3_2, LED3_2);
  ledcAttachPin(PinLED1_3, LED1_3);
  ledcAttachPin(PinLED2_3, LED2_3);
  ledcAttachPin(PinLED3_3, LED3_3);
}

//******************************************************************************
//**** TEST all LED´s 
//******************************************************************************
void LED_Test(){
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(LED1_1, dutyCycle);
  }
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(LED2_1, dutyCycle);
  }
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(LED3_1, dutyCycle);
  }
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(LED1_2, dutyCycle);
  }
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(LED2_2, dutyCycle);
  }
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(LED3_2, dutyCycle);
  }
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(LED1_3, dutyCycle);
  }
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(LED2_3, dutyCycle);
  }
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(LED3_3, dutyCycle);
  }

  dutyCycle = 0;
  ledcWrite(LED1_1, dutyCycle);
  ledcWrite(LED2_1, dutyCycle);
  ledcWrite(LED3_1, dutyCycle);
  ledcWrite(LED1_2, dutyCycle);
  ledcWrite(LED2_2, dutyCycle);
  ledcWrite(LED3_2, dutyCycle);
  ledcWrite(LED1_3, dutyCycle);
  ledcWrite(LED2_3, dutyCycle);
  ledcWrite(LED3_3, dutyCycle);
}
//*****************************************************************************
//
//*****************************************************************************
void Strip_RGB(int Strip_num){
    ledcWrite((Strip_num - 1)*3, map(STRIP_Data[Strip_num].RED_Colour, 0, 255, 0, STRIP_Data[Strip_num].BRIGHTNESS+1));
    ledcWrite(((Strip_num - 1)*3) + 1, map(STRIP_Data[Strip_num].GREEN_Colour, 0, 255, 0, STRIP_Data[Strip_num].BRIGHTNESS+1));
    ledcWrite(((Strip_num - 1)*3) + 2, map(STRIP_Data[Strip_num].BLUE_Colour, 0, 255, 0, STRIP_Data[Strip_num].BRIGHTNESS+1));

}
//********************************
void Strip_GRB(int Strip_num){
    ledcWrite((Strip_num - 1)*3, map(STRIP_Data[Strip_num].GREEN_Colour, 0, 255, 0, STRIP_Data[Strip_num].BRIGHTNESS+1));
    ledcWrite(((Strip_num - 1)*3) + 1, map(STRIP_Data[Strip_num].RED_Colour, 0, 255, 0, STRIP_Data[Strip_num].BRIGHTNESS+1));
    ledcWrite(((Strip_num - 1)*3) + 2, map(STRIP_Data[Strip_num].BLUE_Colour, 0, 255, 0, STRIP_Data[Strip_num].BRIGHTNESS+1));

}
//********************************
void Strip_by_one(int Strip_num){
  
    ledcWrite((Strip_num - 1)*3, STRIP_Data[Strip_num].RED_Colour);
    ledcWrite(((Strip_num - 1)*3) + 1, STRIP_Data[Strip_num].GREEN_Colour);
    ledcWrite(((Strip_num - 1)*3) + 2, STRIP_Data[Strip_num].BLUE_Colour);
  
}
//*****************************************************************************
//*** Manual comands
//*****************************************************************************
void Show_manual(){
  currentMillis = millis();
  if (currentMillis - stripMillis > 500){
    stripMillis = currentMillis;
    if (STRIP_Data[Strip_Num].STRIP_Mode == 1) Strip_RGB(Strip_Num);
    if (STRIP_Data[Strip_Num].STRIP_Mode == 2) Strip_GRB(Strip_Num);
    if (STRIP_Data[Strip_Num].STRIP_Mode == 3) Strip_by_one(Strip_Num);
  }
}

//*****************************************************************************
//*** Effects
//*****************************************************************************
struct LED_Write {
  uint8_t R;       // 0-255
  uint8_t G;       // 0-255
  uint8_t B;       // 0-255
} STRIP[3];
//*****************************************************************************
void Show_effects(){
  if (STRIP_Data[0].RED_Colour == 10){        // first effect - Rainbow 


  }

  
}
//******************************************************************************
//
//******************************************************************************
void LED_Stripe_Write(){
  switch (STRIP_Data[0].GREEN_Colour){
    case 1:
      ledcWrite(LED1_1, STRIP[0].R);
      ledcWrite(LED2_1, STRIP[0].G);
      ledcWrite(LED3_1, STRIP[0].B);
      break;
    case 2:
      ledcWrite(LED1_2, STRIP[1].R);
      ledcWrite(LED2_2, STRIP[1].G);
      ledcWrite(LED3_2, STRIP[1].B);
      break;
    case 3:
      ledcWrite(LED1_1, STRIP[0].R);
      ledcWrite(LED2_1, STRIP[0].G);
      ledcWrite(LED3_1, STRIP[0].B);
      ledcWrite(LED1_2, STRIP[1].R);
      ledcWrite(LED2_2, STRIP[1].G);
      ledcWrite(LED3_2, STRIP[1].B);
      break;
    case 4:
      ledcWrite(LED1_3, STRIP[2].R);
      ledcWrite(LED2_3, STRIP[2].G);
      ledcWrite(LED3_3, STRIP[2].B);
      break;
    case 5:
      ledcWrite(LED1_1, STRIP[0].R);
      ledcWrite(LED2_1, STRIP[0].G);
      ledcWrite(LED3_1, STRIP[0].B);
      ledcWrite(LED1_3, STRIP[2].R);
      ledcWrite(LED2_3, STRIP[2].G);
      ledcWrite(LED3_3, STRIP[2].B);
      break;
    case 6:
      ledcWrite(LED1_2, STRIP[1].R);
      ledcWrite(LED2_2, STRIP[1].G);
      ledcWrite(LED3_2, STRIP[1].B);
      ledcWrite(LED1_3, STRIP[2].R);
      ledcWrite(LED2_3, STRIP[2].G);
      ledcWrite(LED3_3, STRIP[2].B);
      break;
    case 7:
      ledcWrite(LED1_1, STRIP[0].R);
      ledcWrite(LED2_1, STRIP[0].G);
      ledcWrite(LED3_1, STRIP[0].B);
      ledcWrite(LED1_2, STRIP[1].R);
      ledcWrite(LED2_2, STRIP[1].G);
      ledcWrite(LED3_2, STRIP[1].B);
      ledcWrite(LED1_3, STRIP[2].R);
      ledcWrite(LED2_3, STRIP[2].G);
      ledcWrite(LED3_3, STRIP[2].B);
      break;
  }
}
