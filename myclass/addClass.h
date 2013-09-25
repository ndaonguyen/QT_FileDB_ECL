#pragma once

#include <QDialog>
#include "ui_addClass.h"
#include "data_conf.h"

class AddClass :public QDialog, public Ui::myAddClass
{
	Q_OBJECT
public:
	AddClass( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~AddClass(void);
private:
	Ui::myAddClass ui;

public:
	void setConnection();

private slots:

};
