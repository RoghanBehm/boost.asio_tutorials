// Using a timer synchronously
#include <iostream>
#include <boost/asio.hpp>

int main() {
    boost::asio::io_context io; // All asio programs need an I/O execution context
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
    t.wait();  // Blocking wait on the timer (steady_timer::wait() will not return until timer has expired)
    std::cout << "hello, world" << std::endl;
    
    return 0;
}