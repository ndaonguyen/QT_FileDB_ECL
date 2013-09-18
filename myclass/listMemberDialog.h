#pragma once
#include <QDialog>
#include "databaseFile.h"
#include <QSignalMapper>
#include <QStandardItemModel>
#include <QMessageBox>

class QLabel;
class QPushButton;
class QTableView;


class listMemberDialog : public QDialog
{
	 Q_OBJECT
public:
	listMemberDialog(QWidget *parent = 0,databaseFile *dbFileTransfer = 0,QString classId=0);
	~listMemberDialog(void);
public:
	bool isNumber(QString strCheck)
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
private:
	int numOldMemberInDialog;  // tong so luong member cu con ton tai trong list
	QLabel *label;
	QList<QString> listMemberIdDelete;
	QPushButton *saveButton;
	QPushButton *cancelButton;
	QTableView *view;
	QStandardItemModel *model;
	databaseFile *dbFile;
	private slots:
		void deleteMemberAction(QString memberId)
		{
			QList< QMap<QString,QString> > memberRow = dbFile->getListByField("member", "id", memberId);
			QString memberName  = memberRow.at(0)["name"];
			int rowCount = model->rowCount();
			for(int i=0;i<rowCount;i++)
			{
				QString memberCom = model->data(model->index(i,1),Qt::DisplayRole).toString();
				if(memberName == memberCom )
				{
					model->removeRow(i);
					break;
				}
			}
			listMemberIdDelete.append(memberId);
			numOldMemberInDialog--;
		}

		void saveListAction(QString classId)
		{
			int numRow    = model->rowCount();
			int numColumn = model->columnCount();
			QList<QString> memberInfo;
			for(int r = 0;r<numOldMemberInDialog;r++) // edit info
			{
				for(int c =1;c<numColumn-1;c++)
				{
					memberInfo.append(model->data(model->index(r,c),Qt::DisplayRole).toString());
				}
				QString memId = model->data(model->index(r,0),Qt::DisplayRole).toString();
				dbFile->editById("member",memId,memberInfo);
				memberInfo.clear();
			}
			//delete
			int numDelete = listMemberIdDelete.count();
			for(int i =0;i<numDelete;i++)
			{
				dbFile->deleteByField("class_member","member_id",listMemberIdDelete.at(i));
				dbFile->deleteByField("member","id",listMemberIdDelete.at(i));
			}
			//save new data
			QList<QString> memberInfoList;
			for(int i=numOldMemberInDialog;i<numRow;i++)
			{
				
				QString memberName = model->data(model->index(i,1),Qt::DisplayRole).toString().trimmed();
				if(memberName!="")
				{
					QString birthYear = model->data(model->index(i,2),Qt::DisplayRole).toString().trimmed();
					if( birthYear.length()>0 && isNumber(birthYear) == false)
					{
						QMessageBox::warning(this,tr("Member infomation"),tr("Please fill a NUMBER for 'birth year' !!"));
						return;
					}
					QString note = model->data(model->index(i,3),Qt::DisplayRole).toString().trimmed();
					memberInfoList << memberName << birthYear << note;
					
					QMap<QString,QString> memberInsert = dbFile->insertItemWithKeyId("member",memberInfoList);
					QList<QString> classMemberList;
					classMemberList << classId << memberInsert["id"];
					dbFile->insertItemWithoutKeyId("class_member",classMemberList);
					
					memberInfoList.clear();
				}
			}
			close();
		}
		void addMemberAction() 
		{
			int numRow    = model->rowCount();
			int numColumn = model->columnCount();
			for(int i=0;i<numColumn;i++)
				model->setItem(numRow,i, new QStandardItem(tr("")));
		}

};
