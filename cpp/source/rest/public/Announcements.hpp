#pragma once

#include <iostream>
#include <utility>

using namespace Bitwyre::Details;

namespace Bitwyre::Rest::Public {

  struct Announcements {

    [[nodiscard]] std::string uri() const noexcept {
      return "/public/announcements";
    }

    [[nodiscard]] Response get() const noexcept {
      return Request::sendGet(uri());
    }
  };
} // namespace Bitwyre::Rest::Public
