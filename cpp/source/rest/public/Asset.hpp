#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Details;
using AsyncAssetResponse = std::future<AssetResponse>;
namespace Bitwyre::Rest::Public {

  struct Asset {

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/assets";
    }
    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync() noexcept -> AsyncAssetResponse {
        return std::async(std::launch::async, [](){return get<Dispatcher>();});
    }
    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get() noexcept -> AssetResponse {
      auto response = Dispatcher()(uri(), CommonPublicRequest{});
      return processResponse(std::move(response));
    }

    static auto processResponse(json&& rawResponse) -> AssetResponse {
      AssetResponse assetResponse;
      assetResponse.statusCode_ = rawResponse["statusCode"].get<int>();
      assetResponse.errors_ = rawResponse["error"].get<ErrorsT>();

      for (const auto& asset : rawResponse["result"]) {
        AssetElement parsedAsset;
        parsedAsset.name = asset["name"].get<std::string>();
        assetResponse.assets.push_back(std::move(parsedAsset));
      }
      return assetResponse;
    }
  };
} // namespace Bitwyre::Rest::Public
