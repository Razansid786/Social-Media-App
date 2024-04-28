#ifndef DATE_HPP
#define DATE_HPP


class Date {
private:
    int day;
    int month;
    int year;

public:
    // Constructor
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}

    // Getters
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // Setters
    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }
};

#endif /* DATE_HPP */
