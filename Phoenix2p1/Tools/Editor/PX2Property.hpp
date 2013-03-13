/*
*
* �ļ�����	��	PX2Property.hpp
*
*/

#ifndef PX2PROPERTY_HPP
#define PX2PROPERTY_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class PropertyGrid;
	class Property;

	typedef void (*ButtonDownCallback)(Property *prop);

	class wxStringButtonEditor : public wxPGTextCtrlEditor
	{
		DECLARE_DYNAMIC_CLASS(wxStringButtonEditor)
	public:
		wxStringButtonEditor();
		wxStringButtonEditor(Property *prop);
		virtual ~wxStringButtonEditor();

		virtual wxPGWindowList CreateControls( wxPropertyGrid* propGrid,
			wxPGProperty* property,
			const wxPoint& pos,
			const wxSize& sz ) const;
		virtual bool OnEvent( wxPropertyGrid* propGrid,
			wxPGProperty* property,
			wxWindow* ctrl,
			wxEvent& event ) const;

		void SetButtonDownCallback (ButtonDownCallback fun);

	protected:

		ButtonDownCallback mButtonDownCallback;
		Property *mProperty;
	};

	class PropertyPage;

	/**
	* �Ӵ����������Բ���Ҫ�ֶ�����PropertyPage::AddProperty,���캯��ֱ�ӽ����
	* �������б��������ڴ����
	*/
	class Property : public PX2::EventHandler
	{
	public:

		enum PropertyType
		{
			PT_CATEGORY,
			PT_INT,
			PT_FLOAT,
			PT_BOOL,
			PT_BOOLCHECK,
			PT_COLOR3FLOAT3,
			PT_FLOAT2,
			PT_FLOAT3,
			PT_FLOAT4,
			PT_STRING,
			PT_STRINGBUTTON,
			PT_ENUM,
			PT_TRANSFORMATION,
			//
			PT_ACTORTRANSFORMATION,
			//
			PT_EMFLOAT,
			PT_EMFLOATRANGE,
			PT_EMFLOAT3,
			PT_EMFLOAT3RANGE,
			PT_QUANTITY
		};

		Property (PropertyPage *parent, std::string name, PropertyType type,
			void *data, bool enable=true, const std::vector<std::string> *enums=0);
		virtual ~Property ();

		PropertyPage *GetPage () { return mParent; }

		void Enable (bool editable);
		bool IsEnabled ();

		PropertyType GetType () { return mType; }
		std::string GetName () { return mName; }

		void SetValue (std::string val);
		std::string GetAsString ();
		void SetValue (bool val);
		bool GetAsBool ();

		// PT_STRINGBUTTON����ť�����£������ص�����
		void SetButtonDownCallback (ButtonDownCallback fun);

		virtual void OnChange (wxPropertyGridEvent &event);
		virtual void OnChanging (wxPropertyGridEvent &event);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

		wxPGProperty *GetWxProperty ();

	protected:
		Property ();
		wxColor StringToColor (wxString strColor);

		std::string mName;
		PropertyType mType;
		void *mData;

public_internal:
		PropertyPage *mParent;
		wxPGProperty *mProperty;
		bool mEnable;
		wxPGEditor *mStringButtonEditor;
		ButtonDownCallback mButtonDownCallback;
		static int msStringButtonEditorNum;
	};

	typedef PX2::Pointer0<Property> PropertyPtr;

}

#endif