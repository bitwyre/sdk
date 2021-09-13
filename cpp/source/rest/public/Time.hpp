#pragma once
#include "../../details/Dispatcher.hpp"
using namespace Bitwyre::Details;
using AsyncTimeResponse = std::future<TimeResponse>;

namespace Bitwyre::Rest::Public {
  using TimeT = std::chrono::nanoseconds;

  struct Time {

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/time";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync() noexcept -> AsyncTimeResponse {
      return std::async(std::launch::async, [](){return get<Dispatcher>();});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get() noexcept -> TimeResponse { //from Types.hpp
      auto response = Dispatcher()(uri(), CommonPublicRequest{});
      return processResponse(std::move(response));
    }

    static auto processResponse(json&& rawResponse) -> TimeResponse {
      TimeResponse timeResponse;
      timeResponse.statusCode_ = rawResponse["statusCode"].get<int>();
      timeResponse.errors_ = rawResponse["error"].get<ErrorsT>();
      timeResponse.unixtime =
          static_cast<TimeT>(rawResponse["result"]["unixtime"].get<long long int>());
      return timeResponse;
    }
  };
} // namespace Bitwyre::Rest::Public
