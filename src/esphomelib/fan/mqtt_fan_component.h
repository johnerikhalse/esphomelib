//
// Created by Otto Winter on 29.12.17.
//

#ifndef ESPHOMELIB_FAN_MQTT_FAN_COMPONENT_H
#define ESPHOMELIB_FAN_MQTT_FAN_COMPONENT_H

#include "esphomelib/defines.h"

#ifdef USE_FAN

#include "esphomelib/mqtt/mqtt_component.h"
#include "esphomelib/fan/fan_state.h"

ESPHOMELIB_NAMESPACE_BEGIN

namespace fan {

class MQTTFanComponent : public mqtt::MQTTComponent {
 public:
  explicit MQTTFanComponent(FanState *state);

  /// Set a custom oscillation command topic. Defaults to "<base>/oscillation/command".
  void set_custom_oscillation_command_topic(const std::string &topic);
  /// Set a custom oscillation state topic. Defaults to "<base>/oscillation/state".
  void set_custom_oscillation_state_topic(const std::string &topic);
  /// Set a custom speed command topic. Defaults to "<base>/speed/command".
  void set_custom_speed_command_topic(const std::string &topic);
  /// Set a custom speed state topic. Defaults to "<base>/speed/state".
  void set_custom_speed_state_topic(const std::string &topic);

  void send_discovery(JsonBuffer &buffer, JsonObject &root, mqtt::SendDiscoveryConfig &config) override;

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  /// Setup the fan subscriptions and discovery.
  void setup() override;
  /// Send the full current state to MQTT.
  void send_initial_state() override;
  void publish_state();
  /// 'fan' component type for discovery.
  std::string component_type() const override;

  const std::string get_oscillation_command_topic() const;
  const std::string get_oscillation_state_topic() const;
  const std::string get_speed_command_topic() const;
  const std::string get_speed_state_topic() const;

  FanState *get_state() const;

  bool is_internal() override;

 protected:
  std::string friendly_name() const override;

  FanState *state_;
};

} // namespace fan

ESPHOMELIB_NAMESPACE_END

#endif //USE_FAN

#endif //ESPHOMELIB_FAN_MQTT_FAN_COMPONENT_H
