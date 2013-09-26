/********************************************************************************
** Form generated from reading UI file 'myclass.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCLASS_H
#define UI_MYCLASS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myclassClass
{
public:
    QWidget *centralWidget;
    QTabWidget *mainTab;
    QWidget *listClassTab;
    QPushButton *searchClassButton;
    QLineEdit *searchClassLineEdit;
    QTableView *listClassTable;
    QPushButton *refreshClassButton;
    QPushButton *addMoreClassButton;
    QWidget *listCourseTab;
    QTableView *listCourseTable;
    QLineEdit *searchCourseLineEdit;
    QPushButton *searchCourseButton;
    QPushButton *refreshCourseButton;
    QPushButton *addMoreCourseButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myclassClass)
    {
        if (myclassClass->objectName().isEmpty())
            myclassClass->setObjectName(QString::fromUtf8("myclassClass"));
        myclassClass->resize(931, 680);
        myclassClass->setMinimumSize(QSize(931, 680));
        myclassClass->setMaximumSize(QSize(931, 700));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../../Dropbox/Eezy - Member/Eezy document/Design/website/Eezy - empty.png"), QSize(), QIcon::Normal, QIcon::Off);
        myclassClass->setWindowIcon(icon);
        centralWidget = new QWidget(myclassClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        mainTab = new QTabWidget(centralWidget);
        mainTab->setObjectName(QString::fromUtf8("mainTab"));
        mainTab->setGeometry(QRect(10, 0, 901, 631));
        listClassTab = new QWidget();
        listClassTab->setObjectName(QString::fromUtf8("listClassTab"));
        searchClassButton = new QPushButton(listClassTab);
        searchClassButton->setObjectName(QString::fromUtf8("searchClassButton"));
        searchClassButton->setGeometry(QRect(230, 10, 71, 23));
        searchClassLineEdit = new QLineEdit(listClassTab);
        searchClassLineEdit->setObjectName(QString::fromUtf8("searchClassLineEdit"));
        searchClassLineEdit->setGeometry(QRect(20, 10, 201, 20));
        listClassTable = new QTableView(listClassTab);
        listClassTable->setObjectName(QString::fromUtf8("listClassTable"));
        listClassTable->setGeometry(QRect(20, 50, 791, 560));
        listClassTable->setMinimumSize(QSize(791, 560));
        listClassTable->setMaximumSize(QSize(16777215, 560));
        refreshClassButton = new QPushButton(listClassTab);
        refreshClassButton->setObjectName(QString::fromUtf8("refreshClassButton"));
        refreshClassButton->setGeometry(QRect(760, 0, 51, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/myclass/Resources/refresh_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        refreshClassButton->setIcon(icon1);
        refreshClassButton->setIconSize(QSize(35, 35));
        addMoreClassButton = new QPushButton(listClassTab);
        addMoreClassButton->setObjectName(QString::fromUtf8("addMoreClassButton"));
        addMoreClassButton->setGeometry(QRect(820, 0, 51, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/myclass/Resources/addIcon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        addMoreClassButton->setIcon(icon2);
        addMoreClassButton->setIconSize(QSize(32, 32));
        mainTab->addTab(listClassTab, QString());
        listCourseTab = new QWidget();
        listCourseTab->setObjectName(QString::fromUtf8("listCourseTab"));
        listCourseTable = new QTableView(listCourseTab);
        listCourseTable->setObjectName(QString::fromUtf8("listCourseTable"));
        listCourseTable->setGeometry(QRect(20, 50, 791, 611));
        searchCourseLineEdit = new QLineEdit(listCourseTab);
        searchCourseLineEdit->setObjectName(QString::fromUtf8("searchCourseLineEdit"));
        searchCourseLineEdit->setGeometry(QRect(20, 10, 201, 21));
        searchCourseButton = new QPushButton(listCourseTab);
        searchCourseButton->setObjectName(QString::fromUtf8("searchCourseButton"));
        searchCourseButton->setGeometry(QRect(230, 10, 75, 23));
        refreshCourseButton = new QPushButton(listCourseTab);
        refreshCourseButton->setObjectName(QString::fromUtf8("refreshCourseButton"));
        refreshCourseButton->setGeometry(QRect(760, 0, 51, 41));
        refreshCourseButton->setIcon(icon1);
        refreshCourseButton->setIconSize(QSize(35, 35));
        addMoreCourseButton = new QPushButton(listCourseTab);
        addMoreCourseButton->setObjectName(QString::fromUtf8("addMoreCourseButton"));
        addMoreCourseButton->setGeometry(QRect(820, 0, 51, 41));
        addMoreCourseButton->setIcon(icon2);
        addMoreCourseButton->setIconSize(QSize(32, 32));
        mainTab->addTab(listCourseTab, QString());
        myclassClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(myclassClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 931, 21));
        myclassClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myclassClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        myclassClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(myclassClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        myclassClass->setStatusBar(statusBar);
        QWidget::setTabOrder(searchClassLineEdit, searchClassButton);
        QWidget::setTabOrder(searchClassButton, mainTab);
        QWidget::setTabOrder(mainTab, listClassTable);
        QWidget::setTabOrder(listClassTable, refreshClassButton);
        QWidget::setTabOrder(refreshClassButton, addMoreClassButton);
        QWidget::setTabOrder(addMoreClassButton, searchCourseLineEdit);
        QWidget::setTabOrder(searchCourseLineEdit, listCourseTable);
        QWidget::setTabOrder(listCourseTable, searchCourseButton);
        QWidget::setTabOrder(searchCourseButton, refreshCourseButton);
        QWidget::setTabOrder(refreshCourseButton, addMoreCourseButton);

        retranslateUi(myclassClass);
        QObject::connect(mainTab, SIGNAL(currentChanged(int)), myclassClass, SLOT(tabChangeAction(int)));

        mainTab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(myclassClass);
    } // setupUi

    void retranslateUi(QMainWindow *myclassClass)
    {
        myclassClass->setWindowTitle(QApplication::translate("myclassClass", "ECL", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mainTab->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        searchClassButton->setText(QApplication::translate("myclassClass", "Search", 0, QApplication::UnicodeUTF8));
        refreshClassButton->setText(QString());
        mainTab->setTabText(mainTab->indexOf(listClassTab), QApplication::translate("myclassClass", "List class", 0, QApplication::UnicodeUTF8));
        searchCourseButton->setText(QApplication::translate("myclassClass", "Search", 0, QApplication::UnicodeUTF8));
        refreshCourseButton->setText(QString());
        mainTab->setTabText(mainTab->indexOf(listCourseTab), QApplication::translate("myclassClass", "List Course", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class myclassClass: public Ui_myclassClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLASS_H
