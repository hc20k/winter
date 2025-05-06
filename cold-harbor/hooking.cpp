#include "hooking.h"
#include "memory.h"
#include "logging.h"

using namespace hooking;

namespace
{
	[[maybe_unused]] class _
	{
	public:
		_()
		{
			if (MH_Initialize() != MH_OK)
			{
				throw std::runtime_error("Failed to initialize MinHook");
			}
		}

		~_()
		{
			MH_Uninitialize();
		}
	} __;
}

void detour::create(void* place, void* target) {
	this->clear();
	this->place_ = place;

	if (MH_CreateHook(this->place_, target, &this->original_) != MH_OK)
	{
		throw std::runtime_error("Unable to create hook");
	}

	this->enable();
}

void detour::clear()
{
	if (this->place_)
	{
		MH_RemoveHook(this->place_);
	}

	this->place_ = nullptr;
	this->original_ = nullptr;
}

void detour::enable() const
{
	MH_EnableHook(this->place_);
}

detour::~detour()
{
	this->clear();
}

detour::detour(const size_t place, void* target)
{
	this->create(reinterpret_cast<void*>(place), target);
}
detour::detour(void* place, void* target)
{
	this->create(place, target);
}

void detour::disable() const
{
	MH_DisableHook(this->place_);
}

void detour::create(const size_t place, void* target)
{
	this->create(reinterpret_cast<void*>(place), target);
}

void* detour::get_original() const
{
	return this->original_;
}

void hooking::nop(void* place, const size_t length)
{
	DWORD old_protect{};
	VirtualProtect(place, length, PAGE_EXECUTE_READWRITE, &old_protect);

	std::memset(place, 0x90, length);

	VirtualProtect(place, length, old_protect, &old_protect);
	FlushInstructionCache(GetCurrentProcess(), place, length);
}

void hooking::nop(const size_t place, const size_t length)
{
	nop(reinterpret_cast<void*>(place), length);
}

void hooking::copy(void* place, const void* data, const size_t length)
{
	DWORD old_protect{};
	VirtualProtect(place, length, PAGE_EXECUTE_READWRITE, &old_protect);

	std::memmove(place, data, length);

	VirtualProtect(place, length, old_protect, &old_protect);
	FlushInstructionCache(GetCurrentProcess(), place, length);
}

void hooking::copy(const size_t place, const void* data, const size_t length)
{
	copy(reinterpret_cast<void*>(place), data, length);
}

bool hooking::is_relatively_far(const void* pointer, const void* data, const int offset)
{
	const int64_t diff = size_t(data) - (size_t(pointer) + offset);
	const auto small_diff = int32_t(diff);
	return diff != int64_t(small_diff);
}

void hooking::call(void* pointer, void* data)
{
	if (is_relatively_far(pointer, data))
	{
		throw std::runtime_error("Too far away to create 32bit relative branch");
	}

	auto* patch_pointer = PBYTE(pointer);
	set<uint8_t>(patch_pointer, 0xE8);
	set<int32_t>(patch_pointer + 1, int32_t(size_t(data) - (size_t(pointer) + 5)));
}

void hooking::call(const size_t pointer, void* data)
{
	return call(reinterpret_cast<void*>(pointer), data);
}

void hooking::qmov(void* place, void* target) {
	*(BYTE*)place = 0xB8; *(DWORD*)((uint32_t)target + 1) = (DWORD)target;
}

void hooking::qmov(const size_t place, const size_t target) {
	spdlog::info("qmov {} {}", place, target);
	qmov(reinterpret_cast<void*>(place), reinterpret_cast<void*>(target));
}

void hooking::qjmp(void* place, void* target) {
	DWORD old_protect{};
	VirtualProtect(place, 5, PAGE_EXECUTE_READWRITE, &old_protect);
	memory::write<uint8_t>((uintptr_t)place, 0xE9);
	*(uint32_t *)((uint32_t)place + 1) = (uint32_t)target - (uint32_t)place - 5;
	VirtualProtect(place, 5, old_protect, &old_protect);
}

void hooking::qjmp(const size_t place, const size_t target) {
	qjmp(reinterpret_cast<void*>(place), reinterpret_cast<void*>(target));
}

bool hooking::qdetour(void* place, void* target) {
	if (MH_CreateHook(place, target, NULL) != MH_OK)
	{
		return false;
	}
	if (MH_EnableHook(place) != MH_OK)
	{
		return false;
	}
	return true;
}