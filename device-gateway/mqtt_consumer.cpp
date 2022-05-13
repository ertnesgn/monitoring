#include "mqtt_consumer.hpp"

using namespace std;
using namespace chrono;

namespace consumer
{
mqtt_consumer::mqtt_consumer(const string& _address, const string& _client_id)
    : address(_address), client_id(_client_id)
{
    // Initializing the mqtt client and its parameters
    client = make_unique<mqtt::client>(address, client_id);
    client->set_timeout(1000);
    topics.emplace_back(string("#"));
    qos.emplace_back(1);
    
    // Creating the msg_ptr 
    msg_ptr = new mqtt::const_message_ptr;
};

mqtt_consumer::~mqtt_consumer()
{
    topics.clear();
    qos.clear();
    // Disconnect mqtt client
    disconnect();
    // Delete msg_ptr which is initialized in constructor
    delete msg_ptr;
    // Reset the unique pointer of client
    client.reset();
    cout << "~mqtt_consumer" << endl;
}

bool mqtt_consumer::connect()
{
    // Set connection options
    connectionOptions.set_keep_alive_interval(20);
    connectionOptions.set_clean_session(true);

    try
    {
        // Connect to the client
        client->connect(connectionOptions);

        if (!client->is_connected()) return false;

        // Subsribing the topics
        client->subscribe(topics, qos);
        return true;
    }
    catch (const mqtt::exception& exc)
    {
        cerr << "Error: " << exc.what() << " [" << exc.get_reason_code() << "]" << endl;
    }
    return false;
};

void mqtt_consumer::disconnect()
{
    if (client->is_connected())
    {
        client->disconnect();
    }
}
void mqtt_consumer::listen(const uint32_t& ms)
{
    try
    {
        if (client->is_connected())
        {
            // Try to consume the message from broker for given duration
            auto messageConsumed = client->try_consume_message_for(msg_ptr, chrono::milliseconds(ms));

            // If the message is consumed, then lets pass it to callback
            if (messageConsumed && msg_ptr)
            {
                shared_ptr<const mqtt::message> msg = *msg_ptr;
                if (msg.get())
                {
                    if (callback)
                    {
                        callback(msg.get()->get_topic(), msg.get()->to_string());
                    }
                }
            }
        }
        else
        {
            // If the connection is lost, wait for re-establishing the connection
            cout << "Connection is Lost" << endl;
            while (!client->is_connected())
            {
                this_thread::sleep_for(milliseconds(250));
            }
            cout << "Re-established connection" << endl;
        }
    }
    catch (const mqtt::exception& exc)
    {
        cerr << "Error: " << exc.what() << " [" << exc.get_reason_code() << "]" << endl;
    }
    // Disconnect
}
}  // namespace consumer