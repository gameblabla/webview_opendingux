#include <QApplication>
#include <QUrl>
#include <QWebFrame>
#include <QWebView>
#include <QScreen>
#include <QKeyEvent>
#include <QShortcut>
#include <QMainWindow>
#include <QBoxLayout>
#include <iostream>

class MainWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
	MainWindow(QWidget * parent = 0);
	virtual void keyPressEvent(QKeyEvent *event);
    virtual ~MainWindow();
    QWebView* view;
     QUrl m_url;
     QWidget *m_container;
     QBoxLayout *m_layout;
};
