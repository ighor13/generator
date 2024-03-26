#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

#ifndef CODEC_LOCALE
#error Your OS locale is undefined! Check mainwindow.h and add your OS and locale.
#endif

    QTextCodec *codecTr = QTextCodec::codecForName(CODEC_TR);
    QTextCodec *codecLocale = QTextCodec::codecForName(CODEC_LOCALE);
    QTextCodec *codecCStrings = QTextCodec::codecForName(CODEC_LOCALE);
    //QTextCodec::setCodecForTr(codecTr);
    QTextCodec::setCodecForLocale(codecLocale);
    //QTextCodec::setCodecForCStrings(codecCStrings);

    setupMenus();
    setupWidgets();
}


void MainWindow::setupMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Файл"));

    QAction *saveAction = fileMenu->addAction(tr("&Сохранить..."));
    saveAction->setShortcut(QKeySequence(tr("Ctrl+S")));

    QAction *clpbrdAction = fileMenu->addAction(tr("&Копировать в Clipboard..."));
    clpbrdAction->setShortcut(QKeySequence(tr("Ctrl+C")));

    QAction *exitAction = fileMenu->addAction(tr("&Выход!"));
    exitAction->setShortcut(QKeySequence(tr("Ctrl+Q")));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Помощь"));
    QAction *aboutAction = helpMenu->addAction(tr("&О Программе..."));
    aboutAction->setShortcut(QKeySequence(tr("Ctrl+B")));

    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(clpbrdAction, SIGNAL(triggered()), this, SLOT(clpbrd()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::setupWidgets()
{
    QPushButton *gobutton=new QPushButton(tr("Нагенерить"));
    QPushButton *savebutton=new QPushButton(tr("Сохранить в файл"));
    QPushButton *clpbrdbutton=new QPushButton(tr("В Clipboard"));
    QPushButton *restrictbutton=new QPushButton(tr("Ограничить"));
    restrictbutton->setMaximumWidth(100);

    connect(gobutton, SIGNAL(clicked()), this, SLOT(go()));
    connect(savebutton, SIGNAL(clicked()), this, SLOT(save()));
    connect(clpbrdbutton, SIGNAL(clicked()), this, SLOT(clpbrd()));
    connect(restrictbutton, SIGNAL(clicked()), this, SLOT(restrict()));

    listbox = new QListWidget();

    connect(listbox, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(status(QListWidgetItem*)));
    connect(listbox, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(status(QListWidgetItem*)));
 	

    line=new QTextEdit;
    line->setText(tr("[Лучшее|Отличное|Прекрасное] решение для { и |[мелкого|малого]|среднего|крупного} бизнеса."));
    line->selectAll();

    line->setMinimumHeight(50);
    line->setMaximumHeight(70);
    stat=new QStatusBar;

    QGroupBox *subframe = new QGroupBox(tr("После генерации"));
    QLabel *minlentext=new QLabel(tr("Мин. строка"));
    QLabel *maxlentext=new QLabel(tr("Макс. строка"));
    QLabel *maxcounttext=new QLabel(tr("Строк не более"));
    shuffle = new QCheckBox(tr("Перемешать"));
    shuffle->setCheckState(Qt::Checked);
    minlen=new QLineEdit("10");
    minlen->setInputMask("00009");
    maxlen=new QLineEdit("200");
    maxlen->setInputMask("00009");
    maxcount=new QLineEdit("2500");
    maxcount->setInputMask("0000009");
    QHBoxLayout *vbox = new QHBoxLayout;
    vbox->addWidget(minlentext);
    vbox->addWidget(minlen);
    vbox->addWidget(maxlentext);
    vbox->addWidget(maxlen);
    vbox->addWidget(maxcounttext);
    vbox->addWidget(maxcount);
    vbox->addWidget(shuffle);
    vbox->addWidget(restrictbutton);
    subframe->setLayout(vbox);

    QFrame *frame = new QFrame;
    QGridLayout *layout = new QGridLayout(frame);
    layout->setMargin (0);
    layout->addWidget(line, 0, 0);
    layout->addWidget(gobutton, 0, 1);
    layout->addWidget(savebutton, 0, 2);
    layout->addWidget(clpbrdbutton, 0, 3);
    layout->addWidget(subframe, 1, 0, 1, 4);
    layout->addWidget(listbox, 2, 0, 1, 4);
    layout->addWidget(stat, 3, 0, 1, 4);
    setCentralWidget(frame);


    setWindowTitle(tr(name));
    setWindowIcon(QPixmap(":/images/logo.png"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Выйти"),
                                    tr("Вы уверены?"),
                                    QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
	event->accept();
    else
	event->ignore();

}

void MainWindow::save()
{

    QString fileName = QFileDialog::getSaveFileName(this,tr("SaveToFile"),"",tr("All Files (*);;Text Files (*.txt)"));
    if (fileName.length()!=0)
        try
        {
            ofstream outfile(fileName.toLocal8Bit().data());
            for(Result::iterator i=r.begin();i!=r.end();i++)
      	        outfile<<(*i)<<endl;
	}
	catch(ios_base::failure &var)
	{
    	    QMessageBox::critical(this, "Error!", tr((char*)var.what()), QMessageBox::Abort);
	}
}

void MainWindow::clpbrd()
{

        QString text;
        for(Result::iterator i=r.begin();i!=r.end();i++)
	{
  	    text+=i->c_str();
	    text+="\n";
	}

	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(text);	
}

void MainWindow::updateList()
{
    listbox->clear();
    for(Result::iterator i=r.begin();i!=r.end();i++)
	{
	    QString s=(*i).c_str();
        listbox->addItem(s.toUtf8());
	}
	ostringstream s;
    s<<"Строк: "<<r.size();
	stat->showMessage(tr(s.str().c_str()));
}

void MainWindow::go()
{
    string s=line->toPlainText().toLocal8Bit().data();

    for(unsigned register int i=0;i<=s.length();i++)
        if (s[i]=='\n')
	    s.erase(i,1);

    if(s.length()!=0)
    {
    	try
    	{
            r=generate(s);
    	}
   	catch (const char* err)
    	{
    	    QMessageBox::critical(this, "Error!", tr(err), QMessageBox::Abort);
        }
        updateList();
    }
}

void MainWindow::about()
{
    QString content=copyright;
    content+="\n";
    content+=OS;
#if defined(Q_PROCESSOR_X86_32)
    content+="/x86_32";
#elif defined(Q_PROCESSOR_X86_64)
    content+="/x86_64";
//#else
#endif
    content+="/QT ";
    content+=QT_VERSION_STR;

    QMessageBox::information(this, tr(name) , tr(content.toLocal8Bit().data()));
}

void MainWindow::restrict()
{

	Result newres;

//    QString s=(*i).c_str();
//    listbox->addItem(s.toUtf8());

    //minlen
        for(Result::iterator i=r.begin();i!=r.end();i++)
//            if(i->length()>=minlen->text().toUInt() )
        {
            QString s=(*i).c_str();
            if(s.length()>=minlen->text().toUInt())
                newres.push_back(*i);
        }
        r=newres;
//maxlen
	newres.clear();
        for(Result::iterator i=r.begin();i!=r.end();i++)
//            if(i->length()<=maxlen->text().toUInt() )
        {
            QString s=(*i).c_str();
            if(s.length()<=maxlen->text().toUInt())
                newres.push_back(*i);
        }
        r=newres;
//shuffle

	if(shuffle->checkState()==Qt::Checked)
	    random_shuffle(r.begin(),r.end());

//maxcount
	newres.clear(); unsigned c=0;
        for(Result::iterator i=r.begin();i!=r.end()&&c<maxcount->text().toUInt();i++,c++)
	    newres.push_back(*i);
        r=newres;

        updateList();
        
}

void MainWindow::status(QListWidgetItem *item)
{
	ostringstream s;
	s<<"Строк: "<<r.size()<<", Длина текущей строки: "<<item->text().length();
	stat->showMessage(tr(s.str().c_str()));
}
