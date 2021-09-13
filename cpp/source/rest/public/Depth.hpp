#pragma once
#include "../../details/Dispatcher.hpp"
using namespace Bitwyre::Details;
using AsyncDepthResponse = std::future<DepthResponse>;
namespace Bitwyre::Rest::Public {

  struct Depth {

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/depth";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(const DepthRequest& request) noexcept -> AsyncDepthResponse {
      return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(const DepthRequest& request) noexcept
        -> DepthResponse {
      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> DepthResponse {
      DepthResponse depthResponse;
      depthResponse.statusCode_ = rawResponse["statusCode"].get<int>();
      depthResponse.errors_ = rawResponse["error"].get<ErrorsT>();

      for (const auto& depth : rawResponse["result"]["bids"]) {
        auto p = std::make_pair(std::stold(depth[0].get<std::string>()),
                                std::stold(depth[1].get<std::string>()));
        depthResponse.bids.push_back(std::move(p));
      }

      for (const auto& depth : rawResponse["result"]["asks"]) {
        auto p = std::make_pair(std::stold(depth[0].get<std::string>()),
                                std::stold(depth[1].get<std::string>()));
        depthResponse.asks.push_back(std::move(p));
      }
      return depthResponse;
    }
  };
} // namespace Bitwyre::Rest::Public
