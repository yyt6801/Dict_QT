#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif

#include <QtWidgets/QWidget>
#include "ui_QtGuiApplication2.h"

class QtGuiApplication2 : public QWidget
{
    Q_OBJECT

public:
    QtGuiApplication2(QWidget *parent = Q_NULLPTR);
private slots:
	void on_pushButton_clicked();
private:
    Ui::QtGuiApplication2Class ui;
	QPushButton *ui_findButton;
	QTextEdit *ui_textEdit;
	QLineEdit *ui_lineEdit;
};