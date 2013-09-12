#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase> 
#include <QtGui/QMessageBox>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/qsqldriver.h>
#include <QtSql/QSqlDriverPlugin>

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <C:\wamp32\bin\mysql\mysql5.5.16\include\mysql.h>

using namespace std;

class database
{
public:
	static bool createConnection()
	{
		QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
		db.setHostName("127.0.0.1");
		db.setDatabaseName("qt_tracking");
		db.setUserName("root");
		db.setPassword("");
		if (!db.open()) {
		    QMessageBox::critical(0, QObject::tr("Database Error"),db.lastError().text());
			return false;
		}
		return true;
	}

	static MYSQL* connectByC()
	{
	
		MYSQL *con = mysql_init(NULL);
		if(mysql_real_connect(con, "127.0.0.1","root","","qt_tracking",0,NULL,0)== NULL)
		{
			mysql_error(con);
			return NULL;
		}
		else
		{
			return con;
		}		
	}

	static void closeConnectionC(MYSQL *connect)
	{
		mysql_close(connect);
	}

	// MATERIAL TABLE
	static MYSQL_ROW material_searchMaterialId(MYSQL *connect, QString materialId)
	{
	/**
	** @parameter : skillID	
	** @return:  row of all value from skill table
	*/
		MYSQL_RES *res_set;
		MYSQL_ROW row;
	
		QString tem = "SELECT * FROM `english_course`.`material` WHERE `id` = '"+materialId+"'";			
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			row = mysql_fetch_row(res_set);
			return row;
		}
		return NULL;

	}

	static int material_getMaxId(MYSQL *connect)
	{
	/**
	**	@return: max id from material table
	*/
		QString query = "SELECT MAX(id) FROM `english_course`.`material`";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			MYSQL_ROW row;

			res_set = mysql_store_result(connect);
			row     = mysql_fetch_row(res_set);
			return atoi(row[0]);
		}
		return -1;
	}

	static int material_saveAction(MYSQL *connect,QString materialName)
	{
	/**
	** @parameter : material name 	
	** @return: id inserted
	*/
		QString query = "INSERT INTO `english_course`.`material` VALUES(NULL,'"+materialName+"')";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return material_getMaxId(connect);
		}
		return -1;
	}
	static int material_deleteById(MYSQL *connect, QString materialId)
	{
		QString query = "DELETE FROM `english_course`.`material` WHERE `material`.`id` =" + materialId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}
	static int material_editById(MYSQL *connect, QString materialId, QString material)
	{
		//UPDATE `english_course`.`material` SET `name` = 'edit done' WHERE `material`.`id` =198;
		QString query = "UPDATE `english_course`.`material` SET `name` = '"+material+"' WHERE `id` =" + materialId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}

	//SKILL TABLE
	static MYSQL_ROW skill_searchSkillId(MYSQL *connect, QString skillId)
	{
	/**
	** @parameter : skillID	
	** @return:  row of all value from skill table
	*/
		MYSQL_RES *res_set;
		MYSQL_ROW row;
		QString tem = "SELECT * FROM `english_course`.`skill` WHERE `id` = '"+skillId+"'";			
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			row = mysql_fetch_row(res_set);
			return row;
		}
		return NULL;
	}

	static int skill_saveAction(MYSQL *connect, QString skillName)
	{
	/**
	** @parameter : material name 	
	** @return: id inserted
	*/
		QString query = "INSERT INTO `english_course`.`skill` VALUES(NULL,'"+skillName+"')";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return skill_getMaxId(connect);
		}
		return -1;
	}
	static MYSQL_RES* skill_getAll(MYSQL *connect)
	{
		QString query = "SELECT * FROM `english_course`.`skill`";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			res_set = mysql_store_result(connect);
			return res_set;
		}
		return NULL;
	}

	static int skill_getMaxId(MYSQL *connect)
	{
		QString query = "SELECT MAX(id) FROM `english_course`.`skill`";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			MYSQL_ROW row;

			res_set = mysql_store_result(connect);
			row     = mysql_fetch_row(res_set);
			return atoi(row[0]);
		}
		return -1;
	}

	static MYSQL_ROW skill_searchName(MYSQL *connect, QString skillName)
	{
		/**
		** @parameter: skill name
		** @return : row of all value from skill table
		*/
		MYSQL_RES *res_set;
		MYSQL_ROW row;

		QString tem = "SELECT * FROM `english_course`.`skill` WHERE `name` = '"+skillName+"'";			
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			row = mysql_fetch_row(res_set);
			return row;
		}
		return NULL;
	}
	static int skill_deleteById(MYSQL *connect, QString skillId)
	{
		QString query = "DELETE FROM `english_course`.`skill` WHERE `id` =" + skillId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}

	//SKILL_MATERIAL table
	static int skillMaterial_getMaxMaterialID(MYSQL *connect)
	{
		QString query = "SELECT MAX(material_id) FROM `english_course`.`skill_material`";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			MYSQL_ROW row;

			res_set = mysql_store_result(connect);
			row     = mysql_fetch_row(res_set);
			return atoi(row[0]);
		}
		return -1;
	}

	static MYSQL_RES* skillMaterial_searchSkillId(MYSQL *connect, QString skillId,QString courseId)
	{
		/**
		** @parameter: skill id
		** @return : row of all value 
		*/
		MYSQL_RES *res_set;

		QString tem = "SELECT * FROM `english_course`.`skill_material` WHERE `skill_id` = '"+skillId+"' AND `course_id`='"+ courseId+"'";			
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
		//	row = mysql_fetch_row(res_set);
			return res_set;
		}
		return NULL;
	}

	static int skillMaterial_saveAction(MYSQL *connect,QString idSkill, QString idMaterial, QString idCourse)
	{
	/**
	** @parameter : material name 	
	** @return: id inserted
	*/
		QString query = "INSERT INTO `english_course`.`skill_material` VALUE("+idSkill+","+idMaterial+","+idCourse+")";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return skillMaterial_getMaxMaterialID(connect);
		}
		return -1;
	}
	static int skillMaterial_deleteByMaterialId(MYSQL *connect, QString materialId)
	{
		QString query = "DELETE FROM `english_course`.`skill_material` WHERE `material_id` =" + materialId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}


	//COURSE table
	static int course_saveAction(MYSQL *connect, QString courseName)
	{
	/**
	** @parameter : material name 	
	** @return: id inserted
	*/
		QString query = "INSERT INTO `english_course`.`course` VALUES(NULL,'"+courseName+"')";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return course_getMaxId(connect);
		}
		return -1;
	}
	static int course_getMaxId(MYSQL *connect)
	{
		QString query = "SELECT MAX(id) FROM `english_course`.`course`";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			MYSQL_ROW row;

			res_set = mysql_store_result(connect);
			row     = mysql_fetch_row(res_set);
			return atoi(row[0]);
		}
		return -1;
	}
	static MYSQL_RES* course_getAll(MYSQL *connect)
	{
		QString query = "SELECT * FROM `english_course`.`course`";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			res_set = mysql_store_result(connect);
			return res_set;
		}
		return NULL;
	}

	static MYSQL_RES* course_searchPartName(MYSQL *connect, QString namePart)
	{
		QString query = "SELECT * FROM `english_course`.`course` WHERE `name` LIKE '%"+namePart+"%'";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			res_set = mysql_store_result(connect);
			return res_set;
		}
		return NULL;
	}

	static MYSQL_ROW course_searchName(MYSQL *connect, QString courseName)
	{
		/**
		** @parameter: skill name
		** @return : row of all value from skill table
		*/
		MYSQL_RES *res_set;
		MYSQL_ROW row;

		QString tem = "SELECT * FROM `english_course`.`course` WHERE `name` = '"+courseName+"'";			
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			row = mysql_fetch_row(res_set);
			return row;
		}
		return NULL;
	}
	static int course_deleteBySkillId(MYSQL *connect, QString courseId)
	{
		QString query = "DELETE FROM `english_course`.`course` WHERE `id` =" + courseId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}

	static MYSQL_ROW course_searchId(MYSQL *connect, QString courseId)
	{
	/**
	** @parameter : skillID	
	** @return:  row of all value from skill table
	*/
		MYSQL_RES *res_set;
		MYSQL_ROW row;
		QString tem = "SELECT * FROM `english_course`.`course` WHERE `id` = '"+courseId+"'";			
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			row = mysql_fetch_row(res_set);
			return row;
		}
		return NULL;
	}
	static int course_editById(MYSQL *connect, QString courseId, QString course)
	{
		QString query = "UPDATE `english_course`.`course` SET `name` = '"+course+"' WHERE `id` =" + courseId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}

	// COURSE_SKILL table
	static int courseSkill_saveAction(MYSQL *connect,QString idSkill, QString idCourse)
	{
	/**
	** @parameter : material name 	
	** @return: id inserted
	*/
		QString query = "INSERT INTO `english_course`.`course_skill` VALUE("+idCourse+","+idSkill+")";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return courseSkill_getMaxSkillID(connect);
		}
		return -1;
	}

	static int courseSkill_getMaxSkillID(MYSQL *connect)
	{
		QString query = "SELECT MAX(skill_id) FROM `english_course`.`course_skill`";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			MYSQL_ROW row;

			res_set = mysql_store_result(connect);
			row     = mysql_fetch_row(res_set);
			return atoi(row[0]);
		}
		return -1;
	}
	
	static MYSQL_RES* courseSkill_searchCourseId(MYSQL *connect,QString courseId)
	{
	/**
	** @parameter : courseId	
	** @return:  row of all value from course_skill table
	*/
		MYSQL_RES *res_set;
		QString tem = "SELECT * FROM `english_course`.`course_skill` WHERE `course_id` = '"+courseId+"'";			
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			return res_set;
		}
		return NULL;
	}
	static int courseSkill_deleteByCourseId(MYSQL *connect, QString courseId)
	{
		QString query = "DELETE FROM `english_course`.`course_skill` WHERE `course_id` =" + courseId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}

	static int courseSkill_deleteBySkillId(MYSQL *connect, QString skillId)
	{
		QString query = "DELETE FROM `english_course`.`course_skill` WHERE `skill_id` =" + skillId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}
	// CLASS Table
	static int class_saveAction(MYSQL *connect, QList<QString> listinfo)
	{
	/**
	** @parameter : listinfo info of Class in order	
	** @return: id inserted
	*/
		QString numLeaningDay = "0";
		QString query = "INSERT INTO `english_course`.`class` VALUES(NULL,'"+listinfo.at(0)+"',0,'"+listinfo.at(1)+"','"+listinfo.at(2)+"','"+numLeaningDay+"','"+listinfo.at(3)+"')";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return class_getMaxId(connect);
		}
		return -1;
	}
	static int class_getMaxId(MYSQL *connect)
	{
		QString query = "SELECT MAX(id) FROM `english_course`.`class`";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			MYSQL_ROW row;

			res_set = mysql_store_result(connect);
			row     = mysql_fetch_row(res_set);
			return atoi(row[0]);
		}
		return -1;
	}
	static MYSQL_ROW class_searchClassId(MYSQL *connect,QString classId)
	{
		MYSQL_RES *res_set;
		MYSQL_ROW row;
	
		QString tem = "SELECT * FROM `english_course`.`class` WHERE `id` = '"+classId+"'";			
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			row = mysql_fetch_row(res_set);
			return row;
		}
		return NULL;
	}
	static MYSQL_RES* class_searchPartName(MYSQL *connect, QString namePart)
	{
		QString query = "SELECT * FROM `english_course`.`class` WHERE `name` LIKE '%"+namePart+"%'";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			res_set = mysql_store_result(connect);
			return res_set;
		}
		return NULL;
	}


	static MYSQL_RES* class_getAll(MYSQL *connect)
	{
		QString query = "SELECT * FROM `english_course`.`class`";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			res_set = mysql_store_result(connect);
			return res_set;
		}
		return NULL;
	}
	static int class_editCourseIdById(MYSQL *connect, QString classId, QString courseId)
	{
		QString query = "UPDATE `english_course`.`class` SET `course_id` = "+courseId+" WHERE `id` =" + classId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}
	static int class_editById(MYSQL *connect, QString classId, QList<QString> classInfo)
	{
		QString query = "UPDATE `english_course`.`class` SET `name`='"+classInfo.at(0)+"', `course_id` = "+classInfo.at(1)+", `registration_day`= '"+classInfo.at(2)+"',`total_day` = '"+classInfo.at(3)+"', `num_learning_day` ='"+classInfo.at(4)+"', `note` ='"+classInfo.at(5)+"'  WHERE `id` =" + classId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}
	static int class_deleteById(MYSQL *connect, QString classId)
	{
		QString query = "DELETE FROM `english_course`.`class` WHERE `id` =" + classId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}
	//MEMBER table
	static int member_saveAction(MYSQL *connect, QList<QString> listinfo)
	{
	/**
	** @parameter : listinfo info of Class in order	
	** @return: id inserted
	*/
		QString query = "INSERT INTO `english_course`.`member` VALUES(NULL,'"+listinfo.at(0)+"','"+listinfo.at(1)+"','"+listinfo.at(2)+"')";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return member_getMaxId(connect);
		}
		return -1;
	}
	static int member_getMaxId(MYSQL *connect)
	{
		QString query = "SELECT MAX(id) FROM `english_course`.`member`";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set;
			MYSQL_ROW row;

			res_set = mysql_store_result(connect);
			row     = mysql_fetch_row(res_set);
			return atoi(row[0]);
		}
		return -1;
	}
	static MYSQL_ROW member_searchMemberId(MYSQL *connect,QString memberId)
	{
		MYSQL_RES *res_set;
		MYSQL_ROW row;
	
		QString tem = "SELECT * FROM `english_course`.`member` WHERE `id` = '"+memberId+"'";			
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			row = mysql_fetch_row(res_set);
			return row;
		}
		return NULL;
	}
	
	static int member_editById(MYSQL *connect, QString memberId, QList<QString> memberInfo)
	{
		QString query = "UPDATE `english_course`.`member` SET `name` = '"+memberInfo.at(0)+"', `birth_year` = '"+memberInfo.at(1)+"', `note` = '"+memberInfo.at(2)+"' "+" WHERE `id` =" + memberId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}
	static int member_deleteById(MYSQL *connect, QString memberId)
	{
		QString query = "DELETE FROM `english_course`.`member` WHERE `id` =" + memberId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}

	// CLASS_MEMBER table
	static int classMember_saveAction(MYSQL *connect,QString idClass, QString idMember)
	{
		QString query = "INSERT INTO `english_course`.`class_member` VALUE("+idClass+","+idMember+")";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return courseSkill_getMaxSkillID(connect);
		}
		return -1;
	}
	static MYSQL_RES* classMember_searchClassId(MYSQL *connect, QString classId)
	{
		MYSQL_RES *res_set;
	
		QString tem = "SELECT * FROM `english_course`.`class_member` WHERE `class_id` = '"+classId+"'";			
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			return res_set;
		}
		return NULL;
	}
	static int classMember_deleteByClassId(MYSQL *connect, QString classId)
	{
		QString query = "DELETE FROM `english_course`.`class_member` WHERE `class_id` =" + classId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}

	static int classMember_deleteByMemberId(MYSQL *connect, QString memberId)
	{
		QString query = "DELETE FROM `english_course`.`class_member` WHERE `member_id` =" + memberId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}

	// MATERIALUSE TABLE
	static int materialUse_saveAction(MYSQL *connect,QString materialId, QString classId, QString skillId, QString usesStatus)
	{
		QString query = "INSERT INTO `english_course`.`materialuse` VALUE("+materialId+","+classId+","+skillId+","+usesStatus+")";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return courseSkill_getMaxSkillID(connect);
		}
		return -1;
	}
	static MYSQL_RES* materialUse_searchByClassIdNSkillId(MYSQL *connect, QString classId, QString skillId)
	{
		MYSQL_RES *res_set;
	
		QString tem = "SELECT * FROM `english_course`.`materialuse` WHERE class_id="+classId +" AND skill_id="+skillId ;		
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			return res_set;
		}
		return NULL;
	}
	static MYSQL_ROW materialUse_searchMaterialClassId(MYSQL *connect, QString materialId, QString classId)
	{
		MYSQL_RES *res_set;
		MYSQL_ROW row;
		QString tem = "SELECT * FROM `english_course`.`materialuse` WHERE `material_id` = '"+materialId+"' AND `class_id` ='"+classId+"'";			
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			row = mysql_fetch_row(res_set);
			return row;
		}
		return NULL;
	}
	static MYSQL_RES* materialUse_searchSkillByClassId(MYSQL *connect, QString classId)
	{
		MYSQL_RES *res_set;
	
		QString tem = "SELECT skill_id FROM `english_course`.`materialuse` WHERE class_id="+classId +" GROUP BY skill_id" ;		
		std::string temp1 = tem.toStdString();
		const char* temp2 = temp1.c_str();
		if(mysql_query(connect,temp2) ==0)
		{
			res_set = mysql_store_result(connect);
			return res_set;
		}
		return NULL;
	}

	static int materialUse_countByClassId(MYSQL *connect, QString classId)
	{
		QString query = "SELECT count(*) FROM `english_course`.`materialuse` where class_id ='"+classId+"'";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set = mysql_store_result(connect);
			MYSQL_ROW row     = mysql_fetch_row(res_set);
			return atoi(row[0]);
		}
		return -1;
	}
	static int materialUse_countUseMaterialByClassId(MYSQL *connect, QString classId)
	{
		QString query = "SELECT count(*) FROM `english_course`.`materialuse` where status =1 AND class_id ='"+classId+"'";
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			MYSQL_RES *res_set = mysql_store_result(connect);
			MYSQL_ROW row     = mysql_fetch_row(res_set);
			return atoi(row[0]);
		}
		return -1;
	}
	static int materialUse_deleteByClassId(MYSQL *connect, QString classId)
	{
		QString query = "DELETE FROM `english_course`.`materialuse` WHERE `class_id` =" + classId;
		std::string query2 = query.toStdString();
		const char* query1 = query2.c_str();
		if(mysql_query(connect,query1)==0)
		{
			return 1;
		}
		return -1;
	}
};



#endif