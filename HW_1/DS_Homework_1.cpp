#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
unordered_map<int, string> s_month = {{1, "January"}, {2, "Febuary"}, {3, "March"}, {4, "April"}, //map month to its name
                                        {5, "May"}, {6, "June"}, {7, "July"}, {8, "August"}, 
                                        {9, "September"}, {10, "October"}, {11, "November"}, {12, "December"}};
unordered_map<int, int> d_month = {{1, 31}, {2, 28}, {3, 31}, {4, 30}, //map month to its day
                                        {5, 31}, {6, 30}, {7, 31}, {8, 31},
                                        {9, 30}, {10, 31}, {11, 30}, {12, 31}};
unordered_map<int, string> day_week = {{1, "Monday"}, {2, "Tuesday"}, {3, "Wendesday"}, {4, "Thursday"}, //map weekday to its name
                                        {5, "Friday"}, {6, "Saturday"}, {7, "Sunday"}};
class date {
    private:
        int year;
        int month;
        int day;
    public:
        bool is_leap() { //function to determine whether the year is leap year
            if (year % 400 == 0) return true;
            if (year % 100 == 0) return false;
            if (year % 4 == 0) return true;
            return false;
        }
        int day_month(int month) { // return the number of day of the month 
            if (month == 2)
                return is_leap() ? 29 : 28; // if it's leap year than Febuary has 29 days
            return d_month[month];
        }
        bool operator != (const date& a) { //overload != to simplify code
            return (year != a.year) || (month != a.month) || (day != a.day);
        }
        bool operator > (const date& a) { //overload > to simplify code
            if (year != a.year) return year > a.year;
            if (month != a.month) return month > a.month;
            return day > a.day;
        }
        void operator ++ (int) { //overload postfix ++ so the date become next date
            day++;
            if (day > day_month(month)) {
                month++;
                day = 1;
            }                
            if (month > 12) {
                year++;
                month = 1;
            }
        }
        void operator --(int) { //overload postfix -- so the date become previous date
            day--;
            if (day < 1) { //if the day is smaller than 1, than go to previous month
                month--;
                if (month < 1) { //if the month is smaller than 1, than go to previous year
                    year--;                        
                    month = 12;
                }
                day = day_month(month);
            }
        }
        date () {} //default constructor
        date(string input) { //constructor with string parameter(most commonly used in this program)
            year = stoi(input.substr(0, input.find_first_of("/") - 0));
            month = stoi(input.substr(input.find_first_of("/") + 1, input.find_last_of("/") - input.find_first_of("/") - 1));
            day = stoi(input.substr(input.find_last_of("/") + 1 , input.length() - input.find_last_of("/") - 1)); 
        }
        void print_date() { //print the date and WeekOfDay
            cout << s_month[month] << " " << day << ", " << year << " is " << this -> DayOfWeek() << endl;
        }
        void print_sub_date(date a) { // print the result after DateSub
            if (*this > a) {
                a.print_sub_date(*this);
                return;
            }
            cout << DateSub(a) << " " << "days from " << s_month[month] << " " << day << ", " << year <<" to " << s_month[a.month] << " " << a.day << ", " << a.year << endl;
        }
        string DayOfWeek() { //use math formula to calculate the day of week
            int y = this -> year, m = this -> month, d = this -> day;
            if (m == 1 || m == 2) {
                m += 12;
                y--;
            }
            int weekday = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7 + 1;
            return day_week[weekday];
        }
        int DateSub(date a) { //function which calculate number of days start from itself to date a
            if (*this > a) 
                return a.DateSub(*this);
            int n = 0;
            while(*this != a) {
                (*this)++;
                n++;
            }
            return n;
        }
        date DateAdd(int n) { //fuction which calculate the day n days after itself
            date result = *this;
            if (n > 0) { //if n is positive, than use n-- as the conditional statement
                while (n--) 
                    result++;
            }
            else { //if n is nagative, than use n++ as the conditional statement
                while (n++) 
                    result--;
            }
            return result;
        }
        void print_add_date(int x) {
            date date_2 = this -> DateAdd(x);
            cout << abs(x) << " days " << ((x < 0) ? "before " : "after ") << s_month[this -> month] << " " << this -> day <<  ", " << this -> year << 
            " is " << s_month[date_2.month] << " " << date_2.day << " " << date_2.year << endl;
        }
};
int main() {
    string input;
    while(getline(cin, input)) { //get a line as input and store the input in a string
        if (input.find("+") != string::npos) { // if the input contain "+" than do the Date_Add part
            date date_1(input.substr(0, input.find("+") - 1));
            int x = stoi(input.substr(input.find("+") + 2, input.length() - (input.find("+") + 2)));
            date_1.print_add_date(x);
        }
        else if (input.find("-") != string::npos) { // if the input contain "-" than do the Date_Sub part
            date date_1(input.substr(0, input.find("-") - 1));
            date date_2(input.substr(input.find("-") + 2, input.length() - (input.find("-") + 2)));
            date_1.print_sub_date(date_2);
        }
        else { // if the input not contain "+" and "-" than just do the WeekOfDay part
            date date_1(input);
            date_1.print_date();
        }
    }
    return 0;
}