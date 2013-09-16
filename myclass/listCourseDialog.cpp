#include <QtGui>
#include "listCourseDialog.h"

listCourseDialog::listCourseDialog(QWidget *parent,databaseFile *dbFile, QString courseId)
	: QDialog(parent)
{
	QVBoxLayout *topLeftLayout = new QVBoxLayout;
	QList< QMap<QString,QString> > coSkList = dbFile->getListByField("course_skill", "course_id", courseId);
	int numRow = coSkList.count();
	if(numRow >0)
	{
		for(int i=0;i<numRow;i++)
		{
			QString skillID   = coSkList.at(i)["skill_id"];
			QList< QMap<QString,QString> > skillList = dbFile->getListByField("skill", "id",skillID);
			QString skillName = skillList.at(0)["name"];
			QLabel *skill = new QLabel("<b>"+skillName+"</b>");
			topLeftLayout->addWidget(skill);
			
			QList<QString> fields;
			QList<QString> fieldValues;
			fields << "skill_id" << "course_id";
			fieldValues << skillID << courseId;

			QList< QMap<QString,QString> > skMaList = dbFile->getListByFields("skill_material",fields, fieldValues);
			QListWidget *materialList = new QListWidget();
			int numSkMa = skMaList.count();
			for(int i =0;i<numSkMa;i++)
			{
				QString matId = skMaList.at(i)["material_id"];
				QList< QMap<QString,QString> > matList = dbFile->getListByField("material", "id", matId );
				materialList->addItem(matList.at(0)["name"]);
			}
			topLeftLayout->addWidget(materialList);
		}
	}
	setLayout(topLeftLayout);
	setWindowTitle(tr("Material list"));
}

listCourseDialog::~listCourseDialog(void)
{

}
