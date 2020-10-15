#pragma once

//随机数
class Random
{
public:
	//生成范围内的随机整数（左闭右开）
	static int RangeInt(int start, int end);
	//生成范围内的浮点数（左闭右开）
	static float RangeFloat(float start, float end);
};

