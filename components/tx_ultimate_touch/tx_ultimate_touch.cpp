#include "esphome/core/log.h"
#include "tx_ultimate_touch.h"

namespace esphome {
namespace tx_ultimate_touch {

static const char *TAG = "tx_touch";

void TxUltimateTouch::setup() {
  ESP_LOGI(TAG, "TX Ultimate Touch ready");
}

void TxUltimateTouch::loop() {
  int bytes[15] = {0};
  int i = 0;

  while (this->available()) {
    int b = this->read();

    if (i < 15)
      bytes[i++] = b;

    if (b == 170) {
      handle_touch_(bytes);
      i = 0;
    }
  }
}

void TxUltimateTouch::handle_touch_(int bytes[]) {
  if (!is_valid_data_(bytes))
    return;

  send_touch_(get_touch_point_(bytes));
}

bool TxUltimateTouch::is_valid_data_(int bytes[]) {
  return (bytes[0] == 170 && bytes[1] == 85);
}

int TxUltimateTouch::get_touch_state_(int bytes[]) {
  return bytes[4];
}

int TxUltimateTouch::get_x_(int bytes[]) {
  return bytes[6];
}

TouchPoint TxUltimateTouch::get_touch_point_(int bytes[]) {
  TouchPoint tp;
  tp.x = get_x_(bytes);
  tp.state = get_touch_state_(bytes);
  return tp;
}

void TxUltimateTouch::send_touch_(TouchPoint tp) {
  switch (tp.state) {

    case 1:
      ESP_LOGD(TAG, "RELEASE %d", tp.x);
      this->release_trigger_.trigger(tp);
      break;

    case 2:
      ESP_LOGD(TAG, "PRESS %d", tp.x);
      this->touch_trigger_.trigger(tp);
      break;

    case 12:
      ESP_LOGD(TAG, "SWIPE RIGHT");
      this->swipe_right_trigger_.trigger(tp);
      break;

    case 13:
      ESP_LOGD(TAG, "SWIPE LEFT");
      this->swipe_left_trigger_.trigger(tp);
      break;

    case 11:
      ESP_LOGD(TAG, "FULL TOUCH");
      this->full_touch_release_trigger_.trigger(tp);
      break;

    default:
      break;
  }
}

void TxUltimateTouch::dump_config() {
  ESP_LOGCONFIG(TAG, "TX Ultimate Touch OK");
}

}  // namespace tx_ultimate_touch
}  // namespace esphome
