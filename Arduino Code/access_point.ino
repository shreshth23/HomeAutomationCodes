#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Servo.h>
#include <DHT.h>

#define DHTPIN D8
#define DHTTYPE DHT11

//const char* ssid = "JioFiber-tfy84";
//const char* password = "humdohumaredo";
const char* ssid = "The Inter";
const char* password = "00100011";

const String host = "http://192.168.16.219:8080/_01/Service?s=";

Servo door;
DHT dht(DHTPIN, DHTTYPE);

HTTPClient http;
WiFiClient wificlient;

void setup() {
  Serial.begin(9600);

  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D6,OUTPUT);
  
  pinMode(D3, OUTPUT);
  pinMode(A0, INPUT);
   
  pinMode(D5,INPUT);
  pinMode(D4,INPUT);

  door.attach(D0);
  dht.begin();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  toggleLight1();
  toggleLight2();
  toggleLight3();
  toggleLight4();
  security();
  sendTemp();
  fireSense();
}

void sendTemp() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String url = "http://192.168.16.219:8080/_01/value?temp=" + String(t) + "&humd=" + String(h);
  Serial.println(h);
  http.begin(wificlient, url);
  http.GET();
}

void fireSense(){
  int data = digitalRead(D5);
  //    Serial.println(data);
  String url = host + "D5";
  http.begin(wificlient, url);
  http.GET();
  int state = http.getString().toInt();
  if (data == 1||state==1) {
    digitalWrite(D3, HIGH);
    if (state == 0) {
      String url = "http://192.168.16.219:8080/_01/toggle?t=D5";
      http.begin(wificlient, url);
      http.GET();
    }
    return;
  }
  digitalWrite(0, LOW);
}


void security() {
  int data = analogRead(A0);
  //    Serial.println(data);
  String url = host + "A0";
  http.begin(wificlient, url);
  http.GET();
  int state = http.getString().toInt();
  if (data < 100 || state == 1) {
    digitalWrite(D3, HIGH);
    if (state == 0) {
      String url = "http://192.168.16.219:8080/_01/toggle?t=A0";
      http.begin(wificlient, url);
      http.GET();
    }
    return;
  }
  digitalWrite(0, LOW);
}

void toggleLight1() {
  String url = host + "D0";
  http.begin(wificlient, url);
  http.GET();
  Serial.println("D0 : " + http.getString());
  if (http.getString() == "0") {
    digitalWrite(16, LOW);
  } else {
    digitalWrite(16, HIGH);
  }
}
void toggleLight2() {
  String url = host + "D1";
  http.begin(wificlient, url);
  http.GET();
  Serial.println("D1 : " + http.getString());
  if (http.getString() == "0") {
    digitalWrite(5, LOW);
  } else {
    digitalWrite(5, HIGH);
  }
}void toggleLight3() {
  String url = host + "D2";
  http.begin(wificlient, url);
  http.GET();
  Serial.println("D2 : " + http.getString());
  if (http.getString() == "0") {
    digitalWrite(D2, LOW);
  } else {
    digitalWrite(D2, HIGH);
  }
}void toggleLight4() {
  String url = host + "D6";
  http.begin(wificlient, url);
  http.GET();
  Serial.println("D6 : " + http.getString());
  if (http.getString() == "0") {
    digitalWrite(D6, LOW);
  } else {
    digitalWrite(D6, HIGH);
  }
}
