#ifndef SUBPANEL_H
#define SUBPANEL_H

#include <QColor>
#include <QWidget>
#include <QColorDialog>

#include "drawingboard.h"

namespace Ui {
class SubPanel;
}

class SubPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SubPanel(QWidget *parent = 0);
    ~SubPanel();

    DrawingBoard drawBoard;

    void setPenWidthRang();  //设置画笔的最大最小宽度

protected:
    void mouseMoveEvent(QMouseEvent *event);

    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void setIfFill();               //设置是否填充区域
    void setPenColor();             //设置画笔颜色
    void setPenStytle();            //设置画笔样式
    void setLineShape();            //设置画直线
    void setRectShape();            //设置画矩形
    void setCircleShape();          //设置画圆
    void setCurveLineShape();       //设置画任意线
    void setTriangleShape();        //设置画三角形
    void setTrapeziaShape();        //设置画梯形
    void setDiamondShape();         //设置画菱形
    void setParallelogramShape();   //设置画平行四边形


    void setPenWidth(int);      //设置画笔粗细

private:
    Ui::SubPanel *ui;

    /*
     * 子控制面板上“直线”、“曲线”等按钮未选中时的样式
     */
    QString style1;

    /*
     * 子控制面板上“直线”、“曲线”等按钮选中时的样式
     */
    QString style2;
};

#endif // SUBPANEL_H
