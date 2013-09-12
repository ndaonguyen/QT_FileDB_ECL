#pragma once

#include <QList>
#include <QString>
#include <QMap>
#include <QXmlStreamReader>
#include <QFile>

class databaseFile
{
public:
	databaseFile(void);
	~databaseFile(void);
	QFile* getFile(QString table,QString mode);
	bool isNumber(QString strCheck);
	QList<QString> getDbStructure(QString table);
	QList< QMap<QString,QString> > getDbBrowse(QString table);
	bool isItemExist(QList<QString> listCheck, QString value );

	QList< QMap<QString,QString> > readFile(QString table); // name of table
	QMap<QString,QString>parseEach(QString table,QXmlStreamReader& xml);
	void writeFile(QString table,QList< QMap<QString,QString> > listInfo);
	QMap<QString,QString> searchMax(QString table, QString field);
	QMap<QString,QString> insertItemWithKeyId(QString table, QList<QString> infoInsert);
public:
	// list of db structure
	QList<QString> dbClass;
	QList<QString> dbClassMember;
	QList<QString> dbCourse;
	QList<QString> dbCourseSkill;
	QList<QString> dbMaterial;
	QList<QString> dbMaterialUse;
	QList<QString> dbMember;
	QList<QString> dbSkill;
	QList<QString> dbSkillMaterial;

	// list of db browse
	QList< QMap<QString,QString> > classList;
	QList< QMap<QString,QString> > classMemberList;
	QList< QMap<QString,QString> > courseList;
	QList< QMap<QString,QString> > courseSkillList;
	QList< QMap<QString,QString> > materialList;
	QList< QMap<QString,QString> > materialUseList;
	QList< QMap<QString,QString> > memberList;
	QList< QMap<QString,QString> > skillList;
	QList< QMap<QString,QString> > skillMaterialList;

	bool isClassEdit;
	bool isClassMemberEdit;
	bool isCourseEdit;
	bool isCourseSkillEdit;
	bool isMaterialEdit;
	bool isMaterialUseEdit;
	bool isSkill;
	bool isSkillMaterial;
};
