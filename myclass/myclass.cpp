#include "myclass.h"

MyClass::MyClass(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	dbFile = new databaseFile();
	setConnection();
	loadConfigAddCourseTab();
	loadListCourseTab();
	loadOriginConfig();

	loadConfigClass();
	loadDataAddClassTab(0);
	loadListClassTab();
}

MyClass::~MyClass()
{
	delete dbFile;

	delete listCourseModel;

	int skillWidgetsCount = skillWidgets.count();
	for(int i=0;i<skillWidgetsCount;i++)
		delete skillWidgets.at(i);

	delete listClassModel;
	delete addMemberModel;

	int skillModelListCount = skillModelList.count();
	for(int i=0;i<skillModelListCount;i++)
		delete skillModelList.at(i);

	int skillTableListCount = skillTableList.count();
	for(int i=0;i<skillTableListCount;i++)
		delete skillTableList.at(i);

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

	// add class
	QObject::connect(ui.classComboBox, SIGNAL(activated(QString)),
					this, SLOT(courseComboAction(QString)));
	QObject::connect(ui.saveButton_2, SIGNAL(clicked()),
					this, SLOT(saveClassAction()));
	QObject::connect(ui.cancelButton, SIGNAL(clicked()),
					this, SLOT(cancelClassAction()));

	//enableClass1Button
	QObject::connect(ui.enableClass1Button, SIGNAL(clicked()),
					this, SLOT(enableClassInfoAction()));
	QObject::connect(ui.enableClass2Button, SIGNAL(clicked()),
					this, SLOT(enableMemberAction()));
	QObject::connect(ui.enableClass3Button, SIGNAL(clicked()),
					this, SLOT(enableCourseAction()));
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

	ui.cancelCourseButton->setVisible(false);
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
		ui.mainTab->setTabEnabled(0,true);
		ui.mainTab->setTabEnabled(1,false);
		ui.mainTab->setTabEnabled(2,true);
		ui.mainTab->setTabEnabled(3,false);
	}

void MyClass:: clearItemsLayout(QLayout* layout)
{
	while(QLayoutItem *item = layout->takeAt(0))
		if (item->layout()) 
		{
			clearItemsLayout(item->layout());
			delete item->layout();
		}
		else if (item->widget()) 
			delete item->widget();
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

bool MyClass:: isItemExist(QString item,QListWidget *list)
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

bool MyClass:: checkItemExist(QString itemCheck, QList<QString> listItems)
{
	int numExMember = listItems.count();
	for(int j=0;j<numExMember;j++)
		if(listItems.at(j)==itemCheck) 
			return true;
	return false;
}

// --------------------------- ADD CLASS TAB

/**
  * edit memeber In Edit Class Step 
  */
void MyClass::editMember()
{
	QList<QString> exMemberIdList;
	QList< QMap<QString,QString> > resClassMember = dbFile->getListByField("class_member","class_id",
																			QString::number(classID));
	int countClassMember = resClassMember.count();
	for(int i=0;i<countClassMember;i++)
		exMemberIdList.append(resClassMember.at(i)["member_id"]);

	int numRow      = addMemberModel->rowCount();
	// id ko co --> add, id trong table co trong exMember -> edit , con lai trong ExMember : delete
	for(int r=0;r<numRow;r++)
	{
		QString memName = addMemberModel->data(addMemberModel->index(r,0),Qt::DisplayRole).toString().trimmed();
		if(memName.length()>0)
		{
			QString memId   = addMemberModel->data(addMemberModel->index(r,4),
													Qt::DisplayRole).toString().trimmed();
			QString birth   = addMemberModel->data(addMemberModel->index(r,1),
													Qt::DisplayRole).toString().trimmed();
			QString note    = addMemberModel->data(addMemberModel->index(r,2),
													Qt::DisplayRole).toString().trimmed();
			if(memId=="") // add
			{
				QList<QString> memberListInfo;
				memberListInfo << memName << birth << note;
				QMap<QString,QString> memberRow = dbFile->insertItemWithKeyId("member",memberListInfo);
				
				QList<QString> classMemInfo;
				classMemInfo << QString::number(classID) << memberRow["id"];
				dbFile->insertItemWithoutKeyId("class_member",classMemInfo);
			}
			else // edit
			{
				bool isMemberExist = checkItemExist(memId, exMemberIdList);
				if(isMemberExist == true)//edit
				{
					QList<QString> memberInfo;
					memberInfo << memName << birth << note;
					dbFile->editById("member",memId,memberInfo);
					exMemberIdList.removeOne(memId);
				}
			}
		}
	}
	// delete rest item in list member
	int numExMember = exMemberIdList.count(); 
	for(int j =0;j<numExMember;j++)
	{
		dbFile->deleteByField("class_member","member_id",exMemberIdList.at(j));
		dbFile->deleteByField("member","id",exMemberIdList.at(j));
	}
}

/**
  * edit course in Edit Class step. 
  */
void MyClass::editCourse()
{
	QString cName       = ui.courseClassLabel->text();
	QList< QMap<QString,QString> > courseRow = dbFile->getListByField("course", "name", cName );
	if(courseRow.count()>0)
	{
		QString coId        = courseRow.at(0)["id"];
		QList< QMap<QString,QString> > classRow = dbFile->getListByField("class","id",QString::number(classID));
		bool isCourseNew = true;
		QString cId1     = courseRow.at(0)["id"];
		QString cId2     = classRow.at(0)["course_id"];
		if(cId1==cId2) // course new or old?
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
				QString useStatus = tr("0");
				if(isCourseNew ==false)
				{
					QModelIndex index = model->index(j,3,QModelIndex());
					if(index.data(Qt::CheckStateRole) == Qt::Checked)
						useStatus = tr("1");
				}
				QString materialId = model->data(model->index(j,0),Qt::DisplayRole).toString().trimmed();
				QList<QString> matUseList;
				matUseList << materialId<< QString::number(classID) << skillId << useStatus;
				dbFile->insertItemWithoutKeyId("materialuse",matUseList);
			}
		}
	}
}

/**
  * edit information of class in Edit Class step.
  */
void MyClass:: editClass()
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
  * use for load course in edit class( load checkbox to let that material use not not use)
  */
void MyClass:: addUseCheckBox(QString courseNameEdit,QString courseNameChoose)  
{
	if(courseNameEdit.trimmed()==courseNameChoose.trimmed())
	{
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
				//materialUse_searchByClassIdNSkillId
				QString materialId  = model->data(model->index(r,0),Qt::DisplayRole).toString();

				maFieldValues.clear();
				maFieldValues << materialId << QString::number(classID);
				QList< QMap<QString,QString> > maUseList  = dbFile->getListByFields("materialuse",maFields,maFieldValues);
				if(maUseList.count()>0)
				{
					QStandardItem* item = new QStandardItem("Used ?");
					item->setCheckable(true);
					QString status      = maUseList.at(0)["status"];
					if(status=="0")
						item->setCheckState(Qt::Unchecked);
					else
						item->setCheckState(Qt::Checked);
					
					model->setItem(r,3, item); 
				}
			}
		}
	}
}

/**
  * load confif of list class and add class at the constructor
  */
void MyClass:: loadConfigClass()
{
	addMemberModel = new QStandardItemModel(this);
	ui.addMemberTable->setModel(addMemberModel);
	
	listClassModel = new QStandardItemModel(this); 
	ui.listClassTable->setModel(listClassModel);

	classID =0;
	ui.dayUseWidget->setVisible(false);
}


/**
  * Load data to Add Class tab with two method (create, edit) : base on ClassId 
  * @param classId 0:create  #0: edit
  */
void MyClass:: loadDataAddClassTab(int classId)
{
	if(classId ==0)
	{
		enableForEditing.append(false);
		enableForEditing.append(false);
		enableForEditing.append(false);

		skillModelList.clear();
		skillTableList.clear();
		skillIdList.clear();

		ui.dayUseWidget->setVisible(false);
		ui.courseInfoLabel->setText("");
		ui.classNameLineEdit->setText("");
		ui.totalDateLineEdit->setText("");
		addMemberModel->clear();
		ui.otherLineEdit->setText("");
		ui.classComboBox->clear();
		ui.courseClassLabel->setText("");
		clearItemsLayout(ui.courseInfoLayout);

		ui.courseNameLineEdit->setFocus();
		QDate curDate = QDate::currentDate();
		ui.regisdateEdit->setDate(curDate);
		// Set up member table View
		QList<QString> headerList;
		headerList << "Name" << "Birth year" << "Others";
		setHeaderTable(addMemberModel, headerList);
		setEmptyRowTable(addMemberModel,10);

		ui.addMemberTable->setColumnWidth(0,110);
		ui.addMemberTable->setColumnWidth(1,60);
		ui.addMemberTable->setColumnWidth(2,40);

		ui.classComboBox->addItem(tr("Choose course"));

		QList< QMap<QString,QString> > coList = dbFile->getAll("course");
		int numCourse = coList.count();
		for(int i =0;i<numCourse;i++)
			ui.classComboBox->addItem(coList.at(i)["name"]);
		
		ui.classComboBox->setCurrentIndex(0);
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
	else
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

		QString classIdStr = QString::number(classId);
		ui.dayUseWidget->setVisible(true);
		
		QList< QMap<QString,QString> > classRow = dbFile->getListByField("class","id",classIdStr);
		if(classRow.count()>0)
		{
			QString numLearnDay = classRow.at(0)["num_learning_day"];
			ui.dayUseSpinBox->setValue(numLearnDay.toInt());
			ui.classNameLineEdit->setText(classRow.at(0)["name"]);
			QString classDate = classRow.at(0)["registration_day"];
			QStringList dateList = classDate.split("-");
			QDate dateIn;
			dateIn.setDate(dateList.at(0).toInt(),dateList.at(1).toInt(),dateList.at(2).toInt());
			ui.regisdateEdit->setDate(dateIn);

			ui.totalDateLineEdit->setText( classRow.at(0)["total_day"]);
			ui.otherLineEdit->setText(classRow.at(0)["note"]);

			addMemberModel->setHorizontalHeaderItem(3, new QStandardItem(tr("Delete")));
			addMemberModel->setHorizontalHeaderItem(4, new QStandardItem(tr("ID")));
			ui.addMemberTable->setColumnWidth(3,50);
			ui.addMemberTable->setColumnWidth(4,30);
			ui.addMemberTable->setColumnHidden(4,true);
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

				QPushButton *deleteButton = new QPushButton(ui.addMemberTable);
				QIcon ButtonIcon1;
				ButtonIcon1.addFile(QString::fromUtf8("Resources/Delete_icon.png"), QSize(), 
									QIcon::Normal, QIcon::Off);
				deleteButton->setIcon(ButtonIcon1);
				QSignalMapper *signalMapper = new QSignalMapper(ui.addMemberTable);
				signalMapper->setMapping(deleteButton,memberRow.at(0)["id"]);
				QObject::connect(deleteButton,SIGNAL(clicked()),signalMapper,SLOT(map()));
				QObject::connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(delMemberRowAction(QString)));
				ui.addMemberTable->setIndexWidget(addMemberModel->index(rowIndex,3),deleteButton);
			}

			// course of class
			QList < QMap<QString,QString> > courseRow = dbFile->getListByField("course","id",
																				classRow.at(0)["course_id"]);
			ui.courseClassLabel->setText(courseRow.at(0)["name"]);
			 // load material of skills + add radio button use/ not use
			courseComboAction(courseRow.at(0)["name"]);
		}
	
	}
}

/**
  *	Fill Course info : able to delete material ( but not edit). In edit | create mode --> # code
  * @param courseIdStr : course_id --> to load data
  */
void MyClass:: fillMaterial4AddMember(QString courseIdStr)
{	
	QList< QMap<QString,QString> > classRow = dbFile->getListByField("class","id",QString::number(classID));
	bool isCourseEditMode = false;
	if(classRow.count()>0) // edit mode
	{
		QString courseIDCurrent = classRow.at(0)["course_id"];
		if(courseIDCurrent==courseIdStr) //  old course
			isCourseEditMode = true;
	}

	if(isCourseEditMode == false) //load course  ( not in edit mode or in edit mode but new course)
	{
		QList< QMap<QString,QString> >  coSkList = dbFile->getListByField("course_skill","course_id",courseIdStr);
		int numCoSk = coSkList.count();
		for(int skillIndex = 0;skillIndex<numCoSk;skillIndex++)
		{
			QTableView *skillTable = new QTableView(ui.addClassTab);
			QStandardItemModel *skillModel = new QStandardItemModel(ui.addClassTab);
			skillTable->setModel(skillModel);

			QList<QString> headerList;
			headerList << "ID" << "Material" << "Delete" ;
			setHeaderTable(skillModel,headerList);
			skillTable->setColumnHidden(0,true);
			
			QList< QMap<QString,QString> > skList = dbFile->getListByField("skill", "id", 
																			coSkList.at(skillIndex)["skill_id"]);
			QLabel *skillLabel = new QLabel(tr("<b>")+skList.at(0)["name"]+tr("</b>"));
			ui.courseInfoLayout->addWidget(skillLabel);
			
			// QTableView of each skill
			QList<QString> fields;
			QList<QString> fieldValues;
			fields << "skill_id" << "course_id";
			fieldValues << coSkList.at(skillIndex)["skill_id"] << courseIdStr;
			QList< QMap<QString,QString> > skMaList = dbFile->getListByFields("skill_material",fields,fieldValues);
			int numSkMaterial = skMaList.count();
			for(int rowIndex = 0 ;rowIndex<numSkMaterial;rowIndex++ )
			{
				QList< QMap<QString,QString> > mateList = dbFile->getListByField("material", "id", 
																				 skMaList.at(rowIndex)["material_id"]);
				skillModel->setItem(rowIndex,0, new QStandardItem(mateList.at(0)["id"])); //id
				skillModel->setItem(rowIndex,1, new QStandardItem(mateList.at(0)["name"])); // material
				
				QPushButton *deleteButton = new QPushButton(ui.addClassTab);
				QIcon ButtonIcon1;
				ButtonIcon1.addFile(QString::fromUtf8("Resources/Delete_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
				deleteButton->setIcon(ButtonIcon1);
				QSignalMapper *signalMapper = new QSignalMapper(ui.addClassTab);
				signalMapper->setMapping(deleteButton,mateList.at(0)["name"]+tr(",")+QString::number(skillIndex));
				QObject::connect(deleteButton,SIGNAL(clicked()),signalMapper,SLOT(map()));
				QObject::connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(delMaterialTable(QString)));
				skillTable->setIndexWidget(skillModel->index(rowIndex,2),deleteButton);

			}
			skillTable->setColumnWidth(0,50);
			skillTable->setColumnWidth(1,200);
			skillTable->setColumnWidth(2,50);

			skillIdList.append(skList.at(0)["id"]);
			skillTableList.append(skillTable);
			skillModelList.append(skillModel);
			ui.courseInfoLayout->addWidget(skillTable);
		}
	}
	else
	{
		QList< QMap<QString,QString> > maUseList = dbFile->getListByFieldGroupByField("materialuse","class_id",
																					 QString::number(classID),"skill_id");
		int numMaUse = maUseList.count();
		for(int skillIndex = 0;skillIndex<numMaUse;skillIndex++)
		{
			QString skillId = maUseList.at(skillIndex)["skill_id"];
			QList< QMap<QString,QString> > skillRow = dbFile->getListByField("skill","id",skillId); 
			QLabel *skillLabel = new QLabel(tr("<b>")+skillRow.at(0)["name"]+tr("</b>"));
			ui.courseInfoLayout->addWidget(skillLabel);

			QTableView *skillTable = new QTableView(ui.addClassTab);
			QStandardItemModel *skillModel = new QStandardItemModel(ui.addClassTab);
			skillTable->setModel(skillModel);

			QList<QString> headerList;
			headerList << "ID" << "Material" << "Delete" ;
			setHeaderTable(skillModel,headerList);
			skillTable->setColumnHidden(0,true);
			
			QList<QString> fies;
			QList<QString> fiValues;
			fies << "class_id" << "skill_id";
			fiValues << QString::number(classID) << skillId;
			QList< QMap<QString,QString> > resMaterialUse = dbFile->getListByFields("materialuse",fies, fiValues);
			int countResMaUse = resMaterialUse.count();
			for(int rowIndex = 0;rowIndex<countResMaUse;rowIndex++)
			{
				QList< QMap<QString,QString> > materialRow = dbFile->getListByField("material", "id",
																					resMaterialUse.at(rowIndex)["material_id"]);
				skillModel->setItem(rowIndex,0, new QStandardItem(materialRow.at(0)["id"])); //id
				skillModel->setItem(rowIndex,1, new QStandardItem(materialRow.at(0)["name"] )); // material

				QPushButton *deleteButton = new QPushButton(ui.addClassTab);
				QIcon ButtonIcon1;
				ButtonIcon1.addFile(QString::fromUtf8("Resources/Delete_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
				deleteButton->setIcon(ButtonIcon1);
				QSignalMapper *signalMapper = new QSignalMapper(ui.addClassTab);
				signalMapper->setMapping(deleteButton,materialRow.at(0)["name"]+tr(",")+QString::number(skillIndex));
				QObject::connect(deleteButton,SIGNAL(clicked()),signalMapper,SLOT(map()));
				QObject::connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(delMaterialTable(QString)));
				skillTable->setIndexWidget(skillModel->index(rowIndex,2),deleteButton);
			}
			skillTable->setColumnWidth(0,50);
			skillTable->setColumnWidth(1,200);
			skillTable->setColumnWidth(2,50);

			skillIdList.append(skillRow.at(0)["id"]);
			skillTableList.append(skillTable);
			skillModelList.append(skillModel);
			ui.courseInfoLayout->addWidget(skillTable);
		}
	}
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
	// delete class use the course
	dbFile->deleteByField("class","course_id",courseId);

	// Delete row of QTableView
	int rowCount = listCourseModel->rowCount();
	for(int i =0; i < rowCount; i++)
		if(nameCourse == listCourseModel->data(listCourseModel->index(i,0), Qt::DisplayRole).toString())
			listCourseModel->removeRow(i);

	//reload List Class
	loadListClassTab();
}

/**
  * Fill Skill into Add Course Phage
  */
void MyClass:: fillSkillsStep2() //edit + create
{
	if(courseMode == "CREATE")
	{
		// update info to ListWidget of step 2	
		QList< QMap<QString,QString> > skillList = dbFile->getAll("skill");
		int numSkill = skillList.count();
		for(int i = 0 ; i < numSkill; i++)
			ui.leftWidget->addItem(skillList.at(i)["name"]);
	}
	else
	{
		QList< QMap<QString,QString> > coSkList = dbFile->getListByField("course_skill","course_id", 
																		QString::number(courseID));
		int numRow = coSkList.count();
		for(int i =0;i< numRow;i++)
		{
			QMap<QString,QString> coSkRow = coSkList.at(i);
			QList< QMap<QString,QString> > skillList = dbFile->getListByField("skill","id",coSkRow["skill_id"]);
			if(skillList.count()>0)
			{	
				QMap<QString,QString> skill = skillList.at(0);
				ui.rightWidget->addItem(skill["name"]);
			}
		}
	}
}

/**
  * Setup data for step 2
  */
void MyClass:: setup4Step2()// Main step 2 
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
	if(courseMode == "CREATE")
		ui.resultLabel->setText("<span style='color:red'><b>Step1:Saved</b></span>");
}

void MyClass:: saveCourseSKillTable(int numElementSkillBox)
{
	//save to course_skill table
	for(int i = 0;i<numElementSkillBox;i++)
	{
		QString skill = ui.rightWidget->item(i)->text();
		QList< QMap<QString,QString> > skillList = dbFile->getListByField("skill", "name", skill);
		if(skillList.count()>0)
		{
			QString skillIdTemp = skillList.at(0)["id"];
			QList<QString> infoInsert;
			infoInsert <<QString::number(courseID) <<skillIdTemp;
			dbFile->insertItemWithoutKeyId("course_skill", infoInsert);
		}
	}
}

void MyClass:: setupStep3Add(int numElementSkillBox) 
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

void MyClass:: setupInfoBoxStep2Save(int numElementBoxSkill)
{
	for(int i =0;i<numElementBoxSkill;i++)
	{
		QString skill = ui.rightWidget->item(i)->text();
		QLabel *skillLabel = new QLabel(skill);
		ui.step2Layout->addWidget(skillLabel);

		QListWidget *listSkill = new QListWidget(ui.step2WidgetInfo);
		if(courseMode == "EDIT")
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

void MyClass:: setup4Step3() // Main step 3 
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

QString MyClass:: materialBox(QString skill,bool &ok)
{
	QString text = QInputDialog::getText(this, tr("Add Material to ") + skill,tr("Material:"), 
										QLineEdit::Normal, tr("try try"),&ok);
	return text;
}

/**
  * @param skillNID : "<skill>,<index>"
  */
bool MyClass:: isAddMaterial(QString skillNIndex)
{
	bool ok;
	QStringList stringlist = skillNIndex.split(",");
	QString skill = stringlist.at(0);
	QString index = stringlist.at(1);

	QString text =  materialBox(skill,ok);
	if (ok && !text.isEmpty())
	{
		// check Material
		int in = index.toInt();
		QListWidget *list =  skillWidgets.at(in);
		bool isMaExist = isItemExist(text,list);
		if(isMaExist == false)
		{
			QList<QString> matList;
			matList.append(text);
			QMap<QString,QString> insertRow =  dbFile->insertItemWithKeyId("material",matList);
			int idMaterial  = insertRow["id"].toInt();
			if(idMaterial !=-1 )
			{
				//insert into skill_material table	
				QList< QMap<QString,QString> > skillList =  dbFile->getListByField("skill", "name", skill);
				if(skillList.count()>0)
				{
					QString idSkill = skillList.at(0)["id"];
					QList<QString> skillMaterialList;
					skillMaterialList <<idSkill <<QString::number(idMaterial)<<QString::number(courseID);
					QMap<QString,QString> insertRow =  dbFile->insertItemWithoutKeyId("skill_material",skillMaterialList);
					idMaterial = insertRow["material_id"].toInt();
					if(idMaterial!=-1)
						list->addItem(text);
				}
			}
		}
	}
	return ok;
}

void MyClass:: loadConfigAddCourseTab()
{
	ui.saveCourseButton->setVisible(false);
	ui.line1_2->setVisible(false);
	ui.line2_3->setVisible(false);
	ui.step2Widget->setVisible(false);
	ui.step3Widget->setVisible(false);
	ui.skillLabelShow->setVisible(false);
	ui.addMoreButton->setVisible(false);
	courseName = "";
	courseID = 0;
	courseMode = "CREATE";
	ui.courseNameLineEdit->setFocus();
}


void MyClass:: refreshToOriginAddCourse() 
{
	loadConfigAddCourseTab();

	ui.courseNameLineEdit->setText("");
	ui.courseNameLineEdit->setText("");
	ui.step1Widget->setEnabled(true);
	ui.step2Widget->setEnabled(true);
	ui.resultLabel->setText("");
	ui.skillLabelShow->setVisible(false);

	clearItemsLayout(ui.step1Layout);
	clearItemsLayout(ui.step2Layout);
	//step 3
	clearItemsLayout(ui.verticalLayout);

	//step 2 
	int numLeft  = ui.leftWidget->count();
	int numRight = ui.rightWidget->count();
	for (int i =0;i<numLeft;i++)
		ui.leftWidget->takeItem(0);
	for (int i =0;i<numRight;i++)
		ui.rightWidget->takeItem(0);

	courseName = "";
	courseID = 0;
	courseMode = "CREATE";
	skillsCourse.clear();
	skillWidgets.clear();
	ui.courseNameLineEdit->setFocus();
}

// ------------------------------- LIST CLASS TAB
void MyClass:: fillListClass(QList< QMap<QString,QString> > resClass)
{
	int numRow = resClass.count();
	for(int rowCurrent=0;rowCurrent<numRow;rowCurrent++)
	{
		QList< QMap<QString,QString> > coRow = dbFile->getListByField("course","id",
																	 resClass.at(rowCurrent)["course_id"]);
		QString cName  = coRow.at(0)["name"];
		QString regisDate   = resClass.at(rowCurrent)["registration_day"];
		QString className   = resClass.at(rowCurrent)["name"];
		QString totalDay    = resClass.at(rowCurrent)["total_day"];
		QString learnDay    = resClass.at(rowCurrent)["num_learning_day"];

		listClassModel->setItem(rowCurrent,0, new QStandardItem(resClass.at(rowCurrent)["id"]));
		listClassModel->setItem(rowCurrent,1, new QStandardItem(className));
		listClassModel->setItem(rowCurrent,2, new QStandardItem(regisDate));
		
		QPushButton *memberListButton = new QPushButton(ui.listClassTable);
		memberListButton->setText("Detail");
	
		QIcon ButtonIcon;
		ButtonIcon.addFile(QString::fromUtf8("Resources/detail_icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
		memberListButton->setIcon(ButtonIcon);

		QSignalMapper *memberListMapper = new QSignalMapper(ui.listClassTable);
		memberListMapper->setMapping(memberListButton,resClass.at(rowCurrent)["id"]);
		QObject::connect(memberListButton,SIGNAL(clicked()),memberListMapper,SLOT(map()));
		QObject::connect(memberListMapper,SIGNAL(mapped(QString)),this,SLOT(detailMemberAction(QString)));
		ui.listClassTable->setIndexWidget(listClassModel->index(rowCurrent,3),memberListButton);
		//courseName
		listClassModel->setItem(rowCurrent,4,new QStandardItem(cName));
			
		int percentDay   = (learnDay.toInt()*100/totalDay.toInt());
		
		QList<QString> fields;
		QList<QString> fieldUseValues;
		QList<QString> fieldNotUseValues;

		fields << "class_id" << "status";
		fieldUseValues << resClass.at(rowCurrent)["id"] << "1";

		QList< QMap<QString,QString> > allMat = dbFile->getListByField("materialuse","class_id",
																	  resClass.at(rowCurrent)["id"]);
		QList< QMap<QString,QString> > useMat = dbFile->getListByFields("materialuse",fields,fieldUseValues);

		int allMater = allMat.count();
		int useMater = useMat.count();

		QString idMU =  resClass.at(rowCurrent)["id"] ;

		int percentMater = 0;
		if(allMater!=0)
			percentMater = (useMater*100/allMater);

		listClassModel->setItem(rowCurrent,5,new QStandardItem(QString::number(percentDay)));
		listClassModel->setItem(rowCurrent,6,new QStandardItem(QString::number(percentMater)));

		QPushButton *editClassButton = new QPushButton(ui.listClassTable);
		editClassButton->setText("Edit");
		QIcon ButtonIcon1;
		ButtonIcon1.addFile(QString::fromUtf8("Resources/edit.jpg"), QSize(), QIcon::Normal, QIcon::Off);
		editClassButton->setIcon(ButtonIcon1);
		QSignalMapper *editClassMapper = new QSignalMapper(ui.listClassTable);
		editClassMapper->setMapping(editClassButton,resClass.at(rowCurrent)["id"]);
		QObject::connect(editClassButton,SIGNAL(clicked()),editClassMapper,SLOT(map()));
		QObject::connect(editClassMapper,SIGNAL(mapped(QString)),this,SLOT(editClassAction(QString)));
		ui.listClassTable->setIndexWidget(listClassModel->index(rowCurrent,7),editClassButton);

		QPushButton *deleteClassButton = new QPushButton(ui.listClassTable);
		deleteClassButton->setText("Delete");
		QIcon ButtonIcon2;
		ButtonIcon2.addFile(QString::fromUtf8("Resources/Delete_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
		deleteClassButton->setIcon(ButtonIcon2);
		QSignalMapper *deleteClassMapper = new QSignalMapper(ui.listClassTable);
		deleteClassMapper->setMapping(deleteClassButton,resClass.at(rowCurrent)["id"]);
		QObject::connect(deleteClassButton,SIGNAL(clicked()),deleteClassMapper,SLOT(map()));
		QObject::connect(deleteClassMapper,SIGNAL(mapped(QString)),this,SLOT(deleteClassAction(QString)));

		ui.listClassTable->setIndexWidget(listClassModel->index(rowCurrent,8),deleteClassButton);
	}
}

void MyClass:: loadListClassTab()
{
	ui.refreshClassButton->setText("");
	ui.searchClassLineEdit->setText("");
	listClassModel->clear();
	QList<QString> listHeader;
	listHeader << "ID" << "Class name" << "Registration day" << "Member" << "Course" << "% day"
			   << "% material" << "EDIT" << "DELETE";
	setHeaderTable(listClassModel,listHeader);
	// resize columns
	ui.listClassTable->setColumnWidth(0,30);
	ui.listClassTable->setColumnWidth(1,180);
	ui.listClassTable->setColumnWidth(2,100);
	ui.listClassTable->setColumnWidth(3,75);
	ui.listClassTable->setColumnWidth(4,75);
	ui.listClassTable->setColumnWidth(5,75);
	ui.listClassTable->setColumnWidth(6,75);
	ui.listClassTable->setColumnWidth(7,75);
	ui.listClassTable->setColumnWidth(8,75);
	ui.listClassTable->setColumnHidden(0,true);
	// fill value
	QList< QMap<QString,QString> > classList = dbFile->getAll("class");
	fillListClass(classList);
}

// ---------------------LIST COURSE TAB
QString MyClass:: getSkillList(QString courseId)
{
	QList< QMap<QString,QString> > coSkiList = dbFile->getListByField("course_skill","course_id",courseId);
	int numList = coSkiList.count();
	QString skillString="";
	QString skillID ="";
	for(int i=0;i<numList;i++)
	{
		skillID = coSkiList.at(i)["skill_id"];
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
	int numRow = materialRows.count();
	for(int i =0;i< numRow;i++)
	{
		QString course   = materialRows.at(i)["name"];  // course Name
		QString courseId = materialRows.at(i)["id"];
		courseIdList.append(courseId);

		QString skillString = getSkillList(courseId);	
	
		courseModel->setItem(indexTemp,0,new QStandardItem(course));
		courseModel->setItem(indexTemp,1,new QStandardItem(skillString));
		indexTemp++;
	}

	//Add button Detail và Button Edit vào
	int numCourseId = courseIdList.length();
	for(int i = indexRow ; i < numCourseId ; i++)
	{
		int indexCourseIdList = i-indexRow;

		QPushButton *detailButton = new QPushButton("Detail");
		QIcon ButtonIcon3;
		ButtonIcon3.addFile(QString::fromUtf8("Resources/detail_icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
		detailButton->setIcon(ButtonIcon3);
		QSignalMapper *signalMapper = new QSignalMapper();
		signalMapper->setMapping(detailButton,courseIdList.at(indexCourseIdList));
		QObject::connect(detailButton,SIGNAL(clicked()),signalMapper, SLOT(map()));
		QObject::connect(signalMapper, SIGNAL(mapped(QString)),this, SLOT(loadCourseDialogAction(QString)));			
		listCourseTable->setIndexWidget(courseModel->index(i,2),detailButton);

		QPushButton *editButton = new QPushButton("Edit");
		QIcon ButtonIcon;
		ButtonIcon.addFile(QString::fromUtf8("Resources/edit.jpg"), QSize(), QIcon::Normal, QIcon::Off);
		editButton->setIcon(ButtonIcon);
		QSignalMapper *signalMapper1 = new QSignalMapper(this);
		signalMapper1->setMapping(editButton,courseIdList.at(indexCourseIdList));
		QObject::connect(editButton,SIGNAL(clicked()),signalMapper1, SLOT(map()));
		QObject::connect(signalMapper1, SIGNAL(mapped(QString)),this, SLOT(editCourseAction(QString)));
		listCourseTable->setIndexWidget(courseModel->index(i,3),editButton);

		QPushButton *deleteButton = new QPushButton("Delete");
		QIcon ButtonIcon1;
		ButtonIcon1.addFile(QString::fromUtf8("Resources/Delete_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
		deleteButton->setIcon(ButtonIcon1);
		QSignalMapper *signalMapper2 = new QSignalMapper(this);
		signalMapper2->setMapping(deleteButton,courseIdList.at(indexCourseIdList));
		QObject::connect(deleteButton,SIGNAL(clicked()),signalMapper2, SLOT(map()));
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

	ui.listCourseTable->setColumnWidth(0,170);
	ui.listCourseTable->setColumnWidth(1,220);
	ui.listCourseTable->setColumnWidth(2,80);
	ui.listCourseTable->setColumnWidth(3,80);
	ui.listCourseTable->setColumnWidth(4,80);

	QList< QMap<QString,QString> > res_set = dbFile->getAll("course");
	fillListCourse(res_set,ui.listCourseTable,listCourseModel,0);
}
// SLOT
// -------------------------  ADD CLASS TAB
void MyClass:: enableClassInfoAction() // in editing mode
{	
	ui.enableClass1Button->setVisible(false);
	ui.classAdd1Widget->setEnabled(true);
	enableForEditing[0]=true;
}

void MyClass:: enableMemberAction()// in editing mode
{
	ui.enableClass2Button->setVisible(false);
	ui.classAdd2Widget->setEnabled(true);
	enableForEditing[1]=true;
}

void MyClass:: enableCourseAction()
{
	ui.enableClass3Button->setVisible(false);
	ui.classAdd3Widget->setEnabled(true);
	ui.courseInfoLabel->setEnabled(true);
	ui.courseInfoWidget->setEnabled(true);
	enableForEditing[2]=true;
}

void MyClass:: refreshAddClassAction()
{
	loadDataAddClassTab(0);
	QWidget * tab = ui.mainTab->widget(1);
	ui.mainTab->setCurrentWidget(tab);
	classID =0;

	ui.mainTab->setTabEnabled(0,false);
	ui.mainTab->setTabEnabled(1,true);
	ui.mainTab->setTabEnabled(2,false);
	ui.mainTab->setTabEnabled(3,false);
}

void MyClass:: cancelClassAction()
{
	loadDataAddClassTab(0);
	loadListClassTab();
	ui.searchClassLineEdit->setText("");
	QWidget * tab = ui.mainTab->widget(0);
	ui.mainTab->setCurrentWidget(tab);
	classID =0;

	ui.mainTab->setTabEnabled(0,true);
	ui.mainTab->setTabEnabled(1,false);
	ui.mainTab->setTabEnabled(2,true);
	ui.mainTab->setTabEnabled(3,false);
}

/**
  * delete material in skill box info
  * @param materialNSkillIndex : "<material name> , <skill Index>"
  * skillindex : in skillModelList and skillTableList
  */
void MyClass::delMaterialTable(QString materialNSkillIndex)
{
	QStringList arr    = materialNSkillIndex.split(",");
	QString material   = arr.at(0);
	QString skillIndex = arr.at(1);
	int skillIndexInt  = skillIndex.toInt();
	
	QStandardItemModel *model = skillModelList.at(skillIndexInt);
	int rowCount			  = model->rowCount();
	for(int i=0;i<rowCount;i++)
	{
		QString materialCom = model->data(model->index(i,1),Qt::DisplayRole).toString();
		if(material == materialCom)
		{
			model->removeRow(i);
			return;
		}
	}
}


/**
  * Check data before saving
  */
void MyClass:: saveClassAction()
{
	// checl data
	int rowMember = addMemberModel->rowCount();
	if (ui.classNameLineEdit->text()=="")
	{
		QMessageBox::warning(this,tr("Class name"),tr("Please fill the blank!!"));
		ui.classNameLineEdit->setFocus();
		return;
	}
	else if(ui.totalDateLineEdit->text()=="" || isNumber(ui.totalDateLineEdit->text())==false) // check if a number
	{
		QMessageBox::warning(this,tr("Total days"),tr("Please fill the blank, and value is a NUMBER!!"));
		ui.totalDateLineEdit->setFocus();
		return;
	}
	else if(ui.courseClassLabel->text()=="")
	{
		QMessageBox::warning(this,tr("Choose Course"),tr("Please select the suitable course!!"));
		return;
	}
	else  
	{
		QList<QString> memberList;
		bool haveMember = false;
		int numMember = 0;
		for(int i = 0;i<rowMember;i++) // check number in birthyear and check whether have member
		{
			QString birthYear = addMemberModel->data(addMemberModel->index(i,1),Qt::DisplayRole).toString().trimmed();
			QString memberName = addMemberModel->data(addMemberModel->index(i,0),Qt::DisplayRole).toString().trimmed();
			if(memberName!="")
			{
				memberList.append(memberName);
				haveMember = true;
				numMember++;
				if( birthYear.length()>0 && isNumber(birthYear) == false)
				{
					QMessageBox::warning(this,tr("Member infomation"),tr("Please fill a NUMBER for 'birth year' !!"));
					return;
				}
			}
		}
		if (haveMember == false) // check whether contain member
		{
			QMessageBox::warning(this,tr("Add Member"),tr("Please fill the member info!!"));
			return;
		}	

		// SAVE
		if (classID ==0)
		{
			QList<QString> classListInfo;
			classListInfo << ui.classNameLineEdit->text() << "0" << ui.regisdateEdit->date().toString("yyyy-MM-dd")
				          << ui.totalDateLineEdit->text() << "0" <<ui.otherLineEdit->text();
			QMap<QString,QString> classInsert = dbFile->insertItemWithKeyId("class",classListInfo);
			int classId  = 0;
			if(classInsert.count()>0)
			{
				classId = classInsert["id"].toInt();
				//save members
				for(int i = 0;i<numMember;i++)
				{
					QString memberName = memberList.at(i);
					if(memberName != "")
					{
						QString birthYear = addMemberModel->data(addMemberModel->index(i,1),Qt::DisplayRole).toString().trimmed();
						QString note      = addMemberModel->data(addMemberModel->index(i,2),Qt::DisplayRole).toString().trimmed();
						
						QList<QString> memberListInfo;
						memberListInfo << memberName << birthYear << note;
						QMap<QString,QString> memberInsert = dbFile->insertItemWithKeyId("member",memberListInfo);
						if(memberInsert.count() >0)
						{
							QList<QString> classMemberInsert;
							classMemberInsert << QString::number(classId) << memberInsert["id"];
							dbFile->insertItemWithoutKeyId("class_member",classMemberInsert);
						}
					}
				}
				//edit course_id to class table
				QString courseName  = ui.courseClassLabel->text();
				QList< QMap<QString,QString> > courseList = dbFile->getListByField("course","name",courseName);
				dbFile->editOneFieldById("class","id",QString::number(classId),"course_id",courseList.at(0)["id"]);

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
						mateUseList << materialId << QString::number(classId) << skillIdList.at(i) << "0";
						dbFile->insertItemWithoutKeyId("materialuse",mateUseList);
					}
				}
			}

		}
		else // edit
		{
			//member
			if(enableForEditing.at(1)==true )
			{
				editMember();
				enableForEditing[1]=false;
			}
			//course
			if(enableForEditing.at(2) == true)
			{
				editCourse();
				editClass();
				enableForEditing[2]=false;
			}
			//class
			if(enableForEditing.at(0) == true)
			{
				editClass();
				enableForEditing[0]=false;
			}
		}
		classID =0;
		loadListClassTab();
		loadDataAddClassTab(0);
		QWidget * tab = ui.mainTab->widget(0);

		ui.mainTab->setCurrentWidget(tab);
		ui.mainTab->setTabEnabled(0,true);
		ui.mainTab->setTabEnabled(1,false);
		ui.mainTab->setTabEnabled(2,true);
		ui.mainTab->setTabEnabled(3,false);
	}
}

/**
  * when choose course in combox box -> load material up to that course choosen
  */
void MyClass:: courseComboAction(QString courseStr)
{
	clearItemsLayout(ui.courseInfoLayout);
	if(courseStr == "Choose course")
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
	if(classID!=0)
	{
		QList< QMap<QString,QString> > clList = dbFile->getListByField("class","id",QString::number(classID));
		QList< QMap<QString,QString> > coList = dbFile->getListByField("course","id",clList.at(0)["course_id"]);

		addUseCheckBox(coList.at(0)["name"],courseStr);
	}
}

//SLOT
// ----------- ADD COURSE TAB 
void MyClass:: refreshAddCourseAction()
{
	ui.mainTab->setTabEnabled(0,false);
	ui.mainTab->setTabEnabled(1,false);
	ui.mainTab->setTabEnabled(2,false);
	ui.mainTab->setTabEnabled(3,true);

	QWidget * tab = ui.mainTab->widget(3);
	ui.mainTab->setCurrentWidget(tab);

	refreshToOriginAddCourse();
}

void MyClass:: step1SaveAction() // disable step 1, enable step 2, update info to info box
{
	// check box name is empty
	if(ui.courseNameLineEdit->text().trimmed() == "")
	{
		QMessageBox::warning(this,tr("Course name"),tr("Please fill the blank!!"));
		ui.courseNameLineEdit->setFocus();
		return;
	}
	courseName = ui.courseNameLineEdit->text();

	if(courseMode == "CREATE")
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

void MyClass:: step2SaveAction() // save value to skillsCourse, fill step 3 info, step 3 appear, fill info into info bo
{
	int numSkills = ui.rightWidget->count();
	if(numSkills == 0)
	{
		QMessageBox::warning(this,tr("Skill choice"),tr("Please choose skills!!"));
		return;
	}

	if(courseMode == "CREATE")
		saveCourseSKillTable(numSkills);

	setup4Step3();
}

void MyClass:: addSkillAction()
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

		if(checkItemExist(text, listItems) == false)
		{
			QList<QString> skList;
			skList.append(text);
			dbFile->insertItemWithKeyId("skill",skList);
			ui.leftWidget->addItem(text);
		}
	}
}

void MyClass:: left2RightAction()
{
	ui.rightWidget->addItem(ui.leftWidget->takeItem(ui.leftWidget->currentRow()));
}

void MyClass:: right2LeftAction()
{
	ui.leftWidget->addItem(ui.rightWidget->takeItem(ui.rightWidget->currentRow()));
}

void MyClass:: all2LeftAction()
{
	int numElements = ui.rightWidget->count();
	for(int i =0;i<numElements;i++)
	{
		QListWidgetItem *item = ui.rightWidget->takeItem(0);
		ui.leftWidget->addItem(item);
	}
}

void MyClass:: all2RightAction()
{
	int numElements = ui.leftWidget->count();
	for(int i =0;i<numElements;i++)
	{
		QListWidgetItem *item = ui.leftWidget->takeItem(0);
		ui.rightWidget->addItem(item);
	}
}

void MyClass:: left2RightClickAction()
{
	QListWidgetItem *item2 = ui.leftWidget->takeItem(ui.leftWidget->currentRow());
	ui.rightWidget->addItem(item2);
}

void MyClass:: right2LeftClickAction()
{
	QListWidgetItem *item2 = ui.rightWidget->takeItem(ui.rightWidget->currentRow());
	ui.leftWidget->addItem(item2);
}

/**
  * Clisk to "edit material" button 
  *	@param skillNIndex : "<skill>,<index>" (index: index trong skillWidgets [thu tu skills])
  */
void MyClass:: listMaterialAction(QString skillNIndex)
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
	if(isChange == true)
	{
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
		if(numRow>0)
		{
			for(int i=0; i <numRow; i++)
			{
				QString maId = skiMaList.at(i)["material_id"];
				QList< QMap<QString,QString> > maList = dbFile->getListByField("material","id",maId);
				if(maList.count()>0)
				{
					QString ma   = maList.at(0)["name"];
					listWidget->addItem(ma);
				}
			}
		}	
	}
}

/**
  * @param skillNID : "<skill>,<id>"
  */	
void MyClass:: addMaterialAction(QString skillNIndex)
{			
	bool isAdd = isAddMaterial(skillNIndex);
	while(isAdd ==true)
	{
		ui.resultLabel->setText("<span style='color:green'><b>Material: saved</b></span>");
		isAdd = isAddMaterial(skillNIndex);
	}
}

void MyClass:: saveCourseAction()
{
	if(courseMode == "EDIT")
		step1SaveAction();
	QWidget * tab = ui.mainTab->widget(2);
	ui.mainTab->setCurrentWidget(tab);
	refreshToOriginAddCourse();
	// load course list
	loadListCourseTab();
	loadListClassTab();

	ui.mainTab->setTabEnabled(0,true);
	ui.mainTab->setTabEnabled(1,false);
	ui.mainTab->setTabEnabled(2,true);
	ui.mainTab->setTabEnabled(3,false);
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
	fillListCourse(res,ui.listCourseTable,listCourseModel,0);
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
	ui.mainTab->setTabEnabled(0,false);
	ui.mainTab->setTabEnabled(1,false);
	ui.mainTab->setTabEnabled(2,false);
	ui.mainTab->setTabEnabled(3,true);

	// Edit info
	// --> Must asign value to CourseId and CourseName --> for value in clicked() signal()
	QList< QMap<QString,QString> > courseList = dbFile->getListByField("course","id",courseId);
	courseName  = courseList.at(0)["name"];
	courseID = courseId.toInt();
	courseMode = "EDIT";
	//setup info
	ui.courseNameLineEdit->setText(courseName); // step1
	setup4Step2();
	setup4Step3();
	ui.step2Widget->setEnabled(false);

	// Change tab to Course Tab
	QWidget * tab = ui.mainTab->widget(3);
	ui.mainTab->setCurrentWidget(tab);
	ui.mainTab->setTabEnabled(0,false);
	ui.mainTab->setTabEnabled(1,false);
	ui.mainTab->setTabEnabled(2,false);

	ui.addMoreButton->setVisible(false);
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

// SLOT 
// --------------------- LIST CLASS TAB
void MyClass:: searchClassAction()
{
	QString textSearchTemp = ui.searchClassLineEdit->text();
	QString textSearch     = textSearchTemp.trimmed();
	
	//delete all row and fill data
	listClassModel->clear();
	QList<QString> listHeader;
	listHeader << "ID" << "Class name" << "Registration day" << "Member" << "Course" 
			   << "% day" << "% material" << "EDIT" << "DELETE";
	setHeaderTable(listClassModel,listHeader);
			// resize columns
	ui.listClassTable->setColumnWidth(0,30);
	ui.listClassTable->setColumnWidth(1,180);
	ui.listClassTable->setColumnWidth(2,100);
	ui.listClassTable->setColumnWidth(3,75);
	ui.listClassTable->setColumnWidth(4,75);
	ui.listClassTable->setColumnWidth(5,75);
	ui.listClassTable->setColumnWidth(6,75);
	ui.listClassTable->setColumnWidth(7,75);
	ui.listClassTable->setColumnWidth(8,75);
	// fill value
	QList< QMap<QString,QString> > resClass = dbFile->getListByPartValue("class", "name", textSearch);
	fillListClass(resClass);
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

void MyClass:: delMemberRowAction(QString memberId) //Edit class - member 
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

void MyClass:: editClassAction(QString classId)
{
	classID = classId.toInt();
	
	ui.mainTab->setTabEnabled(0,false);
	ui.mainTab->setTabEnabled(1,true);
	ui.mainTab->setTabEnabled(2,false);
	ui.mainTab->setTabEnabled(3,false);
	QWidget * tab = ui.mainTab->widget(1);
	ui.mainTab->setCurrentWidget(tab);

	loadDataAddClassTab(classID);
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

