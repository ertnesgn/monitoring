#include <stdlib.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "mqtt/client.h"

#define QOS 1

using namespace std;
using namespace chrono;

int main(int argc, char* argv[])
{
    int opt;
    string brokerAddress{"127.0.0.1"};
    string topic{""};
    uint32_t period{0};

    while ((opt = getopt(argc, argv, "b:t:p:")) != -1)
    {
        switch (opt)
        {
            case 'b':
                brokerAddress = optarg;
                break;
            case 't':
                topic = optarg;
                break;
            case 'p':
                period = atoi(optarg);
                break;
            default: /* '?' */
                exit(-1);
        }
    }

    if (topic.length() < 3 || topic.length() > 32)
    {
        cerr << "Name of the topic is didn't fullfilled the criteria" << endl;
        exit(-1);
    }
    if (period < 100 || period > 10000)
    {
        cerr << "Period should be between 100 and 10000. Using default period." << endl;
        exit(-1);
    }

    mqtt::client client(brokerAddress, topic);
    mqtt::connect_options connectionOptions;
    connectionOptions.set_keep_alive_interval(20);
    connectionOptions.set_clean_session(true);

    srand((unsigned int)time(NULL));

    try
    {
        // Connect to the client
        client.connect(connectionOptions);

        // Creating the message
        while (true)
        {
            auto data = std::rand() % 100 + 1;
            auto msg = mqtt::make_message(topic, std::to_string(data));
            msg->set_qos(QOS);

            // Publishing
            client.publish(msg);
            this_thread::sleep_for(milliseconds(250));
        }

        // Disconnect
        client.disconnect();
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << " [" << exc.get_reason_code() << "]" << std::endl;
        return 1;
    }

    return 0;
}
