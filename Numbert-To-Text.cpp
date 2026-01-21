#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <vector>
#include <string>


using namespace std;

struct stData
{
	short Year;
	short Month;
	short Day;
};

short DiffInDays(stData Date1, stData Date2, bool IncludeDay = false);

stData IncreaseDateByOneDay(stData Date);

int ReadPostiveNumber(string Massage)
{
	int Number;
	do
	{
		cout << Massage;
		cin >> Number;
	} while (Number <= 0);
	return Number;
}

short ReadYear()
{
	short Year;
	cout << "Enter Year: ";
	cin >> Year;
	return Year;
}

short ReadMonth()
{
	short Month;
	cout << "Enter Month: ";
	cin >> Month;
	while (Month < 1 || Month > 12)
	{
		cout << "Out Validation";
		cout << "Please Enter Month from 1 : 12: ";
		cin >> Month;
	}
	return Month;
}

short ReadDay()
{
	short Day;
	cout << "Enter Day: ";
	cin >> Day;
	while (Day < 0 || Day > 31)
	{
		cout << "Out Validation";
		cout << "Enter Day: ";
		cin >> Day;
	}
	return Day;
}

bool CheckLeapYear(short Number)
{
	return ((Number % 400 == 0) || (Number % 4 == 0 && Number % 100 != 0));
}

short NumberOfDaysInYear(short Year)
{
	return CheckLeapYear(Year) ? 366 : 365;
}

short NumberOfHoursInYear(short Year)
{
	return NumberOfDaysInYear(Year) * 24;
}

int NumberOfMinuteInYear(short Year)
{
	return NumberOfHoursInYear(Year) * 60;
}

int NumberOfSecondInYear(short Year)
{
	return NumberOfMinuteInYear(Year) * 60;
}

short NumberOfDyasInMounth(short Month , short Year)
{
	if (Month < 1 || Month > 12)
	{
		return 0;
	}
	
	int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	return (Month == 2) ? (CheckLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
}

short NumberOfHoursInMounth(short Month, short Year)
{
	return NumberOfDyasInMounth(Month, Year) * 24 ;
}

int NumberOfMinutesInMounth(short Month, short Year)
{
	return NumberOfHoursInMounth(Month, Year) * 60;
}

int NumberOfSecondInMounth(short Month, short Year)
{
	return NumberOfMinutesInMounth(Month, Year) * 60;
}

int DayOfWeekOrder(short Day, short Month,short Year )
{
	int A = (14 - Month) / 12;
	int Y = Year - A;
	int M = Month + 12 * A - 2;

	return ((Day + Y) + (Y / 4) - (Y / 100) + (Y / 400) + (31 * M / 12)) % 7;

}

string NameOfMonth(short Month)
{
	string AllMonth[] = { "Jan" , "Feb" , "Mar" , "Apr" , "May" , "Jun" , "Jul" , "Aug" , "Sep" , "Oct" , "Nov" , "Dec" };

	return AllMonth[Month - 1];
}

void PrintMonthCalender(short Month , short Year)
{
	short Current = DayOfWeekOrder(1, Month, Year);
	short Days = NumberOfDyasInMounth(Month, Year);

	printf("-----------------------------%s----------------------------------------", NameOfMonth(Month).c_str());
	printf("\n  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

	short i;

	for ( i = 0; i < Current; i++)
	{
		printf("     ");
	}
	for (int j = 1; j <= Days; j++)
	{
		printf("%5d", j);

		if (++i == 7)
		{
			printf("\n");
			i = 0;
		}
	}
	printf("\n\n");
	

}

void PrintYearCalender(short Year)
{
	printf("\t______________________________________\n");
	printf("\t\tCalender - %d\n", Year);
	printf("\t______________________________________\n");
	for (int i = 1; i <= 12; i++)
	{
		PrintMonthCalender(i, Year);
	}
}

short CountDayFromBeginingYear(stData Date)
{
	short Count = 0;
	int i = 1;
	while (i < Date.Month)
	{
		Count += NumberOfDyasInMounth(i, Date.Year);
		i++;
	}
	return Count + Date.Day;
	
}

stData GetDataFromOrderInYear(short CountDay, short Year)
{
	stData Data;
	short MonthDay;
	short ReminingDay = CountDay;

	Data.Year = Year;
	Data.Month = 1;

	while (true)
	{
		MonthDay = NumberOfDyasInMounth(Data.Month, Year);

		if (MonthDay < ReminingDay)
		{
			ReminingDay -= MonthDay;
			Data.Month++;
		}
		else
		{
			Data.Day = ReminingDay;
			break;
		}
	}
	return Data;
}

int HowManyDaysAdd()
{
	int AddDays;
	cout << "\nHow Many Days Do You Want To Add? ";
	cin >> AddDays;
	return AddDays;
}

stData AddDaysToDate(int AddDay, stData Data)
{
	
	short ReminingDays = AddDay + CountDayFromBeginingYear(Data);
	short MonthDay ;
	Data.Month = 1;

	while (true)
	{
		MonthDay = NumberOfDyasInMounth(Data.Month, Data.Year);

		if (MonthDay < ReminingDays)
		{
			ReminingDays -= MonthDay;
			Data.Month++;

			if (Data.Month > 12) 
			{
				Data.Year++;
				Data.Month = 1;
			}
		}
		else
		{
			Data.Day = ReminingDays;
			break;
		}
	}
	return Data;
}

stData ReadFullData()
{
	stData Data;
	Data.Day = ReadDay();
	Data.Month = ReadMonth();
	Data.Year = ReadYear();
	return Data;
}

bool IsDate1BeforeDate2(stData Date1 , stData Date2)
{
	if (Date1.Year < Date2.Year)
		return true;

	if (Date1.Year == Date2.Year)
	{
		if (Date1.Month < Date2.Month)
			return true;
		if (Date1.Month == Date2.Month)
		{
			if (Date1.Day < Date2.Day)
				return true;
		}
	}
	return false;

}

bool IsDate1EqualDate2(stData Date1, stData Date2)
{
	return (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day);
}

bool IsDate1AfterDate2(stData Date1, stData Date2)
{
	return (!IsDate1BeforeDate2(Date1, Date2) &&
		!IsDate1EqualDate2(Date1, Date2));
}

enum enDateOrder { Before = -1, After = 1 , Equal = 0  };

enDateOrder CompareDate(stData Date1, stData Date2)
{
	if (IsDate1BeforeDate2(Date1, Date2))
		return enDateOrder::Before;
	if (IsDate1AfterDate2(Date1, Date2))
		return enDateOrder::After;
	return enDateOrder::Equal;
}

struct stPeriodsDate 
{
	stData StartDate;
	stData EndDate;
};

bool IsOverLapPeriod(stPeriodsDate Period1, stPeriodsDate Period2)
{
	if (
		CompareDate(Period2.EndDate, Period1.StartDate) == enDateOrder::Before
		||
		CompareDate(Period2.StartDate, Period1.EndDate) == enDateOrder::After
		)
		return false;
	else
		return true;
}

stPeriodsDate ReadPeriodsDate()
{
	stPeriodsDate Periods;
	cout << "Enter Start Date\n";
	Periods.StartDate = ReadFullData();
	cout << "\nEnter End Date\n";
	Periods.EndDate = ReadFullData();
	return Periods;
	
}

short CountPeriodDay(stPeriodsDate Period, bool IncludeLastDay = false)
{
	return DiffInDays(Period.StartDate, Period.EndDate, IncludeLastDay);
}

bool IsDateInPeriod(stPeriodsDate Period, stData Date)
{
	return !(CompareDate(Date, Period.StartDate) == enDateOrder::Before
		|| CompareDate(Date, Period.EndDate) == enDateOrder::After);
}

int CountOverLapDay(stPeriodsDate Period1, stPeriodsDate Period2)
{
	int Period1Length = CountPeriodDay(Period1, true);
	int Period2Length = CountPeriodDay(Period2, true);
	int OverLap = 0;

	if (!IsOverLapPeriod(Period1, Period2))
		return 0;

	if (Period1Length < Period2Length)
	{
		while (IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
		{
			if (IsDateInPeriod(Period1, Period2.StartDate))
				OverLap++;
			Period1.StartDate = IncreaseDateByOneDay(Period1.StartDate);
		}
	}
	else
	{
		while (IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
		{
			if (IsDateInPeriod(Period2, Period1.StartDate))
				OverLap++;
			Period2.StartDate = IncreaseDateByOneDay(Period2.StartDate);
		}
	}
	return OverLap;
}

bool isLastMonthInYear(short Month)
{
	return Month == 12;
}

bool IsLastDayaInMonth(stData Date)
{
	return Date.Day == NumberOfDyasInMounth(Date.Month, Date.Year);
}

stData FixDayInMonth(stData Date)
{
	short DaysInMonth = NumberOfDyasInMounth(Date.Month, Date.Year);
	if (Date.Day > DaysInMonth)
	{
		Date.Day = DaysInMonth;
	}
	return Date;
}

stData IncreaseDateByOneDay(stData Date)
{
	if (IsLastDayaInMonth(Date))
	{
		if (isLastMonthInYear(Date.Month))
		{
			Date.Day = 1;
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Day = 1;
			Date.Month++;
		}
	}
	else
	{
		Date.Day++;
	}
	return Date;
}

stData IncreaseDateByX_Day(stData Date , short Days)
{
	for (short i = 1; i <= Days; i++)
	{
		Date = IncreaseDateByOneDay(Date);
	}
	return Date;
}

stData IncreaseDateByOneWeek(stData Date)
{
	return IncreaseDateByX_Day(Date, 7);
}

stData IncreaseDateByX_Weeks(stData Date, short Weeks)
{
	for (short i = 1; i <= Weeks; i++)
	{
		Date = IncreaseDateByOneWeek(Date);
	}
	return Date;
}

stData IncreaseDateByOneMonth(stData Date)
{
	if (isLastMonthInYear(Date.Month))
	{
		Date.Year++;
		Date.Month = 1;
	}
	else
	{
		Date.Month++;
	}

	Date = FixDayInMonth(Date);
	
	return Date;
}

stData IncreaseDataByX_Months(stData Date, short Months)
{
	for (int i = 1; i <= Months; i++)
	{
		Date = IncreaseDateByOneMonth(Date);
	}
	return Date;
}

stData IncreaseDateByOneYear(stData Date)
{
	Date.Year++;
	Date = FixDayInMonth(Date);
	return Date;
}

stData IncreaseDateByX_Year(stData Date, short Years)
{
	for (int i = 1; i <= Years; i++)
	{
		Date = IncreaseDateByOneYear(Date);
	}
	return Date;
}

stData IncreaseDateByX_YearFaster(stData Date, short Years)
{
	Date.Year += Years;
	Date = FixDayInMonth(Date);
	return Date;
}

stData IncreaseDateByOneDecade(stData Date)
{
	return IncreaseDateByX_YearFaster(Date, 10);
}

stData IncreaseDateByX_Decade(stData Date, short Decade)
{
	for (int i = 1; i <= Decade; i++)
	{
		Date = IncreaseDateByOneDecade(Date);
	}
	return Date;
}

stData IncreaseDateByX_DecadeFaster(stData Date, short Decade)
{
	Date.Year += 10 * Decade;
	Date = FixDayInMonth(Date);
	return Date;
}

stData IncreaseDateByOneCentury(stData Date)
{
	return IncreaseDateByX_DecadeFaster(Date, 10);

}

stData IncreaseDateByOneMillennium(stData Date)
{
	Date.Year += 1000;
	Date = FixDayInMonth(Date);
	return Date;
}

stData DecreaseDateByOneDay(stData Date)
{
	if (Date.Day == 1)
	{
		Date.Month--;
		if (Date.Month == 0)
		{
			Date.Year--;
			Date.Month = 12;
		}
		Date.Day = NumberOfDyasInMounth(Date.Month, Date.Year);
	}
	else
	{
		Date.Day--;
	}
	return Date;
	
}

stData DecreaseDateByX_Days(stData Date, short Days)
{
	for (short i = 1; i <= Days; i++)
	{
		Date = DecreaseDateByOneDay(Date);
	}
	return Date;
}

stData DecreaseDateByOneWeek(stData Date)
{
	return DecreaseDateByX_Days(Date, 7);
}

stData DecreaseDateByX_Weeks(stData Date, short Weeks)
{
	for (short i = 1; i <= Weeks; i++)
	{
		Date = DecreaseDateByOneWeek(Date);
	}
	return Date;
}

stData DecreaseDateByOneMonth(stData Date)
{
	if (Date.Month == 1)
	{
		Date.Year--;
		Date.Month = 12;
		Date = FixDayInMonth(Date);
	}
	else
	{
		Date.Month--;
		Date = FixDayInMonth(Date);
	}
	return Date;
}

stData DecreaseDateByX_Months(stData Date, short Months)
{
	for (short i = 1; i <= Months; i++)
	{
		Date = DecreaseDateByOneMonth(Date);
	}
	return Date;
}

stData DecreaseDateByOneYear(stData Date)
{
	Date.Year--;
	Date = FixDayInMonth(Date);
	return Date;
}

stData DecreaseDateByX_Years(stData Date, short Years)
{
	for (short i = 1 ; i <= Years; i++)
	{
		Date = DecreaseDateByOneYear(Date);
	}
	return Date;
}

stData DecreaseDateByX_YearsFaster(stData Date, short Years)
{
	Date.Year -= Years;
	Date = FixDayInMonth(Date);
	return Date;
}

stData DecreaseDateByOneDecade(stData Date)
{
	Date.Year -= 10;
	Date = FixDayInMonth(Date);
	return Date;
}

stData DecreaseDateByX_Decades(stData Date, short Decades)
{
	for (short i = 1; i <= Decades; i++)
	{
		Date = DecreaseDateByOneDecade(Date);
	}
	return Date;
}

stData DecreaseDateByX_DecadesFaster(stData Date, short Decades)
{
	Date.Year -= Decades * 10;
	Date = FixDayInMonth(Date);
	return Date;
}

stData DecreaseDateByOneCentury(stData Date)
{
	Date.Year -= 100;
	Date = FixDayInMonth(Date);
	return Date;
}

stData DecreaseDateByOneMilleniumYear(stData Date)
{
	Date.Year -= 1000;
	Date = FixDayInMonth(Date);
	return Date;
}

int DayOfWeekOrder(stData Date)
{
	return DayOfWeekOrder(Date.Day , Date.Month , Date.Year);
}

string GetStringDay(int Day)
{
	string Days[7] = { "Sun" , "Mon" ,"Tues" , "Wed" , "Thurs" , "Fri" , "Sat" };

	return Days[Day];
}

bool IsEndOfWeek(string SDay)
{
	return (SDay == "Fri") ? true : false;
}

short  IsWeekEnd(stData Date)
{
	short DayIndex = DayOfWeekOrder(Date);
	return (DayIndex == 5 || DayIndex == 6) ? true : false;
}

short IsBusinessDay(stData Date)
{
	return (!IsWeekEnd(Date)) ? true : false ;
}

short DiffInDays(stData Date1, stData Date2, bool IncludeDay)
{
	int DiffDay = 0;

	if (!IsDate1BeforeDate2(Date1, Date2))
	{
		swap(Date1, Date2);
	}
	while (IsDate1BeforeDate2(Date1, Date2))
	{
		DiffDay++;
		Date1 = IncreaseDateByOneDay(Date1);
	}

	return IncludeDay ? ++DiffDay  : DiffDay ;
}

short DaysUntilOfWeek(int InDay)
{
	return 6 - InDay;
}

short DaysUntilOfMonth1(stData Date)
{
	int Days = NumberOfDyasInMounth(Date.Month, Date.Year);
	return  Days - Date.Day;
}

short DaysUntilOfMonth(stData Date)
{
	stData EndOfMonth;
	EndOfMonth.Day = NumberOfDyasInMounth(Date.Month, Date.Year);
	EndOfMonth.Month = Date.Month;
	EndOfMonth.Year = Date.Year;

	return DiffInDays(Date, EndOfMonth);
}

short DaysUntilOfYear1(stData Date )
{
	short DaysRemin  = NumberOfDaysInYear(Date.Year) - CountDayFromBeginingYear(Date);
	return DaysRemin;
}

short DaysUntilOfYear(stData Date)
{
	stData EndOfYear;
	EndOfYear.Day = 31;
	EndOfYear.Month = 12;
	EndOfYear.Year = Date.Year;

	short Diff =  DiffInDays(Date, EndOfYear);
	return Diff;
}

stData StartVacation()
{
	stData SVacation;
	cout << "Start Vacation\n";
	SVacation = ReadFullData();
	return SVacation;
}

stData EndVacation()
{
	stData EVacation;
	cout << "\nEnd Vacation\n";
	EVacation = ReadFullData();
	return EVacation;
}

short ActualVacation(stData SVacation, stData EVacation)
{
	short VacationDay = 0;
	short Day = DayOfWeekOrder(SVacation);
	while (!IsDate1EqualDate2(SVacation, EVacation))
	{
		if (IsBusinessDay(SVacation))
			VacationDay++;
		Day = (Day + 1) % 7;
		SVacation = IncreaseDateByOneDay(SVacation);
	}
	return VacationDay;
}

stData IncreaseDateByX_DayWithOutWeekendDay(stData Date , short VacationDays)
{
	short i = VacationDays;
	while (i > 0)
	{
		if (IsBusinessDay(Date))
			i--;
		Date = IncreaseDateByOneDay(Date);
	}
	return Date;
}

stData CalculateVacationReturnDate(stData DateFrom, short VacationDays)
{
	short WeekendCounter = 0;

	while (IsWeekEnd(DateFrom))
	{
		DateFrom = IncreaseDateByOneDay(DateFrom);
	}

	for (int i = 1; i <= VacationDays + WeekendCounter; i++)
	{
		if (IsWeekEnd(DateFrom))
			WeekendCounter++;
		DateFrom = IncreaseDateByOneDay(DateFrom);
	}

	while (IsWeekEnd(DateFrom))
	{
		DateFrom = IncreaseDateByOneDay(DateFrom);
	}
	return DateFrom;
}

stData GetSystemDate()
{
	stData Date;
	time_t t = time(nullptr);
	tm now;

	localtime_s(&now, &t);

	Date.Day = now.tm_mday;
	Date.Month = now.tm_mon + 1;
	Date.Year = now.tm_year + 1900;

	return Date;
}

bool ValidateDate(stData Date)
{
	if (Date.Day > 31 || Date.Day < 1)
		return false;
	if (Date.Month == 2)
	{
		if (CheckLeapYear(Date.Year))
		{
			if (Date.Day > 29)
				return false;
		}
		else
		{
			if (Date.Day > 28)
				return false;
		}
	}
	short CheckDays = NumberOfDyasInMounth(Date.Month, Date.Year);
	if (Date.Day > CheckDays)
		return false;
	return true;
}

vector <string> SplitString(string S1, string Delim)
{
	vector <string> Svector;
	string Sword;
	short Pos = 0;

	while ((Pos = S1.find(Delim)) != std::string::npos)
	{
		Sword = S1.substr(0, Pos);
		if (!Sword.empty())
		{
			Svector.push_back(Sword);
		}
		S1.erase(0, Pos + Delim.length());
	}
	if (!S1.empty())
	{
		Svector.push_back(S1);
	}
	return Svector;
}

stData StringToDate(string DateString)
{
	stData Date = {0,0,0};
	vector <string> Vstring = SplitString(DateString, "/");
	
	if (Vstring.size() != 3)
	{
		return Date;
	}
	Date.Day = stoi(Vstring[0]);
	Date.Month = stoi(Vstring[1]);
	Date.Year = stoi(Vstring[2]);

	return Date;
}

string DateToString(stData Date)
{
	return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
}

string ReadDateString(string massage)
{
	string DateString;
	cout << massage;
	getline(cin >>  ws, DateString);
	return DateString;
}

string ReplaceWord(string S1, string StringToReplace, string sReplaceTo)
{
	short Pos = S1.find(StringToReplace);

	while (Pos != std::string::npos)
	{
		S1 = S1.replace(Pos, StringToReplace.length(), sReplaceTo);
		Pos = S1.find(StringToReplace);
	}
	return S1;

}

string FormateData(stData Date, string DateFormate= "dd/mm/yyyy")
{
	string FormateDateString = "";

	FormateDateString = ReplaceWord(DateFormate, "dd", to_string(Date.Day));
	FormateDateString = ReplaceWord(FormateDateString, "mm", to_string(Date.Month));
	FormateDateString = ReplaceWord(FormateDateString, "yyyy", to_string(Date.Year));

	return FormateDateString;

}




int main()
{
	
	system("pause > 0");
}
