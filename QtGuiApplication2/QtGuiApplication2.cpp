#include "QtGuiApplication2.h"
#include "search_words.h"
//用到哪些组件都引用进来
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>
#include <QFile>
#include <QLibrary>
#include <QDebug>
#include <QTextCodec>
#include <qstring.h>

//继承QWidget
QtGuiApplication2::QtGuiApplication2(QWidget *parent)
	: QWidget(parent)
{
	//与UI绑定
	ui.setupUi(this);
	//通过ObjectName获取UI上的对应组件
	ui_findButton = findChild<QPushButton*>("Button1");
	ui_textEdit = findChild<QTextEdit*>("textEdit");
	ui_lineEdit = findChild<QLineEdit*>("lineEdit");//输入内容

	ui_lineEdit->setFocus();
	ui_textEdit->setText("今天又是美好的一天！");


	setWindowTitle(tr("爱星翻译"));
	//信号与槽绑定
	QMetaObject::connectSlotsByName(this);
}
//
////点击事件
//void QtGuiApplication2::on_Button1_clicked()
//{
//	QString searchString = ui_lineEdit->text();
//	QTextDocument *document = ui_textEdit->document();
//
//	bool found = false;
//
//	// undo previous change (if any)
//	document->undo();
//
//	if (searchString.isEmpty()) {
//		QMessageBox::information(this, tr("Empty Search Field"),
//			tr("The search field is empty. "
//				"Please enter a word and click Find."));
//	}
//	else {
//		QTextCursor highlightCursor(document);
//		QTextCursor cursor(document);
//
//		cursor.beginEditBlock();
//
//		QTextCharFormat plainFormat(highlightCursor.charFormat());
//		QTextCharFormat colorFormat = plainFormat;
//		colorFormat.setForeground(Qt::red);
//
//		while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
//			highlightCursor = document->find(searchString, highlightCursor,
//				QTextDocument::FindWholeWords);
//
//			if (!highlightCursor.isNull()) {
//				found = true;
//				highlightCursor.movePosition(QTextCursor::WordRight,
//					QTextCursor::KeepAnchor);
//				highlightCursor.mergeCharFormat(colorFormat);
//			}
//		}
//
//		cursor.endEditBlock();
//		if (found == false) {
//			QMessageBox::information(this, tr("Word Not Found"),
//				tr("Sorry, the word cannot be found."));
//		}
//	}
//}

//点击查词 
void QtGuiApplication2::on_pushButton_clicked()
{
	//获取输入lineEdit内容 
	QString searchString = ui_lineEdit->text();

	QByteArray arr = searchString.toUtf8(); //将输入内容转为使用UTF-8的编码 

	char *aim_code = new char[128];  // Allocate memory for the array
	strcpy(aim_code, arr.data());
	//memcpy(aim_code, arr.data(), strlen(arr.data()));

	char *root ;
	root = search_words(aim_code); //查询翻译返回值存赋值给root 
	delete[] aim_code;              // Deallocate memory for the array
	aim_code = NULL;
	
	QString str(QTextCodec::codecForName("GB2312")->toUnicode(root)); //无效 

	ui_textEdit->setText(QString(str));



	//QByteArray utf8_bytes = utf8->fromUnicode(ex_words);
	//printf("en_words = %s\n", ex_words);

	/*HINSTANCE h = LoadLibrary(L"test_dll");
	if (h != NULL)
	{
		psearch_words psearch_words = (char *(_cdecl *)(char *))(GetProcAddress(h, "search_words"));
		if (psearch_words != NULL)
		{
			char en_words[20] = "look";
			ex_words = psearch_words(en_words);
		}
		else
		{
			FreeLibrary(h);
			return;
		}
	}*/

	////方法二：使用QLibrary
	////typedef int(*Fun)(int, int); //定义函数指针，以备调用
	//QLibrary mylib("test_dll.dll");   //声明所用到的dll文件
	//int result;
	//if (mylib.load())              //判断是否正确加载
	//{
	//	QMessageBox::information(NULL, "OK", "DLL load is OK!");
	//	psearch_words open = (psearch_words)mylib.resolve("search_words");    //援引 add() 函数
	//	_declspec(dllexport) char *search_words(char *aim_code);

	//	/*psearch_words psearch_words = (char *(_cdecl *)(char *))(GetProcAddress(h, "search_words"));*/
	//	if (open)                  //是否成功连接上 add() 函数
	//	{
	//		QMessageBox::information(NULL, "OK", "Link to Function is OK!");
	//		ex_words = open("look");      //这里函数指针调用dll中的 add() 函数
	//		qDebug() << result;
	//	}
	//	else
	//		QMessageBox::information(NULL, "NO", "Linke to Function is not OK!!!!");
	//}
	//else
	//{
	//	QMessageBox::information(NULL, "NO", "DLL is not loaded!");
	//	return ;  //加载失败则退出
	//}

	////绝对路径可以读取，编码也无问题
	//QFile file("D:\\onedrive\\OneDrive - yyt6801\\QT_Projects\\QT_in_VS2015_Projects\\QtGuiApplication2\\x64\\Debug\\test.txt");
	//if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	//{
	//	QTextStream floStream(&file);
	//	floStream.setCodec("System");
	//	while (!floStream.atEnd()) {
	//		QString lineString = floStream.readLine();
	//		if (lineString != NULL && lineString != " ")
	//		{
	//			ui_textEdit->setText(lineString);
	//		}
	//	}
	//}

	//QFile file(root);
	//file.open(QIODevice::ReadOnly | QIODevice::Text);
	//QString displayString;
	////QByteArray t = file.readAll();//全读取
	////按行读取
	//while (!file.atEnd())
	//{
	//	QByteArray line = file.readLine();
	//	QString str(line);
	//	if (str == "look")
	//	{
	//		QString str2(line);
	//		displayString.append(str2);
	//		break;
	//	}
	//}
	//file.close();
	//ui_textEdit->setText(QString(displayString));


	//QFile file("../QtGuiApplication2/Resources/aaa.txt");
	//file.open(QIODevice::ReadOnly | QIODevice::Text);
	//QString displayString;

	////QByteArray t = file.readAll();//全读取
	////按行读取
	//while (!file.atEnd())
	//{
	//	QByteArray line = file.readLine();
	//	QString str(line);
	//	displayString.append(str);
	//}

	//ui_textEdit->setText(QString(displayString));
	//file.close();

	//ui_textEdit->setText(ex_words);
}
