#define BLYNK_TEMPLATE_ID           "TMPL6ScgjEYrz"
#define BLYNK_TEMPLATE_NAME         "Kontrol Smart Street Light"
#define BLYNK_AUTH_TOKEN            "S_K4Pg8oGpSww0iFL3UdJ7pNCwCsY50Y"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "bakekok";
char pass[] = "hihihi123";

BlynkTimer timer;
bool isLoopOn = true; // Variabel untuk menyimpan status loop

int led1 = 15;
int led2 = 2;
int led3 = 4;
int led4 = 16;
int led5 = 17;
int led6 = 18;  

int ldr = 34;

int ir1 = 27;
int ir2 = 26;
int ir3 = 25;
int ir4 = 33;
int ir5 = 32;
int ir6 = 35;

float Vin, RLDR, logRK, I;
int intensitaslampu = 50; // Nilai antara 0 hingga 255
unsigned long delaysetelahmenyala = 1000; // Penundaan 1 detik
unsigned long interval = 100; // Interval pengecekan sensor
unsigned long previousMillis = 0; // Menyimpan waktu sebelumnya
unsigned long previousMillisIR1 = 0; // Menyimpan waktu sebelumnya untuk IR1
unsigned long previousMillisIR2 = 0; // Menyimpan waktu sebelumnya untuk IR2
unsigned long previousMillisIR3 = 0; // Menyimpan waktu sebelumnya untuk IR3
unsigned long previousMillisIR4 = 0; // Menyimpan waktu sebelumnya untuk IR4
unsigned long previousMillisIR5 = 0; // Menyimpan waktu sebelumnya untuk IR5
unsigned long previousMillisIR6 = 0; // Menyimpan waktu sebelumnya untuk IR6

bool lampuMenyalaPenuh1 = false;
bool lampuMenyalaPenuh2 = false;
bool lampuMenyalaPenuh3 = false;
bool lampuMenyalaPenuh4 = false;
bool lampuMenyalaPenuh5 = false;
bool lampuMenyalaPenuh6 = false;

void setup() 
{
  Serial.begin(115200);

  // Set LED pin as OUTPUT
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  // Set LDR pin as INPUT
  pinMode(ldr, INPUT);

  // Set IR sensor pin as INPUT
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  pinMode(ir6, INPUT);

  // Setup PWM channels
  ledcSetup(0, 5000, 8); // Channel 0, 5000 Hz, 8-bit resolution
  ledcSetup(1, 5000, 8); // Channel 1, 5000 Hz, 8-bit resolution
  ledcSetup(2, 5000, 8); // Channel 2, 5000 Hz, 8-bit resolution
  ledcSetup(3, 5000, 8); // Channel 3, 5000 Hz, 8-bit resolution
  ledcSetup(4, 5000, 8); // Channel 4, 5000 Hz, 8-bit resolution
  ledcSetup(5, 5000, 8); // Channel 5, 5000 Hz, 8-bit resolution

  // Attach the LED pins to PWM channels
  ledcAttachPin(led1, 0);
  ledcAttachPin(led2, 1);
  ledcAttachPin(led3, 2);
  ledcAttachPin(led4, 3);
  ledcAttachPin(led5, 4);
  ledcAttachPin(led6, 5);
  
  timer.setInterval(1000L, sendSensorData); 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
}

void sendSensorData() {
  // Send the intensity values of LEDs to Blynk
  int luxled1 = ledcRead(0);
  Serial.print("LuxLed1: ");
  Serial.println(luxled1);
  Blynk.virtualWrite(V2, luxled1); // LED1 intensity

  int luxled2 = ledcRead(1);
  Serial.print("LuxLed2: ");
  Serial.println(luxled2);
  Blynk.virtualWrite(V2, luxled2); // LED2 intensity

  int luxled3 = ledcRead(2);
  Serial.print("LuxLed3: ");
  Serial.println(luxled3);
  Blynk.virtualWrite(V3, luxled3); // LED3 intensity

  int luxled4 = ledcRead(3);
  Serial.print("LuxLed4: ");
  Serial.println(luxled4);
  Blynk.virtualWrite(V3, luxled4); // LED4 intensity

  int luxled5 = ledcRead(4);
  Serial.print("LuxLed5: ");
  Serial.println(luxled5);
  Blynk.virtualWrite(V4, luxled5); // LED5 intensity

  int luxled6 = ledcRead(5);
  Serial.print("LuxLed6: ");
  Serial.println(luxled6);
  Blynk.virtualWrite(V4, luxled6); // LED6 intensity
}


void loop() 
{
  
if(isLoopOn) {
      
  unsigned long currentMillis = millis();

  // Cek LDR setiap interval waktu tertentu
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int ldrStatus = analogRead(ldr);
    Vin = ldrStatus * 0.00489;
    RLDR = (5000.0 / Vin - 1000.0);
    logRK = log10(RLDR / 127262.2);
    I = pow(10.0, logRK / (-0.858));
    Serial.print("LDR Value: ");
    Serial.println(I);
    Blynk.virtualWrite(V1, I);
        
    if (I <= 220){
      // Jika intensitas cahaya rendah, nyalakan lampu dengan intensitaslampu
      if (!lampuMenyalaPenuh1) {
        ledcWrite(0, intensitaslampu);
      }
      if (!lampuMenyalaPenuh2) {
        ledcWrite(1, intensitaslampu);
      }
      if (!lampuMenyalaPenuh3) {
        ledcWrite(2, intensitaslampu);
      }
      if (!lampuMenyalaPenuh4) {
        ledcWrite(3, intensitaslampu);
      }
      if (!lampuMenyalaPenuh5) {
        ledcWrite(4, intensitaslampu);
      }
      if (!lampuMenyalaPenuh6) {
        ledcWrite(5, intensitaslampu);
      }

      // Cek sensor IR1
      if (digitalRead(ir1) == LOW) {
        lampuMenyalaPenuh1 = true;
        previousMillisIR1 = currentMillis;
        ledcWrite(0, 255); // LED1 menyala dengan intensitas penuh
      }

      // Cek sensor IR2
      if (digitalRead(ir2) == LOW) {
        lampuMenyalaPenuh2 = true;
        previousMillisIR2 = currentMillis;
        ledcWrite(1, 255); // LED2 menyala dengan intensitas penuh
      }

      // Cek sensor IR3
      if (digitalRead(ir3) == LOW) {
        lampuMenyalaPenuh3 = true;
        previousMillisIR3 = currentMillis;
        ledcWrite(2, 255); // LED3 menyala dengan intensitas penuh
      }

      // Cek sensor IR4
      if (digitalRead(ir4) == LOW) {
        lampuMenyalaPenuh4 = true;
        previousMillisIR4 = currentMillis;
        ledcWrite(3, 255); // LED4 menyala dengan intensitas penuh
      }

      // Cek sensor IR5
      if (digitalRead(ir5) == LOW) {
        lampuMenyalaPenuh5 = true;
        previousMillisIR5 = currentMillis;
        ledcWrite(4, 255); // LED5 menyala dengan intensitas penuh
      }

      // Cek sensor IR6
      if (digitalRead(ir6) == LOW) {
        lampuMenyalaPenuh6 = true;
        previousMillisIR6 = currentMillis;
        ledcWrite(5, 255); // LED6 menyala dengan intensitas penuh
      }

    } else {
      // Jika intensitas cahaya tinggi, matikan lampu
      ledcWrite(0, 0);
      ledcWrite(1, 0);
      ledcWrite(2, 0);
      ledcWrite(3, 0);
      ledcWrite(4, 0);
      ledcWrite(5, 0);
      lampuMenyalaPenuh1 = false;
      lampuMenyalaPenuh2 = false;
      lampuMenyalaPenuh3 = false;
      lampuMenyalaPenuh4 = false;
      lampuMenyalaPenuh5 = false;
      lampuMenyalaPenuh6 = false;
    }
  }

  // Matikan LED1 setelah delaysetelahmenyala jika menyala penuh
  if (lampuMenyalaPenuh1 && currentMillis - previousMillisIR1 >= delaysetelahmenyala) {
    lampuMenyalaPenuh1 = false;
    ledcWrite(0, intensitaslampu); // LED1 kembali ke intensitas awal
  }

  // Matikan LED2 setelah delaysetelahmenyala jika menyala penuh
  if (lampuMenyalaPenuh2 && currentMillis - previousMillisIR2 >= delaysetelahmenyala) {
    lampuMenyalaPenuh2 = false;
    ledcWrite(1, intensitaslampu); // LED2 kembali ke intensitas awal
  }

  // Matikan LED3 setelah delaysetelahmenyala jika menyala penuh
  if (lampuMenyalaPenuh3 && currentMillis - previousMillisIR3 >= delaysetelahmenyala) {
    lampuMenyalaPenuh3 = false;
    ledcWrite(2, intensitaslampu); // LED3 kembali ke intensitas awal
  }

  // Matikan LED4 setelah delaysetelahmenyala jika menyala penuh
  if (lampuMenyalaPenuh4 && currentMillis - previousMillisIR4 >= delaysetelahmenyala) {
    lampuMenyalaPenuh4 = false;
    ledcWrite(3, intensitaslampu); // LED4 kembali ke intensitas awal
  }

  // Matikan LED5 setelah delaysetelahmenyala jika menyala penuh
  if (lampuMenyalaPenuh5 && currentMillis - previousMillisIR5 >= delaysetelahmenyala) {
    lampuMenyalaPenuh5 = false;
    ledcWrite(4, intensitaslampu); // LED5 kembali ke intensitas awal
  }

    // Matikan LED6 setelah delaysetelahmenyala jika menyala penuh
  if (lampuMenyalaPenuh6 && currentMillis - previousMillisIR6 >= delaysetelahmenyala) {
    lampuMenyalaPenuh6 = false;
    ledcWrite(5, intensitaslampu); // LED6 kembali ke intensitas awal
  }
    }
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V0)
{
  int pinData = param.asInt(); // Mendapatkan nilai yang dikirim
  if(pinData == 1) {
    isLoopOn = true; // Menghidupkan loop
  } else if(pinData == 0) {
    isLoopOn = false; // Mematikan loop
  }
}
