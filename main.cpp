#include <iostream>
#include <ctime>
#include <string>

namespace Calendar{
	class DayOfWeek{
		static const uint8_t countDays = 7;

		enum class DayName{
			Monday = 1,
			Tuesday,
			Wednesday, // 3
			Thursday,
			Friday,
			Saturday,  
			Sunday     // 7
		};
		static std::string enumToStr(DayName name){
			switch(name){
				case DayName::Monday:return"Monday";
				case DayName::Tuesday:return"Tuesday";
				case DayName::Wednesday:return"Wednesday";
				case DayName::Thursday:return"Thursday";
				case DayName::Friday:return"Friday";
				case DayName::Saturday:return"Saturday";
				case DayName::Sunday:return"Sunday";
			}
		}
		static DayName intToEnum(int val){
			switch(val){
				case 1: return DayName::Monday;
				case 2: return DayName::Tuesday;
				case 3: return DayName::Wednesday;
				case 4: return DayName::Thursday;
				case 5: return DayName::Friday;
				case 6: return DayName::Saturday;
				case 7: return DayName::Sunday;
			}
			return DayName::Saturday;
		}

		DayName day;

	public:
		DayOfWeek(int d = 1): day( intToEnum(d) ){}

		operator DayName() {return day;}
		int number() const {return static_cast<int>(day);}	

		DayOfWeek& operator=  (const DayOfWeek& d) {day = d.day; return *this;}
		DayOfWeek& operator=  (int d) {day = intToEnum(d); return *this;}
		DayOfWeek& operator+=  (int s) {
			day = intToEnum( (static_cast<int>(day) - 1 + s%countDays + countDays)%countDays + 1);
			return *this;
		}
		DayOfWeek& operator-=  (int s) {return operator +=(-s);}
		DayOfWeek& operator++ () {return operator +=(1);}
		DayOfWeek& operator-- () {return operator -=(1);}
		DayOfWeek operator+ (int s) const {DayOfWeek curD(*this);return curD+=s;}
		DayOfWeek operator-  (int s) const {return operator+(-s);}
		
		friend std::ostream& operator<< (std::ostream &out, const DayOfWeek &D){
			return out<<enumToStr(D.day);
		}
	};

	class Month{
		static const uint8_t countMonths = 12;

		enum class MonthName{
			January = 1,
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
			December // 12
		};

		static std::string enumToStr(MonthName name){
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
		static MonthName intToEnum(int val){
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
		Month(int m = 1): month( intToEnum(m) ){}

		operator MonthName() {return month;}
		int number() const {return static_cast<int>(month);}	

		Month& operator=  (const Month& m) {month = m.month; return *this;}
		Month& operator=  (int m) {month = intToEnum(m); return *this;}

		Month& operator+= (int sh) {
			month = intToEnum( (static_cast<int>(month) - 1 + sh%countMonths + countMonths)%countMonths + 1);
			return *this;
		}
		Month& operator-= (int sh) {return operator+=(-sh);}
		Month& operator++ () {return operator+=(1);}
		Month& operator-- () {return operator-=(1);}
		Month operator+ (int s) const {Month curM(*this);return curM+=s;}
		Month operator- (int s) const{return operator+(-s);}
		

		friend std::ostream& operator<< (std::ostream &out, const Month &M){
			return out<<enumToStr(M.month);
		}

		int countDays(bool vis = false) const{
			switch(month){
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
	
	static inline bool isLeapYear(uint16_t year){
		return year%4 == 0 && (year%100 != 0 || year%400 == 0);
	}
	
	class Date
	{
	private:
		Date(uint16_t d, uint16_t m, uint16_t y, uint16_t dow):year(y), month(m), day(d){
			if(month.countDays(isLeapYear(year)) < day)
				day = month.countDays(isLeapYear(year));
			if(dow>0)
				day_of_week = dow;
			else
				day_of_week = (getPivotDate().day_of_week + dateDiff(getPivotDate()));
		}
			
	public:
		Date(){operator=(Calendar::Date::getNowDate());}
		Date(uint16_t d, uint16_t m, uint16_t y):Date(d,m,y,0){}
		
		Date shiftDay(const int days) const{
			int shift = days;
			Date nextDate(*this);
			while(shift > 0){
				int Mlim = nextDate.month.countDays(isLeapYear(nextDate.year));
				if(nextDate.day + shift > Mlim){
					shift = shift - Mlim + nextDate.day - 1; 
					nextDate.day = 1;
					if(nextDate.month.number() != 12)
						nextDate.month = nextDate.month+1;
					else{
						nextDate.month = 1;
						nextDate.year+=1;
					}
				} else {
					nextDate.day +=shift;
					shift = 0;
				}
			}
			while(shift < 0){
				if(nextDate.day + shift < 1){
					shift += nextDate.day; 
					if(nextDate.month.number() != 1)
						nextDate.month = nextDate.month-1;
					else{
						nextDate.month = 12;
						nextDate.year-=1;
					}
					nextDate.day = nextDate.month.countDays(isLeapYear(nextDate.year));
				} else {
					nextDate.day +=shift;
					shift = 0;
				}
			}

			nextDate.day_of_week = nextDate.day_of_week + ((days>0)?1:-1)*(dateDiff(nextDate));

			return nextDate;
		}

		int toDays() const { // from 1900 years;
			int days = 0;
			int countLeap = 0;
			for(int i = 1900; i<year; i+=4)
				countLeap += isLeapYear(i);
			days += countLeap*366 + (year - 1900 - countLeap)*365;

			bool leap = isLeapYear(year);
			for(int i = 1; i<month.number(); i++)
				days += Month(i).countDays(leap);

			days += day;	
			return days;
		}

		int dateDiff(const Date& right) const{
			int diff = toDays() - right.toDays();
			return (diff>0)?diff:-diff;
		}

		void print() const {
			std::cout<<day_of_week<<" "<<day<<" "<<month<<" "<<year<<std::endl;
		}

		friend std::ostream& operator<< (std::ostream &out, const Date &D){
			return out<<D.day_of_week<<" "<<D.day<<" "<<D.month<<" "<<D.year;
		}


		static Date getPivotDate(){
			return Date(1,1,1900,1); // 1 January - Monday
		}

		static Date getNowDate(){
			std::time_t t = std::time(nullptr);   // get time now
			std::tm* now = std::localtime(&t);
			Date now_date(now->tm_mday,now->tm_mon+1,(now->tm_year + 1900));
			return now_date;
		}
		
		Month month;
		
		class Iterator{
			Date* date;
		public:
			Date& operator*() {return *date;}

			Iterator& operator+= (int sh){
				*date = date->shiftDay(sh);
				return *this;
			}
			Iterator& operator-= (int sh){return operator+=(-sh);}
			Iterator& operator++ (){return operator+=(1);}
			Iterator& operator-- (){return operator-=(1);}

			Iterator operator+ (int sh) const {
				Iterator curI;
				*(curI.date) = *(this->date);
				return curI+=sh;
			}
			Iterator operator- (int sh) const {return operator+(-sh);}
		};
	private:
		uint16_t year;
		uint16_t day;
		DayOfWeek day_of_week;
	};
};

using std::cout;
using std::endl;
inline void LINE(){cout<<endl;}

int main() {
	LINE();
	Calendar::Date cur;
	cout<<"Today: "<<cur<<endl;
	LINE();


	Calendar::Date d1(6,9,2002);
	cout<<"My birthday: ";d1.print();
	LINE();

	Calendar::Date d2(1,1,2000);
	d2.print();
	cout<<d2<<" + 365*5 days: "<<d2.shiftDay(365*5)<<endl;
	cout<<d2<<" + 2 days: "<<d2.shiftDay(2)<<endl;
	cout<<d2<<" - 360 days: "<<d2.shiftDay(-360)<<endl;
	LINE();

	Calendar::Date d3(1,2,1900);
	cout<<d3<<" "<<d3.toDays()<<endl<<endl;

	LINE();
	cout<<"---------------------------------------------------"<<endl;
}