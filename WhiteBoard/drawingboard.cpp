#include "drawingboard.h"
#include "ui_drawingboard.h"

DrawingBoard::DrawingBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawingBoard)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_TranslucentBackground, true); //窗口透明控件不透明
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->setFixedSize(QApplication::desktop()->width(), QApplication::desktop()->height());

    initPoint();
    initShapeFlag();
}

//鼠标按下
void DrawingBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint screenPoint = QCursor::pos();    //获取鼠标在屏幕的绝对位置
        m_startX = screenPoint.x();
        m_startY = screenPoint.y();

        switch (shape)
        {
            case Line:           //直线
                {
                    m_isLine = true;
                    m_linePoint.startX = screenPoint.x();
                    m_linePoint.startY = screenPoint.y();                    
                }
                break;
            case CurveLine:      //任意直线
                {
                    m_isCurseLine = true;
                    m_curseLinePenColor = pen;
                    m_vCurseLinePenColor.push_back(m_curseLinePenColor);

                    QVector<QPoint> line;
                    m_vCurseLines.append(line);
                    QVector<QPoint> &lastLine = m_vCurseLines.last();
                    lastLine.append(screenPoint);
                }
                break;
            case Rectangle:      //矩形
                {
                    m_isRect = true;

                    m_rectPoint.startX = screenPoint.x();
                    m_rectPoint.startY = screenPoint.y();
                }
                break;
            case Ellipse:        //椭圆形
                {
                    m_isCircle = true;

                    m_circlePoint.centerX = screenPoint.x();
                    m_circlePoint.centerY = screenPoint.y();
                }
                break;
            case Triangle:       //三角形
                {
                    m_isTri = true;

                    m_triPoint.startX = screenPoint.x();
                    m_triPoint.startY = screenPoint.y();
                }
                break;
            case Parallelogram:  //平行四边形
                {
                    m_isPara = true;

                    m_paraPoint.startX = screenPoint.x();
                    m_paraPoint.startY = screenPoint.y();
                }
                break;
            case Trapezia:       //梯形
                {
                    m_isTra = true;

                    m_traPoint.startX = screenPoint.x();
                    m_traPoint.startY = screenPoint.y();
                }
                break;
            case Diamond:        //菱形
                {
                    m_isDia = true;

                    m_diaPoint.startX = screenPoint.x();
                    m_diaPoint.startY = screenPoint.y();
                }
                break;
            case Arc:            //弧
                //paintShape.drawArc(rect,startAngle,spanAngle);  //后面两个参数分别为 起始角与跨度角
                break;
            default:
            break;
        }
    }
}

//鼠标移动
void DrawingBoard::mouseMoveEvent(QMouseEvent *)
{
    QPoint screenPoint = QCursor::pos();//获取鼠标在屏幕的绝对位置

    m_endX = screenPoint.x();
    m_endY = screenPoint.y();

    if (m_isCurseLine)
    {
        if(!m_vCurseLines.size()) //保证安全
        {
            QVector<QPoint> line;
            m_vCurseLines.append(line);
        }
        QVector<QPoint> &lastLine = m_vCurseLines.last();
        lastLine.append(screenPoint);
    }
    update();

    m_ifMouseMove = true;
}

//鼠标释放
void DrawingBoard::mouseReleaseEvent(QMouseEvent *)
{
    QPoint screenPoint = QCursor::pos();    //获取鼠标在屏幕的绝对位置
    switch (shape)
    {
        case Line:              //直线
            {
                if (m_ifMouseMove)
                {
                    m_isLine = false;
                    m_linePoint.endX = screenPoint.x();
                    m_linePoint.endY = screenPoint.y();

                    m_linePenColor = pen;
                    m_vLinePenColor.push_back(m_linePenColor);
                    m_vLine.push_back(m_linePoint);

                    type.push(Line);
                    m_ifMouseMove = false;
                }
            }
            break;
        case CurveLine:         //任意线
            {
                m_isCurseLine = false;
                QVector<QPoint> &lastLine = m_vCurseLines.last();
                lastLine.append(screenPoint);

                type.push(CurveLine);
                m_ifMouseMove = false;
            }
            break;
        case Rectangle:         //长方形
            {               
                if (m_ifMouseMove)
                {
                    m_isRect = false;
                    m_rectPenColor = pen;
                    m_vRectPenColor.push_back(m_rectPenColor);

                    m_rectPoint.width = screenPoint.x() - m_rectPoint.startX;
                    m_rectPoint.height = screenPoint.y() - m_rectPoint.startY;
                    m_rectPoint.ifFill = m_ifFill;
                    m_vRect.push_back(m_rectPoint);

                    type.push(Rectangle);

                    m_ifMouseMove = false;
                }
            }
            break;
        case Ellipse:           //椭圆形
            {
                if (m_ifMouseMove)
                {
                    m_isCircle = false;

                    m_circlePenColor = pen;
                    m_vCirclePenColor.push_back(m_circlePenColor);

                    m_circlePoint.width = screenPoint.x() - m_circlePoint.centerX;
                    m_circlePoint.height = screenPoint.y() - m_circlePoint.centerY;
                    m_circlePoint.ifFill = m_ifFill;
                    m_vCircle.push_back(m_circlePoint);

                    type.push(Ellipse);

                    m_ifMouseMove = false;
                }
            }
            break;
        case Triangle:          //三角形
            {
                if (m_ifMouseMove)
                {
                    m_isTri = false;
                    m_triPenColor = pen;
                    m_vTriPenColor.push_back(m_triPenColor);

                    m_triPoint.endX = screenPoint.x();
                    m_triPoint.endY = screenPoint.y();
                    m_triPoint.ifFill = m_ifFill;
                    m_vTriangle.push_back(m_triPoint);

                    type.push(Triangle);

                    m_ifMouseMove = false;
                }
            }
            break;
        case Parallelogram:     //平行四边形
            {
                if (m_ifMouseMove)
                {
                    m_isPara = false;
                    m_paraPenColor = pen;
                    m_vParaPenColor.push_back(m_paraPenColor);

                    m_paraPoint.endX = screenPoint.x();
                    m_paraPoint.endY = screenPoint.y();
                    m_paraPoint.ifFill = m_ifFill;
                    m_vParallel.push_back(m_paraPoint);

                    type.push(Parallelogram);

                    m_ifMouseMove = false;
                }
            }
            break;
        case Trapezia:          //梯形
            {
                if (m_ifMouseMove)
                {
                    m_isTra = false;
                    m_traPenColor = pen;
                    m_vTraPenColor.push_back(m_traPenColor);

                    m_traPoint.endX = screenPoint.x();
                    m_traPoint.endY = screenPoint.y();
                    m_traPoint.ifFill = m_ifFill;
                    m_vTrapezia.push_back(m_traPoint);

                    type.push(Trapezia);

                    m_ifMouseMove = false;
                }
            }
            break;
        case Diamond:           //菱形
            {
                if (m_ifMouseMove)
                {
                    m_isDia = false;
                    m_diaPenColor = pen;
                    m_vDiaPenColor.push_back(m_diaPenColor);

                    m_diaPoint.endX = screenPoint.x();
                    m_diaPoint.endY = screenPoint.y();
                    m_diaPoint.ifFill = m_ifFill;
                    m_vDiamond.push_back(m_diaPoint);

                    type.push(Diamond);

                    m_ifMouseMove = false;
                }
            }
            break;
        case Arc:               //弧
            //paintShape.drawArc(rect,startAngle,spanAngle);  //后面两个参数分别为 起始角与跨度角
            break;
        default:
        break;
    }

    m_isPara = false;
    m_isDia = false;
    m_isTra = false;
    m_isTri = false;
    m_isLine = false;
    m_isRect = false;
    m_isCircle = false;
    m_isCurseLine = false;

    update();
}

//绘图
void DrawingBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(255, 255, 255, 1));

    QPainter paintShape(this);
    paintShape.setRenderHints(QPainter::Antialiasing, true); //
    paintShape.setPen(pen);

    brush.setStyle(Qt::SolidPattern);

    //鼠标移动画直线
    if (m_isLine && m_endX != 0)
    {
        paintShape.drawLine(m_startX, m_startY, m_endX, m_endY);
        m_endX = 0;
        m_endY = 0;
    }

    //鼠标移动画任意线
    if (m_isCurseLine)
    {
        for(int i = 0; i < m_vCurseLines.size(); ++i)
        {
            QPen tempPen = m_vCurseLinePenColor.at(i);
            paintShape.setPen(tempPen);
            const QVector<QPoint>& line = m_vCurseLines.at(i);
            for(int j = 0; j < line.size() - 1; ++j)
            {
                paintShape.drawLine(line.at(j), line.at(j+1));
            }

//            if (line.size() == 1)
//            {
//                paintShape.drawPoint(line.at(0));
//            }
//            else
//            {
//                for(int j = 0; j < line.size() - 1; ++j)
//                {
//                        paintShape.drawPoint(line.at(j));
//                        paintShape.drawLine(line.at(j), line.at(j+1));
//                        paintShape.drawPoint(line.at(j+1));
//                }
//            }
        }

        m_endX = 0;
        m_endY = 0;
    }

    //鼠标移动画矩形
    if (m_isRect && m_endX != 0)
    {
        paintShape.drawRect(m_startX, m_startY, m_endX - m_startX, m_endY - m_startY);
        m_endX = 0;
        m_endY = 0;
    }

    //鼠标移动画圆
    if (m_isCircle && m_endX != 0)
    {
        paintShape.drawEllipse(m_startX, m_startY, m_endX - m_startX, m_endY - m_startY);
        m_endX = 0;
        m_endY = 0;
    }

    //鼠标移动画三角形
    if (m_isTri && m_endX != 0)
    {
        paintShape.drawLine(m_startX, m_startY, m_endX, m_endY);
        if (m_startX < m_endX)
        {
            paintShape.drawLine(m_endX, m_endY,  m_endX - 2 * (m_endX - m_startX), m_endY);
            paintShape.drawLine(m_endX - 2 * (m_endX - m_startX), m_endY, m_startX, m_startY);
        }
        else
        {
            paintShape.drawLine(m_endX, m_endY,  abs(m_endX - abs(m_endY - m_startY)), m_endY);
            paintShape.drawLine(abs(m_endX - abs(m_endY - m_startY)), m_endY, m_startX, m_startY);
        }

        m_endX = 0;
        m_endY = 0;
    }

    //鼠标移动画平行四边形
    if (m_isPara && m_endX != 0)
    {
        if (m_startX < m_endX)
        {
            QPainterPath path;
            path.moveTo(m_startX, m_startY);
            path.lineTo(m_startX, m_startY);
            path.lineTo(m_endX - 50, m_startY);
            path.lineTo(m_endX, m_endY);
            path.lineTo(m_startX + 50, m_endY);
            path.lineTo(m_startX, m_startY);
            paintShape.drawPath(path);
        }
        else
        {
            QPainterPath path;
            path.moveTo(m_startX, m_startY);
            path.lineTo(m_startX, m_startY);
            path.lineTo(m_endX + 50, m_startY);
            path.lineTo(m_endX, m_endY);
            path.lineTo(m_startX - 50, m_endY);
            path.lineTo(m_startX, m_startY);
            paintShape.drawPath(path);
        }

        m_endX = 0;
        m_endY = 0;
    }

    //鼠标移动画梯形
    if (m_isTra && m_endX != 0)
    {
        QPainterPath path;
        path.moveTo(m_startX, m_startY);
        path.lineTo(m_startX, m_startY);
        path.lineTo(m_endX - 70, m_startY);
        path.lineTo(m_endX, m_endY);
        path.lineTo(m_startX - 70, m_endY);
        path.lineTo(m_startX, m_startY);
        paintShape.drawPath(path);

        m_endX = 0;
        m_endY = 0;
    }

    //鼠标移动画菱形
    if (m_isDia && m_endX != 0)
    {
        QPainterPath path;
        path.moveTo(m_startX, m_startY);
        path.lineTo(m_startX, m_startY);
        path.lineTo(m_startX + 180, abs(m_startY + m_endY) / 2);
        path.lineTo(m_startX, m_endY);
        path.lineTo(m_startX - 180, abs(m_startY + m_endY) / 2);
        path.lineTo(m_startX, m_startY);
        paintShape.drawPath(path);

        m_endX = 0;
        m_endY = 0;
    }

    /******************** 绘制直线 ********************/
    for (unsigned int i = 0; i < m_vLine.size(); i++)
    {
        QPen tempPen = m_vLinePenColor.at(i);
        paintShape.setPen(tempPen);
        LinePoint p = m_vLine.at(i);
        paintShape.drawLine(p.startX, p.startY, p.endX, p.endY);
    }

    /****************** 绘制任意线条 ********************/
    for(int i = 0; i < m_vCurseLines.size(); ++i)
    {
        QPen tempPen = m_vCurseLinePenColor.at(i);
        paintShape.setPen(tempPen);
        const QVector<QPoint>& line = m_vCurseLines.at(i);

        if (line.size() == 1)
        {
            paintShape.drawPoint(line.at(0));
        }
        else
        {
            for(int j = 0; j < line.size() - 1; ++j)
            {
                    paintShape.drawPoint(line.at(j));
                    paintShape.drawLine(line.at(j), line.at(j+1));
                    paintShape.drawPoint(line.at(j+1));
            }
        }
    }

    /***************** 绘制矩形 ***********************/
    for (unsigned int i = 0; i < m_vRect.size(); i++)
    {
        QPen tempPen = m_vRectPenColor.at(i);
        paintShape.setPen(tempPen);
        RectPoint p = m_vRect.at(i);
        if (p.ifFill)
        {
            brush.setColor(tempPen.color());
            paintShape.setBrush(brush);
            paintShape.drawRect(p.startX, p.startY, p.width, p.height);
        }
        else
        {
            paintShape.setBrush(Qt::NoBrush);
            paintShape.drawRect(p.startX, p.startY, p.width, p.height);
        }
    }

    /****************** 绘制圆 ********************/
    for (unsigned int i = 0; i < m_vCircle.size(); i++)
    {
        QPen tempPen = m_vCirclePenColor.at(i);
        paintShape.setPen(tempPen);
        CirclePoint p = m_vCircle.at(i);
        if (p.ifFill)
        {
            brush.setColor(tempPen.color());
            paintShape.setBrush(brush);
            paintShape.drawEllipse(p.centerX, p.centerY, p.width, p.height);
        }
        else
        {
            paintShape.setBrush(Qt::NoBrush);
            paintShape.drawEllipse(p.centerX, p.centerY, p.width, p.height);
        }

    }

    /***************** 绘制三角形 ***********************/
    for (unsigned int i = 0; i < m_vTriangle.size(); i++)
    {
        QPen tempPen = m_vTriPenColor.at(i);
        paintShape.setPen(tempPen);
        TrianglePoint p = m_vTriangle.at(i);
        if (p.ifFill)
        {
            brush.setColor(tempPen.color());

            if (p.startX < p.endX)
            {
                QPainterPath path;
                path.lineTo(p.startX, p.startY);
                path.lineTo(p.endX, p.endY);
                path.lineTo(p.endX -2*(p.endX - p.startX), p.endY);
                path.lineTo(p.startX, p.startY);

                paintShape.fillPath(path, brush);
            }
            else
            {
                QPainterPath path;
                path.lineTo(p.startX, p.startY);
                path.lineTo(p.endX, p.endY);
                path.lineTo(abs(p.endX - abs(p.endY - p.startY)), p.endY);
                path.lineTo(p.startX, p.startY);

                paintShape.fillPath(path, brush);
            }
        }
        else
        {
            paintShape.setBrush(Qt::NoBrush);

            paintShape.drawLine(p.startX, p.startY, p.endX, p.endY);
            if (p.startX < p.endX)
            {
                paintShape.drawLine(p.endX, p.endY,  p.endX - 2 * (p.endX - p.startX), p.endY);
                paintShape.drawLine(p.endX - 2 * (p.endX - p.startX), p.endY, p.startX, p.startY);
            }
            else
            {
                paintShape.drawLine(p.endX, p.endY,  abs(p.endX - abs(p.endY - p.startY)), p.endY);
                paintShape.drawLine(abs(p.endX - abs(p.endY - p.startY)), p.endY, p.startX, p.startY);
            }
        }
    }

    /***************** 绘制平行四边形 ***********************/
    for (unsigned int i = 0; i < m_vParallel.size(); i++)
    {
        QPen tempPen = m_vParaPenColor.at(i);
        paintShape.setPen(tempPen);
        ParallelPoint p = m_vParallel.at(i);
        if (p.ifFill)
        {
            brush.setColor(tempPen.color());

            if (p.startX < p.endX)
            {
                QPainterPath path;
                path.moveTo(p.startX, p.startY);
                path.lineTo(p.startX, p.startY);
                path.lineTo(p.endX - 50, p.startY);
                path.lineTo(p.endX, p.endY);
                path.lineTo(p.startX + 50, p.endY);
                path.lineTo(p.startX, p.startY);

                paintShape.fillPath(path, brush);
            }
            else
            {
                QPainterPath path;
                path.moveTo(p.startX, p.startY);
                path.lineTo(p.startX, p.startY);
                path.lineTo(p.endX + 50, p.startY);
                path.lineTo(p.endX, p.endY);
                path.lineTo(p.startX - 50, p.endY);
                path.lineTo(p.startX, p.startY);

                paintShape.fillPath(path, brush);
            }
        }
        else
        {
            paintShape.setBrush(Qt::NoBrush);

            if (p.startX < p.endX)
            {
                QPainterPath path;
                path.moveTo(p.startX, p.startY);
                path.lineTo(p.startX, p.startY);
                path.lineTo(p.endX - 50, p.startY);
                path.lineTo(p.endX, p.endY);
                path.lineTo(p.startX + 50, p.endY);
                path.lineTo(p.startX, p.startY);
                paintShape.drawPath(path);
            }
            else
            {
                QPainterPath path;
                path.moveTo(p.startX, p.startY);
                path.lineTo(p.startX, p.startY);
                path.lineTo(p.endX + 50, p.startY);
                path.lineTo(p.endX, p.endY);
                path.lineTo(p.startX - 50, p.endY);
                path.lineTo(p.startX, p.startY);
                paintShape.drawPath(path);
            }
        }
    }

    /***************** 绘制梯形 ***********************/
    for (unsigned int i = 0; i < m_vTrapezia.size(); i++)
    {
        QPen tempPen = m_vTraPenColor.at(i);
        paintShape.setPen(tempPen);
        TrapeziaPoint p = m_vTrapezia.at(i);
        if (p.ifFill)
        {
            brush.setColor(tempPen.color());

            QPainterPath path;
            path.moveTo(p.startX, p.startY);
            path.lineTo(p.startX, p.startY);
            path.lineTo(p.endX - 70, p.startY);
            path.lineTo(p.endX, p.endY);
            path.lineTo(p.startX - 70, p.endY);
            path.lineTo(p.startX, p.startY);
            paintShape.drawPath(path);

            paintShape.fillPath(path, brush);
        }
        else
        {
            paintShape.setBrush(Qt::NoBrush);

            QPainterPath path;
            path.moveTo(p.startX, p.startY);
            path.lineTo(p.startX, p.startY);
            path.lineTo(p.endX - 70, p.startY);
            path.lineTo(p.endX, p.endY);
            path.lineTo(p.startX - 70, p.endY);
            path.lineTo(p.startX, p.startY);
            paintShape.drawPath(path);
        }
    }

    /***************** 绘制菱形 ***********************/
    for (unsigned int i = 0; i < m_vDiamond.size(); i++)
    {
        QPen tempPen = m_vDiaPenColor.at(i);
        paintShape.setPen(tempPen);
        DiamondPoint p = m_vDiamond.at(i);
        if (p.ifFill)
        {
            brush.setColor(tempPen.color());

            QPainterPath path;
            path.moveTo(p.startX, p.startY);
            path.lineTo(p.startX, p.startY);
            path.lineTo(p.startX + 180, abs(p.startY + p.endY) / 2);
            path.lineTo(p.startX, p.endY);
            path.lineTo(p.startX - 180, abs(p.startY + p.endY) / 2);
            path.lineTo(p.startX, p.startY);
            paintShape.drawPath(path);

            paintShape.fillPath(path, brush);
        }
        else
        {
            paintShape.setBrush(Qt::NoBrush);

            QPainterPath path;
            path.moveTo(p.startX, p.startY);
            path.lineTo(p.startX, p.startY);
            path.lineTo(p.startX + 180, abs(p.startY + p.endY) / 2);
            path.lineTo(p.startX, p.endY);
            path.lineTo(p.startX - 180, abs(p.startY + p.endY) / 2);
            path.lineTo(p.startX, p.startY);
            paintShape.drawPath(path);
        }
    }
}

DrawingBoard::~DrawingBoard()
{
    delete ui;
}

//
void DrawingBoard::initPoint()
{
    m_startX = 0;
    m_startY = 0;
    m_endX = 0;
    m_endY = 0;
}


// 设置窗口鼠标穿透
void DrawingBoard::setThrough()
{
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //SetWindowPos(HWND(this->winId()), HWND_TOPMOST , 0, 0, 0, 0, SWP_SHOWWINDOW);

    Qt::WindowFlags m_flags = windowFlags();
    this->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    this->show();
}

// 设置窗口鼠标不穿透
void DrawingBoard::setNoThrough()
{
    this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->show();
}

//关闭窗口
void DrawingBoard::closeWindow()
{
    this->close();
}

//
void DrawingBoard::initShapeFlag()
{
    m_isPara = false;
    m_isDia = false;
    m_isTra = false;
    m_isTri = false;
    m_isLine = false;
    m_isRect = false;
    m_ifFill = false;
    m_isCircle = false;
    m_isCurseLine = false;
}

//清屏
void DrawingBoard::cleanScreen()
{
    vector<QPen>().swap(m_vLinePenColor);
    vector<LinePoint>().swap(m_vLine);

    vector<QPen>().swap(m_vCurseLinePenColor);
    QVector<QVector<QPoint> >().swap(m_vCurseLines);

    vector<QPen>().swap(m_vRectPenColor);
    vector<RectPoint>().swap(m_vRect);

    vector<QPen>().swap(m_vCirclePenColor);
    vector<CirclePoint>().swap(m_vCircle);

    vector<QPen>().swap(m_vTriPenColor);
    vector<TrianglePoint>().swap(m_vTriangle);

    vector<QPen>().swap(m_vParaPenColor);
    vector<ParallelPoint>().swap(m_vParallel);

    vector<QPen>().swap(m_vDiaPenColor);
    vector<DiamondPoint>().swap(m_vDiamond);

    vector<QPen>().swap(m_vTraPenColor);
    vector<TrapeziaPoint>().swap(m_vTrapezia);

    QStack<Shape>().swap(type);
    update();
}

//撤回
void DrawingBoard::withdraw()
{
    if (!type.empty())
    {
        Shape sp = type.top();

        switch (sp)
        {
            case Line:              //直线
                {
                    if (m_vLine.size() > 0)
                    {
                        m_vLinePenColor.pop_back();
                        m_vLine.pop_back();
                        type.pop_back();
                        update();
                    }
                }
                break;
            case CurveLine:         //任意线
                {
                    if (m_vCurseLines.size() > 0)
                    {
                        m_vCurseLinePenColor.pop_back();
                        m_vCurseLines.pop_back();
                        type.pop_back();
                        update();
                    }
                }
                break;
            case Rectangle:         //长方形
                {
                    if (m_vRect.size() > 0)
                    {
                        m_vRectPenColor.pop_back();
                        m_vRect.pop_back();
                        type.pop_back();
                        update();
                    }
                }
                break;
            case Ellipse:           //椭圆形
                {
                    if (m_vCircle.size() > 0)
                    {
                        m_vCirclePenColor.pop_back();
                        m_vCircle.pop_back();
                        type.pop_back();
                        update();
                    }
                }
                break;
            case Triangle:          //三角形
                {
                    if (m_vTriangle.size() > 0)
                    {
                        m_vTriPenColor.pop_back();
                        m_vTriangle.pop_back();
                        type.pop_back();
                        update();
                    }
                }
                break;
            case Parallelogram:     //平行四边形
                {
                    if (m_vParallel.size() >0)
                    {
                        m_vParaPenColor.pop_back();
                        m_vParallel.pop_back();
                        type.pop_back();
                        update();
                    }
                }
                break;
            case Trapezia:          //梯形
                {
                    if (m_vTrapezia.size() > 0)
                    {
                        m_vTraPenColor.pop_back();
                        m_vTrapezia.pop_back();
                        type.pop_back();
                        update();
                    }
                }
                break;
            case Diamond:           //菱形
                {
                    if (m_vDiamond.size() > 0)
                    {
                        m_vDiaPenColor.pop_back();
                        m_vDiamond.pop_back();
                        type.pop_back();
                        update();
                    }
                }
                break;
            default:
            break;
        }
    }
    else
        qDebug() << "Stack is empty!";
}


