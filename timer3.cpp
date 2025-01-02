// Binding arguments to a completion handler

#include <functional>
#include <iostream>
#include <boost/asio.hpp>

void print(const boost::system::error_code& /*e*/,
    boost::asio::steady_timer* t, int* count)
{
    if (*count < 5)
    {
        std::cout << *count << std::endl;
        ++(*count);
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));

        // The steady_timer::async_wait() function expects a handler function (or function object) 
        // with the signature void(const boost::system::error_code&). Binding the additional parameters
        // converts your print function into a function object that matches the signature correctly. 

        // In this example, the boost::asio::placeholders::error argument to std::bind is a named placeholder for the error object passed to the handler
        // When initiating the asynchronous operation, and if using std::bind, you must specify only the arguments that match the handler's parameter list. 

        t->async_wait(std::bind(print,
          boost::asio::placeholders::error, t, count));
    }
}

int main()
{
    boost::asio::io_context io;

    int count = 0;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));

    t.async_wait(std::bind(print,
    boost::asio::placeholders::error, &t, &count));

    io.run();
    std::cout << "Final count is " << count << std::endl;

    return 0;
}