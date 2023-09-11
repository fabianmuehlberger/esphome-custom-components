#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"

#include "esphome/components/tmc2209/tmc2209.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace tmc {

class TMC2209Sensor : public PollingComponent, public sensor::Sensor {
 public:
  TMC2209Sensor() = default;

  float get_setup_priority() const override { return setup_priority::DATA; }
  void dump_config() override;
  void setup() override;
  void update() override;

 protected:
  TMC2209 *tmc2209;
};

}  // namespace tmc
}  // namespace esphome
