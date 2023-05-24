#pragma once
#include <DirectXMath.h>
#include<math.h>
//イージングの種類
enum ease
{
	InSine = 1,
	OutSine,
	InOutSine,
	InQuad,
	OutQuad,
	InOutQuad,
	InCubic,
	OutCubic,
	InOutCubic,
	InQuart,
	OutQuart,
	InOutQuart,
	InQuint,
	OutQuint,
	InOutQuint,
	InExpo,
	OutExpo,
	InOutExpo,
	InCirc,
	OutCirc,
	InOutCirc,
	InBack,
	OutBack,
	InOutBack,
	InElastic,
	OutElastic,
	InOutElastic,
	InBounce,
	OutBounce,
	InOutBounce
};

class easing
{
public:
	static void Updete(double &pos, double rearPos, int anyEase, double &time);
private:
	static const double c1;
	static const double c2;
	static const double c3;
	static const double c4;
	static const double c5;
	static const double n1;
	static const double d1;
	static double easingSet;
	static double easeInSine(double x);
	static double easeOutSine(double x);
	static double easeInOutSine(double x);
	static double easeInQuad(double x);
	static double easeOutQuad(double x);
	static double easeInOutQuad(double x);
	static double easeInCubic(double x);
	static double easeOutCubic(double x);
	static double easeInOutCubic(double x);
	static double easeInQuart(double x);
	static double easeOutQuart(double x);
	static double easeInOutQuart(double x);
	static double easeInQuint(double x);
	static double easeOutQuint(double x);
	static double easeInOutQuint(double x);
	static double easeInExpo(double x);
	static double easeOutExpo(double x);
	static double easeInOutExpo(double x);
	static double easeInCirc(double x);
	static double easeOutCirc(double x);
	static double easeInOutCirc(double x);
	static double easeInBack(double x);
	static double easeOutBack(double x);
	static double easeInOutBack(double x);
	static double easeInElastic(double x);
	static double easeOutElastic(double x);
	static double easeInOutElastic(double x);
	static double easeInBounce(double x);
	static double easeOutBounce(double x);
	static double easeInOutBounce(double x);
};