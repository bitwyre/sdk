#pragma once
#include "../../details/Types.hpp"
#include<future>
using namespace Bitwyre::Types::Private;
using AsyncAccountStatementResponse = std::future<AccountStatementResponse>;

namespace Bitwyre::Rest::Private {

  struct AccountStatement {

    using Callback = std::function<void(const AccountStatementResponse&)>;

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/private/account/statement";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const AccountStatementRequest& request) noexcept -> void {
      static_assert( std::is_nothrow_invocable_v<decltype(cb), AccountStatementResponse>);
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const AccountStatementRequest& request) noexcept -> void {
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(const AccountStatementRequest& request) noexcept
        -> AsyncAccountStatementResponse {
      return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(const AccountStatementRequest& request) noexcept
        -> AccountStatementResponse {
      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse)
        -> AccountStatementResponse {
      AccountStatementResponse statementResponse;
      statementResponse.statusCode_ = rawResponse["statusCode"].get<int>();
      statementResponse.errors_ = rawResponse["error"].get<ErrorsT>();

      auto deposits = rawResponse["result"]["deposit"];

      for (auto it = deposits.cbegin(); it != deposits.cend(); ++it) {
        std::vector<AccountStatementElement> assetDeposits;

        for (const auto& deposit : it.value()) {
          AccountStatementElement statementElement{};
          statementElement.fee = deposit["fee"].get<long double>();
          statementElement.grossAmount =
              deposit["gross_amount"].get<long double>();
          statementElement.nettAmount =
              deposit["nett_amount"].get<long double>();
          statementElement.id = deposit["id"].get<long>();
          statementElement.provider = deposit["provider"].get<std::string>();
          statementElement.type = deposit["type"].get<std::string>();
          statementElement.status = deposit["status"].get<std::string>();
          if (statementElement.type == "crypto") {
            statementElement.txId = deposit["tx_id"].get<std::string>();
            statementElement.networkConfirmation =
                deposit["network_confirmation"].get<std::uint64_t>();
          }

          statementElement.submitTime = static_cast<Types::TimeT>(
              deposit["submit_time"].get<long long int>());
          statementElement.successTime = static_cast<Types::TimeT>(
              deposit["success_time"].get<long long int>());
          assetDeposits.push_back(std::move(statementElement));
        }
        statementResponse.deposits.push_back(
            std::make_pair(it.key(), assetDeposits));
      }

      auto withdrawals = rawResponse["result"]["withdrawal"];

      for (auto it = withdrawals.cbegin(); it != withdrawals.cend(); ++it) {
        std::vector<AccountStatementElement> assetDeposits;
        for (const auto& withdrawal : it.value()) {
          AccountStatementElement statementElement{};
          statementElement.fee = withdrawal["fee"].get<long double>();
          statementElement.grossAmount =
              withdrawal["gross_amount"].get<long double>();
          statementElement.nettAmount =
              withdrawal["nett_amount"].get<long double>();
          statementElement.id = withdrawal["id"].get<long>();
          statementElement.provider = withdrawal["provider"].get<std::string>();
          statementElement.type = withdrawal["type"].get<std::string>();
          statementElement.status = withdrawal["status"].get<std::string>();
          if (statementElement.type == "crypto") {
            statementElement.txId = withdrawal["tx_id"].get<std::string>();
            statementElement.networkConfirmation =
                withdrawal["network_confirmation"].get<std::uint64_t>();
          }

          statementElement.submitTime = static_cast<Types::TimeT>(
              withdrawal["submit_time"].get<long long int>());
          statementElement.successTime = static_cast<Types::TimeT>(
              withdrawal["success_time"].get<long long int>());
          assetDeposits.push_back(std::move(statementElement));
        }
        statementResponse.withdrawals.push_back(
            std::make_pair(it.key(), assetDeposits));
      }
      return statementResponse;
    }
  };
}// namespace Bitwyre::Rest::Private