# boost-asio-iouring

<a href="https://gitpod.io/#https://github.com/wahabshah/boost-asio-iouring" rel="nofollow noopener noreferrer" target="_blank" class="after:hidden"><img src="https://gitpod.io/button/open-in-gitpod.svg" alt="Open in Gitpod"></a>

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
