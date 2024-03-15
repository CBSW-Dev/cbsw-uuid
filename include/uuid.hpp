#pragma once

#include <cstdint>
#include <stdexcept>

namespace CBSW {
    namespace Private::Uuid {
        constexpr std::uint8_t buildNybble(const char digit) {
            return (digit >= '0' && digit<= '9') ? digit - '0' :
                (digit >= 'a' && digit<= 'f') ? digit - 'a' + 10 :
                (digit >= 'A' && digit<= 'F') ? digit - 'A' + 10 :
                throw std::domain_error("Invalid character in uuid");
        }

        constexpr std::uint8_t buildByte(std::uint8_t index, const char* uuid) {
            return (buildNybble(uuid[index]) << 4) | buildNybble(uuid[index + 1]);
        }

        constexpr char buildChar(std::uint8_t digit) {
            return (digit <= 9) ? digit + '0' : (digit - 10) + 'a';
        }

        constexpr char buildCharHigh(std::uint8_t digit) {
            return buildChar((digit >> 4) & 0x0F);
        }

        constexpr char buildCharLow(std::uint8_t digit) {
            return buildChar((digit >> 0) & 0x0F);
        }

        constexpr void test_precondition(const char* uuid, const std::size_t N) {

            uuid[8] == '-' ? 0 : throw std::domain_error("Invalid character in uuid");
            uuid[13] == '-' ? 0 : throw std::domain_error("Invalid character in uuid");
            uuid[18] == '-' ? 0 : throw std::domain_error("Invalid character in uuid");
            uuid[23] == '-' ? 0 : throw std::domain_error("Invalid character in uuid");

            N == 36 ? 0 : throw std::domain_error("Uuid is incorrect length");
        }

        class Precondition {
        public:
            constexpr Precondition() = default;
            constexpr Precondition(const char *uuid, const std::size_t N) {
                test_precondition(uuid, N);
            }
        };
    }

    class Uuid: public Private::Uuid::Precondition {
    public:
        std::uint8_t data[16];

        constexpr Uuid():
            data{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        {}

        template <int N> constexpr Uuid(const char (&uuid)[N]):
            Uuid(static_cast<const char *>(uuid), N - 1)
        {}

        constexpr Uuid(const char *uuid, std::size_t N):
            Precondition(uuid, N),
            data{
                Private::Uuid::buildByte(0, uuid),
                Private::Uuid::buildByte(2, uuid),
                Private::Uuid::buildByte(4, uuid),
                Private::Uuid::buildByte(6, uuid),
                Private::Uuid::buildByte(9, uuid),
                Private::Uuid::buildByte(11, uuid),
                Private::Uuid::buildByte(14, uuid),
                Private::Uuid::buildByte(16, uuid),
                Private::Uuid::buildByte(19, uuid),
                Private::Uuid::buildByte(21, uuid),
                Private::Uuid::buildByte(24, uuid),
                Private::Uuid::buildByte(26, uuid),
                Private::Uuid::buildByte(28, uuid),
                Private::Uuid::buildByte(30, uuid),
                Private::Uuid::buildByte(32, uuid),
                Private::Uuid::buildByte(34, uuid)
            }
        {}

        Uuid(const std::uint8_t *uuid):
            data{
                uuid[0], uuid[1], uuid[2], uuid[3],
                uuid[4], uuid[5], uuid[6], uuid[7],
                uuid[8], uuid[9], uuid[10], uuid[11],
                uuid[12], uuid[13], uuid[14], uuid[15]
            }
        {}

        std::string toString() const noexcept {
            const char array[36] = {
                Private::Uuid::buildCharHigh(data[0]),Private::Uuid::buildCharLow(data[0]),
                Private::Uuid::buildCharHigh(data[1]),Private::Uuid::buildCharLow(data[1]),
                Private::Uuid::buildCharHigh(data[2]),Private::Uuid::buildCharLow(data[2]),
                Private::Uuid::buildCharHigh(data[3]),Private::Uuid::buildCharLow(data[3]),
                '-',
                Private::Uuid::buildCharHigh(data[4]),Private::Uuid::buildCharLow(data[4]),
                Private::Uuid::buildCharHigh(data[5]),Private::Uuid::buildCharLow(data[5]),
                '-',
                Private::Uuid::buildCharHigh(data[6]),Private::Uuid::buildCharLow(data[6]),
                Private::Uuid::buildCharHigh(data[7]),Private::Uuid::buildCharLow(data[7]),
                '-',
                Private::Uuid::buildCharHigh(data[8]),Private::Uuid::buildCharLow(data[8]),
                Private::Uuid::buildCharHigh(data[9]),Private::Uuid::buildCharLow(data[9]),
                '-',
                Private::Uuid::buildCharHigh(data[10]),Private::Uuid::buildCharLow(data[10]),
                Private::Uuid::buildCharHigh(data[11]),Private::Uuid::buildCharLow(data[11]),
                Private::Uuid::buildCharHigh(data[12]),Private::Uuid::buildCharLow(data[12]),
                Private::Uuid::buildCharHigh(data[13]),Private::Uuid::buildCharLow(data[13]),
                Private::Uuid::buildCharHigh(data[14]),Private::Uuid::buildCharLow(data[14]),
                Private::Uuid::buildCharHigh(data[15]),Private::Uuid::buildCharLow(data[15]),
            };
            return std::string(array, 36);
        }
    };
}

constexpr ::CBSW::Uuid operator""_uuid(const char *uuid, std::size_t N) {
    return ::CBSW::Uuid(uuid, N);
}

