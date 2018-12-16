#include "webTabWidget.h"

webTabWidget::webTabWidget(QWidget* parent):QTabWidget(parent)
{
    initTabWidget();
    setTabsClosable(true);

    _addTabButton();
    setProfile();
    //����ͷ��ǩ�ĳߴ�
    setStyleSheet("QTabBar::tab{width:180px;height:30px}");//��ʽ��
}

void webTabWidget::initTabWidget()
{
    connect(this, &QTabWidget::tabCloseRequested, [this](int index) {
        removeTab(index);
        delete m_webview[index];
        m_webview.remove(index);
        emit loadpressnum(100);
        if (m_webview.size() == 0) {
            emit CloseSingal();  //if no one webview,emit a close signal to mainwindow to close;
        }
    });
    connect(this, &QTabWidget::tabBarClicked, [this](int index) {
        this->sentCurrentUrl(index);
    });

}
WebView* webTabWidget::createTabWebView()
{
    WebView* webview = new WebView();
    if (webview != NULL)
    {
        addTab(webview,"New Tab");
        setCurrentWidget(webview);

        m_webview.push_back(webview);
        setup_webview(webview);
    }
    return webview;
}

bool webTabWidget::setup_webview(WebView* webview)
{
    bool ret = true;
    webview->setWindowPoint(this);   //��tabwidget��ָ�봫����ǰwebview�ڴ��еı���
    connect(webview, &QWebEngineView::loadProgress, [this,webview](int progress) {
        emit loadpressnum(progress);
        int index = m_webview.indexOf(webview);
        if(currentIndex() == index)		//��������ҳ�Ĺ����У����tabwidget��ǰҳ����������ҳ�±겻һ�£��򲻷��������������ҳ��ַ
            this->sentCurrentUrl(index);
    });
    connect(webview, &QWebEngineView::iconChanged, [this, webview](const QIcon) {
        int index = m_webview.indexOf(webview);
        setTabIcon(index, webview->page()->icon());	//set currentWidgetTab webview icon����page()����Ϊ��ǰҳ�����ҳ��
    });
    connect(webview, &QWebEngineView::loadFinished, [this,webview](bool ok){
        if (ok) {
        int index = m_webview.indexOf(webview);//���ڵ�webview���������ĸ�λ�ã���Ӧ���±�
        setTabText(index, webview->page()->title());//set currentWidgetTab webview title
        //test(webview->page());//������
        }
    });
    connect(webview, &QWebEngineView::loadStarted, [this]() {
        emit startload();
    });
    connect(webview, &QWebEngineView::titleChanged, [this, webview](const QString&) {
        emit send_Title_url(webview->page()->history()->currentItem().title()
            , webview->page()->history()->currentItem().url());
    });
    setWebPage(webview);			//������ҳ�������ļ���cookie��,��ʾ��ʼ��ҳ���
    return ret;
}
WebView* webTabWidget::current_widget()
{
    return m_webview[currentIndex()];
}

void webTabWidget::_addTabButton()
{
    QPushButton* tb = new QPushButton();
    tb->setText("+");
    setCornerWidget(tb);   //��tabwidget�����Ͻ�����QPushButton
    connect(tb, &QAbstractButton::clicked, [this](bool) {
        createTabWebView();
    });   //�������µ�ʱ�����һ����web��ǩҳ
}

bool webTabWidget::setProfile()
{
    bool ret = true;
    this->m_profile = QWebEngineProfile::defaultProfile();
    if (m_profile != NULL)
    {   //Ĭ��cookieΪ��ʱ�Ự�����ݴ洢
        m_profile->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
        //����cookie���ļ��Ĵ��·��
        //m_profile->setPersistentStoragePath("C:\\Qt\\QT_file\\VS_Qt\\My_browser\\profile");
        //ʹ���ڴ滺���������洢���������ҳ��Ϣ��Ĭ���������Ӳ�̴洢��һֱ�������������ǲ��Դ��룬������ڴ滺�漴��
        m_profile->setHttpCacheType(QWebEngineProfile::MemoryHttpCache);
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool webTabWidget::setWebPage(WebView* webview)
{
    bool ret = true;
    QWebEnginePage* page = new QWebEnginePage(m_profile,webview);
    if (page != NULL)
    {
        webview->setPage(page);
        //	qrc:// + url����Ҫд�����ָ�ʽ��������Ϊ��ַ��ʽ��ʶ��
        //������Ϊ��ʼ��������Դ���ҳ
        //webview->page()->load(QUrl("qrc:///My_browser/HTML/Html.html"));
        //webview->page()->load(QUrl::fromLocalFile("C:\\Qt\\QT_file\\VS_Qt\\My_browser\\My_browser\\Html.html"));//fromlocfile()�������ļ�·��ת��ΪQURL��
        webview->page()->load(QUrl("qrc:///My_browser/Html.html"));
    }
    else
    {
        ret = false;
    }
    return ret;
}

void webTabWidget::clearCookie(bool)
{
    //������е�cookie��¼
    m_profile->cookieStore()->deleteAllCookies();
    //�����������е���ʷ��¼
    //m_profile->clearAllVisitedLinks();
}
void webTabWidget::sentCurrentUrl(int index)
{
    QString s = m_webview[index]->url().toString();
    if (!s.startsWith("file://"))
    {
        emit currentUrl(m_webview[index]->url());
    }
    else     //ÿ�л�һ��ҳ�棬�Ͱ���ַ���е���ַ����Ϊ��ǰҳ�����ַ,�������վ��ַ������ַ���Ǳ��ص��ļ���ַ����Ϊ��
    {
        emit currentUrl(QUrl(""));
    }
}
void webTabWidget::test(QWebEnginePage* page)
{
    QWebChannel* channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("web"), this);
    page->setWebChannel(channel);
}
void webTabWidget::doSomething()
{
    tabBar()->insertTab(count(),"this from javascript");
}
webTabWidget::~webTabWidget()
{

}
