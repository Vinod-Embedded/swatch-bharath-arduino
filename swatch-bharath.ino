#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#define ROW1 0
#define ROW2 2
#define ROW3 3
#define ROW4 A5
#define MP 6
#define MN 7

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
SoftwareSerial esp(4,5);

String ssid ="iot";                    
String password="iot12345";

void setup() 
{
  Serial.begin(9600);
  esp.begin(9600);
  pinMode(ROW1,INPUT);
  pinMode(ROW2,INPUT);
  pinMode(ROW3,INPUT);
  pinMode(ROW4,INPUT);
  pinMode(MP,OUTPUT);
  pinMode(MN,OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Swatch bharath"); 
  lcd.setCursor(0, 1);
  lcd.print("Dust collection"); 
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("Conecting wifi.."); 
  lcd.setCursor(0, 1);
  lcd.print("checking...     ");
  delay(600);
  if(connectwifi())
  { 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wifi Conected!"); 
    delay(2000);
  } 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Collecting Dust");
}

void loop() 
{
  int a,b,c,d;
  while(digitalRead(ROW1)==0 && digitalRead(ROW2)==0 && digitalRead(ROW3)==0 && digitalRead(ROW4)==0);

  a=digitalRead(ROW1);  
  b=digitalRead(ROW2); 
  c=digitalRead(ROW3);
  d=digitalRead(ROW4);
  
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println(d);
  
  if(a==1) {
    // Floor 1
    Serial.println("Collecting Dust");
    Serial.println("Floor 1");
    lcd.setCursor(0, 0);
    lcd.print("Collecting Dust");
    lcd.setCursor(0, 1);
    lcd.print("Floor 1  ");
    digitalWrite(MP,1);
    delay(800);
    digitalWrite(MP,0);
    post("1");
    //delay(300);
    delay(3000);
  } else if(b==1) {
    // Floor 2
    Serial.println("Collecting Dust");
    Serial.println("Floor 2");
    lcd.setCursor(0, 0);
    lcd.print("Collecting Dust");
    lcd.setCursor(0, 1);
    lcd.print("Floor 2  ");
    digitalWrite(MP,1);
    delay(800);
    digitalWrite(MP,0);
    post("2");
    //delay(300);
    delay(3000);
  } else if(c==1) {
    // Floor 3
    Serial.println("Collecting Dust");
    Serial.println("Floor 3");
    lcd.setCursor(0, 0);
    lcd.print("Collecting Dust");
    lcd.setCursor(0, 1);
    lcd.print("Floor 3  ");
    digitalWrite(MP,1);
    delay(800);
    digitalWrite(MP,0);
    post("3");
    //delay(300);
    delay(3000);
  } else if(d==1) {
    //Ground Floor
    lcd.setCursor(0, 1);
    lcd.print("GND Floor");
    digitalWrite(MP,0);
    digitalWrite(MN,1);
    delay(2300);
    digitalWrite(MN,0);
    post("0");
  }
  delay(1000);
  Serial.println("");
}

void post(String value1)
{
  // Paste the website of yours
  String server = "www.orangewebtools.com";   
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += server; 
  cmd += "\",80";
  esp.println(cmd);
  response();
  delay(500);
  String uri ="/Swachbharat/entry.php"; 
  uri += "?a=" + value1;

  String getStr = "GET " + uri + " HTTP/1.0\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n";
  
  String str = "AT+CIPSEND=";
  str += String(getStr.length());
  esp.println(str);
  response();
  delay(100);
  if(esp.find(">"))  
  {
    esp.println(getStr);
    showResponse(1000);
  }
}

void response()
{
  while(esp.available()!=0)
  Serial.write(char (esp.read()));
}

void showResponse(int waitTime)
{
  long t=millis();
  char c;
  while (t+waitTime>millis())
  {
  if (esp.available()>0)
  {
    c=esp.read();
    Serial.print(c);
   }
  }               
}

int connectwifi()
{
  String cmd ="AT+CWJAP=\"" + ssid + "\",\"" + password + "\"";
  esp.println(cmd);
  delay(5000);
  if(esp.find("WIFI CONNECTED"))
  {
    Serial.println("Wifi Connected");
    return 1;
  }
  else
  {
    Serial.println("connecting wifi...");
    connectwifi(); 
    delay(1000);
   }
}
