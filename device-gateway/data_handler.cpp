#include "data_handler.hpp"

#include <iostream>

using namespace std;

namespace data_handler
{

data_handler::data_handler() {}
data_handler::~data_handler()
{
    consumer.reset();
    cout << "~data_handler" << endl;
}
void data_handler::register_consumer(unique_ptr<consumer::base_consumer> _consumer)
{
    // Move the consumer to class member
    consumer = move(_consumer);

    // Registering lambda expressions as a callback function
    consumer->register_callback(
        [&](string device, string data)
        {
            // Find the device in the map
            auto found = data_map.find(device);

            if (found == data_map.end())
            {
                // If the device is not found, add this new device
                cout << device << " is added with " << data << endl;
                data_map.insert(pair<string, data_details<string>>(device, data_details<string>(data)));
            }
            else
            {
                // If the device is found, update it.
                found->second.update(data);
                cout << "Update " << found->first << " with " << data << ".Count:" << found->second.count << endl;
            }
        });
}
void data_handler::consume(const uint32_t& ms)
{
    // Listen the consumer and it will call the callback
    consumer->listen(ms);
}

void data_handler::print_data_map()
{
    for (auto element : data_map)
    {
        cout << "Device: " << element.first << endl;
        cout << "    Last data :" << element.second.last << endl;
        cout << "    Count     :" << element.second.count << endl;
    }
}

}  // namespace data_handler