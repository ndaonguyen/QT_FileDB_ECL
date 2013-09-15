#include <QtGui>
#include "listMaterialDialog.h"

listMaterialDialog::listMaterialDialog(QWidget *parent, QString skillName, int courseId)
    : QDialog(parent)
{
	isChanged = false;
	conn = database::connectByC();
	label      = new QLabel(tr("List  of Material ")+skillName);
	view = new QTableView;
	model = new QStandardItemModel(this);
	view->setModel(model);
	model->setColumnCount(3);
	view->setColumnWidth(0,30);
	view->setColumnWidth(1,170);
	view->setColumnWidth(2,30);

	MYSQL* conn = database::connectByC();
	MYSQL_ROW skillRow = database::skill_searchName(conn,skillName);
	if (skillRow)
	{
		model->setHorizontalHeaderItem(2,new QStandardItem(tr("-")));
		model->setHorizontalHeaderItem(1,new QStandardItem(tr("Material")));
		model->setHorizontalHeaderItem(0,new QStandardItem(tr("Id")));

		QString skillId = skillRow[0];
		QString couId   = QString::number(courseId);
		MYSQL_RES* res_set =  database::skillMaterial_searchSkillId(conn,skillId,couId);
		MYSQL_ROW row;
		int rowIndex = 0;
		while(row = mysql_fetch_row(res_set))
		{
			QString materialId = row[1];
			MYSQL_ROW rowMaterial =  database::material_searchMaterialId(conn,materialId);
			QString material = QString::fromUtf8(rowMaterial[1]);

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

			QString maIDStr = row[1];
			QStandardItem *materialIdItem = new QStandardItem(maIDStr);
			model->setItem(rowIndex, 0, materialIdItem);

			view->setIndexWidget(model->index(rowIndex,2),button);
			rowIndex++;
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
	database::closeConnectionC(conn);
}

//#include "GeneratedFiles/Debug/moc_listMaterialDialog.cpp"