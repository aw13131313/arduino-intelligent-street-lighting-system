#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <DS3231.h>

DS3231 rtc(SDA, SCL);
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte smile[8] = {
  B00000, B00000, B01010, B00000, B00000, B10001, B01110, B00000
};

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial); 

bool absentToday[37] = {false};  // Array status absensi

const String names[] = { // Array nama lebih efisien dengan tipe String
  "Rianto L", "S. Abadi A", "Hadi", "Soetyadi", "Nur K", "Samsul", 
  "Endro", "Ahmad", "Rony S", "Soleh", "Suripno", "Ghiyas", 
  "Zainul", "Rony A", "Radit", "Mahfud", "Yudha", "Indra", 
  "Gandung", "Arvian", "Naufal", "Yuniarto", "Khisbul", 
  "Wulidal", "Mustafa", "Defi", "Ronggo", "Huda", 
  "Bondan", "Renddy", "Lido", "Ilham", "Irfan", "Alam", 
  "Arisky", "Ulung", "Didit", "Umbar"
};

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, smile);
  rtc.begin();

  finger.begin(57600);
  if (!finger.verifyPassword()) {
    Serial.println("Sensor fingerprint tidak ditemukan.");
    while (true) delay(1);
  }

  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
}

void loop() {
  // Tampilkan waktu pada LCD
  lcd.setCursor(0, 0);
  lcd.print(rtc.getDOWStr(1));
  lcd.print(" ");
  lcd.print(rtc.getDateStr());

  lcd.setCursor(0, 1);
  lcd.print(rtc.getTimeStr());
  lcd.print(" SENKOM");

  // Proses sidik jari
  getFingerprintID();
  delay(50);

  // Reset status absensi di tengah malam
  if (rtc.getTime().hour == 0 && rtc.getTime().min == 0 && rtc.getTime().sec == 0) {
    memset(absentToday, false, sizeof(absentToday)); // Reset array absensi
  }
}

void processFingerprint(int id) {
  if (id > 0 && id <= 37 ) {
    if (absentToday[id - 1]) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sudah Absen");
      lcd.setCursor(0, 1);
      lcd.print("Hari Ini ");
      lcd.write(0);
    } else {
      absentToday[id - 1] = true;
      lcd.clear();
      digitalWrite(8, HIGH);
      lcd.setCursor(4, 0);
      lcd.print("Welcome ");
      lcd.write(0);
      lcd.setCursor(5, 1);
      lcd.print(names[id - 1]);  // Tampilkan nama sesuai ID

      Serial.print("DATA,");
      Serial.print(rtc.getDOWStr(2));
      Serial.print(",");
      Serial.print(rtc.getDateStr());
      Serial.print(",");
      Serial.print(names[id - 1]);  // Cetak nama ke Serial
      Serial.print(",");
      Serial.print(rtc.getTimeStr());
      Serial.print(", ");
      if (rtc.getTime().hour < 8) {
        Serial.println("On Time");
      } else {
        Serial.println("Late");
      }

      delay(2000); // Tampilkan pesan selama 2 detik
      digitalWrite(8, LOW);
    }
  }
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return p;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return p;

  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    processFingerprint(finger.fingerID);  // Kirim ID untuk diproses
  }
  return p;
}
