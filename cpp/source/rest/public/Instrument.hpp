#pragma once
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Details;
using namespace Bitwyre::Types::Public;
using AsyncInstrumentResponse = std::future<InstrumentResponse>;
using Callback = std::function<void(const InstrumentResponse&)>;

namespace Bitwyre::Rest::Public {

  struct Instrument {

    [[nodiscard]] static auto uri() noexcept -> std::string {
      return "/public/pairs";
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const InstrumentRequest& request) noexcept -> void {
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const InstrumentRequest& request) noexcept -> void {
      static_assert( std::is_nothrow_invocable_v<decltype(cb), InstrumentResponse> );
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(Callback cb, const InstrumentRequest& request) noexcept -> void {
      auto result = getAsync(request);
      return cb(result.get());
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto getAsync(const InstrumentRequest& request) noexcept -> AsyncInstrumentResponse {
      return std::async(std::launch::async, [&request](){return get<Dispatcher>(request);});
    }

    template<typename Dispatcher = Dispatcher>
    [[nodiscard]] static auto get(const InstrumentRequest& request) noexcept
        -> InstrumentResponse {
      auto rawResponse = Dispatcher()(uri(), request);
      return processResponse(std::move(rawResponse));
    }

    static auto processResponse(json&& rawResponse) noexcept
        -> InstrumentResponse {
      InstrumentResponse instrumentResponse;
      instrumentResponse.statusCode_ = rawResponse["statusCode"].get<int>();
      instrumentResponse.errors_ = rawResponse["error"].get<ErrorsT>();

      for (const auto& rawInstrument : rawResponse["result"]) {
        InstrumentElement instrumentElement;
        instrumentElement.instrument =
            rawInstrument["instrument"].get<std::string>();
        instrumentElement.symbol = rawInstrument["symbol"].get<std::string>();
        instrumentResponse.instruments.push_back(std::move(instrumentElement));
      }
      return instrumentResponse;
    }
  };
} // namespace Bitwyre::Rest::Public