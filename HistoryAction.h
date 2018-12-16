#pragma once
#include <QAction>
#include <QString>
#include <QEvent>
#include <QUrl>

class HistoryAction :public QAction
{
	Q_OBJECT   //һ��Ҫ����
public:
	explicit HistoryAction(QWidget* parent = NULL);
	virtual ~HistoryAction();
signals:
	void SendUrl(const QString& s);
protected slots:
	void MousePress();
//protected:
//	bool event(QEvent *e);
};

