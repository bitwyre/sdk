#pragma once
#include "details/Types.hpp"
#include "nlohmann/json.hpp"
#include "gmock/gmock.h"

using ::testing::AtLeast;
using json = nlohmann::json;
using namespace Bitwyre::Types::Public;
using namespace Bitwyre::Types::Private;

class MockDispatcher {
public:
  MOCK_METHOD(json, dispatch, (std::string_view uri, CommonPublicRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, InstrumentRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, TickerRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, TradesRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, DepthRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, ContractRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, AccountBalanceRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, AccountStatementRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, CancelOrderRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, ClosedOrdersRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, OpenOrdersRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, OrderInfoRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, TradesHistoryRequest));
  MOCK_METHOD(json, dispatch, (std::string_view uri, NewOrderRequest));
  MOCK_METHOD(json, dispatch,
              (std::string_view uri, TransactionHistoryRequest));

  auto operator()(std::string_view uri, CommonPublicRequest commonPublicRequest)
      -> json {
    return dispatch(uri, commonPublicRequest);
  }

  auto operator()(std::string_view uri, InstrumentRequest instrumentRequest)
      -> json {
    return dispatch(uri, instrumentRequest);
  }

  auto operator()(std::string_view uri, TickerRequest tickerRequest) -> json {
    return dispatch(uri, tickerRequest);
  }

  auto operator()(std::string_view uri, TradesRequest tickerRequest) -> json {
    return dispatch(uri, tickerRequest);
  }

  auto operator()(std::string_view uri, DepthRequest depthRequest) -> json {
    return dispatch(uri, depthRequest);
  }

  auto operator()(std::string_view uri, ContractRequest contractRequest)
      -> json {
    return dispatch(uri, contractRequest);
  }

  // Private endpoints mocks

  auto operator()(std::string_view uri,
                  AccountBalanceRequest accountBalanceRequest) -> json {
    return dispatch(uri, accountBalanceRequest);
  }

  auto operator()(std::string_view uri,
                  AccountStatementRequest accountStatementRequest) -> json {
    return dispatch(uri, accountStatementRequest);
  }

  auto operator()(std::string_view uri, CancelOrderRequest cancelOrderRequest)
      -> json {
    return dispatch(uri, cancelOrderRequest);
  }

  auto operator()(std::string_view uri, ClosedOrdersRequest closedOrdersRequest)
      -> json {
    return dispatch(uri, closedOrdersRequest);
  }

  auto operator()(std::string_view uri, OpenOrdersRequest closedOrdersRequest)
      -> json {
    return dispatch(uri, closedOrdersRequest);
  }

  auto operator()(std::string_view uri, OrderInfoRequest orderInfoRequest)
      -> json {
    return dispatch(uri, orderInfoRequest);
  }

  auto operator()(std::string_view uri,
                  TradesHistoryRequest tradesHistoryRequest) -> json {
    return dispatch(uri, tradesHistoryRequest);
  }

  auto operator()(std::string_view uri, NewOrderRequest newOrderRequest)
      -> json {
    return dispatch(uri, newOrderRequest);
  }

  auto operator()(std::string_view uri, TransactionHistoryRequest request)
      -> json {
    return dispatch(uri, request);
  }
};