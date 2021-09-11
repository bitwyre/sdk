#include "MockDispatcher.hpp"
#include "MockAsyncDispatcher.hpp"
#include "catch2/catch.hpp"
#include "details/Types.hpp"
#include "rest/public/Asset.hpp"
#include "rest/public/Contract.hpp"
#include "rest/public/CryptoAsset.hpp"
#include "rest/public/Depth.hpp"
#include "rest/public/FiatAsset.hpp"
#include "rest/public/Instrument.hpp"
#include "rest/public/Market.hpp"
#include "rest/public/OrderTypes.hpp"
#include "rest/public/Product.hpp"
#include "rest/public/SupportedLanguages.hpp"
#include "rest/public/Ticker.hpp"
#include "rest/public/Time.hpp"
#include "rest/public/Trades.hpp"
#include <type_traits>
#include <future>

using namespace Bitwyre::Rest::Public;
using namespace Bitwyre::Types;
using ::testing::Return;
using ::testing::_;
using ::testing::An;

TEST_CASE("Time request", "[rest][public][time]") {
  MockDispatcher mockDispatcher;
  json apiRes =
      R"({"statusCode": 200, "error": [], "result": {"unixtime": 1571744594571020435} })"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
      .WillOnce(Return(apiRes));

  auto rawResponse =
      mockDispatcher.dispatch(Time::uri(), CommonPublicRequest{});
  auto timeResponse = Time::processResponse(std::move(rawResponse));
<<<<<<< HEAD
  // std::cout << timeResponse.unixtime.count() << "\n";
  //std::cout << ".unixtime = " << apiRes["result"]["unixtime"].get<long long int>() << "\n";
=======
  std::cout << timeResponse.unixtime.count() << "\n";
  std::cout << ".unixtime = " << apiRes["result"]["unixtime"].get<long long int>() << "\n";
>>>>>>> d872085... getAsync<MockDispatcher> leads a SF
  REQUIRE(timeResponse.unixtime ==
          static_cast<TimeT>(apiRes["result"]["unixtime"].get<long long int>()));
  REQUIRE(timeResponse.statusCode_ == 200);
}

TEST_CASE("AsyncTime request", "[rest][public][async][time]") {
    // Arrange
    MockDispatcher mockDispatcher;
    MockAsyncDispatcher asyncDispatcher;
    json apiRes =
            R"({"statusCode": 200, "error": [], "result": {"unixtime": 1571744594571020435} })"_json;

    EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
    .WillOnce(Return(apiRes));

<<<<<<< HEAD
    EXPECT_CALL(asyncDispatcher,getAsync()).WillOnce(Return(mockDispatcher.dispatch(Time::uri(),CommonPublicRequest{})));

    auto asyncRawRes =
            asyncDispatcher.getAsync();
    auto timeResponse = Time::processResponse(std::move(asyncRawRes));
    REQUIRE(timeResponse.unixtime ==  static_cast<TimeT>(apiRes["result"]["unixtime"].get<long long int>()));
    REQUIRE(timeResponse.statusCode_ == 200);
=======
    auto rawResponse =
            mockDispatcher.dispatch(Time::uri(), CommonPublicRequest{});
    auto timeResponse = Time::processResponse(std::move(rawResponse));
    Time time1;
    auto future = time1.getAsync<MockDispatcher>();
    auto response = future.get();
 //   std::cout << response.unixtime << "\n";
    REQUIRE(response.unixtime ==  static_cast<TimeT>(apiRes["result"]["unixtime"].get<long long int>()));
    //REQUIRE( response.unixtime == apiRes["result"]["unixtime"].get<long long int>() );
  //   REQUIRE(timeResponse.statusCode_ == 200);
>>>>>>> d872085... getAsync<MockDispatcher> leads a SF
}


TEST_CASE("Market request", "[rest][public][market]") {
  MockDispatcher mockDispatcher;

  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [
        "crypto",
        "equities",
        "stablecoin",
        "commodities",
        "fixed_income",
        "carbon"
    ]
})"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
      .WillOnce(Return(apiRes));

  auto rawResponse =
      mockDispatcher.dispatch(Market::uri(), CommonPublicRequest{});
  auto marketResponse = Market::processResponse(std::move(rawResponse));

  REQUIRE(marketResponse.markets.size() >= 5);
  REQUIRE(marketResponse.markets.at(0) == "crypto");
  REQUIRE(marketResponse.statusCode_ == 200);
}

TEST_CASE("Market Asyncrequest", "[rest][public][async][market]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;

  json apiRes = R"({
      "statusCode": 200,
      "error": [],
      "result": [
          "crypto",
          "equities",
          "stablecoin",
          "commodities",
          "fixed_income",
          "carbon"
      ]
})"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
  .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync()).WillOnce(Return(mockDispatcher.dispatch(Market::uri(), CommonPublicRequest{})));
  auto asyncRawRes = asyncDispatcher.getAsync();
  auto marketResponse = Market::processResponse(std::move(asyncRawRes));
  REQUIRE(marketResponse.markets.size() >= 5);
  REQUIRE(marketResponse.markets.at(0) == "crypto");
  REQUIRE(marketResponse.statusCode_ == 200);
}

TEST_CASE("Product request", "[rest][public][product]") {
  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [
         "spot",
        "futures",
        "options",
        "swaps",
        "spreads"
    ]
})"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
      .WillOnce(Return(apiRes));

  auto rawResponse =
      mockDispatcher.dispatch(Product::uri(), CommonPublicRequest{});
  auto productResponse = Product::processResponse(std::move(rawResponse));

  REQUIRE(productResponse.products.empty() == false);
  REQUIRE(productResponse.products.at(0) == "spot");
  REQUIRE(productResponse.statusCode_ == 200);
}

TEST_CASE("Asset Request", "[rest][public][asset]") {

  MockDispatcher mockDispatcher;

  json apiRes = R"({
      "statusCode": 200,
      "error": [],
      "result": [       {
              "asset": "btc",
              "btc_equivalent": "1",
              "icon_url": "https://storage.bitwyre.com/assets/btc.png",
              "is_deposit_enabled": true,
              "is_trading_enabled": true,
              "is_withdraw_enabled": true,
              "local_equivalent": "",
              "local_reference": "",
              "max_withdrawal": "10",
              "min_withdrawal": "0.001",
              "name": "Bitcoin",
              "precision": "1e-8",
              "withdrawal_fee": "0.00000001"
          },
          {
              "asset": "eth",
              "btc_equivalent": "",
              "icon_url": "https://storage.bitwyre.com/public/images/coins/raster/ETH_500px.png",
              "is_deposit_enabled": true,
              "is_trading_enabled": true,
              "is_withdraw_enabled": true,
              "local_equivalent": "",
              "local_reference": "",
              "max_withdrawal": "10",
              "min_withdrawal": "0.001",
              "name": "Ethereum",
              "precision": "1e-9",
              "withdrawal_fee": "0.00000001"
          } ]
  })"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
      .WillOnce(Return(apiRes));

  auto rawResponse =
      mockDispatcher.dispatch(Asset::uri(), CommonPublicRequest{});
  auto response = Asset::processResponse(std::move(rawResponse));

  REQUIRE(response.assets.empty() == false);
  REQUIRE(response.assets.size() == 2);
  REQUIRE(response.assets.at(0).name == "Bitcoin");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("AsyncAsset Request", "[rest][public][async][asset]") {

  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  json apiRes = R"({
      "statusCode": 200,
      "error": [],
      "result": [       {
              "asset": "btc",
              "btc_equivalent": "1",
              "icon_url": "https://storage.bitwyre.com/assets/btc.png",
              "is_deposit_enabled": true,
              "is_trading_enabled": true,
              "is_withdraw_enabled": true,
              "local_equivalent": "",
              "local_reference": "",
              "max_withdrawal": "10",
              "min_withdrawal": "0.001",
              "name": "Bitcoin",
              "precision": "1e-8",
              "withdrawal_fee": "0.00000001"
          },
          {
              "asset": "eth",
              "btc_equivalent": "",
              "icon_url": "https://storage.bitwyre.com/public/images/coins/raster/ETH_500px.png",
              "is_deposit_enabled": true,
              "is_trading_enabled": true,
              "is_withdraw_enabled": true,
              "local_equivalent": "",
              "local_reference": "",
              "max_withdrawal": "10",
              "min_withdrawal": "0.001",
              "name": "Ethereum",
              "precision": "1e-9",
              "withdrawal_fee": "0.00000001"
          } ]
  })"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
  .WillOnce(Return(apiRes));

  EXPECT_CALL(asyncDispatcher,getAsync()).WillOnce(Return(mockDispatcher.dispatch(Asset::uri(),CommonPublicRequest{})));
  auto asyncRawRes = asyncDispatcher.getAsync();
  auto assetResponse = Asset::processResponse(std::move(asyncRawRes));

  REQUIRE(assetResponse.assets.empty() == false);
  REQUIRE(assetResponse.assets.size() == 2);
  REQUIRE(assetResponse.assets.at(0).name == "Bitcoin");
  REQUIRE(assetResponse.statusCode_ == 200);
}

TEST_CASE("Crypto Asset Request", "[rest][public][cryptoasset]") {
  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [       {
            "asset": "btc",
            "btc_equivalent": "1",
            "icon_url": "https://storage.bitwyre.com/assets/btc.png",
            "is_deposit_enabled": true,
            "is_trading_enabled": true,
            "is_withdraw_enabled": true,
            "local_equivalent": "",
            "local_reference": "",
            "max_withdrawal": "10",
            "min_withdrawal": "0.001",
            "name": "Bitcoin",
            "precision": "1e-8",
            "withdrawal_fee": "0.00000001"
        },
        {
            "asset": "eth",
            "btc_equivalent": "",
            "icon_url": "https://storage.bitwyre.com/public/images/coins/raster/ETH_500px.png",
            "is_deposit_enabled": true,
            "is_trading_enabled": true,
            "is_withdraw_enabled": true,
            "local_equivalent": "",
            "local_reference": "",
            "max_withdrawal": "10",
            "min_withdrawal": "0.001",
            "name": "Ethereum",
            "precision": "1e-9",
            "withdrawal_fee": "0.00000001"
        } ]
})"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
      .WillOnce(Return(apiRes));

  auto rawResponse =
      mockDispatcher.dispatch(CryptoAsset::uri(), CommonPublicRequest{});
  auto response = CryptoAsset::processResponse(std::move(rawResponse));

  REQUIRE(response.assets.empty() == false);
  REQUIRE(response.assets.size() == 2);
  REQUIRE(response.assets.at(0).name == "Bitcoin");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Crypto AsyncAsset Request", "[rest][public][async][cryptoasset]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;

  json apiRes = R"({
      "statusCode": 200,
      "error": [],
      "result": [       {
              "asset": "btc",
              "btc_equivalent": "1",
              "icon_url": "https://storage.bitwyre.com/assets/btc.png",
              "is_deposit_enabled": true,
              "is_trading_enabled": true,
              "is_withdraw_enabled": true,
              "local_equivalent": "",
              "local_reference": "",
              "max_withdrawal": "10",
              "min_withdrawal": "0.001",
              "name": "Bitcoin",
              "precision": "1e-8",
              "withdrawal_fee": "0.00000001"
          },
          {
              "asset": "eth",
              "btc_equivalent": "",
              "icon_url": "https://storage.bitwyre.com/public/images/coins/raster/ETH_500px.png",
              "is_deposit_enabled": true,
              "is_trading_enabled": true,
              "is_withdraw_enabled": true,
              "local_equivalent": "",
              "local_reference": "",
              "max_withdrawal": "10",
              "min_withdrawal": "0.001",
              "name": "Ethereum",
              "precision": "1e-9",
              "withdrawal_fee": "0.00000001"
          } ]
  })"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
  .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync()).WillOnce(Return(mockDispatcher.dispatch(CryptoAsset::uri(), CommonPublicRequest{})));
  auto asyncRawRes = asyncDispatcher.getAsync();
  auto crytoassetResponse = CryptoAsset::processResponse(std::move(asyncRawRes));

  REQUIRE(crytoassetResponse.assets.empty() == false);
  REQUIRE(crytoassetResponse.assets.size() == 2);
  REQUIRE(crytoassetResponse.assets.at(0).name == "Bitcoin");
  REQUIRE(crytoassetResponse.statusCode_ == 200);
}


TEST_CASE("Fiat Asset Request", "[rest][public][cryptoasset]") {

  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [        {
            "asset": "idr",
            "btc_equivalent": "",
            "icon_url": "https://storage.bitwyre.com/public/images/coins/raster/IDR.png",
            "is_deposit_enabled": true,
            "is_trading_enabled": true,
            "is_withdraw_enabled": true,
            "local_equivalent": "",
            "local_reference": "",
            "max_withdrawal": "100000000",
            "min_withdrawal": "100000",
            "name": "Indonesian Rupiah",
            "precision": "1",
            "withdrawal_fee": "0"
        }
]
})"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
      .WillOnce(Return(apiRes));

  auto rawResponse =
      mockDispatcher.dispatch(FiatAsset::uri(), CommonPublicRequest{});
  auto response = FiatAsset::processResponse(std::move(rawResponse));

  REQUIRE(response.assets.empty() == false);
  REQUIRE(response.assets.size() == 1);
  REQUIRE(response.assets.at(0).name == "Indonesian Rupiah");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Fiat Asset AsyncRequest", "[rest][public][async]fiatasset]") {

  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  json apiRes = R"({
      "statusCode": 200,
      "error": [],
      "result": [        {
              "asset": "idr",
              "btc_equivalent": "",
              "icon_url": "https://storage.bitwyre.com/public/images/coins/raster/IDR.png",
              "is_deposit_enabled": true,
              "is_trading_enabled": true,
              "is_withdraw_enabled": true,
              "local_equivalent": "",
              "local_reference": "",
              "max_withdrawal": "100000000",
              "min_withdrawal": "100000",
              "name": "Indonesian Rupiah",
              "precision": "1",
              "withdrawal_fee": "0"
          }
  ]
  })"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
  .WillOnce(Return(apiRes));

  EXPECT_CALL(asyncDispatcher, getAsync()).WillOnce(Return(mockDispatcher.dispatch(FiatAsset::uri(), CommonPublicRequest{})));

  auto rawResponse =
          asyncDispatcher.getAsync();
  auto response = FiatAsset::processResponse(std::move(rawResponse));

  REQUIRE(response.assets.empty() == false);
  REQUIRE(response.assets.size() == 1);
  REQUIRE(response.assets.at(0).name == "Indonesian Rupiah");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Instrument Request", "[rest][public][instrument]") {
  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [{"instrument": "btc_idr_spot", "symbol" : "BTC/IDR"},
              {"instrument": "bch_idr_spot", "symbol": "BCH/IDR"}] }
  )"_json;

  InstrumentRequest instrumentRequest{
      MarketT("spot"), ProductT("myProduct"), CountryT("mycountry")};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<InstrumentRequest>()))
      .WillOnce(Return(apiRes));

  auto rawResponse =
      mockDispatcher.dispatch(Instrument::uri(), instrumentRequest);

  auto response = Instrument::processResponse(std::move(rawResponse));

  REQUIRE(response.instruments.size() == 2);
  REQUIRE(response.instruments.at(0).instrument == "btc_idr_spot");
  REQUIRE(response.statusCode_ == 200);
}
TEST_CASE("Instrument AsyncRequest", "[rest][public][async][instrument]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [{"instrument": "btc_idr_spot", "symbol" : "BTC/IDR"},
              {"instrument": "bch_idr_spot", "symbol": "BCH/IDR"}] }
  )"_json;

  InstrumentRequest instrumentRequest{
      MarketT("spot"), ProductT("myProduct"), CountryT("mycountry")};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<InstrumentRequest>()))
      .WillOnce(Return(apiRes));
  
  EXPECT_CALL(asyncDispatcher, getAsync(An<InstrumentRequest>()))
  .WillOnce(Return(mockDispatcher.dispatch(Instrument::uri(), instrumentRequest)));
  auto asyncRawRes = asyncDispatcher.getAsync(instrumentRequest);

  auto response = Instrument::processResponse(std::move(asyncRawRes));

  REQUIRE(response.instruments.size() == 2);
  REQUIRE(response.instruments.at(0).instrument == "btc_idr_spot");
  REQUIRE(response.statusCode_ == 200);
}



TEST_CASE("Ticker Request", "[rest][public][ticker]") {
  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [{
            "instrument": "btc_idr_spot",
            "asset_base": "btc",
            "asset_quote": "idr",
            "high": "126989000",
            "low": "115201000",
            "percent_change": "-2.123",
            "volume_base": "611.66499447",
            "volume_quote": "7434324.9431",
            "last": "124783000",
            "best_bid": "124761000",
            "best_ask": "124777000",
            "timestamp": 1571744594571020435,
            "market": "crypto",
            "is_frozen": false
        }] })"_json;

  TickerRequest tickerRequest{InstrumentT("btc_idr_spot")};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<TickerRequest>()))
      .WillOnce(Return(apiRes));

  auto rawResponse = mockDispatcher.dispatch(Ticker::uri(), tickerRequest);

  auto response = Ticker::processResponse(std::move(rawResponse));

  REQUIRE(response.tickers.size() == 1);
  REQUIRE(response.tickers.at(0).instrument == "btc_idr_spot");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Ticker AsyncRequest", "[rest][public][async][ticker]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [{
            "instrument": "btc_idr_spot",
            "asset_base": "btc",
            "asset_quote": "idr",
            "high": "126989000",
            "low": "115201000",
            "percent_change": "-2.123",
            "volume_base": "611.66499447",
            "volume_quote": "7434324.9431",
            "last": "124783000",
            "best_bid": "124761000",
            "best_ask": "124777000",
            "timestamp": 1571744594571020435,
            "market": "crypto",
            "is_frozen": false
        }] })"_json;

  TickerRequest tickerRequest{InstrumentT("btc_idr_spot")};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<TickerRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync(An<TickerRequest>()))
      .WillOnce(Return(mockDispatcher.dispatch(Ticker::uri(), tickerRequest)));
  auto asyncRawRes= asyncDispatcher.getAsync(tickerRequest);

  auto response = Ticker::processResponse(std::move(asyncRawRes));

  REQUIRE(response.tickers.size() == 1);
  REQUIRE(response.tickers.at(0).instrument == "btc_idr_spot");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Ticker Request with no params", "[rest][public][ticker]") {
  MockDispatcher mockDispatcher;
//  MockAsyncDispatcher asyncDispatcher;

  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
            "instrument": "btc_idr_spot",
            "asset_base": "btc",
            "asset_quote": "idr",
            "high": "126989000",
            "low": "115201000",
            "percent_change": "-2.123",
            "volume_base": "611.66499447",
            "volume_quote": "7434324.9431",
            "last": "124783000",
            "best_bid": "124761000",
            "best_ask": "124777000",
            "timestamp": 1571744594571020435,
            "market": "crypto",
            "is_frozen": false
        } })"_json;

  TickerRequest tickerRequest{};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<TickerRequest>()))
      .WillOnce(Return(apiRes));

  auto rawResponse = mockDispatcher.dispatch(Ticker::uri(), tickerRequest);

  auto response = Ticker::processResponse(std::move(rawResponse));

  REQUIRE(response.tickers.size() == 1);
  REQUIRE(response.tickers.at(0).instrument == "btc_idr_spot");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Ticker AsyncRequest with no params", "[rest][public][async][ticker]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;

  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
            "instrument": "btc_idr_spot",
            "asset_base": "btc",
            "asset_quote": "idr",
            "high": "126989000",
            "low": "115201000",
            "percent_change": "-2.123",
            "volume_base": "611.66499447",
            "volume_quote": "7434324.9431",
            "last": "124783000",
            "best_bid": "124761000",
            "best_ask": "124777000",
            "timestamp": 1571744594571020435,
            "market": "crypto",
            "is_frozen": false
        } })"_json;

  //TickerRequest tickerRequest{};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<TickerRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync()).WillOnce(Return(mockDispatcher.dispatch(Ticker::uri(), TickerRequest{})));
  auto asyncRawRes = asyncDispatcher.getAsync();
  auto response = Ticker::processResponse(std::move(asyncRawRes));

  REQUIRE(response.tickers.size() == 1);
  REQUIRE(response.tickers.at(0).instrument == "btc_idr_spot");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Trades Request", "[rest][public][trades]") {
  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [
       {
            "instrument": "btc_usd_spot",
            "price": "70000.0",
            "side": 1,
            "timestamp": 1617701262147203562,
            "trade_uuid": "7d0cec66-f130-4fc6-b314-622d394ccec2",
            "value": "4900.0",
            "volume": "0.07"
        },
        {
            "instrument": "btc_usd_spot",
            "price": "70000.0",
            "side": 2,
            "timestamp": 1617701262147203562,
            "trade_uuid": "7d0cec66-f130-4fc6-b314-622d394ccec2",
            "value": "4900.0",
            "volume": "0.07"
        }
]})"_json;

  TradesRequest tradesRequest{InstrumentT("btc_usd_spot"), TradeNumT(2)};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<TradesRequest>()))
      .WillOnce(Return(apiRes));

  auto rawResponse = mockDispatcher.dispatch(Trades::uri(), tradesRequest);

  auto response = Trades::processResponse(std::move(rawResponse));

  REQUIRE(response.trades.size() == 2);
  REQUIRE(response.trades.at(0).instrument == "btc_usd_spot");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Trades AsyncRequest", "[rest][public][async][trades]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;

  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [
       {
            "instrument": "btc_usd_spot",
            "price": "70000.0",
            "side": 1,
            "timestamp": 1617701262147203562,
            "trade_uuid": "7d0cec66-f130-4fc6-b314-622d394ccec2",
            "value": "4900.0",
            "volume": "0.07"
        },
        {
            "instrument": "btc_usd_spot",
            "price": "70000.0",
            "side": 2,
            "timestamp": 1617701262147203562,
            "trade_uuid": "7d0cec66-f130-4fc6-b314-622d394ccec2",
            "value": "4900.0",
            "volume": "0.07"
        }
]})"_json;

  TradesRequest tradesRequest{InstrumentT("btc_usd_spot"), TradeNumT(2)};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<TradesRequest>()))
      .WillOnce(Return(apiRes));

  EXPECT_CALL(asyncDispatcher, getAsync(An<TradesRequest>()))
  .WillOnce(Return(mockDispatcher.dispatch(Trades::uri(), tradesRequest)));
  auto asyncRawRes = asyncDispatcher.getAsync(tradesRequest);
  auto response = Trades::processResponse(std::move(asyncRawRes));

  REQUIRE(response.trades.size() == 2);
  REQUIRE(response.trades.at(0).instrument == "btc_usd_spot");
  REQUIRE(response.statusCode_ == 200);
}

// @TODO add trade request with tradeNum param only

TEST_CASE("OrderTypes Request", "[rest][public][product]") {
  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [ "Market", "Limit", "Stop", "Stop Limit" ]
})"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
      .WillOnce(Return(apiRes));
  auto rawResponse =
      mockDispatcher.dispatch(OrderTypes::uri(), CommonPublicRequest{});

  OrderTypesResponse response =
      OrderTypes::processResponse(std::move(rawResponse));

  REQUIRE(response.orderTypes.size() == 4);
  REQUIRE(response.orderTypes.at(0) == "Market");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("OrderTypes AsyncRequest", "[rest][public][async][product]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;

  json apiRes = R"({
      "statusCode": 200,
      "error": [],
      "result": [ "Market", "Limit", "Stop", "Stop Limit" ]
  })"_json;

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CommonPublicRequest>()))
  .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync()).WillOnce(Return(mockDispatcher.dispatch(OrderTypes::uri(), CommonPublicRequest{})));
  auto asyncRawRes = asyncDispatcher.getAsync();
  auto response = OrderTypes::processResponse(std::move(asyncRawRes));

  REQUIRE(response.orderTypes.size() == 4);
  REQUIRE(response.orderTypes.at(0) == "Market");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Depth Request", "[rest][public][depth]") {
  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
    "bids": [
      ["124112000", "0.1815405"],
      ["124110000", "0.47319750"]
    ],
    "asks": [
      ["124130000", "0.03701609"],
      ["124251000", "0.03223585"]
    ],
    "is_frozen": 0
  }
})"_json;

  DepthRequest depthRequest{InstrumentT("btc_usd_spot"), DepthNumT(2)};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<DepthRequest>()))
      .WillOnce(Return(apiRes));
  auto rawResponse = mockDispatcher.dispatch(Depth::uri(), depthRequest);

  auto response = Depth::processResponse(std::move(rawResponse));

  REQUIRE(response.bids.size() == 2);
  REQUIRE(response.bids.at(0).first == 124112000);
  REQUIRE(response.bids.at(0).second == 0.1815405);
  REQUIRE(response.asks.size() == 2);
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Depth AsyncRequest", "[rest][public][async][depth]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;

  json apiRes = R"({
      "statusCode": 200,
      "error": [],
      "result": {
      "bids": [
        ["124112000", "0.1815405"],
        ["124110000", "0.47319750"]
      ],
      "asks": [
        ["124130000", "0.03701609"],
        ["124251000", "0.03223585"]
      ],
      "is_frozen": 0
    }
  })"_json;

  DepthRequest depthRequest{InstrumentT("btc_usd_spot"), DepthNumT(2)};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<DepthRequest>())).WillOnce(Return(apiRes));

  EXPECT_CALL(asyncDispatcher, getAsync(An<DepthRequest>()))
  .WillOnce(Return(mockDispatcher.dispatch(Depth::uri(), depthRequest)));

  auto asyncRawRes= asyncDispatcher.getAsync(depthRequest);

  auto response = Depth::processResponse(std::move(asyncRawRes));
  REQUIRE(response.bids.size() == 2);
  REQUIRE(response.bids.at(0).first == 124112000);
  REQUIRE(response.bids.at(0).second == 0.1815405);
  REQUIRE(response.asks.size() == 2);
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Contract Request", "[rest][public][contract]") {
  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
        "instrument": "btcusdtx_usdt_200607F1000000",
        "details": "contract for cash delivery of BTC/USD index settled for July 6th, 2020 for the strike price of 10,000 USD",
        "pricing_source": "CME Bitcoin Real Time Index",
        "bitwyre_index_price": "11500.00",
        "bitwyre_index_price_currency": "USD",
        "24h_volume": "800,000,000.00",
        "24h_volume_currency": "USD",
        "open_interest": "600,000,000.00",
        "interest_rate": "0.001%",
        "contract_value": "1 USD",
        "initial_margin_base_value": "1%",
        "maintenance_margin_base_value": "0.5%"
    }
})"_json;

  ContractRequest contractRequest{InstrumentT{"btcusdtx_usdt_200607F1000000"}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<ContractRequest>()))
      .WillOnce(Return(apiRes));
  auto rawResponse = mockDispatcher.dispatch(Contract::uri(), contractRequest);

  auto response = Contract::processResponse(std::move(rawResponse));

  REQUIRE(response.contractValue == "1 USD");
  REQUIRE(response.instrument == "btcusdtx_usdt_200607F1000000");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Contract AsyncRequest", "[rest][public][async][contract]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  json apiRes = R"({
      "statusCode": 200,
      "error": [],
      "result": {
          "instrument": "btcusdtx_usdt_200607F1000000",
          "details": "contract for cash delivery of BTC/USD index settled for July 6th, 2020 for the strike price of 10,000 USD",
          "pricing_source": "CME Bitcoin Real Time Index",
          "bitwyre_index_price": "11500.00",
          "bitwyre_index_price_currency": "USD",
          "24h_volume": "800,000,000.00",
          "24h_volume_currency": "USD",
          "open_interest": "600,000,000.00",
          "interest_rate": "0.001%",
          "contract_value": "1 USD",
          "initial_margin_base_value": "1%",
          "maintenance_margin_base_value": "0.5%"
      }
  })"_json;

  ContractRequest contractRequest{InstrumentT{"btcusdtx_usdt_200607F1000000"}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<ContractRequest>()))
  .WillOnce(Return(apiRes));

  EXPECT_CALL(asyncDispatcher, getAsync(An<ContractRequest>())).WillOnce(Return(mockDispatcher.dispatch(Contract::uri(), contractRequest)));
  auto asyncRawRes = asyncDispatcher.getAsync(contractRequest);

  auto response = Contract::processResponse(std::move(asyncRawRes));

  REQUIRE(response.contractValue == "1 USD");
  REQUIRE(response.instrument == "btcusdtx_usdt_200607F1000000");
  REQUIRE(response.statusCode_ == 200);
}

//TEST_CASE("Supported languages Request", "[rest][public][supportedlanguage]") {
//  auto supportedLanguages = SupportedLanguages::get();
//}

//TEST_CASE("Supported languages AsyncRequest", "[rest][public][supportedlanguage]") {
//  auto supportedLanguages = SupportedLanguages::getAsyncLanguage();
//}