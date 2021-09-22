#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Types::Private;
using AsyncOrderInfoResponse = std::future<OrderInfoResponse>;

namespace Bitwyre::Rest::Private {

  struct OrderInfo {

    using Callback = std::function<void(const OrderInfoResponse&)>;

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/private/orders/info";
    }

    using Callback = std::function<void(const OrderInfoResponse&)>;
    template <typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const OrderInfoRequest& request) noexcept -> void {
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(const OrderInfoRequest& request) noexcept
        -> AsyncOrderInfoResponse {
      return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(const OrderInfoRequest& request) noexcept
        -> OrderInfoResponse {
      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> OrderInfoResponse {
      OrderInfoResponse response{};
      response.statusCode_ = rawResponse["statusCode"].get<int>();
      response.errors_ = rawResponse["error"].get<ErrorsT>();

      for (const auto& order : rawResponse["result"]) {
        ExecutionReport executionReport;
        executionReport.avgPx = std::stold(order["AvgPx"].get<std::string>());
        executionReport.lastLiquidityInd =
            std::stold(order["LastLiquidityInd"].get<std::string>());
        executionReport.lastPx = std::stold(order["LastPx"].get<std::string>());
        executionReport.lastQty =
            std::stold(order["LastQty"].get<std::string>());
        executionReport.cumQty = std::stold(order["cumqty"].get<std::string>());
        executionReport.fillPrice =
            std::stold(order["fill_price"].get<std::string>());
        executionReport.leavesQty =
            std::stold(order["leavesqty"].get<std::string>());
        executionReport.orderQty =
            std::stold(order["orderqty"].get<std::string>());
        executionReport.price = std::stold(order["price"].get<std::string>());
        executionReport.stopPx = std::stold(order["stoppx"].get<std::string>());
        executionReport.value = std::stold(order["value"].get<std::string>());
        if (order["ordrejreason"].get<std::string>().size()) {
          executionReport.ordRejReason =
              std::stold(order["ordrejreason"].get<std::string>());
        } else {
          executionReport.ordRejReason = 0;
        }

        executionReport.ordStatusReqId =
            order["ordstatusReqID"].get<std::string>();
        executionReport.origcliId = order["origclid"].get<std::string>();
        executionReport.account = order["account"].get<std::string>();
        executionReport.clOrdId = order["clorderid"].get<std::string>();
        executionReport.instrument = order["instrument"].get<std::string>();
        executionReport.orderId = order["orderid"].get<std::string>();

        executionReport.ordStatus = order["ordstatus"].get<std::uint8_t>();
        executionReport.ordType = order["ordtype"].get<std::uint8_t>();
        executionReport.timeInForce =
            order["time_in_force"].get<std::uint8_t>();

        executionReport.execId = order["execid"].get<std::string>();
        executionReport.execType = order["exectype"].get<std::uint8_t>();
        executionReport.expiry = order["expiry"].get<std::uint8_t>();
        executionReport.side = order["side"].get<std::uint8_t>();

        executionReport.timestamp =
            static_cast<Types::TimeT>(order["timestamp"].get<long long int>());
        executionReport.transactTime = static_cast<Types::TimeT>(
            order["transacttime"].get<long long int>());

        executionReport.cancelOnDisconnect =
            static_cast<bool>(order["cancelondisconnect"].get<short>());

        response.ordersInfo.push_back(std::move(executionReport));
      }
      return response;
    }
  };
} // namespace Bitwyre::Rest::Private