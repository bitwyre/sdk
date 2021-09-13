#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Types::Private;
using AsyncResponse = std::future<Response>;

namespace Bitwyre::Rest::Private {

  struct OpenOrders {

    using Callback = std::function<void(const Response&)>;

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/private/orders/open";
    }

    template <typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const OpenOrdersRequest& request) noexcept -> void {
      auto result = getAsync(request);
      return cb(result.get());
    }
    
    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(const OpenOrdersRequest& request) noexcept
        -> Response {
      return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(const OpenOrdersRequest& request) noexcept
        -> Response {
      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> OpenOrdersResponse {
      OpenOrdersResponse response;
      response.statusCode_ = rawResponse["statusCode"].get<int>();
      response.errors_ = rawResponse["error"].get<ErrorsT>();

      auto closedOrders = rawResponse["result"];

      for (auto it = closedOrders.cbegin(); it != closedOrders.cend(); ++it) {
        std::vector<ExecutionReport> orders;

        for (const auto& openOrder : it.value()) {
          ExecutionReport executionReport;
          executionReport.avgPx =
              std::stold(openOrder["AvgPx"].get<std::string>());
          executionReport.lastLiquidityInd =
              std::stold(openOrder["LastLiquidityInd"].get<std::string>());
          executionReport.lastPx =
              std::stold(openOrder["LastPx"].get<std::string>());
          executionReport.lastQty =
              std::stold(openOrder["LastQty"].get<std::string>());
          executionReport.cumQty =
              std::stold(openOrder["cumqty"].get<std::string>());
          executionReport.fillPrice =
              std::stold(openOrder["fill_price"].get<std::string>());
          executionReport.leavesQty =
              std::stold(openOrder["leavesqty"].get<std::string>());
          executionReport.orderQty =
              std::stold(openOrder["orderqty"].get<std::string>());
          executionReport.price =
              std::stold(openOrder["price"].get<std::string>());
          executionReport.stopPx =
              std::stold(openOrder["stoppx"].get<std::string>());
          executionReport.value =
              std::stold(openOrder["value"].get<std::string>());
          if (openOrder["ordrejreason"].get<std::string>().size()) {
            executionReport.ordRejReason =
                std::stold(openOrder["ordrejreason"].get<std::string>());
          } else {
            executionReport.ordRejReason = 0;
          }

          executionReport.ordStatusReqId =
              openOrder["ordstatusReqID"].get<std::string>();
          executionReport.origcliId = openOrder["origclid"].get<std::string>();
          executionReport.account = openOrder["account"].get<std::string>();
          executionReport.clOrdId = openOrder["clorderid"].get<std::string>();
          executionReport.instrument =
              openOrder["instrument"].get<std::string>();
          executionReport.orderId = openOrder["orderid"].get<std::string>();

          executionReport.ordStatus =
              openOrder["ordstatus"].get<std::uint8_t>();
          executionReport.ordType = openOrder["ordtype"].get<std::uint8_t>();
          executionReport.timeInForce =
              openOrder["time_in_force"].get<std::uint8_t>();

          executionReport.execId = openOrder["execid"].get<std::string>();
          executionReport.execType = openOrder["exectype"].get<std::uint8_t>();
          executionReport.expiry = openOrder["expiry"].get<std::uint8_t>();
          executionReport.side = openOrder["side"].get<std::uint8_t>();

          executionReport.timestamp = static_cast<Types::TimeT>(
              openOrder["timestamp"].get<long long int>());
          executionReport.transactTime = static_cast<Types::TimeT>(
              openOrder["transacttime"].get<long long int>());

          executionReport.cancelOnDisconnect =
              static_cast<bool>(openOrder["cancelondisconnect"].get<short>());

          orders.push_back(std::move(executionReport));
        }
        response.openOrders.push_back(
            std::make_pair(it.key(), std::move(orders)));
      }
      return response;
    }
  };
} // namespace Bitwyre::Rest::Private