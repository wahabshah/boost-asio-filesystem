#define BOOST_ASIO_HAS_CO_AWAIT
#define BOOST_ASIO_HAS_STD_COROUTINE
#define BOOST_ASIO_HAS_IO_URING
#define BOOST_ASIO_DISABLE_EPOLL

#include <iostream>
#include <boost/asio.hpp>
#include <boost/container/vector.hpp>
#include <filesystem>
#include <fmt/format.h>

using boost::asio::awaitable;
using boost::asio::buffer;
using boost::asio::detached;
using boost::asio::use_awaitable;
using boost::asio::ip::tcp;

awaitable<void> writeAndreadFile(boost::asio::io_context &my_io_context) {

  try {
    std::filesystem::path path1 = "/workspace/boost-asio-iouring/test.txt";
    char data1[1024] = "Hello World";
    std::size_t n1 = 11;
    boost::asio::stream_file file(my_io_context,
                                  path1.c_str(),
                                  boost::asio::stream_file::write_only |
                                      boost::asio::stream_file::create |
                                      boost::asio::stream_file::truncate);
    co_await file.async_write_some(buffer(data1, n1), use_awaitable);
    std::cout << "wrote to: " << path1.c_str() << ": " << n1 << " " << data1 << std::endl;

    boost::asio::stream_file file1(my_io_context,
                                   path1.c_str(),
                                   boost::asio::stream_file::read_only);
    char data2[1024];
    std::size_t n2 =
        co_await file1.async_read_some(buffer(data2), use_awaitable);
    std::cout << "read from: " << path1.c_str() << ": " << n2 << " " << data2 << std::endl;

  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

int main() {
  std::cout << "Starting Writing and Reading File" << std::endl;
  boost::asio::io_context ctx;
  boost::asio::co_spawn(ctx, writeAndreadFile(ctx), boost::asio::detached);
  ctx.run();
}