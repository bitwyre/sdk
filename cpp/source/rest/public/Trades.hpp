#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Details;

namespace Bitwyre::Rest::Public {

  struct Trades {

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/trades";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(const TradesRequest& tradesRequest) noexcept
        -> TradesResponse {
      auto rawResponse = Dispatcher()(uri(), tradesRequest);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> TradesResponse {
      TradesResponse tradesResponse;
      tradesResponse.statusCode_ = rawResponse["statusCode"].get<int>();
      tradesResponse.errors_ = rawResponse["error"].get<ErrorsT>();

      for (const auto& trade : rawResponse["result"]) {
        TradeElement tradeElement{};
        tradeElement.instrument = trade["instrument"].get<std::string>();
        tradeElement.tradeUuid = trade["trade_uuid"].get<std::string>();
        tradeElement.price = std::stold(trade["price"].get<std::string>());
        tradeElement.value = std::stold(trade["price"].get<std::string>());
        tradeElement.volume = std::stold(trade["volume"].get<std::string>());
        tradeElement.timestamp =
            static_cast<TimeT>(trade["timestamp"].get<long long int>());
        tradesResponse.trades.push_back(std::move(tradeElement));
      }
      return tradesResponse;
    }
  };
} // namespace Bitwyre::Rest::Public
