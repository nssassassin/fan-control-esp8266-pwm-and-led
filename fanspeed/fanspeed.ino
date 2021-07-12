/*
    Basic control for 6 PWM channels at 25 KHz and some LED effects for 3.
    Copyright (C) 2021  Nssassassin

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <avr/pgmspace.h>
#include "index.h"
#include <sstream>
#include <string>   // std::string
#include <iostream> // std::cout
//#include <ESPFlash.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WiFi.h>
#include <FastLED.h>
//#include <WebServer.h>
#include <Arduino.h>

extern "C"{
  #include "pwm.h"
  #include "user_interface.h"
}
//DEFINE FOR PWM
//The setup function is called once at startup of the sketch
//For this to work you need to define the amount of PWM channels
#define PWM_CHANNELS 6
//Then define the frequency
long freq = 25000;
//Work out pwm period
double per = 1.0/freq;
double divider = 0.0000002;
const uint32_t period = per/divider;

//Deprecated
//const uint32_t period = 200; // * 200ns ^= 25 kHz 0.00004 seconds  
uint32 io_info[PWM_CHANNELS][3] = {
   // MUX,          FUNC,     PIN
// {PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5,   5}, // D1
   {PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4,   4}, // D2
   {PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0,   0}, // D3
   {PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2 ,  2},//D4
   {PERIPHS_IO_MUX_MTMS_U,  FUNC_GPIO14, 14},//D5
   {PERIPHS_IO_MUX_MTDI_U,  FUNC_GPIO12, 12},//D6
   {PERIPHS_IO_MUX_MTCK_U,  FUNC_GPIO13, 13},//D7
   //{PERIPHS_IO_MUX_MTDO_U,  FUNC_GPIO15, 15},//D8
   //{PERIPHS_IO_MUX_SD_DATA3_U,  FUNC_GPIO10, 10},//SD3
   
   };
// initial duty: all off
uint32 pwm_duty_init[PWM_CHANNELS] = {0, 0, 0, 0, 0, 0};
//END DEFINE PWM


//LOCAL VARIABLES
uint8_t currentDuty[PWM_CHANNELS] = {0, 15, 30, 45, 60, 75};

//Start Webserver and update server
#define OTAUSER "admin"     // Set OTA user
#define OTAPASSWORD "admin" // Set OTA password
#define OTAPATH "/update"   // Set path for update
#define SERVERPORT 80       // Server port
//ESP8266WebServer myServer(SERVERPORT);
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer server(SERVERPORT);
const char *ssid = "PWM control";
const char *password = "a1b2c3d4e5";

//test
//double supposedOutput = 0;
//uint8_t currentDutyperc = 10;
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void sendPWMvalues1()
{
  //int a = analogRead(A0);
  String pwmVal = String(currentDuty[0]);
  //String PWM = String(a);
  server.send(200, "text/plane", pwmVal); //Send ADC value only to client ajax request
  Serial.println("Sent: " + pwmVal );
}
void sendPWMvalues2()
{
  //int a = analogRead(A0);
  String pwmVal = String(currentDuty[1]);
  //String PWM = String(a);
  server.send(200, "text/plane", pwmVal); //Send ADC value only to client ajax request
  Serial.println("Sent: " + pwmVal );
}
void sendPWMvalues3()
{
  //int a = analogRead(A0);
  String pwmVal = String(currentDuty[2]);
  //String PWM = String(a);
  server.send(200, "text/plane", pwmVal); //Send ADC value only to client ajax request
  Serial.println("Sent: " + pwmVal );
}
void sendPWMvalues4()
{
  //int a = analogRead(A0);
  String pwmVal = String(currentDuty[3]);
  //String PWM = String(a);
  server.send(200, "text/plane", pwmVal); //Send ADC value only to client ajax request
  Serial.println("Sent: " + pwmVal );
}
void sendPWMvalues5()
{
  //int a = analogRead(A0);
  String pwmVal = String(currentDuty[4]);
  //String PWM = String(a);
  server.send(200, "text/plane", pwmVal); //Send ADC value only to client ajax request
  Serial.println("Sent: " + pwmVal );
}
void sendPWMvalues6()
{
  //int a = analogRead(A0);
  String pwmVal = String(currentDuty[5]);
  //String PWM = String(a);
  server.send(200, "text/plane", pwmVal); //Send ADC value only to client ajax request
  Serial.println("Sent: " + pwmVal );
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
// Set pins (Important! All Pins must be initialized, the PWM SDK cannot work without this
  Serial.println("Set PWM Pin OUTPUT");
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  Serial.println("Set PWM Pin LOW");
  // pinMode(D8, OUTPUT);
  //pinMode(10, OUTPUT);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  // digitalWrite(D8, LOW);
  //digitalWrite(10, LOW);
  // FastLED
  Serial.println("Set PWM Pin LOW and start PWM");
  pwm_init(period, pwm_duty_init, PWM_CHANNELS, io_info);
  pwm_start();
  Serial.println("START WIFI AP");
  WiFi.mode(WIFI_AP); //Access Point mode
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.print("Start server");
  server.on("/", handleRoot);      //This is display page
  server.on("/getPWM1", sendPWMvalues1);//To get update of PWM Value only
  server.on("/getPWM2", sendPWMvalues2);//To get update of PWM Value only
  server.on("/getPWM3", sendPWMvalues3);//To get update of PWM Value only
  server.on("/getPWM4", sendPWMvalues4);//To get update of PWM Value only
  server.on("/getPWM5", sendPWMvalues5);//To get update of PWM Value only
  server.on("/getPWM6", sendPWMvalues6);//To get update of PWM Value only

  httpUpdater.setup(&server, OTAPATH, OTAUSER, OTAPASSWORD);



  server.begin();                  //Start server
}
void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
EVERY_N_MILLISECONDS(3000){

  for(int i = 0; i<6;i++)
  {
    pwmpercentSetDuty(currentDuty[i],i);
  }
  delay(1);
}





/*
  for(int i = 0; i<5;i++)
  {
    pwmpercentSetDuty(currentDutyperc,i);
  }
  
  supposedOutput = 3.3*currentDutyperc /100.0;
  
  

  Serial.print("Output voltage: ");
  Serial.print(supposedOutput);
  Serial.print(" Current percentage: ");  
  Serial.print(currentDutyperc);
  Serial.println();

  currentDutyperc+=10;
  if(currentDutyperc>100){
    currentDutyperc = 10;
  }
  delay(500);
*/
}
void pwmpercentSetDuty(uint8_t input, uint8_t channel)
{
  //This takes values from 0 to 100, because, hell thats easy
  if(input>100)
  {
    input = 100;
  }
  uint8_t outputPeriod;
  outputPeriod = input*2;

  pwm_set_duty(outputPeriod, channel);
  pwm_start();
}
/*
You can use any of the GPIOs 0 to 15, you just have to set the pin function correctly. Pin function registers are:
GPIO0: PERIPHS_IO_MUX_GPIO0_U
GPIO1: PERIPHS_IO_MUX_U0TXD_U
GPIO2: PERIPHS_IO_MUX_GPIO2_U
GPIO3: PERIPHS_IO_MUX_U0RXD_U
GPIO4: PERIPHS_IO_MUX_GPIO4_U
GPIO5: PERIPHS_IO_MUX_GPIO5_U
GPIO6: PERIPHS_IO_MUX_SD_CLK_U
GPIO7: PERIPHS_IO_MUX_SD_DATA0_U
GPIO8: PERIPHS_IO_MUX_SD_DATA1_U
GPIO9: PERIPHS_IO_MUX_SD_DATA2_U
GPIO10: PERIPHS_IO_MUX_SD_DATA3_U
GPIO11: PERIPHS_IO_MUX_SD_CMD_U
GPIO12: PERIPHS_IO_MUX_MTDI_U
GPIO13: PERIPHS_IO_MUX_MTCK_U
GPIO14: PERIPHS_IO_MUX_MTMS_U
GPIO15: PERIPHS_IO_MUX_MTDO_U
 */
