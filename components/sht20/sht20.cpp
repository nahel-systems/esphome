#include "sht20.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sht20 {

static const char *TAG = "sht20";

void SHT20Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up SHT20...");
}

void SHT20Component::update() {
  ESP_LOGD(TAG, "Reading SHT20 sensor...");
  float temperature = read_temperature();
  float humidity = read_humidity();
  if (temperature_ != nullptr)
    temperature_->publish_state(temperature);
  if (humidity_ != nullptr)
    humidity_->publish_state(humidity);
}

}  // namespace sht20
}  // namespace esphome
