#pragma once
#include <Windows.h>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <type_traits>
#include <cassert>

namespace memory {

    // RAII helper to manage page protection changes
    class ProtectionGuard {
    public:
        ProtectionGuard(void* address, size_t size, DWORD newProtect);
        ~ProtectionGuard();

        ProtectionGuard(const ProtectionGuard&) = delete;
        ProtectionGuard& operator=(const ProtectionGuard&) = delete;

    private:
        void* _address;
        size_t _size;
        DWORD _oldProtect;
    };

    // Template read function
    template<typename T>
    T read(uintptr_t address);

    // Template write function
    template<typename T>
    void write(uintptr_t address, const T& value);

    // Write a byte vector to memory
    void write_bytes(uintptr_t address, const std::vector<uint8_t>& bytes);

    // NOP out a section of memory
    void nop(uintptr_t address, size_t count);

    // Read a vector of bytes from memory
    std::vector<uint8_t> read_bytes(uintptr_t address, size_t count);

} // namespace memory

  // Inline template definitions
namespace memory {

    inline ProtectionGuard::ProtectionGuard(void* address, size_t size, DWORD newProtect)
        : _address(address), _size(size), _oldProtect(0) {
        if (!VirtualProtect(_address, _size, newProtect, &_oldProtect)) {
            throw std::runtime_error("Failed to change memory protection.");
        }
    }

    inline ProtectionGuard::~ProtectionGuard() {
        DWORD temp;
        VirtualProtect(_address, _size, _oldProtect, &temp);
    }

    template<typename T>
    inline T read(uintptr_t address) {
        static_assert(std::is_trivially_copyable_v<T>, "read<T> only supports trivially copyable types.");
        T buffer{};
        memcpy(&buffer, reinterpret_cast<void*>(address), sizeof(T));
        return buffer;
    }

    template<typename T>
    inline void write(uintptr_t address, const T& value) {
        static_assert(std::is_trivially_copyable_v<T>, "write<T> only supports trivially copyable types.");
        ProtectionGuard guard(reinterpret_cast<void*>(address), sizeof(T), PAGE_EXECUTE_READWRITE);
        memcpy(reinterpret_cast<void*>(address), &value, sizeof(T));
    }

    inline void write_bytes(uintptr_t address, const std::vector<uint8_t>& bytes) {
        if (bytes.empty()) return;
        ProtectionGuard guard(reinterpret_cast<void*>(address), bytes.size(), PAGE_EXECUTE_READWRITE);
        memcpy(reinterpret_cast<void*>(address), bytes.data(), bytes.size());
    }

    inline void nop(uintptr_t address, size_t count) {
        ProtectionGuard guard(reinterpret_cast<void*>(address), count, PAGE_EXECUTE_READWRITE);
        memset(reinterpret_cast<void*>(address), 0x90, count);
    }

    inline std::vector<uint8_t> read_bytes(uintptr_t address, size_t count) {
        std::vector<uint8_t> buffer(count);
        memcpy(buffer.data(), reinterpret_cast<void*>(address), count);
        return buffer;
    }


    inline uint32_t sigscan_ex(uint8_t* base_ptr, const uint8_t* end_ptr, const uint8_t* pattern, const char* mask) {
        size_t Length = strlen(mask);
        size_t i = 0;
        while (base_ptr < end_ptr)
        {
            for (i = 0; i < Length; i++)
            {
                if (!(mask[i] == '?' || mask[i] == '\x02') && pattern[i] != base_ptr[i])
                {
                    break;
                }
            }
            if (i == Length)
            {
                return (uint32_t)base_ptr;
            }
            base_ptr++;
        }
        return 0;
    }


    inline uint32_t sigscan(const uint8_t* pattern, const char* mask) {
        uint8_t *BasePtr = (uint8_t *)0x400100;
        uint8_t *EndPtr = BasePtr + 0x800000;

        return sigscan_ex(BasePtr, EndPtr, pattern, mask);
    }

    inline uint32_t sigscan(const char* pattern, const char* mask) {
        uint8_t *BasePtr = (uint8_t *)0x400100;
        uint8_t *EndPtr = BasePtr + 0x800000;

        return sigscan_ex(BasePtr, EndPtr, (const uint8_t*)pattern, mask);
    }

} // namespace memory
