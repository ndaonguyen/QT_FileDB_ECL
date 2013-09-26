/********************************************************************************
** Form generated from reading UI file 'addCourse.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCOURSE_H
#define UI_ADDCOURSE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *resultLabel;
    QWidget *step1Widget;
    QLabel *step1Label;
    QLabel *setCourseLabel;
    QLineEdit *courseNameLineEdit;
    QPushButton *saveButton;
    QGroupBox *classInsertGroupBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *step1Layout;
    QLabel *skillLabelShow;
    QWidget *step2WidgetInfo;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *step2Layout;
    QPushButton *cancelCourseButton;
    QPushButton *saveCourseButton;
    QFrame *line2_3;
    QFrame *line1_2;
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

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(850, 642);
        Form->setMinimumSize(QSize(850, 642));
        Form->setMaximumSize(QSize(850, 642));
        resultLabel = new QLabel(Form);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        resultLabel->setGeometry(QRect(0, 240, 91, 41));
        step1Widget = new QWidget(Form);
        step1Widget->setObjectName(QString::fromUtf8("step1Widget"));
        step1Widget->setGeometry(QRect(30, 0, 381, 81));
        step1Label = new QLabel(step1Widget);
        step1Label->setObjectName(QString::fromUtf8("step1Label"));
        step1Label->setGeometry(QRect(10, 20, 291, 16));
        setCourseLabel = new QLabel(step1Widget);
        setCourseLabel->setObjectName(QString::fromUtf8("setCourseLabel"));
        setCourseLabel->setGeometry(QRect(40, 50, 91, 16));
        courseNameLineEdit = new QLineEdit(step1Widget);
        courseNameLineEdit->setObjectName(QString::fromUtf8("courseNameLineEdit"));
        courseNameLineEdit->setGeometry(QRect(130, 50, 231, 20));
        saveButton = new QPushButton(step1Widget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(340, 10, 41, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/myclass/Resources/saveButtton.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        saveButton->setIcon(icon);
        saveButton->setIconSize(QSize(18, 18));
        classInsertGroupBox = new QGroupBox(Form);
        classInsertGroupBox->setObjectName(QString::fromUtf8("classInsertGroupBox"));
        classInsertGroupBox->setGeometry(QRect(480, 10, 341, 621));
        horizontalLayoutWidget = new QWidget(classInsertGroupBox);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 30, 261, 41));
        step1Layout = new QHBoxLayout(horizontalLayoutWidget);
        step1Layout->setObjectName(QString::fromUtf8("step1Layout"));
        step1Layout->setContentsMargins(0, 0, 0, 0);
        skillLabelShow = new QLabel(classInsertGroupBox);
        skillLabelShow->setObjectName(QString::fromUtf8("skillLabelShow"));
        skillLabelShow->setGeometry(QRect(20, 80, 46, 13));
        step2WidgetInfo = new QWidget(classInsertGroupBox);
        step2WidgetInfo->setObjectName(QString::fromUtf8("step2WidgetInfo"));
        step2WidgetInfo->setGeometry(QRect(50, 110, 261, 471));
        verticalLayoutWidget_2 = new QWidget(step2WidgetInfo);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 10, 261, 451));
        step2Layout = new QVBoxLayout(verticalLayoutWidget_2);
        step2Layout->setObjectName(QString::fromUtf8("step2Layout"));
        step2Layout->setContentsMargins(0, 0, 0, 0);
        cancelCourseButton = new QPushButton(classInsertGroupBox);
        cancelCourseButton->setObjectName(QString::fromUtf8("cancelCourseButton"));
        cancelCourseButton->setGeometry(QRect(190, 590, 131, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/myclass/Resources/cancel_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelCourseButton->setIcon(icon1);
        saveCourseButton = new QPushButton(classInsertGroupBox);
        saveCourseButton->setObjectName(QString::fromUtf8("saveCourseButton"));
        saveCourseButton->setGeometry(QRect(20, 590, 141, 23));
        saveCourseButton->setAutoFillBackground(true);
        line2_3 = new QFrame(Form);
        line2_3->setObjectName(QString::fromUtf8("line2_3"));
        line2_3->setGeometry(QRect(30, 320, 381, 16));
        line2_3->setFrameShape(QFrame::HLine);
        line2_3->setFrameShadow(QFrame::Sunken);
        line1_2 = new QFrame(Form);
        line1_2->setObjectName(QString::fromUtf8("line1_2"));
        line1_2->setGeometry(QRect(30, 100, 381, 16));
        line1_2->setFrameShape(QFrame::HLine);
        line1_2->setFrameShadow(QFrame::Sunken);
        step2Widget = new QWidget(Form);
        step2Widget->setObjectName(QString::fromUtf8("step2Widget"));
        step2Widget->setGeometry(QRect(30, 120, 381, 191));
        step2Label = new QLabel(step2Widget);
        step2Label->setObjectName(QString::fromUtf8("step2Label"));
        step2Label->setGeometry(QRect(10, 20, 211, 16));
        leftWidget = new QListWidget(step2Widget);
        leftWidget->setObjectName(QString::fromUtf8("leftWidget"));
        leftWidget->setGeometry(QRect(20, 50, 121, 111));
        rightWidget = new QListWidget(step2Widget);
        rightWidget->setObjectName(QString::fromUtf8("rightWidget"));
        rightWidget->setGeometry(QRect(230, 50, 121, 111));
        left2RightButton = new QPushButton(step2Widget);
        left2RightButton->setObjectName(QString::fromUtf8("left2RightButton"));
        left2RightButton->setGeometry(QRect(160, 50, 51, 23));
        right2LeftButton = new QPushButton(step2Widget);
        right2LeftButton->setObjectName(QString::fromUtf8("right2LeftButton"));
        right2LeftButton->setGeometry(QRect(160, 80, 51, 23));
        all2RightButton = new QPushButton(step2Widget);
        all2RightButton->setObjectName(QString::fromUtf8("all2RightButton"));
        all2RightButton->setGeometry(QRect(160, 110, 51, 23));
        all2LeftButton = new QPushButton(step2Widget);
        all2LeftButton->setObjectName(QString::fromUtf8("all2LeftButton"));
        all2LeftButton->setGeometry(QRect(160, 140, 51, 23));
        saveButton2 = new QPushButton(step2Widget);
        saveButton2->setObjectName(QString::fromUtf8("saveButton2"));
        saveButton2->setGeometry(QRect(340, 10, 41, 31));
        saveButton2->setIcon(icon);
        saveButton2->setIconSize(QSize(18, 18));
        addSkill = new QPushButton(step2Widget);
        addSkill->setObjectName(QString::fromUtf8("addSkill"));
        addSkill->setGeometry(QRect(260, 10, 75, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/myclass/Resources/add-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        addSkill->setIcon(icon2);
        addSkill->setIconSize(QSize(18, 18));
        label = new QLabel(step2Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 170, 46, 13));
        label_2 = new QLabel(step2Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(260, 170, 71, 16));
        step3Widget = new QWidget(Form);
        step3Widget->setObjectName(QString::fromUtf8("step3Widget"));
        step3Widget->setGeometry(QRect(30, 340, 381, 281));
        step2Label_2 = new QLabel(step3Widget);
        step2Label_2->setObjectName(QString::fromUtf8("step2Label_2"));
        step2Label_2->setGeometry(QRect(10, 10, 131, 16));
        verticalLayoutWidget = new QWidget(step3Widget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 30, 351, 241));
        verticalLayoutWidget_3 = new QWidget(verticalLayoutWidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(0, 10, 351, 221));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(step3Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(110, 10, 231, 16));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Add Course", 0, QApplication::UnicodeUTF8));
        resultLabel->setText(QString());
        step1Label->setText(QApplication::translate("Form", "<html><head/><body><p><span style=\" font-weight:600;\">Step 1 :Course name (e.g: Ielts, Toefl,...)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        setCourseLabel->setText(QApplication::translate("Form", "Set course name:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveButton->setToolTip(QApplication::translate("Form", "save course name", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        classInsertGroupBox->setToolTip(QApplication::translate("Form", "Add skills", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        classInsertGroupBox->setTitle(QApplication::translate("Form", "Info inserted :", 0, QApplication::UnicodeUTF8));
        skillLabelShow->setText(QApplication::translate("Form", "<html><head/><body><p><span style=\" font-weight:600;\">Skills:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        cancelCourseButton->setText(QApplication::translate("Form", "Cancel", 0, QApplication::UnicodeUTF8));
        saveCourseButton->setText(QApplication::translate("Form", "FINISH,  BACK  TO LIST !!!", 0, QApplication::UnicodeUTF8));
        step2Label->setText(QApplication::translate("Form", "<html><head/><body><p><span style=\" font-weight:600;\">Step 2: Skills</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        left2RightButton->setText(QApplication::translate("Form", ">>", 0, QApplication::UnicodeUTF8));
        right2LeftButton->setText(QApplication::translate("Form", "<<", 0, QApplication::UnicodeUTF8));
        all2RightButton->setText(QApplication::translate("Form", "all >>", 0, QApplication::UnicodeUTF8));
        all2LeftButton->setText(QApplication::translate("Form", "<< all", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveButton2->setToolTip(QApplication::translate("Form", "save skill", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveButton2->setText(QString());
#ifndef QT_NO_TOOLTIP
        addSkill->setToolTip(QApplication::translate("Form", "add skill", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addSkill->setText(QString());
        label->setText(QApplication::translate("Form", "Skill list", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Form", "course's skill", 0, QApplication::UnicodeUTF8));
        step2Label_2->setText(QApplication::translate("Form", "<html><head/><body><p><span style=\" font-weight:600;\">Step 3: Materials</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form", "(Can not add 2 materials with the same name!!)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCOURSE_H
