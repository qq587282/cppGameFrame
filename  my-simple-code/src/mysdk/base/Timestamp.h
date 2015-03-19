#ifndef MYSDK_BASE_TIMESTAMP_H
#define MYSDK_BASE_TIMESTAMP_H

#include <mysdk/base/Common.h>

#include <string>
using namespace std;

namespace mysdk
{
	///
	/// Time stamp in UTC, in microseconds resolution.
	///
	/// This class is immutable.
	/// It's recommended to pass it by value, since it's passed in register on x64.
	///
	class Timestamp
	{
	public:
		  ///
		  /// Constucts an invalid Timestamp.
		  ///
		Timestamp();
		  ///
		  /// Constucts a Timestamp at specific time
		  ///
		  /// @param microSecondsSinceEpoch
		explicit Timestamp(int64 microSecondsSinceEpoch);
		void swap(Timestamp& that)
		{
			std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
		}
		// default copy/assignment/dtor are Okay
		string toString() const;
		string toFormattedString() const;

		bool valid() const {return microSecondsSinceEpoch_ > 0; }
		  // for internal usage.
		int64 microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }
		  ///
		  /// Get time of now.
		  ///
		static Timestamp now();
		static Timestamp invalid();

		static const int kMicroSecondsPerSecond = 1000 * 1000;
	private:
		int64 microSecondsSinceEpoch_;
	};

	inline bool operator<(Timestamp lhs, Timestamp rhs)
	{
		return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
	}

	inline bool operator>(Timestamp lhs, Timestamp rhs)
	{
		return lhs.microSecondsSinceEpoch() > rhs.microSecondsSinceEpoch();
	}

	inline bool operator<=(Timestamp lhs, Timestamp rhs)
	{
		return lhs.microSecondsSinceEpoch() <= rhs.microSecondsSinceEpoch();
	}

	inline bool operator==(Timestamp lhs, Timestamp rhs)
	{
		return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
	}

	///
	/// Gets time difference of two timestamps, result in seconds.
	///
	/// @param high, low
	/// @return (high-low) in seconds
	/// @c double has 52-bit precision, enough for one-microseciond
	/// resolution for next 100 years.
	inline double timeDifference(Timestamp high, Timestamp low)
	{
		int64 diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
		return static_cast<double> (diff) / Timestamp::kMicroSecondsPerSecond;
	}
	///
	/// Add @c seconds to given timestamp.
	///
	/// @return timestamp+seconds as Timestamp
	///
	inline Timestamp addTime(Timestamp timestamp, double seconds)
	{
		int64 delta = static_cast<int64>(seconds * Timestamp::kMicroSecondsPerSecond);
		return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
	}
}

#endif