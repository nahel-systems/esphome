#include "esphome.h"

class SHT20Component : public PollingComponent, public i2c::I2CDevice {
 public:
  SHT20Component() : PollingComponent(60000) {}

  void set_temperature_sensor(sensor::Sensor *temperature) { temperature_ = temperature; }
  void set_humidity_sensor(sensor::Sensor *humidity) { humidity_ = humidity; }

  void setup() override {
    ESP_LOGCONFIG("sht20", "Setting up SHT20 sensor...");
  }

  void update() override {
    // Here you'd normally call read_temperature(), read_humidity()
    // For now, we will just simulate values
    if (temperature_ != nullptr)
      temperature_->publish_state(25.0 + (float) (esp_random() % 100) / 100); // random around 25°C
    if (humidity_ != nullptr)
      humidity_->publish_state(50.0 + (float) (esp_random() % 100) / 100); // random around 50%
  }

 protected:
  sensor::Sensor *temperature_{nullptr};
  sensor::Sensor *humidity_{nullptr};

  float read_temperature() {
    // TODO: implement real I2C reading here
    return 25.0;
  }

  float read_humidity() {
    // TODO: implement real I2C reading here
    return 50.0;
  }
};
