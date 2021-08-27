#pragma once
#include "Config.hpp"
#include "Response.hpp"
#include "Types.hpp"
#include "cpr/cpr.h"
#include "nlohmann/json.hpp"
#include <string_view>
#include <utility>

using namespace Bitwyre::Types::Public;
using namespace Bitwyre::Types::Private;

namespace Bitwyre {

  using json = nlohmann::json;
  using ErrorsT = std::vector<std::string>;

  namespace Details {

    class Dispatcher {
      inline static const auto config = Config::getConfig();

    public:
      Dispatcher() = default;

      auto operator()(std::string_view uri, CommonPublicRequest) noexcept {
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());
        auto res = cpr::Get(endpoint);

        auto jsonRes = json::parse(res.text.begin(), res.text.end());
        jsonRes["statusCode"] = res.status_code;
        return jsonRes;
      }

      auto operator()(std::string_view uri,
                      const InstrumentRequest& request) noexcept {
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());

        auto queryString = cpr::Parameters{{"market", request.market_.get()},
                                           {"product", request.product_.get()},
                                           {"country", request.country_.get()}};

        auto res = cpr::Get(endpoint, std::move(queryString));

        auto jsonRes = json::parse(res.text.begin(), res.text.end());
        jsonRes["statusCode"] = res.status_code;
        return jsonRes;
      }

      auto operator()(std::string_view uri,
                      const TickerRequest& request) noexcept {
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());

        cpr::Response res;
        if (request.instrument_.get().empty()) {
          res = cpr::Get(endpoint);
        } else {
          auto queryString =
              cpr::Parameters{{"instrument", request.instrument_.get()}};
          res = cpr::Get(endpoint, std::move(queryString));
        }
        auto jsonRes = json::parse(res.text.begin(), res.text.end());
        jsonRes["statusCode"] = res.status_code;
        return jsonRes;
      }

      auto operator()(std::string_view uri,
                      const ContractRequest& request) noexcept {
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());

        auto queryString =
            cpr::Parameters{{"instrument", request.instrument_.get()}};
        auto res = cpr::Get(endpoint, std::move(queryString));
        auto jsonRes = json::parse(res.text.begin(), res.text.end());

        jsonRes["statusCode"] = res.status_code;
        return jsonRes;
      }

      auto operator()(std::string_view uri,
                      const TradesRequest& request) noexcept {
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());

        auto queryString = cpr::Parameters{
            {"instrument", request.instrument_.get()},
            {"trade_num", std::to_string(request.tradeNum_.get())}};
        auto res = cpr::Get(endpoint, std::move(queryString));
        auto jsonRes = json::parse(res.text.begin(), res.text.end());

        jsonRes["statusCode"] = res.status_code;
        return jsonRes;
      }

      auto operator()(std::string_view uri,
                      const DepthRequest& request) noexcept {
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());

        auto queryString = cpr::Parameters{
            {"instrument", request.instrument_.get()},
            {"depth_num", std::to_string(request.depthNum_.get())}};
        auto res = cpr::Get(endpoint, std::move(queryString));
        auto jsonRes = json::parse(res.text.begin(), res.text.end());

        jsonRes["statusCode"] = res.status_code;
        return jsonRes;
      }

      auto operator()(std::string_view uri,
                      const AccountBalanceRequest& request) noexcept {
        assert(std::getenv("BITWYRE_API_KEY") != nullptr &&
               "BITWYRE_API_KEY NOT SET");

        auto nonce = Utils::getTimestamp();
        auto checksum = Utils::lowercase(request.checksum());
        auto signature = Utils::lowercase(Utils::sign(uri, nonce, checksum));

        auto parameters = cpr::Parameters{
            {"nonce", std::to_string(nonce)},
            {"checksum", checksum},
            {"payload", ""},
        };
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());

        auto header = cpr::Header{{"Api-Key", std::getenv("BITWYRE_API_KEY")},
                                  {"API-Sign", signature}};

        auto res = cpr::Get(endpoint, header, parameters);
        auto rawResponse = json::parse(res.text.begin(), res.text.end());
        rawResponse["statusCode"] = res.status_code;
        return rawResponse;
      }

      auto operator()(std::string_view uri,
                      const AccountStatementRequest& request) noexcept {
        assert(std::getenv("BITWYRE_API_KEY") != nullptr &&
               "BITWYRE_API_KEY NOT SET");

        auto nonce = Utils::getTimestamp();
        auto checksum = Utils::lowercase(request.checksum());
        auto signature = Utils::lowercase(Utils::sign(uri, nonce, checksum));

        std::string payloadParam{};
        if (!request.assets_.get().empty()) {
          payloadParam = request.toString();
        }

        auto parameters = cpr::Parameters{
            {"nonce", std::to_string(nonce)},
            {"checksum", checksum},
            {"payload", payloadParam},
        };
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());

        auto header = cpr::Header{{"Api-Key", std::getenv("BITWYRE_API_KEY")},
                                  {"API-Sign", signature}};

        auto res = cpr::Get(endpoint, header, parameters);
        auto rawResponse = json::parse(res.text.begin(), res.text.end());
        rawResponse["statusCode"] = res.status_code;
        return rawResponse;
      }

      auto operator()(std::string_view uri,
                      const CancelOrderRequest& request) noexcept {
        assert(std::getenv("BITWYRE_API_KEY") != nullptr &&
               "BITWYRE_API_KEY NOT SET");

        auto nonce = Utils::getTimestamp();
        auto checksum = Utils::lowercase(request.checksum());
        auto signature = Utils::lowercase(Utils::sign(uri, nonce, checksum));

        auto parameters = cpr::Parameters{
            {"nonce", std::to_string(nonce)},
            {"checksum", checksum},
            {"payload", request.toString()},
        };
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());

        auto header = cpr::Header{{"Api-Key", std::getenv("BITWYRE_API_KEY")},
                                  {"API-Sign", signature}};

        auto res = cpr::Delete(endpoint, header, parameters);
        auto rawResponse = json::parse(res.text.begin(), res.text.end());
        rawResponse["statusCode"] = res.status_code;
        return rawResponse;
      }

      auto operator()(std::string_view uri,
                      const ClosedOrdersRequest& request) noexcept {
        assert(std::getenv("BITWYRE_API_KEY") != nullptr &&
               "BITWYRE_API_KEY NOT SET");
        auto nonce = Utils::getTimestamp();
        auto checksum = Utils::lowercase(request.checksum());
        std::string modifiedURI{};
        std::string payload{};

        if (request.instrument_.get().empty()) {
          modifiedURI = std::string{uri} + "/all";
        } else {
          modifiedURI = uri.data();
          payload = request.toString();
        }

        auto signature = Utils::sign(modifiedURI, nonce, checksum);
        auto parameters = cpr::Parameters{
            {"nonce", std::to_string(nonce)},
            {"checksum", std::move(checksum)},
            {"payload", payload},
        };
        auto endpoint = cpr::Url(std::string{config.at("URL_API_BITWYRE")} +
                                 std::move(modifiedURI));

        auto header = cpr::Header{{"Api-Key", std::getenv("BITWYRE_API_KEY")},
                                  {"API-Sign", Utils::lowercase(signature)}};
        auto res = cpr::Get(endpoint, header, parameters);
        auto jsonRes = json::parse(res.text.begin(), res.text.end());
        jsonRes["statusCode"] = res.status_code;
        return jsonRes;
      }

      auto operator()(std::string_view uri, NewOrderRequest request) {
        assert(std::getenv("BITWYRE_API_KEY") != nullptr &&
               "BITWYRE_API_KEY NOT SET");

        auto nonce = Utils::getTimestamp();
        auto checksum = Utils::lowercase(request.checksum());
        auto signature = Utils::sign(uri, nonce, checksum);
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());

        json payload = {{"nonce", nonce},
                        {"checksum", checksum},
                        {"payload", request.toString()}};

        auto reqPayload = cpr::Body{payload.dump()};

        auto header = cpr::Header{{"Api-Key", std::getenv("BITWYRE_API_KEY")},
                                  {"API-Sign", Utils::lowercase(signature)},
                                  {"Content-Type", "application/json"}};

        auto res = cpr::Post(endpoint, header, reqPayload);
        auto jsonRes = json::parse(res.text.begin(), res.text.end());
        jsonRes["statusCode"] = 200;
        return jsonRes;
      }

      auto operator()(std::string_view uri, const OrderInfoRequest& request) {
        assert(std::getenv("BITWYRE_API_KEY") != nullptr &&
               "BITWYRE_API_KEY NOT SET");

        auto nonce = Utils::getTimestamp();
        auto checksum = Utils::lowercase(request.checksum());
        std::string modifiedURI;

        if (request.orderId_.get().empty()) {
          modifiedURI = std::string(uri.data()) + "/all";
        } else {
          modifiedURI = std::string(uri) + "/" + request.orderId_.get();
        }

        auto signature = Utils::sign(modifiedURI, nonce, checksum);

        auto parameters = cpr::Parameters{
            {"nonce", std::to_string(nonce)},
            {"checksum", checksum},
            {"payload", ""},
        };
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + modifiedURI);

        auto header = cpr::Header{{"Api-Key", std::getenv("BITWYRE_API_KEY")},
                                  {"API-Sign", Utils::lowercase(signature)}};
        auto res = cpr::Get(endpoint, header, parameters);
        auto jsonRes = json::parse(res.text.begin(), res.text.end());
        return jsonRes;
      }

      auto operator()(std::string_view uri,
                      const TradesHistoryRequest& request) {
        assert(std::getenv("BITWYRE_API_KEY") != nullptr &&
               "BITWYRE_API_KEY NOT SET");

        auto nonce = Utils::getTimestamp();
        auto checksum = Utils::lowercase(request.checksum());
        auto signature = Utils::sign(uri, nonce, checksum);

        auto parameters = cpr::Parameters{
            {"nonce", std::to_string(nonce)},
            {"checksum", checksum},
            {"payload", ""},
        };
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());

        auto header = cpr::Header{{"Api-Key", std::getenv("BITWYRE_API_KEY")},
                                  {"API-Sign", Utils::lowercase(signature)}};
        auto res = cpr::Get(endpoint, header, parameters);
        return json::parse(res.text.begin(), res.text.end());
      }

      auto operator()(std::string_view uri,
                      const TransactionHistoryRequest& request) {
        auto nonce = Utils::getTimestamp();
        auto checksum = Utils::lowercase(request.checksum());
        auto signature = Utils::sign(uri, nonce, checksum);

        auto parameters = cpr::Parameters{
            {"nonce", std::to_string(nonce)},
            {"checksum", checksum},
            {"payload", ""},
        };
        auto endpoint =
            cpr::Url(std::string{config.at("URL_API_BITWYRE")} + uri.data());

        auto header = cpr::Header{{"Api-Key", std::getenv("BITWYRE_API_KEY")},
                                  {"API-Sign", Utils::lowercase(signature)}};
        auto res = cpr::Get(endpoint, header, parameters);
        return json::parse(res.text.begin(), res.text.end());
      }
    };
  } // namespace Details
} // namespace Bitwyre