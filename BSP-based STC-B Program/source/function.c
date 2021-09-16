void dealwithDisp()
{
	unsigned char d[8];
	static unsigned char ct100mS = 10;
	unsigned char warn = 0;
	// unsigned int tm = std.temp_mid, tr = std.temp_range, rm = std.rop_mid, rr = std.rop_range;

	if (--ct100mS == 0)
		ct100mS = 10;
	switch (funcmode)
	{
	case MainPage:
		ADCresult = GetADC();
		temp = dist((temp / 15), temp_mid);
		rop = dist(rop, rop_mid);
		if (GetVibAct() == enumVibQuake)
			d[3] = 13;
		else 
			d[3] = 10;
		
		if (temp <= temp_range * A)
			d[5] = 10;
		else if (temp <= temp_range * B)
			d[5] = 11;
		else if (temp <= temp_range * C)
			d[5] = 12;
		else
			d[5] = 13;
		if (rop <= rop_range * A)
			d[7] = 10;
		else if (rop <= rop_range * B)
			d[7] = 11;
		else if (rop <= rop_range * C)
			d[7] = 12;
		else
			d[7] = 13;
		d[0] = 15;
		d[1] = 15;
		d[2] = 15;
		d[4] = 14;
		d[6] = 14;
		
		break;

	case RTC_YMD:
		if (tempadj == 0)
			t = RTC_Read(); //非调时钟时， 读RTC
		d[0] = t.year >> 4;
		d[1] = t.year & 0x0f;
		d[2] = 14;
		d[3] = t.month >> 4;
		d[4] = t.month & 0x0f;
		d[5] = 14;
		d[6] = t.day >> 4;
		d[7] = t.day & 0x0f;
		break;

	case RTC_HMS:
		if (tempadj == 0)
			t = RTC_Read();
		d[0] = t.hour >> 4;
		d[1] = t.hour & 0x0f;
		d[2] = 14;
		d[3] = t.minute >> 4;
		d[4] = t.minute & 0x0f;
		d[5] = 14;
		d[6] = t.second >> 4;
		d[7] = t.second & 0x0f;
		break;

	case Rt_Rop:
		ADCresult = GetADC();

		d[0] = ((temp / 15) / 15) / 100 % 100;
		d[1] = (temp / 15) / 10 % 10;
		d[2] = (temp / 15) % 10;
		d[3] = 15;
		d[4] = 15;
		d[5] = rop / 100;
		d[6] = rop / 10 % 10;
		d[7] = rop % 10;
		break;

	case Weight:
		valOfWeight = GetWeight() - stdWeight; //a为称重AD数据，带符号整数（16bit补码），未标定
		d[0] = 15;
		d[1] = 15;
		d[2] = 15;
		if (valOfWeight < 0)
		{
			valOfWeight = -valOfWeight;
			d[2] = 14;
		} //a变正数，d[2]符号
		d[3] = valOfWeight / 10000;
		valOfWeight = valOfWeight % 10000;
		d[4] = valOfWeight / 1000;
		valOfWeight = valOfWeight % 1000;
		d[5] = valOfWeight / 100;
		valOfWeight = valOfWeight % 100;
		d[6] = valOfWeight / 10;
		d[7] = valOfWeight % 10;
		break;

	default:
		break;
	}

	if (ct100mS >= 8)
		switch (tempadj)
		{
		case 1:
			d[0] = 10;
			d[1] = 10;
			break;
		case 2:
			d[3] = 10;
			d[4] = 10;
			break;
		case 3:
			d[6] = 10;
			d[7] = 10;
			break;
		default:
			break;
		}
	Seg7Print(d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7]);
}

void dealwithmyKN()
{
	if (GetAdcNavAct(enumAdcNavKey3) == enumKeyRelease) //示例。按键3:(抬起时）向串口1发送二进制数据包：报告系统性能
	{
		// SetBeep(1000, 20);
		if (funcmode == Weight) //
		{
			stdWeight = GetWeight();
		}
	}
}

void dealwithmykey()
{
	if (GetKeyAct(enumKey2) == enumKeyPress) //示例。按键2:（按下时）切换显示和按键功能模式
	{
		// SetBeep(1000,20);
		if (++funcmode > Weight)
			funcmode = MainPage;
		LedPrint(funcmode);
		M24C02_Write(0x00, funcmode);
		if (funcmode == Weight)
			EXTInit(enumEXTWeight);
	}
}