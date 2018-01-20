#pragma once

/*	说明:
 *  USEOPENCV宏：true 使用opencv相关函数与类；flash 不使用opencv相关函数与类，导致部分opencv相关函数无法使用
 *	内部自定义点结构体 Hpoint用于存储点
 *	SetPoints将要拟合的点传入函数，可以直接传入opencv边缘查找函数输出的vector<Point>(非vector<vector<Point>>)。必须设置USEOPENCV为true
 *	也可以传入vector<HPoint>
 *  FitCurve()开始拟合数据，可带最大允许平方误差。如果不带，使用此函数前需要用SetFitMaxAllowSqDist函数设置（不设置默认为5）
 *	GetFitResult获取拟合结果，返回数据类型详见函数声明
 *  GetFitInterpret()获取拟合数据的插值，可用来直接绘图。
 *	DrawResultOnMat()将拟合结果绘制在指定Mat上（必须设置USEOPENCV为true），详见函数声明
 *
 *	函数调用顺序：
 *	SetPoints 传入点数据
 *	SetFitMaxAllowSqDist 设置最大允许平方误差（可选）
 *	FitCurve 开始拟合
 *	GetFitResult 获取拟合结果
 *
 *	最大允许平方误差：拟合点与对应原始点距离平方的最大允许值，单位：像素
 */

#define USEOPENCV true

#if USEOPENCV
#include <opencv2\opencv.hpp>
#endif

#include <iostream>
#include <vector>

using namespace std;

#if USEOPENCV
using namespace cv;
#endif

class BezierFit
{
public:
	struct Hpoint
	{
		double x;
		double y;
	};

	struct Bezier
	{
		Hpoint p[4];
	};

	struct node
	{
		node *next;			//下一个节点指针
		bool fit;			//本节点至下一个节点中间的数据是否拟合完成
		int cutIndex;		//间断点标号
		Hpoint cp[4];		//此间断点与下个间断点之间的贝塞尔拟合曲线控制点
	};
	struct chain
	{
		node *head;			//指向第一个节点的指针
		int Num;			//节点数量
	};

private:
	vector<Hpoint> *PointSerial = new vector<Hpoint>;	//原始点序列
	vector<Hpoint> *FitPointSerial = new vector<Hpoint>;	//拟合点序列
	chain CutPointIndex;			//存放间断点及拟合贝塞尔曲线控制点链表
	vector<Bezier> BezierCP;		//最终拟合贝塞尔曲线
	double MaxAllowSqError = 5;		//最大允许误差
	bool CloseCurve = true;			//封闭曲线

public:
	BezierFit();
	~BezierFit();

	void Clear();															//清空数据
	bool SetPoints(const vector<Hpoint> &_PointSerial, bool _ClodeCurve);	//传入点列

#if USEOPENCV
	bool SetPoints(const vector<Point> &_PointSerial, bool _ClodeCurve);	//传入点列(兼容Opencv边缘序列）
#endif

	bool FitCurve();														//拟合曲线
	bool FitCurve(double _MaxAllowSqError);									//拟合曲线,带最大允许平方误差
	bool SetFitMaxAllowSqDist(double _MaxAllowSqError);						//设置拟合最大允许误差
	double GetFitMaxAllowSqDist();											//获取拟合最大允许误差
	vector<Bezier> GetFitResult();											//获取拟合结果
	vector<Hpoint> GetFitInterpret();										//获取拟合插值点
	int GetbezierNum();														//获取贝塞尔曲线片段数量

#if USEOPENCV
	void DrawResultOnMat(Mat &img, Scalar &pointColor1, Scalar &pointColor2);//在MAT上绘制所有已经拟合号的曲线（两种颜色交替使用）
	void DrawResultOnMat(Mat &img, int index, Scalar &pointColor);			//在MAT上绘制标号为index的已经拟合号的曲线
#endif

private:
	node *CreateNode();		//新建节点
	void FitInit();			//拟合前的初始化
	void SegmentFit(int index1, int index2, Hpoint (&cp)[4]);					//片段拟合
	void BezierInterpret(int index1, int index2, const Hpoint (&cp)[4]);		//贝塞尔函数差值
	void FindMaxSqDist(int index1, int index2, int &_MaxSqDistIndex, double &_MaxSqDist);	//找出最大误差
};
