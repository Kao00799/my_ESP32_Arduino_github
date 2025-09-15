#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ฟิสิกส์
const double c = 3.0e8;        // ความเร็วแสง (m/s)
const double freq = 2.4e9;     // ความถี่ Wi-Fi (Hz)
double wavelength = c / freq;  // ความยาวคลื่น (m)

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22); // SDA=21, SCL=22 ของ ESP32

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // ใช้ขนาดตัวอักษรพอดี
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("WiFi Physics Demo");
  display.display();
  delay(2000);
}

void loop() {
  Serial.println("Scanning...");
  int n = WiFi.scanNetworks();

  display.clearDisplay();
  display.setTextSize(1);      // ขนาดพอดี
  display.setCursor(0,0);

  if (n == 0) {
    display.println("No networks");
  } else {
    // หา Wi-Fi ที่แรงที่สุด
    int bestIndex = 0;
    for (int i = 1; i < n; i++) {
      if (WiFi.RSSI(i) > WiFi.RSSI(bestIndex)) bestIndex = i;
    }

    // แสดงผลบนจอ
    display.print("SSID: ");
    display.println(WiFi.SSID(bestIndex));
    display.println() ;

    display.print("RSSI: ");
    display.print(WiFi.RSSI(bestIndex));
    display.println(" dBm");
    display.println() ;

    display.print("f: ");
    display.print(freq, 0);
    display.println(" Hz");
    display.println() ;

    display.print("lambda: ");
    display.print(wavelength*100,1);
    display.println(" cm");
    display.println() ;
  }

  display.display();
  delay(3000); // สแกนใหม่ทุก 3 วิ
}
