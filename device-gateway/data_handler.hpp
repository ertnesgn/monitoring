#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

#include "base_consumer.hpp"
#include "data_details.hpp"

using namespace std;

namespace data_handler
{

class data_handler
{
  public:
    data_handler();
    ~data_handler();
    void register_consumer(unique_ptr<consumer::base_consumer> _consumer);
    void consume(const uint32_t& ms);
    void print_data_map();

  private:
    unique_ptr<consumer::base_consumer> consumer{nullptr};
    unordered_map<string, data_details<string>> data_map;
};

}  // namespace data_handler