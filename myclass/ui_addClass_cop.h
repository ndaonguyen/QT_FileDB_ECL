/********************************************************************************
** Form generated from reading UI file 'addClass.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCLASS_H
#define UI_ADDCLASS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addClassWidget
{
public:
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
    QWidget *courseInfoWidget;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *courseInfoLayout;
    QWidget *classAdd2Widget;
    QLabel *label_3;
    QLabel *memberLabel;
    QTableView *addMemberTable;
    QGroupBox *groupBox_2;
    QWidget *classAdd3Widget;
    QLabel *courseClassLabel;
    QComboBox *courseComboBox;
    QLabel *chooseCourseLabel;
    QGroupBox *groupBox_3;
    QPushButton *enableClass2Button;
    QPushButton *cancelButton;
    QLabel *courseInfoLabel;
    QPushButton *enableClass1Button;
    QFrame *line;
    QPushButton *saveButton_2;
    QPushButton *enableClass3Button;

    void setupUi(QWidget *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName(QString::fromUtf8("widget"));
        widget->resize(934, 630);
        widget->setMinimumSize(QSize(934, 630));
        widget->setMaximumSize(QSize(934, 630));
        classAdd1Widget = new QWidget(widget);
        classAdd1Widget->setObjectName(QString::fromUtf8("classAdd1Widget"));
        classAdd1Widget->setGeometry(QRect(20, 20, 431, 221));
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
        courseInfoWidget = new QWidget(widget);
        courseInfoWidget->setObjectName(QString::fromUtf8("courseInfoWidget"));
        courseInfoWidget->setGeometry(QRect(480, 50, 411, 531));
        verticalLayoutWidget_4 = new QWidget(courseInfoWidget);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(10, 20, 401, 501));
        courseInfoLayout = new QVBoxLayout(verticalLayoutWidget_4);
        courseInfoLayout->setObjectName(QString::fromUtf8("courseInfoLayout"));
        courseInfoLayout->setContentsMargins(0, 0, 0, 0);
        classAdd2Widget = new QWidget(widget);
        classAdd2Widget->setObjectName(QString::fromUtf8("classAdd2Widget"));
        classAdd2Widget->setGeometry(QRect(20, 260, 431, 211));
        label_3 = new QLabel(classAdd2Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 180, 281, 16));
        memberLabel = new QLabel(classAdd2Widget);
        memberLabel->setObjectName(QString::fromUtf8("memberLabel"));
        memberLabel->setGeometry(QRect(10, 30, 91, 16));
        addMemberTable = new QTableView(classAdd2Widget);
        addMemberTable->setObjectName(QString::fromUtf8("addMemberTable"));
        addMemberTable->setGeometry(QRect(100, 30, 321, 151));
        groupBox_2 = new QGroupBox(classAdd2Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 0, 441, 201));
        groupBox_2->raise();
        label_3->raise();
        memberLabel->raise();
        addMemberTable->raise();
        classAdd3Widget = new QWidget(widget);
        classAdd3Widget->setObjectName(QString::fromUtf8("classAdd3Widget"));
        classAdd3Widget->setGeometry(QRect(20, 479, 431, 101));
        courseClassLabel = new QLabel(classAdd3Widget);
        courseClassLabel->setObjectName(QString::fromUtf8("courseClassLabel"));
        courseClassLabel->setGeometry(QRect(100, 30, 251, 16));
        courseComboBox = new QComboBox(classAdd3Widget);
        courseComboBox->setObjectName(QString::fromUtf8("courseComboBox"));
        courseComboBox->setGeometry(QRect(100, 60, 121, 22));
        chooseCourseLabel = new QLabel(classAdd3Widget);
        chooseCourseLabel->setObjectName(QString::fromUtf8("chooseCourseLabel"));
        chooseCourseLabel->setGeometry(QRect(10, 30, 91, 16));
        groupBox_3 = new QGroupBox(classAdd3Widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 10, 431, 81));
        groupBox_3->raise();
        courseClassLabel->raise();
        courseComboBox->raise();
        chooseCourseLabel->raise();
        enableClass2Button = new QPushButton(widget);
        enableClass2Button->setObjectName(QString::fromUtf8("enableClass2Button"));
        enableClass2Button->setGeometry(QRect(310, 250, 141, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/myclass/Resources/TurnOn_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        enableClass2Button->setIcon(icon);
        cancelButton = new QPushButton(widget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(510, 590, 221, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/myclass/Resources/cancel_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon1);
        courseInfoLabel = new QLabel(widget);
        courseInfoLabel->setObjectName(QString::fromUtf8("courseInfoLabel"));
        courseInfoLabel->setGeometry(QRect(480, 30, 231, 16));
        enableClass1Button = new QPushButton(widget);
        enableClass1Button->setObjectName(QString::fromUtf8("enableClass1Button"));
        enableClass1Button->setGeometry(QRect(310, 10, 141, 23));
        enableClass1Button->setIcon(icon);
        line = new QFrame(widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(450, 30, 20, 561));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        saveButton_2 = new QPushButton(widget);
        saveButton_2->setObjectName(QString::fromUtf8("saveButton_2"));
        saveButton_2->setGeometry(QRect(140, 590, 241, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/myclass/Resources/save_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveButton_2->setIcon(icon2);
        enableClass3Button = new QPushButton(widget);
        enableClass3Button->setObjectName(QString::fromUtf8("enableClass3Button"));
        enableClass3Button->setGeometry(QRect(310, 480, 141, 23));
        enableClass3Button->setIcon(icon);
        QWidget::setTabOrder(classNameLineEdit, regisdateEdit);
        QWidget::setTabOrder(regisdateEdit, totalDateLineEdit);
        QWidget::setTabOrder(totalDateLineEdit, otherLineEdit);
        QWidget::setTabOrder(otherLineEdit, addMemberTable);
        QWidget::setTabOrder(addMemberTable, courseComboBox);
        QWidget::setTabOrder(courseComboBox, saveButton_2);
        QWidget::setTabOrder(saveButton_2, cancelButton);
        QWidget::setTabOrder(cancelButton, enableClass1Button);
        QWidget::setTabOrder(enableClass1Button, enableClass2Button);
        QWidget::setTabOrder(enableClass2Button, enableClass3Button);
        QWidget::setTabOrder(enableClass3Button, dayUseSpinBox);

        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QWidget *widget)
    {
        widget->setWindowTitle(QApplication::translate("widget", "Add Class", 0, QApplication::UnicodeUTF8));
        otherLabel->setText(QApplication::translate("widget", "Note", 0, QApplication::UnicodeUTF8));
        totalDayLabel->setText(QApplication::translate("widget", "Total days", 0, QApplication::UnicodeUTF8));
        dayUseLabel->setText(QApplication::translate("widget", "Day use", 0, QApplication::UnicodeUTF8));
        classNameLabel->setText(QApplication::translate("widget", "Class name", 0, QApplication::UnicodeUTF8));
        regisDayLabel->setText(QApplication::translate("widget", "Registration day", 0, QApplication::UnicodeUTF8));
        otherLineEdit->setText(QString());
        groupBox->setTitle(QString());
        label_3->setText(QApplication::translate("widget", "Edit, delete or add member in table directly ", 0, QApplication::UnicodeUTF8));
        memberLabel->setText(QApplication::translate("widget", "Members", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        courseClassLabel->setText(QString());
        chooseCourseLabel->setText(QApplication::translate("widget", "Choose course", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QString());
        enableClass2Button->setText(QApplication::translate("widget", "Enable member edit", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("widget", "CANCEL", 0, QApplication::UnicodeUTF8));
        courseInfoLabel->setText(QString());
        enableClass1Button->setText(QApplication::translate("widget", "Enable class info edit", 0, QApplication::UnicodeUTF8));
        saveButton_2->setText(QApplication::translate("widget", "SAVE", 0, QApplication::UnicodeUTF8));
        enableClass3Button->setText(QApplication::translate("widget", "Enable course edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class addClassWidget: public Ui_addClassWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCLASS_H
