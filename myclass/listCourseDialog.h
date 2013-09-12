#pragma once

class QLabel;
class QListWidget;

class listCourseDialog : public QDialog
{
public:
	listCourseDialog(QWidget *parent = 0, QString courseId=0);
	~listCourseDialog(void);
private:
    QList<QLabel*> skills;
	QList<QListWidget*> materialList;
};
