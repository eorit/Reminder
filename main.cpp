/*
Для напоминания о приближающихся днях рождениях сотрудников (прошедших с последнего запуска, сегодня, в ближашую неделю, две), с подсчетом возраста,
перечень которых указанн в текстовом файле.

made by Palatov A.M.
*/
//#define _CRT_SECURE_NO_WARNINGS

#include "reminder.h"
#include "widget.h"

#include <QApplication>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <ctime>
#include <clocale>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include <thread>


#include <QLabel>
#include <QWidget>
#include <QLayout>
#include <QString>
#include <QTextBrowser>
#include <QTimer>
#include <QTime>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //=====================================================
    //настройки консоли-язык, шрифт
    //=====================================================

    //WideCharToMultiByte (CP_UTF8, WC_NO_BEST_FIT_CHARS, pszWideSource, nWideLength, pszByteSource, nByteLegth, NULL, NULL);
    //setlocale(LC_ALL, "Russian");
    //SetConsoleCP(CP_UTF8);
    //SetConsoleOutputCP(CP_UTF8);

   /* HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
    wcscpy(fontInfo.FaceName, L"Lucida Console");
    fontInfo.dwFontSize.Y = 16;
    SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
   */ //======================================================


    //значнеия для диапазонов дней
    const int INTERVAL_FIVE_DAYS = 5;
    const int INTERVAL_TWO_WEEK = 14;
    //const int INTERVAL_NEXT_MOUNTH = 30;

    bool first_run_flag = 0;

    //инициализация экземпляров класса
    Date Date_today;
    Date Date_previous(0);

    //инициализация переменной для всех данных
    std::multimap <int, std::string> dbTEMP;

    //чтение даннных из файла
    read_datafile(&dbTEMP);

    //чтение даты последенего запуска
    if (!read_date_of_launch(&Date_previous))
    {
        save_date_of_launch(&Date_today);
        first_run_flag = true;
    };


    //инициализация экземпляров класса для хранение данных необходимого диапазона дней
    Sorted_Database Database_next_five_days(&Date_today, INTERVAL_FIVE_DAYS);
    Sorted_Database Database_next_two_week(&Date_today, INTERVAL_TWO_WEEK);
    Sorted_Database Database_today(&Date_today);
    Sorted_Database_Previous Database_past(&Date_previous, Date_today);


    //инициализация итератора для определения положения текущей даты в "массиве" данных
    std::multimap <int, std::string>::iterator begin;

    //определение положения текущей даты в "массиве" данных
    find_iterator(&dbTEMP, &begin, &Date_today);

    //формированиие "массивов" данных заданного диапазона
    sorter(&dbTEMP, &Database_today, &begin);

    sorter(&dbTEMP, &Database_next_five_days, &begin);

    sorter(&dbTEMP, &Database_next_two_week, &begin);


    //формирование "массива" данных нужного диапазона для прошедшего после предыдущего включения диапазона
    if (check_downtime(&Date_today, &Date_previous)&& !first_run_flag )
    {
        find_iterator(&dbTEMP, &begin, &Date_previous);
        sorter(&dbTEMP, &Database_past, &begin);
    }

    dbTEMP.clear();

    //сохранение текущей даты запуска
    save_date_of_launch(&Date_today);

    //проверка условия вывода-если массивы не пусты и сегодня программа еще не запускалась
    if ((!Database_today.empty() || !Database_next_five_days.empty() || !Database_next_two_week.empty() || !Database_past.empty()) && (!(Date_today==Date_previous)||first_run_flag))
    {

        out_string_stream<<"\nСегодня:\n\n";

        out_string_stream<<( std::string(get_current_day_of_week()))<<" - ";

        out_string_stream<<Date_today.get_string_date();

        Database_past.out_string();

        Database_today.out_string();

        Database_next_five_days.out_string();

        Database_next_two_week.out_string();

        QWidget *window =new QWidget;
        window->setWindowTitle ("Reminder");


        QLabel *cout=new QLabel;
        QFont font = cout->font();
        font.setPixelSize(18);
        cout->setFont (font);
        cout->setText(QString::fromStdString(out_string_stream.str()));
        QHBoxLayout *layout=new QHBoxLayout;

        //==========================
        QTimer *timer=new QTimer;
        QLabel *timer_cout=new QLabel;
        QFont font_timer = timer_cout->font();
        font_timer.setPixelSize(10);
        timer_cout->setFont (font_timer);

        timer->setInterval(1000);
        timer->singleShot(60000, window, SLOT(close()));
        timer->start();

        //============================


        layout->addWidget(cout);
        layout->addWidget(timer_cout);
        window->setLayout(layout);
        window->show();





    }

return a.exec();
}
