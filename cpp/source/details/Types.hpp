#pragma once
#include "details/Response.hpp"
#include "details/Utils.hpp"
#include "named_type.hpp"
#include "nlohmann/json.hpp"
#include <sstream>
#include <string>

using Bitwyre::Details::Response;
using namespace fluent;

namespace Bitwyre::Types {
  using json = nlohmann::json;
  using TimeT = std::chrono::nanoseconds;
  using MarketT = NamedType<std::string, struct MarketTag>;
  using OrderIdT = NamedType<std::string, struct MarketTag>;
  using ProductT = NamedType<std::string, struct ProductTag>;
  using CountryT = NamedType<std::string, struct CountryTag>;
  using InstrumentT = NamedType<std::string, struct InstrumentTag>;
  using TradeNumT = NamedType<std::uint32_t, struct TradeNumTag>;
  using DepthNumT = NamedType<std::uint32_t, struct TradeNumTag>;
  using CountT = NamedType<std::uint64_t, struct CountTag>;
  using AssetsT = NamedType<std::vector<std::string>, struct AssetsTag>;
  using OrderIdsT = NamedType<std::vector<std::string>, struct OrderIdsTag>;
  using QtyT = NamedType<long double, struct QtyTag>;
  using SideT = NamedType<short, struct SideTag>;
  using OrdType = NamedType<short, struct OrdTypeTag>;
  using PriceT = NamedType<short, struct PriceTag>;

  namespace Public {

    struct TimeResponse : Response {
      TimeT unixtime;
    };

    struct MarketResponse : Response {
      std::vector<std::string> markets;
    };

    struct ProductResponse : Response {
      std::vector<std::string> products;
    };

    struct AssetElement {
      std::string asset;
      std::string iconUrl;
      std::string name;
      std::string precision;
      std::string localEquivalent;
      std::string localReference;
      std::string btcEquivalent;
      double withdrawalFee;
      double minWithdrawal;
      double maxWithdrawal;
      bool isDepositEnabled;
      bool isTradingEnabled;
      bool isWithdrawEnabled;
    };

    struct AssetResponse : Response {
      std::vector<AssetElement> assets;
    };

    struct CryptoAssetResponse : Response {
      std::vector<AssetElement> assets;
    };

    struct FiatAssetResponse : Response {
      std::vector<AssetElement> assets;
    };

    struct InstrumentElement {
      std::string instrument;
      std::string symbol;
    };

    struct InstrumentResponse : Response {
      std::vector<InstrumentElement> instruments;
    };

    struct CommonPublicRequest {};

    struct InstrumentRequest {
      MarketT market_;
      ProductT product_;
      CountryT country_;

      InstrumentRequest(MarketT market, ProductT product, CountryT country)
          : market_{std::move(market)}, product_{std::move(product)},
            country_{std::move(country)} {}
    };

    struct TickerRequest {
      InstrumentT instrument_{""};

      TickerRequest() = default;
      TickerRequest(InstrumentT instrument)
          : instrument_{std::move(instrument)} {}
    };

    struct TickerElement {
      std::string instrument;
      std::string assetBase;
      std::string assetQuote;
      std::string market;
      bool isFrozen;
      long double high;
      long double low;
      long double percentChange;
      long double volumeBase;
      long double volumeQuote;
      long double last;
      long double bestBid;
      long double bestAsk;
      TimeT timestamp;
    };

    struct TickerResponse : Response {
      std::vector<TickerElement> tickers;
    };

    struct TradesRequest {
      InstrumentT instrument_;
      TradeNumT tradeNum_;

      TradesRequest(InstrumentT instrument, TradeNumT tradeNum)
          : instrument_{std::move(instrument)}, tradeNum_{tradeNum} {}

      TradesRequest(TradeNumT tradeNum)
          : instrument_{""}, tradeNum_{std::move(tradeNum)} {}
    };

    struct TradeElement {
      std::string instrument;
      long double price;
      short side;
      TimeT timestamp;
      std::string tradeUuid;
      long double value;
      long double volume;
    };

    struct TradesResponse : Response {
      std::vector<TradeElement> trades;
    };

    struct DepthRequest {
      InstrumentT instrument_;
      DepthNumT depthNum_;

      DepthRequest(InstrumentT instrument, DepthNumT depthNum)
          : instrument_{std::move(instrument)}, depthNum_{depthNum} {}
      DepthRequest(DepthNumT depthNum) : instrument_{""}, depthNum_{depthNum} {}
    };

    struct DepthResponse : Response {
      using LongDouble = long double;
      bool isFrozen;
      std::vector<std::pair<LongDouble, LongDouble>> bids;
      std::vector<std::pair<LongDouble, LongDouble>> asks;
    };

    struct OrderTypesResponse : Response {
      std::vector<std::string> orderTypes;
    };

    struct ContractRequest {
      InstrumentT instrument_;
    };

    struct ContractResponse : Response {
      std::string instrument;
      std::string details;
      std::string pricingSource;
      std::string openInterest;
      std::string interestRate;
      std::string contractValue;
      std::string initialMarginBaseValue;
      std::string maintenanceMarginBaseValue;
      long double bitwyreIndexPrice;
      long double volume24h;
      std::string volume24hCurrency;
      std::string bitwyreIndexPriceCurrency;
    };

    struct Language {
      std::string iso6392code;
      std::string language;
    };

    struct SupportedLanguagesResponse : Response {
      std::vector<Language> languages;
    };

  } // namespace Public

  namespace Private {

    struct AccountBalanceRequest {
      InstrumentT instrument_;

      AccountBalanceRequest(InstrumentT instrument)
          : instrument_{std::move(instrument)} {}

      [[nodiscard]] auto checksum() const noexcept -> std::string {
        json j = "";
        return Utils::SHA256(json(j.dump()).dump());
      }
    };

    struct AccountBalanceElement {
      std::string asset;
      std::int64_t availableBalance;
      std::int64_t btcEquivalent;
      std::int64_t localEquivalent;
      std::int64_t lockedBalance;
      std::int64_t totalBalance;
      std::string localReference;
    };

    struct AccountBalanceResponse : Response {
      std::vector<AccountBalanceElement> balances;
    };

    struct AccountStatementRequest {
      AssetsT assets_;

      AccountStatementRequest() = default;
      AccountStatementRequest(const AssetsT& assets) : assets_{assets} {}

      [[nodiscard]] auto checksum() const noexcept -> std::string {
        if (assets_.get().empty()) {
          return Utils::SHA256(json(toString()).dump());
        }
        auto dumpTwice = json(toString()).dump();
        return Utils::SHA256(json(dumpTwice).dump());
      }

      auto toString() const -> std::string {
        json payload;
        if (assets_.get().empty()) {
          payload = "";
          return payload.dump();
        }
        payload["assets"] = assets_.get();
        return payload.dump();
      }
    };

    struct AccountStatementElement {
      long double fee;
      long double grossAmount;
      long double nettAmount;
      std::uint64_t networkConfirmation;
      std::uint64_t id;

      std::string provider;
      std::string status;
      std::string transactionId;
      std::string txId;
      std::string type;

      TimeT submitTime;
      TimeT successTime;
    };

    struct AccountStatementResponse : Response {
      std::vector<std::pair<std::string, std::vector<AccountStatementElement>>>
          deposits;
      std::vector<std::pair<std::string, std::vector<AccountStatementElement>>>
          withdrawals;
    };

    struct TxHistoryElement {
      std::uint64_t accountBalanceId;
      std::string address;
      std::string asset;
      std::string status;
      std::string notes;
      long double amount;
      long double finalBalance;
      long double fee;
      short type;
      TimeT time;
    };

    struct TransactionHistoryResponse : Response {
      std::vector<std::pair<std::string, std::vector<TxHistoryElement>>>
          deposits;
      std::vector<std::pair<std::string, std::vector<TxHistoryElement>>>
          withdrawals;
    };

    struct TransactionHistoryRequest {

      [[nodiscard]] auto checksum() const noexcept -> std::string {
        json j = "";
        return Utils::SHA256(json(j.dump()).dump());
      }

      auto toString() const -> std::string {
        return "";
      }
    };

    struct ExecutionReport : Response {
      std::string orderId;
      std::string clOrdId;
      std::string ordStatusReqId;
      std::string execId;
      std::string account;
      std::string instrument;
      std::string origcliId;

      [[warn("Not yet supported")]] std::string execInst;

      std::uint8_t execType;
      std::uint8_t ordStatus;
      std::uint8_t ordRejReason;
      std::uint8_t side;
      std::uint8_t ordType;
      std::uint8_t timeInForce;
      std::uint8_t expiry;

      long double orderQty;
      long double price;
      long double stopPx;
      long double lastQty;
      long double lastPx;
      long double lastLiquidityInd;
      long double leavesQty;
      long double cumQty;
      long double avgPx;
      long double fillPrice;
      long double value;

      bool cancelOnDisconnect;

      TimeT transactTime;
      TimeT timestamp;
      TimeT expireTime;
    };

    struct NewOrderResponse : ExecutionReport {};
    struct NewOrderRequest {
      // Only Required Fields for now
      InstrumentT instrument_;
      SideT side_;
      OrdType ordType_;
      PriceT price_;
      QtyT orderQty_;

      NewOrderRequest(InstrumentT instrument, SideT side, OrdType type,
                      PriceT price, QtyT qty)
          : instrument_{std::move(instrument)}, side_{std::move(side)},
            ordType_{std::move(type)}, price_{std::move(price)},
            orderQty_{std::move(qty)} {}

      [[nodiscard]] auto checksum() const noexcept -> std::string {
        json payload;
        payload["instrument"] = instrument_.get();
        payload["side"] = side_.get();
        payload["ordtype"] = ordType_.get();
        payload["orderqty"] = orderQty_.get();
        payload["price"] = price_.get();
        // We need to dump it three times to comply with the API expectations
        auto dumpTwice = json(payload.dump()).dump();
        return Utils::SHA256(json(std::move(dumpTwice)).dump());
      }

      auto toString() const -> std::string {
        json payload;
        payload["instrument"] = instrument_.get();
        payload["side"] = side_.get();
        payload["ordtype"] = ordType_.get();
        payload["orderqty"] = orderQty_.get();
        payload["price"] = price_.get();
        return payload.dump();
      }
    };

    struct CancelOrderRequest {
      OrderIdsT orderIds_;
      QtyT quantities_;

      CancelOrderRequest(OrderIdsT orderIds, QtyT qties)
          : orderIds_{std::move(orderIds)}, quantities_{std::move(qties)} {}

      [[nodiscard]] auto checksum() const noexcept -> std::string {
        // We need to dump it three times to comply with the API expectations
        auto dumpTwice = json(toString()).dump();
        return Utils::SHA256(json(std::move(dumpTwice)).dump());
      }

      [[nodiscard]] auto toString() const noexcept -> std::string {
        json payload;
        payload["order_ids"] = orderIds_.get();
        payload["qtys"] = quantities_.get();
        return payload.dump();
      }
    };

    struct OrderInfoResponse : Response {
      std::vector<ExecutionReport> ordersInfo;
    };

    struct OrderInfoRequest {
      OrderIdT orderId_{""};

      OrderInfoRequest() = default;

      OrderInfoRequest(OrderIdT orderId) : orderId_{std::move(orderId)} {}

      [[nodiscard]] auto checksum() const noexcept -> std::string {
        json payload = "";
        return Utils::SHA256(json(payload.dump()).dump());
      }
    };

    struct TradesHistoryElement {
      long double execPrice;
      long double execQty;
      long double execType;
      long double execValue;
      long double feePaid;
      long double feeRate;
      long double feeType;
      long double orderPrice;
      long double orderQty;
      long double orderRemaining;
      short orderType;
      short side;
      short status;

      std::string notes;
      std::string symbol;
      TimeT timestamp;
      std::string orderUuid;
      std::string userUuid;
    };

    struct TradesHistoryResponse : Response {
      std::vector<std::pair<std::string, std::vector<TradesHistoryElement>>>
          histories;
    };

    struct TradesHistoryRequest {
      // All parameters for this request are optional
      // we may define constructors that deal with each cases
      // as of now only the instrument and count can be passed to filter
      // the request
      InstrumentT instrument_{""};
      CountT count_{0};
      TimeT fromTime_{};
      TimeT toTime_{};

      TradesHistoryRequest() = default;

      TradesHistoryRequest(std::string instrument, CountT count)
          : instrument_{std::move(instrument)}, count_{count} {}

      TradesHistoryRequest(CountT count) : count_{std::move(count)} {}

      [[nodiscard]] auto checksum() const noexcept -> std::string {
        if (instrument_.get().empty() && count_.get() == 0) {
          nlohmann::ordered_json payload = "";
          return Utils::SHA256(json(toString()).dump());
        }
        auto dumpedTwice = json(toString()).dump();
        return Utils::SHA256(json(std::move(dumpedTwice)).dump());
      }

      [[nodiscard]] auto toString() const noexcept -> std::string {
        nlohmann::ordered_json payload;

        if (instrument_.get().empty() && count_.get() == 0) {
          payload = "";
          return payload.dump();
        }
        payload["instrument"] = instrument_.get();
        payload["count"] = count_.get();
        return payload.dump();
      }
    };

    struct ClosedOrdersResponse : Response {
      std::vector<std::pair<std::string, std::vector<ExecutionReport>>>
          closedOrders;
    };

    struct ClosedOrdersRequest {
      InstrumentT instrument_{""};
      TimeT from_{};
      TimeT to_{};

      ClosedOrdersRequest(InstrumentT instrument)
          : instrument_{std::move(instrument)} {}
      ClosedOrdersRequest() = default;

      [[nodiscard]] auto checksum() const noexcept -> std::string {
        if (instrument_.get().empty()) {
          json payload = "";
          return Utils::SHA256(json(toString()).dump());
        }
        auto dumpedTwice = json(toString()).dump();
        return Utils::SHA256(json(std::move(dumpedTwice)).dump());
      }

      [[nodiscard]] auto toString() const noexcept -> std::string {
        json payload;

        if (instrument_.get().empty()) {
          payload = "";
          return payload.dump();
        }
        payload["instrument"] = instrument_.get();
        return payload.dump();
      }
    };

    struct OpenOrdersResponse : Response {
      std::vector<std::pair<std::string, std::vector<ExecutionReport>>>
          openOrders;
    };

    struct OpenOrdersRequest {
      InstrumentT instrument_{""};
      TimeT from_{};
      TimeT to_{};

      OpenOrdersRequest(InstrumentT instrument)
          : instrument_{std::move(instrument)} {}
      OpenOrdersRequest() = default;

      [[nodiscard]] auto checksum() const noexcept -> std::string {
        if (instrument_.get().empty()) {
          nlohmann::ordered_json payload = "";
          return Utils::SHA256(json(toString()).dump());
        }
        auto dumpedTwice = json(toString()).dump();
        return Utils::SHA256(json(std::move(dumpedTwice)).dump());
      }

      [[nodiscard]] auto toString() const noexcept -> std::string {
        nlohmann::ordered_json payload;

        if (instrument_.get().empty()) {
          payload = "";
          return payload.dump();
        }
        payload["instrument"] = instrument_.get();
        return payload.dump();
      }
    };
  } // namespace Private

} // namespace Bitwyre::Types