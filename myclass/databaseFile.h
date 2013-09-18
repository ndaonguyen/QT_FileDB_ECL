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
	
	void replaceItemDbBrowse(QString table,int index,QMap<QString,QString> item );
	void removeItemsDbBrowse(QString table,int index);

	bool isItemExist(QList<QString> listCheck, QString value );
	void appendItem(QString table, QMap<QString,QString> item);
	int indexSearchItem(QString table,QMap<QString,QString> item);
	QList<int> indexSearchField(QString table,QString field, QString fieldValue);

	QList< QMap<QString,QString> > readFile(QString table); // name of table
	QMap<QString,QString> parseEach(QString table,QXmlStreamReader& xml);
	void writeFile(QString table,QList< QMap<QString,QString> > listInfo);
	
	//Save
	QMap<QString,QString> insertItemWithKeyId(QString table, QList<QString> infoInsert);
	QMap<QString,QString> insertItemWithoutKeyId(QString table, QList<QString> infoInsert);
	
	QMap<QString,QString> searchMax(QString table, QString field);
	QList< QMap<QString,QString> > getAll(QString table);
	QList< QMap<QString,QString> > getListByField(QString table, QString field, QString fieldValue);
	QList< QMap<QString,QString> > getListByFields(QString table, QList<QString> fields, QList<QString> fieldValues);
	QList< QMap<QString,QString> > getListByPartValue(QString table, QString field, QString partValue);
	QList< QMap<QString,QString> > getListByFieldGroupByField(QString table, QString field, QString fieldValue, QString fieldGroup);


	//Edit a id by searching another id
	void editOneFieldById(QString table,QString fieldSearch, QString fieldValue, QString fieldReplace, QString valueReplace);
	void editById(QString table, QString idValue ,QList<QString> listInfo); // edit with table have key ( ex: id,...)

	//Delete
	void deleteByField(QString table, QString field, QString fieldValue);
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
};
