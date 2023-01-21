# boost-asio-iouring

<a href="https://gitpod.io/#https://github.com/wahabshah/boost-asio-iouring" rel="nofollow noopener noreferrer" target="_blank" class="after:hidden"><img src="https://gitpod.io/button/open-in-gitpod.svg" alt="Open in Gitpod"></a>

* The repository is using boot asio with io-uring library and coroutines
* Boost Asio 1.78 got support for filesytem to use io-uring

```sh
uname -r
# 5.15.0-47-generic
```

```sh
rm -rf build && mkdir -p build && \
(cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make clean all VERBOSE=1) && \
./build/filesystem-coroutine
```

* https://stackoverflow.com/questions/70632719/asio-reading-stream-file-asynchronously-fails-with-coroutines-and-alternatives
* https://www.boost.org/doc/libs/1_78_0/doc/html/boost_asio/history.html
* https://fmt.dev/latest/usage.html#usage-with-cmake
* https://packages.debian.org/sid/libfmt-dev
* https://packages.debian.org/sid/amd64/libfmt-dev/filelist
* https://www.boost.org/doc/libs/1_68_0/boost/container/vector.hpp
* https://www.gitpod.io/docs/configure/workspaces/workspace-image#custom-base-image
* https://packages.debian.org/experimental/libboost-all-dev
* https://packages.debian.org/bookworm/liburing-dev
* https://stackoverflow.com/questions/71590689/how-to-properly-handle-windows-paths-with-the-long-path-prefix-with-stdfilesys
* https://stackoverflow.com/questions/29191855/what-is-the-proper-way-to-use-pkg-config-from-cmake
