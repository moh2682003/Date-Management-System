#include <iostream>

using namespace std;

long long ReadPostiveNumber(string Massage)
{
	long long Number;
	do
	{
		cout << Massage;
		cin >> Number;
	} while (Number < 0);
	return Number;
}


string ConverNumberToText(long long  Number)
{
	if (Number == 0)
	{
		return "";
	}
	if (Number >= 1 && Number <= 19)
	{
		string Arr[] = { "" , "One" , "Tow" , "Three" , "Four" , "Five" , "Six" , "Seven" , "Eight" , "Nine" , "Ten",
		"Eleven", "Twelve" , "Thirteen" , "Fourteen" ,"Fifteen" , "Sixteen" , "Seventeen" , "Eighteen" , "Nineteen" };

		return Arr[Number];
	}
	if (Number >= 20 && Number <= 99)
	{
		string Arr1[] = { "" , "" , "Twenty" , "Thirty" , "Forty" , "Fifty" , "Sixty" , "Seventy" , "Eighty", "Ninty" };
		return Arr1[Number / 10] + " " + ConverNumberToText(Number % 10);
	}
	if (Number >= 100 && Number <= 199)
	{
		return "OneHundred "  + ConverNumberToText(Number % 100);
	}
	if (Number >= 200 && Number <= 999)
	{
		return ConverNumberToText(Number / 100) + "Hundred " + ConverNumberToText(Number % 100);
	}
	if (Number >= 1000 && Number <= 1999)
	{
		return "OneThousand " + ConverNumberToText(Number % 1000);
	}
	if (Number >= 2000 && Number <= 999999)
	{
		return ConverNumberToText(Number / 1000) + "Thousands " + ConverNumberToText(Number % 1000);
	}
	if (Number >= 1000000 && Number <= 1999999)
	{
		return "OneMillion " + ConverNumberToText(Number % 1000000);
	}
	if (Number >= 2000000 && Number <= 999999999)
	{
		return ConverNumberToText(Number / 1000000) + "Million " + ConverNumberToText(Number % 1000000);
	}
	if (Number >= 1000000000 && Number <= 1999999999)
	{
		return "OneBillion" + ConverNumberToText(Number % 1000000000);
	}
	if (Number >= 2000000000 && Number <= 999999999999)
	{
		return ConverNumberToText(Number / 1000000000) + "Billion " + ConverNumberToText(Number % 1000000000);
	}

}


int main()
{
	long long Number = ReadPostiveNumber("Enter Postive Number: ");
	cout << ConverNumberToText(Number);
	cout << endl << endl << endl;
	system("pause");
}