#pragma once

namespace df {

	class Clock {

	private:
		long long m_previous_time; // Last call to delta() in ?s

	public:
		Clock();

		// Returns elapsed time in ?s, then resets
		long long delta();

		// Returns elapsed time in ?s without resetting
		long long split() const;
	};

}