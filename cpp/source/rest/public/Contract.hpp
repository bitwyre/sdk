#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Details;
using AsyncContractRequest = std::future<ContractRequest>;
namespace Bitwyre::Rest::Public {

  struct Contract {

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/contract";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(const ContractRequest& request) noexcept ->  AsyncContractRequest {
        return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(const ContractRequest& request) noexcept
        -> ContractResponse {
      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> ContractResponse {
      ContractResponse contractResponse;
      contractResponse.statusCode_ = rawResponse["statusCode"].get<int>();
      contractResponse.errors_ = rawResponse["error"].get<ErrorsT>();
      auto contract = rawResponse["result"];
      contractResponse.instrument = contract["instrument"].get<std::string>();
      contractResponse.details = contract["details"].get<std::string>();
      contractResponse.pricingSource =
          contract["pricing_source"].get<std::string>();
      contractResponse.bitwyreIndexPrice =
          std::stold(contract["bitwyre_index_price"].get<std::string>());
      contractResponse.bitwyreIndexPriceCurrency =
          contract["bitwyre_index_price_currency"].get<std::string>();
      contractResponse.volume24h =
          std::stold(contract["24h_volume"].get<std::string>());
      contractResponse.volume24hCurrency =
          contract["24h_volume_currency"].get<std::string>();
      contractResponse.openInterest =
          contract["open_interest"].get<std::string>();
      contractResponse.interestRate =
          contract["interest_rate"].get<std::string>();
      contractResponse.contractValue =
          contract["contract_value"].get<std::string>();
      contractResponse.initialMarginBaseValue =
          contract["initial_margin_base_value"].get<std::string>();
      contractResponse.maintenanceMarginBaseValue =
          contract["maintenance_margin_base_value"].get<std::string>();
      return contractResponse;
    }
  };
} // namespace Bitwyre::Rest::Public
