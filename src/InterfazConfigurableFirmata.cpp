/*
 * ConfiguredFirmata.ino generated by FirmataBuilder
 * Mon Jul 23 2018 18:44:05 GMT-0400 (EDT)
 */


#include <ConfigurableFirmata.h>

#include <DigitalInputFirmata.h>
DigitalInputFirmata digitalInput;

#include <DigitalOutputFirmata.h>
DigitalOutputFirmata digitalOutput;

#include <AnalogInputFirmata.h>
AnalogInputFirmata analogInput;

#include <AnalogOutputFirmata.h>
AnalogOutputFirmata analogOutput;

#include <Servo.h>
#include <ServoFirmata.h>
ServoFirmata servo;

#include <Wire.h>
#include <I2CFirmata.h>
I2CFirmata i2c;

#include <PingFirmata.h>
PingFirmata ping;

#include <PixelFirmata.h>
PixelFirmata pixel;

#include <OneWireFirmata.h>
OneWireFirmata oneWire;

#if defined(_L293SHIELD_)
  #include <InterfazL293DShieldFirmata.h>
  InterfazL293DShieldFirmata motor;
#endif

#if defined(_RASTI_)
  #include <InterfazRastiDCFirmata.h>
  InterfazRastiDCFirmata motor;
#endif

#if defined(_PCF8591_)
  #include <InterfazPCF8591Firmata.h>
  InterfazPCF8591Firmata PCF8591;
#endif


#include <AccelStepperFirmata.h>
AccelStepperFirmata stepper;

#include <InterfazLCDFirmata.h>
InterfazLCDFirmata lcd;

#include <InterfazFirmata.h>
InterfazFirmata interfaz;

/*
#include <StringFirmata.h>
StringFirmata string;
*/

#include <FirmataExt.h>
FirmataExt firmataExt;

#include <AnalogWrite.h>

#include <FirmataReporting.h>
FirmataReporting reporting;



void systemResetCallback()
{
  for (byte i = 0; i < TOTAL_PINS; i++) {
    if (IS_PIN_ANALOG(i)) {
      Firmata.setPinMode(i, ANALOG);
    } else if (IS_PIN_DIGITAL(i)) {
      Firmata.setPinMode(i, OUTPUT);
    }
  }
  firmataExt.reset();
}

void initTransport()
{
  // Uncomment to save a couple of seconds by disabling the startup blink sequence.
  Firmata.disableBlinkVersion();
  Firmata.begin(57600);
}

void initFirmata()
{
  Firmata.setFirmwareVersion(FIRMATA_FIRMWARE_MAJOR_VERSION, FIRMATA_FIRMWARE_MINOR_VERSION);

  firmataExt.addFeature(digitalInput);
  firmataExt.addFeature(digitalOutput);
  firmataExt.addFeature(analogInput);
  #ifdef _LCD_
  firmataExt.addFeature(lcd);  // PONER JUSTO ANTES DE LOS SYSEX
  #endif
    firmataExt.addFeature(analogOutput);
  firmataExt.addFeature(servo);
  firmataExt.addFeature(ping);
  firmataExt.addFeature(pixel);
  firmataExt.addFeature(i2c);
  firmataExt.addFeature(oneWire);
  firmataExt.addFeature(stepper);
#if defined(_PCF8591_)
  firmataExt.addFeature(PCF8591);
#endif
#if defined(_L293SHIELD_)
  firmataExt.addFeature(motor);
#endif
#if defined(_RASTI_)
  firmataExt.addFeature(motor);
#endif
  firmataExt.addFeature(reporting);
  //firmataExt.addFeature(string);
  firmataExt.addFeature(interfaz); // PONER AL FINAL DE LA LISTA

  Firmata.attach(SYSTEM_RESET, systemResetCallback);
}


void setup()
{
  initFirmata();

  initTransport();

  Firmata.parse(SYSTEM_RESET);
}

void loop()
{
  digitalInput.report();

  while(Firmata.available()) {
    Firmata.processInput();
  }

  if (reporting.elapsed()) {
    analogInput.report();
    i2c.report();
    #if defined(_PCF8591_)
      PCF8591.report();
    #endif
  }


  stepper.update();
}
