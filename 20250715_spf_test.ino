#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#include <LiquidCrystal_I2C.h>


#define BME_SCK     13
#define BME_MISO    12
#define BME_MOSI    11
#define BME_CS      10

#define SEALEVELPRESSURE_HPA (1013.25)


LiquidCrystal_I2C   lcd ( 0x27,20,4 );  // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_BME680     bme ( BME_CS    ); // hardware SPI

void setup( )
{
  lcd.init( );                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight( );

  lcd.setCursor( 3,0 );
  lcd.print( "Hello, world!" );

  bme.begin( );
  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  delay(1500);

  lcd.clear( );

}

void loop( ) 
{
  
  // Tell BME680 to begin measurement.
  unsigned long endTime = bme.beginReading();
  if (endTime == 0) {
    return;
  }

  delay(50); // This represents parallel work.
  // There's no need to delay() until millis() >= endTime: bme.endReading()
  // takes care of that. It's okay for parallel work to take longer than
  // BME680's measurement time.

  // Obtain measurement results from BME680. Note that this operation isn't
  // instantaneous even if milli() >= endTime due to I2C/SPI latency.
  if (!bme.endReading()) {
    return;
  }

  lcd.setCursor ( 0,0 );
  lcd.print     ( "Temp =   " );
  lcd.print     (bme.temperature);
  lcd.print     (" *C");

  lcd.setCursor ( 0,1 );
  lcd.print     ( "Humi =   " );
  lcd.print     (bme.humidity);
  lcd.print     (" %");

  lcd.setCursor ( 0,2 );
  lcd.print     ( "Pres = " );
  lcd.print     (bme.pressure / 100.0);
  lcd.print     (" hPa");

  lcd.setCursor ( 0,3 );
  lcd.print     ( "Gas  =  " );
  lcd.print     (bme.gas_resistance / 1000.0);
  lcd.print     (" KOhms");

  delay(2000);

}
