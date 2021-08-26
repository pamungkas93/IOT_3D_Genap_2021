// #include <Arduino.h>
// #include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27, 16, 2);

// void setup()
// {
//     lcd.init(); // initialize the lcd
//     lcd.backlight();
//     lcd.home();
// }

// void scrollText(int row, String message, int delayTime, int lcdColumns)
//  {
//    for (int i = 0; i < lcdColumns; i++)
//    {
//      message = " " + message;
//    }
//    message = message + " ";
//    for (int pos = 0; pos < message.length(); pos++)
//    {
//      lcd.setCursor(0, row);
//      lcd.print(message.substring(pos, pos + lcdColumns));
//      delay(delayTime);
//    }
//  }
 
// void loop()
// {
//     lcd.home();
//     lcd.print("Selamat Datang");
//     scrollText(1, "Parakan 01", 250, 16);
// }
//     for (address = 1; address < 127; address++)
//     {
//         Wire.beginTransmission(address);
//         error = Wire.endTransmission();
//         if (error == 0)
//         {
//             Serial.print("I2C ditemukan pada 0x");
//             if (address < 16)
//             {
//                 Serial.print("0");
//             }
//             Serial.println(address, HEX);
//             nDevices++;
//         }
//         else if (error == 4)
//         {
//             Serial.print("Unknow error at address 0x");
//             if (address < 16)
//             {
//                 Serial.print("0");
//             }
//             Serial.println(address, HEX);
//         }
//     }
//     if (nDevices == 0)
//     {
//         Serial.println("No I2C devices found\n");
//     }
//     else
//     {
//         Serial.println("done\n");
//     }
//     delay(3000);
// }


// Tugas 

#include <Arduino.h>
#include <LiquidCrystal_I2C.h> 
#include <DHT.h>

#define DHTTYPE DHT11 
#define RED_LED D5 
#define GREEN_LED D6 
#define BLUE_LED D7

DHT dht(D3, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  lcd.home();
}

void scrollText(int row, String message, int delayTime, int lcdColumns)
{
  for (int i = 0; i < lcdColumns; i++)
  {
    message = " " + message;
  }
  message = message + " ";
  for (int pos = 0; pos < message.length(); pos++)
  {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

void red()
{
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
}

void green()
{
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
}

void blue()
{
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
}

void dead()
{
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
}

void loop()
{
  delay(2000);
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (t >= 35)
  {
    for (int i = 0; i < 3; i++)
    {
      red();
      delay(150);
      dead();
      delay(150);
    }
    scrollText(1, "Suhu Panas", 250, 16);
  }
  else if (t <= 25)
  {
    for (int i = 0; i < 3; i++)
    {
      green();
      delay(150);
      dead();
      delay(150);
    }
    scrollText(1, "Suhu Dingin", 250, 16);
  }
  else
  {
    for (int i = 0; i < 3; i++)
    {
      blue();
      delay(150);
      dead();
      delay(150);
    }
    scrollText(1, "Suhu Sedang", 250, 16);
  }
  lcd.home();
  lcd.print(t);
  lcd.print("\337C ");
  lcd.print(f);
  lcd.print("\337F");
  
}