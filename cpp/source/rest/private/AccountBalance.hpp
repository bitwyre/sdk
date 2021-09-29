#pragma once
#include "../../details/Dispatcher.hpp"
using namespace Bitwyre::Types::Private;
using namespace Bitwyre::Details;
using AsyncAccountBalanceResponse = std::future<AccountBalanceResponse>;

namespace Bitwyre::Rest::Private {
  using json = nlohmann::json;

  struct AccountBalance {

    using Callback = std::function<void(const AccountBalanceResponse&)>;

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/private/account/spotbalance";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const AccountBalanceRequest& request) noexcept -> void {
      static_assert( std::is_invocable_v<decltype(cb), AccountBalanceResponse>);
      auto result = getAsync(request);
      return cb(result.get());
    }

//    template<class Callback, typename Dispatcher = Dispatcher>
//    [[nodiscard]] static auto getAsync(Callback cb) noexcept -> std::future<void> {
//      static_assert( std::is_nothrow_invocable_v<decltype(cb), AccountBalanceResponse> );
//      return std::async(std::launch::async, [cb](){return cb(get<Dispatcher>());});
//    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const AccountBalanceRequest& request) noexcept -> void {
      static_assert( std::is_nothrow_invocable_v<decltype(cb), AccountBalanceResponse>);
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const AccountBalanceRequest& request) noexcept -> void {
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(const AccountBalanceRequest& request) noexcept
        -> AsyncAccountBalanceResponse {
      return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(const AccountBalanceRequest& request) noexcept
        -> AccountBalanceResponse {
      auto rawResponse = Dispatcher()(uri().data(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> AccountBalanceResponse {
      AccountBalanceResponse accountBalanceResponse;
      accountBalanceResponse.statusCode_ = rawResponse["statusCode"].get<int>();
      accountBalanceResponse.errors_ = rawResponse["error"].get<ErrorsT>();

      for (const auto& rawBalance : rawResponse["result"]) {
        AccountBalanceElement balanceElement;
        balanceElement.asset = rawBalance["asset"].get<std::string>();
        balanceElement.localReference =
            rawBalance["local_reference"].get<std::string>();
        balanceElement.availableBalance =
            rawBalance["available_balance"].get<std::int64_t>();
        balanceElement.btcEquivalent =
            rawBalance["btc_equivalent"].get<std::int64_t>();
        balanceElement.localEquivalent =
            rawBalance["local_equivalent"].get<std::int64_t>();
        balanceElement.lockedBalance =
            rawBalance["locked_balance"].get<std::int64_t>();
        balanceElement.totalBalance =
            rawBalance["total_balance"].get<std::int64_t>();
        accountBalanceResponse.balances.push_back(std::move(balanceElement));
      }
      return accountBalanceResponse;
    }
  };
} // namespace Bitwyre::Rest::Private