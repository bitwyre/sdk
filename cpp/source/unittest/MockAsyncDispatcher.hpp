#pragma once
#include "details/Types.hpp"
#include "nlohmann/json.hpp"
#include "gmock/gmock.h"

using ::testing::AtLeast;
using json = nlohmann::json;
using namespace Bitwyre::Types::Public;
using namespace Bitwyre::Types::Private;

class MockAsyncDispatcher {
public:
    MOCK_METHOD(json, getAsync, ());
    MOCK_METHOD(json, getAsync, (const DepthRequest& request));
    MOCK_METHOD(json, getAsync, (const ContractRequest& request));
};

// https://stackoverflow.com/questions/36940031/gtest-gmock-matcher-for-subsequence-between-a-pair-of-iterators#37071027
// https://chromium.googlesource.com/external/gmock/+/refs/heads/master/include/gmock/gmock-matchers.h