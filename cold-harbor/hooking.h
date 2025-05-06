#pragma once
#include <MinHook.h>
#include <stdexcept>

namespace hooking
{
	class detour {
	public:
		detour() = default;
		void create(void* place, void* target);
		void create(const size_t place, void* target);

		void clear();
		void enable() const;
		void disable() const;
		~detour();
		detour(const size_t place, void* target);
		detour(void* place, void* target);

		template <typename T>
		T* get() const
		{
			return static_cast<T*>(this->get_original());
		}

		template <typename T = void, typename... Args>
		T invoke(Args ... args)
		{
			return static_cast<T(*)(Args ...)>(this->get_original())(args...);
		}

		[[nodiscard]] void* get_original() const;
	private:
		void* place_{};
		void* original_{};
	};

	void qmov(void* place, void* target);
	void qmov(const size_t place, const size_t target);

	void qjmp(void* place, void* target);
	void qjmp(const size_t place, const size_t target);

	void nop(void* place, size_t length);
	void nop(size_t place, size_t length);

	void copy(void* place, const void* data, size_t length);
	void copy(size_t place, const void* data, size_t length);

	bool qdetour(void* place, void* target);

	bool is_relatively_far(const void* pointer, const void* data, int offset = 5);

	void call(void* pointer, void* data);
	void call(size_t pointer, void* data);

	template <typename T>
	static void set(void* place, T value)
	{
		DWORD old_protect;
		VirtualProtect(place, sizeof(T), PAGE_EXECUTE_READWRITE, &old_protect);

		*static_cast<T*>(place) = value;

		VirtualProtect(place, sizeof(T), old_protect, &old_protect);
		FlushInstructionCache(GetCurrentProcess(), place, sizeof(T));
	}

	template <typename T>
	static void set(const size_t place, T value)
	{
		return set<T>(reinterpret_cast<void*>(place), value);
	}

	template <typename T, typename... Args>
	static T invoke(size_t place, Args ... args)
	{
		return static_cast<T(*)(Args ...)>((void*)place)(args...);
	};
};

