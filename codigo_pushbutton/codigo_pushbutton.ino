//#include <WiFi.h>
//#include <FirebaseESP32.h>
//
//#define FIREBASE_HOST "interface-6d928-default-rtdb.firebaseio.com"
//#define FIREBASE_AUTH "AIzaSyBRf_YmBfbrAyl3ASsRa-563ma545qbohI"
//
//FirebaseData fbdo;
//
//FirebaseAuth auth;
//FirebaseConfig config;
//
//
//float freq=1;
//float dado=0;
//int potValue=0;
//unsigned long sendDataPrevMillis = 0;
//
//const char* ssid = "TP-Link_BC8D";
//const char* password = "30254985";
//bool signupOK = false;
//int potPin=34;
//
//void setup(){
//  Serial.begin(115200);
//  pinMode(potPin, INPUT);
//  // Connect to Wi-Fi
//  
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(1000);
//    Serial.println("Connecting to WiFi..");
//  }
//
//  Serial.println(WiFi.localIP());
//
//  config.api_key = FIREBASE_AUTH;
//
//  config.database_url = FIREBASE_HOST;
//
//  if (Firebase.signUp(&config, &auth, "", "")){
//    Serial.println("ok");
//    signupOK = true;
//  }
//  else{
//    Serial.printf("%s\n", config.signer.signupError.message.c_str());
//  }
//  
//  Firebase.begin(&config, &auth);
//  Firebase.reconnectWiFi(true);
//}
//
//void loop(){
//  potValue = analogRead(potPin);
//  freq = potValue*0.0003;
//  
//  dado=sin(freq*millis()/1000);
//  Serial.println(dado);
//  if (Firebase.ready() && signupOK){
//    if (Firebase.RTDB.setFloat(&fbdo, "freq", freq)) {
//      Serial.println("PASSED");
//      Serial.println("PATH: " + fbdo.dataPath());
//      Serial.println("TYPE: " + fbdo.dataType());
//    }else {
//      Serial.println(fbdo.errorReason());
//    }
//  
//    if (Firebase.RTDB.setFloat(&fbdo, "valor", dado)) {
//      Serial.println("PASSED");
//      Serial.println("PATH: " + fbdo.dataPath());
//      Serial.println("TYPE: " + fbdo.dataType());
//    }else {
//      Serial.println(fbdo.errorReason());
//    }
//  }
//  Serial.println(freq);
//  delay(1L);
//}



#include <WiFi.h>
#include <FirebaseESP32.h>

#define FIREBASE_HOST "https://sensor-8a60d-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyDTm3ZTfCnSEMPIH6zu8rwWWzsC_B02AMU"

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

const int LEDPIN = 22; 
const int PushButton = 15;
float freq=1;
float dado=0;

const char* ssid = "TP-Link_BC8D";
const char* password = "30254985";
bool signupOK = false;

void setup(){
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  pinMode(PushButton, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

   /* Assign the api key (required) */
  config.api_key = FIREBASE_AUTH;
  config.database_url = FIREBASE_HOST;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
  int Push_button_state = digitalRead(PushButton);
  if ( Push_button_state == HIGH ){
    digitalWrite(LEDPIN, HIGH);
    freq=freq+0.01;
    if (Firebase.RTDB.setFloat(&fbdo, "freq", freq)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }else {
      Serial.println(fbdo.errorReason());
    }
    delay(100L);
  }else{
    digitalWrite(LEDPIN, LOW);
    dado=plotSineWave();
    if (Firebase.RTDB.setFloat(&fbdo, "valor", dado)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }else {
      Serial.println(fbdo.errorReason());
    }
    delay(50L);
  }
}

float plotSineWave() {
   //for (float i = 0.05; i <= 2 * PI; i += 0.05) {
      Serial.println(sin(freq*millis()/800));
      return (sin(freq*millis()/800));
   //}  
}
