#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"


#include <HCSR04.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


// Insert Firebase project API Key
#define API_KEY "AIzaSyC6Wyj9o2hAeYQQeUT9KobMmN_469N_b30"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://ultra-himeas-4a302-default-rtdb.firebaseio.com" 

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;


// MPU6050 Slave Device Address
const uint8_t MPU6050SlaveAddress = 0x68;
// Select SDA and SCL pins for I2C communication 
const uint8_t scl = D2;
const uint8_t sda = D1;
// sensitivity scale factor respective to full scale setting provided in datasheet 
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131;

// MPU6050 few configuration register addresses
const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;

int16_t AccelX, AccelY, AccelZ, Temperature, GyroX, GyroY, GyroZ;


//__________________________________________________________________________


HCSR04 hc(0, 2); // Initialize Pin D7, D6
// Network SSID
const char* ssid = "IPHONE 20 PRO";
const char* password = "mokorutoaitokotoz";
// #define FIREBASE_HOST "https://ultra-himeas-default-rtdb.asia-southeast1.firebasedatabase.app/"                          // the project name address from firebase id
// #define FIREBASE_AUTH "dujjQMpGIpa48na8mTyALDgfXTTwOzF5uLjR8J19"            // the secret key generated from firebase
float ul[100];
String randomString = " ";
int z=0;

void setup() {
  delay(10);
  z=0;

  pinMode(D8, OUTPUT);
  Serial.begin(9600);
  Wire.begin(sda, scl);
  MPU6050_Init();
  digitalWrite(D8,HIGH);
  delay(15);
  digitalWrite(D8,LOW);
  delay(15);


  Serial.begin(115200);
  randomSeed(analogRead(0));

  // Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);



  WiFi.hostname("HIMEAS AX01");
  WiFi.begin(ssid, password);

  digitalWrite(D8,HIGH);
  delay(10);
  digitalWrite(D8,LOW);
  delay(10);
  digitalWrite(D8,HIGH);
  delay(10);
  digitalWrite(D8,LOW);
  delay(10);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  digitalWrite(D8,HIGH);
  delay(10);
  digitalWrite(D8,LOW);
  delay(10);
  digitalWrite(D8,HIGH);
  delay(10);
  digitalWrite(D8,LOW);
  delay(10);
  digitalWrite(D8,HIGH);
  delay(10);
  delay(10);
  digitalWrite(D8,LOW);
 
  // Print the IP address
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());

/* Assign the api key (required) */
  config.api_key = API_KEY;
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;

    digitalWrite(D8,HIGH);
    delay(10);
    digitalWrite(D8,LOW);
    delay(10);
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Firebase.RTDB.setInt(&fbdo, "SENSE/ID/CRYPT", msg);


}
 
void loop() {
  
  if(z<2){
      //CREATE CRYPT UNQ ID
  //generate random string once
  for (int i = 0; i < 25; i++) {
    char randomChar = (char)(random(48, 123)); 
    if ((randomChar >= 58 && randomChar <= 64) || (randomChar >= 91 && randomChar <= 96)) {
      randomChar = (char)(random(48, 58) + random(65, 91) + random(97, 123));
    }
    randomString += randomChar;
  }
  Serial.println("TX CREATED");
  Firebase.RTDB.setString(&fbdo, "SENSE/ID/TX", randomString);
  Serial.println("TX HAS BEEN SEND");
  }
  else{}
  z++;



  double Ax, Ay, Az, T, Gx, Gy, Gz;



  Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);

  //divide each with their sensitivity scale factor
  Ax = (double)AccelX/AccelScaleFactor;
  Ay = (double)AccelY/AccelScaleFactor;
  Az = (double)AccelZ/AccelScaleFactor;
  T = (double)Temperature/340+36.53; //temperature formula
  Gx = (double)GyroX/GyroScaleFactor;
  Gy = (double)GyroY/GyroScaleFactor;
  Gz = (double)GyroZ/GyroScaleFactor;

  Serial.print("Ax: "); Serial.print(Ax);
  Serial.print(" Ay: "); Serial.print(Ay);
  Serial.print(" Az: "); Serial.print(Az);
  Serial.print(" T: "); Serial.print(T);
  Serial.print(" Gx: "); Serial.print(Gx);
  Serial.print(" Gy: "); Serial.print(Gy);
  Serial.print(" Gz: "); Serial.println(Gz);


  //Serial.println(hc.dist()); // Print in centimeters the value from the sensor
  


  // Firebase.pushString("/ULT/CM", hc.dist());  
  
  // if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 50 || sendDataPrevMillis == 0)){
  //     sendDataPrevMillis = millis();
  //     // Write an Int number on the database path test/int
  // }
 
  if (Ax>-0.05 && Ax<0.11 && Ay>-0.10 && Ay<0.16 && Az>0.95 && Az<1.03){
    for (int i=0 ;i<100 ; i++)  {
      ul[i] = {hc.dist()};



      digitalWrite(D8,HIGH);
      delay(1);
      digitalWrite(D8,LOW);
      delay(1);
      Serial.println(ul[i]);
     }

    //  for (int i=0 ;i<100 ; i++)  {
    //  Serial.print(ul[i]);
    //  }
     Serial.println("SEARCH THE MAX VAL");
    

    float max,current, maxI; 
    for(int j = 0;j < 100;j++){
    current = ul[j];
    if(current > max){
    max = current;
    maxI = j;
    }
    }

    Serial.println("SEARCH THE AVG VAL");
    unsigned int index;
    long arraySum;

    arraySum = 0;
    for(index = 0; index < sizeof(ul)/sizeof(ul[0]); index++)
    { arraySum += ul[index]; }

    float avg = arraySum/100;

    Serial.print("JSN MAX VALUE: ");
    Serial.println(max);
    Serial.print("JSN AVG VALUE: ");
    Serial.println(avg);
    upload(avg, max, Ax, Ay, Az, T, Gx, Gy, Gz);

  }
  // qHx�c7uhcAv�XBtMQDRlTyFtE
  else{
  digitalWrite(D8,HIGH);
  delay(25);
  digitalWrite(D8,LOW);
  delay(25);
  }

  
  delay(10);

  }


  void I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t data){
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.write(data);
  Wire.endTransmission();

}




void upload(float avg, float max, double Ax,double Ay,double Az,double T,double Gx,double Gy,double Gz){
    Firebase.RTDB.setInt(&fbdo, "SENSE/ULTRA/HEIGHT(AVG)", avg);    
    Firebase.RTDB.setInt(&fbdo, "SENSE/ULTRA/HEIGHT(HST)", max);


    Firebase.RTDB.setInt(&fbdo, "SENSE/GYRO/AX", Ax);
    Firebase.RTDB.setInt(&fbdo, "SENSE/GYRO/AY", Ay);
    Firebase.RTDB.setInt(&fbdo, "SENSE/GYRO/AZ", Az);
    Firebase.RTDB.setInt(&fbdo, "SENSE/GYRO/GX", Gx);
    Firebase.RTDB.setInt(&fbdo, "SENSE/GYRO/GY", Gy);
    Firebase.RTDB.setInt(&fbdo, "SENSE/GYRO/GZ", Gz);
    Firebase.RTDB.setInt(&fbdo, "SENSE/GYRO/TEMP", T);
    Serial.println();
    Serial.println("UPLOADED");
    Serial.println("PATH: " + fbdo.dataPath());
    Serial.println("TYPE: " + fbdo.dataType());
}

// read all 14 register
void Read_RawValue(uint8_t deviceAddress, uint8_t regAddress){
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, (uint8_t)14);
  AccelX = (((int16_t)Wire.read()<<8) | Wire.read());
  AccelY = (((int16_t)Wire.read()<<8) | Wire.read());
  AccelZ = (((int16_t)Wire.read()<<8) | Wire.read());
  Temperature = (((int16_t)Wire.read()<<8) | Wire.read());
  GyroX = (((int16_t)Wire.read()<<8) | Wire.read());
  GyroY = (((int16_t)Wire.read()<<8) | Wire.read());
  GyroZ = (((int16_t)Wire.read()<<8) | Wire.read());
}

//configure MPU6050
void MPU6050_Init(){
  delay(150);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SMPLRT_DIV, 0x07);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_1, 0x01);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_2, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_CONFIG, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_GYRO_CONFIG, 0x00);//set +/-250 degree/second full scale
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_CONFIG, 0x00);// set +/- 2g full scale
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_FIFO_EN, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_INT_ENABLE, 0x01);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SIGNAL_PATH_RESET, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_USER_CTRL, 0x00);
}

