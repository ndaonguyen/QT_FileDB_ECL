#pragma once
#include "databaseFile.h"


class QLabel;
class QListWidget;

class listCourseDialog : public QDialog
{
public:
	listCourseDialog(QWidget *parent = 0,databaseFile *dbFile =0, QString courseId=0);
	~listCourseDialog(void);
private:
    QList<QLabel*> skills;
	QList<QListWidget*> materialList;
};
