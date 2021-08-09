#include <QApplication>
#include <QUrl>
#include <QWebFrame>
#include <QWebView>
#include <QScreen>
#include <QKeyEvent>
#include <QShortcut>
#include <QMainWindow>
#include <iostream>
#include <QBoxLayout>
#include "main.h"

char* page_load;
int w_width, w_height;

void quit()
{
	qApp->quit();
}

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
//! [1] //! [2]
{
	m_container = new QWidget();
	view = new QWebView();
	
	m_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

	view->page()->mainFrame()->setScrollBarPolicy(
				Qt::Vertical, Qt::ScrollBarAlwaysOff);
	view->page()->mainFrame()->setScrollBarPolicy(
				Qt::Horizontal, Qt::ScrollBarAlwaysOff);
	view->setGeometry(0,0,w_width,w_height);
	view->setFixedSize(w_width,w_height);
	view->load(QUrl::fromLocalFile(page_load));
	
    m_container->setLayout(m_layout);
    m_layout->addWidget(view);
    this->setCentralWidget(m_container);
}


MainWindow::~MainWindow()
//! [1] //! [2]
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{ 
	if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_Home) 
	{
		qApp->quit(); 
	}
}

int main(int argc, char **argv)
{
	
	if (argc < 2) {
		std::cerr << "Please input URL as the last argument\n";
		return 1;
	}

	//view->initialize();
	QApplication app(argc, argv);
	
	app.setOverrideCursor( QCursor( Qt::BlankCursor ) );
	
	QScreen *screen = QGuiApplication::primaryScreen();
	QRect  screenGeometry = screen->geometry();
	w_height = screenGeometry.height();
	w_width = screenGeometry.width();

	page_load = realpath(argv[1], NULL);
	
	MainWindow mainWin;
	#ifdef OPENDINGUX
	mainWin.showFullScreen();
	#else
    mainWin.show();
    #endif


	return app.exec();
}

