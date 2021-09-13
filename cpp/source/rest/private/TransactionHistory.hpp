#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Types::Private;

namespace Bitwyre::Rest::Private {

  struct TransactionHistory {

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/private/account/transactions";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(
        const TransactionHistoryRequest& request) noexcept
        -> TransactionHistoryResponse {
      return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(
        const TransactionHistoryRequest& request) noexcept
        -> TransactionHistoryResponse {
      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse)
        -> TransactionHistoryResponse {
      TransactionHistoryResponse response;
      response.statusCode_ = rawResponse["statusCode"].get<int>();
      response.errors_ = rawResponse["error"].get<ErrorsT>();

      auto deposits = rawResponse["result"]["deposit"];

      for (auto it = deposits.cbegin(); it != deposits.cend(); ++it) {
        std::vector<TxHistoryElement> historyDeposits;

        for (const auto& deposit : it.value()) {
          TxHistoryElement element{};
          element.accountBalanceId =
              deposit["account_balance_id"].get<std::uint64_t>();
          element.type = deposit["type"].get<short>();
          element.status = deposit["status"].get<std::string>();
          element.asset = deposit["asset"].get<std::string>();
          element.notes = deposit["notes"].get<std::string>();
          element.amount = std::stold(deposit["amount"].get<std::string>());
          element.finalBalance =
              std::stold(deposit["final_balance"].get<std::string>());
          element.address = deposit["address"].get<std::string>();
          element.time =
              static_cast<Types::TimeT>(deposit["time"].get<long long int>());

          historyDeposits.push_back(std::move(element));
        }
        response.deposits.push_back(std::make_pair(it.key(), historyDeposits));
      }

      auto withdrawals = rawResponse["result"]["withdrawal"];

      for (auto it = withdrawals.cbegin(); it != withdrawals.cend(); ++it) {
        std::vector<TxHistoryElement> historyWithdrawals;

        for (const auto& withdrawal : it.value()) {
          TxHistoryElement element{};
          element.accountBalanceId =
              withdrawal["account_balance_id"].get<std::uint64_t>();
          element.type = withdrawal["type"].get<short>();
          element.status = withdrawal["status"].get<std::string>();
          element.asset = withdrawal["asset"].get<std::string>();
          element.notes = withdrawal["notes"].get<std::string>();
          element.amount = std::stold(withdrawal["amount"].get<std::string>());
          element.finalBalance =
              std::stold(withdrawal["final_balance"].get<std::string>());
          element.address = withdrawal["address"].get<std::string>();
          element.time = static_cast<Types::TimeT>(
              withdrawal["time"].get<long long int>());

          historyWithdrawals.push_back(std::move(element));
        }
        response.withdrawals.push_back(
            std::make_pair(it.key(), historyWithdrawals));
      }
      return response;
    }
  };
} // namespace Bitwyre::Rest::Private