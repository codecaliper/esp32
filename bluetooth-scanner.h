#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.print("Device found: ");
      Serial.println(advertisedDevice.getName().c_str());
      Serial.print("  Address: ");
      Serial.println(advertisedDevice.getAddress().toString().c_str());
    }
};

void setup() {
  Serial.begin(115200);
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
}

void loop() {
  BLEScanResults foundDevices = pBLEScan->start(10);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  pBLEScan->clearResults();
  delay(1000);
}
