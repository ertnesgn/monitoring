#pragma once

template <typename T>
struct data_details
{
    data_details() = delete;
    data_details(T first) { update(first); };
    void update(T data)
    {
        // Update the last data
        last = data;

        // Increase the counter by one
        count++;
    }
    uint32_t count{0};
    T last;
};
