#include <iostream>
#include <ctime>
#include <string>

namespace Date{
	// DECLARE_ENUM(
	// 	DAY,       // enum class DAY

	// 	Sunday,    // DAY::Sunday
	// 	Monday,	   // DAY::Monday ...
	// 	Tuesday,
	// 	Wednesday,
	// 	Thursday,
	// 	Friday,
	// 	Saturday
	// );
	class DayOfWeek{
		static const uint8_t countDays = 7;

		enum class DayName{
			Sunday = 1,
			Monday = 2,
			Tuesday = 3,
			Wednesday = 4,
			Thursday = 5,
			Friday = 6,
			Saturday = 7
		};
		std::string enumToStr(DayName name){
			switch(name){
				case DayName::Sunday:return"Sunday";
				case DayName::Monday:return"Monday";
				case DayName::Tuesday:return"Tuesday";
				case DayName::Wednesday:return"Wednesday";
				case DayName::Thursday:return"Thursday";
				case DayName::Friday:return"Friday";
				case DayName::Saturday:return"Saturday";
			}
		}
		DayName intToEnum(int val){
			switch(val){
				case 1: return DayName::Sunday;
				case 2: return DayName::Monday;
				case 3: return DayName::Tuesday;
				case 4: return DayName::Wednesday;
				case 5: return DayName::Thursday;
				case 6: return DayName::Friday;
				case 7: return DayName::Saturday;
			}
			return DayName::Saturday;
		}

		DayName day;

		public:
			operator DayName() {return day;}
			operator std::string() {return enumToStr(day);}

			DayOfWeek& operator=  (int d) {day = intToEnum(d); return *this;}
			DayOfWeek& operator+  (int s) {day = intToEnum( (static_cast<int>(day) - 1 + s)%countDays + 1); return *this;}
			DayOfWeek& operator-  (int s) {day = intToEnum( (static_cast<int>(day) - 1 - s%countDays + countDays)%countDays + 1); return *this;}
			DayOfWeek& operator++ ()      {return operator+(1);}
			DayOfWeek& operator-- ()      {return operator-(1);}
	};

	class Month{
		enum class MonthName{
			January,
			February,
			March,
			April,
			May,
			June,
			July,
			August,
			September,
			October,
			November,
			December
		};
		std::string enumToStr(MonthName name){
			switch(name){
				case MonthName::January:return"January";
				case MonthName::February:return"February";
				case MonthName::March:return"March";
				case MonthName::April:return"April";
				case MonthName::May:return"May";
				case MonthName::June:return"June";
				case MonthName::July:return"July";
				case MonthName::August:return"August";
				case MonthName::September:return"September";
				case MonthName::October:return"October";
				case MonthName::November:return"November";
				case MonthName::December:return"December";
			}
		}
		MonthName intToEnum(int val){
			switch(val){
				case 1: return MonthName::January;
				case 2: return MonthName::February;
				case 3: return MonthName::March;
				case 4: return MonthName::April;
				case 5: return MonthName::May;
				case 6: return MonthName::June;
				case 7: return MonthName::July;
				case 8: return MonthName::August;
				case 9: return MonthName::September;
				case 10: return MonthName::October;
				case 11:return MonthName::November;
				case 12:return MonthName::December;
			}
			return MonthName::December;
		}

		MonthName month;

		public:
			Month& operator= (const int & m) {month = intToEnum(m); return *this;}
			operator MonthName() {return month;}
			operator std::string() {return enumToStr(month);}	

			int monthLimit(MonthName name, bool vis = false){
				switch(name){
						case MonthName::January:
						case MonthName::March:
						case MonthName::May:
						case MonthName::July:
						case MonthName::August:
						case MonthName::October:
						case MonthName::December: return 31;
						case MonthName::September:
						case MonthName::April:
						case MonthName::June:
						case MonthName::November: return 30;
						case MonthName::February: return 28 + vis;
				}
			}
	};


	
	

	class Date
	{
	public:    
		Date(unsigned short d, unsigned short m, unsigned short y):year(y), month(m), day(d){}
		
		bool isCorrect() const;

		static Date getNowDate();
	private:
		unsigned short year;
		Month month;
		unsigned short day;
		DAY day_of_week;
	};

	bool Date::isCorrect() const{

		return true;
	}

	Date Date::getNowDate()
	{
		std::time_t t = std::time(nullptr);   // get time now
		std::tm* now = std::localtime(&t);
		Date now_date(now->tm_mday,now->tm_mon+1,(now->tm_year + 1900));
		return now_date;
	}
};

int main() {
  std::cout << "Hello World!\n";
}
