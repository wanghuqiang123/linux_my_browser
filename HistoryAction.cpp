#include "HistoryAction.h"

HistoryAction::HistoryAction(QWidget* parent):QAction(parent)
{
	connect(this, SIGNAL(triggered(bool)), this, SLOT(MousePress()));
}

//bool HistoryAction::event(QEvent* e)
//{
//	if (e->type() == QEvent::MouseButtonPress)
//	{
//		emit SendUrl(text());
//	}
//
//	return QAction::event(e);//����ֱ�ӵ��ø����е�event().
//}

void HistoryAction::MousePress()
{
	emit SendUrl(text());
}

HistoryAction::~HistoryAction()
{

}
