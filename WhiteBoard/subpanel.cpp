#include "subpanel.h"
#include "ui_subpanel.h"

SubPanel::SubPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubPanel)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

    Qt::WindowFlags m_flags = windowFlags();
    this->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);

    //设置背景图
    QPixmap bgImage("resource/bgi.png");
    QPalette palette = this->palette();
    palette.setBrush(this->backgroundRole(), QBrush(bgImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setPalette(palette);

    drawBoard.show();

    setPenStytle();
    setPenWidthRang();

    connect(ui->colorBt, SIGNAL(clicked(bool)), this, SLOT(setPenColor()));
    connect(ui->lineBt, SIGNAL(clicked(bool)), this, SLOT(setLineShape()));
    connect(ui->rectBt, SIGNAL(clicked(bool)), this, SLOT(setRectShape()));
    connect(ui->circleBt, SIGNAL(clicked(bool)), this, SLOT(setCircleShape()));
    connect(ui->curveLineBt, SIGNAL(clicked(bool)), this, SLOT(setCurveLineShape()));
    connect(ui->triangleBt, SIGNAL(clicked(bool)), this, SLOT(setTriangleShape()));
    connect(ui->diamondBt, SIGNAL(clicked(bool)), this, SLOT(setDiamondShape()));
    connect(ui->trapeziaBt, SIGNAL(clicked(bool)), this, SLOT(setTrapeziaShape()));
    connect(ui->parallelBt, SIGNAL(clicked(bool)), this, SLOT(setParallelogramShape()));

    connect(ui->fillBox, SIGNAL(stateChanged(int)), this, SLOT(setIfFill()));
    connect(ui->dashBox, SIGNAL(stateChanged(int)), this, SLOT(setPenStytle()));
    connect(ui->dotBox, SIGNAL(stateChanged(int)), this, SLOT(setPenStytle()));
    connect(ui->dashDotBox, SIGNAL(stateChanged(int)), this, SLOT(setPenStytle()));

    connect(ui->penWidth, SIGNAL(valueChanged(int)), this, SLOT(setPenWidth(int)));

    drawBoard.shape = DrawingBoard::Shape::NoShape;

    ui->colorBt->installEventFilter(this);

    style1 = "QPushButton{ \
            color: rgb(255, 255, 255); \
            border:4px groove rgb(255, 165, 0); \
            border-radius:16px; \
            font: 75 11pt 微软雅黑; \
                    }    \
        QPushButton:hover{ \
            color: rgb(0, 255, 255); \
            border:4px groove rgb(0, 255, 255); \
                    }  \
        QPushButton:pressed{ \
            color: rgb(255, 0, 0); \
            border:4px groove rgb(255, 0, 0); \
                    }";

    style2 = "QPushButton{ \
            color: rgb(0, 255, 0); \
            border:4px groove rgb(0, 255, 0); \
            border-radius:16px; \
            font: 75 11pt 微软雅黑; \
                    }    \
        QPushButton:hover{ \
            color: rgb(0, 255, 255); \
            border:4px groove rgb(0, 255, 255); \
                    }  \
        QPushButton:pressed{ \
            color: rgb(255, 0, 0); \
            border:4px groove rgb(255, 0, 0); \
                    }";
}

SubPanel::~SubPanel()
{
    delete ui;
}

//
bool SubPanel::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->colorBt)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            ui->colorBt->setToolTip("设置画笔颜色");
            ui->colorBt->resize(48, 48);
            ui->colorBt->setToolTip("设置画笔颜色");
            ui->colorBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/rgb48.png);");
        }
        if(event->type() == QEvent::Leave)
        {
            ui->colorBt->resize(32, 32);
            ui->colorBt->setStyleSheet("background-color: transparent; background-image: url(:/resource/rgb32.png);");
        }
    }

    return QWidget::eventFilter(obj, event);
}


//设置画笔颜色
void SubPanel::setPenColor()
{
    QColorDialog colorDialog;
    QColor color = colorDialog.getColor(Qt::red);
    drawBoard.pen.setColor(color);
}

//设置画笔粗细
void SubPanel::setPenWidth(int value)
{
    drawBoard.pen.setWidth(value);
    ui->label->setText(QString("%1").arg(value));
}

//设置画笔样式
void SubPanel::setPenStytle()
{
    if (ui->dashBox->isChecked())
    {
        drawBoard.pen.setStyle(Qt::DashLine);
        ui->dotBox->setEnabled(false);
        ui->dashDotBox->setEnabled(false);
    } else if (ui->dashDotBox->isChecked())
    {
        drawBoard.pen.setStyle(Qt::DashDotLine);
        ui->dashBox->setEnabled(false);
        ui->dotBox->setEnabled(false);
    } else if (ui->dotBox->isChecked())
    {
        drawBoard.pen.setStyle(Qt::DotLine);
        ui->dashBox->setEnabled(false);
        ui->dashDotBox->setEnabled(false);
    }
    else
    {
        drawBoard.pen.setStyle(Qt::SolidLine);
        ui->dotBox->setEnabled(true);
        ui->dashBox->setEnabled(true);
        ui->dashDotBox->setEnabled(true);
    }

    drawBoard.pen.setCapStyle(Qt::RoundCap);
    drawBoard.pen.setJoinStyle(Qt::RoundJoin);
}


//设置画直线
void SubPanel::setLineShape()
{
    drawBoard.shape = DrawingBoard::Shape::Line;

    ui->lineBt->setStyleSheet(style2);
    ui->curveLineBt->setStyleSheet(style1);
    ui->rectBt->setStyleSheet(style1);
    ui->circleBt->setStyleSheet(style1);
    ui->diamondBt->setStyleSheet(style1);
    ui->parallelBt->setStyleSheet(style1);
    ui->trapeziaBt->setStyleSheet(style1);
    ui->triangleBt->setStyleSheet(style1);
}

//设置画矩形
void SubPanel::setRectShape()
{
    drawBoard.shape = DrawingBoard::Shape::Rectangle;

    ui->lineBt->setStyleSheet(style1);
    ui->curveLineBt->setStyleSheet(style1);
    ui->rectBt->setStyleSheet(style2);
    ui->circleBt->setStyleSheet(style1);
    ui->diamondBt->setStyleSheet(style1);
    ui->parallelBt->setStyleSheet(style1);
    ui->trapeziaBt->setStyleSheet(style1);
    ui->triangleBt->setStyleSheet(style1);
}

//设置画任意线
void SubPanel::setCurveLineShape()
{
    drawBoard.shape = DrawingBoard::Shape::CurveLine;

    ui->lineBt->setStyleSheet(style1);
    ui->curveLineBt->setStyleSheet(style2);
    ui->rectBt->setStyleSheet(style1);
    ui->circleBt->setStyleSheet(style1);
    ui->diamondBt->setStyleSheet(style1);
    ui->parallelBt->setStyleSheet(style1);
    ui->trapeziaBt->setStyleSheet(style1);
    ui->triangleBt->setStyleSheet(style1);
}

//设置画圆
void SubPanel::setCircleShape()
{
    drawBoard.shape = DrawingBoard::Shape::Ellipse;

    ui->lineBt->setStyleSheet(style1);
    ui->curveLineBt->setStyleSheet(style1);
    ui->rectBt->setStyleSheet(style1);
    ui->circleBt->setStyleSheet(style2);
    ui->diamondBt->setStyleSheet(style1);
    ui->parallelBt->setStyleSheet(style1);
    ui->trapeziaBt->setStyleSheet(style1);
    ui->triangleBt->setStyleSheet(style1);
}

//设置画三角形
void SubPanel::setTriangleShape()
{
    drawBoard.shape = DrawingBoard::Shape::Triangle;

    ui->lineBt->setStyleSheet(style1);
    ui->curveLineBt->setStyleSheet(style1);
    ui->rectBt->setStyleSheet(style1);
    ui->circleBt->setStyleSheet(style1);
    ui->diamondBt->setStyleSheet(style1);
    ui->parallelBt->setStyleSheet(style1);
    ui->trapeziaBt->setStyleSheet(style1);
    ui->triangleBt->setStyleSheet(style2);
}

//设置画梯形
void SubPanel::setTrapeziaShape()
{
    drawBoard.shape = DrawingBoard::Shape::Trapezia;

    ui->lineBt->setStyleSheet(style1);
    ui->curveLineBt->setStyleSheet(style1);
    ui->rectBt->setStyleSheet(style1);
    ui->circleBt->setStyleSheet(style1);
    ui->diamondBt->setStyleSheet(style1);
    ui->parallelBt->setStyleSheet(style1);
    ui->trapeziaBt->setStyleSheet(style2);
    ui->triangleBt->setStyleSheet(style1);
}

//设置画菱形
void SubPanel::setDiamondShape()
{
    drawBoard.shape = DrawingBoard::Shape::Diamond;

    ui->lineBt->setStyleSheet(style1);
    ui->curveLineBt->setStyleSheet(style1);
    ui->rectBt->setStyleSheet(style1);
    ui->circleBt->setStyleSheet(style1);
    ui->diamondBt->setStyleSheet(style2);
    ui->parallelBt->setStyleSheet(style1);
    ui->trapeziaBt->setStyleSheet(style1);
    ui->triangleBt->setStyleSheet(style1);
}

//设置画平行四边形
void SubPanel::setParallelogramShape()
{
    drawBoard.shape = DrawingBoard::Shape::Parallelogram;

    ui->lineBt->setStyleSheet(style1);
    ui->curveLineBt->setStyleSheet(style1);
    ui->rectBt->setStyleSheet(style1);
    ui->circleBt->setStyleSheet(style1);
    ui->diamondBt->setStyleSheet(style1);
    ui->parallelBt->setStyleSheet(style2);
    ui->trapeziaBt->setStyleSheet(style1);
    ui->triangleBt->setStyleSheet(style1);
}

//设置画笔的最大最小宽度
void SubPanel::setPenWidthRang()
{
    ui->penWidth->setMaximum(1);
    ui->penWidth->setMaximum(30);
    ui->penWidth->setValue(1);
    ui->label->setText("1");
}

//设置是否填充
void SubPanel::setIfFill()
{
    if (ui->fillBox->isChecked())
    {
        drawBoard.m_ifFill = true;
    }
    else
    {
        drawBoard.m_ifFill = false;
    }
}

//鼠标移动
void SubPanel::mouseMoveEvent(QMouseEvent *e)
{
    move(e->globalPos());
}
