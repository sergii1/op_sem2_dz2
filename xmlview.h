#ifndef XMLVIEW_H
#define XMLVIEW_H

#include <QMainWindow>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QtXml>
#include <QTreeView>
#include <QGridLayout>
#include <QFileInfo>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QtXmlPatterns/QXmlQuery>
#include <QHeaderView>
#include <QXmlResultItems>
#include "dommodel.h"

class XMLView : public QMainWindow
{
    Q_OBJECT

public:
    explicit XMLView(QWidget *parent = 0);
    ~XMLView();

private:
    QFile *m_file;
    DomModel *m_model;
    QLabel* m_LabelXML;
    QTreeView* m_TreeView;
    QLabel* m_LabelXQuery;
    QTextEdit* m_XQueryTextEdit;
    QGridLayout* m_Layout;
    QPushButton* m_bttnSubmit;
    QPushButton* m_bttnLoadXQFile;
    bool is_empty;
public slots:
    void slotOpen();
    void slotClose();
    void slotExit();
    void slotSubmit();
    void slotLoadXQFile();
    void slotAbout();
};

#endif // XMLVIEW_H
