#include "controlpanel.h"
#include "ui_controlpanel.h"

ControlPanel::ControlPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground, true); //窗口透明控件不透明

    Qt::WindowFlags m_flags = windowFlags();
    this->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    this->move(QApplication::desktop()->width() / 2 - this->width() / 2,
               QApplication::desktop()->height() - 300);

    connect(ui->throughBt, SIGNAL(clicked(bool)), this, SLOT(setIfThrough()));
    connect(ui->closeBt, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));
    connect(ui->drawBt, SIGNAL(clicked(bool)), this, SLOT(showSubPanel()));
    connect(ui->cleanBt, SIGNAL(clicked(bool)), this, SLOT(cleanScreen()));
    connect(ui->withdrawBt, SIGNAL(clicked(bool)), this, SLOT(withdrawOperation()));

    m_ifThrough = false;
    m_ifSubPanelShow = false;

    initButtonStytle();
    buttonInstallFilter();
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

//
void ControlPanel::initButtonStytle()
{
    ui->throughBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/lock48.png);");
    ui->drawBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/draw48.png);");
    ui->withdrawBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/leftArrow48.png);");
    ui->cleanBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/clean48.png);");
    ui->closeBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/close48.png);");
}


//安装事件过滤器
void ControlPanel::buttonInstallFilter()
{
    ui->throughBt->installEventFilter(this);
    ui->drawBt->installEventFilter(this);
    ui->withdrawBt->installEventFilter(this);
    ui->cleanBt->installEventFilter(this);
    ui->closeBt->installEventFilter(this);
}


//事件过滤器
bool ControlPanel::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->throughBt)
    {
        if (!m_ifThrough)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                ui->throughBt->resize(64, 64);
                ui->throughBt->setToolTip("锁定画板/解锁");
                ui->throughBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/lock64.ico);");
            }
            if(event->type() == QEvent::Leave)
            {
                ui->throughBt->resize(48, 48);
                ui->throughBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/lock48.png);");
            }
        }
        else
        {
            if(event->type() == QEvent::HoverEnter)
            {
                ui->throughBt->resize(64, 64);
                ui->throughBt->setToolTip("锁定画板/解锁");
                ui->throughBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/unlock64.ico);");
            }
            if(event->type() == QEvent::Leave)
            {
                ui->throughBt->resize(48, 48);
                ui->throughBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/unlock48.png);");
            }
        }
    }

    if(obj == ui->drawBt)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            ui->drawBt->resize(64, 64);
            ui->drawBt->setToolTip("设置画笔");
            ui->drawBt->setStyleSheet("background-color: transparent; \
                                      background-image: url(:/resource/draw64.ico);");
        }
        if(event->type() == QEvent::Leave)
        {
            ui->drawBt->resize(48, 48);
            ui->drawBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/draw48.png);");
        }
    }

    if(obj == ui->withdrawBt)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            ui->withdrawBt->resize(64, 64);
            ui->withdrawBt->setToolTip("撤回");
            ui->withdrawBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/leftArrow64.ico);");
        }
        if(event->type() == QEvent::Leave)
        {
            ui->withdrawBt->resize(48, 48);
            ui->withdrawBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/leftArrow48.png);");
        }
    }

    if(obj == ui->cleanBt)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            ui->cleanBt->resize(64, 64);
            ui->cleanBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/clean64.ico);");
        }
        if(event->type() == QEvent::Leave)
        {
            ui->cleanBt->resize(48, 48);
            ui->cleanBt->setToolTip("清屏");
            ui->cleanBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/clean48.png);");
        }
    }

    if(obj == ui->closeBt)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            ui->closeBt->resize(64, 64);
            ui->closeBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/close64.ico);");
        }
        if(event->type() == QEvent::Leave)
        {
            ui->closeBt->resize(48, 48);
            ui->closeBt->setToolTip("关闭");
            ui->closeBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/close48.png);");
        }
    }

    return QMainWindow::eventFilter(obj, event);
}

//设置画板穿透
void ControlPanel::setIfThrough()
{
    if (!m_ifThrough)
    {
        m_ifThrough = true;
        subPanel.drawBoard.setThrough();
        ui->throughBt->setStyleSheet("background-color: transparent; \
                                     background-image: url(:/resource/unlock64.ico);");
    }
    else
    {
        m_ifThrough = false;
        subPanel.drawBoard.setNoThrough();
        ui->throughBt->setStyleSheet("background-color: transparent; \
                                     background-image: url(:/resource/lock64.ico)");
    }
}


//关闭控制窗口
void ControlPanel::closeWindow()
{
    subPanel.drawBoard.closeWindow();
    subPanel.close();
    this->close();
}

//显示子控制窗口
void ControlPanel::showSubPanel()
{
    if (!m_ifSubPanelShow)
    {
        QPropertyAnimation *animation1 = new QPropertyAnimation(&subPanel, "windowOpacity");
        animation1->setDuration(1000);
        animation1->setStartValue(0);
        animation1->setEndValue(0.9);
        animation1->start();

        QPropertyAnimation *animation = new QPropertyAnimation(&subPanel, "geometry");
        animation->setDuration(1000);
        animation->setStartValue(QRect(QApplication::desktop()->width() / 2 - subPanel.width() / 2, -subPanel.height(),
                                       subPanel.width(), subPanel.height()));
        animation->setEndValue(QRect(QApplication::desktop()->width() / 2 - subPanel.width() / 2,
                                     1, subPanel.width(), subPanel.height()));
        animation->start();
        subPanel.show();
        m_ifSubPanelShow = true;
    }
    else
    {
        QPropertyAnimation *animation1 = new QPropertyAnimation(&subPanel, "windowOpacity");
        animation1->setDuration(1000);
        animation1->setStartValue(0.9);
        animation1->setEndValue(0);
        animation1->start();

        QPropertyAnimation *animation = new QPropertyAnimation(&subPanel, "geometry");
        animation->setDuration(1000);
        animation->setStartValue(QRect(QApplication::desktop()->width() / 2 - subPanel.width() / 2,
                                     1, subPanel.width(), subPanel.height()));
        animation->setEndValue(QRect(QApplication::desktop()->width() / 2 - subPanel.width() / 2, -subPanel.height(),
                                       subPanel.width(), subPanel.height()));
        animation->start();
        //subPanel.hide();
        m_ifSubPanelShow = false;
    }
}

//清屏
void ControlPanel::cleanScreen()
{
    subPanel.drawBoard.cleanScreen();
}

//撤回
void ControlPanel::withdrawOperation()
{
    subPanel.drawBoard.withdraw();
}

/***************************** 鼠标事件 *****************************/
//鼠标移动
void ControlPanel::mouseMoveEvent(QMouseEvent *e)
{
    move(e->globalPos());
}

