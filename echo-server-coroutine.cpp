#define BOOST_ASIO_HAS_CO_AWAIT
#define BOOST_ASIO_HAS_STD_COROUTINE
#define BOOST_ASIO_HAS_IO_URING 
#define BOOST_ASIO_DISABLE_EPOLL

#include <boost/asio.hpp>
#include <boost/container/vector.hpp>
#include <filesystem>

using boost::asio::awaitable;
using boost::asio::buffer;
using boost::asio::detached;
using boost::asio::use_awaitable;
using boost::asio::ip::tcp;
using boost::asio::stream_file;

awaitable<void> echo(tcp::socket s)
{
    try
    {
        char data[1024];
        for (;;)
        {
            std::size_t n =
            co_await s.async_read_some(
                    buffer(data),
                    use_awaitable);
            co_await async_write(
                s,
                buffer(data, n),
                use_awaitable);
        }
    }
    catch (const std::exception &e)
    {
    }
}
awaitable<void> listen(tcp::acceptor a)
{
    for (;;)
    {
        co_spawn(
            a.get_executor(),
            echo(co_await a.async_accept(use_awaitable)),
            detached);
    }
}



boost::asio::awaitable<boost::container::vector<std::byte>> read_file_async(
   boost::asio::any_io_executor & exe, 
   const std::filesystem::path & p) { 
   using boost::asio::use_awaitable;
   boost::asio::stream_file file(exe, p.c_str(), 
                                 boost::asio::file_base::read_only | boost::asio::file_base::exclusive);

   if (!file.is_open()) {
     throw std::runtime_error(fmt::format("Could not open {}", p._c_str()));
   }
   constexpr std::size_t block_size = 1024 * 1024 * 2; 
   boost::container::vector<std::byte> buf(block_size, boost::container::default_init); 
   std::size_t curr_pos = 0; 
   std::size_t bytes_read = 1; 
   std::vector<std::byte> v(block_size);
   while (bytes_read > 0) {
       try {
         bytes_read = co_await file.async_read_some(boost::asio::buffer(buf.data() + curr_pos,
                                                                        buf.size() - curr_pos),
                                                    use_awaitable);
         curr_pos += bytes_read;
         if (curr_pos == buf.size())
           buf.resize(buf.size() * 2, boost::container::default_init);
       }
       catch (const boost::system::system_error & e) {
         fmt::print("{}\n", e.what());
         throw;
       }
   }
   buf.resize(curr_pos, boost::container::default_init);
   buf.shrink_to_fit();
   co_return std::move(buf);
 }


int main()
{
    //boost::asio::io_context ctx;
    //co_spawn(ctx,listen({ctx, {tcp::v4(), 1084}}),detached);
    //ctx.run();

boost::asio::io_context ctx;
auto the_task =
     [&](std::filesystem::path p) -> boost::asio::awaitable<void> {
       boost::asio::any_io_executor executor = co_await boost::asio::this_coro::executor;
       auto file_contents = co_await read_file_async(executor, p);
   };
  for (const auto &file_path : rng)
    boost::asio::co_spawn(ctx, the_task(file_path), boost::asio::detached);
  ctx.run();
}

