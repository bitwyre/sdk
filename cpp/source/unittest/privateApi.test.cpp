#include "MockDispatcher.hpp"
#include "MockAsyncDispatcher.hpp"
#include "catch2/catch.hpp"
#include "details/Utils.hpp"
#include "rest/private/AccountBalance.hpp"
#include "rest/private/AccountStatement.hpp"
#include "rest/private/CancelOrder.hpp"
#include "rest/private/ClosedOrders.hpp"
#include "rest/private/NewOrder.hpp"
#include "rest/private/OpenOrders.hpp"
#include "rest/private/OrderInfo.hpp"
#include "rest/private/TradesHistory.hpp"
#include "rest/private/TransactionHistory.hpp"

using namespace Bitwyre::Rest::Private;
using namespace Bitwyre::Types;
using ::testing::Return;
using ::testing::_;
using ::testing::An;

TEST_CASE("Account balance", "[rest][private][accountbalance]") {

  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [
        {
            "asset": "btc",
            "available_balance": 10000.3434,
            "btc_equivalent": 1,
            "local_equivalent": 0,
            "local_reference": "",
            "locked_balance": 0,
            "total_balance": 0
        },
        {
            "asset": "eth",
            "available_balance": 0,
            "btc_equivalent": 0,
            "local_equivalent": 0,
            "local_reference": "",
            "locked_balance": 0,
            "total_balance": 0
        }
  ]
})"_json;

  AccountBalanceRequest accountBalanceRequest{InstrumentT("btc_usd_spot")};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<AccountBalanceRequest>()))
      .WillOnce(Return(apiRes));
  auto rawResponse =
      mockDispatcher.dispatch(AccountBalance::uri(), accountBalanceRequest);

  auto response = AccountBalance::processResponse(std::move(rawResponse));

  REQUIRE(response.balances.size() == 2);
  REQUIRE(response.balances.at(0).availableBalance == 10000);
  REQUIRE(response.balances.at(0).asset == "btc");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Async Account balance", "[rest][private][async][accountbalance]") {

  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [
        {
            "asset": "btc",
            "available_balance": 10000.3434,
            "btc_equivalent": 1,
            "local_equivalent": 0,
            "local_reference": "",
            "locked_balance": 0,
            "total_balance": 0
        },
        {
            "asset": "eth",
            "available_balance": 0,
            "btc_equivalent": 0,
            "local_equivalent": 0,
            "local_reference": "",
            "locked_balance": 0,
            "total_balance": 0
        }
  ]
})"_json;

  AccountBalanceRequest accountBalanceRequest{InstrumentT("btc_usd_spot")};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<AccountBalanceRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync(An<AccountBalanceRequest>()))
  .WillOnce(Return(mockDispatcher.dispatch(AccountBalance::uri(),accountBalanceRequest)));

  auto asyncRawRes = asyncDispatcher.getAsync(accountBalanceRequest);
  auto response = AccountBalance::processResponse(std::move(asyncRawRes));
//  auto rawResponse =
//      mockDispatcher.dispatch(AccountBalance::uri(), accountBalanceRequest);
//
//  auto response = AccountBalance::processResponse(std::move(rawResponse));

  REQUIRE(response.balances.size() == 2);
  REQUIRE(response.balances.at(0).availableBalance == 10000);
  REQUIRE(response.balances.at(0).asset == "btc");
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Account statement without assets param",
          "[rest][private][accountstatement]") {

  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
        "deposit": {
            "brl": [],
            "btc": [
                {
                    "fee": 5e-5,
                    "gross_amount": 0.01,
                    "id": 4,
                    "nett_amount": 0.00995,
                    "network_confirmation": 0,
                    "provider": "duitku",
                    "status": "pending",
                    "submit_time": 1571747594573320135,
                    "success_time": 0,
                    "transaction_id": "26a13a32-2e11-472a-84cc-242d765a88dg",
                    "tx_id": "26a13a32-2e11-472a-84cc-242d765a88dg",
                    "type": "crypto"
                }
            ],
            "eth": [],
            "idr": [
                {
                    "centralized_confirmation": 0,
                    "fee": 1000.0,
                    "gross_amount": 5000.0,
                    "id": 5,
                    "nett_amount": 4000.0,
                    "provider": "duitku",
                    "status": "pending",
                    "submit_time": 1571747594573320135,
                    "success_time": 0,
                    "transaction_id": "26a13a32-2e11-472a-84cc-242d765a88dg",
                    "type": "fiat"
                }
            ],
            "mxn": [],
            "usd": [],
            "usdt": [],
            "xmr": [],
            "zec": []
        },
        "withdrawal": {
            "brl": [],
            "btc": [
                {
                    "fee": 5e-5,
                    "gross_amount": 0.01,
                    "id": 6,
                    "nett_amount": 0.00995,
                    "network_confirmation": 0,
                    "provider": "duitku",
                    "status": "pending",
                    "submit_time": 1571747594573320135,
                    "success_time": 0,
                    "transaction_id": "26a13a32-2e11-472a-84cc-242d765a88dj",
                    "tx_id": "26a13a32-2e11-472a-84cc-242d765a88dj",
                    "type": "crypto"
                }
             ],
            "eth": [],
            "idr": [
                {
                    "centralized_confirmation": 0,
                    "fee": 1000.0,
                    "gross_amount": 10000.0,
                    "id": 1,
                    "nett_amount": 9000.0,
                    "provider": "duitku",
                    "status": "pending",
                    "submit_time": 1571747594573320135,
                    "success_time": 0,
                    "transaction_id": "26a13a32-2e11-472a-84cc-242d765a88de",
                    "type": "fiat"
                },
                {
                    "centralized_confirmation": 0,
                    "fee": 1000.0,
                    "gross_amount": 5000.0,
                    "id": 3,
                    "nett_amount": 4000.0,
                    "provider": "duitku",
                    "status": "pending",
                    "submit_time": 1571747594573320135,
                    "success_time": 0,
                    "transaction_id": "26a13a32-2e11-472a-84cc-242d765a88df",
                    "type": "fiat"
                }
            ],
            "mxn": [],
            "usd": [],
            "usdt": [],
            "xmr": [],
            "zec": []
        }
    }
})"_json;

  AccountStatementRequest accountStatementRequest{AssetsT{{"btc", "usd"}}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<AccountStatementRequest>()))
      .WillOnce(Return(apiRes));
  auto rawResponse =
      mockDispatcher.dispatch(AccountStatement::uri(), accountStatementRequest);

  auto response = AccountStatement::processResponse(std::move(rawResponse));

  REQUIRE(response.deposits.size() == 9);
  REQUIRE(response.withdrawals.size() == 9);
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Async Account statement without assets param",
          "[rest][private][async][accountstatement]") {

  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
        "deposit": {
            "brl": [],
            "btc": [
                {
                    "fee": 5e-5,
                    "gross_amount": 0.01,
                    "id": 4,
                    "nett_amount": 0.00995,
                    "network_confirmation": 0,
                    "provider": "duitku",
                    "status": "pending",
                    "submit_time": 1571747594573320135,
                    "success_time": 0,
                    "transaction_id": "26a13a32-2e11-472a-84cc-242d765a88dg",
                    "tx_id": "26a13a32-2e11-472a-84cc-242d765a88dg",
                    "type": "crypto"
                }
            ],
            "eth": [],
            "idr": [
                {
                    "centralized_confirmation": 0,
                    "fee": 1000.0,
                    "gross_amount": 5000.0,
                    "id": 5,
                    "nett_amount": 4000.0,
                    "provider": "duitku",
                    "status": "pending",
                    "submit_time": 1571747594573320135,
                    "success_time": 0,
                    "transaction_id": "26a13a32-2e11-472a-84cc-242d765a88dg",
                    "type": "fiat"
                }
            ],
            "mxn": [],
            "usd": [],
            "usdt": [],
            "xmr": [],
            "zec": []
        },
        "withdrawal": {
            "brl": [],
            "btc": [
                {
                    "fee": 5e-5,
                    "gross_amount": 0.01,
                    "id": 6,
                    "nett_amount": 0.00995,
                    "network_confirmation": 0,
                    "provider": "duitku",
                    "status": "pending",
                    "submit_time": 1571747594573320135,
                    "success_time": 0,
                    "transaction_id": "26a13a32-2e11-472a-84cc-242d765a88dj",
                    "tx_id": "26a13a32-2e11-472a-84cc-242d765a88dj",
                    "type": "crypto"
                }
             ],
            "eth": [],
            "idr": [
                {
                    "centralized_confirmation": 0,
                    "fee": 1000.0,
                    "gross_amount": 10000.0,
                    "id": 1,
                    "nett_amount": 9000.0,
                    "provider": "duitku",
                    "status": "pending",
                    "submit_time": 1571747594573320135,
                    "success_time": 0,
                    "transaction_id": "26a13a32-2e11-472a-84cc-242d765a88de",
                    "type": "fiat"
                },
                {
                    "centralized_confirmation": 0,
                    "fee": 1000.0,
                    "gross_amount": 5000.0,
                    "id": 3,
                    "nett_amount": 4000.0,
                    "provider": "duitku",
                    "status": "pending",
                    "submit_time": 1571747594573320135,
                    "success_time": 0,
                    "transaction_id": "26a13a32-2e11-472a-84cc-242d765a88df",
                    "type": "fiat"
                }
            ],
            "mxn": [],
            "usd": [],
            "usdt": [],
            "xmr": [],
            "zec": []
        }
    }
})"_json;

  AccountStatementRequest accountStatementRequest{AssetsT{{"btc", "usd"}}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<AccountStatementRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync(An<AccountStatementRequest>()))
  .WillOnce(Return(mockDispatcher.dispatch(AccountStatement::uri(), accountStatementRequest)));

  auto asyncRawRes = asyncDispatcher.getAsync(accountStatementRequest);

  auto response = AccountStatement::processResponse(std::move(asyncRawRes));

  REQUIRE(response.deposits.size() == 9);
  REQUIRE(response.withdrawals.size() == 9);
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Cancel order", "[rest][private][cancelorder]") {

  MockDispatcher mockDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
        "AvgPx": "0",
        "LastLiquidityInd": "0",
        "LastPx": "0",
        "LastQty": "0",
        "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
        "cancelondisconnect": 0,
        "clorderid": "",
        "cumqty": "0",
        "execid": "",
        "exectype": 5,
        "expiry": 0,
        "fill_price": "0",
        "instrument": "btc_usdt_spot",
        "leavesqty": "10",
        "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
        "orderqty": "10",
        "ordrejreason": "",
        "ordstatus": 6,
        "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc9",
        "ordtype": 3,
        "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
        "price": "10.0",
        "side": 1,
        "stoppx": "0",
        "time_in_force": 0,
        "timestamp": 123123132123,
        "transacttime": 0,
        "value": "100.0"
    }
})"_json;

  CancelOrderRequest cancelOrderRequest{
      OrderIdsT{{"9be73240-c3e4-4d0d-a8d7-57d9a6d798e1"}}, QtyT{{1}}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CancelOrderRequest>()))
      .WillOnce(Return(apiRes));
  auto rawResponse =
      mockDispatcher.dispatch(CancelOrder::uri(), cancelOrderRequest);

  auto response = CancelOrder::processResponse(std::move(rawResponse));
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Async Cancel order", "[rest][private][async][cancelorder]") {

  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  json apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
        "AvgPx": "0",
        "LastLiquidityInd": "0",
        "LastPx": "0",
        "LastQty": "0",
        "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
        "cancelondisconnect": 0,
        "clorderid": "",
        "cumqty": "0",
        "execid": "",
        "exectype": 5,
        "expiry": 0,
        "fill_price": "0",
        "instrument": "btc_usdt_spot",
        "leavesqty": "10",
        "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
        "orderqty": "10",
        "ordrejreason": "",
        "ordstatus": 6,
        "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc9",
        "ordtype": 3,
        "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
        "price": "10.0",
        "side": 1,
        "stoppx": "0",
        "time_in_force": 0,
        "timestamp": 123123132123,
        "transacttime": 0,
        "value": "100.0"
    }
})"_json;

  CancelOrderRequest cancelOrderRequest{
      OrderIdsT{{"9be73240-c3e4-4d0d-a8d7-57d9a6d798e1"}}, QtyT{{1}}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<CancelOrderRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, delAsync(An<CancelOrderRequest>()))
  .WillOnce(Return(mockDispatcher.dispatch(CancelOrder::uri(), cancelOrderRequest)));

  auto asyncRawRes = asyncDispatcher.delAsync(cancelOrderRequest);

  auto response = CancelOrder::processResponse(std::move(asyncRawRes));
  REQUIRE(response.statusCode_ == 200);
}

TEST_CASE("Closed orders request /all", "[rest][private][closedorders]") {
  auto resApi = R"("")"_json;
}

TEST_CASE("Closed orders request", "[rest][private][closedorders]") {
  MockDispatcher mockDispatcher;
  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
    "btc_usd_spot": [
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 123123132123,
            "transacttime": 0,
            "value": "100.0"
        },
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 2345676543246,
            "transacttime": 0,
            "value": "100.0"
        }
    ]
    } })"_json;

  ClosedOrdersRequest request{InstrumentT{"btc_usd_spot"}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<ClosedOrdersRequest>()))
      .WillOnce(Return(apiRes));
  auto rawResponse = mockDispatcher.dispatch(ClosedOrders::uri(), request);
  auto response = ClosedOrders::processResponse(std::move(rawResponse));

  REQUIRE(response.closedOrders.size() == 1);
  REQUIRE(response.closedOrders.at(0).second.size() == 2);
  REQUIRE(response.closedOrders.at(0).first == "btc_usd_spot");
}


TEST_CASE("Closed orders async request", "[rest][private][async][closedorders]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
    "btc_usd_spot": [
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 123123132123,
            "transacttime": 0,
            "value": "100.0"
        },
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 2345676543246,
            "transacttime": 0,
            "value": "100.0"
        }
    ]
    } })"_json;

  ClosedOrdersRequest request{InstrumentT{"btc_usd_spot"}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<ClosedOrdersRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync(An<ClosedOrdersRequest>()))
  .WillOnce(Return(mockDispatcher.dispatch(ClosedOrders::uri(), request)));
  auto asyncRawRes = asyncDispatcher.getAsync(request);
  auto response = ClosedOrders::processResponse(std::move(asyncRawRes));

  REQUIRE(response.closedOrders.size() == 1);
  REQUIRE(response.closedOrders.at(0).second.size() == 2);
  REQUIRE(response.closedOrders.at(0).first == "btc_usd_spot");
}

TEST_CASE("Open orders request", "[rest][private][closedorders]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
    "btc_usd_spot": [
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 123123132123,
            "transacttime": 0,
            "value": "100.0"
        },
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 2345676543246,
            "transacttime": 0,
            "value": "100.0"
        }
    ]
    } })"_json;

  OpenOrdersRequest request{InstrumentT{"btc_usd_spot"}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<OpenOrdersRequest>()))
      .WillOnce(Return(apiRes));
  auto rawResponse = mockDispatcher.dispatch(OpenOrders::uri(), request);
  auto response = OpenOrders::processResponse(std::move(rawResponse));

  REQUIRE(response.openOrders.size() == 1);
  REQUIRE(response.openOrders.at(0).second.size() == 2);
  REQUIRE(response.openOrders.at(0).first == "btc_usd_spot");
}

TEST_CASE("Open orders async request", "[rest][private][async][openorders]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 123123132123,
            "transacttime": 0,
            "value": "100.0"
        },
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 2345676543246,
            "transacttime": 0,
            "value": "100.0"
        }
    ]
})"_json;

  OrderInfoRequest request{OrderIdT{"9be73240-c3e4-4d0d-a8d7-57d9a6d798e1"}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<OrderInfoRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync(An<OpenOrdersRequest>()))
  .WillOnce(Return(mockDispatcher.dispatch(OpenOrders::uri(), request)));
  auto asyncRawRes = asyncDispatcher.getAsync(request);
  auto response = OpenOrders::processResponse(std::move(asyncRawRes));
  REQUIRE(response.openOrders.size() == 1);
  REQUIRE(response.openOrders.at(0).second.size() == 2);
  REQUIRE(response.openOrders.at(0).first == "btc_usd_spot");
}


TEST_CASE("Async Order info", "[rest][private][async][orderinfo]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 123123132123,
            "transacttime": 0,
            "value": "100.0"
        },
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 2345676543246,
            "transacttime": 0,
            "value": "100.0"
        }
    ]
})"_json;

  OrderInfoRequest request{OrderIdT{"9be73240-c3e4-4d0d-a8d7-57d9a6d798e1"}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<OrderInfoRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync())
     .WillOnce(Return(mockDispatcher.dispatch(OrderInfo::uri(), request)));

  auto asyncRawRes = asyncDispatcher.getAsync();
  auto response = OrderInfo::processResponse(std::move(asyncRawRes));

  REQUIRE(response.ordersInfo.size() == 2);
  REQUIRE(response.ordersInfo.at(0).instrument == "btc_usd_spot");
}


TEST_CASE("Async Order info", "[rest][private][async][orderinfo]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": [
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 123123132123,
            "transacttime": 0,
            "value": "100.0"
        },
        {
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc1",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 2345676543246,
            "transacttime": 0,
            "value": "100.0"
        }
    ]
})"_json;

  OrderInfoRequest request{OrderIdT{"9be73240-c3e4-4d0d-a8d7-57d9a6d798e1"}};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<OrderInfoRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync())
     .WillOnce(Return(mockDispatcher.dispatch(OrderInfo::uri(), request)));

  auto asyncRawRes = asyncDispatcher.getAsync();
  auto response = OrderInfo::processResponse(std::move(asyncRawRes));

  REQUIRE(response.ordersInfo.size() == 2);
  REQUIRE(response.ordersInfo.at(0).instrument == "btc_usd_spot");
}

TEST_CASE("New Order ", "[rest][private][neworder]") {
  MockDispatcher mockDispatcher;
  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result":{
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 123123132123,
            "transacttime": 0,
            "value": "100.0"
        }
})"_json;

  NewOrderRequest request{
      InstrumentT{"btc_usd_spot"},
      SideT{1},
      OrdType{1},
      PriceT{100},
      QtyT{100},
  };

  EXPECT_CALL(mockDispatcher, dispatch(_, An<NewOrderRequest>()))
      .WillOnce(Return(apiRes));
  auto rawResponse = mockDispatcher.dispatch(NewOrder::uri(), request);
  auto response = NewOrder::processResponse(std::move(rawResponse));

  REQUIRE(response.instrument == "btc_usd_spot");
}

TEST_CASE("New Order Async ", "[rest][private][async][neworder]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result":{
            "AvgPx": "0",
            "LastLiquidityInd": "0",
            "LastPx": "0",
            "LastQty": "0",
            "account": "a9e3d010-3169-489d-9063-ced912b0fdc8",
            "cancelondisconnect": 0,
            "clorderid": "",
            "cumqty": "0",
            "execid": "",
            "exectype": 1,
            "expiry": 0,
            "fill_price": "0",
            "instrument": "btc_usd_spot",
            "leavesqty": "1",
            "orderid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "orderqty": "1",
            "ordrejreason": "",
            "ordstatus": 1,
            "ordstatusReqID": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "ordtype": 1,
            "origclid": "a9e3d010-3169-489d-9063-ced912b0fdc9",
            "price": "10.0",
            "side": 1,
            "stoppx": "0",
            "time_in_force": 0,
            "timestamp": 123123132123,
            "transacttime": 0,
            "value": "100.0"
        }
})"_json;

  NewOrderRequest request{
      InstrumentT{"btc_usd_spot"},
      SideT{1},
      OrdType{1},
      PriceT{100},
      QtyT{100},
  };

  EXPECT_CALL(mockDispatcher, dispatch(_, An<NewOrderRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, postAsync(An<NewOrderRequest>()))
  .WillOnce(Return(mockDispatcher.dispatch(NewOrder::uri(), request)));
  auto asyncRawRes = asyncDispatcher.postAsync(request);
  auto response = NewOrder::processResponse(std::move(asyncRawRes));

  REQUIRE(response.instrument == "btc_usd_spot");
}

TEST_CASE("Trades History", "[rest][private][tradehistory]") {
  MockDispatcher mockDispatcher;
  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
        "btc_usd_spot": [
            {
                "exec_price": 20.0,
                "exec_qty": 1.0,
                "exec_type": 1,
                "exec_value": 20000.0,
                "fee_paid": 0.005,
                "fee_rate": 0.0001,
                "fee_type": 1,
                "notes": "insert notes",
                "order_price": 0,
                "order_qty": 0,
                "order_remaining": 0,
                "order_type": 1,
                "order_uuid": "9927e7e9-c6d0-43ad-9443-8bb6b56ce1fd",
                "side": 1,
                "status": 1,
                "symbol": "btc_usd_spot",
                "timestamp": 123123,
                "user_uuid": "9927e7e9-c6d0-43ad-9443-8bb6b56ce1fb"
            },
            {
                "exec_price": 20.0,
                "exec_qty": 1.0,
                "exec_type": 1,
                "exec_value": 20000.0,
                "fee_paid": 0.005,
                "fee_rate": 0.0001,
                "fee_type": 1,
                "notes": "insert notes",
                "order_price": 0,
                "order_qty": 0,
                "order_remaining": 0,
                "order_type": 1,
                "order_uuid": "9927e7e9-c6d0-43ad-9443-8bb6b56ce1fe",
                "side": 1,
                "status": 1,
                "symbol": "btc_usd_spot",
                "timestamp": 123123,
                "user_uuid": "9927e7e9-c6d0-43ad-9443-8bb6b56ce1fb"
            }
        ]
}
})"_json;

  TradesHistoryRequest request{};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<TradesHistoryRequest>()))
      .WillOnce(Return(apiRes));
  auto rawResponse = mockDispatcher.dispatch(TradesHistory::uri(), request);
  auto response = TradesHistory::processResponse(std::move(rawResponse));

  REQUIRE(response.histories.size() == 1);
  REQUIRE(response.histories.at(0).second.size() == 2);
}

TEST_CASE("Async Trades History", "[rest][private][async][tradehistory]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;

  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
    "result": {
        "btc_usd_spot": [
            {
                "exec_price": 20.0,
                "exec_qty": 1.0,
                "exec_type": 1,
                "exec_value": 20000.0,
                "fee_paid": 0.005,
                "fee_rate": 0.0001,
                "fee_type": 1,
                "notes": "insert notes",
                "order_price": 0,
                "order_qty": 0,
                "order_remaining": 0,
                "order_type": 1,
                "order_uuid": "9927e7e9-c6d0-43ad-9443-8bb6b56ce1fd",
                "side": 1,
                "status": 1,
                "symbol": "btc_usd_spot",
                "timestamp": 123123,
                "user_uuid": "9927e7e9-c6d0-43ad-9443-8bb6b56ce1fb"
            },
            {
                "exec_price": 20.0,
                "exec_qty": 1.0,
                "exec_type": 1,
                "exec_value": 20000.0,
                "fee_paid": 0.005,
                "fee_rate": 0.0001,
                "fee_type": 1,
                "notes": "insert notes",
                "order_price": 0,
                "order_qty": 0,
                "order_remaining": 0,
                "order_type": 1,
                "order_uuid": "9927e7e9-c6d0-43ad-9443-8bb6b56ce1fe",
                "side": 1,
                "status": 1,
                "symbol": "btc_usd_spot",
                "timestamp": 123123,
                "user_uuid": "9927e7e9-c6d0-43ad-9443-8bb6b56ce1fb"
            }
        ]
}
})"_json;

  TradesHistoryRequest request{};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<TradesHistoryRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync(An<TradesHistoryRequest>()))
  .WillOnce(Return(mockDispatcher.dispatch(TradesHistory::uri(), request)));
  auto asyncRawRes = asyncDispatcher.getAsync(request);
  auto response = TradesHistory::processResponse(std::move(asyncRawRes));

  REQUIRE(response.histories.size() == 1);
  REQUIRE(response.histories.at(0).second.size() == 2);
}

TEST_CASE("Transaction History", "[rest][private][txhistory]") {
  MockDispatcher mockDispatcher;
  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
        "result": {
        "deposit": {
            "idr": [
                {
                    "account_balance_id": 1,
                    "address": "thisisaddress",
                    "amount": "100000000.0",
                    "asset": "idr",
                    "fee": "0.0",
                    "final_balance": "1100000000.0",
                    "notes": "",
                    "status": "Cancelled",
                    "time": 1618206392203845000,
                    "type": 1
                 }
            ],
            "btc": [
                {
                    "account_balance_id": 2,
                    "address": "thisisaddress",
                    "amount": "1.0",
                    "asset": "btc",
                    "fee": "0.0",
                    "final_balance": "10.0",
                    "notes": "",
                    "status": "Cancelled",
                    "time": 1618206125002066000,
                    "type": 1
                }
            ]
        },
        "withdrawal": {
            "btc": [
                {
                    "account_balance_id": 4,
                    "address": "thisisaddress",
                    "amount": "-1.0",
                    "asset": "btc",
                    "fee": "0.0",
                    "final_balance": "9.0",
                    "notes": "",
                    "status": "Pending",
                    "time": 1617974544507879000,
                    "type": 2
                }
            ],
            "idr": [
                {
                    "account_balance_id": 3,
                    "address": "thisisaddress",
                    "amount": "-1000.0",
                    "asset": "idr",
                    "fee": "0.0",
                    "final_balance": "1099999000.0",
                    "notes": "",
                    "status": "Pending",
                    "time": 1618207558627212000,
                    "type": 2
                }
            ]
        }
}
})"_json;

  TransactionHistoryRequest request{};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<TransactionHistoryRequest>()))
      .WillOnce(Return(apiRes));
  auto rawResponse =
      mockDispatcher.dispatch(TransactionHistory::uri(), request);
  auto response = TransactionHistory::processResponse(std::move(rawResponse));

  REQUIRE(response.withdrawals.size() > 1);
  REQUIRE(response.deposits.size() >= 2);
}

TEST_CASE("Async Transaction History", "[rest][private][async][txhistory]") {
  MockDispatcher mockDispatcher;
  MockAsyncDispatcher asyncDispatcher;
  auto apiRes = R"({
    "statusCode": 200,
    "error": [],
        "result": {
        "deposit": {
            "idr": [
                {
                    "account_balance_id": 1,
                    "address": "thisisaddress",
                    "amount": "100000000.0",
                    "asset": "idr",
                    "fee": "0.0",
                    "final_balance": "1100000000.0",
                    "notes": "",
                    "status": "Cancelled",
                    "time": 1618206392203845000,
                    "type": 1
                 }
            ],
            "btc": [
                {
                    "account_balance_id": 2,
                    "address": "thisisaddress",
                    "amount": "1.0",
                    "asset": "btc",
                    "fee": "0.0",
                    "final_balance": "10.0",
                    "notes": "",
                    "status": "Cancelled",
                    "time": 1618206125002066000,
                    "type": 1
                }
            ]
        },
        "withdrawal": {
            "btc": [
                {
                    "account_balance_id": 4,
                    "address": "thisisaddress",
                    "amount": "-1.0",
                    "asset": "btc",
                    "fee": "0.0",
                    "final_balance": "9.0",
                    "notes": "",
                    "status": "Pending",
                    "time": 1617974544507879000,
                    "type": 2
                }
            ],
            "idr": [
                {
                    "account_balance_id": 3,
                    "address": "thisisaddress",
                    "amount": "-1000.0",
                    "asset": "idr",
                    "fee": "0.0",
                    "final_balance": "1099999000.0",
                    "notes": "",
                    "status": "Pending",
                    "time": 1618207558627212000,
                    "type": 2
                }
            ]
        }
}
})"_json;

  TransactionHistoryRequest request{};

  EXPECT_CALL(mockDispatcher, dispatch(_, An<TransactionHistoryRequest>()))
      .WillOnce(Return(apiRes));
  EXPECT_CALL(asyncDispatcher, getAsync(An<TransactionHistoryRequest>()))
  .WillOnce(Return(mockDispatcher.dispatch(TransactionHistory::uri(),request)));
  auto asyncRawRes =
      asyncDispatcher.getAsync(request);
  auto response = TransactionHistory::processResponse(std::move(asyncRawRes));

  REQUIRE(response.withdrawals.size() > 1);
  REQUIRE(response.deposits.size() >= 2);
}