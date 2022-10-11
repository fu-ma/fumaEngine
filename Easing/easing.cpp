#include "easing.h"
const double easing:: c1 = 1.70158;
const double easing::c2 = c1 * 1.525;
const double easing::c3 = c1 + 1;
const double easing::c4 = (2 * DirectX::XM_PI) / 3;
const double easing::c5 = (2 * DirectX::XM_PI) / 4.5;
const double easing::n1 = 7.5625;
const double easing::d1 = 2.75;
double easing::easingSet = 0;
//’¼ÚŒÄ‚Ô•K—v‚ª‚È‚­‚È‚é‚Ì‚Åprivate‚É
double easing::easeInSine(double x)
{
	return 1.001f - cos((x * DirectX::XM_PI) / 2);
}
double easing::easeOutSine(double x)
{
	return sin((x * DirectX::XM_PI) / 2);
}
double easing::easeInOutSine(double x)
{
	return -(cos(DirectX::XM_PI * x) - 1) / 2;
}
double easing::easeInQuad(double x)
{
	return (x * x) + 0.001f;
}
double easing::easeOutQuad(double x)
{
	return 1 - (1 - x) * (1 - x);
}
double easing::easeInOutQuad(double x)
{
	return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
}
double easing::easeInCubic(double x)
{
	return (x * x * x) + 0.001f;
}
double easing::easeOutCubic(double x)
{
	return 1 - pow(1 - x, 3);
}
double easing::easeInOutCubic(double x)
{
	return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2;
}
double easing::easeInQuart(double x)
{
	return x * x * x * x;
}
double easing::easeOutQuart(double x)
{
	return 1 - pow(1 - x, 4);
}
double easing::easeInOutQuart(double x)
{
	return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2;
}
double easing::easeInQuint(double x)
{
	return x * x * x * x * x;
}
double easing::easeOutQuint(double x)
{
	return 1 - pow(1 - x, 5);
}
double easing::easeInOutQuint(double x)
{
	return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
}
double easing::easeInExpo(double x)
{
	return x == 0 ? 0 : pow(2, 10 * x - 10);
}
double easing::easeOutExpo(double x)
{
	return x == 1 ? 1 : 1 - pow(2, -10 * x);
}
double easing::easeInOutExpo(double x)
{
	return x == 0
		? 0
		: x == 1
		? 1
		: x < 0.5 ? pow(2, 20 * x - 10) / 2
		: (2 - pow(2, -20 * x + 10)) / 2;
}
double easing::easeInCirc(double x)
{
	return 1 - sqrt(1 - pow(x, 2));
}
double easing::easeOutCirc(double x)
{
	return sqrt(1 - pow(x - 1, 2));
}
double easing::easeInOutCirc(double x)
{
	return x < 0.5
		? (1 - sqrt(1 - pow(2 * x, 2))) / 2
		: (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
}
double easing::easeInBack(double x)
{
	return c3 * x * x * x - c1 * x * x;
}
double easing::easeOutBack(double x)
{
	return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
}
double easing::easeInOutBack(double x)
{
	return x < 0.5
		? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
		: (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
}
double easing::easeInElastic(double x)
{
	return x == 0
		? 0
		: x == 1
		? 1
		: -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4);
}
double easing::easeOutElastic(double x)
{
	return x == 0
		? 0
		: x == 1
		? 1
		: pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
}
double easing::easeInOutElastic(double x)
{
	return x == 0
		? 0
		: x == 1
		? 1
		: x < 0.5
		? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2
		: (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1;
}
double easing::easeInBounce(double x)
{
	return 1 - easeOutBounce(1 - x);
}
double easing::easeOutBounce(double x)
{
	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	}
	else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}
double easing::easeInOutBounce(double x)
{
	return x < 0.5
		? (1 - easeOutBounce(1 - 2 * x)) / 2
		: (1 + easeOutBounce(2 * x - 1)) / 2;
}

//public
void easing::Updete(double &pos, double rearPos, int anyEase, double &time)
{
	const double initialPos = pos;
	switch (anyEase)
	{
	case 1:
		easingSet = easeInSine(time);
		break;
	case 2:
		easingSet = easeOutSine(time);
		break;
	case 3:
		easingSet = easeInOutSine(time);
		break;
	case 4:
		easingSet = easeInQuad(time);
		break;
	case 5:
		easingSet = easeOutQuad(time);
		break;
	case 6:
		easingSet = easeInOutQuad(time);
		break;
	case 7:
		easingSet = easeInCubic(time);
		break;
	case 8:
		easingSet = easeOutCubic(time);
		break;
	case 9:
		easingSet = easeInOutCubic(time);
		break;
	case 10:
		easingSet = easeInQuart(time);
		break;
	case 11:
		easingSet = easeOutQuart(time);
		break;
	case 12:
		easingSet = easeInOutQuart(time);
		break;
	case 13:
		easingSet = easeInQuint(time);
		break;
	case 14:
		easingSet = easeOutQuint(time);
		break;
	case 15:
		easingSet = easeInOutQuint(time);
		break;
	case 16:
		easingSet = easeInExpo(time);
		break;
	case 17:
		easingSet = easeOutExpo(time);
		break;
	case 18:
		easingSet = easeInOutExpo(time);
		break;
	case 19:
		easingSet = easeInCirc(time);
		break;
	case 20:
		easingSet = easeOutCirc(time);
		break;
	case 21:
		easingSet = easeInOutCirc(time);
		break;
	case 22:
		easingSet = easeInBack(time);
		break;
	case 23:
		easingSet = easeOutBack(time);
		break;
	case 24:
		easingSet = easeInOutBack(time);
		break;
	case 25:
		easingSet = easeInElastic(time);
		break;
	case 26:
		easingSet = easeOutElastic(time);
		break;
	case 27:
		easingSet = easeInOutElastic(time);
		break;
	case 28:
		easingSet = easeInBounce(time);
		break;
	case 29:
		easingSet = easeOutBounce(time);
		break;
	case 30:
		easingSet = easeInOutBounce(time);
		break;
	}
	if (time <= 1.0f)
	{
		pos = initialPos + (easingSet * (rearPos-initialPos));
	}
	//if (time < 1.0f)
	//{
	//	time += 0.01f;
	//}
}