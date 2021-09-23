#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Types::Private;
using AsyncExecutionReport = std::future<ExecutionReport>;
using Callback = std::function<void(const ExecutionReport&)>;

namespace Bitwyre::Rest::Private {

  struct CancelOrder {

    using Callback = std::function<void(const ExecutionReport&)>;

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/private/orders/cancel";
    }

    template <typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto delAsync(Callback cb, const CancelOrderRequest& request) noexcept -> void {
      auto result = delAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto delAsync(const CancelOrderRequest& request) noexcept
        -> AsyncExecutionReport {
      return std::async(std::launch::async, [&request](){return del<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto del(const CancelOrderRequest& request) noexcept
        -> ExecutionReport {
      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> ExecutionReport {
      ExecutionReport executionReport{};
      executionReport.statusCode_ = rawResponse["statusCode"].get<int>();
      executionReport.errors_ = rawResponse["error"].get<ErrorsT>();

      auto result = rawResponse["result"];
      executionReport.avgPx = std::stold(result["AvgPx"].get<std::string>());
      executionReport.lastLiquidityInd =
          std::stold(result["LastLiquidityInd"].get<std::string>());
      executionReport.lastPx = std::stold(result["LastPx"].get<std::string>());
      executionReport.lastQty =
          std::stold(result["LastQty"].get<std::string>());
      executionReport.cumQty = std::stold(result["cumqty"].get<std::string>());
      executionReport.fillPrice =
          std::stold(result["fill_price"].get<std::string>());
      executionReport.leavesQty =
          std::stold(result["leavesqty"].get<std::string>());
      executionReport.orderQty =
          std::stold(result["orderqty"].get<std::string>());
      executionReport.price = std::stold(result["price"].get<std::string>());
      executionReport.stopPx = std::stold(result["stoppx"].get<std::string>());
      executionReport.value = std::stold(result["value"].get<std::string>());
      if (result["ordrejreason"].get<std::string>().size()) {
        executionReport.ordRejReason =
            std::stold(result["ordrejreason"].get<std::string>());
      } else {
        executionReport.ordRejReason = 0;
      }

      executionReport.ordStatusReqId =
          result["ordstatusReqID"].get<std::string>();
      executionReport.origcliId = result["origclid"].get<std::string>();
      executionReport.account = result["account"].get<std::string>();
      executionReport.clOrdId = result["clorderid"].get<std::string>();
      executionReport.instrument = result["instrument"].get<std::string>();
      executionReport.orderId = result["orderid"].get<std::string>();

      executionReport.ordStatus = result["ordstatus"].get<std::uint8_t>();
      executionReport.ordType = result["ordtype"].get<std::uint8_t>();
      executionReport.timeInForce = result["time_in_force"].get<std::uint8_t>();

      executionReport.execId = result["execid"].get<std::string>();
      executionReport.execType = result["exectype"].get<std::uint8_t>();
      executionReport.expiry = result["expiry"].get<std::uint8_t>();
      executionReport.side = result["side"].get<std::uint8_t>();

      executionReport.timestamp =
          static_cast<Types::TimeT>(result["timestamp"].get<long long int>());
      executionReport.transactTime = static_cast<Types::TimeT>(
          result["transacttime"].get<long long int>());

      executionReport.cancelOnDisconnect =
          static_cast<bool>(result["cancelondisconnect"].get<short>());
      return executionReport;
    }
  };
} // namespace Bitwyre::Rest::Private