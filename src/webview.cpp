/*573:*/
#line 52 "./webview.w"

#include "webview.h"

/*574:*/
#line 66 "./webview.w"

TypicaWebView::TypicaWebView():QWebView()
{
page()->setLinkDelegationPolicy(QWebPage::DelegateExternalLinks);
connect(page(),SIGNAL(linkClicked(QUrl)),this,SLOT(linkDelegate(QUrl)));

QDesktopWidget*desktop= QApplication::desktop();
const int dpi= desktop->logicalDpiX();
setZoomFactor((qreal)(dpi)/96.0);

settings()->setUserStyleSheetUrl(QUrl("qrc:/resources/css/default.css"));
}

/*:574*//*575:*/
#line 88 "./webview.w"

void TypicaWebView::linkDelegate(const QUrl&url)
{
if(url.scheme()=="typica")
{
QString address(url.toEncoded());
/*576:*/
#line 106 "./webview.w"

if(address=="typica://aboutqt")
{
QMessageBox::aboutQt(this);
return;
}

/*:576*/
#line 94 "./webview.w"

/*577:*/
#line 115 "./webview.w"

if(address.startsWith("typica://script/"))
{
emit scriptLinkClicked(address.remove(0,16));
return;
}

/*:577*/
#line 95 "./webview.w"

}
else
{
QDesktopServices::openUrl(url);
}
}

/*:575*//*578:*/
#line 127 "./webview.w"

void TypicaWebView::load(const QString&url)
{
QWebView::load(QUrl(url));
}

void TypicaWebView::setHtml(const QString&html,const QUrl&baseUrl)
{
QWebView::setHtml(html,baseUrl);
}

void TypicaWebView::setContent(QIODevice*device)
{
QSettings settings;
device->reset();
QByteArray content= device->readAll();
QUrl baseDir= QUrl("file://"+settings.value("config").toString()+"/");
QWebView::setContent(content,"application/xhtml+xml",baseDir);
}

QString TypicaWebView::saveXml()
{
return page()->currentFrame()->documentElement().toOuterXml();
}

/*:578*//*579:*/
#line 159 "./webview.w"

void TypicaWebView::print(const QString&printerName)
{
QPrinter*printer= new QPrinter(QPrinter::HighResolution);
if(!printerName.isEmpty())
{
printer->setPrinterName(printerName);
printer->setFullPage(true);
QWebView::print(printer);
return;
}
QPrintDialog printDialog(printer,NULL);
if(printDialog.exec()==QDialog::Accepted)
{
QWebView::print(printer);
}
}

/*:579*//*585:*/
#line 240 "./webview.w"

QWebElement TypicaWebView::documentElement()
{
return page()->mainFrame()->documentElement();
}

QWebElement TypicaWebView::findFirstElement(const QString&selector)
{
return page()->mainFrame()->findFirstElement(selector);
}

/*:585*/
#line 55 "./webview.w"


/*:573*/
