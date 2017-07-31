#ifndef SIMPLEEDITOR_H
#define SIMPLEEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_simpleeditor.h"

class SimpleEditor : public QMainWindow
{
	Q_OBJECT

public:
	SimpleEditor(QWidget *parent = 0);
	~SimpleEditor();

private:
	Ui::SimpleEditorClass ui;
};

#endif // SIMPLEEDITOR_H
