#pragma once

#include "ConstexprMap.hpp"
#include <map>

namespace Bitwyre::Details {

  [[nodiscard]] static auto getEnvOr(std::string_view envName,
                                     std::string_view defValue) noexcept
      -> std::string {

    if (auto* envVal = std::getenv(envName.data())) {
      return envVal;
    }
    return std::string{defValue};
  }

  struct Config {
    using ConfMapT = ConstexprMap<std::string_view, std::string_view, 2>;

  private:
    const inline static auto API_URL =
        getEnvOr("URL_API_BITWYRE", "https://api.bitwyre.id");
    const inline static std::map<std::string, std::string> confMap_ = {
        {"URL_API_BITWYRE", API_URL},
        {"TIMEOUT", "5"},
    };

  public:
    static auto getConfig() {
      return confMap_;
    }
  };

} // namespace Bitwyre::Details
