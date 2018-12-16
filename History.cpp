#include "History.h"


History::History(QMenu* parent)
	:QMenu(parent)
{
	setTitle("History");
	makeClearAction();
}


void History::addHistoryAction(QString& s,QUrl& url)
{
	if ( (historys_data.find(s) == historys_data.end()) && (s != ""))
	{
		HistoryAction* action = makeHistoryAction(s);
		if (action != NULL)
		{
			addAction(action);
			connect(action,SIGNAL(SendUrl(const QString&)),this,SLOT(ReciveUrlFromAction(const QString&)));
			historys_data.insert(s, url);
		}
	}
}

HistoryAction* History::makeHistoryAction(QString& s)
{
	HistoryAction* action = new HistoryAction();
	action->setText(s);
	return action;
}

void History::ReciveUrlFromAction(const QString& s)
{
	QUrl& url = historys_data[s];
	emit SendToMainUrl(url);
}

void History::makeClearAction()
{
	QAction* action = addAction("Clear History");
	connect(action, SIGNAL(triggered(bool)), this, SLOT(ClearHisyory()));
}

void History::ClearHisyory()
{ //�˺����Ĺ����������ʷ��¼��
	clear();		//�����֮�е�actionm
	makeClearAction();  //ȫ��ɾ����ֻ����clearѡ��
	historys_data.clear();
}

History::~History()
{
	
}
