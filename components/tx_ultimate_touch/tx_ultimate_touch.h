#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace tx_ultimate_touch {

struct TouchPoint {
  int8_t x = -1;
  int8_t state = -1;
};

class TxUltimateTouch : public Component, public uart::UARTDevice {
 public:
  Trigger<TouchPoint> touch_trigger_;
  Trigger<TouchPoint> release_trigger_;
  Trigger<TouchPoint> swipe_left_trigger_;
  Trigger<TouchPoint> swipe_right_trigger_;
  Trigger<TouchPoint> full_touch_release_trigger_;
  Trigger<TouchPoint> long_touch_release_trigger_;

  void setup() override;
  void loop() override;
  void dump_config() override;

 protected:
  void handle_touch_(int bytes[]);
  bool is_valid_data_(int bytes[]);
  TouchPoint get_touch_point_(int bytes[]);
  int get_touch_state_(int bytes[]);
  int get_x_(int bytes[]);
  void send_touch_(TouchPoint tp);
};

}  // namespace tx_ultimate_touch
}  // namespace esphome
