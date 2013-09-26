#include "addCourse.h"

AddCourse::AddCourse(QWidget * parent, Qt::WindowFlags f, databaseFile *dbFileOri, QString courseId)
{	
	ui.setupUi(this);
	dbFile = dbFileOri;
	setConnection();
	courseID = courseId.toInt();
	if(courseID == ADD_MODE_COURSE)
		refreshToOriginAddCourse();
	else
	{
		ui.cancelCourseButton->setVisible(false);
		QList< QMap<QString,QString> > courseList = dbFile->getListByField("course","id",courseId);
		courseName  = courseList.at(0)["name"];
		courseMode  = EDIT_COURSE_MODE;
		ui.courseNameLineEdit->setText(courseName); // step1
		setup4Step2();
		setup4Step3();
		ui.step2Widget->setEnabled(false);
		ui.addMoreButton->setVisible(false);
	}
}

AddCourse::~AddCourse(void)
{
	int skillWidgetsCount = skillWidgets.count();
	for(int i=0;i<skillWidgetsCount;i++)
		delete skillWidgets.at(i);
}


void AddCourse::setConnection()
{
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
  * Fill Skill into Add Course Phage
  */
void AddCourse:: fillSkillsStep2() //edit + create
{
	if( courseMode == CREATE_COURSE_MODE)
	{
		// update info to ListWidget of step 2	
		QList< QMap<QString,QString> > skillList = dbFile->getAll("skill");
		int numSkill = skillList.count();
		for(int i = 0 ; i < numSkill; i++)
			ui.leftWidget->addItem(skillList.at(i)["name"]);
	}
	else if( courseMode == EDIT_COURSE_MODE)
	{
		QList< QMap<QString,QString> > coSkList = dbFile->getListByField("course_skill","course_id", 
																		QString::number(courseID));
		int numRow = coSkList.count();
		for(int i =0;i< numRow;i++)
		{
			QMap<QString,QString> coSkRow = coSkList.at(i);
			QList< QMap<QString,QString> > skillList = dbFile->getListByField("skill","id",coSkRow["skill_id"]);
			if(skillList.count()<=0)
				continue;

			QMap<QString,QString> skill = skillList.at(0);
			ui.rightWidget->addItem(skill["name"]);
		}
	}
}


/**
  * Setup data for step 2
  */
void AddCourse:: setup4Step2()// Main step 2 
{
	fillSkillsStep2();
	ui.line1_2->setVisible(true);
	ui.step2Widget->setVisible(true);

	QLabel *courseLabel = new QLabel(ui.classInsertGroupBox);
	courseLabel->setText("<b>Course name:</b>");
	ui.step1Layout->addWidget(courseLabel);

	QLabel *courseNameShow = new QLabel(ui.classInsertGroupBox);
	courseNameShow->setText(courseName);
	ui.step1Layout->addWidget(courseNameShow);
	if(courseMode == CREATE_COURSE_MODE)
		ui.resultLabel->setText("<span style='color:red'><b>Step1:Saved</b></span>");
}


void AddCourse:: saveCourseSKillTable(int numElementSkillBox)
{
	//save to course_skill table
	for(int i = 0;i<numElementSkillBox;i++)
	{
		QString skill = ui.rightWidget->item(i)->text();
		QList< QMap<QString,QString> > skillList = dbFile->getListByField("skill", "name", skill);
		if(skillList.count() <= 0)
			continue;

		QString skillIdTemp = skillList.at(0)["id"];
		QList<QString> infoInsert;
		infoInsert << QString::number(courseID) << skillIdTemp;
		dbFile->insertItemWithoutKeyId("course_skill", infoInsert);
	}
}


void AddCourse:: setupStep3Add(int numElementSkillBox) 
{
	QHBoxLayout *horizontalLayout_2;
	
	for( int i =0;i<numElementSkillBox;i++)
	{
		QSignalMapper *signalMapper = new QSignalMapper(this);
		QSignalMapper *signalMapper1 = new QSignalMapper(this);

		QString skill = ui.rightWidget->item(i)->text();
		skillsCourse.append(skill);

		QLabel *skillLabel = new QLabel("<b>"+skill+"</b>");
		ui.verticalLayout->addWidget(skillLabel);

		horizontalLayout_2 = new QHBoxLayout();
		horizontalLayout_2->setSpacing(6);
		horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

		QLabel *temp = new QLabel(ui.verticalLayoutWidget);
		horizontalLayout_2->addWidget(temp);

		QPushButton *addButton = new QPushButton(ui.verticalLayoutWidget);
		addButton->setText("Add material");
		horizontalLayout_2->addWidget(addButton);
		addButton->setObjectName(QString::fromUtf8("addMaterialButton")+QString::number(i));
		signalMapper->setMapping(addButton,skill+","+QString::number(i)+","+QString::number(courseID));
		QObject::connect(addButton,SIGNAL(clicked()),signalMapper, SLOT(map()));
		QObject::connect(signalMapper, SIGNAL(mapped(QString)),this, SLOT(addMaterialAction(QString)));

		QPushButton *listButton  = new QPushButton(ui.verticalLayoutWidget);
		listButton->setText("Edit materials");
		horizontalLayout_2->addWidget(listButton);
		listButton->setObjectName(QString::fromUtf8("listMaterialButton")+QString::number(i));
		signalMapper1->setMapping(listButton,skill+","+QString::number(i)+","+QString::number(courseID));
		QObject::connect(listButton,SIGNAL(clicked()),signalMapper1, SLOT(map()));
		QObject::connect(signalMapper1, SIGNAL(mapped(QString)),this, SLOT(listMaterialAction(QString)));

		QLabel *temp1 = new QLabel(ui.verticalLayoutWidget);
		horizontalLayout_2->addWidget(temp1);

		ui.verticalLayout->addLayout(horizontalLayout_2);
	}
}


void AddCourse:: setupInfoBoxStep2Save(int numElementBoxSkill)
{
	for(int i =0;i<numElementBoxSkill;i++)
	{
		QString skill = ui.rightWidget->item(i)->text();
		QLabel *skillLabel = new QLabel(skill);
		ui.step2Layout->addWidget(skillLabel);

		QListWidget *listSkill = new QListWidget(ui.step2WidgetInfo);
		if(courseMode == EDIT_COURSE_MODE)
		{
			QList< QMap<QString,QString> > skillRow = dbFile->getListByField("skill", "name", skill);
			QString skillId    = skillRow.at(0)["id"];
			
			QList<QString> fields;
			QList<QString> fieldValues;
			fields << "skill_id" << "course_id";
			fieldValues << skillId << QString::number(courseID);
			QList< QMap<QString,QString> > res = dbFile->getListByFields("skill_material",fields,fieldValues);
			int countRes = res.count();
			for(int i =0;i<countRes;i++)
			{	
				QString materialId    = res.at(i)["material_id"];
				QList< QMap<QString,QString> > materialRow = dbFile->getListByField("material","id",materialId);
				listSkill->addItem(materialRow.at(0)["name"]);
			}
		}
		ui.step2Layout->addWidget(listSkill);
		skillWidgets.append(listSkill);
	}
}

void AddCourse:: setup4Step3() // Main step 3 
{
	int numSkills = ui.rightWidget->count();

	//set up What appear in info added box
	setupStep3Add(numSkills);	// create + edit : ok 
	ui.line2_3->setVisible(true);
	ui.step3Widget->setVisible(true);
	ui.step2Widget->setEnabled(false);

	//set up what show in info box
	ui.skillLabelShow->setVisible(true);
	setupInfoBoxStep2Save(numSkills);		
	ui.resultLabel->setText("<span style='color:blue'><b>Step2:saved</b></span>");

	ui.saveCourseButton->setVisible(true);
	ui.addMoreButton->setVisible(true);
}

QString AddCourse:: materialBox(QString skill,bool &ok)
{
	QString text = QInputDialog::getText(this, tr("Add Material to ") + skill,tr("Material:"), 
										QLineEdit::Normal, tr("try try"),&ok);
	return text;
}


/**
  * @param skillNID : "<skill>,<index>"
  */
bool AddCourse:: isAddMaterial(QString skillNIndex)
{
	bool ok;
	QStringList stringlist = skillNIndex.split(",");
	QString skill = stringlist.at(0);
	QString index = stringlist.at(1);

	QString text =  materialBox(skill,ok);
	if (!(ok && !text.isEmpty()))
		return false;

	// check Material Exist
	int in = index.toInt();
	QListWidget *list =  skillWidgets.at(in);
	bool isMaExist = isItemExist(text,list);
	if(isMaExist == true) 
		return false;

	// Insert success or not
	QList<QString> matList;
	matList.append(text);
	QMap<QString,QString> insertRow =  dbFile->insertItemWithKeyId("material",matList);
	int idMaterial  = insertRow["id"].toInt();
	if(idMaterial ==-1 )
		return false;

	//insert into skill_material table	
	QList< QMap<QString,QString> > skillList =  dbFile->getListByField("skill", "name", skill);
	if(skillList.count() <= 0)
		return false;
	
	QString idSkill = skillList.at(0)["id"];
	QList<QString> skillMaterialList;
	skillMaterialList <<idSkill <<QString::number(idMaterial)<<QString::number(courseID);
	QMap<QString,QString> insertSkillMat =  dbFile->insertItemWithoutKeyId("skill_material",skillMaterialList);
	idMaterial     = insertSkillMat["material_id"].toInt();
	if(idMaterial != -1)
		list->addItem(text);
	
	return ok;
}

void AddCourse:: loadConfigAddCourseTab()
{
	ui.saveCourseButton->setVisible(false);
	ui.line1_2->setVisible(false);
	ui.line2_3->setVisible(false);
	ui.step2Widget->setVisible(false);
	ui.step3Widget->setVisible(false);
	ui.skillLabelShow->setVisible(false);
	ui.addMoreButton->setVisible(false);
	courseName = "";
	courseID   = ADD_MODE_COURSE;
	courseMode = CREATE_COURSE_MODE;
	ui.courseNameLineEdit->setFocus();
}


void AddCourse:: refreshToOriginAddCourse() 
{
	loadConfigAddCourseTab();

	ui.cancelCourseButton->setVisible(true);
	ui.courseNameLineEdit->setText("");
	ui.courseNameLineEdit->setText("");
	ui.step1Widget->setEnabled(true);
	ui.step2Widget->setEnabled(true);
	ui.resultLabel->setText("");
	ui.skillLabelShow->setVisible(false);

	clearItemsLayout(ui.step1Layout);
	clearItemsLayout(ui.step2Layout);
	clearItemsLayout(ui.verticalLayout);

	//step 2 
	int numLeft  = ui.leftWidget->count();
	int numRight = ui.rightWidget->count();
	for (int i = 0; i < numLeft; i++)
		ui.leftWidget->takeItem(0);
	for (int i = 0; i < numRight; i++)
		ui.rightWidget->takeItem(0);

	courseName = "";
	courseID   = ADD_MODE_COURSE;
	courseMode = CREATE_COURSE_MODE;
	skillsCourse.clear();
	skillWidgets.clear();
	ui.courseNameLineEdit->setFocus();
}


void AddCourse:: step1SaveAction() // disable step 1, enable step 2, update info to info box
{
	// check box name is empty
	if(ui.courseNameLineEdit->text().trimmed() == "")
	{
		QMessageBox::warning(this,tr("Course name"),tr("Please fill the blank!!"));
		ui.courseNameLineEdit->setFocus();
		return;
	}
	courseName = ui.courseNameLineEdit->text();

	if(courseMode == CREATE_COURSE_MODE)
	{
		ui.step1Widget->setEnabled(false);
		QList<QString> courseList;
		courseList.append(courseName);
		QMap<QString,QString> courseMap = dbFile->insertItemWithKeyId("course",courseList);
		courseID = courseMap["id"].toInt();
		setup4Step2();
	}
	else 
	{
		dbFile->editOneFieldById("course","id", QString::number(courseID),"name", courseName);

		//update info box
		clearItemsLayout(ui.step1Layout);
		QLabel *courseLabel = new QLabel(ui.classInsertGroupBox);
		courseLabel->setText("<b>Course name:</b>");
		ui.step1Layout->addWidget(courseLabel);

		QLabel *courseNameShow = new QLabel(ui.classInsertGroupBox);
		courseNameShow->setText(courseName);
		ui.step1Layout->addWidget(courseNameShow);

		ui.resultLabel->setText("<span style='color:red'><b>Step1:Saved</b></span>");
	}
	return;
}


void AddCourse:: step2SaveAction() // save value to skillsCourse, fill step 3 info, step 3 appear, fill info into info bo
{
	int numSkills = ui.rightWidget->count();
	if(numSkills == 0)
	{
		QMessageBox::warning(this,tr("Skill choice"),tr("Please choose skills!!"));
		return;
	}

	if(courseMode == CREATE_COURSE_MODE)
		saveCourseSKillTable(numSkills);

	setup4Step3();
}


void AddCourse:: addSkillAction()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Add Skill"),tr("Skill:"), QLineEdit::Normal, tr("try try"),&ok);

	if (ok && !text.isEmpty())
	{
		QList< QMap<QString,QString> > skillList = dbFile->getAll("skill");
		QList<QString> listItems;
		int numSkill = skillList.count();
		for(int i=0;i<numSkill;i++)
			listItems.append(skillList.at(i)["name"]);

		if(checkItemExist(text, listItems) == true) // item exist -> not add
			return;

		QList<QString> skList;
		skList.append(text);
		dbFile->insertItemWithKeyId("skill",skList);
		ui.leftWidget->addItem(text);
	}
}


void AddCourse:: left2RightAction()
{
	ui.rightWidget->addItem(ui.leftWidget->takeItem(ui.leftWidget->currentRow()));
}

void AddCourse:: right2LeftAction()
{
	ui.leftWidget->addItem(ui.rightWidget->takeItem(ui.rightWidget->currentRow()));
}

void AddCourse:: all2LeftAction()
{
	int numElements = ui.rightWidget->count();
	for(int i =0;i<numElements;i++)
	{
		QListWidgetItem *item = ui.rightWidget->takeItem(0);
		ui.leftWidget->addItem(item);
	}
}

void AddCourse:: all2RightAction()
{
	int numElements = ui.leftWidget->count();
	for(int i =0;i<numElements;i++)
	{
		QListWidgetItem *item = ui.leftWidget->takeItem(0);
		ui.rightWidget->addItem(item);
	}
}

void AddCourse:: left2RightClickAction()
{
	QListWidgetItem *item2 = ui.leftWidget->takeItem(ui.leftWidget->currentRow());
	ui.rightWidget->addItem(item2);
}

void AddCourse:: right2LeftClickAction()
{
	QListWidgetItem *item2 = ui.rightWidget->takeItem(ui.rightWidget->currentRow());
	ui.leftWidget->addItem(item2);
}

/**
  * Clisk to "edit material" button 
  *	@param skillNIndex : "<skill>,<index>" (index: index trong skillWidgets [thu tu skills])
  */
void AddCourse:: listMaterialAction(QString skillNIndex)
{
	QStringList stringlist = skillNIndex.split(",");
	QString skill = stringlist.at(0);
	QString index = stringlist.at(1);
	std::string temp1 = index.toStdString();
	const char* temp2 = temp1.c_str();
	int indexInt  = atoi(temp2);

	listMaterialDialog *dialog = new listMaterialDialog(this,dbFile,skill,courseID);
	dialog->exec();
	bool isChange = dialog->isChanged;
	if(isChange == false) 
		return;

	QList< QMap<QString,QString> > skillList =  dbFile->getListByField("skill", "name", skill);
	QString skillId    = skillList.at(0)["id"];
	//Clear old list, and add new list --> Box Info
	QListWidget *listWidget = skillWidgets.at(indexInt);
	listWidget->clear();
	QString courseIdStr  = QString::number(courseID);
	//getListByFields
	QList<QString> fieldList;
	QList<QString> valueList;
	fieldList << "skill_id" << "course_id" ;
	valueList << skillId << courseIdStr;
	QList< QMap<QString,QString > > skiMaList = dbFile->getListByFields("skill_material",fieldList,valueList);

	int numRow = skiMaList.count();
	if(numRow <= 0)
		return;

	for(int i=0; i <numRow; i++)
	{
		QString maId = skiMaList.at(i)["material_id"];
		QList< QMap<QString,QString> > maList = dbFile->getListByField("material","id",maId);
		if(maList.count() <= 0)
			continue;

		QString ma   = maList.at(0)["name"];
		listWidget->addItem(ma);
	}
}
/**
  * @param skillNID : "<skill>,<id>"
  */	
void AddCourse:: addMaterialAction(QString skillNIndex)
{			
	bool isAdd = isAddMaterial(skillNIndex);
	while(isAdd ==true)
	{
		ui.resultLabel->setText("<span style='color:green'><b>Material: saved</b></span>");
		isAdd = isAddMaterial(skillNIndex);
	}
}

void AddCourse:: saveCourseAction()
{
	if(courseMode == EDIT_COURSE_MODE)
		step1SaveAction();
	close();
}

void AddCourse:: cancelCourseAction()
{
	if(courseMode == CREATE_COURSE_MODE && courseID != ADD_MODE_COURSE)
		deleteCourse(QString::number(courseID));
	close();
}


bool AddCourse:: isItemExist(QString item,QListWidget *list)
{
	int numItem = list->count();
	for(int i=0;i<numItem;i++)
	{
		QString maComp = list->item(i)->text();
		if(maComp==item)
			return true;
	}
	return false;
}


void AddCourse:: clearItemsLayout(QLayout* layout)
{
	while(QLayoutItem *item = layout->takeAt(0))
	{
		if (item->layout()) 
		{
			clearItemsLayout(item->layout());
			delete item->layout();
		}
		else if (item->widget()) 
			delete item->widget();
	}
}


bool AddCourse:: checkItemExist(QString itemCheck, QList<QString> listItems)
{
	int numExMember = listItems.count();
	for(int j=0;j<numExMember;j++)
		if(listItems.at(j)==itemCheck) 
			return true;
	return false;
}


void AddCourse:: deleteCourse(QString courseId) // delete course base on course id --> delete all thing related to course
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
/*
	int rowCount = listCourseModel->rowCount();
	for(int i =0; i < rowCount; i++)
		if(nameCourse == listCourseModel->data(listCourseModel->index(i,0), Qt::DisplayRole).toString())
			listCourseModel->removeRow(i);
*/
}

void AddCourse:: refreshAddCourseAction()
{

}