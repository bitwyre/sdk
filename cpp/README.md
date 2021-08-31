# Official Bitwyre C++ Software Development Kit

# Getting Started

Roughly speaking, a REST API is about getting request and processing response.

The Dispatcher class is responsible to send request. Each end point has to process response, write it to JSON format output.

The API URL is retrieve from the environment variable `URL_API_BITWYRE`, but if you do not set it, a default one
pointing to our production cluster will be used.

# Building from source 

## Requirements

- Clang 12.0.1 or any Compiler with support of C++17
- Conan version 1.37 or greater for package management
- CMake version 3.20.3

## Build commands

```shell
rm -r ~/.conan/data/bitwyresdk
conan create . bitwyresdk/1.0.0@ 
mkdir build
cd build
#conan install .. --build=missing
conan install .. -e CONAN_RUN_TESTS=0
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=1
make
#&& cd $_ && cmake .. -DUNIT_TESTS=1 -DBUILD_TESTING=1 -DCMAKE_BUILD_TYPE=Debug
```

Note: everytime we run `conan create` we don't need to wait for our changes to be merged in develop branch.
The `create` command will update our local cache and we can run the examples with the updates.

In order to build the test suite add `-DBUILD_TESTING` definition.

# Package Managers 

## Conan 

Add our remote https://conan.bitwyre.id/artifactory/api/conan/bitwyre to your list of remotes

```
conan remote add bitwyre  https://conan.bitwyre.id/artifactory/api/conan/bitwyre
```

Then inside your `conanfile.py` or `conanfile.txt` add `bitwyresdk/[>=1.0]`

## Vckpg 

Coming Soon 

# Example of usage Public API

- Getting the Server time https://docs.bitwyre.id/#server-time

```c++
#include "bitwyresdk/rest/public/Time.hpp"

auto main() -> int {
    // TimeResponse here can be replaced with auto
    TimeResponse tr = Bitwyre::Rest::Public::Time::get();
    
    std::cout << tr.unixtime.count() << "\n";
}
```

- Getting the list of tickers https://docs.bitwyre.id/#ticker

```c++
#include "rest/public/Ticker.hpp"

auto main() -> int {
    TickerRequest tickReq{InstrumentT{"btc_usd_spot"}};
    TickerResponse tr = Ticker::get(tickReq);
    
    std::cout << tr.tickers.size() << "\n";
}
```

# Example of usage Private API

All private APIs are authenticated following https://docs.bitwyre.id/#authentication.

For running these endpoints, follow the documentation link above and retrieve your **API-KEY** and **API-SECRET**, they will be
required in order to sign every request.

Once you've retrieved the API credentials, set them as environment variable.

```shell
export BITWYRE_API_SECRET=mysecret
export BITWYRE_API_KEY=mypublic
```

At this point we are all set to run the examples.

- Opening a new order https://docs.bitwyre.id/#ticker

```c++
#include "rest/public/NewOrder.hpp"

auto main() -> int {
    NewOrderRequest request{
      InstrumentT{"btc_usd_spot"},
      SideT{1},
      OrdType{1},
      PriceT{100},
      QtyT{100},
  };
    
    auto result = NewOrder::post(request);
    
    std::cout << result.instrument << "\n";
}
```

# License

> Copyright (c) 2019 Kracejic
> Copyright (c) 2021 Bitwyre LLC
>
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
