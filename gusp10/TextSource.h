#pragma once

class TextSource : public gr::IColorTextSource
{
private:
	std::wstring _sText;
	int _foreColor;
	int _backColor;
	bool _isRightToLeft;

public:
	TextSource (const wchar_t * sText,
				size_t cbText):
		_sText(sText, cbText),
		_foreColor(gr::kclrBlack),
		_backColor(gr::kclrTransparent),
		_isRightToLeft(false)
	{
	}

	TextSource ():
		_sText(),
		_foreColor(gr::kclrBlack),
		_backColor(gr::kclrTransparent),
		_isRightToLeft(false)
	{
	}

	TextSource (const TextSource& ts):
	_sText(ts._sText),
		_foreColor(ts._foreColor),
		_backColor(ts._backColor),
		_isRightToLeft(ts._isRightToLeft)
	{
	}

	void setText(const std::wstring & sText){
		_sText = sText;
	}

	gr::UtfType utfEncodingForm()
	{
		return gr::kutf16;
	}
	size_t getLength()
	{
		return _sText.length();
	}
	size_t fetch(toffset ichMin, size_t cch, gr::utf32 * prgchBuffer)
	{
		throw;
	}
	size_t fetch(toffset ichMin, size_t cch, gr::utf16 * prgchwBuffer)
	{
		size_t ichRet = min(cch, getLength() - ichMin);
		memcpy(prgchwBuffer, _sText.c_str(), isizeof(gr::utf16) * ichRet);
		return ichRet;
	}
	size_t fetch(toffset ichMin, size_t cch, gr::utf8 * prgchsBuffer)
	{
		throw;
	}
	bool getRightToLeft(toffset ich)
	{
		return _isRightToLeft;
	}
	void setRightToLeft(bool isRightToLeft)
	{
		_isRightToLeft = isRightToLeft;
	}

	unsigned int getDirectionDepth(toffset ich)
	{
		return 0;
	}
	float getVerticalOffset(toffset ich)
	{
		return 0;
	}
	isocode getLanguage(toffset ich)
	{
		char lang[4];
		lang[0] = 'e'; lang[1] = 'n'; lang[2] = 0; lang[3] = 0;
		isocode ret;
		memcpy(&ret, lang, 4);
		return ret;
	}
	std::pair<toffset, toffset> gr::ITextSource::propertyRange(toffset ich)
	{
		std::pair<toffset, toffset> pairRet;
		pairRet.first = 0;
		pairRet.second = static_cast<toffset>(getLength());
		return pairRet;
	}
	size_t getFontFeatures(toffset ich, gr::FeatureSetting * prgfset)
	{
		return 0; // no features in this simple implementation
	}
	bool sameSegment(toffset ich1, toffset ich2)
	{
		return true;
	}
	void getColors(toffset ich, int * pclrFore, int * pclrBack)
	{
		*pclrFore = _foreColor;
		*pclrBack = _backColor;
	}
	void setColors(toffset ich, int clrFore, int clrBack)
	{
		_foreColor = clrFore;
		_backColor = clrBack;
	}

};