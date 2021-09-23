#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Types::Private;
using AsyncCloseOrdersResponse = std::future<ClosedOrdersResponse>;

namespace Bitwyre::Rest::Private {

  struct ClosedOrders {

    using Callback = std::function<void(const ClosedOrdersResponse&)>;

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/private/orders/closed";
    }

    using Callback = std::function<void(const ClosedOrdersResponse&)>;
    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const ClosedOrdersRequest& request) noexcept -> void{
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const ClosedOrdersRequest& request) noexcept -> void{
      static_assert( std::is_nothrow_invocable_v<decltype(cb), ClosedOrdersResponse>);
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const ClosedOrdersRequest& request) noexcept -> void{
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(const ClosedOrdersRequest& request) noexcept
        -> AsyncCloseOrdersResponse {
      return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(const ClosedOrdersRequest& request) noexcept
        -> ClosedOrdersResponse {

      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> ClosedOrdersResponse {
      ClosedOrdersResponse response;
      response.statusCode_ = rawResponse["statusCode"].get<int>();
      response.errors_ = rawResponse["error"].get<ErrorsT>();

      auto closedOrders = rawResponse["result"];

      for (auto it = closedOrders.cbegin(); it != closedOrders.cend(); ++it) {
        std::vector<ExecutionReport> orders;

        for (const auto& closedOrder : it.value()) {
          ExecutionReport executionReport;
          executionReport.avgPx =
              std::stold(closedOrder["AvgPx"].get<std::string>());
          executionReport.lastLiquidityInd =
              std::stold(closedOrder["LastLiquidityInd"].get<std::string>());
          executionReport.lastPx =
              std::stold(closedOrder["LastPx"].get<std::string>());
          executionReport.lastQty =
              std::stold(closedOrder["LastQty"].get<std::string>());
          executionReport.cumQty =
              std::stold(closedOrder["cumqty"].get<std::string>());
          executionReport.fillPrice =
              std::stold(closedOrder["fill_price"].get<std::string>());
          executionReport.leavesQty =
              std::stold(closedOrder["leavesqty"].get<std::string>());
          executionReport.orderQty =
              std::stold(closedOrder["orderqty"].get<std::string>());
          executionReport.price =
              std::stold(closedOrder["price"].get<std::string>());
          executionReport.stopPx =
              std::stold(closedOrder["stoppx"].get<std::string>());
          executionReport.value =
              std::stold(closedOrder["value"].get<std::string>());
          if (closedOrder["ordrejreason"].get<std::string>().size()) {
            executionReport.ordRejReason =
                std::stold(closedOrder["ordrejreason"].get<std::string>());
          } else {
            executionReport.ordRejReason = 0;
          }
          executionReport.ordStatusReqId =
              closedOrder["ordstatusReqID"].get<std::string>();
          executionReport.origcliId =
              closedOrder["origclid"].get<std::string>();
          executionReport.account = closedOrder["account"].get<std::string>();
          executionReport.clOrdId = closedOrder["clorderid"].get<std::string>();
          executionReport.instrument =
              closedOrder["instrument"].get<std::string>();
          executionReport.orderId = closedOrder["orderid"].get<std::string>();

          executionReport.ordStatus =
              closedOrder["ordstatus"].get<std::uint8_t>();
          executionReport.ordType = closedOrder["ordtype"].get<std::uint8_t>();
          executionReport.timeInForce =
              closedOrder["time_in_force"].get<std::uint8_t>();

          executionReport.execId = closedOrder["execid"].get<std::string>();
          executionReport.execType =
              closedOrder["exectype"].get<std::uint8_t>();
          executionReport.expiry = closedOrder["expiry"].get<std::uint8_t>();
          executionReport.side = closedOrder["side"].get<std::uint8_t>();

          executionReport.timestamp = static_cast<Types::TimeT>(
              closedOrder["timestamp"].get<long long int>());
          executionReport.transactTime = static_cast<Types::TimeT>(
              closedOrder["transacttime"].get<long long int>());

          executionReport.cancelOnDisconnect =
              static_cast<bool>(closedOrder["cancelondisconnect"].get<short>());

          orders.push_back(std::move(executionReport));
        }
        response.closedOrders.push_back(
            std::make_pair(it.key(), std::move(orders)));
      }
      return response;
    }
  };

}; // namespace Bitwyre::Rest::Private