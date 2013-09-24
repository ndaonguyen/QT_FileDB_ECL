#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtGui/QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QCheckBox>
#include "ui_myclass.h"
#include "data_conf.h"

#include "databaseFile.h"
#include <QSignalMapper>
#include <QStandardItemModel>
#include "listMaterialDialog.h"
#include "listCourseDialog.h"
#include "listMemberDialog.h"



class MyClass : public QMainWindow
{
	Q_OBJECT
public:
	MyClass(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MyClass();
private:
	Ui::myclassClass ui;
private: 
//	MYSQL *conn;
	databaseFile *dbFile;

// COURSE info
	QStandardItemModel *listCourseModel;
	QString courseMode;
	QString courseName; //Current course name ( initial = "" )
	int courseID;  // Current course_id ( initial = 0 )
	QList<QString> skillsCourse;
	QList<QListWidget *> skillWidgets;

// CLASS info
	QStandardItemModel *listClassModel;
	QStandardItemModel *addMemberModel;
	QList<QStandardItemModel*> skillModelList; // list contain material ( set current situation) // ADD CLASS
	QList<QTableView*>  skillTableList; // list contain material   // ADD CLASS
	QList<QString> skillIdList;     // skill of contain material   // ADD CLASS
	int classID; // != 0 : edit mode . =0: save
	QList<bool> enableForEditing;  // order:  class info, member, course
public:
// COMMON
	void setConnection();
	void setHeaderTable(QStandardItemModel *model, QList<QString> listHeader);
	void setEmptyRowTable(QStandardItemModel *model, int numRow);
	bool isNumber(QString strCheck);
	bool checkItemExist(QString itemCheck, QList<QString> listItems);
	bool isItemExist(QString item,QListWidget *list);
	void clearItemsLayout(QLayout* layout);
	void loadOriginConfig();
	QPushButton* addActionButton(QString typeButton, QString mappingType, QString mappingData, QSignalMapper *mapper, bool isAddTextButton );
// END COMMON

// START : ADD CLASS TAB
	// START ---- edit class
	QList<QString> getMemIdInClass(int classiD);
	void deleteMemberById(QString memberId);
	void editMember();
	void editCourse();
	void editClass();
	void addUseCheckBox(QString courseNameEdit,QString courseNameChoose);  // use for load course in edit class
	void loadBasicInfoAddClassTab(QMap<QString,QString> classInfo);
	void loadMemberAddClassTab(QString classIdStr);
	void loadConfigEditInAddClassTab();
	// END --- edit class
	void loadConfigClass();
	void loadDataAddClassTab(int classId);
	void loadAddModeInAddClassTab();
	
	void setSizeMaterialBox(QTableView *skillTable );
	bool checkCourseNew(QString courseCompare, int classiD );
	void setSkillLabelInMaBox(QString skillId);
	void fillMaterialForEachSkill(QList< QMap<QString,QString> > resMaterialUse, int skillIndex, 
								  QTableView *skillTable, QStandardItemModel *skillModel);
	void fillMaterial4AddMember(QString courseIdStr); // **
	QList<QString> getMemberListSaveClass();
	bool validateDataSaveClass();
	void configAfterSaveClass();
	void saveMembersInClass(QList<QString> memberList, QString classId);
// END   : ADD CLASS TAB


//  START :ADD COURSE TAB
	void deleteCourse(QString courseId);
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
//  END :ADD COURSE TAB


// START: LIST CLASS TAB
	void getPerCentInClass(IN QMap<QString,QString> classRow, OUT int &percentMater, OUT int &percentDay );
	void fillListClass(QList< QMap<QString,QString> > resClass);
	void loadDataAndHeaderListClass(QList< QMap<QString,QString> > resClass);
	void loadListClassTab();  // main function
	
// END: LIST CLASS TAB


//  START :LIST COURSE TAB
	QString getSkillListStr(QString courseId);
	void fillListCourse(QList< QMap<QString,QString> > materialRows,QTableView *listCourseTable,
						QStandardItemModel *courseModel, int indexRow);
	void loadListCourseTab();
// END : LIST COURSE TAB


// START : ADD CLASS TAB
	public slots:
		void enableClassInfoAction();
		void enableMemberAction();
		void enableCourseAction();
		void refreshAddClassAction();
		void cancelClassAction();
		void delMaterialTable(QString materialNSkillIndex);		
		void saveClassAction();		
		void courseComboAction(QString courseStr);
// END   : ADD CLASS TAB


// ADD COURSE TAB
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

// LIST COURSE TAB
	public slots:
		void searchCourseAction();
		void refreshCourseListAction();
		void loadCourseDialogAction(QString courseId);
		void editCourseAction(QString courseId);
		void deleteCourseAction(QString courseId);
/*
		void cancelCourseAction()
		{
			ui.mainTab->setTabEnabled(0,true);
			ui.mainTab->setTabEnabled(1,false);
			ui.mainTab->setTabEnabled(2,true);
			ui.mainTab->setTabEnabled(3,false);

			QWidget * tab = ui.mainTab->widget(2);
			ui.mainTab->setCurrentWidget(tab);

			if(courseMode == "CREATE" && courseID !=0)
				deleteCourse(QString::number(courseID));
			refreshToOriginAddCourse();
			loadListCourseTab();
			ui.searchClassLineEdit->setText("");
		}
*/


// START: LIST CLASS TAB
	public slots:
		void searchClassAction();
		void refreshClassListAction();
		void detailMemberAction(QString classId);
		void delMemberRowAction(QString memberId);
		void editClassAction(QString classId);
		void deleteClassAction(QString classId);
// END: LIST CLASS TAB
};

#endif // MYCLASS_H
