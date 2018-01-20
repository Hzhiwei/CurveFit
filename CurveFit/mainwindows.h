#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H


#include <QtWidgets/QMainWindow>
#include "ui_mainwindows.h"
#include "qfiledialog.h"
#include "bezierfit.hpp"
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

class mainWindows : public QMainWindow
{
	Q_OBJECT

public:
	mainWindows(QWidget *parent = 0);
	~mainWindows();

private:
	Ui::mainWindowsClass ui;

	Mat srcImage;
	Mat grayImage;
	Mat thresholdImage;
	Mat *contoursImage;
	Mat *fitImage;

	BezierFit FitTool;

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

private:
	bool ShowMatOnLabel(const Mat &Image, QLabel &L);

private slots:
	void Slot_OpenImage(void);
	void Slot_AdjustThreshImage(void);
	void Slot_AdjustMaxSqError(void);
};

#endif // MAINWINDOWS_H
