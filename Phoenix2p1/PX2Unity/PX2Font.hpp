/*
*
* 文件名称	：	PX2Font.hpp
*
*/

#ifndef PX2FONT_HPP
#define PX2FONT_HPP

#include "PX2UnityPre.hpp"
#include "PX2CharCoding.hpp"
#include "PX2FontDefine.hpp"
#include "PX2FontGlyphMap.hpp"

namespace PX2
{

	class Font
	{
	public:
		enum FontType
		{
			FT_BITMAP,
			FT_COMMON,
			FT_MAX_TYPE
		};
		Font (FontType type);
		virtual ~Font ();

		FontType GetFontType ();

		virtual bool Initlize (int fontWidth, int fontHeight, 
			const char *fontFilename, CharCodingType codingType,
			unsigned int fontExtStyle);

		/// 根据传入的参数判断所要创建的字体是否与本字体是等价的
		virtual bool IsSame (int fontWidth, int fontHeight,
			const char *fontFilename, CharCodingType codingType,
			unsigned int fontExtStyle) = 0;
		const std::string &GetFontFilename () const;
		unsigned int GetFontExtStyle () const;
		virtual void GetFontSize (int &width, int &height);

		virtual void SetCharSize (int width, int height);
		virtual void GetCharSize (float &width, float &height);

		virtual void SetLineInterval (float interval);
		virtual void GetLineInterval (float &interval);	

		/// 获得一个字符显示尺寸
		virtual void GetCharSize (const unsigned char *character, float &width,
			float &height);
		virtual void GetCharExtent (const unsigned char *character,
			float &width, float &height);

		/// 取得字符串的显示尺寸，此函数可处理换行控制符
		virtual void GetTextExtent (const char *text, float &width,
			float &height, bool doTransfer = false);

		/// 获取从字符串头部到限定宽度范围内，所完整包含的字符串信息
		/**
		* width: 从字符串头部到限定宽度范围内，完整包含的部分字符串显示宽度
		* numBytes: 从字符串头部到限定宽度范围内，完整包含的部分字符串字节长度
		*/
		virtual void GetTextExtentFitInWidth (const char *text, float fixedWidth,
			float &width, int &numBytes, bool doTransfer = false);

		/// 显示字符串
		virtual void TextOutM (TriMesh *mesh, const char *text, float xPos, float yPos,
			const Float4 &color, unsigned int drawStyle=FES_NORMAL,
			bool doTransfer=false, float scale = 1.0f, float depth=0.0f);

		/// 在矩形区域里显示文本
		/**
		* autoWrap表示是否自动换行
		*/
		virtual void TextOutRect (TriMesh *mesh, const char *text, Rectf &rect, float offsetX,
			float offsetY, bool autoWrap, const Float4 &color,
			unsigned int fontStyle=FES_NORMAL, bool doTransfer=false, 
			float scale=1.0f);

		Texture2D *GetTexture ();

	protected:
		Font ();
		void RenderText (TriMesh *mesh, float depth = 0.0f);
		// 从字符串开始到最近的可换行位置的距离
		float GetMinDisToNewLine(const char *text, bool doTransfer = false);
		virtual Texture2D *TexUVMaping (const unsigned char *character, Rectf &rectUV) = 0;

		FontType mFontType;
		std::string mFontFilename;
		CharCodingType mCodingType;
		unsigned int mFontExtStyle;
		int mFontWidth;
		int mFontHeight;
		float mCharWidth;
		float mCharHeight;
		float mLineInterval; //< 行间距
		int mCharNumMaxCache; //< 一张图支持的最大字符数
		int mTexWidth;
		int mTexHeight;
		CharCoding *mCharCodingObj; //< 编码方式处理对象
		FontGlyphMap *mGlyphMap; //< 字形映射对象
		int mShowNum; //< 当前准备输出的多边形数
		Texture2DPtr mTexture; //< 当前需要输出的文字使用的贴图
		std::vector<FontDrawRect> mDrawRects;

		static unsigned int msCounts;
	};

	typedef Pointer0<Font> FontPtr;
#include "PX2Font.inl"

}

#endif