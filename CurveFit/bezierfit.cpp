#include "bezierfit.hpp"

BezierFit::BezierFit()
{
	CutPointIndex.head = NULL;
}

BezierFit::~BezierFit()
{
	node *p0 = CutPointIndex.head;
	node *p1;
	while (true)
	{
		if (p0 != NULL)
		{
			p1 = p0->next;
			delete p0;
			p0 = p1;
		}
		else
		{
			break;
		}
	}

	delete FitPointSerial;
	delete PointSerial;
}


void BezierFit::Clear()
{
	node *p0 = CutPointIndex.head;
	node *p1;
	while (true)
	{
		if (p0 != NULL)
		{
			p1 = p0->next;
			delete p0;
			p0 = p1;
		}
		else
		{
			break;
		}
	}
	CutPointIndex.Num = 0;

	delete FitPointSerial;
	delete PointSerial;
	BezierCP.clear();
}


bool BezierFit::SetPoints(const vector<Hpoint> &_PointSerial, bool _ClodeCurve)
{
	vector<Hpoint>().swap(*PointSerial);
	if (CloseCurve)
	{
		if (_PointSerial.size() < 3)
		{
			return false;
		}
		else
		{
			*PointSerial = _PointSerial;
			PointSerial->push_back((*PointSerial)[0]);
		}
	}
	else
	{
		if (_PointSerial.size() < 2)
		{
			return false;
		}
		else
		{
			*PointSerial = _PointSerial;
		}
	}
}


#if USEOPENCV
bool BezierFit::SetPoints(const vector<Point> &_PointSerial, bool _ClodeCurve)
{
	vector<Hpoint>().swap(*PointSerial);
	int Num = _PointSerial.size();
	Hpoint temp;

	if (CloseCurve)
	{
		if (_PointSerial.size() < 3)
		{
			return false;
		}
		else
		{
			for (int i = 0; i < Num; ++i)
			{
				temp.x = _PointSerial[i].x;
				temp.y = _PointSerial[i].y;
				PointSerial->push_back(temp);
			}
			PointSerial->push_back((*PointSerial)[0]);
		}
	}
	else
	{
		if (_PointSerial.size() < 2)
		{
			return false;
		}
		else
		{
			for (int i = 0; i < Num; ++i)
			{
				temp.x = _PointSerial[i].x;
				temp.y = _PointSerial[i].y;
				PointSerial->push_back(temp);
			}
		}
	}
}
#endif


bool BezierFit::FitCurve()
{
	Bezier bezierTemp;
	node *nodeTemp[3];

	FitInit();

	//初始化处理，闭合曲线先分成两段（三个间断点），非闭合直接一段（两个间断点）直接进行拟合。
	if (CloseCurve)
	{
		if (PointSerial->size() < 4)
		{
			return false;
		}
		else
		{
			nodeTemp[0] = CreateNode();
			nodeTemp[0]->fit = false;
			nodeTemp[0]->cutIndex = 0;
			CutPointIndex.head = nodeTemp[0];

			nodeTemp[1] = CreateNode();
			nodeTemp[1]->fit = false;
			nodeTemp[1]->cutIndex = PointSerial->size() / 2;
			nodeTemp[0]->next = nodeTemp[1];

			nodeTemp[0] = nodeTemp[1];

			nodeTemp[1] = CreateNode();
			nodeTemp[1]->fit = false;
			nodeTemp[1]->cutIndex = PointSerial->size() - 1;
			nodeTemp[0]->next = nodeTemp[1];

			nodeTemp[1]->next = NULL;
			CutPointIndex.Num = 3;
		}
	}
	else
	{
		if (PointSerial->size() < 2)
		{
			return false;
		}
		else
		{
			nodeTemp[0] = CreateNode();
			nodeTemp[0]->fit = false;
			nodeTemp[0]->cutIndex = 0;
			CutPointIndex.head = nodeTemp[0];

			nodeTemp[1] = CreateNode();
			nodeTemp[1]->fit = false;
			nodeTemp[1]->cutIndex = PointSerial->size() - 1;
			nodeTemp[0]->next = nodeTemp[1];

			nodeTemp[1]->next = NULL;
			CutPointIndex.Num = 2;
		}
	}

	double MaxDist;
	int MaxDistIndex;
	//拟合核心算法
	nodeTemp[0] = CutPointIndex.head;
	nodeTemp[1] = CutPointIndex.head->next;

	while (nodeTemp[0] != NULL)
	{
		if (nodeTemp[0]->fit)
		{
			if (nodeTemp[1]->next == NULL)
			{
				break;
			}
			else
			{
				nodeTemp[0] = nodeTemp[1];
				nodeTemp[1] = nodeTemp[1]->next;
				continue;
			}
		}
		else
		{
			SegmentFit(nodeTemp[0]->cutIndex, nodeTemp[1]->cutIndex, nodeTemp[0]->cp);
			BezierInterpret(nodeTemp[0]->cutIndex, nodeTemp[1]->cutIndex, nodeTemp[0]->cp);
			FindMaxSqDist(nodeTemp[0]->cutIndex, nodeTemp[1]->cutIndex, MaxDistIndex, MaxDist);
			if (MaxDist > MaxAllowSqError)
			{
				nodeTemp[0]->fit = false;
				nodeTemp[2] = CreateNode();
				nodeTemp[2]->cutIndex = MaxDistIndex;
				nodeTemp[2]->fit = false;
				nodeTemp[2]->next = nodeTemp[1];
				nodeTemp[0]->next = nodeTemp[2];
				nodeTemp[1] = nodeTemp[2];
				++CutPointIndex.Num;
				continue;
			}
			else
			{
				nodeTemp[0]->fit = true;
				if (nodeTemp[1]->next == NULL)
				{
					break;
				}
				else
				{
					nodeTemp[0] = nodeTemp[1];
					nodeTemp[1] = nodeTemp[1]->next;
					continue;
				}
			}
		}
	}

	nodeTemp[0] = CutPointIndex.head;
	while (true)
	{
		if (nodeTemp[0]->next != NULL)
		{
			bezierTemp.p[0] = nodeTemp[0]->cp[0];
			bezierTemp.p[1] = nodeTemp[0]->cp[1];
			bezierTemp.p[2] = nodeTemp[0]->cp[2];
			bezierTemp.p[3] = nodeTemp[0]->cp[3];
			BezierCP.push_back(bezierTemp);
			nodeTemp[0] = nodeTemp[0]->next;
		}
		else
		{
			break;
		}
	}
}


bool BezierFit::FitCurve(double _MaxAllowSqError)
{
	if (_MaxAllowSqError > 0)
	{
		MaxAllowSqError = _MaxAllowSqError;
	}
	else
	{
		return false;
	}
	return FitCurve();
}


bool BezierFit::SetFitMaxAllowSqDist(double _MaxAllowSqError)
{
	if (_MaxAllowSqError > 0)
	{
		MaxAllowSqError = _MaxAllowSqError;
		return true;
	}
	else
	{
		return false;
	}
}


double BezierFit::GetFitMaxAllowSqDist()
{
	return MaxAllowSqError;
}


vector<BezierFit::Bezier> BezierFit::GetFitResult()
{
	return BezierCP;
}


vector<BezierFit::Hpoint> BezierFit::GetFitInterpret()
{
	return *FitPointSerial;
}


int BezierFit::GetbezierNum()
{
	if (CutPointIndex.Num > 0)
	{
		return CutPointIndex.Num - 1;
	}
	else
	{
		return CutPointIndex.Num;
	}
}


#if USEOPENCV
void BezierFit::DrawResultOnMat(Mat &img, Scalar &pointColor1, Scalar &pointColor2)
{
	Scalar *c = &pointColor1;
	for (int index = 0; index < CutPointIndex.Num; ++index)
	{
		DrawResultOnMat(img, index, *c);
		if (c == &pointColor1)
		{
			c = &pointColor2;
		}
		else
		{
			c = &pointColor1;
		}
	}
}


void BezierFit::DrawResultOnMat(Mat &img, int index, Scalar &pointColor)
{
	node *temp = CutPointIndex.head;
	int start, end;
	int pixelPerLine = img.cols * img.channels();
	int set;

	if (index > CutPointIndex.Num - 2)
	{
		return;
	}

	for (int count = 0; count < index; ++count)
	{
		if (temp->next == NULL)
		{
			return;
		}
		else
		{
			temp = temp->next;
		}
	}
	start = temp->cutIndex;
	end = temp->next->cutIndex;

	for (int count = start; count <= end; ++count)
	{
		if (((*FitPointSerial)[count].y >= img.rows) || ((*FitPointSerial)[count].x >= img.cols))
		{
			return;
		}
		if (((*FitPointSerial)[count].y < 0) || ((*FitPointSerial)[count].x < 0))
		{
			return;
		}
		set = pixelPerLine * (int)((*FitPointSerial)[count].y) + img.channels() * (int)((*FitPointSerial)[count].x);
		img.data[set] = pointColor[0];
		img.data[set + 1] = pointColor[1];
		img.data[set + 2] = pointColor[2];
	}
}
#endif


BezierFit::node *BezierFit::CreateNode()
{
	return new node;
}

//初始化，清空所有拟合中间数据
void BezierFit::FitInit()
{
	node *p0 = CutPointIndex.head;
	node *p1;
	while (true)
	{
		if (p0 != NULL)
		{
			p1 = p0->next;
			delete p0;
			p0 = p1;
		}
		else
		{
			break;
		}
	}

	vector<Hpoint>().swap(*FitPointSerial);
	FitPointSerial->resize(PointSerial->size());
	BezierCP.clear();
}


void BezierFit::SegmentFit(int index1, int index2, Hpoint(&cp)[4])
{
	int pointNum = index2 - index1 + 1;
	double step = 1.0 / pointNum;
	double A1 = 0, A2 = 0, A12 = 0;
	Hpoint C1, C2;
	double B0, B1, B2, B3;
	double t = 0, xt;
	double DENOM;

	C1.x = 0;
	C1.y = 0;
	C2.x = 0;
	C2.y = 0;

	cp[0] = (*PointSerial)[index1];
	cp[3] = (*PointSerial)[index2];

	if (pointNum == 1)
	{
		cp[1] = (*PointSerial)[index1];
		cp[2] = (*PointSerial)[index1];
	}
	else if (pointNum == 2)
	{
		cp[1] = (*PointSerial)[index1];
		cp[2] = (*PointSerial)[index2];
	}
	else if (pointNum == 3)
	{
		cp[1] = (*PointSerial)[index1 + 1];
		cp[2] = (*PointSerial)[index1 + 1];
	}
	else if (pointNum == 4)
	{
		cp[1] = (*PointSerial)[index1 + 1];
		cp[2] = (*PointSerial)[index1 + 2];
	}
	else
	{
		for (int index = index1; index <= index2; ++index, t += step)
		{
			xt = 1 - t;
			B0 = xt * xt * xt;
			B1 = 3 * t * xt * xt;
			B2 = 3 * t * t * xt;
			B3 = t * t * t;

			A1 += B1 * B1;
			A2 += B2 * B2;
			A12 += B1 * B2;
			C1.x += B1 * ((*PointSerial)[index].x - B0 * cp[0].x - B3 * cp[3].x);
			C1.y += B1 * ((*PointSerial)[index].y - B0 * cp[0].y - B3 * cp[3].y);
			C2.x += B2 * ((*PointSerial)[index].x - B0 * cp[0].x - B3 * cp[3].x);
			C2.y += B2 * ((*PointSerial)[index].y - B0 * cp[0].y - B3 * cp[3].y);
		}
		DENOM = A1 * A2 - A12 * A12;

		if (DENOM == 0)
		{
			cp[1] = cp[0];
			cp[2] = cp[3];
		}
		else
		{
			cp[1].x = (A2 * C1.x - A12 * C2.x) / DENOM;
			cp[1].y = (A2 * C1.y - A12 * C2.y) / DENOM;
			cp[2].x = (A1 * C2.x - A12 * C1.x) / DENOM;
			cp[2].y = (A1 * C2.y - A12 * C1.y) / DENOM;
		}

	}
}


void BezierFit::BezierInterpret(int index1, int index2, const Hpoint (&cp)[4])
{
	double step = 1.0 / (index2 - index1);
	double t = 0, mt;

	for (int index = index1; index <= index2; ++index, t += step)
	{
		mt = 1 - t;

		(*FitPointSerial)[index].x = mt * mt * mt * cp[0].x +
			3 * t * mt * mt * cp[1].x +
			3 * t * t * mt * cp[2].x +
			t * t * t * cp[3].x;
		(*FitPointSerial)[index].y = mt * mt * mt * cp[0].y +
			3 * t * mt * mt * cp[1].y +
			3 * t * t * mt * cp[2].y +
			t * t * t * cp[3].y;
	}
}


void BezierFit::FindMaxSqDist(int index1, int index2, int &_MaxSqDistIndex, double &_MaxSqDist)
{
	double dist;
	double MaxSqDist;
	int MaxSqDistIndex;
	double xTemp, yTemp;

	xTemp = (*PointSerial)[index1].x - (*FitPointSerial)[index1].x;
	yTemp = (*PointSerial)[index1].y - (*FitPointSerial)[index1].y;
	MaxSqDist = xTemp * xTemp + yTemp * yTemp;
	MaxSqDistIndex = index1;
	for (int index = index1 + 1; index <= index2; ++index)
	{
		xTemp = (*PointSerial)[index].x - (*FitPointSerial)[index].x;
		yTemp = (*PointSerial)[index].y - (*FitPointSerial)[index].y;
		dist = xTemp * xTemp + yTemp * yTemp;
		if (dist > MaxSqDist)
		{
			MaxSqDist = dist;
			MaxSqDistIndex = index;
		}
	}

	_MaxSqDistIndex = MaxSqDistIndex;
	_MaxSqDist = MaxSqDist;
}
