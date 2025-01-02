// Using a timer asynchronously

#include <iostream>
#include <boost/asio.hpp>

void print(const boost::system::error_code& /*e*/) {
    std::cout << "hello world" << std::endl;
}

int main() {
    boost::asio::io_context io;

    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));

    t.async_wait(&print);

    io.run();
    return 0;
}