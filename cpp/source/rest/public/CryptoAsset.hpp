#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Details;
using AsyncCrytoAssetResponse = std::future<CryptoAssetResponse>;

namespace Bitwyre::Rest::Public {

  struct CryptoAsset {

    using Callback = std::function<void(const CryptoAssetResponse&)>;

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/assets/crypto";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb) noexcept -> void {
      auto result = getAsync();
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync() noexcept -> AsyncCrytoAssetResponse {
      return std::async(std::launch::async, [](){return get<Dispatcher>();});

    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get() noexcept -> CryptoAssetResponse {
      auto rawResponse = Dispatcher()(uri(), CommonPublicRequest{});
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) -> CryptoAssetResponse {
      CryptoAssetResponse assetResponse;
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
