/********************************************************************************
** Form generated from reading UI file 'sysmonitor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSMONITOR_H
#define UI_SYSMONITOR_H

#include <QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sysMonitor
{
public:
    QTabWidget *selectTab;
    QWidget *tab_1;
    QTableWidget *processInfo;
    QPushButton *killProcessBtn;
    QLineEdit *searchLineEdit;
    QWidget *tab_2;
    QGroupBox *groupBox;
    QChartView *cpuUsageChart;
    QLabel *label_21;
    QLabel *cpuUsageLabel;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *cpuInfoLabel;
    QLabel *label_3;
    QLabel *coreNumLabel;
    QLabel *label_44;
    QLabel *uptimeLabel;
    QWidget *tab_3;
    QGroupBox *groupBox_3;
    QChartView *memoryUsageChart;
    QLabel *label_31;
    QLabel *inUseMemoryLabel;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_5;
    QLabel *totalMemoryLabel;
    QLabel *label_34;
    QLabel *availableMemoryLabel;
    QLabel *label_35;
    QLabel *memoryUsageLabel;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *totalVirtualMemoryLabel;
    QLabel *availableVirtualMemoryLabel;
    QWidget *tab_4;
    QGroupBox *formGroupBox;
    QFormLayout *formLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_41;
    QLabel *localHostNameLabel;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_42;
    QLabel *osInfoLabel;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_43;
    QLabel *osTypeLabel;
    QSpacerItem *verticalSpacer_7;
    QGroupBox *groupBox_4;
    QLabel *label_45;
    QLabel *diskInfoLabel;
    QPushButton *diskRefreshBtn;
    QWidget *tab_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;

    void setupUi(QWidget *sysMonitor)
    {
        if (sysMonitor->objectName().isEmpty())
            sysMonitor->setObjectName(QStringLiteral("sysMonitor"));
        sysMonitor->setWindowModality(Qt::NonModal);
        sysMonitor->resize(720, 576);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sysMonitor->sizePolicy().hasHeightForWidth());
        sysMonitor->setSizePolicy(sizePolicy);
        selectTab = new QTabWidget(sysMonitor);
        selectTab->setObjectName(QStringLiteral("selectTab"));
        selectTab->setGeometry(QRect(0, 0, 720, 576));
        QFont font;
        font.setFamily(QStringLiteral("Bahnschrift Light"));
        selectTab->setFont(font);
        selectTab->setMouseTracking(false);
        selectTab->setStyleSheet(QLatin1String("QTabWidget::pane\n"
"{\n"
"	top:3px;\n"
"	border:none;\n"
"	bottom:3px;\n"
"}\n"
"QTabBar::tab\n"
"{\n"
"	color:#333333;\n"
"	background:transparent;	\n"
"	padding-left:9px;\n"
"	padding-right:9px;\n"
"	width:75px;\n"
"	height:30px;\n"
"	margin-left:0px;\n"
"	margin-right:0px;\n"
"} \n"
"\n"
"QTabBar::tab:selected\n"
"{\n"
"	color:#618BE5;\n"
"	background:transparent;	\n"
"	border-bottom:2px solid #618BE5;\n"
"}\n"
"\n"
"QTabBar::tab:hover\n"
"{\n"
"	color:#618BE5;\n"
"	background:transparent;	\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    alignment: left;  \n"
"	left:20px;	\n"
"} \n"
"\n"
""));
        selectTab->setIconSize(QSize(16, 16));
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        processInfo = new QTableWidget(tab_1);
        if (processInfo->columnCount() < 7)
            processInfo->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        processInfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        processInfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        processInfo->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        processInfo->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        processInfo->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        processInfo->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        processInfo->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        processInfo->setObjectName(QStringLiteral("processInfo"));
        processInfo->setGeometry(QRect(0, 0, 720, 500));
        sizePolicy.setHeightForWidth(processInfo->sizePolicy().hasHeightForWidth());
        processInfo->setSizePolicy(sizePolicy);
        processInfo->setMaximumSize(QSize(720, 505));
        processInfo->setMouseTracking(true);
        processInfo->setFocusPolicy(Qt::NoFocus);
        processInfo->setContextMenuPolicy(Qt::CustomContextMenu);
        processInfo->setStyleSheet(QLatin1String("font: 25 9pt \"Bahnschrift Light\";\n"
"selection-background-color: lightblue;\n"
"QScrollBar::handle {\n"
"	background:lightgray;\n"
"	border:2px solid transparent;\n"
"	border-radius:5px;\n"
"}\n"
"QScrollBar::handle:hover {\n"
"	background:gray;\n"
"}\n"
"QScrollBar::sub-line {\n"
"	background:transparent;\n"
"}\n"
"QScrollBar::addline {\n"
"	background:transparent;\n"
"}"));
        processInfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        processInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        processInfo->setSelectionMode(QAbstractItemView::SingleSelection);
        processInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        processInfo->setShowGrid(false);
        processInfo->setGridStyle(Qt::SolidLine);
        processInfo->setSortingEnabled(false);
        processInfo->horizontalHeader()->setCascadingSectionResizes(true);
        processInfo->horizontalHeader()->setHighlightSections(false);
        processInfo->horizontalHeader()->setStretchLastSection(true);
        processInfo->verticalHeader()->setVisible(false);
        killProcessBtn = new QPushButton(tab_1);
        killProcessBtn->setObjectName(QStringLiteral("killProcessBtn"));
        killProcessBtn->setGeometry(QRect(620, 505, 90, 30));
        QFont font1;
        font1.setFamily(QStringLiteral("Bahnschrift Light"));
        font1.setPointSize(8);
        killProcessBtn->setFont(font1);
        searchLineEdit = new QLineEdit(tab_1);
        searchLineEdit->setObjectName(QStringLiteral("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(5, 510, 261, 25));
        searchLineEdit->setFont(font);
        selectTab->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 5, 700, 530));
        QFont font2;
        font2.setFamily(QStringLiteral("Bahnschrift Light"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        groupBox->setFont(font2);
        cpuUsageChart = new QChartView(groupBox);
        cpuUsageChart->setObjectName(QStringLiteral("cpuUsageChart"));
        cpuUsageChart->setGeometry(QRect(30, 65, 640, 220));
        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(30, 335, 120, 20));
        label_21->setFont(font1);
        cpuUsageLabel = new QLabel(groupBox);
        cpuUsageLabel->setObjectName(QStringLiteral("cpuUsageLabel"));
        cpuUsageLabel->setGeometry(QRect(150, 335, 521, 20));
        cpuUsageLabel->setFont(font);
        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(655, 285, 16, 16));
        label_22->setFont(font1);
        label_23 = new QLabel(groupBox);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(30, 285, 120, 16));
        label_23->setFont(font1);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(645, 45, 32, 15));
        label->setFont(font1);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 45, 120, 15));
        label_4->setFont(font1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 380, 90, 20));
        label_2->setFont(font1);
        cpuInfoLabel = new QLabel(groupBox);
        cpuInfoLabel->setObjectName(QStringLiteral("cpuInfoLabel"));
        cpuInfoLabel->setGeometry(QRect(150, 380, 500, 20));
        cpuInfoLabel->setFont(font);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 420, 80, 20));
        label_3->setFont(font1);
        coreNumLabel = new QLabel(groupBox);
        coreNumLabel->setObjectName(QStringLiteral("coreNumLabel"));
        coreNumLabel->setGeometry(QRect(150, 420, 500, 20));
        coreNumLabel->setFont(font);
        label_44 = new QLabel(groupBox);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setGeometry(QRect(30, 460, 56, 17));
        label_44->setFont(font1);
        uptimeLabel = new QLabel(groupBox);
        uptimeLabel->setObjectName(QStringLiteral("uptimeLabel"));
        uptimeLabel->setGeometry(QRect(150, 460, 500, 17));
        uptimeLabel->setFont(font);
        selectTab->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 5, 700, 530));
        QFont font3;
        font3.setFamily(QStringLiteral("Bahnschrift Light"));
        font3.setPointSize(10);
        groupBox_3->setFont(font3);
        memoryUsageChart = new QChartView(groupBox_3);
        memoryUsageChart->setObjectName(QStringLiteral("memoryUsageChart"));
        memoryUsageChart->setGeometry(QRect(30, 65, 640, 220));
        label_31 = new QLabel(groupBox_3);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(30, 320, 70, 20));
        label_31->setFont(font1);
        inUseMemoryLabel = new QLabel(groupBox_3);
        inUseMemoryLabel->setObjectName(QStringLiteral("inUseMemoryLabel"));
        inUseMemoryLabel->setGeometry(QRect(230, 320, 420, 20));
        inUseMemoryLabel->setFont(font);
        label_32 = new QLabel(groupBox_3);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(655, 285, 16, 16));
        label_32->setFont(font1);
        label_33 = new QLabel(groupBox_3);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(30, 285, 120, 16));
        label_33->setFont(font1);
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 45, 120, 15));
        label_5->setFont(font1);
        totalMemoryLabel = new QLabel(groupBox_3);
        totalMemoryLabel->setObjectName(QStringLiteral("totalMemoryLabel"));
        totalMemoryLabel->setGeometry(QRect(630, 45, 40, 15));
        totalMemoryLabel->setFont(font1);
        label_34 = new QLabel(groupBox_3);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(30, 360, 70, 20));
        label_34->setFont(font1);
        availableMemoryLabel = new QLabel(groupBox_3);
        availableMemoryLabel->setObjectName(QStringLiteral("availableMemoryLabel"));
        availableMemoryLabel->setGeometry(QRect(230, 360, 420, 20));
        availableMemoryLabel->setFont(font);
        label_35 = new QLabel(groupBox_3);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(30, 400, 70, 20));
        label_35->setFont(font1);
        memoryUsageLabel = new QLabel(groupBox_3);
        memoryUsageLabel->setObjectName(QStringLiteral("memoryUsageLabel"));
        memoryUsageLabel->setGeometry(QRect(230, 400, 420, 20));
        memoryUsageLabel->setFont(font);
        label_36 = new QLabel(groupBox_3);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(30, 440, 150, 20));
        label_36->setFont(font1);
        label_37 = new QLabel(groupBox_3);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(30, 480, 150, 20));
        label_37->setFont(font1);
        totalVirtualMemoryLabel = new QLabel(groupBox_3);
        totalVirtualMemoryLabel->setObjectName(QStringLiteral("totalVirtualMemoryLabel"));
        totalVirtualMemoryLabel->setGeometry(QRect(230, 440, 420, 20));
        totalVirtualMemoryLabel->setFont(font);
        availableVirtualMemoryLabel = new QLabel(groupBox_3);
        availableVirtualMemoryLabel->setObjectName(QStringLiteral("availableVirtualMemoryLabel"));
        availableVirtualMemoryLabel->setGeometry(QRect(230, 480, 420, 20));
        availableVirtualMemoryLabel->setFont(font);
        selectTab->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        formGroupBox = new QGroupBox(tab_4);
        formGroupBox->setObjectName(QStringLiteral("formGroupBox"));
        formGroupBox->setGeometry(QRect(10, 5, 700, 250));
        formGroupBox->setFont(font3);
        formLayout = new QFormLayout(formGroupBox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(0, QFormLayout::LabelRole, verticalSpacer);

        label_41 = new QLabel(formGroupBox);
        label_41->setObjectName(QStringLiteral("label_41"));
        label_41->setFont(font1);
        label_41->setLineWidth(1);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_41);

        localHostNameLabel = new QLabel(formGroupBox);
        localHostNameLabel->setObjectName(QStringLiteral("localHostNameLabel"));
        localHostNameLabel->setFont(font);

        formLayout->setWidget(1, QFormLayout::FieldRole, localHostNameLabel);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(2, QFormLayout::LabelRole, verticalSpacer_3);

        label_42 = new QLabel(formGroupBox);
        label_42->setObjectName(QStringLiteral("label_42"));
        label_42->setFont(font1);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_42);

        osInfoLabel = new QLabel(formGroupBox);
        osInfoLabel->setObjectName(QStringLiteral("osInfoLabel"));
        osInfoLabel->setFont(font);

        formLayout->setWidget(4, QFormLayout::FieldRole, osInfoLabel);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(5, QFormLayout::LabelRole, verticalSpacer_6);

        label_43 = new QLabel(formGroupBox);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setFont(font1);

        formLayout->setWidget(6, QFormLayout::LabelRole, label_43);

        osTypeLabel = new QLabel(formGroupBox);
        osTypeLabel->setObjectName(QStringLiteral("osTypeLabel"));
        osTypeLabel->setFont(font);

        formLayout->setWidget(6, QFormLayout::FieldRole, osTypeLabel);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(7, QFormLayout::LabelRole, verticalSpacer_7);

        groupBox_4 = new QGroupBox(tab_4);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 265, 700, 225));
        groupBox_4->setFont(font3);
        label_45 = new QLabel(groupBox_4);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setGeometry(QRect(15, 40, 120, 17));
        label_45->setFont(font1);
        diskInfoLabel = new QLabel(groupBox_4);
        diskInfoLabel->setObjectName(QStringLiteral("diskInfoLabel"));
        diskInfoLabel->setGeometry(QRect(15, 70, 671, 140));
        diskInfoLabel->setFont(font);
        diskRefreshBtn = new QPushButton(tab_4);
        diskRefreshBtn->setObjectName(QStringLiteral("diskRefreshBtn"));
        diskRefreshBtn->setGeometry(QRect(620, 505, 90, 30));
        diskRefreshBtn->setFont(font1);
        selectTab->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        label_6 = new QLabel(tab_5);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(310, 20, 381, 411));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/img/author.JPG")));
        label_7 = new QLabel(tab_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 90, 251, 41));
        label_7->setFont(font);
        label_8 = new QLabel(tab_5);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 150, 241, 31));
        label_8->setFont(font);
        label_9 = new QLabel(tab_5);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(30, 210, 241, 31));
        label_9->setFont(font);
        selectTab->addTab(tab_5, QString());

        retranslateUi(sysMonitor);

        selectTab->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(sysMonitor);
    } // setupUi

    void retranslateUi(QWidget *sysMonitor)
    {
        sysMonitor->setWindowTitle(QApplication::translate("sysMonitor", "System monitor", nullptr));
        QTableWidgetItem *___qtablewidgetitem = processInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("sysMonitor", "PID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = processInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("sysMonitor", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = processInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("sysMonitor", "PPID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = processInfo->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("sysMonitor", "Threads", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = processInfo->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("sysMonitor", "Memory", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = processInfo->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("sysMonitor", "Priority", nullptr));
        killProcessBtn->setText(QApplication::translate("sysMonitor", "End task", nullptr));
        searchLineEdit->setPlaceholderText(QApplication::translate("sysMonitor", "Search process", nullptr));
        selectTab->setTabText(selectTab->indexOf(tab_1), QApplication::translate("sysMonitor", "Process", nullptr));
        groupBox->setTitle(QApplication::translate("sysMonitor", "CPU", nullptr));
        label_21->setText(QApplication::translate("sysMonitor", "Utilisatoin:", nullptr));
        cpuUsageLabel->setText(QString());
        label_22->setText(QApplication::translate("sysMonitor", "0", nullptr));
        label_23->setText(QApplication::translate("sysMonitor", "60 seconds", nullptr));
        label->setText(QApplication::translate("sysMonitor", "100%", nullptr));
        label_4->setText(QApplication::translate("sysMonitor", "%  Utilisation", nullptr));
        label_2->setText(QApplication::translate("sysMonitor", "Processor:", nullptr));
        cpuInfoLabel->setText(QString());
        label_3->setText(QApplication::translate("sysMonitor", "Cores:", nullptr));
        coreNumLabel->setText(QString());
        label_44->setText(QApplication::translate("sysMonitor", "Up time:", nullptr));
        uptimeLabel->setText(QString());
        selectTab->setTabText(selectTab->indexOf(tab_2), QApplication::translate("sysMonitor", "CPU", nullptr));
        groupBox_3->setTitle(QApplication::translate("sysMonitor", "Memory", nullptr));
        label_31->setText(QApplication::translate("sysMonitor", "In use:", nullptr));
        inUseMemoryLabel->setText(QString());
        label_32->setText(QApplication::translate("sysMonitor", "0", nullptr));
        label_33->setText(QApplication::translate("sysMonitor", "60s", nullptr));
        label_5->setText(QApplication::translate("sysMonitor", "Memory  usage", nullptr));
        totalMemoryLabel->setText(QString());
        label_34->setText(QApplication::translate("sysMonitor", "Available:", nullptr));
        availableMemoryLabel->setText(QString());
        label_35->setText(QApplication::translate("sysMonitor", "Utilisation:", nullptr));
        memoryUsageLabel->setText(QString());
        label_36->setText(QApplication::translate("sysMonitor", "Total virtual memory:", nullptr));
        label_37->setText(QApplication::translate("sysMonitor", "Available virtual memory:", nullptr));
        totalVirtualMemoryLabel->setText(QString());
        availableVirtualMemoryLabel->setText(QString());
        selectTab->setTabText(selectTab->indexOf(tab_3), QApplication::translate("sysMonitor", "Memory", nullptr));
        formGroupBox->setTitle(QApplication::translate("sysMonitor", "System", nullptr));
        label_41->setText(QApplication::translate("sysMonitor", "Computer name:", nullptr));
        localHostNameLabel->setText(QString());
        label_42->setText(QApplication::translate("sysMonitor", "Opeatring system:", nullptr));
        osInfoLabel->setText(QString());
        label_43->setText(QApplication::translate("sysMonitor", "System type:", nullptr));
        osTypeLabel->setText(QString());
        groupBox_4->setTitle(QApplication::translate("sysMonitor", "Disk", nullptr));
        label_45->setText(QApplication::translate("sysMonitor", "Utilisation:", nullptr));
        diskInfoLabel->setText(QString());
        diskRefreshBtn->setText(QApplication::translate("sysMonitor", "Refresh", nullptr));
        selectTab->setTabText(selectTab->indexOf(tab_4), QApplication::translate("sysMonitor", "Other", nullptr));
        label_6->setText(QString());
        label_7->setText(QApplication::translate("sysMonitor", "Author:  Raymond Wong", nullptr));
        label_8->setText(QApplication::translate("sysMonitor", "Class:    1702", nullptr));
        label_9->setText(QApplication::translate("sysMonitor", "Id:            U201716998", nullptr));
        selectTab->setTabText(selectTab->indexOf(tab_5), QApplication::translate("sysMonitor", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sysMonitor: public Ui_sysMonitor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSMONITOR_H
