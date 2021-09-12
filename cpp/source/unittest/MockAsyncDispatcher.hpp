#pragma once
#include "details/Types.hpp"
#include "nlohmann/json.hpp"
#include "gmock/gmock.h"

using ::testing::AtLeast;
using json = nlohmann::json;
using namespace Bitwyre::Types::Public;
using namespace Bitwyre::Types::Private;
using Callback = std::function<void(const TimeResponse&)>;

class MockAsyncDispatcher {
public:
    MOCK_METHOD(void, getAsync, (Callback cb));
    MOCK_METHOD(json, getAsync, ());
    MOCK_METHOD(json, getAsync, (DepthRequest request));
    MOCK_METHOD(json, getAsync, (InstrumentRequest request));
    MOCK_METHOD(json, getAsync, (ContractRequest request));
    MOCK_METHOD(json, getAsync, (TickerRequest request));
    MOCK_METHOD(json, getAsync, (TradesRequest request));
    MOCK_METHOD(json, getAsync, (AccountBalanceRequest request));
};
