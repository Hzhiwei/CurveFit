#include "mainwindows.h"

mainWindows::mainWindows(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.PB_open, SIGNAL(clicked()), this, SLOT(Slot_OpenImage()));
	connect(ui.SB_thresh, SIGNAL(valueChanged(int)), this, SLOT(Slot_AdjustThreshImage()));
	connect(ui.SB_maxAllowSqError1, SIGNAL(valueChanged(int)), this, SLOT(Slot_AdjustMaxSqError()));
	connect(ui.SB_maxAllowSqError2, SIGNAL(valueChanged(int)), this, SLOT(Slot_AdjustMaxSqError()));
}

mainWindows::~mainWindows()
{

}

void mainWindows::Slot_OpenImage(void)
{
	double resizeRate[2];
	int bezierNum = 0;
	double err = ui.SB_maxAllowSqError1->value() + ui.SB_maxAllowSqError2->value() / 100.0;

	FitTool.SetFitMaxAllowSqDist(err);

	QString imageName = QFileDialog::getOpenFileName(this, "open image", "", "image(*.png *.jpg *.jpeg *bmp)");

	if (imageName == NULL)
	{
		return;
	}

	srcImage = imread(imageName.toStdString());

	ShowMatOnLabel(srcImage, *(ui.L_srcImage));

	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	threshold(grayImage, thresholdImage, ui.SB_thresh->value(), 255, THRESH_BINARY);
	ShowMatOnLabel(thresholdImage, *(ui.L_adjImage));

	contoursImage = new Mat(srcImage.rows, srcImage.cols, CV_8UC3, Scalar(255, 255, 255));
	findContours(thresholdImage, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
	drawContours(*contoursImage, contours, -1, Scalar(0));
	ShowMatOnLabel(*contoursImage, *(ui.L_conImage));

	fitImage = new Mat(srcImage.rows, srcImage.cols, CV_8UC3, Scalar(255, 255, 255));
	for (int index = 0; index < contours.size(); ++index)
	{
		if (contours[index].size() < 3)
		{
			continue;
		}
		FitTool.SetPoints(contours[index], true);
		FitTool.FitCurve();
		FitTool.DrawResultOnMat(*fitImage, Scalar(0, 0, 255), Scalar(255, 0, 0));
		bezierNum += FitTool.GetbezierNum();
	}
	ShowMatOnLabel(*fitImage, *(ui.L_fitImage));
	ui.L_conNum->setText(QString::number(contours.size(), 10));
	ui.L_bezierNum->setText(QString::number(bezierNum, 10));

	imshow("contours", *contoursImage);
	imshow("bezier", *fitImage);
}


void mainWindows::Slot_AdjustThreshImage(void)
{
	int bezierNum = 0;
	double err = ui.SB_maxAllowSqError1->value() + ui.SB_maxAllowSqError2->value() / 100.0;

	FitTool.SetFitMaxAllowSqDist(err);
	ui.L_thresh->setText(QString::number(ui.SB_thresh->value(), 10));

	if (!srcImage.empty())
	{
		cvtColor(srcImage, grayImage, CV_BGR2GRAY);
		threshold(grayImage, thresholdImage, ui.SB_thresh->value(), 255, THRESH_BINARY);
		ShowMatOnLabel(thresholdImage, *(ui.L_adjImage));

		contoursImage = new Mat(srcImage.rows, srcImage.cols, CV_8UC3, Scalar(255, 255, 255));
		findContours(thresholdImage, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
		drawContours(*contoursImage, contours, -1, Scalar(0));
		ShowMatOnLabel(*contoursImage, *(ui.L_conImage));

		fitImage = new Mat(srcImage.rows, srcImage.cols, CV_8UC3, Scalar(255, 255, 255));
		for (int index = 0; index < contours.size(); ++index)
		{
			if (contours[index].size() < 3)
			{
				continue;
			}
			FitTool.SetPoints(contours[index], true);
			FitTool.FitCurve();
			FitTool.DrawResultOnMat(*fitImage, Scalar(0, 0, 255), Scalar(255, 0, 0));
			bezierNum += FitTool.GetbezierNum();
		}
		ShowMatOnLabel(*fitImage, *(ui.L_fitImage));
		ui.L_conNum->setText(QString::number(contours.size(), 10));
		ui.L_bezierNum->setText(QString::number(bezierNum, 10));

		imshow("contours", *contoursImage);
		imshow("bezier", *fitImage);
	}
}


void mainWindows::Slot_AdjustMaxSqError(void)
{
	int bezierNum = 0;
	double err = ui.SB_maxAllowSqError1->value() + ui.SB_maxAllowSqError2->value() / 100.0;

	ui.L_maxAllowSqError1->setText(QString::number(ui.SB_maxAllowSqError1->value(), 10));
	ui.L_maxAllowSqError2->setText(QString::number(ui.SB_maxAllowSqError2->value() / 100.0f));

	FitTool.SetFitMaxAllowSqDist(err);

	if (!srcImage.empty())
	{
		cvtColor(srcImage, grayImage, CV_BGR2GRAY);
		threshold(grayImage, thresholdImage, ui.SB_thresh->value(), 255, THRESH_BINARY);
		ShowMatOnLabel(thresholdImage, *(ui.L_adjImage));

		contoursImage = new Mat(srcImage.rows, srcImage.cols, CV_8UC3, Scalar(255, 255, 255));
		findContours(thresholdImage, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
		drawContours(*contoursImage, contours, -1, Scalar(0));
		ShowMatOnLabel(*contoursImage, *(ui.L_conImage));

		fitImage = new Mat(srcImage.rows, srcImage.cols, CV_8UC3, Scalar(255, 255, 255));
		for (int index = 0; index < contours.size(); ++index)
		{
			if (contours[index].size() < 3)
			{
				continue;
			}
			FitTool.SetPoints(contours[index], true);
			FitTool.FitCurve();
			FitTool.DrawResultOnMat(*fitImage, Scalar(0, 0, 255), Scalar(255, 0, 0));
			bezierNum += FitTool.GetbezierNum();
		}
		ShowMatOnLabel(*fitImage, *(ui.L_fitImage));
		ui.L_conNum->setText(QString::number(contours.size(), 10));
		ui.L_bezierNum->setText(QString::number(bezierNum, 10));

		imshow("contours", *contoursImage);
		imshow("bezier", *fitImage);
	}
}


bool mainWindows::ShowMatOnLabel(const Mat &Image, QLabel &L)
{
	Mat tempImage;

	if (Image.empty())
	{
		return false;
	}

	double resizeRate[2];

	//adjust size
	resizeRate[0] = (double)(L.width()) / Image.size().width;
	resizeRate[1] = (double)(L.height()) / Image.size().height;
	resizeRate[0] = resizeRate[0] < resizeRate[1] ? resizeRate[0] : resizeRate[1];
	cv::resize(Image, tempImage, Size(Image.size().width * resizeRate[0], Image.size().height * resizeRate[0]));

	if (tempImage.type() == CV_8UC3)
	{
		cv::cvtColor(tempImage, tempImage, CV_BGR2RGB);
	}
	else if (tempImage.type() == CV_8UC1)
	{
		cv::cvtColor(tempImage, tempImage, CV_GRAY2RGB);
	}
	QImage img = QImage((const unsigned char*)(tempImage.data), tempImage.cols, tempImage.rows, tempImage.cols*tempImage.channels(), QImage::Format_RGB888);
	L.clear();
	L.setPixmap(QPixmap::fromImage(img));

	return true;
}


