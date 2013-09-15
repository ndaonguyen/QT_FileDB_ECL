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
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
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
    QWidget *addClassTab;
    QFrame *line;
    QLabel *courseInfoLabel;
    QWidget *courseInfoWidget;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *courseInfoLayout;
    QPushButton *saveButton_2;
    QPushButton *cancelButton;
    QWidget *classAdd1Widget;
    QLabel *otherLabel;
    QLabel *totalDayLabel;
    QWidget *dayUseWidget;
    QLabel *dayUseLabel;
    QSpinBox *dayUseSpinBox;
    QLineEdit *totalDateLineEdit;
    QDateEdit *regisdateEdit;
    QLabel *classNameLabel;
    QLineEdit *classNameLineEdit;
    QLabel *regisDayLabel;
    QLineEdit *otherLineEdit;
    QGroupBox *groupBox;
    QWidget *classAdd2Widget;
    QLabel *label_3;
    QLabel *memberLabel;
    QTableView *addMemberTable;
    QGroupBox *groupBox_2;
    QWidget *classAdd3Widget;
    QLabel *courseClassLabel;
    QComboBox *classComboBox;
    QLabel *chooseCourseLabel;
    QGroupBox *groupBox_3;
    QPushButton *enableClass1Button;
    QPushButton *enableClass2Button;
    QPushButton *enableClass3Button;
    QWidget *listCourseTab;
    QTableView *listCourseTable;
    QLineEdit *searchCourseLineEdit;
    QPushButton *searchCourseButton;
    QPushButton *refreshCourseButton;
    QPushButton *addMoreCourseButton;
    QWidget *addCourseTab;
    QGroupBox *classInsertGroupBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *step1Layout;
    QLabel *skillLabelShow;
    QWidget *step2WidgetInfo;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *step2Layout;
    QPushButton *cancelCourseButton;
    QPushButton *saveCourseButton;
    QWidget *step1Widget;
    QLabel *step1Label;
    QLabel *setCourseLabel;
    QLineEdit *courseNameLineEdit;
    QPushButton *saveButton;
    QWidget *step2Widget;
    QLabel *step2Label;
    QListWidget *leftWidget;
    QListWidget *rightWidget;
    QPushButton *left2RightButton;
    QPushButton *right2LeftButton;
    QPushButton *all2RightButton;
    QPushButton *all2LeftButton;
    QPushButton *saveButton2;
    QPushButton *addSkill;
    QLabel *label;
    QLabel *label_2;
    QWidget *step3Widget;
    QLabel *step2Label_2;
    QWidget *verticalLayoutWidget;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QFrame *line1_2;
    QFrame *line2_3;
    QLabel *resultLabel;
    QPushButton *addMoreButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myclassClass)
    {
        if (myclassClass->objectName().isEmpty())
            myclassClass->setObjectName(QString::fromUtf8("myclassClass"));
        myclassClass->resize(926, 760);
        centralWidget = new QWidget(myclassClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        mainTab = new QTabWidget(centralWidget);
        mainTab->setObjectName(QString::fromUtf8("mainTab"));
        mainTab->setGeometry(QRect(0, 0, 901, 701));
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
        listClassTable->setGeometry(QRect(20, 50, 791, 601));
        refreshClassButton = new QPushButton(listClassTab);
        refreshClassButton->setObjectName(QString::fromUtf8("refreshClassButton"));
        refreshClassButton->setGeometry(QRect(760, 0, 51, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/myclass/Resources/refresh_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        refreshClassButton->setIcon(icon);
        refreshClassButton->setIconSize(QSize(35, 35));
        addMoreClassButton = new QPushButton(listClassTab);
        addMoreClassButton->setObjectName(QString::fromUtf8("addMoreClassButton"));
        addMoreClassButton->setGeometry(QRect(820, 0, 51, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/myclass/Resources/addIcon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        addMoreClassButton->setIcon(icon1);
        addMoreClassButton->setIconSize(QSize(32, 32));
        mainTab->addTab(listClassTab, QString());
        addClassTab = new QWidget();
        addClassTab->setObjectName(QString::fromUtf8("addClassTab"));
        line = new QFrame(addClassTab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(440, 30, 20, 591));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        courseInfoLabel = new QLabel(addClassTab);
        courseInfoLabel->setObjectName(QString::fromUtf8("courseInfoLabel"));
        courseInfoLabel->setGeometry(QRect(470, 30, 231, 16));
        courseInfoWidget = new QWidget(addClassTab);
        courseInfoWidget->setObjectName(QString::fromUtf8("courseInfoWidget"));
        courseInfoWidget->setGeometry(QRect(470, 50, 411, 571));
        verticalLayoutWidget_4 = new QWidget(courseInfoWidget);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(10, 20, 401, 561));
        courseInfoLayout = new QVBoxLayout(verticalLayoutWidget_4);
        courseInfoLayout->setSpacing(6);
        courseInfoLayout->setContentsMargins(11, 11, 11, 11);
        courseInfoLayout->setObjectName(QString::fromUtf8("courseInfoLayout"));
        courseInfoLayout->setContentsMargins(0, 0, 0, 0);
        saveButton_2 = new QPushButton(addClassTab);
        saveButton_2->setObjectName(QString::fromUtf8("saveButton_2"));
        saveButton_2->setGeometry(QRect(130, 640, 241, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/myclass/Resources/save_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveButton_2->setIcon(icon2);
        cancelButton = new QPushButton(addClassTab);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(500, 640, 221, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/myclass/Resources/cancel_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon3);
        classAdd1Widget = new QWidget(addClassTab);
        classAdd1Widget->setObjectName(QString::fromUtf8("classAdd1Widget"));
        classAdd1Widget->setGeometry(QRect(10, 20, 431, 221));
        otherLabel = new QLabel(classAdd1Widget);
        otherLabel->setObjectName(QString::fromUtf8("otherLabel"));
        otherLabel->setGeometry(QRect(10, 170, 91, 16));
        totalDayLabel = new QLabel(classAdd1Widget);
        totalDayLabel->setObjectName(QString::fromUtf8("totalDayLabel"));
        totalDayLabel->setGeometry(QRect(10, 120, 91, 16));
        dayUseWidget = new QWidget(classAdd1Widget);
        dayUseWidget->setObjectName(QString::fromUtf8("dayUseWidget"));
        dayUseWidget->setGeometry(QRect(230, 110, 181, 41));
        dayUseLabel = new QLabel(dayUseWidget);
        dayUseLabel->setObjectName(QString::fromUtf8("dayUseLabel"));
        dayUseLabel->setGeometry(QRect(20, 10, 61, 16));
        dayUseSpinBox = new QSpinBox(dayUseWidget);
        dayUseSpinBox->setObjectName(QString::fromUtf8("dayUseSpinBox"));
        dayUseSpinBox->setGeometry(QRect(80, 10, 71, 22));
        totalDateLineEdit = new QLineEdit(classAdd1Widget);
        totalDateLineEdit->setObjectName(QString::fromUtf8("totalDateLineEdit"));
        totalDateLineEdit->setGeometry(QRect(100, 120, 71, 20));
        regisdateEdit = new QDateEdit(classAdd1Widget);
        regisdateEdit->setObjectName(QString::fromUtf8("regisdateEdit"));
        regisdateEdit->setGeometry(QRect(99, 80, 151, 22));
        classNameLabel = new QLabel(classAdd1Widget);
        classNameLabel->setObjectName(QString::fromUtf8("classNameLabel"));
        classNameLabel->setGeometry(QRect(10, 40, 71, 16));
        classNameLineEdit = new QLineEdit(classAdd1Widget);
        classNameLineEdit->setObjectName(QString::fromUtf8("classNameLineEdit"));
        classNameLineEdit->setGeometry(QRect(100, 40, 291, 20));
        regisDayLabel = new QLabel(classAdd1Widget);
        regisDayLabel->setObjectName(QString::fromUtf8("regisDayLabel"));
        regisDayLabel->setGeometry(QRect(10, 80, 91, 16));
        otherLineEdit = new QLineEdit(classAdd1Widget);
        otherLineEdit->setObjectName(QString::fromUtf8("otherLineEdit"));
        otherLineEdit->setGeometry(QRect(100, 170, 281, 20));
        groupBox = new QGroupBox(classAdd1Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 431, 221));
        groupBox->raise();
        otherLabel->raise();
        totalDayLabel->raise();
        dayUseWidget->raise();
        totalDateLineEdit->raise();
        regisdateEdit->raise();
        classNameLabel->raise();
        classNameLineEdit->raise();
        regisDayLabel->raise();
        otherLineEdit->raise();
        classAdd2Widget = new QWidget(addClassTab);
        classAdd2Widget->setObjectName(QString::fromUtf8("classAdd2Widget"));
        classAdd2Widget->setGeometry(QRect(10, 260, 431, 241));
        label_3 = new QLabel(classAdd2Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 210, 281, 16));
        memberLabel = new QLabel(classAdd2Widget);
        memberLabel->setObjectName(QString::fromUtf8("memberLabel"));
        memberLabel->setGeometry(QRect(10, 30, 91, 16));
        addMemberTable = new QTableView(classAdd2Widget);
        addMemberTable->setObjectName(QString::fromUtf8("addMemberTable"));
        addMemberTable->setGeometry(QRect(100, 30, 321, 181));
        groupBox_2 = new QGroupBox(classAdd2Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 0, 441, 241));
        groupBox_2->raise();
        label_3->raise();
        memberLabel->raise();
        addMemberTable->raise();
        classAdd3Widget = new QWidget(addClassTab);
        classAdd3Widget->setObjectName(QString::fromUtf8("classAdd3Widget"));
        classAdd3Widget->setGeometry(QRect(10, 519, 431, 101));
        courseClassLabel = new QLabel(classAdd3Widget);
        courseClassLabel->setObjectName(QString::fromUtf8("courseClassLabel"));
        courseClassLabel->setGeometry(QRect(100, 40, 251, 16));
        classComboBox = new QComboBox(classAdd3Widget);
        classComboBox->setObjectName(QString::fromUtf8("classComboBox"));
        classComboBox->setGeometry(QRect(100, 70, 121, 22));
        chooseCourseLabel = new QLabel(classAdd3Widget);
        chooseCourseLabel->setObjectName(QString::fromUtf8("chooseCourseLabel"));
        chooseCourseLabel->setGeometry(QRect(10, 40, 91, 16));
        groupBox_3 = new QGroupBox(classAdd3Widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 10, 431, 91));
        groupBox_3->raise();
        courseClassLabel->raise();
        classComboBox->raise();
        chooseCourseLabel->raise();
        enableClass1Button = new QPushButton(addClassTab);
        enableClass1Button->setObjectName(QString::fromUtf8("enableClass1Button"));
        enableClass1Button->setGeometry(QRect(300, 10, 141, 23));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/myclass/Resources/TurnOn_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        enableClass1Button->setIcon(icon4);
        enableClass2Button = new QPushButton(addClassTab);
        enableClass2Button->setObjectName(QString::fromUtf8("enableClass2Button"));
        enableClass2Button->setGeometry(QRect(300, 250, 141, 23));
        enableClass2Button->setIcon(icon4);
        enableClass3Button = new QPushButton(addClassTab);
        enableClass3Button->setObjectName(QString::fromUtf8("enableClass3Button"));
        enableClass3Button->setGeometry(QRect(300, 520, 141, 23));
        enableClass3Button->setIcon(icon4);
        mainTab->addTab(addClassTab, QString());
        classAdd3Widget->raise();
        classAdd2Widget->raise();
        classAdd1Widget->raise();
        line->raise();
        courseInfoLabel->raise();
        courseInfoWidget->raise();
        saveButton_2->raise();
        cancelButton->raise();
        enableClass1Button->raise();
        enableClass2Button->raise();
        enableClass3Button->raise();
        listCourseTab = new QWidget();
        listCourseTab->setObjectName(QString::fromUtf8("listCourseTab"));
        listCourseTable = new QTableView(listCourseTab);
        listCourseTable->setObjectName(QString::fromUtf8("listCourseTable"));
        listCourseTable->setGeometry(QRect(20, 50, 791, 591));
        searchCourseLineEdit = new QLineEdit(listCourseTab);
        searchCourseLineEdit->setObjectName(QString::fromUtf8("searchCourseLineEdit"));
        searchCourseLineEdit->setGeometry(QRect(20, 10, 201, 21));
        searchCourseButton = new QPushButton(listCourseTab);
        searchCourseButton->setObjectName(QString::fromUtf8("searchCourseButton"));
        searchCourseButton->setGeometry(QRect(230, 10, 75, 23));
        refreshCourseButton = new QPushButton(listCourseTab);
        refreshCourseButton->setObjectName(QString::fromUtf8("refreshCourseButton"));
        refreshCourseButton->setGeometry(QRect(760, 0, 51, 41));
        refreshCourseButton->setIcon(icon);
        refreshCourseButton->setIconSize(QSize(35, 35));
        addMoreCourseButton = new QPushButton(listCourseTab);
        addMoreCourseButton->setObjectName(QString::fromUtf8("addMoreCourseButton"));
        addMoreCourseButton->setGeometry(QRect(820, 0, 51, 41));
        addMoreCourseButton->setIcon(icon1);
        addMoreCourseButton->setIconSize(QSize(32, 32));
        mainTab->addTab(listCourseTab, QString());
        addCourseTab = new QWidget();
        addCourseTab->setObjectName(QString::fromUtf8("addCourseTab"));
        classInsertGroupBox = new QGroupBox(addCourseTab);
        classInsertGroupBox->setObjectName(QString::fromUtf8("classInsertGroupBox"));
        classInsertGroupBox->setGeometry(QRect(530, 10, 341, 651));
        horizontalLayoutWidget = new QWidget(classInsertGroupBox);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 20, 261, 41));
        step1Layout = new QHBoxLayout(horizontalLayoutWidget);
        step1Layout->setSpacing(6);
        step1Layout->setContentsMargins(11, 11, 11, 11);
        step1Layout->setObjectName(QString::fromUtf8("step1Layout"));
        step1Layout->setContentsMargins(0, 0, 0, 0);
        skillLabelShow = new QLabel(classInsertGroupBox);
        skillLabelShow->setObjectName(QString::fromUtf8("skillLabelShow"));
        skillLabelShow->setGeometry(QRect(20, 70, 46, 13));
        step2WidgetInfo = new QWidget(classInsertGroupBox);
        step2WidgetInfo->setObjectName(QString::fromUtf8("step2WidgetInfo"));
        step2WidgetInfo->setGeometry(QRect(50, 100, 261, 491));
        verticalLayoutWidget_2 = new QWidget(step2WidgetInfo);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 261, 491));
        step2Layout = new QVBoxLayout(verticalLayoutWidget_2);
        step2Layout->setSpacing(6);
        step2Layout->setContentsMargins(11, 11, 11, 11);
        step2Layout->setObjectName(QString::fromUtf8("step2Layout"));
        step2Layout->setContentsMargins(0, 0, 0, 0);
        cancelCourseButton = new QPushButton(classInsertGroupBox);
        cancelCourseButton->setObjectName(QString::fromUtf8("cancelCourseButton"));
        cancelCourseButton->setGeometry(QRect(190, 610, 131, 23));
        cancelCourseButton->setIcon(icon3);
        saveCourseButton = new QPushButton(classInsertGroupBox);
        saveCourseButton->setObjectName(QString::fromUtf8("saveCourseButton"));
        saveCourseButton->setGeometry(QRect(20, 610, 141, 23));
        saveCourseButton->setAutoFillBackground(true);
        step1Widget = new QWidget(addCourseTab);
        step1Widget->setObjectName(QString::fromUtf8("step1Widget"));
        step1Widget->setGeometry(QRect(120, 20, 381, 81));
        step1Label = new QLabel(step1Widget);
        step1Label->setObjectName(QString::fromUtf8("step1Label"));
        step1Label->setGeometry(QRect(10, 10, 291, 16));
        setCourseLabel = new QLabel(step1Widget);
        setCourseLabel->setObjectName(QString::fromUtf8("setCourseLabel"));
        setCourseLabel->setGeometry(QRect(40, 40, 91, 16));
        courseNameLineEdit = new QLineEdit(step1Widget);
        courseNameLineEdit->setObjectName(QString::fromUtf8("courseNameLineEdit"));
        courseNameLineEdit->setGeometry(QRect(130, 40, 231, 20));
        saveButton = new QPushButton(step1Widget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(340, 0, 41, 31));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/myclass/Resources/saveButtton.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        saveButton->setIcon(icon5);
        saveButton->setIconSize(QSize(18, 18));
        step2Widget = new QWidget(addCourseTab);
        step2Widget->setObjectName(QString::fromUtf8("step2Widget"));
        step2Widget->setGeometry(QRect(120, 160, 381, 181));
        step2Label = new QLabel(step2Widget);
        step2Label->setObjectName(QString::fromUtf8("step2Label"));
        step2Label->setGeometry(QRect(10, 10, 211, 16));
        leftWidget = new QListWidget(step2Widget);
        leftWidget->setObjectName(QString::fromUtf8("leftWidget"));
        leftWidget->setGeometry(QRect(20, 40, 121, 111));
        rightWidget = new QListWidget(step2Widget);
        rightWidget->setObjectName(QString::fromUtf8("rightWidget"));
        rightWidget->setGeometry(QRect(230, 40, 121, 111));
        left2RightButton = new QPushButton(step2Widget);
        left2RightButton->setObjectName(QString::fromUtf8("left2RightButton"));
        left2RightButton->setGeometry(QRect(160, 40, 51, 23));
        right2LeftButton = new QPushButton(step2Widget);
        right2LeftButton->setObjectName(QString::fromUtf8("right2LeftButton"));
        right2LeftButton->setGeometry(QRect(160, 70, 51, 23));
        all2RightButton = new QPushButton(step2Widget);
        all2RightButton->setObjectName(QString::fromUtf8("all2RightButton"));
        all2RightButton->setGeometry(QRect(160, 100, 51, 23));
        all2LeftButton = new QPushButton(step2Widget);
        all2LeftButton->setObjectName(QString::fromUtf8("all2LeftButton"));
        all2LeftButton->setGeometry(QRect(160, 130, 51, 23));
        saveButton2 = new QPushButton(step2Widget);
        saveButton2->setObjectName(QString::fromUtf8("saveButton2"));
        saveButton2->setGeometry(QRect(340, 0, 41, 31));
        saveButton2->setIcon(icon5);
        saveButton2->setIconSize(QSize(18, 18));
        addSkill = new QPushButton(step2Widget);
        addSkill->setObjectName(QString::fromUtf8("addSkill"));
        addSkill->setGeometry(QRect(260, 0, 75, 31));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/myclass/Resources/add-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        addSkill->setIcon(icon6);
        addSkill->setIconSize(QSize(18, 18));
        label = new QLabel(step2Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 160, 46, 13));
        label_2 = new QLabel(step2Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(260, 160, 71, 16));
        step3Widget = new QWidget(addCourseTab);
        step3Widget->setObjectName(QString::fromUtf8("step3Widget"));
        step3Widget->setGeometry(QRect(120, 400, 381, 241));
        step2Label_2 = new QLabel(step3Widget);
        step2Label_2->setObjectName(QString::fromUtf8("step2Label_2"));
        step2Label_2->setGeometry(QRect(10, 10, 131, 16));
        verticalLayoutWidget = new QWidget(step3Widget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 40, 351, 201));
        verticalLayoutWidget_3 = new QWidget(verticalLayoutWidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(0, 0, 351, 201));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(step3Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(110, 10, 231, 16));
        line1_2 = new QFrame(addCourseTab);
        line1_2->setObjectName(QString::fromUtf8("line1_2"));
        line1_2->setGeometry(QRect(120, 120, 381, 16));
        line1_2->setFrameShape(QFrame::HLine);
        line1_2->setFrameShadow(QFrame::Sunken);
        line2_3 = new QFrame(addCourseTab);
        line2_3->setObjectName(QString::fromUtf8("line2_3"));
        line2_3->setGeometry(QRect(120, 370, 381, 16));
        line2_3->setFrameShape(QFrame::HLine);
        line2_3->setFrameShadow(QFrame::Sunken);
        resultLabel = new QLabel(addCourseTab);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        resultLabel->setGeometry(QRect(0, 240, 91, 41));
        addMoreButton = new QPushButton(addCourseTab);
        addMoreButton->setObjectName(QString::fromUtf8("addMoreButton"));
        addMoreButton->setGeometry(QRect(10, 120, 71, 71));
        addMoreButton->setIcon(icon1);
        addMoreButton->setIconSize(QSize(60, 60));
        mainTab->addTab(addCourseTab, QString());
        myclassClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(myclassClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 926, 21));
        myclassClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myclassClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        myclassClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(myclassClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        myclassClass->setStatusBar(statusBar);

        retranslateUi(myclassClass);

        mainTab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(myclassClass);
    } // setupUi

    void retranslateUi(QMainWindow *myclassClass)
    {
        myclassClass->setWindowTitle(QApplication::translate("myclassClass", "myclass", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mainTab->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        searchClassButton->setText(QApplication::translate("myclassClass", "Search", 0, QApplication::UnicodeUTF8));
        refreshClassButton->setText(QString());
        mainTab->setTabText(mainTab->indexOf(listClassTab), QApplication::translate("myclassClass", "List class", 0, QApplication::UnicodeUTF8));
        courseInfoLabel->setText(QString());
        saveButton_2->setText(QApplication::translate("myclassClass", "SAVE", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("myclassClass", "CANCEL", 0, QApplication::UnicodeUTF8));
        otherLabel->setText(QApplication::translate("myclassClass", "Note", 0, QApplication::UnicodeUTF8));
        totalDayLabel->setText(QApplication::translate("myclassClass", "Total days", 0, QApplication::UnicodeUTF8));
        dayUseLabel->setText(QApplication::translate("myclassClass", "Day use", 0, QApplication::UnicodeUTF8));
        classNameLabel->setText(QApplication::translate("myclassClass", "Class name", 0, QApplication::UnicodeUTF8));
        regisDayLabel->setText(QApplication::translate("myclassClass", "Registration day", 0, QApplication::UnicodeUTF8));
        otherLineEdit->setText(QString());
        groupBox->setTitle(QString());
        label_3->setText(QApplication::translate("myclassClass", "Edit, delete or add member in table directly ", 0, QApplication::UnicodeUTF8));
        memberLabel->setText(QApplication::translate("myclassClass", "Members", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        courseClassLabel->setText(QString());
        chooseCourseLabel->setText(QApplication::translate("myclassClass", "Choose course", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QString());
        enableClass1Button->setText(QApplication::translate("myclassClass", "Enable class info edit", 0, QApplication::UnicodeUTF8));
        enableClass2Button->setText(QApplication::translate("myclassClass", "Enable member edit", 0, QApplication::UnicodeUTF8));
        enableClass3Button->setText(QApplication::translate("myclassClass", "Enable course edit", 0, QApplication::UnicodeUTF8));
        mainTab->setTabText(mainTab->indexOf(addClassTab), QApplication::translate("myclassClass", "Add class", 0, QApplication::UnicodeUTF8));
        searchCourseButton->setText(QApplication::translate("myclassClass", "Search", 0, QApplication::UnicodeUTF8));
        refreshCourseButton->setText(QString());
        mainTab->setTabText(mainTab->indexOf(listCourseTab), QApplication::translate("myclassClass", "List Course", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        classInsertGroupBox->setToolTip(QApplication::translate("myclassClass", "Add skills", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        classInsertGroupBox->setTitle(QApplication::translate("myclassClass", "Info inserted :", 0, QApplication::UnicodeUTF8));
        skillLabelShow->setText(QApplication::translate("myclassClass", "<html><head/><body><p><span style=\" font-weight:600;\">Skills:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        cancelCourseButton->setText(QApplication::translate("myclassClass", "Cancel", 0, QApplication::UnicodeUTF8));
        saveCourseButton->setText(QApplication::translate("myclassClass", "FINISH,  BACK  TO LIST !!!", 0, QApplication::UnicodeUTF8));
        step1Label->setText(QApplication::translate("myclassClass", "<html><head/><body><p><span style=\" font-weight:600;\">Step 1 :Course name (e.g: Ielts, Toefl,...)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        setCourseLabel->setText(QApplication::translate("myclassClass", "Set course name:", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QString());
        step2Label->setText(QApplication::translate("myclassClass", "<html><head/><body><p><span style=\" font-weight:600;\">Step 2: Skills</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        left2RightButton->setText(QApplication::translate("myclassClass", ">>", 0, QApplication::UnicodeUTF8));
        right2LeftButton->setText(QApplication::translate("myclassClass", "<<", 0, QApplication::UnicodeUTF8));
        all2RightButton->setText(QApplication::translate("myclassClass", "all >>", 0, QApplication::UnicodeUTF8));
        all2LeftButton->setText(QApplication::translate("myclassClass", "<< all", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveButton2->setToolTip(QApplication::translate("myclassClass", "<html><head/><body><p>Save skills</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveButton2->setText(QString());
        addSkill->setText(QString());
        label->setText(QApplication::translate("myclassClass", "Skill list", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("myclassClass", "course's skill", 0, QApplication::UnicodeUTF8));
        step2Label_2->setText(QApplication::translate("myclassClass", "<html><head/><body><p><span style=\" font-weight:600;\">Step 3: Materials</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("myclassClass", "(Can not add 2 materials with the same name!!)", 0, QApplication::UnicodeUTF8));
        resultLabel->setText(QString());
        mainTab->setTabText(mainTab->indexOf(addCourseTab), QApplication::translate("myclassClass", "Add course", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class myclassClass: public Ui_myclassClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLASS_H
