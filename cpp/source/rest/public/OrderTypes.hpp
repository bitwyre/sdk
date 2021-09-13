#pragma once
#include "../../details/Dispatcher.hpp"
using namespace Bitwyre::Details;
using AsyncOrderTypesResponse = std::future<OrderTypesResponse>;

namespace Bitwyre::Rest::Public {

  struct OrderTypes {

    using Callback = std::function<void(const OrderTypesResponse&)>;

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/ordertypes";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb) noexcept -> void {
      static_assert( std::is_nothrow_invocable_v<decltype(cb), OrderTypesResponse> );
      auto result = getAsync();
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync() noexcept -> AsyncOrderTypesResponse {
      return std::async(std::launch::async, [](){return get<Dispatcher>();});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get() noexcept -> OrderTypesResponse {
      auto rawResponse = Dispatcher()(uri(), CommonPublicRequest{});
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> OrderTypesResponse {
      OrderTypesResponse orderTypesResponse;
      orderTypesResponse.statusCode_ = rawResponse["statusCode"].get<int>();
      orderTypesResponse.errors_ = rawResponse["error"].get<ErrorsT>();

      for (const auto& orderType : rawResponse["result"]) {
        orderTypesResponse.orderTypes.push_back(orderType);
      }
      return orderTypesResponse;
    }
  };
} // namespace Bitwyre::Rest::Public