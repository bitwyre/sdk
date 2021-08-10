#include "catch2/catch.hpp"

TEST_CASE("Sha256 of a payload", "[rest][private][sign]") {
  nlohmann::ordered_json payload;
  payload["instrument"] = "btc_usdt_spot";
  payload["side"] = 1;
  payload["price"] = 10000;
  payload["ordtype"] = 2;
  payload["orderqty"] = 1;

  std::cout << nlohmann::ordered_json(payload.dump()).dump() << "\n";
  std::cout << Bitwyre::Utils::SHA256(
      nlohmann::ordered_json(payload.dump()).dump());
}

TEST_CASE("HMAC", "[rest][private][hmac]") {
  auto r = Bitwyre::Utils::HMAC("qwerty");
  auto expectedHmac =
      "BABA40E43388359970C18593159EEA9881E24F00304412848B4EF53EB264531E4D17920D"
      "BB8FAD7B30EF9D6F5E5F1E0AD124B24109410BE53FE158BAC6BB041E";
  REQUIRE(expectedHmac == r);
}