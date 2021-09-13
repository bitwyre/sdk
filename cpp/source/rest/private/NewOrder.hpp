#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Types::Private;
using AsyncNewOrderRequest = std::future<NewOrderRequest>;
namespace Bitwyre::Rest::Private {

  struct NewOrder {

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/private/orders";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto postAsync(const NewOrderRequest& request) noexcept
        -> NewOrderRequest {
      return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto post(const NewOrderRequest& request) noexcept
        -> NewOrderResponse {
      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> NewOrderResponse {
      NewOrderResponse executionReport;
      auto res = rawResponse["result"];
      executionReport.avgPx = std::stold(res["AvgPx"].get<std::string>());
      executionReport.lastLiquidityInd =
          std::stold(res["LastLiquidityInd"].get<std::string>());
      executionReport.lastPx = std::stold(res["LastPx"].get<std::string>());
      executionReport.lastQty = std::stold(res["LastQty"].get<std::string>());
      executionReport.cumQty = std::stold(res["cumqty"].get<std::string>());
      executionReport.fillPrice =
          std::stold(res["fill_price"].get<std::string>());
      executionReport.leavesQty =
          std::stold(res["leavesqty"].get<std::string>());
      executionReport.orderQty = std::stold(res["orderqty"].get<std::string>());
      executionReport.price = std::stold(res["price"].get<std::string>());
      executionReport.stopPx = std::stold(res["stoppx"].get<std::string>());
      executionReport.value = std::stold(res["value"].get<std::string>());
      if (res["ordrejreason"].get<std::string>().size()) {
        executionReport.ordRejReason =
            std::stold(res["ordrejreason"].get<std::string>());
      } else {
        executionReport.ordRejReason = 0;
      }

      executionReport.ordStatusReqId = res["ordstatusReqID"].get<std::string>();
      executionReport.origcliId = res["origclid"].get<std::string>();
      executionReport.account = res["account"].get<std::string>();
      executionReport.clOrdId = res["clorderid"].get<std::string>();
      executionReport.instrument = res["instrument"].get<std::string>();
      executionReport.orderId = res["orderid"].get<std::string>();

      executionReport.ordStatus = res["ordstatus"].get<std::uint8_t>();
      executionReport.ordType = res["ordtype"].get<std::uint8_t>();
      executionReport.timeInForce = res["time_in_force"].get<std::uint8_t>();

      executionReport.execId = res["execid"].get<std::string>();
      executionReport.execType = res["exectype"].get<std::uint8_t>();
      executionReport.expiry = res["expiry"].get<std::uint8_t>();
      executionReport.side = res["side"].get<std::uint8_t>();

      executionReport.timestamp =
          static_cast<Types::TimeT>(res["timestamp"].get<long long int>());
      executionReport.transactTime =
          static_cast<Types::TimeT>(res["transacttime"].get<long long int>());

      executionReport.cancelOnDisconnect =
          static_cast<bool>(res["cancelondisconnect"].get<short>());

      return executionReport;
    }
  };

} // namespace Bitwyre::Rest::Private