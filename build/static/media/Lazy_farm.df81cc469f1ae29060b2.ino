#include "DHT.h"
#include <TimeLib.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#define DHTPIN 2    
#define DHTTYPE DHT22  
int Value1,Value2,Value3,Value4;
#define soil1 36
#define soil2 37
#define soil3 38
#define soil4 39
#define Solinoid 13
#define Motor 17
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
 float t ;
 float h ;
  String Output;
    String Date;
const char ssid[] = "realme 7i";  //  your network SSID (name)
const char pass[] = "12345678";       // your network password
const char* host = "192.168.85.151";
  int a,b,c,d,fin;
// NTP Servers:
static const char ntpServerName[] = "pool.ntp.org";

const int timeZone = 7;     // UTC

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);
void printDigitsOled();
void watersensing();
void sqlclient();
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
    pinMode(Solinoid,OUTPUT);
    pinMode(Motor,OUTPUT);
  lcd.init();   
  lcd.backlight();
  lcd.clear();
    lcd.setCursor(3,0);
  lcd.print("Dr.Daeng Ja ahe");                   
  dht.begin();
  delay(250);
  Serial.println("TimeNTP Example");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.disconnect();
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("IP number assigned by DHCP is ");
  Serial.println(WiFi.localIP());
  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
//  Serial.println(Udp.localPort());
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  setSyncInterval(300);
  delay(1000); 
}
time_t prevDisplay = 0;
void loop() {
  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      digitalClockDisplay();
    }
  }
 watersensing();
 if(second() == 0 || second()==1 )
 {
 sqlclient();
 }
}
void sqlclient()
{
      Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }
    // This will send the request to the server
 client.print(String("GET http://192.168.246.151/abcd/insert_data.php?") +
                          ("&soli1=") + Value1+
                          ("&soli2=") + Value2+
                          ("&soli3=") + Value3+
                          ("&soli4=") + Value4+
                          ("&temp=") + t +
                          ("&humi=") + h +
                          " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 1000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        
    }

    Serial.println();
    Serial.println("closing connection");
}
void watersensing()
{
 a=analogRead(soil1);
 b=analogRead(soil2);
 c=analogRead(soil3);
 d=analogRead(soil4);
 Value1=map(a,1503,4095,100,0);
 Value2=map(b,1587,4095,100,0);
 Value3=map(c,1637,4095,100,0);
 Value4=map(d,1577,4095,100,0);
 t = dht.readTemperature();
 h = dht.readHumidity();
 fin=(Value1+Value2+Value3+Value4)/4;
     if(hour()==12||hour()==17)
   { 
    if(fin<50)  
    {
      digitalWrite(Solinoid,LOW);
    }
    if(fin>=65)
    {
      digitalWrite(Solinoid,HIGH);
    }
   }
   else if (hour() !=12||hour ()!=17)
   {
    digitalWrite(Solinoid,HIGH);
   }
      if(day() ==16||day() == 1)
   {
        if(hour() ==18&&minute() <=1)
          {
            digitalWrite(Motor,LOW);
            Serial.println("ON");
          }
        else if(hour()!=18||minute() >1)
        {
            digitalWrite(Motor,HIGH);
        }
   }
      else if(day()!=1||day()!=16)
      {
        digitalWrite(Motor,HIGH);
      }
    Serial.println(a);
    Serial.println("1");
 Serial.println(b);
 Serial.println(c);
 Serial.println(d);
  lcd.setCursor(0,0);
  lcd.print("Soli moisture "+String(fin)+" %");
    lcd.setCursor(0,1);
  lcd.print("Temp "+String(t)+" c");
    lcd.setCursor(0,2);
  lcd.print("Humidity "+String(h)+" %");
      lcd.setCursor(0,3);
  lcd.print(Output);
  delay(100);
}
void digitalClockDisplay()
{
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  printDigitsOled();
  Serial.print(" ");
  Serial.print(day());
  Serial.print(".");
  Serial.print(month());
  Serial.print(".");
  Serial.print(year());
  Serial.println();
  Date=String(day())+":"+String(month())+":"+String(year());
}

void printDigits(int digits)
{
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
void printDigitsOled()
{
  int Hour,Min,Sec;
  Hour = hour();Min=minute();Sec=second();
  if(Min<10)
  {
      if(Sec<10)
      {
        Output = String(Hour)+":"+"0"+String(Min)+":"+"0"+String(Sec); 
      }
    Output = String(Hour)+":"+"0"+String(Min)+":"+String(Sec); 
  }
  if(Sec<10)
  {
      if(Min<10)
      {
        Output = String(Hour)+":"+"0"+String(Min)+":"+"0"+String(Sec); 
      }
    Output = String(Hour)+":"+String(Min)+":"+"0"+String(Sec); 
  }
  else
  {
    Output = String(Hour)+":"+String(Min)+":"+String(Sec); 
  }
}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
