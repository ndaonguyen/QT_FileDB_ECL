#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include <QSignalMapper>
#include "ui_addClass.h"
#include "data_conf.h"
#include "databaseFile.h"

class AddClass :public QDialog//, public Ui::Form
{
	Q_OBJECT
public:
	AddClass( QWidget * parent = 0, Qt::WindowFlags f = 0, databaseFile *dbFile = 0, QString classID = 0);
	~AddClass(void);
private:
	Ui::Form ui;
private:
	databaseFile *dbFile;

	int classID; // != 0 : edit mode . =0: save
	QStandardItemModel *addMemberModel;
	QList<QStandardItemModel*> skillModelList; // list contain material ( set current situation) // ADD CLASS
	QList<QTableView*>  skillTableList; // list contain material   // ADD CLASS
	QList<QString> skillIdList;     // skill of contain material   // ADD CLASS
	QList<bool> enableForEditing;  // order:  class info, member, course
public:
	void setConnection();
	void clearItemsLayout(QLayout* layout);
	void setHeaderTable(QStandardItemModel *model, QList<QString> listHeader);
	void setEmptyRowTable(QStandardItemModel *model, int numRow);
	bool isNumber(QString strCheck);
	bool checkItemExist(QString itemCheck, QList<QString> listItems);
	QPushButton* addActionButton(QString typeButton, QString mappingType, QString mappingData, 
								 QSignalMapper *mapper, bool isAddTextButton );

	
	QList<QString> getMemIdInClass(int classiD);
	void deleteMemberById(QString memberId);
	void editMember();
	void editCourse();
	void editClass();
	

	void addUseCheckBox(QString courseNameEdit,QString courseNameChoose);  // use for load course in edit class
	bool checkCourseNew(QString courseCompare, int classiD );
	void setSizeMaterialBox(QTableView *skillTable );
	void setSkillLabelInMaBox(QString skillId);
	void fillMaterialForEachSkill(QList< QMap<QString,QString> > resMaterialUse, int skillIndex, 
								  QTableView *skillTable, QStandardItemModel *skillModel);
	void fillMaterial4AddMember(QString courseIdStr); // **
	void loadConfigEditInAddClassTab();
	void loadDataAddClassTab(int classId);
	void loadConfigAddClass();
	void loadAddModeInAddClassTab();
	void loadBasicInfoAddClassTab(QMap<QString,QString> classInfo);
	void loadMemberAddClassTab(QString classIdStr);

	QList<QString> getMemberListSaveClass();
	bool validateDataSaveClass();
	void saveMembersInClass(QList<QString> memberList, QString classId);
	

	


private slots:
	void courseComboAction(QString courseStr);
	void saveClassAction();
	void enableClassInfoAction();
	void enableMemberAction();
	void enableCourseAction();
	void cancelClassAction();
	void delMaterialTable(QString materialNSkillIndex);	


	void delMemberRowAction(QString memberId);
};
