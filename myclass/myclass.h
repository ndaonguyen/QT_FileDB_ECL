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
#include "listCourseDialog.h"
#include "listMemberDialog.h"

#include "addClass.h"
#include "addCourse.h"


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

	QStandardItemModel *listCourseModel;
	QStandardItemModel *listClassModel;
public:
// COMMON
	void setConnection();
	void setHeaderTable(QStandardItemModel *model, QList<QString> listHeader);
	void setEmptyRowTable(QStandardItemModel *model, int numRow);
	bool isNumber(QString strCheck);
	QPushButton* addActionButton(QString typeButton, QString mappingType, QString mappingData, 
								 QSignalMapper *mapper, bool isAddTextButton );

	void loadConfigListClass();
	void saveMembersInClass(QList<QString> memberList, QString classId);
	void deleteCourse(QString courseId);

// START: LIST CLASS TAB
	void getPerCentInClass(IN QMap<QString,QString> classRow, OUT int &percentMater, OUT int &percentDay );
	void fillListClass(QList< QMap<QString,QString> > resClass);
	void loadDataAndHeaderListClass(QList< QMap<QString,QString> > resClass);
	void loadListClassTab();  // main function
	

//  START :LIST COURSE TAB
	QString getSkillListStr(QString courseId);
	void fillListCourse(QList< QMap<QString,QString> > materialRows,QTableView *listCourseTable,
						QStandardItemModel *courseModel, int indexRow);
	void loadListCourseTab();

	public slots:
		void refreshAddClassAction();
		void refreshAddCourseAction();

// LIST COURSE TAB
		void searchCourseAction();
		void refreshCourseListAction();
		void loadCourseDialogAction(QString courseId);
		void editCourseAction(QString courseId);
		void deleteCourseAction(QString courseId);

//  LIST CLASS TAB
		void searchClassAction();
		void refreshClassListAction();
		void detailMemberAction(QString classId);
		void editClassAction(QString classId);
		void deleteClassAction(QString classId);
};

#endif // MYCLASS_H
