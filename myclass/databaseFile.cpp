#include "databaseFile.h"

databaseFile::databaseFile(void)
{
	dbClass<< "id" << "name" << "course_id" << "registration_day" << "total_day" << "num_learning_day" << "note";
	dbClassMember << "class_id" << "member_id";
	dbCourse << "id" << "name";
	dbCourseSkill << "course_id" << "skill_id";
	dbMaterial << "id" << "name";
	dbMaterialUse << "material_id" << "class_id" << "skill_id" << "status";
	dbMember << "id" << "name" << "birth_year" << "note";
	dbSkill << "id" << "name";
	dbSkillMaterial << "skill_id" << "material_id" << "course_id";

	//get info 
	classList			= readFile("class");
	classMemberList		= readFile("class_member");
	courseList			= readFile("course");
	courseSkillList		= readFile("course_skill");
	materialList		= readFile("material");
	materialUseList		= readFile("materialuse");
	memberList			= readFile("member");
	skillList			= readFile("skill");
	skillMaterialList	= readFile("skill_material");
}

databaseFile::~databaseFile(void)
{
	writeFile("class",classList);
	writeFile("class_member",classMemberList);
	writeFile("course",courseList);
	writeFile("course_skill",courseSkillList);
	writeFile("material",materialList);
	writeFile("materialuse",materialUseList);
	writeFile("member",memberList);
	writeFile("skill",skillList);
	writeFile("skill_material",skillMaterialList);
}

/**
  * edit table with key : search by id and change rest info( except id)
  */
void databaseFile::editById(QString table, QString idValue, QList<QString> list) // listInfo ko co id
{
	QList<int> indexList = indexSearchField(table,"id", idValue);
	if(indexList.count()>0)
	{
		int index = indexList.at(0);
		QList< QMap<QString,QString> > listInfo = getAll(table);
		QMap<QString,QString>  item = listInfo.at(index);
		QList<QString> dbGet = getDbStructure(table);
		int numItem = dbGet.count();
		for(int i =1;i<numItem;i++) // ko doi id
			item[dbGet.at(i)] = list.at(i-1);
		replaceItemDbBrowse(table,index,item);
	}
}

/**
  * for table with key ( like id)
  */
void databaseFile:: editOneFieldById(QString table,QString fieldSearch, QString fieldValue, QString fieldReplace, QString valueReplace)
{
	QList<int> indexList = indexSearchField(table,fieldSearch, fieldValue);
	if(indexList.count()>0)
	{
		int index = indexList.at(0);
		QList< QMap<QString,QString> > listInfo = getAll(table);
		QMap<QString,QString>  item = listInfo.at(index);
		item[fieldReplace] = valueReplace;
		replaceItemDbBrowse(table,index,item);
	}
}

/**
  * for table without key ( like id)
  */
QMap<QString,QString> databaseFile:: insertItemWithoutKeyId(QString table, QList<QString> infoInsert)
{
	QList<QString> dbGet = getDbStructure(table);
	QMap<QString,QString> item;
	int numDb			 = dbGet.count();
	int numFieldInsert	 = infoInsert.count();
	if(numFieldInsert == numDb) // number insert equal
	{
		for(int j=0;j<numDb;j++)
			item[dbGet.at(j)] = infoInsert.at(j);
		appendItem(table,item);
	}
	return item;
}

QMap<QString,QString> databaseFile:: insertItemWithKeyId(QString table, QList<QString> infoInsert) // id is key ( increase each time)
{
	QList<QString> dbGet = getDbStructure(table);
	QMap<QString,QString> item;
	int numDb			 = dbGet.count();
	int numFieldInsert	 = infoInsert.count();
	if(numFieldInsert == numDb - 1) // number insert equal ( except id)
	{
		QMap<QString,QString> maxItem = searchMax(table,"id");
		int id = 1;
		if(maxItem.isEmpty()==false)
			id = maxItem["id"].toInt() +1;
		item["id"] = QString::number(id); // id must be the first order
		for(int j=1;j<numDb;j++)
			item[dbGet.at(j)] = infoInsert.at(j-1);
		// append 
		appendItem(table, item);
	}
	return item;
}

QMap<QString,QString> databaseFile::searchMax(QString table, QString field)
{
	QList<QString> dbGet = getDbStructure(table);
	QList< QMap<QString,QString> > listInfo = getAll(table);
	QMap<QString,QString> itemReturn;
	// find if that field is exist in table
	bool isExist = isItemExist(dbGet,field );
	int maxValue = 0;
	int indexMax = 0;
	// exist --> find the max
	if(isExist == true)
	{
		int numRow = listInfo.count();
		if(numRow > 0)
		{
			// check if number
			QMap<QString,QString> tempInfo = listInfo.at(0);
			QString tempValue = tempInfo[field];
			if(isNumber(tempValue) == true)
			{
				for(int j=0;j<numRow;j++)
				{
					QMap<QString,QString> itemInfo = listInfo.at(j);
					QString itemValue = itemInfo[field];
					int itemValueInt  = itemValue.toInt();
					if(itemValueInt > maxValue)
					{
						maxValue = itemValueInt;
						indexMax = j;
					}
				}
			}
			itemReturn =  listInfo.at(indexMax);
		}
	}
	return itemReturn;
}

QList< QMap<QString,QString> > databaseFile::getListByField(QString table, QString field, QString fieldValue)
{
	QList< QMap<QString,QString> > listInfo = getAll(table);
	QList< QMap<QString,QString> > listReturn;
	int countItem = listInfo.count();
	for(int i=0;i<countItem;i++)
	{
		QMap<QString,QString> rowInfo = listInfo.at(i);
		if( rowInfo[field] ==fieldValue )
			listReturn.append(rowInfo);
	}
	return listReturn;
}

QList< QMap<QString,QString> > databaseFile::getListByFieldGroupByField(QString table, QString field, QString fieldValue, QString fieldGroup)
{
	QList< QMap<QString,QString> > listInfo = getAll(table);
	QList< QMap<QString,QString> > listReturn;
	int countItem = listInfo.count();
	bool isAdd = true;
	for(int i=0;i<countItem;i++)
	{
		QMap<QString,QString> rowInfo = listInfo.at(i);
		int countListReturn = listReturn.count();
		if( rowInfo[field] ==fieldValue )
		{
			for(int j=0;j<countListReturn;j++)
				if(listReturn.at(j)[fieldGroup] == rowInfo[fieldGroup])
					isAdd = false;

			if(isAdd == true)
				listReturn.append(rowInfo);
			isAdd = true;
		}
	}
	return listReturn;
}

QList< QMap<QString,QString> > databaseFile::getListByFields(QString table, QList<QString> fields, QList<QString> fieldValues)
{
	QList< QMap<QString,QString> > listInfo = getAll(table);
	QList< QMap<QString,QString> > listReturn;
	int countItem   = listInfo.count();
	int countFields = fields.count();
	bool isItemCheck = true;
	for(int i=0;i<countItem;i++)
	{
		QMap<QString,QString> rowInfo = listInfo.at(i);
		for(int j=0;j<countFields;j++)
		{
			QString field = fields.at(j);
			QString value =  fieldValues.at(j);
			QString	rowVa =  rowInfo[field];
			if(rowInfo[field] !=  fieldValues.at(j)) 
			{
				isItemCheck = false;
				break;
			}
		}
		if(isItemCheck == true)
			listReturn.append(rowInfo);
		else
			isItemCheck = true;
	}
	return listReturn;
}

QList< QMap<QString,QString> > databaseFile::getListByPartValue(QString table, QString field, QString partValue)
{
	QList< QMap<QString,QString> > listInfo = getAll(table);
	QList< QMap<QString,QString> > listReturn;
	int countItem = listInfo.count();
	for(int i=0;i<countItem;i++)
	{
		QMap<QString,QString> rowInfo = listInfo.at(i);
		if( rowInfo[field].indexOf(partValue) != -1 )
			listReturn.append(rowInfo);
	}
	return listReturn;
}

void databaseFile::deleteByField(QString table, QString field, QString fieldValue)
{
	QList<int> indexSearch = indexSearchField(table, field, fieldValue);
	while(indexSearch.count()>0)
	{
		int index = indexSearch.at(0);
		removeItemsDbBrowse(table,index);
		indexSearch.clear();
		indexSearch = indexSearchField(table, field, fieldValue);
	}
}


void databaseFile::removeItemsDbBrowse(QString table,int index)
{
	QList< QMap<QString,QString> > listInfo = getAll(table);
	if(index < listInfo.count())
	{
		if(table =="class")
			classList.removeAt(index);
		else if(table =="class_member")
			classMemberList.removeAt(index);
		else if(table =="course")
			courseList.removeAt(index);
		else if(table =="course_skill")
			courseSkillList.removeAt(index);
		else if(table =="material")
			materialList.removeAt(index);
		else if(table =="materialuse")
			materialUseList.removeAt(index);
		else if(table =="member")
			memberList.removeAt(index);
		else if(table =="skill")
			skillList.removeAt(index);
		else if(table =="skill_material")
			skillMaterialList.removeAt(index);
	}
}

bool databaseFile:: isNumber(QString strCheck)
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

QFile* databaseFile::getFile(QString table,QString mode)
{
	QFile* file ;
	if(mode == "read")
	{
		if(table =="class")
			file = new QFile("DB/class.xml");
		else if(table =="class_member")
			file = new QFile("DB/class_member.xml");
		else if(table =="course")
			file = new QFile("DB/course.xml");
		else if(table =="course_skill")
			file = new QFile("DB/course_skill.xml");
		else if(table =="material")
			file = new QFile("DB/material.xml");
		else if(table =="materialuse")
			file = new QFile("DB/materialuse.xml");
		else if(table =="member")
			file = new QFile("DB/member.xml");
		else if(table =="skill")
			file = new QFile("DB/skill.xml");
		else if(table =="skill_material")
			file = new QFile("DB/skill_material.xml");
	}
	else if(mode == "write")
	{
		if(table=="class")
			file = new QFile("DB/class.xml");
		else if(table=="class_member")
			file = new QFile("DB/class_member.xml");
		else if(table =="course")
			file = new QFile("DB/course.xml");
		else if(table =="course_skill")
			file = new QFile("DB/course_skill.xml");
		else if(table =="material")
			file = new QFile("DB/material.xml");
		else if(table =="materialuse")
			file = new QFile("DB/materialuse.xml");
		else if(table =="member")
			file = new QFile("DB/member.xml");
		else if(table =="skill")
			file = new QFile("DB/skill.xml");
		else if(table =="skill_material")
			file = new QFile("DB/skill_material.xml");
	}
	return file;
}

QList< QMap<QString,QString> > databaseFile::readFile(QString table)
{
	QList< QMap<QString,QString> > infoRead;
	QFile* file = this->getFile(table,"read");
	if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) 
		return infoRead;

	QXmlStreamReader xml(file);
	while(!xml.atEnd() && !xml.hasError()) 
	{
		QXmlStreamReader::TokenType token = xml.readNext();
		if(token == QXmlStreamReader::StartDocument) 
			continue;

		if(token == QXmlStreamReader::StartElement) 
		{
			if(table =="class" || table =="class_member" || table =="course" || table =="course_skill" || table =="material"|| table =="materialuse" || table =="member"|| table =="skill"|| table =="skill_material")
			{
				if(xml.name() == "classes" || xml.name() == "class_members" || xml.name() == "courses" || xml.name() == "course_skills" || xml.name() == "materials" || xml.name() == "materialuses"|| xml.name() == "members"|| xml.name() == "skills"|| xml.name() == "skill_materials")
					continue;
				else if(xml.name() == "class" || xml.name() == "class_member" || xml.name() == "course" || xml.name() == "course_skill" || xml.name() == "material" || xml.name() == "materialuse"|| xml.name() == "member" || xml.name() == "skill" || xml.name() == "skill_material") 
					infoRead.append(this->parseEach(table,xml));
			}
        }
	}
	xml.clear();
	file->close();
	delete file;
	return infoRead;
}

QMap<QString,QString> databaseFile:: parseEach(QString table,QXmlStreamReader& xml)
{
	QMap<QString,QString> classDB;
    /* Let's check that we're really getting a class */
    if(xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == table) {
        return classDB;
    }
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == table)) 
	{
        if(xml.tokenType() == QXmlStreamReader::StartElement) 
		{
			QString name = xml.name().toString();
			QList<QString> dbGet = getDbStructure(table);
			int numElement = dbGet.count();
			for(int i=0;i<numElement;i++)
				if(name == dbGet.at(i))
				{
					classDB[dbGet.at(i)] = xml.readElementText();
					break;
				}
        }
        xml.readNext();
    }
    return classDB;
}

void databaseFile::writeFile(QString table,QList< QMap<QString,QString> > classList)
{
	QFile* file = this->getFile(table,"write");
	bool result = file->setPermissions(QFile::WriteOther | QFile::ExeOther);
	if (!file->open(QIODevice::WriteOnly| QIODevice::Text))
	{
		QString error = "The file is in read only mode";
		return;
	}	
	else
	{
		QList<QString> dbGet = getDbStructure(table);
		QXmlStreamWriter* xmlWriter = new QXmlStreamWriter();
		xmlWriter->setDevice(file);
		/* Writes a document start with the XML version number version. */
		xmlWriter->writeStartDocument();
		xmlWriter->writeCharacters("\n");  
		if(table =="class")
			xmlWriter->writeStartElement("classes");
		else if(table =="class_member")
			xmlWriter->writeStartElement("class_members");
		else if(table =="course")
			xmlWriter->writeStartElement("courses");
		else if(table =="course_skill")
			xmlWriter->writeStartElement("course_skills");
		else if(table =="material")
			xmlWriter->writeStartElement("materials");
		else if(table =="materialuse")
			xmlWriter->writeStartElement("materialuses");
		else if(table =="member")
			xmlWriter->writeStartElement("members");
		else if(table =="skill")
			xmlWriter->writeStartElement("skills");
		else if(table =="skill_material")
			xmlWriter->writeStartElement("skill_materials");

		xmlWriter->writeCharacters("\n");  

		int numClass = classList.count();
		for(int i = 0; i < numClass ; i++ )
		{
			QMap<QString,QString> classInfo = classList.at(i);
			int numElement = classInfo.count(); 
			xmlWriter->writeCharacters("	");

			if(table =="class")
				xmlWriter->writeStartElement("class");
			else if(table =="class_member")
				xmlWriter->writeStartElement("class_member");
			else if(table =="course")
				xmlWriter->writeStartElement("course");
			else if(table =="course_skill")
				xmlWriter->writeStartElement("course_skill");
			else if(table =="material")
				xmlWriter->writeStartElement("material");
			else if(table =="materialuse")
				xmlWriter->writeStartElement("materialuse");
			else if(table =="member")
				xmlWriter->writeStartElement("member");
			else if(table =="skill")
				xmlWriter->writeStartElement("skill");
			else if(table =="skill_material")
				xmlWriter->writeStartElement("skill_material");

			xmlWriter->writeCharacters("\n");  
			for(int j=0;j<numElement;j++)
			{
				xmlWriter->writeCharacters("		");  
				xmlWriter->writeTextElement(dbGet.at(j),classInfo[dbGet.at(j)]);
				xmlWriter->writeCharacters("\n"); 
			}
			xmlWriter->writeCharacters("	");
			xmlWriter->writeEndElement();
			xmlWriter->writeCharacters("\n");
		} 
		xmlWriter->writeEndElement(); // classes end tag
		xmlWriter->writeCharacters("\n");  
		xmlWriter->writeEndDocument();
		delete xmlWriter;
		file->close();
		delete file;
	}
	
}

QList<int>databaseFile::indexSearchField(QString table,QString field, QString fieldValue)
{
	QList< QMap<QString,QString> > listInfo = getAll(table);
	QList<int> listIndex;
	int countItem = listInfo.count();
	for(int i=0;i<countItem;i++)
	{
		QMap<QString,QString> rowInfo = listInfo.at(i);
		if( rowInfo[field] ==fieldValue )
			listIndex.append(i);
	}
	return listIndex;
}

int databaseFile::indexSearchItem(QString table,QMap<QString,QString> item)
{
	QList< QMap<QString,QString> > listInfo = getAll(table);
	int index = -1;
	int countItem = listInfo.count();
	for(int i=0;i<countItem;i++)
		if(listInfo.at(i)==item )
			index = i;
	return index;
}

/**
  * Replace at index index of table value <item>
  */
void databaseFile::replaceItemDbBrowse(QString table,int index,QMap<QString,QString> item )
{
	if(table =="class")
		classList.replace(index,item);
	else if(table =="class_member")
		classMemberList.replace(index,item);
	else if(table =="course")
		courseList.replace(index,item);
	else if(table =="course_skill")
		courseSkillList.replace(index,item);
	else if(table =="material")
		materialList.replace(index,item);
	else if(table =="materialuse")
		materialUseList.replace(index,item);
	else if(table =="member")
		memberList.replace(index,item);
	else if(table =="skill")
		skillList.replace(index,item);
	else if(table =="skill_material")
		skillMaterialList.replace(index,item);
}

QList<QString> databaseFile::getDbStructure(QString table)
{
	QList<QString> dbGet;
	if(table =="class")
		dbGet	 = dbClass;
	else if(table =="class_member")
		dbGet	 = dbClassMember;
	else if(table =="course")
		dbGet	 = dbCourse;
	else if(table =="course_skill")
		dbGet	 = dbCourseSkill;
	else if(table =="material")
		dbGet	 = dbMaterial;
	else if(table =="materialuse")
		dbGet	 = dbMaterialUse;
	else if(table =="member")
		dbGet	 = dbMember;
	else if(table =="skill")
		dbGet	 = dbSkill;
	else if(table =="skill_material")
		dbGet	 = dbSkillMaterial;
	return dbGet;
}

QList< QMap<QString,QString> > databaseFile::getAll(QString table)
{
	QList< QMap<QString,QString> > listInfo;
	if(table =="class")
		listInfo = classList;
	else if(table =="class_member")
		listInfo = classMemberList;
	else if(table =="course")
		listInfo = courseList;
	else if(table =="course_skill")
		listInfo = courseSkillList;
	else if(table =="material")
		listInfo = materialList;
	else if(table =="materialuse")
		listInfo = materialUseList;
	else if(table =="member")
		listInfo = memberList;
	else if(table =="skill")
		listInfo = skillList;
	else if(table =="skill_material")
		listInfo = skillMaterialList;
	return listInfo;
}

bool databaseFile::isItemExist(QList<QString> listCheck, QString value )
{
	bool isExist = false;
	int numElementDb = listCheck.count();
	for(int i=0;i<numElementDb;i++)
	{
		if(listCheck.at(i) == value)
		{
			isExist = true;
			break;
		}
	}
	return isExist;
}

void databaseFile::appendItem(QString table, QMap<QString,QString> item)
{
	if(table =="class")
		classList.append(item);
	else if(table =="class_member")
		classMemberList.append(item);
	else if(table =="course")
		courseList.append(item);
	else if(table =="course_skill")
		courseSkillList.append(item);
	else if(table =="material")
		materialList.append(item);
	else if(table =="materialuse")
		materialUseList.append(item);
	else if(table =="member")
		memberList.append(item);
	else if(table =="skill")
		skillList.append(item);
	else if(table =="skill_material")
		skillMaterialList.append(item);
}