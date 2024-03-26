#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QtWidgets>
#include <QtCore/QTextCodec>

#define CODEC_TR "UTF8"
#define OS "Unrecognized OS"

#if defined Q_OS_UNIX
#define CODEC_LOCALE "KOI8R"
#define OS "Unix"
#elif defined Q_OS_WIN
#define CODEC_LOCALE "UTF8"
#define OS "Windows"
//-----------------------------------
#elif defined Q_OS_YOUR_OS_DEFINITION
#define CODEC_LOCALE "YOUR_OS_LOCALE"
#define OS "Your OS name"
#endif
//-----------------------------------

#include "../engine/generator.h"
#include <fstream>
#include <sstream>
#include <algorithm>

const char name[]	="Генерило v1.0b";
const char copyright[]	="(c) 2007-2019 by Ighor Poteryakhin\nighor@ighor.ru";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    QListWidget *listbox;
    QTextEdit *line;
    QLineEdit *minlen;
    QLineEdit *maxlen;
    QLineEdit *maxcount;
    QStatusBar *stat;
    QCheckBox *shuffle;

private slots:
    void go();
    void restrict();
    void save();
    void clpbrd();
    void about();
    void status(QListWidgetItem *item);

private:
    void setupMenus();
    void setupWidgets();
    void updateList();
    Result r;

protected:
    void closeEvent(QCloseEvent *event);

};

#endif
