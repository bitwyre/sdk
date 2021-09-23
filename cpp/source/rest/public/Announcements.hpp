#pragma once
#include <iostream>
#include <utility>
#include "../../details/Dispatcher.hpp"

using namespace Bitwyre::Details;

namespace Bitwyre::Rest::Public {

  struct Announcements {

    [[nodiscard]] std::string uri() const noexcept {
      return "/public/announcements";
    }
    [[nodiscard]] Response getAsync() const noexcept {
          return std::async(std::launch::async, [](){return get<Dispatcher>();});
    }
    [[nodiscard]] Response get() const noexcept {
      return Request::sendGet(uri());
    }
  };
} // namespace Bitwyre::Rest::Public
