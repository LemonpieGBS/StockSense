#include <ctime>

time_t now = time(0);
tm *ltm = localtime(&now);

void update_timer()
{
    now = time(0);
    ltm = localtime(&now);
}

int get_current_year()
{
    update_timer();
    return (1900 + ltm->tm_year);
}
int get_current_month()
{
    update_timer();
    return (1 + ltm->tm_mon);
}
int get_current_day()
{
    update_timer();
    return (ltm->tm_mday);
}
int get_current_hour()
{
    update_timer();
    return (ltm->tm_hour);
}
int get_current_minute()
{
    update_timer();
    return (ltm->tm_min);
}
int get_current_second()
{
    update_timer();
    return (ltm->tm_sec);
}

int get_unix_year(time_t unix)
{
    ltm = localtime(&unix);
    return (1900 + ltm->tm_year);
}
int get_unix_month(time_t unix)
{
    ltm = localtime(&unix);
    return (1 + ltm->tm_mon);
}
int get_unix_day(time_t unix)
{
    ltm = localtime(&unix);
    return (ltm->tm_mday);
}
int get_unix_hour(time_t unix)
{
    ltm = localtime(&unix);
    return (ltm->tm_hour);
}
int get_unix_minute(time_t unix)
{
    ltm = localtime(&unix);
    return (ltm->tm_min);
}
int get_unix_second(time_t unix)
{
    ltm = localtime(&unix);
    return (ltm->tm_sec);
}