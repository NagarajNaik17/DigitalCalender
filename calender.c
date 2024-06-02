#include <stdio.h>
#include <time.h>

const char* weekDays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* monthNames[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int getStartingDayOfMonth(int year, int month) {
    struct tm timeInfo = {0};
    timeInfo.tm_year = year - 1900;
    timeInfo.tm_mon = month - 1;
    timeInfo.tm_mday = 1;
    mktime(&timeInfo);
    return timeInfo.tm_wday;
}

int main() {
    int year;

    time_t currentTime;
    struct tm* localTimeInfo;

    time(&currentTime);
    localTimeInfo = localtime(&currentTime);

    int currentYear = localTimeInfo->tm_year + 1900;

    printf("\nEnter the year: ");
    scanf("%d", &year);

    int isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    printf("\n+----------------------------------------------------+");
    printf("\n|         CURRENT DATE    %s %02d %s %d         |", weekDays[localTimeInfo->tm_wday], localTimeInfo->tm_mday, monthNames[localTimeInfo->tm_mon + 1], currentYear);
    printf("\n|              CURRENT TIME %02d:%02d:%02d                 |", localTimeInfo->tm_hour, localTimeInfo->tm_min, localTimeInfo->tm_sec);
    printf("\n+----------------------------------------------------+\n");

    printf("\n+----------------------------------------------------+");
    printf("\n|               CALENDAR OF %d                     |", year);
    printf("\n+----------------------------------------------------+\n");

    for (int month = 1; month <= 12; month++) {
        int daysInMonth = (month == 2 && isLeapYear) ? 29 : (month == 2 ? 28 : (month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31);
        int startingDay = getStartingDayOfMonth(year, month);

        printf("\n\n%s %d\n", monthNames[month], year);
        printf("+-----------------------------------------+\n");
        printf("| Sun   Mon   Tue   Wed   Thu   Fri   Sat |\n");
        printf("+-----------------------------------------+\n");

        int currentDay = 1;

        for (int week = 0; week < 6; week++) {
            printf("|");

            for (int weekday = 0; weekday < 7; weekday++) {
                if (week == 0 && weekday < startingDay) {
                    printf("     ");
                } else if (currentDay <= daysInMonth) {
                    printf(" %3d ", currentDay);
                    currentDay++;
                } else {
                    printf("     ");
                }

                printf("|");
            }

            printf("\n");
        }

        printf("+-----------------------------------------+\n");
    }

    return 0;
}
