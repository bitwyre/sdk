#pragma once
#include "details/Types.hpp"
#include "nlohmann/json.hpp"
#include "gmock/gmock.h"
#include <future>

using ::testing::AtLeast;
using json = nlohmann::json;
using namespace Bitwyre::Types::Public;
using namespace Bitwyre::Types::Private;
using Callback = std::function<void(const TimeResponse&)>;

class MockAsyncDispatcher {
public:
    //MOCK_METHOD(std::future<void>, getAsync, (Callback cb));
    MOCK_METHOD(void, getAsync, (Callback cb));
    MOCK_METHOD(json, getAsync, ());
    MOCK_METHOD(json, getAsync, (DepthRequest request));
    MOCK_METHOD(json, getAsync, (InstrumentRequest request));
    MOCK_METHOD(json, getAsync, (ContractRequest request));
    MOCK_METHOD(json, getAsync, (TickerRequest request));
    MOCK_METHOD(json, getAsync, (TradesRequest request));
    MOCK_METHOD(json, getAsync, (AccountBalanceRequest request));
    MOCK_METHOD(json, getAsync, (AccountStatementRequest request));
    MOCK_METHOD(json, delAsync, (CancelOrderRequest request));
    MOCK_METHOD(json, getAsync, (OpenOrdersRequest request));
    MOCK_METHOD(json, getAsync, (ClosedOrdersRequest request));
    MOCK_METHOD(json, postAsync, (NewOrderRequest request));
    MOCK_METHOD(json, getAsync, (OrderInfoRequest request));
    MOCK_METHOD(json, getAsync, (TradesHistoryRequest request));

//    MOCK_METHOD(json, getCallback, (Callback cb));
//  //  template<class Callback, typename Dispatcher = Dispatcher>
//    template<typename Callback>
//    auto GetValue(Callback& call);
//    template<>
//    auto GetValue(json& value){
//      getCallback(value);
//    }
//    [[nodiscard]] static auto getAsync(Callback cb) noexcept -> AsyncTimeResponse {
//      return std::async(std::launch::async, [](Callback cb){return cb(get<Dispatcher>());}, std::move(cb));
//    }

//    template<typename ValueType>
//    void GetValue(ValueType& value)
//
//    template <typename ValueType>
//    void getValue(ValueType& value);
//
//    template<>
//    void getValue(Callback cb) {
//      getAsync(cb);
//    }

};
