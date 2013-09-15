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

	isClassEdit = false;
	isClassMemberEdit = false;
	isCourseEdit = false;
	isCourseSkillEdit = false;
	isMaterialEdit = false;
	isMaterialUseEdit = false;
	isSkill = false;
	isSkillMaterial = false;

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

QMap<QString,QString> databaseFile:: insertItemWithKeyId(QString table, QList<QString> infoInsert) // id is key ( increase each time)
{
	QList<QString> dbGet = getDbStructure(table);
	QMap<QString,QString> item;
	int numDb			 = dbGet.count();
	int numFieldInsert	 = infoInsert.count();
	if(numFieldInsert == numDb - 1) // number insert equal ( except id)
	{
		QMap<QString,QString> maxItem = searchMax(table,"id");
		int maxId = maxItem["id"].toInt() +1;
		item["id"] = QString::number(maxId); // id must be the first order
		for(int j=1;j<numDb;j++)
			item[dbGet.at(j)] = infoInsert.at(j-1);
		// append 
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
	return item;
}

QMap<QString,QString> databaseFile::searchMax(QString table, QString field)
{
	QList<QString> dbGet = getDbStructure(table);
	QList< QMap<QString,QString> > listInfo = getDbBrowse(table);

	// find if that field is exist in table
	bool isExist = isItemExist(dbGet,field );
	int maxValue = 0;
	int indexMax = 0;
	// exist --> find the max
	if(isExist == true)
	{
		int numRow = listInfo.count();
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
	}
	return listInfo.at(indexMax);
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
			file = new QFile("DB/class1.xml");
		else if(table=="class_member")
			file = new QFile("DB/class_member1.xml");
		else if(table =="course")
			file = new QFile("DB/course1.xml");
		else if(table =="course_skill")
			file = new QFile("DB/course_skill1.xml");
		else if(table =="material")
			file = new QFile("DB/material1.xml");
		else if(table =="materialuse")
			file = new QFile("DB/materialuse1.xml");
		else if(table =="member")
			file = new QFile("DB/member1.xml");
		else if(table =="skill")
			file = new QFile("DB/skill1.xml");
		else if(table =="skill_material")
			file = new QFile("DB/skill_material1.xml");
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
	if (!file->open(QIODevice::WriteOnly))
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
QList< QMap<QString,QString> > databaseFile::getDbBrowse(QString table)
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