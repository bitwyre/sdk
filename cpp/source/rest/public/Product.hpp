#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Details;
using AsyncProductResponse = std::future<ProductResponse>;
using Callback = std::function<void(const ProductResponse&)>;

namespace Bitwyre::Rest::Public {

  struct Product {

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/products";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb) noexcept -> void {
      auto result = getAsync();
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync() noexcept -> AsyncProductResponse {
      return std::async(std::launch::async, [](){return get<Dispatcher>();});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get() noexcept -> ProductResponse {
      auto rawResponse = Dispatcher()(uri(), CommonPublicRequest{});
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& response) -> ProductResponse {
      ProductResponse productResponse;
      productResponse.statusCode_ = response["statusCode"];
      productResponse.errors_ = response["error"].get<ErrorsT>();
      productResponse.products =
          response["result"].get<std::vector<std::string>>();
      return productResponse;
    }
  };
} // namespace Bitwyre::Rest::Public
