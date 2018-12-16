#include <mainwindow.h>

void My_browser::on_backButton_click()
{
	m_currenttab->current_widget()->back();
}

void My_browser::on_forwardButton_click()
{
	m_currenttab->current_widget()->forward();
}

void My_browser::on_refreshButton_click()
{
	m_currenttab->current_widget()->reload();
}

void My_browser::on_goButton_click()
{
	QString url = line->text();
	if (!url.startsWith("http://") && !url.startsWith("https://"))
	{
		url = "http://" + url;
	}
	m_currenttab->current_widget()->load(QUrl(url));//�ڵ�ǰҳ������
}

void My_browser::webviewLoding(int progress)
{
	if (progress >= 100)
	{
		PB->setVisible(false);
	}
	PB->setValue(progress);
}

/*void My_browser::webview_PagePrint()
{
	QPrintDialog dlg(this);    //������ӡ�Ի���
	dlg.setWindowTitle("Print");    //�Ի������

	if (dlg.exec() == QPrintDialog::Accepted)        //�ȴ������Ƿ� ѡ���Ǵ�ӡ
	{
		QPrinter* p = dlg.printer();               //��ȡ��ӡ������

		//���༭���е����ݴ�����ӡ����ӡ���ڶ������������õ���lambda�﷨����Ϊ��QWebEngine������Ҫһ���ص�����
		//m_currenttab->currrnt_widget()->page()->print(p, [=](bool ok) { });
	}
}*/
void My_browser::setlinetext(QUrl url)
{
    line->setText(url.toString());
}
void My_browser::recive_url_fromhistory(const QUrl& url)
{
	m_currenttab->createTabWebView();   //����һ���յı�ǩҳ
	m_currenttab->current_widget()->load(url);
}
void My_browser::webview_History(QString& s,QUrl& url)
{
	//�����ʷ��¼
	m_history->addHistoryAction(s,url);
}

void My_browser::browser_exit()
{
	close();
}
