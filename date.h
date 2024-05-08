#ifndef DATE_HPP
#define DATE_HPP


class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}

    // Getters
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // Setters
    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }

    int calculateDaysDifference(const Date& otherDate) const {
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        int daysDifference = 0;

        if (year == otherDate.getYear()) {
            if (month == otherDate.getMonth()) {
                daysDifference = otherDate.getDay() - day;
            } else {
                daysDifference += daysInMonth[month - 1] - day; 
                for (int i = month; i < otherDate.getMonth() - 1; ++i) {
                    daysDifference += daysInMonth[i]; 
                }
                daysDifference += otherDate.getDay(); 
            }
        } else {
            daysDifference += daysInMonth[month - 1] - day;
            for (int i = month; i <= 12; ++i) {
                daysDifference += daysInMonth[i - 1]; 
            }
            for (int i = year + 1; i < otherDate.getYear(); ++i) {
                daysDifference += 365;
            }
            for (int i = 1; i < otherDate.getMonth(); ++i) {
                daysDifference += daysInMonth[i - 1];
            }
            daysDifference += otherDate.getDay();
        }

        return daysDifference;
    }
};

#endif /* DATE_HPP */
