#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include <QSignalMapper>
#include "listMaterialDialog.h"
#include "ui_addCourse_cop.h"
#include "data_conf.h"
#include "databaseFile.h"

class AddCourse : public QDialog
{
	Q_OBJECT
public:
	AddCourse(QWidget * parent = 0, Qt::WindowFlags f = 0, databaseFile *dbFile = 0, QString courseId = 0);
	~AddCourse(void);
private:
	Ui::addCourse ui;

private:
	databaseFile *dbFile;

	QString courseMode;
	QString courseName; //Current course name ( initial = "" )
	int courseID;  // Current course_id ( initial = 0 )
	QList<QString> skillsCourse;
	QList<QListWidget *> skillWidgets;

public:
	void setConnection();
	bool isItemExist(QString item,QListWidget *list);
	void clearItemsLayout(QLayout* layout);
	bool checkItemExist(QString itemCheck, QList<QString> listItems);

			/* STEP 1 - 2 : CLICK BUTTON1 SAVE */
	void fillSkillsStep2();
	void setup4Step2();// Main step 2 
			/* END STEP 1 - 2  */

			/* START STEP 2 - 3 CLICK BUTTON2 SAVE */
	void saveCourseSKillTable(int numElementSkillBox);
	void setupStep3Add(int numElementSkillBox) ;
	void setupInfoBoxStep2Save(int numElementBoxSkill);
	void setup4Step3(); // Main step 3 
			/* END STEP 2 - 3 CLICK BUTTON2 SAVE */
	QString materialBox(QString skill,bool &ok);
	bool isAddMaterial(QString skillNIndex);
	void loadConfigAddCourseTab();
	void refreshToOriginAddCourse();

	void deleteCourse(QString courseId);

public slots:
	void refreshAddCourseAction();
	void step1SaveAction(); // disable step 1, enable step 2, update info to info box
	void step2SaveAction();
	void addSkillAction(); 
	void left2RightAction();
	void right2LeftAction();
	void all2LeftAction();
	void all2RightAction();
	void left2RightClickAction();
	void right2LeftClickAction();
	void listMaterialAction(QString skillNIndex);
	void addMaterialAction(QString skillNIndex);
	void saveCourseAction();
	void cancelCourseAction();

};
