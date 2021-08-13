#pragma once
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/hmac.h"
#include "cryptopp/sha.h"

namespace Bitwyre {
  namespace Utils {

    inline static std::string lowercase(const std::string& data) {
      std::string res{};
      for (auto& e : data) {
        if (!std::isdigit(e)) {
          res += std::tolower(e);
        } else {
          res += e;
        }
      }
      return res;
    }

    inline static std::string SHA256(const std::string& data) {
      CryptoPP::SHA256 hash{};
      std::string digest;

      CryptoPP::StringSource stringSource{
          data,
          /*dumpAll=*/true,
          new CryptoPP::HashFilter(
              hash,
              new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest)))};
      return digest;
    }

    inline static std::string HMAC(const std::string& data) {
      assert(std::getenv("BITWYRE_API_SECRET") != nullptr && "BITWYRE_API_SECRET NOT SET");
      std::string encoded;
      std::string key = std::getenv("BITWYRE_API_SECRET");
      std::string mac;
      try {
        CryptoPP::HMAC<CryptoPP::SHA512> hmac((CryptoPP::byte*)key.c_str(),
                                              key.size());
        CryptoPP::StringSource stringSource(
            data,
            true,
            new CryptoPP::HashFilter(
                hmac,
                new CryptoPP::StringSink(mac)) // HashFilter
        );                                     // StringSource
      } catch (const CryptoPP::Exception& e) {
        std::cerr << e.what() << "\n";
        exit(1);
      }
      encoded.clear();
      CryptoPP::StringSource stringSource(
          mac,
          true,
          new CryptoPP::HexEncoder(
              new CryptoPP::StringSink(encoded)) // HexEncoder
      );                                         // StringSource
      return encoded;
    }

    static auto getTimestamp() {
      return std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch())
          .count();
    }

    static auto sign(std::string_view uri, std::uint64_t nonce,
                     std::string checksum) -> std::string {
      auto nonceChecksum = SHA256(std::to_string(nonce) + checksum);
      auto dataToSign = std::string(uri.data()) + lowercase(nonceChecksum);
      return HMAC(dataToSign);
    }

  } // namespace Utils

} // namespace Bitwyre