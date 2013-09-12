#include "myclass.h"




MyClass::MyClass(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	setConnection();
	loadConfigAddCourseTab();
	conn = database::connectByC();
	dbFile = new databaseFile();
	loadListCourseTab();
	
	loadOriginConfig();
	loadConfigClass();
	loadDataAddClassTab(0);
	loadListClassTab();
}

MyClass::~MyClass()
{
	database::closeConnectionC(conn);
	delete dbFile;
}
//#include "GeneratedFiles/Debug/moc_myclass.cpp"
