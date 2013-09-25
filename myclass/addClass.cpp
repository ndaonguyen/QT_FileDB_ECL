#include "addClass.h"

AddClass::AddClass( QWidget * parent, Qt::WindowFlags f )
		: QDialog(parent, f)
{
	setupUi(this);
	
}

AddClass::~AddClass(void)
{


}

void AddClass::setConnection()
{
	QObject::connect(ui.classComboBox, SIGNAL(activated(QString)),
					this, SLOT(courseComboAction(QString)));
	QObject::connect(ui.saveButton_2, SIGNAL(clicked()),
					this, SLOT(saveClassAction()));
	QObject::connect(ui.cancelButton, SIGNAL(clicked()),
					this, SLOT(cancelClassAction()));

	QObject::connect(ui.enableClass1Button, SIGNAL(clicked()),
					this, SLOT(enableClassInfoAction()));
	QObject::connect(ui.enableClass2Button, SIGNAL(clicked()),
					this, SLOT(enableMemberAction()));
	QObject::connect(ui.enableClass3Button, SIGNAL(clicked()),
					this, SLOT(enableCourseAction()));
}
