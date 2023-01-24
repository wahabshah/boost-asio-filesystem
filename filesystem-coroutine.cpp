#define BOOST_ASIO_HAS_CO_AWAIT
#define BOOST_ASIO_HAS_STD_COROUTINE
#define BOOST_ASIO_HAS_IO_URING
#define BOOST_ASIO_DISABLE_EPOLL

#include <iostream>
#include <filesystem>
#include <boost/asio.hpp>

boost::asio::awaitable<void> writeAndreadFile(boost::asio::io_context &my_io_context)
{
  try
  {
    std::filesystem::path path = std::filesystem::current_path() /= "test.txt";
    char data1[1024] = "Hello World";
    std::size_t n1 = 11;
    boost::asio::stream_file file1(my_io_context, path.c_str(), boost::asio::stream_file::write_only | boost::asio::stream_file::create | boost::asio::stream_file::truncate);
                     co_await boost::asio::async_write(file1, boost::asio::buffer(data1, n1), boost::asio::use_awaitable);
    std::cout << "wrote to: " << path.c_str() << ": " << n1 << " " << data1 << std::endl;

    boost::asio::stream_file file2(my_io_context, path.c_str(), boost::asio::stream_file::read_only);
    char data2[1024];
    std::size_t n2 = co_await file2.async_read_some(boost::asio::buffer(data2), boost::asio::use_awaitable);
    std::cout << "read from: " << path.c_str() << ": " << n2 << " " << data2 << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }
}

int main()
{
  std::cout << "Starting Writing and Reading File" << std::endl;
  boost::asio::io_context ctx;
  boost::asio::co_spawn(ctx, writeAndreadFile(ctx), boost::asio::detached);
  ctx.run();
}
