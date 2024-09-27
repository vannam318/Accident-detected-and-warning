#include <SoftwareSerial.h>

SoftwareSerial sim808Serial(7, 8);

String latitude = "";
String longitude = "";

int smsSentCount = 0;

void setup() {
  sim808Serial.begin(9600);
  delay(1000);
  sim808Serial.println("AT+CGNSPWR=1");
  delay(1000);
  sim808Serial.println("AT+CGNSURC=1");
  delay(1000);
}

void getGPSLocation() {
  sim808Serial.println("AT+CGNSINF");
  delay(1000);

  while (sim808Serial.available()) {
    String response = sim808Serial.readString();
    if (response.indexOf("OK") != -1 && response.indexOf("+CGNSINF:") != -1) {
      int index = response.indexOf(",");
      if (index != -1) {
        latitude = response.substring(index + 1, index + 11);
        longitude = response.substring(index + 12, index + 23);
        Serial.print("Latitude: ");
        Serial.println(latitude);
        Serial.print("Longitude: ");
        Serial.println(longitude);
      }
    }
  }
}

void sendSMS() {
  sim808Serial.println("AT+CMGF=1");
  delay(1000);

  String smsMessage = "Tai nan xay ra! Thoi gian: ";
  smsMessage += millis();
  smsMessage += "ms, Nhiet do: ";
  smsMessage += ThermalValue;
  smsMessage += " *C, Vi tri: https://maps.google.com/?q=";
  smsMessage += latitude;
  smsMessage += ",";
  smsMessage += longitude;

  sim808Serial.print("AT+CMGS=\"+84708222232\"");
  sim808Serial.write((byte)0x0D);
  delay(1000);
  sim808Serial.print(smsMessage);
  delay(1000);
  sim808Serial.write((byte)0x1A);
  delay(5000);
}

void loop() {
  if (smsSentCount < 3) {
    getGPSLocation();
    sendSMS();
    smsSentCount++;
  }
  
  delay(10000); // Thời gian chờ giữa các lần gửi tin nhắn
}
