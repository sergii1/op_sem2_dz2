#include "xmlview.h"

XMLView::XMLView(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowIcon(QIcon("IconXML2.png"));
    QWidget *widget = new QWidget();
    m_Layout = new QGridLayout();
    m_LabelXML = new QLabel("Xml Файл:");
    m_TreeView = new QTreeView;
    m_LabelXQuery = new QLabel("XQuery:");
    m_XQueryTextEdit = new QTextEdit;
    m_bttnSubmit = new QPushButton("Выполнить");
    m_bttnLoadXQFile = new QPushButton("Загрузить xq-файл");
    m_Layout->addWidget(m_LabelXML);
    m_Layout->addWidget(m_TreeView);
    m_Layout->addWidget(m_LabelXQuery);
    m_Layout->addWidget(m_XQueryTextEdit);
    m_Layout->addWidget(m_bttnSubmit);
    m_Layout->addWidget(m_bttnLoadXQFile);
    widget->setLayout(m_Layout);
    setCentralWidget(widget);
    QMenu* pmnuFile = new QMenu("Файл");
    pmnuFile->addAction("Открыть", this, SLOT(slotOpen()));
    pmnuFile->addAction("Закрыть все", this, SLOT(slotClose()));
    pmnuFile->addAction("Выход", this, SLOT(slotExit()));
    menuBar()->addMenu(pmnuFile);
    menuBar()->addSeparator();
    QMenu* pmnuFAQ = new QMenu("Справка");
    pmnuFAQ->addAction("О программе", this, SLOT(slotAbout()));
    menuBar()->addMenu(pmnuFAQ);
    is_empty = true;

    connect(m_bttnSubmit, SIGNAL(clicked(bool)), this, SLOT(slotSubmit()));
    connect(m_bttnLoadXQFile, SIGNAL(clicked(bool)), this, SLOT(slotLoadXQFile()));

}

void XMLView::slotOpen()
{
    if(!is_empty)
        m_file->close();
    qDebug() << "Open";
    m_file = new QFile(QFileDialog::getOpenFileName(this, "Открыть XML файл..."));
    QDomDocument document;
    document.setContent(m_file);
    if(!m_file)
    {
        QMessageBox *message = new QMessageBox(QMessageBox::Critical, "Ошибка", "Не удалось открыть файл", QMessageBox::Ok, this);
        message->show();
        delete m_file;
        m_file = nullptr;
        return;
    }

    m_model = new DomModel(document, this);
    m_TreeView->setModel(m_model);
    QHeaderView* pTreeHeader = m_TreeView->header();
    pTreeHeader->setStretchLastSection(false);
    pTreeHeader->setSectionResizeMode(0, QHeaderView::Stretch);
    pTreeHeader->setSectionResizeMode(1, QHeaderView::Stretch);
    QFileInfo fInfo(*m_file);
    setWindowTitle("XML Parser - " + fInfo.baseName());
    m_file->close();
    is_empty = false;
}

void XMLView::slotClose()
{
    if(is_empty)
        return;
    delete m_file;
    delete m_model;
    m_TreeView->setModel(nullptr);
    m_XQueryTextEdit->clear();
    m_file = nullptr;
    m_model = nullptr;
    setWindowTitle("XML Parser");
//    m_closeAction->setEnabled(false);
//    m_executeButton->setEnabled(false);
//    m_executeAction->setEnabled(false);
//    m_loadButton->setEnabled(false);
//    m_loadAction->setEnabled(false);
    is_empty = true;
}

void XMLView::slotExit()
{
    slotClose();
    close();
}

void XMLView::slotSubmit()
{
    m_file->open(QIODevice::ReadOnly);
    QXmlQuery q;
//    q.bindVariable("document", m_file);
    q.setFocus(m_file);
    q.setQuery(m_XQueryTextEdit->toPlainText());
    QString result;
    if(!q.evaluateTo(&result))
        result = "Выполнение xQuery запроса завершилось ошибкой";
    else if(result == "" || result == "\n")
        result = "Выполнение xQuery запроса не дало результатов";
    QMessageBox::information(this, "Результат", result);
//    QXmlResultItems results;
//    q.evaluateTo(&results);
//    QXmlQuery childQuery(q.namePool());
//    while (!results.next().isNull()) {
//        childQuery.setFocus(results.current());
//        childQuery.setQuery("./global_id/text()");
//        QString r;
//        childQuery.evaluateTo(&r);
//        qDebug() << r;
//    }
    m_file->close();
}

void XMLView::slotLoadXQFile()
{
    QFile *file = new QFile(QFileDialog::getOpenFileName(this, "Открыть xQuery файл..."));
    QDomDocument document;
    if(!file)
    {
        QMessageBox::critical(this,  "Ошибка", "Не удалось открыть файл");
        delete file;
        return;
    }

    file->open(QIODevice::ReadOnly);
    m_XQueryTextEdit->clear();
    m_XQueryTextEdit->insertPlainText(QString(file->readAll()));
    file->close();
    delete file;
}

void XMLView::slotAbout()
{
    QMessageBox::about(this, "О программе", "Домашнее задание №2\nШамшидов О.\nЧепурной С. (ФН11-32)");
}

XMLView::~XMLView()
{
}
