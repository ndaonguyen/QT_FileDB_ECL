#include <QtGui>
#include "listMaterialDialog.h"

listMaterialDialog::listMaterialDialog(QWidget *parent, databaseFile *dbFileTransfer, QString skillName, int courseId)
    : QDialog(parent)
{
	isChanged = false;
	dbFile    = dbFileTransfer;
	QList< QMap<QString,QString> > skMaList = dbFile->skillMaterialList;
	
	label     = new QLabel(tr("List  of Material ")+skillName);
	view      = new QTableView;
	model     = new QStandardItemModel(this);
	view->setModel(model);
	model->setColumnCount(3);
	view->setColumnWidth(0,30);
	view->setColumnWidth(1,170);
	view->setColumnWidth(2,30);

	QList<QMap<QString,QString>> skillList = dbFile->getListByField("skill","name",skillName);
	if (skillList.count()>0)
	{
		model->setHorizontalHeaderItem(2,new QStandardItem(tr("-")));
		model->setHorizontalHeaderItem(1,new QStandardItem(tr("Material")));
		model->setHorizontalHeaderItem(0,new QStandardItem(tr("Id")));
		view->setColumnHidden(0,true);

		QString skillId = skillList.at(0)["id"];
		QString couId   = QString::number(courseId);

		QList<QString> fieldList;
		QList<QString> valueList;
		fieldList << "skill_id" << "course_id";
		valueList << skillId << couId;
		QList< QMap<QString,QString> > skiMaList = dbFile->getListByFields("skill_material",fieldList,valueList);
		int numRow = skiMaList.count();
		if(numRow>0)
		{
			for( int rowIndex = 0; rowIndex < numRow; rowIndex ++)
			{
				QString materialId = skiMaList.at(rowIndex)["material_id"];
				QList< QMap<QString,QString> > materialList = dbFile->getListByField("material","id",materialId);
				QString material = materialList.at(0)["name"];

				QPushButton *button = new QPushButton("");
				QIcon ButtonIcon2;
				ButtonIcon2.addFile(QString::fromUtf8(":/myclass/Resources/Delete_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
				button->setIcon(ButtonIcon2);
				QSignalMapper *signalMapper = new QSignalMapper(this);
				signalMapper->setMapping(button,materialId);
				QObject::connect(button,SIGNAL(clicked()),signalMapper,SLOT(map()));
				QObject::connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(deleteMaterial(QString)));

				QStandardItem *materName = new QStandardItem(material);
				model->setItem(rowIndex, 1, materName);

				QString maIDStr = materialId;
				QStandardItem *materialIdItem = new QStandardItem(maIDStr);
				model->setItem(rowIndex, 0, materialIdItem);

				view->setIndexWidget(model->index(rowIndex,2),button);
			}
		}
	}
	QVBoxLayout *topLeftLayout = new QVBoxLayout;
	topLeftLayout->addWidget(label);
	topLeftLayout->addWidget(view);

	QPushButton *saveButton = new QPushButton("Save");
	QObject::connect(saveButton,SIGNAL(clicked()),this,SLOT(editMaterialAction()));
	topLeftLayout->addWidget(saveButton);

	setLayout(topLeftLayout);
	setWindowTitle(tr("Material list"));
	setFixedHeight(sizeHint().height());
}
listMaterialDialog::~listMaterialDialog(void)
{
}

