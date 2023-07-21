#pragma once

#include "esphome/core/component.h"
#include "esphome/components/stepper/stepper.h"
#include "esphome/components/uart/uart.h"

extern "C" {
#include <ic/TMC2209/TMC2209.h>
}

namespace esphome {
namespace tmc {

class TMC2209;

static TMC2209 *comp = nullptr;

class TMC2209 : public stepper::Stepper, public Component, public uart::UARTDevice {
 public:
  TMC2209() = default;
  TMC2209(const TMC2209 &) = delete;
  TMC2209 &operator=(const TMC2209 &) = delete;
  ~TMC2209();

  void set_step_pin(GPIOPin *pin) { this->step_pin_ = pin; }
  void set_direction_pin(GPIOPin *pin) { this->dir_pin_ = pin; }
  void set_enable_pin(GPIOPin *pin) { this->enable_pin_ = pin; }

  void setup() override;
  void dump_config() override;
  void loop() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

 protected:
  GPIOPin *step_pin_;
  GPIOPin *dir_pin_;
  GPIOPin *enable_pin_{nullptr};

  bool enable_pin_state_;
  HighFrequencyLoopRequester high_freq_;

  uint32_t last_run_ = 0;
  bool direction = false;

  // TMC API stuff
  uint8_t channel_ = 0;
  uint8_t slaveAddress_ = 0x0;
  TMC2209TypeDef driver_def;
  TMC2209TypeDef *driver = &driver_def;
  ConfigurationTypeDef driver_config_def;
  ConfigurationTypeDef *driver_config = &driver_config_def;
};

}  // namespace tmc
}  // namespace esphome