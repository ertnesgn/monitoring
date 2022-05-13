#pragma once

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

#include "base_consumer.hpp"
#include "mqtt/client.h"

using namespace std;

namespace consumer
{
class mqtt_consumer : public base_consumer
{
  public:
    mqtt_consumer(const string& _address, const string& _client_id);
    ~mqtt_consumer();
    bool connect() override;
    void listen(const uint32_t& ms) override;
    void disconnect() override;

  private:
    unique_ptr<mqtt::client> client{nullptr};
    mqtt::const_message_ptr* msg_ptr{nullptr};
    string address{""};
    string client_id{""};
    mqtt::connect_options connectionOptions;
    vector<string> topics;
    vector<int> qos;
};
}  // namespace consumer