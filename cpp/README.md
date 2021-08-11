# Official Bitwyre C++ Software Development Kit

# Getting Started

The API URL is retrieve from the environment variable `URL_API_BITWYRE`, but if you do not set it, a default one
pointing our production cluster will be used.

# Example of usage Public API

- Getting the Server time https://docs.bitwyre.id/#server-time

```c++
#include "rest/public/time.hpp"

auto main() -> int {
    // TimeResponse here can be replaced with auto
    TimeResponse tr = Time::get();
    
    std::cout << tr.unixtime << "\n";
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

- Opening an new order https://docs.bitwyre.id/#ticker

```c++
#include "rest/public/NewOrder.hpp"

auto main() -> int {
    TickerRequest tickReq{InstrumentT{"btc_usd_spot"}};
    TickerResponse tr = Ticker::get(tickReq);
    
    std::cout << tr.tickers.size() << "\n";
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
