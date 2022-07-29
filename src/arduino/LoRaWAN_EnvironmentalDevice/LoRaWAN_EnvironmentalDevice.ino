
#include<CayenneLPP.h>
#include "Zanshin_BME680.h"  // Include the BME680 Sensor library

#define OTAA_DEVEUI   {0xAC,0x1F,0x09,0xFF,0xFE,0x08,0x34,0x94}
#define OTAA_APPKEY   {0x82, 0xe0, 0x1c, 0x7e, 0x20, 0xe1, 0x0e, 0x75, 0x1c, 0xdc, 0x11, 0x53, 0x77, 0x35, 0x69, 0xb7}
#define OTAA_APPEUI   {0x0E, 0x0D, 0x0D, 0x01, 0x0E, 0x01, 0x02, 0x0E}
#define OTAA_PERIOD   (600*1000) // 10 minute seconds
#define OTAA_BAND     (RAK_REGION_US915)
#define TXP 14        // FCC limits TX power to 14 dBM

BME680_Class BME680;  ///< Create an instance of the BME680 class

/** Packet buffer for sending */
CayenneLPP payload(32);

void recvCallback(SERVICE_LORA_RECEIVE_T * data)
{
  if (data->BufferSize > 0) {
    Serial.println("Something received!");
    for (int i = 0; i < data->BufferSize; i++) {
      Serial.printf("%x", data->Buffer[i]);
    }
    Serial.print("\r\n");
  }
}

void joinCallback(int32_t status)
{
  Serial.printf("Join status: %d\r\n", status);
}

void sendCallback(int32_t status)
{
  if (status == 0) {
    Serial.println("Successfully sent");
  } else {
    Serial.println("Sending failed");
  }
}


void setup()
{
  Serial.begin(115200, RAK_AT_MODE);

  Serial.println("RAKwireless LoRaWan OTAA Example");
  Serial.println("------------------------------------------------------");

  // OTAA Device EUI MSB first
  uint8_t node_device_eui[8] = OTAA_DEVEUI;
  // OTAA Application EUI MSB first
  uint8_t node_app_eui[8] = OTAA_APPEUI;
  // OTAA Application Key MSB first
  uint8_t node_app_key[16] = OTAA_APPKEY;

  if (!api.lorawan.appeui.set(node_app_eui, 8)) {
    Serial.printf("LoRaWan OTAA - set application EUI is incorrect! \r\n");
    return;
  }
  if (!api.lorawan.appkey.set(node_app_key, 16)) {
    Serial.printf("LoRaWan OTAA - set application key is incorrect! \r\n");
    return;
  }
  if (!api.lorawan.deui.set(node_device_eui, 8)) {
    Serial.printf("LoRaWan OTAA - set device EUI is incorrect! \r\n");
    return;
  }

  if (!api.lorawan.band.set(OTAA_BAND)) {
    Serial.printf("LoRaWan OTAA - set band is incorrect! \r\n");
    return;
  }
  
  if (!api.lorawan.deviceClass.set(RAK_LORA_CLASS_A)) {
    Serial.printf("LoRaWan OTAA - set device class is incorrect! \r\n");
    return;
  }
  if (!api.lorawan.njm.set(RAK_LORA_OTAA))  // Set the network join mode to OTAA
  {
    Serial.printf
  ("LoRaWan OTAA - set network join mode is incorrect! \r\n");
    return;
  }
  if (!api.lorawan.join())  // Join to Gateway
  {
    Serial.printf("LoRaWan OTAA - join fail! \r\n");
    return;
  }

  /** Wait for Join success */
  while (api.lorawan.njs.get() == 0) {
    Serial.print("Wait for LoRaWAN join...");
    api.lorawan.join();
    delay(10000);
  }

  if (!api.lorawan.adr.set(true)) {
    Serial.printf
  ("LoRaWan OTAA - set adaptive data rate is incorrect! \r\n");
    return;
  }
  if (!api.lorawan.rety.set(2)) {
    Serial.printf("LoRaWan OTAA - set retry times is incorrect! \r\n");
    return;
  }
  if (!api.lorawan.cfm.set(1)) {
    Serial.printf("LoRaWan OTAA - set confirm mode is incorrect! \r\n");
    return;
  }
  
  if (!api.lorawan.txp.set(TXP)) {
    Serial.printf("LoRaWan TXP - set transmit power fail! \r\n");
    return;
  }
//  
//  if (!api.lorawan.pnm.set(false)) {
//    Serial.printf("LoRaWan OTAA - set to private network fail! \r\n");
//    return;
//  };

  /** Check LoRaWan Status*/
  Serial.printf("Duty cycle is %s\r\n", api.lorawan.dcs.get()? "ON" : "OFF"); // Check Duty Cycle status
  Serial.printf("Packet is %s\r\n", api.lorawan.cfm.get()? "CONFIRMED" : "UNCONFIRMED");  // Check Confirm status
  uint8_t assigned_dev_addr[4] = { 0 };
  api.lorawan.daddr.get(assigned_dev_addr, 4);
  Serial.printf("Device Address is %02X%02X%02X%02X\r\n", assigned_dev_addr[0], assigned_dev_addr[1], assigned_dev_addr[2], assigned_dev_addr[3]);  // Check Device Address
  Serial.printf("Uplink period is %ums\r\n", OTAA_PERIOD);
  Serial.println("");
  api.lorawan.registerRecvCallback(recvCallback);
  api.lorawan.registerJoinCallback(joinCallback);
  api.lorawan.registerSendCallback(sendCallback);

  /** Setup BME680 **/
  
  Serial.print(F("- Initializing BME680 sensor\n"));
  while (!BME680.begin(I2C_STANDARD_MODE)) {  // Start BME680 using I2C, use first device found
    Serial.print(F("-  Unable to find BME680. Trying again in 5 seconds.\n"));
    delay(5000);
  }  // of loop until device is located
  Serial.print(F("- Setting 16x oversampling for all sensors\n"));
  BME680.setOversampling(TemperatureSensor, Oversample16);  // Use enumerated type values
  BME680.setOversampling(HumiditySensor, Oversample16);     // Use enumerated type values
  BME680.setOversampling(PressureSensor, Oversample16);     // Use enumerated type values
  Serial.print(F("- Setting IIR filter to a value of 4 samples\n"));
  BME680.setIIRFilter(IIR4);  // Use enumerated type values
  Serial.print(F("- Setting gas measurement to 320\xC2\xB0\x43 for 150ms\n"));  // "�C" symbols
  BME680.setGas(320, 150);  // 320�c for 150 milliseconds
}

void uplink_routine()
{
  static int32_t  temp, humidity, pressure, gas;  // BME readings
  BME680.getSensorData(temp, humidity, pressure, gas);  // Get readings
  static float batt = api.system.bat.get();

  payload.reset();
  payload.addTemperature(1, ((float) temp) / 100);
  payload.addRelativeHumidity(2, ((float) humidity) / 1000);
//  payload.addVoltage(3, batt);
  payload.addBarometricPressure(3, ((float) pressure) / 100);
//  payload.addGenericSensor(4, ((float) gas) / 100);
  //payload.addVoltage(5, batt_f);
  

  Serial.printf("Data Packet: %d\n", payload.getSize());
  Serial.printf("Temperature: %f\n", ((float) temp) / 100);
  Serial.printf("Battery: %f\n", batt);

  /** Send the data package */
  if (api.lorawan.send(payload.getSize(), (uint8_t *) payload.getBuffer(), 1)) {
    Serial.println("Sending is requested");
  } else {
    Serial.println("Sending failed");
  }
}

void loop()
{
  if (!api.lorawan.txp.set(TXP)) {
    Serial.printf("LoRaWan TXP - set transmit power fail! \r\n");
    return;
  }
  int retry = 3;
  /** Wait for Join success */
  while (api.lorawan.njs.get() == 0) {
    Serial.print("Wait for LoRaWAN join...");
    api.lorawan.join();
    api.system.sleep.all(10000);
    if (retry-- <= 0) {
      break;
    }    
  }

  if(retry > 0 ){
    uplink_routine();
  }
  Serial.printf("Try sleep %ums..", OTAA_PERIOD);
  api.system.sleep.all(OTAA_PERIOD);
  Serial.println("Wakeup..");
  
}
