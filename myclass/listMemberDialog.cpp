#include <QtGui>
#include "listMemberDialog.h"


listMemberDialog::listMemberDialog(QWidget *parent,databaseFile *dbFileTransfer,QString classId)
{
//	conn = database::connectByC();
	dbFile = dbFileTransfer;
	QVBoxLayout *topLeftLayout = new QVBoxLayout;

	view  = new QTableView(this);
	model = new QStandardItemModel(this);
	view->setModel(model);

	model->setHorizontalHeaderItem(0, new QStandardItem(tr("ID")));
	model->setHorizontalHeaderItem(1, new QStandardItem(tr("Name")));
	model->setHorizontalHeaderItem(2, new QStandardItem(tr("Birth year")));
	model->setHorizontalHeaderItem(3, new QStandardItem(tr("Note")));
	model->setHorizontalHeaderItem(4, new QStandardItem(tr("-")));
	
	view->setColumnWidth(0,20);
	view->setColumnWidth(1,90);
	view->setColumnWidth(2,57);
	view->setColumnWidth(3,40);
	view->setColumnWidth(4,30);
	
	label = new QLabel("Member list");
	topLeftLayout->addWidget(label);
	int rowCurrent = 0;

//	MYSQL_RES *res = database::classMember_searchClassId(conn,classId);
//	while(MYSQL_ROW classMemberRow = mysql_fetch_row(res))
	QList< QMap<String,QString> > res = dbFile->getListByField("class_member","class_id",classId);
	int numClassMember = res.count();
	for(int i = 0;i<numClassMember;i++)
	{
	//	QString memberId   = classMemberRow[1];
		QString memberId    = res.at(i)["member_id"];
		QList< QMap<String,QString> > memberRow = dbFile->getListByField("member","id",memberId);
//		MYSQL_ROW memberRow = database::member_searchMemberId(conn,memberId);
		
		model->setItem(rowCurrent, 0, new QStandardItem(memberRow.at(0)["id"]));
		model->setItem(rowCurrent, 1, new QStandardItem(memberRow.at(0)["name"]));
		model->setItem(rowCurrent, 2, new QStandardItem(memberRow.at(0)["birth_year"]));
		model->setItem(rowCurrent, 3, new QStandardItem(memberRow.at(0)["note"]));

		QPushButton *button = new QPushButton("");
		QIcon ButtonIcon2;
		ButtonIcon2.addFile(QString::fromUtf8(":/myclass/Resources/Delete_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
		button->setIcon(ButtonIcon2);


		QSignalMapper *signalMapper = new QSignalMapper(this);
		signalMapper->setMapping(button,memberId);
		QObject::connect(button,SIGNAL(clicked()),signalMapper,SLOT(map()));
		QObject::connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(deleteMemberAction(QString)));
		view->setIndexWidget(model->index(rowCurrent,4),button);

		rowCurrent++;
	}
	numOldMemberInDialog = rowCurrent;
	topLeftLayout->addWidget(view);

	QHBoxLayout *horizontalLayout = new QHBoxLayout();
	QPushButton *saveButton = new QPushButton("Save");
	QPixmap pixmap1("Resources/save_icon.png");
	QIcon ButtonIcon1(pixmap1);
	saveButton->setIcon(ButtonIcon1);
	QSignalMapper *saveMapper = new QSignalMapper(this);
	saveMapper->setMapping(saveButton,classId);
	QObject::connect(saveButton,SIGNAL(clicked()),saveMapper,SLOT(map()));
	QObject::connect(saveMapper,SIGNAL(mapped(QString)),this,SLOT(saveListAction(QString)));
	
	horizontalLayout->addWidget(saveButton);
	
	QPushButton *addMemberButton = new QPushButton("Add Member");
	QPixmap pixmap("Resources/add-icon.png");
	QIcon ButtonIcon(pixmap);
	addMemberButton->setIcon(ButtonIcon);
	QObject::connect(addMemberButton,SIGNAL(clicked()),this,SLOT(addMemberAction()));
	horizontalLayout->addWidget(addMemberButton);

	setLayout(topLeftLayout);
	topLeftLayout->addLayout(horizontalLayout);
	setWindowTitle(tr("Member list"));
	setFixedHeight(sizeHint().height());
	
}

listMemberDialog::~listMemberDialog(void)
{
}
