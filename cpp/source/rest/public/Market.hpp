#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Details;
using AsyncMarketResponse = std::future<MarketResponse>;

namespace Bitwyre::Rest::Public {

  struct Market {

    using Callback = std::function<void(const MarketResponse&)>;

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/markets";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb) noexcept -> void {
      static_assert( std::is_invocable_v<decltype(cb), MarketResponse> );
      auto result = getAsync();
      return cb(result.get());
    }

//    template<class Callback, typename Dispatcher = Dispatcher>
//    [[nodiscard]] static auto getAsync(Callback cb) noexcept -> std::future<void> {
//      static_assert( std::is_nothrow_invocable_v<decltype(cb), MarketResponse> );
//      return std::async(std::launch::async, [cb](){return cb(get<Dispatcher>());});
//    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync() noexcept ->  AsyncMarketResponse {
      return std::async(std::launch::async, [](){return get<Dispatcher>();});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get() noexcept -> MarketResponse {
      auto response = Dispatcher()(uri(), CommonPublicRequest{});
      return processResponse(std::move(response));
    }

    static auto processResponse(json&& response) -> MarketResponse {
      MarketResponse marketResponse;
      marketResponse.statusCode_ = response["statusCode"].get<int>();
      marketResponse.errors_ = response["error"].get<ErrorsT>();
      marketResponse.markets =
          response["result"].get<std::vector<std::string>>();
      return marketResponse;
    }
  };
} // namespace Bitwyre::Rest::Public