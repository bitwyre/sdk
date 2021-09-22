#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Details;
using namespace Bitwyre::Types;
using AsyncTickerResponse = std::future<TickerResponse>;

namespace Bitwyre::Rest::Public {

  struct Ticker {

    using Callback = std::function<void(const TickerResponse&)>;

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/ticker";
    }

    using Callback = std::function<void(const TickerResponse&)>;
    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const TickerRequest& request) noexcept -> void {
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const TickerRequest& request) noexcept -> void {
      static_assert( std::is_nothrow_invocable_v<decltype(cb), TickerResponse> );
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(const TickerRequest& request) noexcept -> AsyncTickerResponse {
      return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(const TickerRequest& request) noexcept
        -> TickerResponse {
      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> TickerResponse {
      TickerResponse tickerResponse;
      tickerResponse.statusCode_ = rawResponse["statusCode"].get<int>();
      tickerResponse.errors_ = rawResponse["error"].get<ErrorsT>();

      if (rawResponse["result"].is_array()) {
        for (const auto& ticker : rawResponse["result"]) {
          TickerElement tickerElement{};
          tickerElement.instrument = ticker["instrument"].get<std::string>();
          tickerElement.assetBase = ticker["asset_base"].get<std::string>();
          tickerElement.assetQuote = ticker["asset_quote"].get<std::string>();
          tickerElement.market = ticker["market"].get<std::string>();
          tickerElement.isFrozen = ticker["is_frozen"].get<int>();
          tickerElement.high = std::stold(ticker["high"].get<std::string>());
          tickerElement.low = std::stold(ticker["low"].get<std::string>());
          tickerElement.percentChange =
              std::stold(ticker["percent_change"].get<std::string>());
          tickerElement.volumeQuote =
              std::stold(ticker["volume_quote"].get<std::string>());
          tickerElement.volumeBase =
              std::stold(ticker["volume_base"].get<std::string>());
          tickerElement.last = std::stold(ticker["last"].get<std::string>());
          tickerElement.bestBid =
              std::stold(ticker["best_bid"].get<std::string>());
          tickerElement.bestAsk =
              std::stold(ticker["best_ask"].get<std::string>());
          tickerElement.timestamp =
              static_cast<TimeT>(ticker["timestamp"].get<long long int>());

          tickerResponse.tickers.push_back(std::move(tickerElement));
        }
      } else {
        TickerElement tickerElement{};
        auto ticker = rawResponse["result"];
        tickerElement.instrument = ticker["instrument"].get<std::string>();
        tickerElement.assetBase = ticker["asset_base"].get<std::string>();
        tickerElement.assetQuote = ticker["asset_quote"].get<std::string>();
        tickerElement.market = ticker["market"].get<std::string>();
        tickerElement.isFrozen = ticker["is_frozen"].get<int>();
        tickerElement.high = std::stold(ticker["high"].get<std::string>());
        tickerElement.low = std::stold(ticker["low"].get<std::string>());
        tickerElement.percentChange =
            std::stold(ticker["percent_change"].get<std::string>());
        tickerElement.volumeQuote =
            std::stold(ticker["volume_quote"].get<std::string>());
        tickerElement.volumeBase =
            std::stold(ticker["volume_base"].get<std::string>());
        tickerElement.last = std::stold(ticker["last"].get<std::string>());
        tickerElement.bestBid =
            std::stold(ticker["best_bid"].get<std::string>());
        tickerElement.bestAsk =
            std::stold(ticker["best_ask"].get<std::string>());
        tickerElement.timestamp =
            static_cast<TimeT>(ticker["timestamp"].get<long long int>());

        tickerResponse.tickers.push_back(std::move(tickerElement));
      }
      return tickerResponse;
    }
  };
} // namespace Bitwyre::Rest::Public
