#ifdef _WIN32

#ifndef SLICED_TIME_HPP
#define SLICED_TIME_HPP

#include <string>
#include <Windows.h>

namespace Electrux
{
	class SlicedTime
	{
		std::string _day, _month;
		int year, date, h, m, s, day, month;
		void SetIntDM()
		{
			if (_day == std::string("Mon"))
			{
				day = 1;
			}
			if (_day == std::string("Tue"))
			{
				day = 2;
			}
			if (_day == std::string("Wed"))
			{
				day = 3;
			}
			if (_day == std::string("Thu"))
			{
				day = 4;
			}
			if (_day == std::string("Fri"))
			{
				day = 5;
			}
			if (_day == std::string("Sat"))
			{
				day = 6;
			}
			if (_day == std::string("Sun"))
			{
				day = 7;
			}
			if (_month == std::string("Jan"))
			{
				month = 1;
			}
			if (_month == std::string("Feb"))
			{
				month = 2;
			}
			if (_month == std::string("Mar"))
			{
				month = 3;
			}
			if (_month == std::string("Apr"))
			{
				month = 4;
			}
			if (_month == std::string("May"))
			{
				month = 5;
			}
			if (_month == std::string("Jun"))
			{
				month = 6;
			}
			if (_month == std::string("Jul"))
			{
				month = 7;
			}
			if (_month == std::string("Aug"))
			{
				month = 8;
			}
			if (_month == std::string("Sep"))
			{
				month = 9;
			}
			if (_month == std::string("Oct"))
			{
				month = 10;
			}
			if (_month == std::string("Nov"))
			{
				month = 11;
			}
			if (_month == std::string("Dec"))
			{
				month = 12;
			}
		}
		std::string getDayStr()
		{
			if (day == 1)
				return std::string("Mon");
			if (day == 2)
				return std::string("Tue");
			if (day == 3)
				return std::string("Wed");
			if (day == 4)
				return std::string("Thu");
			if (day == 5)
				return std::string("Fri");
			if (day == 6)
				return std::string("Sat");
			if (day == 7)
				return std::string("Sun");
			return std::string("NA");
		}
		std::string getMonthStr()
		{
			if (month == 1)
				return std::string("Jan");
			if (month == 2)
				return std::string("Feb");
			if (month == 3)
				return std::string("Mar");
			if (month == 4)
				return std::string("Apr");
			if (month == 5)
				return std::string("May");
			if (month == 6)
				return std::string("Jun");
			if (month == 7)
				return std::string("Jul");
			if (month == 8)
				return std::string("Aug");
			if (month == 9)
				return std::string("Sep");
			if (month == 10)
				return std::string("Oct");
			if (month == 11)
				return std::string("Nov");
			if (month == 12)
				return std::string("Dec");
			return std::string("NA");
		}
		std::string getTimeStr()
		{
			std::string temp_;
			char _temp_[4];
			temp_.clear();
			_itoa_s(h, _temp_, 10);
			temp_ += _temp_;
			temp_ += ":";
			_itoa_s(m, _temp_, 10);
			temp_ += _temp_;
			temp_ += ":";
			_itoa_s(s, _temp_, 10);
			temp_ += _temp_;
			return temp_;
		}
		std::string getDateStr()
		{
			char _temp[3];
			_itoa_s(date, _temp, 10);
			return std::string(_temp);
		}
		std::string getYearStr()
		{
			char _temp[5];
			_itoa_s(year, _temp, 10);
			return std::string(_temp);
		}
		void SliceHMS(std::string &str)
		{
			std::string temp;
			int curr = 0;
			temp.clear();
			for (auto it = str.begin(); it != str.end(); ++it)
			{
				if (*it == ':')
				{
					if (curr == 1)
					{
						m = atoi(temp.c_str());
						curr++;
					}
					if (curr == 0)
					{
						h = atoi(temp.c_str());
						curr++;
					}
					temp.clear();
				}
				else
				{
					temp += *it;
				}
			}
			s = atoi(temp.c_str());
			temp.clear();
		}
		void SetParam(std::string &str, int &curr)
		{
			if (curr == 0)
			{
				_day = str;
			}
			if (curr == 1)
			{
				_month = str;
			}
			if (curr == 2)
			{
				date = atoi(str.c_str());
			}
			if (curr == 3)
			{
				SliceHMS(str);
			}
			if (curr == 4)
			{
				year = atoi(str.c_str());
			}
		}
		int SliceTime(std::string &__time)
		{
			std::string temp;
			int current = 0;
			temp.clear();
			for (auto it = __time.begin(); it != __time.end(); ++it)
			{
				if (*it == ' ')
				{
					SetParam(temp, current);
					temp.clear();
					current++;
				}
				else if (*it == '\n')
				{
					if (current != 4)
					{
						return 0;
					}
					else
					{
						SetParam(temp, current);
						temp.clear();
					}
				}
				else
				{
					temp += *it;
				}
			}
			SetIntDM();
			return 1;
		}
	public:
		enum Data
		{
			HOURS,
			MINUTES,
			SECONDS,
			DAY,
			DATE,
			MONTH,
			YEAR
		};
		int setTime(std::string &__time)
		{
			return SliceTime(__time);
		}
		int setTime(std::time_t time)
		{
			char __time[30];
			ctime_s(__time, 30, &time);
			return SliceTime(std::string(__time));
		}
		int setTime(int time, int __day = 0, int __date = 0, int __month = 0, int __year = 0)
		{
			setTime(getCurrentRawTime());
			h = time / 100;
			m = time % 100;
			s = 0;
			if (__day > 0 && __day <= 7)
			{
				day = __day;
			}
			if (__date > 0 && __date <= 31)
			{
				date = __date;
			}
			if (__month > 0 && __day <= 12)
			{
				month = __month;
			}
			if (__year > 2015 && __year <= 2050)
			{
				year = __year;
			}
			return 1;
		}
		/*
			Brief:-
				Takes in SlicedTime::Data constants as argument.
		*/
		int getDateTime(int which = SlicedTime::Data::DATE)
		{
			if (which == Data::HOURS)
			{
				return h;
			}
			if (which == Data::MINUTES)
			{
				return m;
			}
			if (which == Data::SECONDS)
			{
				return s;
			}
			if (which == Data::DAY)
			{
				return day;
			}
			if (which == Data::DATE)
			{
				return date;
			}
			if (which == Data::MONTH)
			{
				return month;
			}
			if (which == Data::YEAR)
			{
				return year;
			}
			return -1;
		}
		std::string getFormattedDT()
		{
			std::string temp;
			temp.clear();
			temp = getDayStr();
			temp += " ";
			temp += getMonthStr();
			temp += " ";
			temp += getDateStr();
			temp += " ";
			temp += getTimeStr();
			temp += " ";
			temp += getYearStr();
			return temp;
		}
		/*
			Brief:-
				Returns an std::time_t object to directly feed the current time in setTime function.
		*/
		static std::time_t getCurrentRawTime()
		{
			return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		}
	};
}

#endif // SLICED_TIME_HPP

#endif // _WIN32
