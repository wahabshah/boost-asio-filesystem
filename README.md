# boost-asio-iouring


```sh
uname -r
# 5.15.0-47-generic
```

```sh
rm -rf build && mkdir -p build && \
(cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make clean all VERBOSE=1) && \
./build/echo-server-perthread
```

* https://stackoverflow.com/questions/70632719/asio-reading-stream-file-asynchronously-fails-with-coroutines-and-alternatives
