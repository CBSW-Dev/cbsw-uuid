#include "pch.hpp"
#include "test.hpp"

#include "uuid.hpp"
suite() {
    describe("Uuid") {
        it("is the correct size") {
            CBSW::Uuid uuid;
            expect(sizeof(uuid)).to.equal(16);
        }

        it("constructs a null uuid by default") {
            CBSW::Uuid uuid;
            expect(uuid.data[0]).to.equal(0);
            expect(uuid.data[1]).to.equal(0);
            expect(uuid.data[2]).to.equal(0);
            expect(uuid.data[3]).to.equal(0);
            expect(uuid.data[4]).to.equal(0);
            expect(uuid.data[5]).to.equal(0);
            expect(uuid.data[6]).to.equal(0);
            expect(uuid.data[7]).to.equal(0);
            expect(uuid.data[8]).to.equal(0);
            expect(uuid.data[9]).to.equal(0);
            expect(uuid.data[10]).to.equal(0);
            expect(uuid.data[11]).to.equal(0);
            expect(uuid.data[12]).to.equal(0);
            expect(uuid.data[13]).to.equal(0);
            expect(uuid.data[14]).to.equal(0);
            expect(uuid.data[15]).to.equal(0);
        }

        it("constructs a uuid from a character array") {
            constexpr CBSW::Uuid uuid{"6167ebb3-2b9a-425c-87bd-c66798d72dff"};
            expect((int)uuid.data[0]).to.equal(0x61);
            expect((int)uuid.data[1]).to.equal(0x67);
            expect((int)uuid.data[2]).to.equal(0xEB);
            expect((int)uuid.data[3]).to.equal(0xB3);
            expect((int)uuid.data[4]).to.equal(0x2B);
            expect((int)uuid.data[5]).to.equal(0x9A);
            expect((int)uuid.data[6]).to.equal(0x42);
            expect((int)uuid.data[7]).to.equal(0x5C);
            expect((int)uuid.data[8]).to.equal(0x87);
            expect((int)uuid.data[9]).to.equal(0xBD);
            expect((int)uuid.data[10]).to.equal(0xC6);
            expect((int)uuid.data[11]).to.equal(0x67);
            expect((int)uuid.data[12]).to.equal(0x98);
            expect((int)uuid.data[13]).to.equal(0xD7);
            expect((int)uuid.data[14]).to.equal(0x2D);
            expect((int)uuid.data[15]).to.equal(0xFF);
        }

        it("constructs a uuid from a character array (using the user-defined literal)") {
            constexpr CBSW::Uuid uuid = "6167ebb3-2b9a-425c-87bd-c66798d72dff"_uuid;
            expect((int)uuid.data[0]).to.equal(0x61);
            expect((int)uuid.data[1]).to.equal(0x67);
            expect((int)uuid.data[2]).to.equal(0xEB);
            expect((int)uuid.data[3]).to.equal(0xB3);
            expect((int)uuid.data[4]).to.equal(0x2B);
            expect((int)uuid.data[5]).to.equal(0x9A);
            expect((int)uuid.data[6]).to.equal(0x42);
            expect((int)uuid.data[7]).to.equal(0x5C);
            expect((int)uuid.data[8]).to.equal(0x87);
            expect((int)uuid.data[9]).to.equal(0xBD);
            expect((int)uuid.data[10]).to.equal(0xC6);
            expect((int)uuid.data[11]).to.equal(0x67);
            expect((int)uuid.data[12]).to.equal(0x98);
            expect((int)uuid.data[13]).to.equal(0xD7);
            expect((int)uuid.data[14]).to.equal(0x2D);
            expect((int)uuid.data[15]).to.equal(0xFF);
        }

        it("constructs a uuid from a different character array") {
            constexpr CBSW::Uuid uuid{"10d9d9aa-764f-4ae6-b4a0-7018f190d90c"};
            expect((int)uuid.data[0]).to.equal(0x10);
            expect((int)uuid.data[1]).to.equal(0xD9);
            expect((int)uuid.data[2]).to.equal(0xD9);
            expect((int)uuid.data[3]).to.equal(0xAA);
            expect((int)uuid.data[4]).to.equal(0x76);
            expect((int)uuid.data[5]).to.equal(0x4F);
            expect((int)uuid.data[6]).to.equal(0x4A);
            expect((int)uuid.data[7]).to.equal(0xE6);
            expect((int)uuid.data[8]).to.equal(0xB4);
            expect((int)uuid.data[9]).to.equal(0xA0);
            expect((int)uuid.data[10]).to.equal(0x70);
            expect((int)uuid.data[11]).to.equal(0x18);
            expect((int)uuid.data[12]).to.equal(0xF1);
            expect((int)uuid.data[13]).to.equal(0x90);
            expect((int)uuid.data[14]).to.equal(0xD9);
            expect((int)uuid.data[15]).to.equal(0x0C);
        }

        it("constructs a uuid from a different character array (using the user-defined literal)") {
            constexpr CBSW::Uuid uuid = "10d9d9aa-764f-4ae6-b4a0-7018f190d90c"_uuid;
            expect((int)uuid.data[0]).to.equal(0x10);
            expect((int)uuid.data[1]).to.equal(0xD9);
            expect((int)uuid.data[2]).to.equal(0xD9);
            expect((int)uuid.data[3]).to.equal(0xAA);
            expect((int)uuid.data[4]).to.equal(0x76);
            expect((int)uuid.data[5]).to.equal(0x4F);
            expect((int)uuid.data[6]).to.equal(0x4A);
            expect((int)uuid.data[7]).to.equal(0xE6);
            expect((int)uuid.data[8]).to.equal(0xB4);
            expect((int)uuid.data[9]).to.equal(0xA0);
            expect((int)uuid.data[10]).to.equal(0x70);
            expect((int)uuid.data[11]).to.equal(0x18);
            expect((int)uuid.data[12]).to.equal(0xF1);
            expect((int)uuid.data[13]).to.equal(0x90);
            expect((int)uuid.data[14]).to.equal(0xD9);
            expect((int)uuid.data[15]).to.equal(0x0C);
        }

        it("constructs a uuid from a uint8_t array") {
            std::vector<uint8_t> data = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xF1, 0xC3, 0xA5, 0x87, 0x69, 0x4B, 0x2D, 0x0F};
            const CBSW::Uuid uuid{data.data()};
            expect((int)uuid.data[0]).to.equal(0x01);
            expect((int)uuid.data[1]).to.equal(0x23);
            expect((int)uuid.data[2]).to.equal(0x45);
            expect((int)uuid.data[3]).to.equal(0x67);
            expect((int)uuid.data[4]).to.equal(0x89);
            expect((int)uuid.data[5]).to.equal(0xAB);
            expect((int)uuid.data[6]).to.equal(0xCD);
            expect((int)uuid.data[7]).to.equal(0xEF);
            expect((int)uuid.data[8]).to.equal(0xF1);
            expect((int)uuid.data[9]).to.equal(0xC3);
            expect((int)uuid.data[10]).to.equal(0xA5);
            expect((int)uuid.data[11]).to.equal(0x87);
            expect((int)uuid.data[12]).to.equal(0x69);
            expect((int)uuid.data[13]).to.equal(0x4B);
            expect((int)uuid.data[14]).to.equal(0x2D);
            expect((int)uuid.data[15]).to.equal(0x0F);
        }

        it("converts a uuid to a string") {
            std::vector<uint8_t> data = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xF1, 0xC3, 0xA5, 0x87, 0x69, 0x4B, 0x2D, 0x0F};
            const CBSW::Uuid uuid{data.data()};
            std::string uuidString (uuid.toString());
            expect(std::string(uuid.toString())).to.equal("01234567-89ab-cdef-f1c3-a587694b2d0f");
        }
    }
}