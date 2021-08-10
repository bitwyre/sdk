#pragma once
#include "nlohmann/json.hpp"
#include <iostream>

namespace Bitwyre::Details {
  using json = nlohmann::json;
  using ErrorsT = std::vector<std::string>;

  struct Response {
    int statusCode_;
    ErrorsT errors_;
    bool next_{false};

    [[nodiscard]] auto getErrors() const& noexcept -> const ErrorsT& {
      return errors_;
    }

    [[nodiscard]] auto getErrors() && noexcept -> ErrorsT {
      return std::move(errors_);
    }

    [[nodiscard]] auto getStatusCode() const noexcept -> long {
      return statusCode_;
    }

    auto hasNext() const -> bool {
      return next_;
    }

    auto showErrors() -> void {
      for (const auto& e : errors_) {
        std::cout << e << "\n";
      }
    }
  };
} // namespace Bitwyre::Details