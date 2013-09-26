#include "myclass.h"

MyClass::MyClass(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	dbFile = new databaseFile();
	setConnection();
	loadListCourseTab();
	loadOriginConfig();

	loadConfigListClass();
	loadListClassTab();
}

MyClass::~MyClass()
{
	delete dbFile;
	delete listCourseModel;
	delete listClassModel;
}

/**
  * set connection for all button, combobox,...
  */
void MyClass::setConnection()
{
	// List Class
	QObject::connect(ui.refreshClassButton, SIGNAL(clicked()),
					this, SLOT(refreshClassListAction()));
	QObject::connect(ui.addMoreClassButton, SIGNAL(clicked()),
					this, SLOT(refreshAddClassAction()));
	QObject::connect(ui.searchClassButton, SIGNAL(clicked()),
					this, SLOT(searchClassAction()));
    QObject::connect(ui.searchClassLineEdit, SIGNAL(returnPressed()),
					this, SLOT(searchClassAction()));


	// list course
	QObject::connect(ui.refreshCourseButton, SIGNAL(clicked()),
					this, SLOT(refreshCourseListAction()));
	QObject::connect(ui.addMoreCourseButton, SIGNAL(clicked()),
					this, SLOT(refreshAddCourseAction()));
	QObject::connect(ui.searchCourseButton, SIGNAL(clicked()),
					this, SLOT(searchCourseAction()));
    QObject::connect(ui.searchCourseLineEdit, SIGNAL(returnPressed()),
					this, SLOT(searchCourseAction()));

	// add course
    QObject::connect(ui.addMoreButton, SIGNAL(clicked()),
		             this, SLOT(refreshAddCourseAction()));
    QObject::connect(ui.leftWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
					this, SLOT(left2RightClickAction()));
    QObject::connect(ui.rightWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
					this, SLOT(right2LeftClickAction()));
    QObject::connect(ui.left2RightButton, SIGNAL(clicked()),
					this, SLOT(left2RightAction()));
    QObject::connect(ui.right2LeftButton, SIGNAL(clicked()),
					this, SLOT(right2LeftAction()));
    QObject::connect(ui.all2RightButton, SIGNAL(clicked()),
					this, SLOT(all2RightAction()));
    QObject::connect(ui.all2LeftButton, SIGNAL(clicked()),
					this, SLOT(all2LeftAction()));
    QObject::connect(ui.addSkill, SIGNAL(clicked()),
					this, SLOT(addSkillAction()));
    QObject::connect(ui.cancelCourseButton, SIGNAL(clicked()),
					this, SLOT(cancelCourseAction()));
	QObject::connect(ui.saveButton,SIGNAL(clicked()),
					this, SLOT(step1SaveAction()));
	QObject::connect(ui.courseNameLineEdit,SIGNAL(returnPressed()),
					this, SLOT(step1SaveAction()));
	QObject::connect(ui.saveButton2,SIGNAL(clicked()),
					this, SLOT(step2SaveAction()));
	QObject::connect(ui.saveCourseButton,SIGNAL(clicked()),
					this, SLOT(saveCourseAction()));
}

/**
  * set Header for QTableView
  * @param model: of QTableView, listHeader : list of Header String
  */
void MyClass::setHeaderTable(QStandardItemModel *model, QList<QString> listHeader)
{
	int count = listHeader.count();
	for(int i =0;i<count;i++)
		model->setHorizontalHeaderItem(i, new QStandardItem(listHeader.at(i)));
}

/**
  * fill Table with empty value
  */
void MyClass::setEmptyRowTable(QStandardItemModel *model, int numRow)
{
	int columns  = model->columnCount();
	int rowIndex = 0;
	while (rowIndex <numRow)
	{
		for(int i =0;i<columns;i++)
			model->setItem(rowIndex,i, new QStandardItem(tr("")));
		rowIndex ++;
	}
}

void MyClass::loadOriginConfig()
{
	ui.mainTab->setTabEnabled(LIST_CLASS_TAB ,true);
	ui.mainTab->setTabEnabled(ADD_CLASS_TAB  ,false);
	ui.mainTab->setTabEnabled(LIST_COURSE_TAB,true);
	ui.mainTab->setTabEnabled(ADD_COURSE_TAB ,false);
}

bool MyClass:: isNumber(QString strCheck)
{
	int strLen = strCheck.length();
	if(strLen==0)
		return false;

	for(int i=0;i<strLen;i++)
	{
		QChar ch = strCheck.at(i);
		if(ch.isDigit() == false)
			return false;
	}

	return true;
}

QPushButton* MyClass:: addActionButton(QString typeButton, QString mappingType, 
									   QString mappingData, QSignalMapper *mapper,bool isAddTextButton )
{
	QPushButton *button = new QPushButton();
	if(isAddTextButton == ENABLE_TEXT_BUTTON)
		button->setText(typeButton);

	QString pathIcon = "";
	if( typeButton == EDIT_BUTTON )
		pathIcon = EDIT_ICON_PATH;
	if( typeButton == DELETE_BUTTON )
		pathIcon = DELETE_ICON_PATH;
	if( typeButton == DETAIL_BUTTON )
		pathIcon = DETAIL_ICON_PATH;

	QIcon ButtonIcon1;
	ButtonIcon1.addFile(pathIcon, QSize(), QIcon::Normal, QIcon::Off);
	button->setIcon(ButtonIcon1);

	if(mappingType == MAPPING_TYPE_INT)
	{
		int dataMappingInt = mappingData.toInt();
		mapper->setMapping(button,dataMappingInt);
		QObject::connect(button,SIGNAL(clicked()),mapper,SLOT(map()));
		return button;
	}

	mapper->setMapping(button,mappingData);
	QObject::connect(button,SIGNAL(clicked()),mapper,SLOT(map()));
	return button;
}

/**
  * load confif of list class and add class at the constructor
  */
void MyClass:: loadConfigListClass()
{
	listClassModel = new QStandardItemModel(this); 
	ui.listClassTable->setModel(listClassModel);
}

// ----------------------------- ADD COURSE TAB
void MyClass:: deleteCourse(QString courseId) // delete course base on course id --> delete all thing related to course
{
	//delete database ( children --> parent)
	QList< QMap<QString,QString> > courseList = dbFile->getListByField("course","id",courseId);
	QString nameCourse  = courseList.at(0)["name"];
	
	QList< QMap<QString,QString> > coSkList = dbFile->getListByField("course_skill","course_id",courseId);
	int numCoSk = coSkList.count();
	for(int i=0;i<numCoSk;i++)
	{
		QString skillId = coSkList.at(i)["skill_id"];

		QList<QString> fields;
		QList<QString> fieldValues;
		fields << "skill_id" << "course_id";
		fieldValues << skillId << courseId;
		QList< QMap<QString,QString> > skMaList = dbFile->getListByFields("skill_material",fields, fieldValues);
		int numSkMa = skMaList.count();
		for(int i =0;i< numSkMa;i++)
		{
			QString materialId = skMaList.at(i)["material_id"];
			dbFile->deleteByField("material","id",materialId);
			dbFile->deleteByField("skill_material","material_id",materialId);
		}
		dbFile->deleteByField("course_skill","course_id",courseId);
	}
	dbFile->deleteByField("course","id",courseId);
	dbFile->deleteByField("class","course_id",courseId);

	// Delete row of QTableView
	int rowCount = listCourseModel->rowCount();
	for(int i =0; i < rowCount; i++)
		if(nameCourse == listCourseModel->data(listCourseModel->index(i,0), Qt::DisplayRole).toString())
			listCourseModel->removeRow(i);

	loadListClassTab(); //reload List Class
}

// ------------------------------- LIST CLASS TAB

void MyClass:: getPerCentInClass(IN QMap<QString,QString> classRow, OUT int &percentMater, OUT int &percentDay )
{
	QList<QString> fields;
	fields << "class_id" << "status";
	QList<QString> fieldUseValues;
	fieldUseValues << classRow["id"] << "1";

	QList< QMap<QString,QString> > allMat = dbFile->getListByField("materialuse","class_id", classRow["id"]);
	QList< QMap<QString,QString> > useMat = dbFile->getListByFields("materialuse",fields,fieldUseValues);

	int allMater = allMat.count();
	int useMater = useMat.count();

	if(allMater!=0)
		percentMater    = (useMater*100/allMater);

	QString totalDay    = classRow["total_day"];
	QString learnDay    = classRow["num_learning_day"];
	percentDay   = (learnDay.toInt()*100/totalDay.toInt());
}

void MyClass:: fillListClass(QList< QMap<QString,QString> > resClass)
{
	int numRow = resClass.count();

	for(int rowCurrent = 0; rowCurrent < numRow; rowCurrent++)
	{
		QMap<QString,QString> classRow       = resClass.at(rowCurrent);
		QList< QMap<QString,QString> > coRow = dbFile->getListByField("course", "id", classRow["course_id"]);
		QString cName       = coRow.at(0)["name"];
		QString regisDate   = classRow["registration_day"];
		QString className   = classRow["name"];
		QString totalDay    = classRow["total_day"];
		QString learnDay    = classRow["num_learning_day"];

		listClassModel->setItem(rowCurrent,0, new QStandardItem(classRow["id"]));
		listClassModel->setItem(rowCurrent,1, new QStandardItem(className));
		listClassModel->setItem(rowCurrent,2, new QStandardItem(regisDate));
		listClassModel->setItem(rowCurrent,4,new QStandardItem(cName));

		int percentMater;
		int percentDay;
		getPerCentInClass(classRow, percentMater, percentDay );
		listClassModel->setItem(rowCurrent,5,new QStandardItem(QString::number(percentDay)));
		listClassModel->setItem(rowCurrent,6,new QStandardItem(QString::number(percentMater)));

		QSignalMapper *memberListMapper = new QSignalMapper(ui.listClassTable);
		QPushButton   *memberListButton = addActionButton(DETAIL_BUTTON, MAPPING_TYPE_STR, classRow["id"],
														  memberListMapper, ENABLE_TEXT_BUTTON);
		QObject::connect(memberListMapper,SIGNAL(mapped(QString)),this,SLOT(detailMemberAction(QString)));
		ui.listClassTable->setIndexWidget(listClassModel->index(rowCurrent,3),memberListButton);

		QSignalMapper *editClassMapper = new QSignalMapper(ui.listClassTable);
		QPushButton *editClassButton   = addActionButton (EDIT_BUTTON, MAPPING_TYPE_STR, classRow["id"], 
														  editClassMapper, ENABLE_TEXT_BUTTON);
		QObject::connect(editClassMapper,SIGNAL(mapped(QString)),this,SLOT(editClassAction(QString)));
		ui.listClassTable->setIndexWidget(listClassModel->index(rowCurrent,7),editClassButton);

		QSignalMapper *deleteClassMapper = new QSignalMapper(ui.listClassTable);
		QPushButton *deleteClassButton   = addActionButton(DELETE_BUTTON, MAPPING_TYPE_STR, classRow["id"],
														   deleteClassMapper, ENABLE_TEXT_BUTTON);
		QObject::connect(deleteClassMapper,SIGNAL(mapped(QString)),this,SLOT(deleteClassAction(QString)));
		ui.listClassTable->setIndexWidget(listClassModel->index(rowCurrent,8),deleteClassButton);
	}
}

void MyClass:: loadListClassTab()
{
	ui.refreshClassButton->setText("");
	ui.searchClassLineEdit->setText("");
	QList< QMap<QString,QString> > classList = dbFile->getAll("class");
	loadDataAndHeaderListClass(classList);
}

// ---------------------LIST COURSE TAB
QString MyClass:: getSkillListStr(QString courseId)
{
	QList< QMap<QString,QString> > coSkiList = dbFile->getListByField("course_skill","course_id",courseId);
	int numList = coSkiList.count();
	QString skillString = "";
	QString skillID     = "";
	for(int i=0;i<numList;i++)
	{
		skillID     = coSkiList.at(i)["skill_id"];
		QList< QMap<QString,QString> > skillList = dbFile->getListByField("skill","id",skillID);
		skillString = skillString + skillList.at(0)["name"] +",";
	}
	skillString = skillString.mid(0,skillString.length()-1);  // Skill of that course
	return skillString;
}

/**
  * Fill to the next rows of QTableList ( when choose course --> list material )
  * @param res_set: data need to be filled
  * @param listCourseTable : QTableView to filled data
  * @param courseModel : Model of QTableView
  * @param indexRow    : index of row to continue insert
  */
void MyClass:: fillListCourse(QList< QMap<QString,QString> > materialRows,QTableView *listCourseTable,
					QStandardItemModel *courseModel, int indexRow)
{
	int indexTemp = indexRow;
	QList<QString> courseIdList;
	int numRow    = materialRows.count();
	for(int i = 0; i < numRow; i++)
	{
		QString course   = materialRows.at(i)["name"];  // course Name
		QString courseId = materialRows.at(i)["id"];
		courseIdList.append(courseId);

		QString skillString = getSkillListStr(courseId);	
	
		courseModel->setItem(indexTemp,0,new QStandardItem(course));
		courseModel->setItem(indexTemp,1,new QStandardItem(skillString));

		indexTemp++;
	}

	//Add button Detail và Button Edit vào
	int numCourseId = courseIdList.length();
	for(int i = indexRow ; i < numCourseId ; i++)
	{
		int indexCourseIdList = i-indexRow;

		QSignalMapper *signalMapper = new QSignalMapper();
		QPushButton *detailButton   = addActionButton( DETAIL_BUTTON, MAPPING_TYPE_STR, courseIdList.at(indexCourseIdList),
													   signalMapper, ENABLE_TEXT_BUTTON);
		QObject::connect(signalMapper, SIGNAL(mapped(QString)),this, SLOT(loadCourseDialogAction(QString)));			
		listCourseTable->setIndexWidget(courseModel->index(i,2),detailButton);

		QSignalMapper *signalMapper1 = new QSignalMapper(this);
		QPushButton *editButton      = addActionButton( EDIT_BUTTON, MAPPING_TYPE_STR, courseIdList.at(indexCourseIdList),
														signalMapper1, ENABLE_TEXT_BUTTON);
		QObject::connect(signalMapper1, SIGNAL(mapped(QString)),this, SLOT(editCourseAction(QString)));
		listCourseTable->setIndexWidget(courseModel->index(i,3),editButton);

		QSignalMapper *signalMapper2 = new QSignalMapper(this);
		QPushButton *deleteButton    = addActionButton(DELETE_BUTTON, MAPPING_TYPE_STR, courseIdList.at(indexCourseIdList),
													   signalMapper2, ENABLE_TEXT_BUTTON);
		QObject::connect(signalMapper2, SIGNAL(mapped(QString)),this, SLOT(deleteCourseAction(QString)));
		listCourseTable->setIndexWidget(courseModel->index(i,4),deleteButton);
	}
}

void MyClass:: loadListCourseTab()
{
	listCourseModel = new QStandardItemModel(ui.listCourseTab);
	ui.listCourseTable->setModel(listCourseModel);

	QList<QString> headerList;
	headerList << "Course Name" << "Skill" << "Material" << "Edit" << "Delete";
	setHeaderTable(listCourseModel, headerList);

	ui.listCourseTable->setColumnWidth(0,LIST_COURSE_COL_1);
	ui.listCourseTable->setColumnWidth(1,LIST_COURSE_COL_2);
	ui.listCourseTable->setColumnWidth(2,LIST_COURSE_COL_3);
	ui.listCourseTable->setColumnWidth(3,LIST_COURSE_COL_4);
	ui.listCourseTable->setColumnWidth(4,LIST_COURSE_COL_5);

	QList< QMap<QString,QString> > res_set = dbFile->getAll("course");
	fillListCourse(res_set,ui.listCourseTable,listCourseModel,0);
}

void MyClass:: refreshAddClassAction()
{
	AddClass *addClassDialog = new AddClass(0,0, dbFile, ADD_MODE_CLASS); ;
	addClassDialog->exec();
	ui.searchClassLineEdit->setText("");
	loadListClassTab();
}

//SLOT
// ----------- ADD COURSE TAB 
void MyClass:: refreshAddCourseAction()
{
	AddCourse *addCourseDialog = new AddCourse(0,0, dbFile, ADD_MODE_COURSE);
	addCourseDialog->exec();
	loadListCourseTab();
	ui.searchCourseLineEdit->setText("");

}
// SLOT
// --------------------- LIST COURSE TAB
void MyClass:: searchCourseAction()
{
	QString textSearchTemp = ui.searchCourseLineEdit->text();
	QString textSearch     = textSearchTemp.trimmed();

	QList< QMap<QString,QString> >res =  dbFile->getListByPartValue("course","name", textSearch);
	//delete all row and fill data
	listCourseModel->clear();
	QList<QString> headerList;
	headerList << "Course Name" << "Skill" << "Material" << "Edit" << "Delete";
	setHeaderTable(listCourseModel, headerList);
	fillListCourse(res, ui.listCourseTable, listCourseModel, 0);
}

void MyClass:: refreshCourseListAction()
{
	loadListCourseTab();
	ui.searchCourseLineEdit->setText("");
}

void MyClass:: loadCourseDialogAction(QString courseId)
{
	listCourseDialog *courseDialog = new listCourseDialog(this,dbFile,courseId);
	courseDialog->exec();
}

void MyClass:: editCourseAction(QString courseId)
{
	AddCourse *addCourseDialog = new AddCourse(0,0, dbFile, courseId); ;
	addCourseDialog->exec();
	loadListCourseTab();
	ui.searchCourseLineEdit->setText("");
}


/**
** Purpose: Confirm delete action-->delete database first --> delete row in QTableView
**/
void MyClass:: deleteCourseAction(QString courseId)
{
	int ret = QMessageBox::warning(this, tr("Delete course"),tr("All classes use this course will also be deleted. Please confirm !!"),
                        QMessageBox::Ok | QMessageBox::Cancel);

	if(ret == QMessageBox::Ok)
		deleteCourse(courseId);
}

void MyClass::loadDataAndHeaderListClass(QList< QMap<QString,QString> > resClass)
{
	listClassModel->clear();
	QList<QString> listHeader;
	listHeader << "ID" << "Class name" << "Registration day" << "Member" << "Course" 
			   << "% day" << "% material" << "EDIT" << "DELETE";
	setHeaderTable(listClassModel,listHeader);
			// resize columns
	ui.listClassTable->setColumnWidth(0,LIST_CLASS_COL_1);
	ui.listClassTable->setColumnWidth(1,LIST_CLASS_COL_2);
	ui.listClassTable->setColumnWidth(2,LIST_CLASS_COL_3);
	ui.listClassTable->setColumnWidth(3,LIST_CLASS_COL_4);
	ui.listClassTable->setColumnWidth(4,LIST_CLASS_COL_5);
	ui.listClassTable->setColumnWidth(5,LIST_CLASS_COL_6);
	ui.listClassTable->setColumnWidth(6,LIST_CLASS_COL_7);
	ui.listClassTable->setColumnWidth(7,LIST_CLASS_COL_8);
	ui.listClassTable->setColumnWidth(8,LIST_CLASS_COL_9);
	// fill value	
	fillListClass(resClass);
}

// SLOT 
// --------------------- LIST CLASS TAB
void MyClass:: searchClassAction()
{
	QString textSearchTemp = ui.searchClassLineEdit->text();
	QString textSearch     = textSearchTemp.trimmed();
	
	QList< QMap<QString,QString> > resClass = dbFile->getListByPartValue("class", "name", textSearch);
	loadDataAndHeaderListClass(resClass);
}

void MyClass:: refreshClassListAction()
{
	loadListClassTab();
}

void MyClass:: detailMemberAction(QString classId)
{
	listMemberDialog *dialog = new listMemberDialog(this,dbFile,classId);
	dialog->exec();
}

void MyClass:: editClassAction(QString classId)
{
	AddClass *addClassDialog = new AddClass(0,0, dbFile, classId); ;
	addClassDialog->exec();
	loadListClassTab();
	ui.searchClassLineEdit->setText("");
}

void MyClass:: deleteClassAction(QString classId)
{
	int ret = QMessageBox::warning(this, tr("Delete class"),tr("Please confirm !!"),
                        QMessageBox::Ok | QMessageBox::Cancel);

	if(ret == QMessageBox::Ok)
	{
		dbFile->deleteByField("materialuse","class_id",classId);
		QList< QMap<QString,QString> > resClassMember = dbFile->getListByField("class_member","class_id",classId);
		int numClassMember = resClassMember.count();
		for(int i=0;i<numClassMember;i++)
		{
			QString memberId = resClassMember.at(i)["member_id"];
			dbFile->deleteByField("member","id",memberId);
		}
		dbFile->deleteByField("class_member","class_id",classId);
		dbFile->deleteByField("class","id",classId);
		// Delete row of QTableView
		
		int rowCount = listClassModel->rowCount();
		for(int i =0; i < rowCount; i++)
		{	
			QString idCom = listClassModel->data(listClassModel->index(i,0), Qt::DisplayRole).toString();
			if(classId == idCom.trimmed() )
				listClassModel->removeRow(i);
		}
	}
}

