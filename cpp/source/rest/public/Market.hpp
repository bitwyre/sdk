#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Details;

namespace Bitwyre::Rest::Public {

  struct Market {

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/markets";
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