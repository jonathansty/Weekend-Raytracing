#pragma once

class ScopedTimer
{
public:
	ScopedTimer(const char* inMsg) : msg(inMsg)
	{
		t0 = m_timer.now();
	}
	~ScopedTimer()
	{
		t1 = m_timer.now();
		std::cout << msg << "( " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms)." << std::endl;
	}

private:
	const char* msg;

	using timepoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
	timepoint t0;
	timepoint t1;
	std::chrono::high_resolution_clock m_timer;

};



