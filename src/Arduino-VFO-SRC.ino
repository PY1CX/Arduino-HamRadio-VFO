/****************************************************
*  LCD Includes & Proto Functions
****************************************************/
//LiquidCrystal library
#include <LiquidCrystal.h>

#define RS 12
#define EN 13
#define DB4 7
#define DB5 6
#define DB6 5
#define DB7 4

//HD47780 4bit mode
LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);

float i = 7100;
void setup_lcd(void);

/****************************************************
* Encoder Includes & Proto Functions
****************************************************/
#include <Rotary.h>

//Encoder result as a global variable
unsigned char result;

Rotary encoder = Rotary(3, 2);
void setup_encoder(void);


/****************************************************
* Switchs Defines & Proto Functions
****************************************************/
#define SW4 A2
#define SW3 A3
#define SW2 A4
//Switch Encoder
#define SW1 A5

static int band_index;

#define band_max 3
int bands[band_max]
{
    7000,
    14000,
    21000
};

#define step_max 5
int stepsize[step_max]
{
  1,
  10,
  100,
  1000,
  10000
};

float freq;

#define DEBUG

/****************************************************
* Band Output Pins
****************************************************/
#define BAND1 A1
#define BAND2 A0
//3rd BAND isn't on a Pin capable of I/O, only Analog Input
//#define BAND3 

void setup_bandIO(void);

/****************************************************
* 
* General Setup Function
* 
****************************************************/
void setup() {
  //If defined DEBUG, initialize the Serial Port
#ifdef DEBUG
  Serial.begin(115200);
#endif
  setup_bandIO();  //Bring-up Band Switch Output
  setup_sw();      //Bring-up Switches
  setup_lcd();     //Bring-up LCD
  setup_encoder(); //Bring-up Rotary Encoder

}

/****************************************************
* 
* General Main Function
* 
****************************************************/
void loop() {
  // put your main code here, to run repeatedly:
  //printlcd();
  
}

/****************************************************
* BandIO Setup
****************************************************/
void setup_bandIO()
{
  pinMode(BAND1, OUTPUT);
  pinMode(BAND2, OUTPUT);
  //pinMode(BAND3, OUTPUT);
}


/****************************************************
* Switch Setup
****************************************************/
void setup_sw(void)
{
  pinMode(SW4, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW1, INPUT);
  //Enable PC Interrupt on SW pins
  PCICR  |=  (1 << PCIE1);
  // Enables the interrupt in the SW pins
  PCMSK1 |= (1 << PCINT10) | (1 << PCINT11) | (1 << PCINT12) |(1 << PCINT13);   
}

/****************************************************
* Interrupt Service Routine for the Switchs
****************************************************/
ISR(PCINT1_vect)
{
  int bandup = digitalRead(SW4);
  int SW33 = digitalRead(SW3);
  int SW22 = digitalRead(SW2);
  int SW11 = digitalRead(SW1);
  
  //Band-Up
  if(bandup == 0)
  { 
      band_index += 1;
      if( band_index > 3){ band_index = 0;}
  }
  
  if(SW33 == 0){ lcd.setCursor (0,1); lcd.print("33");}
  if(SW22 == 0){ lcd.setCursor (0,1); lcd.print("22");}
  if(SW11 == 0){ lcd.setCursor (0,1); lcd.print("11");}
}

void printlcd(void)
{ 
  if(digitalRead(SW4) == 0)
    {
    band_index++;
    if(band_index >= band_max)
    {
      band_index = 0;
    }
    freq = 0;
    freq = bands[band_index];
    lcd.setCursor(0, 1);
    lcd.print(freq);
    Serial.println(freq);
    delay(100);
  }
}


/****************************************************
* LCD Setup
****************************************************/
void setup_lcd(void)
{
  lcd.begin(16, 2);
  lcd.print(" PY1CX - Felipe");
  lcd.setCursor(0, 1);
  lcd.print("Arduino VFO V1.0");
}

/****************************************************
* Encoder Interrupt Setup
****************************************************/
void setup_encoder(void)
{
  // Enables the Pin Change Interrupt on Encoder pins
  PCICR  |= (1 << PCIE2); 
  // Pin Change Interrupt Control Register
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);
  // Direct to the interrupt Pin PD2 and PD3
  // PD2 (PCINT18) and PD3 (PCINT19)
  sei(); //Enables interrupt
}

/****************************************************
* Interrupt Service Routine for the Encoder
****************************************************/
ISR(PCINT2_vect)
{
  result = encoder.process();
  if (result == DIR_NONE) {
    // do nothing
  }
  else if (result == DIR_CW) {
    i = i+1;
    lcd.setCursor(0, 1);
    lcd.print(i);lcd.print("            ");
  }
  else if (result == DIR_CCW) {
    i = i-1;
    lcd.setCursor(0, 1);
    lcd.print(i);lcd.print("            ");
  }
}
