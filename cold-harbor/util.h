#pragma once
#include <functional>
namespace util
{
	bool file_exists(const char* filename);
	const char* get_executable_path();
	void fatal_error(const char* message, ...);

	class on_delete
	{
	public:
		on_delete(std::function<void()> func) : m_func(func) {}
		~on_delete()
		{
			if (m_func)
			{
				m_func();
			}
		}
	private:
		std::function<void()> m_func;
	};
};

