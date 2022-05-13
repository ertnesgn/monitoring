#include <csignal>
#include <iostream>

#include "data_handler.hpp"
#include "mqtt_consumer.hpp"

using namespace std;

atomic_bool run{true};

void handler(int sig)
{
    run = false;
}

int main()
{
    // Catch the SIGINT
    signal(SIGINT, handler);

    data_handler::data_handler handler;

    // Initializing the mqtt consumer.
    const string address{"127.0.0.1"};
    const string id{"gateway"};
    auto consumer = make_unique<consumer::mqtt_consumer>(address, id);

    // Connecting the consumer to broker
    if (!consumer->connect())
    {
        consumer.reset();
        return -1;
    }

    // Pass consumer to handler
    handler.register_consumer(move(consumer));

    // Consume in loop with 1000ms timeout for each iteration
    while (run)
    {
        handler.consume(1000);
    }

    // Printing the collected data on exit
    handler.print_data_map();

    return 0;
}
