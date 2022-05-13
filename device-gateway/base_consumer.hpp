#pragma once

#include <functional>

using namespace std;

namespace consumer
{
typedef function<void(string, string)> CallbackFunction;

class base_consumer
{
  public:
    virtual ~base_consumer() {};
    virtual bool connect() = 0;
    virtual void listen(const uint32_t& milliseconds) = 0;
    virtual void disconnect() = 0;

    void register_callback(CallbackFunction _callback) { callback = _callback; }

  protected:
    CallbackFunction callback;
};

}  // namespace consumer
