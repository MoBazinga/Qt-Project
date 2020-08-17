#ifndef DrawingBoard_H
#define DrawingBoard_H

#include <vector>
#include <QStack>
#include <QDir>
#include <QImage>
#include <QDebug>
#include <QTimer>
#include <QScreen>
#include <QPixmap>
#include <QPainter>
#include <QObject>
#include <QEvent>
#include <QVector>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDesktopWidget>

using namespace std;

//直线段的坐标
typedef struct LinePoint{
    int startX;
    int startY;
    int endX;
    int endY;
}LinePoint;

//矩形的坐标
typedef struct RectPoint{
    int startX;
    int startY;
    int width;
    int height;
    bool ifFill;
}RectPoint;


//圆的坐标
typedef struct CirclePoint{
    int centerX;
    int centerY;
    int width;
    int height;
    bool ifFill;
}CirclePoint;

//三角形的坐标
typedef struct TrianglePoint{
    int startX;
    int startY;
    int endX;
    int endY;
    bool ifFill;
}TrianglePoint;

//平行四边形的坐标
typedef struct ParallelPoint{
    int startX;
    int startY;
    int endX;
    int endY;
    bool ifFill;
}ParallelPoint;

//菱形的坐标
typedef struct DiamondPoint{
    int startX;
    int startY;
    int endX;
    int endY;
    bool ifFill;
}DiamondPoint;

//梯形的坐标
typedef struct TrapeziaPoint{
    int startX;
    int startY;
    int endX;
    int endY;
    bool ifFill;
}TrapeziaPoint;

namespace Ui {
class DrawingBoard;
}

class DrawingBoard : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingBoard(QWidget *parent = 0);
    ~DrawingBoard();

    enum Shape{NoShape, Line, CurveLine, Rectangle, Triangle, Ellipse,
               Parallelogram, Diamond, Trapezia, Arc
              };

    Shape shape;            //绘图形状
    QPen pen;               //画笔
    QBrush brush;           //画笔
    bool m_ifFill;          //标记是否对区域进行填充

    QStack<Shape> type;

    void initPoint();
    void initShapeFlag();
    void cleanScreen();     //清屏
    void withdraw();        //撤回

public slots:
    void setThrough();    //画板鼠标穿透
    void setNoThrough();  //画板鼠标不穿透
    void closeWindow();   //关闭画板

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    Ui::DrawingBoard *ui;

    int m_stackCount;
    bool m_ifMouseMove;

    /* 记录鼠标划过的位置 */
    int m_startX;
    int m_startY;
    int m_endX;
    int m_endY;

    //line
    bool m_isLine;                              //标记是否画直线
    QPen m_linePenColor;                        //画笔的颜色
    vector<QPen> m_vLinePenColor;               //存储画直线的画笔的颜色
    LinePoint m_linePoint;                      //直线的坐标点
    vector<LinePoint> m_vLine;                  //存储直线

    //curse line
    bool m_isCurseLine;                         //标记是否画任意直线
    QPen m_curseLinePenColor;                   //画笔的颜色
    vector<QPen> m_vCurseLinePenColor;          //存储画任意直线的画笔的颜色
    QVector<QVector<QPoint> > m_vCurseLines;    //存储任意直线

    //rectangle
    bool m_isRect;                              //标记是否画矩形
    QPen m_rectPenColor;                        //画笔的颜色
    vector<QPen> m_vRectPenColor;               //存储画矩形的画笔的颜色
    RectPoint m_rectPoint;                      //矩形的坐标及大小
    vector<RectPoint> m_vRect;                  //存储坐标点

    //circle
    bool m_isCircle;                            //标记是否画圆
    QPen m_circlePenColor;                      //画笔的颜色
    vector<QPen> m_vCirclePenColor;             //存储画矩形的画笔的颜色
    CirclePoint m_circlePoint;                  //圆的坐标及大小
    vector<CirclePoint> m_vCircle;              //存储坐标点

    //triangle
    bool m_isTri;                               //标记是否画三角形
    QPen m_triPenColor;                         //画笔的颜色
    vector<QPen> m_vTriPenColor;                //存储画三角形的画笔的颜色
    TrianglePoint m_triPoint;                   //三角形的坐标及大小
    vector<TrianglePoint> m_vTriangle;          //存储坐标点

    //paralleiogram
    bool m_isPara;                              //标记是否画平行四边形
    QPen m_paraPenColor;                        //画笔的颜色
    vector<QPen> m_vParaPenColor;               //存储画平行四边形的画笔的颜色
    ParallelPoint m_paraPoint;                  //平行四边形的坐标及大小
    vector<ParallelPoint> m_vParallel;          //存储坐标点

    //diamond
    bool m_isDia;                               //标记是否画菱形
    QPen m_diaPenColor;                         //画笔的颜色
    vector<QPen> m_vDiaPenColor;                //存储画菱形的画笔的颜色
    DiamondPoint m_diaPoint;                    //菱形的坐标及大小
    vector<DiamondPoint> m_vDiamond;            //存储坐标点

    //trapezia
    bool m_isTra;                               //标记是否画梯形
    QPen m_traPenColor;                         //画笔的颜色
    vector<QPen> m_vTraPenColor;                //存储画梯形的画笔的颜色
    TrapeziaPoint m_traPoint;                   //梯形的坐标及大小
    vector<TrapeziaPoint> m_vTrapezia;          //存储坐标点
};

#endif // DrawingBoard_H
