#pragma once

#include "../../details/Dispatcher.hpp"
using namespace Bitwyre::Types::Private;
using AsyncResponse = std::future<Response>;
namespace Bitwyre::Rest::Private {

  struct TradesHistory {

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/private/trades";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(const TradesHistoryRequest& request) noexcept
        -> AsyncResponse {
      return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(const TradesHistoryRequest& request) noexcept
        -> Response {
      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> TradesHistoryResponse {
      TradesHistoryResponse tradesHistoryResponse;
      tradesHistoryResponse.statusCode_ = rawResponse["statusCode"].get<int>();
      tradesHistoryResponse.errors_ = rawResponse["error"].get<ErrorsT>();

      for (auto it = rawResponse["result"].cbegin();
           it != rawResponse["result"].cend();
           ++it) {
        std::vector<TradesHistoryElement> trades;

        for (const auto& trade : it.value()) {
          TradesHistoryElement thistoryElmt;
          thistoryElmt.execPrice = trade["exec_price"].get<long double>();
          thistoryElmt.execQty = trade["exec_qty"].get<long double>();
          thistoryElmt.execValue = trade["exec_value"].get<long double>();
          thistoryElmt.feePaid = trade["fee_paid"].get<long double>();
          thistoryElmt.feeRate = trade["fee_rate"].get<long double>();
          thistoryElmt.feeRate = trade["fee_rate"].get<long double>();
          thistoryElmt.feeType = trade["fee_type"].get<long double>();
          thistoryElmt.notes = trade["notes"].get<std::string>();
          thistoryElmt.orderUuid = trade["order_uuid"].get<std::string>();
          thistoryElmt.symbol = trade["symbol"].get<std::string>();
          thistoryElmt.userUuid = trade["user_uuid"].get<std::string>();

          thistoryElmt.orderPrice = trade["order_price"].get<long double>();
          thistoryElmt.orderQty = trade["order_qty"].get<long double>();
          thistoryElmt.orderRemaining =
              trade["order_remaining"].get<long double>();
          thistoryElmt.orderType = trade["order_type"].get<short>();
          thistoryElmt.side = trade["side"].get<short>();
          thistoryElmt.status = trade["status"].get<short>();
          thistoryElmt.timestamp = static_cast<Types::TimeT>(
              trade["timestamp"].get<long long int>());

          trades.push_back(std::move(thistoryElmt));
        }

        tradesHistoryResponse.histories.push_back(
            std::make_pair(it.key(), std::move(trades)));
      }
      return tradesHistoryResponse;
    }
  };
} // namespace Bitwyre::Rest::Private