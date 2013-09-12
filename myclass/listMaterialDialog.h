#pragma once
#include <QDialog>
#include "database.h"
//#include "databaseFile.h"
#include <QSignalMapper>
#include <QStandardItemModel>

class QLabel;
class QTableView;
class QPushButton;

class listMaterialDialog : public QDialog
{
    Q_OBJECT
public:
	bool isChanged; // to recognize whether data is changed or not --> update to Info Box
    listMaterialDialog(QWidget *parent = 0, QString skillName = "",int courseId=0);
	~listMaterialDialog(void);

private:
    QLabel *label;
	QTableView *view;
	MYSQL *conn;
	QList<QString > listMaterialIdDelete;  // save list id need to be deleted
	QStandardItemModel *model;
	private slots:
		void deleteMaterial(QString materialId)
		{
			MYSQL_ROW rowMater = database::material_searchMaterialId(conn,materialId);
			QString materialName = rowMater[1];
			listMaterialIdDelete.append(materialId);

			int numRows = model->rowCount();
			for(int i =0;i<numRows;i++)
			{
				if(materialName == model->data(model->index(i,1),Qt::DisplayRole).toString() )
					model->removeRow(i);
			}
			isChanged = true;
		}

		void editMaterialAction()
		{
			int rowCount = model->rowCount();
			for(int i=0;i<rowCount;i++)
			{
				QString materId      = model->data(model->index(i,0),Qt::DisplayRole).toString();
				QString materialStr  = model->data(model->index(i,1),Qt::DisplayRole).toString();
				
				database::material_editById(conn,materId,materialStr);
			}
			int countIdDelete = listMaterialIdDelete.count();
			for(int i=0; i < countIdDelete; i++)
			{
				QString matId = listMaterialIdDelete.at(i);
				database::material_deleteById(conn,matId);
				database::skillMaterial_deleteByMaterialId(conn,matId);
			}

			isChanged = true;
			close();
		}
};
