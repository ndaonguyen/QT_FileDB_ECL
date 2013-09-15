#include <QtGui>
#include "listCourseDialog.h"
#include "database.h"

listCourseDialog::listCourseDialog(QWidget *parent, QString courseId)
	: QDialog(parent)
{
	QVBoxLayout *topLeftLayout = new QVBoxLayout;
	MYSQL* conn = database::connectByC();

	MYSQL_RES* res_set = database::courseSkill_searchCourseId(conn,courseId);
	MYSQL_ROW row;
	while(row = mysql_fetch_row(res_set))
	{
		QString skillID = row[1];
		MYSQL_ROW skillRow =  database::skill_searchSkillId(conn,skillID);
		QString skillName = skillRow[1];
		QLabel *skill = new QLabel("<b>"+skillName+"</b>");
		topLeftLayout->addWidget(skill);
		
		MYSQL_RES* result = database::skillMaterial_searchSkillId(conn,skillID,courseId); 
		MYSQL_ROW materialRow;
		QListWidget *materialList = new QListWidget();
		while(materialRow = mysql_fetch_row(result))
		{
			QString matId = materialRow[1];
			MYSQL_ROW materialData = database::material_searchMaterialId(conn,matId);
			materialList->addItem(materialData[1]);
		}
		topLeftLayout->addWidget(materialList);
	}
	setLayout(topLeftLayout);
	setWindowTitle(tr("Material list"));
}

listCourseDialog::~listCourseDialog(void)
{

}
