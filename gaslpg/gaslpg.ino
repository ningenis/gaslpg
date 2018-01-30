/*
Kode Sistem Pengelolaan Kebocoran Gas LPG
*/

// Library Initialization

// WiFi Setting 
#define SSID "HOMENET"        // SSID
#define PASS "0123456789"     // Password
#define HOST "192.168.1.7"  // Webhost
//-------------------------------

// Inisialisasi Buzzer 
const int Buzzer = 9;

// Calibration Setting
int calibrationTime = 10;    

// Variable Declaration
int val = 0; // Penampung nilai dari sensor api
int value = 0; // Penampung nilai dari sensor gas
const int pingas = 0; // Pin untuk sensor gas
const int pinapi = 1; // Pin untuk sensor api
int nilaiapi; // Penampung nilai sensor api untuk dikirim ke server
int nilaigas; // Penampung nilai sensor gas untuk dikirim ke server

int interval = 970; // Interval for one loop

//-------------------------------

// Setup
void setup(){
  // Serial Declaration
  Serial.begin(9600);
  
  // Sensor Calibration
  Serial.print("calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
    }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);

  // Setting Pin 13 as Output
  pinMode(Buzzer, OUTPUT);
  
  // ESP8266 Module Connection
  Serial.println("AT");
  delay(5000);
  connectWiFi();
  //if(Serial.find("OK")){
    //connectWiFi();
  //}
}

// Main Program (Loop)
void loop(){
  delay(10);
  sensorgas();
  delay(10);
  sensorapi();
  delay(10);
  // Send Data to Server
  sendData(String(nilaiapi), String(nilaigas));
  delay(interval);
}

// Prosedur memproses data sensor api dan mengaktuasi buzzer
void sensorapi() {
  val = analogRead(pinapi); // Simpan nilai dari sensor
  Serial.print("Nilai Sensor Api = ");
  Serial.print(val, DEC); // Print di serial monitor untuk debug
  Serial.println();
  // Logika aktuasi
  if (val >= 625) {
    digitalWrite(Buzzer, HIGH);
  }
  else
  {
    digitalWrite(Buzzer, LOW);
  }
  // Simpan nilai sensor untuk dikirimkan ke server
  nilaiapi = val; 
}

// Prosedur memproses data sensor gas dan mengaktuasi buzzer
void sensorgas() {
  value = analogRead(pingas); // Simpan nilai dari sensor
  Serial.print("Nilai Sensor Gas = ");
  Serial.print(value); // Print di serial monitor untuk debug
  Serial.println();
  // Logika aktuasi
  if (value >= 850) {
    digitalWrite(Buzzer, HIGH);
  }
  else
  {
    digitalWrite(Buzzer, LOW);
  } 
  // Simpan nilai sensor untuk dikirimkan ke server
  nilaigas = value;
}

// Send Data to Server Procedure
void sendData(String nilaiapi, String nilaigas){
  // Setup TCP Connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += HOST;
  cmd += "\",80";
  Serial.println(cmd);
  delay(2000);

  // Send Data to Server with GET Method.
  cmd = "GET /gaslpg/add_data.php"; // Link to API                   
  cmd += "?sensorapi=";             // Selektor Sensor Api
  cmd += nilaiapi;                  // Nilai Sensor Api
  cmd += "&sensorgas=";             // Selektor Sensor Gas  
  cmd += nilaigas;                  // Nilai Sensor Gas
  cmd += " HTTP/1.1\r\nHost: "; 
  cmd += HOST;
  cmd += "\r\n\r\n\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  Serial.print(cmd);
  //if(Serial.find(">")){
    //Serial.print(cmd);
  //}  
}

// Connect WiFi Procedure
void connectWiFi(){
  // Connect to Access Point
  Serial.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial.println(cmd);
  delay(5000);
  // WiFi Connection Checking
  if(Serial.find("OK")){
    Serial.println("Connection");
    //return true;
  }
  else{
    Serial.println("No Connection");
    //return false;
  }
}
