#include "addClass.h"

AddClass::AddClass( QWidget * parent, Qt::WindowFlags f,
				   databaseFile *dbFileOri, QString classId)
		: QDialog(parent, f)
{
	ui.setupUi(this);
	setConnection();
	classID = classId.toInt();
	dbFile = dbFileOri;
	loadConfigAddClass();
	loadDataAddClassTab(classID);
}

AddClass::~AddClass(void)
{
	delete addMemberModel;

	int skillModelListCount = skillModelList.count();
	for(int i=0;i<skillModelListCount;i++)
		delete skillModelList.at(i);

	int skillTableListCount = skillTableList.count();
	for(int i=0;i<skillTableListCount;i++)
		delete skillTableList.at(i);
}

void AddClass::setConnection()
{
	QObject::connect(ui.courseComboBox, SIGNAL(activated(QString)),
					this, SLOT(courseComboAction(QString)));
	QObject::connect(ui.saveButton_2, SIGNAL(clicked()),
					this, SLOT(saveClassAction()));
	QObject::connect(ui.cancelButton, SIGNAL(clicked()),
					this, SLOT(cancelClassAction()));

	QObject::connect(ui.enableClass1Button, SIGNAL(clicked()),
					this, SLOT(enableClassInfoAction()));
	QObject::connect(ui.enableClass2Button, SIGNAL(clicked()),
					this, SLOT(enableMemberAction()));
	QObject::connect(ui.enableClass3Button, SIGNAL(clicked()),
					this, SLOT(enableCourseAction()));
}


void AddClass:: loadConfigAddClass()
{
	ui.dayUseWidget->setVisible(false);

	enableForEditing.append(EDITCLASS_INFO_DISABLE);
	enableForEditing.append(EDITCLASS_MEMBER_DISABLE);
	enableForEditing.append(EDITCLASS_COURSE_DISABLE);

	// Set up member table View
	addMemberModel = new QStandardItemModel(this);
	ui.addMemberTable->setModel(addMemberModel);
	addMemberModel->clear();
	QList<QString> headerList;
	headerList << "Name" << "Birth year" << "Others";
	setHeaderTable(addMemberModel, headerList);
	setEmptyRowTable(addMemberModel,NUM_MEM_EMPTY);

	ui.addMemberTable->setColumnWidth(0,ADD_MEM_COL_1);
	ui.addMemberTable->setColumnWidth(1,ADD_MEM_COL_2);
	ui.addMemberTable->setColumnWidth(2,ADD_MEM_COL_3);

	clearItemsLayout(ui.courseInfoLayout);
	ui.courseComboBox->clear();
	ui.courseComboBox->addItem(tr("Choose course"));
	QList< QMap<QString,QString> > coList = dbFile->getAll("course");
	int numCourse = coList.count();
	for(int i =0;i<numCourse;i++)
		ui.courseComboBox->addItem(coList.at(i)["name"]);
	ui.courseComboBox->setCurrentIndex(0);
}

/**
  * Load data to Add Class tab with two method (create, edit) : base on ClassId 
  * @param classId 0:create  #0: edit
  */
void AddClass:: loadDataAddClassTab(int classId)
{
	if(classId == ADD_MODE_CLASS)
		loadAddModeInAddClassTab();
	else
	{
		loadConfigEditInAddClassTab();

		QString classIdStr = QString::number(classId);
		QList< QMap<QString,QString> > classRow = dbFile->getListByField("class","id",classIdStr);
		if(classRow.count()<=0)
			return;

		loadBasicInfoAddClassTab(classRow.at(0));// basic info of class
		loadMemberAddClassTab(classIdStr); // member info

		// load course of class
		QList < QMap<QString,QString> > courseRow = dbFile->getListByField("course","id",
																			classRow.at(0)["course_id"]);
		ui.courseClassLabel->setText(courseRow.at(0)["name"]);
		courseComboAction(courseRow.at(0)["name"]);// load material of skills + add radio button use/ not use
	}
}

void AddClass:: loadAddModeInAddClassTab()
{
	skillModelList.clear();
	skillTableList.clear();
	skillIdList.clear();	

	ui.dayUseWidget->setVisible(false);
	ui.courseInfoLabel->setText("");
	ui.classNameLineEdit->setText("");
	ui.totalDateLineEdit->setText("");	
	ui.otherLineEdit->setText("");
	ui.courseClassLabel->setText("");	

	ui.classNameLineEdit->setFocus();
	QDate curDate = QDate::currentDate();
	ui.regisdateEdit->setDate(curDate);	
	
	ui.enableClass1Button->setVisible(false);
	ui.enableClass2Button->setVisible(false);
	ui.enableClass3Button->setVisible(false);

	ui.groupBox->setVisible(false);
	ui.groupBox_2->setVisible(false);
	ui.groupBox_3->setVisible(false);

	ui.classAdd1Widget->setEnabled(true);
	ui.classAdd2Widget->setEnabled(true);
	ui.classAdd3Widget->setEnabled(true);
	ui.courseInfoLabel->setEnabled(true);
	ui.courseInfoWidget->setEnabled(true);
}

void AddClass:: clearItemsLayout(QLayout* layout)
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

/**
  * set Header for QTableView
  * @param model: of QTableView, listHeader : list of Header String
  */
void AddClass::setHeaderTable(QStandardItemModel *model, QList<QString> listHeader)
{
	int count = listHeader.count();
	for(int i =0;i<count;i++)
		model->setHorizontalHeaderItem(i, new QStandardItem(listHeader.at(i)));
}

/**
  * fill Table with empty value
  */
void AddClass::setEmptyRowTable(QStandardItemModel *model, int numRow)
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

bool AddClass:: isNumber(QString strCheck)
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

void AddClass:: loadConfigEditInAddClassTab()
{
	ui.enableClass1Button->setVisible(true);
	ui.enableClass2Button->setVisible(true);
	ui.enableClass3Button->setVisible(true);

	ui.groupBox->setVisible(true);
	ui.groupBox_2->setVisible(true);
	ui.groupBox_3->setVisible(true);

	ui.classAdd1Widget->setEnabled(false);
	ui.classAdd2Widget->setEnabled(false);
	ui.classAdd3Widget->setEnabled(false);
	ui.courseInfoLabel->setEnabled(false);
	ui.courseInfoWidget->setEnabled(false);
	ui.dayUseWidget->setVisible(true);

	addMemberModel->setHorizontalHeaderItem(3, new QStandardItem(tr("Delete")));
	addMemberModel->setHorizontalHeaderItem(4, new QStandardItem(tr("ID")));
	ui.addMemberTable->setColumnWidth(3,ADD_MEM_COL_4);
	ui.addMemberTable->setColumnWidth(4,ADD_MEM_COL_5);
	ui.addMemberTable->setColumnHidden(4,true);
}

void AddClass:: loadBasicInfoAddClassTab(QMap<QString,QString> classInfo)
{
	QString numLearnDay = classInfo["num_learning_day"];
	ui.dayUseSpinBox->setValue(numLearnDay.toInt());
	ui.classNameLineEdit->setText(classInfo["name"]);
	ui.totalDateLineEdit->setText( classInfo["total_day"]);
	ui.otherLineEdit->setText(classInfo["note"]);

	QString classDate    = classInfo["registration_day"];
	QStringList dateList = classDate.split("-");
	QDate dateIn;
	dateIn.setDate(dateList.at(0).toInt(),dateList.at(1).toInt(),dateList.at(2).toInt());
	ui.regisdateEdit->setDate(dateIn);
}

void AddClass::loadMemberAddClassTab(QString classIdStr)
{
	QList< QMap<QString,QString> > resClassMember = dbFile->getListByField("class_member","class_id",classIdStr);
	int countClass = resClassMember.count();
	for(int rowIndex =0; rowIndex < countClass; rowIndex ++)
	{
		QList< QMap<QString,QString> > memberRow = dbFile->getListByField("member","id",
															resClassMember.at(rowIndex)["member_id"]);
		addMemberModel->setItem(rowIndex,0,new QStandardItem(memberRow.at(0)["name"]));
		addMemberModel->setItem(rowIndex,1,new QStandardItem(memberRow.at(0)["birth_year"]));
		addMemberModel->setItem(rowIndex,2,new QStandardItem(memberRow.at(0)["note"]));
		addMemberModel->setItem(rowIndex,4,new QStandardItem(memberRow.at(0)["id"]));

		QSignalMapper *signalMapper = new QSignalMapper();
		QPushButton *deleteButton = addActionButton(DELETE_BUTTON, MAPPING_TYPE_STR, 
													memberRow.at(0)["id"],signalMapper,DISABLE_TEXT_BUTTON);
		QObject::connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(delMemberRowAction(QString)));
		ui.addMemberTable->setIndexWidget(addMemberModel->index(rowIndex,3),deleteButton);
	}
}

void AddClass:: courseComboAction(QString courseStr)
{
	clearItemsLayout(ui.courseInfoLayout);
	if(courseStr == DEFAULT_COURSE_BOX)
	{
		ui.courseInfoLabel->setText(tr(""));
		ui.courseClassLabel->setText(tr(""));	
		return;
	}
	skillModelList.clear();
	skillTableList.clear();
	skillIdList.clear();

	ui.courseClassLabel->setText(courseStr);
	QList< QMap<QString,QString> > courseList = dbFile->getListByField("course","name",courseStr);
	QString courseIdStr = courseList.at(0)["id"];
	fillMaterial4AddMember(courseIdStr);
	ui.courseInfoLabel->setText("<b>Course "+courseStr+" info</b>");
	if(classID == ADD_MODE_CLASS)
		return;

	QList< QMap<QString,QString> > clList = dbFile->getListByField("class","id",QString::number(classID));
	QList< QMap<QString,QString> > coList = dbFile->getListByField("course","id",clList.at(0)["course_id"]);

	addUseCheckBox(coList.at(0)["name"],courseStr);
}


/**
  *	Fill Course info : able to delete material ( but not edit). In edit | create mode --> # code
  * @param courseIdStr : course_id --> to load data
  */
void AddClass:: fillMaterial4AddMember(QString courseIdStr)
{	
	bool isCourseEditMode = checkCourseNew(courseIdStr, classID );
	QList< QMap<QString,QString> >  neededList;
	QList<QString> headerList;
	headerList << "ID" << "Material" << "Delete" ; //Header of each skill Box
	QList<QString> fields;
	QList<QString> fieldValues;
	
	if(isCourseEditMode == false) //load course  ( not in edit mode or in edit mode but new course)
	{
		neededList = dbFile->getListByField("course_skill","course_id",courseIdStr);
		fields << "skill_id" << "course_id";
	}
	else
	{
		neededList = dbFile->getListByFieldGroupByField("materialuse","class_id",
														QString::number(classID),"skill_id");
		fields << "class_id" << "skill_id";
	}

	int numList = neededList.count();
	for(int skillIndex = 0; skillIndex < numList ; skillIndex++)
	{
		QString skillId = neededList.at(skillIndex)["skill_id"];
		setSkillLabelInMaBox(skillId); // label skill
		
		//set header
		QTableView *skillTable = new QTableView();
		QStandardItemModel *skillModel = new QStandardItemModel();
		skillTable->setModel(skillModel);
		setHeaderTable(skillModel,headerList);
		skillTable->setColumnHidden(0,true);

		// Material of each skill 
		QList< QMap<QString,QString> > resultTable;
		fieldValues.clear();
		if(isCourseEditMode == false) //load course  ( not in edit mode or in edit mode but new course)
		{
			fieldValues << neededList.at(skillIndex)["skill_id"] << courseIdStr;
			resultTable = dbFile->getListByFields("skill_material",fields,fieldValues);
		}
		else
		{
			fieldValues << QString::number(classID) << skillId;
			resultTable = dbFile->getListByFields("materialuse",fields, fieldValues);
		}
		fillMaterialForEachSkill(resultTable,skillIndex,skillTable,skillModel);
		
		// Add to suitable list
		setSizeMaterialBox(skillTable );
		skillIdList.append(skillId);
		skillTableList.append(skillTable);
		skillModelList.append(skillModel);
		ui.courseInfoLayout->addWidget(skillTable);
	}
}


/**
  * use for load course in edit class( load checkbox to let that material use not not use)
  * if new course equal ex course -> no load. Otherwise, load ;)
  */
void AddClass:: addUseCheckBox(QString courseNameEdit,QString courseNameChoose)  
{
	if(courseNameEdit.trimmed()!=courseNameChoose.trimmed())
		return;

	int numList = skillModelList.count();
	for(int i=0;i<numList;i++)    // each table skill
	{
		QStandardItemModel *model = skillModelList.at(i);
		QString skillId           = skillIdList.at(i);
		model->setHorizontalHeaderItem(3, new QStandardItem("Use?"));
		int numRow    = model->rowCount();

		QList<QString> maFields;
		QList<QString> maFieldValues;
		maFields << "material_id" << "class_id";
		for(int r =0;r<numRow;r++)
		{
			QString materialId  = model->data(model->index(r,0),Qt::DisplayRole).toString();

			maFieldValues.clear();
			maFieldValues << materialId << QString::number(classID);
			QList< QMap<QString,QString> > maUseList  = dbFile->getListByFields("materialuse",maFields,maFieldValues);

			if(maUseList.count()<=0)
				continue;

			QStandardItem* item = new QStandardItem("Used ?");
			item->setCheckable(true);
			QString status      = maUseList.at(0)["status"];
			if(status == MATERIAL_NOTUSE)
				item->setCheckState(Qt::Unchecked);
			else
				item->setCheckState(Qt::Checked);
			
			model->setItem(r,3, item); 
		}
	}
}


/**
  * edit memeber In Edit Class Step 
  */

void AddClass::editMember()
{
	QList<QString> exMemberIdList = getMemIdInClass(classID);
	int numRow      = addMemberModel->rowCount();
	// id dont exist --> add member, id exist exMember -> edit , rest in  ExMember (old) : delete
	for(int r=0;r<numRow;r++)
	{
		QString memName = addMemberModel->data(addMemberModel->index(r,0),Qt::DisplayRole).toString().trimmed();
		if(memName.length()<=0)
			continue;

		QString memId   = addMemberModel->data(addMemberModel->index(r,4),
												Qt::DisplayRole).toString().trimmed();
		QString birth   = addMemberModel->data(addMemberModel->index(r,1),
												Qt::DisplayRole).toString().trimmed();
		QString note    = addMemberModel->data(addMemberModel->index(r,2),
												Qt::DisplayRole).toString().trimmed();

		QList<QString> memberInfo;
		memberInfo << memName << birth << note;

		if(memId=="") // add
		{
			QMap<QString,QString> memberRow = dbFile->insertItemWithKeyId("member",memberInfo);
			
			QList<QString> classMemInfo;
			classMemInfo << QString::number(classID) << memberRow["id"];
			dbFile->insertItemWithoutKeyId("class_member",classMemInfo);
		}
		else // edit
		{
			bool isMemberExist = checkItemExist(memId, exMemberIdList);
			if(isMemberExist == true)//edit
			{
				dbFile->editById("member",memId,memberInfo);
				exMemberIdList.removeOne(memId);
			}
		}
	}
	// delete rest item in list member
	int numExMember = exMemberIdList.count(); 
	for(int j =0;j<numExMember;j++)
		deleteMemberById(exMemberIdList.at(j));
}


/**
  * edit course in Edit Class step. 
  */

void AddClass::editCourse()
{
	QString cName       = ui.courseClassLabel->text();
	QList< QMap<QString,QString> > courseRow = dbFile->getListByField("course", "name", cName );

	if(courseRow.count()<=0)
		return;

	QString coId     = courseRow.at(0)["id"];
	QList< QMap<QString,QString> > classRow = dbFile->getListByField("class","id",QString::number(classID));

	bool isCourseNew = true;
	QString cId2     = classRow.at(0)["course_id"];
	if(coId==cId2) // course new or old?
		isCourseNew = false;

	//delete all, after that save new
	dbFile->deleteByField("materialuse","class_id",QString::number(classID));
	
	int numSkill = skillIdList.count();
	for(int i =0;i<numSkill;i++)
	{
		QStandardItemModel *model = skillModelList.at(i);
		QString  skillId		  = skillIdList.at(i);
		int numRow = model->rowCount();
		for(int j=0;j<numRow;j++)
		{
			QString useStatus = tr(MATERIAL_NOTUSE);
			if(isCourseNew == false)
			{
				QModelIndex index = model->index(j,3,QModelIndex());
				if(index.data(Qt::CheckStateRole) == Qt::Checked)
					useStatus = tr(MATERIAL_USED);
			}
			QString materialId = model->data(model->index(j,0),Qt::DisplayRole).toString().trimmed();
			QList<QString> matUseList;
			matUseList << materialId<< QString::number(classID) << skillId << useStatus;
			dbFile->insertItemWithoutKeyId("materialuse",matUseList);
		}
	}
}


/**
  * edit information of class in Edit Class step.
  */

void AddClass:: editClass()
{
	QString cName       = ui.courseClassLabel->text();
	QList< QMap<QString,QString> > courseRow = dbFile->getListByField("course","name",cName);
	QString coId        = courseRow.at(0)["id"];

	QList<QString> classListInfo;
	classListInfo << ui.classNameLineEdit->text() << coId << ui.regisdateEdit->date().toString("yyyy-MM-dd")
				  <<ui.totalDateLineEdit->text()<<ui.dayUseSpinBox->text() << ui.otherLineEdit->text();
	dbFile->editById("class",QString::number(classID),classListInfo);
}


/**
  * Check data before saving
  */
void AddClass:: saveClassAction()
{
	// validate data
	bool isDataPass = validateDataSaveClass();
	if (isDataPass == false)
		return;

	// SAVE
	if (classID == ADD_MODE_CLASS)
	{
		QList<QString> classListInfo;
		classListInfo << ui.classNameLineEdit->text() << "0" << ui.regisdateEdit->date().toString("yyyy-MM-dd")
			          << ui.totalDateLineEdit->text() << "0" <<ui.otherLineEdit->text();
		QMap<QString,QString> classInsert = dbFile->insertItemWithKeyId("class",classListInfo);
		if(classInsert.count() <= 0)
			return;
		
		//save members
		QList<QString> memberList = getMemberListSaveClass();
		saveMembersInClass(memberList, classInsert["id"]);

		//edit course_id to class table 
		QString courseName  = ui.courseClassLabel->text();
		QList< QMap<QString,QString> > courseList = dbFile->getListByField("course","name",courseName);
		dbFile->editOneFieldById("class", "id", classInsert["id"], "course_id", courseList.at(0)["id"]);

		//save material
		int skillNum = skillModelList.count();
		QList<QString> mateUseList;
		for(int i =0;i<skillNum;i++)
		{
			QStandardItemModel *skillModel = skillModelList.at(i);
			int materialRow                = skillModel->rowCount();
			for(int j=0;j<materialRow;j++)
			{
				QString materialId = skillModel->data(skillModel->index(j,0),Qt::DisplayRole).toString().trimmed();
				mateUseList.clear();
				mateUseList << materialId << classInsert["id"] << skillIdList.at(i) << "0";
				dbFile->insertItemWithoutKeyId("materialuse",mateUseList);
			}
		}
	}
	else // edit
	{
		if(enableForEditing.at(INDEX_MEMBER_INFO) == EDITCLASS_MEMBER_ENABLE )
		{
			editMember();
			enableForEditing[INDEX_MEMBER_INFO] = EDITCLASS_MEMBER_DISABLE;
		}
		if(enableForEditing.at(INDEX_COURSE_INFO) == EDITCLASS_COURSE_ENABLE)
		{
			editCourse();
			editClass();
			enableForEditing[INDEX_COURSE_INFO] = EDITCLASS_COURSE_DISABLE;
		}
		if(enableForEditing.at(INDEX_CLASS_INFO) == EDITCLASS_INFO_ENABLE)
		{
			editClass();
			enableForEditing[INDEX_CLASS_INFO] = EDITCLASS_INFO_DISABLE;
		}
	}
	close();
}


bool AddClass:: validateDataSaveClass()
{
	if (ui.classNameLineEdit->text()=="")
	{
		QMessageBox::warning(this,tr("Class name"),tr("Please fill the blank!!"));
		ui.classNameLineEdit->setFocus();
		return false;
	}
	else if(ui.totalDateLineEdit->text()=="" || isNumber(ui.totalDateLineEdit->text())==false) // check if a number
	{
		QMessageBox::warning(this,tr("Total days"),tr("Please fill the blank, and value is a NUMBER!!"));
		ui.totalDateLineEdit->setFocus();
		return false;
	}
	else if(ui.courseClassLabel->text()=="")
	{
		QMessageBox::warning(this,tr("Choose Course"),tr("Please select the suitable course!!"));
		return false;
	}

	QList<QString> memberList = getMemberListSaveClass();
	if (memberList.count() == 0 ) // check whether contain member
	{
		QMessageBox::warning(this,tr("Add Member"),tr("Please fill the member info!!"));
		return false;
	}	

	return true;
}

void AddClass:: enableClassInfoAction() // in editing mode
{	
	ui.enableClass1Button->setVisible(false);
	ui.classAdd1Widget->setEnabled(true);
	enableForEditing[INDEX_CLASS_INFO] = EDITCLASS_INFO_ENABLE;
}

void AddClass:: enableMemberAction()// in editing mode
{
	ui.enableClass2Button->setVisible(false);
	ui.classAdd2Widget->setEnabled(true);
	enableForEditing[INDEX_MEMBER_INFO] = EDITCLASS_MEMBER_ENABLE;
}

void AddClass:: enableCourseAction()
{
	ui.enableClass3Button->setVisible(false);
	ui.classAdd3Widget->setEnabled(true);
	ui.courseInfoLabel->setEnabled(true);
	ui.courseInfoWidget->setEnabled(true);
	enableForEditing[INDEX_COURSE_INFO] = EDITCLASS_COURSE_ENABLE;
}

void AddClass:: cancelClassAction()
{
	close();
//	loadDataAddClassTab(ADD_MODE_CLASS);
//	loadListClassTab();
//	ui.searchClassLineEdit->setText("");
/*
	QWidget * tab = ui.mainTab->widget(LIST_CLASS_TAB);
	ui.mainTab->setCurrentWidget(tab);
	classID = ADD_MODE_CLASS;

	ui.mainTab->setTabEnabled(LIST_CLASS_TAB ,true);
	ui.mainTab->setTabEnabled(ADD_CLASS_TAB  ,false);
	ui.mainTab->setTabEnabled(LIST_COURSE_TAB,true);
	ui.mainTab->setTabEnabled(ADD_COURSE_TAB ,false);
*/
}
/**
  * delete material in skill box info
  * @param materialNSkillIndex : "<material name> , <skill Index>"
  * skillindex : in skillModelList and skillTableList
  */
void AddClass::delMaterialTable(QString materialNSkillIndex)
{
	QStringList arr    = materialNSkillIndex.split(",");
	QString material   = arr.at(0);
	QString skillIndex = arr.at(1);
	int skillIndexInt  = skillIndex.toInt();
	
	QStandardItemModel *model = skillModelList.at(skillIndexInt);
	int rowCount			  = model->rowCount();
	for(int i = 0; i < rowCount; i++)
	{
		QString materialCom = model->data(model->index(i,1),Qt::DisplayRole).toString();
		if(material == materialCom)
		{
			model->removeRow(i);
			return;
		}
	}
}

QList<QString> AddClass::getMemberListSaveClass()
{
	int rowMember = addMemberModel->rowCount();
	QList<QString> memberList;
	for(int i = 0;i<rowMember;i++) // check number in birthyear and check whether have member
	{
		QString birthYear = addMemberModel->data(addMemberModel->index(i,1),Qt::DisplayRole).toString().trimmed();
		QString memberName = addMemberModel->data(addMemberModel->index(i,0),Qt::DisplayRole).toString().trimmed();
		if(memberName=="")
			continue;

		memberList.append(memberName);
		if( birthYear.length() > 0 && isNumber(birthYear) == false)
		{
			QMessageBox::warning(this,tr("Member infomation"),tr("Please fill a NUMBER for 'birth year' !!"));
			memberList.clear();
			return memberList;
		}
	}
	return memberList;
}

void AddClass::saveMembersInClass(QList<QString> memberList, QString classId)
{
	int numMember             = memberList.count();
	for(int i = 0;i<numMember;i++)
	{
		QString memberName = memberList.at(i);
		if(memberName == "")
			continue;

		QString birthYear = addMemberModel->data(addMemberModel->index(i,1),Qt::DisplayRole).toString().trimmed();
		QString note      = addMemberModel->data(addMemberModel->index(i,2),Qt::DisplayRole).toString().trimmed();
		
		QList<QString> memberListInfo;
		memberListInfo << memberName << birthYear << note;
		QMap<QString,QString> memberInsert = dbFile->insertItemWithKeyId("member",memberListInfo);
		if(memberInsert.count() <= 0)
			continue;

		QList<QString> classMemberInsert;
		classMemberInsert << classId << memberInsert["id"];
		dbFile->insertItemWithoutKeyId("class_member",classMemberInsert);
	}
}

void AddClass:: delMemberRowAction(QString memberId) //Edit class - member 
{
	int numRow = addMemberModel->rowCount();
	for(int i=0;i<numRow;i++)
	{
		QString memberGet = addMemberModel->data(addMemberModel->index(i,4),Qt::DisplayRole).toString().trimmed();
		if(memberGet==memberId)
		{
			addMemberModel->removeRow(i);
			return;
		}
	}
}


QPushButton* AddClass:: addActionButton(QString typeButton, QString mappingType, 
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

bool AddClass:: checkCourseNew(QString courseCompare, int classId )
{
	QList< QMap<QString,QString> > classRow = dbFile->getListByField("class","id",QString::number(classId));
	bool isCourseEditMode = false;
	if(classRow.count()>0) // edit mode
	{
		QString courseIDCurrent = classRow.at(0)["course_id"];
		if(courseIDCurrent == courseCompare) //  old course
			isCourseEditMode = true;
	}
	return isCourseEditMode;
}

void AddClass:: setSizeMaterialBox(QTableView *skillTable )
{
	skillTable->setColumnWidth(0,MATER_BOX_COL_1);
	skillTable->setColumnWidth(1,MATER_BOX_COL_2);
	skillTable->setColumnWidth(2,MATER_BOX_COL_3);
}

/**
  * Set skill label In Material Box
  */

void AddClass:: setSkillLabelInMaBox(QString skillId)
{
	QList< QMap<QString,QString> > skList = dbFile->getListByField("skill", "id", skillId);
	QLabel *skillLabel = new QLabel(tr("<b>")+skList.at(0)["name"]+tr("</b>"));
	ui.courseInfoLayout->addWidget(skillLabel);
}

/**
  * Parameter: materialRes --> List material
  *            skillIndex  --> index of skill to insert to list (skillIdList)
  *			   skillTable & skillModel : table and view of that TableView skill
  */
void AddClass:: fillMaterialForEachSkill(QList< QMap<QString,QString> > skMaList, int skillIndex, 
								  QTableView *skillTable, QStandardItemModel *skillModel)
{
	int numSkMaterial = skMaList.count();
	for(int rowIndex = 0 ;rowIndex<numSkMaterial;rowIndex++ )
	{
		QList< QMap<QString,QString> > mateList = dbFile->getListByField("material", "id",
																			skMaList.at(rowIndex)["material_id"]);
		skillModel->setItem(rowIndex,0, new QStandardItem(mateList.at(0)["id"])); //id
		skillModel->setItem(rowIndex,1, new QStandardItem(mateList.at(0)["name"] )); // material

		QString mappingData         = mateList.at(0)["name"]+tr(",")+QString::number(skillIndex);
		QSignalMapper *signalMapper = new QSignalMapper();
		QPushButton *deleteButton   = addActionButton(DELETE_BUTTON, MAPPING_TYPE_STR, mappingData,
													  signalMapper, DISABLE_TEXT_BUTTON);
		QObject::connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(delMaterialTable(QString)));
		skillTable->setIndexWidget(skillModel->index(rowIndex,2),deleteButton);
	}
}

QList<QString> AddClass:: getMemIdInClass(int classId)
{
	QList< QMap<QString,QString> > resClassMember = dbFile->getListByField("class_member","class_id",
																			QString::number(classId));
	int countClassMember = resClassMember.count();
	QList<QString> exMemberIdList;
	for(int i=0;i<countClassMember;i++)
		exMemberIdList.append(resClassMember.at(i)["member_id"]);

	return exMemberIdList;
}


bool AddClass:: checkItemExist(QString itemCheck, QList<QString> listItems)
{
	int numExMember = listItems.count();
	for(int j=0;j<numExMember;j++)
		if(listItems.at(j)==itemCheck) 
			return true;
	return false;
}

void AddClass:: deleteMemberById(QString memberId)
{
	dbFile->deleteByField("class_member","member_id",memberId);
	dbFile->deleteByField("member","id",memberId);
}
#include "moc_addClass.cpp"