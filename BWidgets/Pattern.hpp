/* Pattern.hpp
 * Copyright (C) 2018 - 2023  Sven Jähnichen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BWIDGETS_PATTERN_HPP_
#define BWIDGETS_PATTERN_HPP_

#include "Pad.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/Draggable.hpp"
#include "Supports/ValidatableRange.hpp"
#include "Supports/ValueTransferable.hpp"
#include "Supports/KeyPressable.hpp"
#include "../BEvents/PointerEvent.hpp"

#ifndef BWIDGETS_DEFAULT_PATTERN_WIDTH
#define BWIDGETS_DEFAULT_PATTERN_WIDTH 400
#endif

#ifndef BWIDGETS_DEFAULT_PATTERN_HEIGHT
#define BWIDGETS_DEFAULT_PATTERN_HEIGHT 200
#endif

namespace BWidgets
{
/**
 *  @brief  Composite widget displaying a pattern of pad widgets (default: 
 *  Pads).
 *  @tparam T  Pad widget type.
 *
 *  %Pattern is a Valueable widget displaying a pattern of pad widgets 
 *  (default: Pads). It is intended to use a Pad-derived widget to display a
 *  step or pad sequencer-like pattern, but it is also possible to use any 
 *  other Valueable widget. The pad widgets value type
 *  * MUST support the standard comparison operators, 
 *  * MUST support the standard arithmetic operators. 
 *  * MUST be compatible with ValueableTyped, ValidatableRange, and
 *    ValueTransferable.
 *
 *  %Pattern allows to draw a pattern by left-clicking on the pads or dragging
 *  over the pads via support of Draggable and setting the pad values to 
 *  their @c getMin() or defined default drawing value (defined with
 *  @c pads.setValue() ), respectively. %Pattern also supports KeyPressable.
 *
 *  Right-clicking picks the respective pad value and re-defines the default 
 *  drawing value. This action is equivalent to left-clicking in the
 *  PICK_MODE.
 *
 *  If the select mode is on (by setting the EditMode, e. g., cut, copy, 
 *  delete, swap), pressing the left mouse button or dragging will mark the 
 *  respective pad instead and the action of the 
 *  selected EditMode will be applied after the button release.
 *
 *  Pattern is an Enterable Widget. Once entered (e.g., by clicking on it),
 *  keyboard control is enabled:
 *  * Cursor keys for navigation
 *  * SHIFT + cursor keys for dragging (only in select mode)
 *  * CTRL + A to select all (only in select mode)
 *  * +/- to increase or decrease the recent pad value
 *  * ENTER to apply action
 *  * ESCAPE to leave this Pattern.
 *
 *  The value of the %Pattern is a 2D vector of @c std::pair with the repective 
 *  pad extends (default: BUtilities::Point<size_t>(0, 0)) as the first and 
 *  the respective pad value as the second type.
 *
 *  @todo  Support change pattern size.
 *  @todo  Support merge pads by dragging.
 *  @todo  Support Journal.
 */
template <class T = Pad<>>
class Pattern : public Widget, 
				public ValueableTyped<std::vector<std::vector<std::pair<BUtilities::Point<size_t>, typename T::value_type>>>>,
				public Clickable, 
				public Draggable,
				public KeyPressable
{

public:

	typedef std::vector<std::vector<std::pair<BUtilities::Point<size_t>, typename T::value_type>>> value_type;

protected:

	/**
	 *  @brief  Pad value and value modifiers template class. 
	 */
	class PadsTemplType :	public ValueableTyped<typename T::value_type>, 
							public ValidatableRange<typename T::value_type>, 
							public ValueTransferable<typename T::value_type>
	{
	private:
		Pattern<T>* parent__;

	public:
		PadsTemplType () = delete;
		PadsTemplType (Pattern<T>* parent);
		PadsTemplType (const PadsTemplType& that) = delete;
		~PadsTemplType () = default;
		PadsTemplType& operator= (const PadsTemplType& that);

		/**
		 *  @brief  Sets the range lower limit.
		 *  @param min  Lower limit.
		 */
		virtual void setMin (const typename T::value_type& min) override;

	    /**
	     *  @brief  Sets the range upper limit.
	     *  @param min  Upper limit.
 	    */
 	   virtual void setMax (const typename T::value_type& max) override;

		/**
		 *  @brief  Sets the range step size.
		 *  @param min  Step size.
		 */
		virtual void setStep (const typename T::value_type& step) override;

		/**
		 *  @brief  Sets the value range.
		 *  @param min  Lower limit.
		 *  @param max  Upper limit.
		 *  @param step  Step.
		 */
		virtual void setRange (const typename T::value_type& min, const typename T::value_type& max, const typename T::value_type& step) override;

 		/**
		 *  @brief  Sets the transfer function.
		 *  @param func  Transfer function.
		 *
		 *  The transfer function is used
		 *  to transfer a value from an external context (e. g., frequencies with a
		 *  logarithmic distribution) to an internal context (e. g., a slider with 
		 *  linear distribution). In this case a possible transfer function would be:
		 *  @code
		 *  [] (const double& x) {return log10 (x);}
		 *  @endcode
		 *
		 *  The transfer function (and its re-transfer function) MUST be biunique.
		 */
		virtual void setTransferFunction (std::function<typename T::value_type (const typename T::value_type& x)> func) override;

		/**
		 *  @brief  Sets the re-transfer function.
		 *  @param func  Re-transfer function.
		 *
		 *  The re-transfer function is used to transfer a value from an internal 
		 *  context (e. g., a
		 *  position within a slider with linear distribution) to an external
		 *  context (e. g., frequencies with a logarithmic distribution). In this
		 *  case a possible re-transfer function would be:
		 *  @code
		 *  [] (const double& x) {return pow (10, x);}
		 *  @endcode
		 *
		 *  The transfer function (and its re-transfer function) MUST be biunique.
     	 */
    	virtual void setReTransferFunction (std::function<typename T::value_type (const typename T::value_type& x)> func) override;
	};

public:

	/**
	 *  @brief  Allows to set value modifiers (ValidatableRange,
	 *  ValueTransferable) to all pads and to set the default
	 *  value for clicked pads.
	 */
	PadsTemplType pads;

	enum class EditMode
	{
		edit = 0,
		pick,
		select,
		cut,
		copy,
		paste,
		del,
		xflip,
		yflip
	};

protected:

	size_t columns_;
	size_t rows_;
	std::vector<std::vector<Widget*>> pads_;
	BUtilities::Area<size_t> selection_;
	BUtilities::Point<size_t> selectionP1_;
	BUtilities::Point<size_t> selectionP2_;
	bool selected_;
	bool drag_;
	EditMode editMode_;
	bool allowYMerge_;
	value_type clipBoard_;


private:
	bool padOn__;	// Status of the pad where button pressed, used for 
					// onPointerDragged()


public:

	/**
	 *  @brief  Constructs a new %Pattern object with default parameters.
	 */
	Pattern ();

	/**
	 *  @brief  Constructs a new %Pattern object with default parameters.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	Pattern (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %Pattern with default size.
	 *  @param columns  Number of columns.
	 *  @param rows  Number of rows.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Pattern	(const size_t columns, const size_t rows, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %Pattern.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param columns  Number of columns.
	 *  @param rows  Number of rows.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Pattern	(const double x, const double y, const double width, const double height, 
			 const size_t columns, const size_t rows,
			 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	~Pattern();

	/**
	 *  @brief  Creates a clone of the %Pattern. 
	 *  @return  Pointer to the new %Pattern.
	 *
	 *  Creates a clone of this %Pattern by copying all properties. But NOT
	 *  its linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %Pattern. 
	 *  @param that  Other %Pattern.
	 *
	 *  Copies all properties from another %Pattern. But NOT its linkage.
	 */
	void copy (const Pattern* that);

	/**
	 *  @brief  Changes the edit mode.
	 *  @param editMode  EditMode.
	 */
	void setEditMode (const EditMode editMode);

	/**
	 *  @brief  Gets the edit mode.
	 *  return  EditMode.
	 */
	EditMode getEditMode () const;

	/**
	 *  @brief  Selects a %Pattern area.
	 *  @param p1  First point (column, row).
	 *  @param p2  Second point (column, row).
	 */
	void select (const BUtilities::Point<size_t> p1, const BUtilities::Point<size_t> p2);

	/**
	 *  @brief  Performs an action (cut, copy, paste, ...) on the pattern
	 *  pad values.
	 *  @param mode  EditMode for action.
	 *  @param selection  Area to apply action on.
	 */
	void action (const EditMode mode, const BUtilities::Area<size_t> selection);

	/**
	 *  @brief  Cuts pad values to the clipboard. 
	 *  @param selection  Selection area.
	 *
	 *  Pads of the cut area will be left with a getMin() value.
	 */
	void cutValues (const BUtilities::Area<size_t> selection);

	/**
	 *  @brief  Copies pad values to the clipboard. 
	 *  @param selection  Selection area.
	 */
	void copyValues (const BUtilities::Area<size_t> selection);

	/**
	 *  @brief  Pastes pad values from the clipboard. 
	 *  @param pos  Start position to paste at.
	 */
	void pasteValues (const BUtilities::Point<size_t> pos);

	/**
	 *  @brief  Deletes pad values and set getMin() instead. 
	 *  @param selection  Selection area.
	 */
	void deleteValues (const BUtilities::Area<size_t> selection);

	/**
	 *  @brief  Flips pad values horizontally. 
	 *  @param selection  Selection area.
	 */
	void xflipValues (const BUtilities::Area<size_t> selection);

	/**
	 *  @brief  Flips pad values vertically. 
	 *  @param selection  Selection area.
	 */
	void yflipValues (const BUtilities::Area<size_t> selection);

	/**
	 *  @brief  Gets the Wigget for the respective pad.
	 *  @param column  %Pattern column (starting with 0). 
	 *  @param row  %Pattern row (starting with 0).
	 *  @return  Pointer to the Widget for the respective pad.
	 */
	Widget* getPad (const size_t column, const size_t row) const;

	/**
     *  @brief  Optimizes the widget extends.
     *
	 *  Firstly optimizes the pad sizes. Then resizes the widget to include
	 *  all direct children (including the pads) into the widget area.
	 */
	virtual void resize () override;

    /**
     *  @brief  Resizes the widget extends.
	 *  @param width  New widget width.
	 *  @param height  New widget height.
	 */
	virtual void resize (const double width, const double height) override;

    /**
	 *  @brief  Resizes the widget extends.
	 *  @param extends  New widget extends.
	 */
	virtual void resize (const BUtilities::Point<> extends) override;
	
	/**
     *  @brief  Enters this %Pattern.
     *
     *  Activates this %Pattern, takes over keyboard control, and calls to leave 
	 *  all other widgets linked to the main Window to become the only entered 
	 *  Widget.
     */
    virtual void enter () override;

	/**
     *  @brief  Leaves this %Pattern
     *
     *  De-activates this %Pattern and release keyboard conrol.
     */
    virtual void leave () override;

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

	/**
     *  @brief  Method called when pointer button pressed.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button pressed. By default, it calls its static callback 
     *  function.
     */
    virtual void onButtonPressed (BEvents::Event* event) override;

	/**
     *  @brief  Method called when pointer button released.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button released. By default, it calls its static callback 
     *  function.
     */
    virtual void onButtonReleased (BEvents::Event* event) override;
	
	/**
     *  @brief  Method called upon (mouse) wheel scroll.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a (mouse) wheel scroll. Increases or decreases the value and calls the
	 *  widget static callback function.
     */
    virtual void onPointerDragged (BEvents::Event* event) override;

	/**
     *  @brief  Method when a KeyEvent with the type keyPressEvent is 
     *  received.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler if a
     *  key is pressed. By default, it calls its static callback function.
     */
    virtual void onKeyPressed (BEvents::Event* event) override;

    /**
     *  @brief  Method when a KeyEvent with the type keyReleaseEvent is 
     *  received.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler if a
     *  key is released. By default, it calls its static callback function.
     */
    virtual void onKeyReleased (BEvents::Event* event) override;

protected:

	/**
	 *  @brief  Callback function for VALUE_CHANGED_EVENTs emitted by pads.
	 *  @param event  Passed event.
	 */
	static void padChangedCallback (BEvents::Event* event);

	/**
	 *  @brief  Tests if the %Pattern is in an EditMode that supports
	 *  selection of pads by clicking or dragging.
	 *  @return  True if selection of pads is supported, otherwise false.
	 */
	bool isSelectMode() const;

	/**
	 *  @brief  Gets the pad index (column, row) from a position.
	 *  @param x  X position relative to the %Pattern origin.
	 *  @param y  Y position relative to the %Pattern origin.
	 *  @return  Pad index asBUtilities::Point<size_t>.
	 */
	BUtilities::Point<size_t> getPadIndex (const double x, const double y) const;

	void updatePads();

	/**
     *  @brief  Unclipped draw to the surface (if is visualizable).
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped Draw to the surface (if is visualizable).
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped Draw to the surface (if is visualizable).
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

template <class T>
inline Pattern<T>::PadsTemplType::PadsTemplType (Pattern<T>* parent) :
	ValidatableRange<typename T::value_type> (),
	ValueTransferable<typename T::value_type> (),
	parent__ (parent)
{

}

template <class T>
inline typename Pattern<T>::PadsTemplType& Pattern<T>::PadsTemplType::operator= (const Pattern<T>::PadsTemplType& that)
{
	// Keep parent__ !
	
	ValueTransferable<typename T::value_type>::operator= (that);
	ValidatableRange<typename T::value_type>::operator= (that);
	ValueableTyped<typename T::value_type>::operator= (that);
}

template <class T>
inline void Pattern<T>::PadsTemplType::setMin (const typename T::value_type& min)
{
	ValidatableRange<typename T::value_type>::setMin (min);
	parent__->updatePads();
}

template <class T>
inline void Pattern<T>::PadsTemplType::setMax (const typename T::value_type& max)
{
	ValidatableRange<typename T::value_type>::setMax (max);
	parent__->updatePads();
}

template <class T>
inline void Pattern<T>::PadsTemplType::setStep (const typename T::value_type& step)
{
	ValidatableRange<typename T::value_type>::setStep (step);
	parent__->updatePads();
}

template <class T>
inline void Pattern<T>::PadsTemplType::setRange (const typename T::value_type& min, const typename T::value_type& max, const typename T::value_type& step)
{
	ValidatableRange<typename T::value_type>::setRange (min, max, step);
	parent__->updatePads();
}

template <class T>
inline void Pattern<T>::PadsTemplType::setTransferFunction (std::function<typename T::value_type (const typename T::value_type& x)> func)
{
	ValueTransferable<typename T::value_type>::setTransferFunction (func);
	parent__->updatePads();
}

template <class T>
inline void Pattern<T>::PadsTemplType::setReTransferFunction (std::function<typename T::value_type (const typename T::value_type& x)> func)
{
	ValueTransferable<typename T::value_type>::setReTransferFunction (func);
	parent__->updatePads();
}

template <class T>
inline Pattern<T>::Pattern () : 
	Pattern	(0.0, 0.0, BWIDGETS_DEFAULT_PATTERN_WIDTH, BWIDGETS_DEFAULT_PATTERN_HEIGHT, 0, 0, BUTILITIES_URID_UNKNOWN_URID, "") 
{

}

template <class T>
inline Pattern<T>::Pattern	(const uint32_t urid, const std::string& title) :
	Pattern	(0.0, 0.0, BWIDGETS_DEFAULT_PATTERN_WIDTH, BWIDGETS_DEFAULT_PATTERN_HEIGHT, 0, 0, urid, title) 
{

}

template <class T>
inline Pattern<T>::Pattern	(const size_t columns, const size_t rows, uint32_t urid, std::string title) :
	Pattern	(0.0, 0.0, BWIDGETS_DEFAULT_PATTERN_WIDTH, BWIDGETS_DEFAULT_PATTERN_HEIGHT, columns, rows, urid, title) 
{

}

template <class T>
inline Pattern<T>::Pattern	(const double x, const double y, const double width, const double height, 
						 	 const size_t columns, const size_t rows, uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	ValueableTyped<std::vector<std::vector<std::pair<BUtilities::Point<size_t>, typename T::value_type>>>> (),
	Clickable (),
	Draggable (),
	KeyPressable(),
	pads (this),
	columns_(columns),
	rows_(rows),
	pads_ (),
	selection_(),
	selectionP1_(),
	selectionP2_(),
	selected_ (false),
	drag_ (false),
	editMode_ (EditMode::edit),
	allowYMerge_ (false),
	clipBoard_(),
	padOn__ (false)
{
	setActivatable(true);
	setEnterable(true);
	setKeyPressable(false);
	pads.setValue (1.0);
	for (size_t r = 0; r < rows_; ++r)
	{
		std::vector<std::pair<BUtilities::Point<size_t>, typename T::value_type>> vs;
		std::vector<Widget*> ws;

		for (size_t c = 0; c < columns_; ++c)
		{
			T* w = new T(BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/pad"), "(" + std::to_string(c) + ", " + std::to_string(r) + ")");
			w->setActivatable(false);
			w->setEnterable(false);
			w->setCallbackFunction (BEvents::Event::EventType::valueChangedEvent, padChangedCallback);
			w->setClickable (false);
			w->setEventPassable(BEvents::Event::EventType::buttonEvents | BEvents::Event::EventType::pointerDragEvent);
			add (w);
			ws.push_back (w);

			BUtilities::Point<size_t> ext (0, 0);
			typename T::value_type value = typename T::value_type ();
			std::pair<BUtilities::Point<size_t>, typename T::value_type> v (ext, value);
			vs.push_back (v);
		}

		pads_.push_back (ws);
		this->value_.push_back (vs);
	}
}

template <class T>
inline Pattern<T>::~Pattern ()
{
	if (getParentWidget()) getParentWidget()->release (this);

	for (size_t r = 0; r < rows_; ++r)
	{
		for (size_t c = 0; c < columns_; ++c)
		{
			if (pads_[r][c]) delete pads_[r][c];
		}
	}
}

template <class T>
inline Widget* Pattern<T>::clone () const 
{
	Widget* f = new Pattern (urid_, title_);
	f->copy (this);
	return f;
}

template <class T>
inline void Pattern<T>::copy (const Pattern<T>* that)
{
	pads = that->pads;

	for (size_t r = 0; r < rows_; ++r)
	{
		for (size_t c = 0; c < columns_; ++c)
		{
			if (pads_[r][c]) delete pads_[r][c];
			pads_[r][c] = nullptr;
		}
	}
	pads_.clear();

	columns_ = that->columns_;
	rows_ = that->rows_;

	for (size_t r = 0; r < rows_; ++r)
	{
		std::vector<Widget*> ws;

		for (size_t c = 0; c < columns_; ++c)
		{
			Widget* w = (that->pads_[r][c] ? that->pads_[r][c]->clone() : nullptr);
			add (w);
			ws.push_back (w);
		}

		pads_.push_back (ws);
	}

	selection_ = that->selectionPos_;
	selectionP1_ = that->selectionP1_;
	selectionP2_ = that->selectionP2_;
	selected_ = that->selected_;
	drag_ = that->drag_;
	editMode_ = that->editMode_;
	allowYMerge_ = that->allowYMerge_;
	clipBoard_ = that->clipBoard_;
	padOn__ = that->padOn;

	KeyPressable::operator=(*that);
	Draggable::operator= (*that);
	Clickable::operator= (*that);
	ValueableTyped<value_type>::operator= (*that);
	Widget::copy (that);
}

template <class T>
void Pattern<T>::setEditMode (const EditMode editMode)
{
	editMode_ = editMode;
	selection_ = BUtilities::Area<size_t>();
	selectionP1_ = BUtilities::Point<size_t>();
	selectionP2_ = BUtilities::Point<size_t>();
	selected_ = false;
	update();
}

template <class T>
typename Pattern<T>::EditMode Pattern<T>::getEditMode() const
{
	return editMode_;
}

template <class T>
void Pattern<T>::select (const BUtilities::Point<size_t> p1, const BUtilities::Point<size_t> p2)
{
	selectionP1_ = BUtilities::Point<size_t>(std::min (p1.x, (columns_ > 0 ? columns_ - 1 : 0)), std::min (p1.y, (rows_ > 0 ? rows_ - 1 : 0)));
	selectionP2_ = BUtilities::Point<size_t>(std::min (p2.x, (columns_ > 0 ? columns_ - 1 : 0)), std::min (p2.y, (rows_ > 0 ? rows_ - 1 : 0)));
	selection_ = BUtilities::Area<size_t> (selectionP1_, selectionP2_);
	selected_ = true;
	update();
}

template <class T>
void Pattern<T>::action (const EditMode mode, const BUtilities::Area<size_t> selection)
{
	switch (mode)
	{
		case EditMode::edit:	break;

		case EditMode::pick:	break;

		case EditMode::cut:		cutValues (selection);
								break;

		case EditMode::copy:	copyValues (selection);
								break;

		case EditMode::paste:	pasteValues (selection.getPosition());
								break;

		case EditMode::del:		deleteValues (selection);
								break;

		case EditMode::xflip:	xflipValues (selection);
								break;

		case EditMode::yflip:	yflipValues (selection);
								break;

		default:				break;
	}
}

template <class T>
void Pattern<T>::cutValues(const BUtilities::Area<size_t> selection)
{
	copyValues (selection);
	deleteValues (selection);
}

template <class T>
void Pattern<T>::copyValues(const BUtilities::Area<size_t> selection)
{
	clipBoard_.clear();

	for (size_t dr = 0; dr <= selection.getHeight(); ++dr)
	{
		std::vector<std::pair<BUtilities::Point<size_t>, typename T::value_type>> vs;
		
		for (size_t dc = 0; dc <= selection.getWidth(); ++dc)
		{
			const std::pair<BUtilities::Point<size_t>, typename T::value_type> v = this->value_[selection.getY() + dr][selection.getX() + dc];
			vs.push_back (v);
		}

		clipBoard_.push_back (vs);
	}
}

template <class T>
void Pattern<T>::pasteValues(const BUtilities::Point<size_t> pos)
{
	for (size_t dr = 0; (dr < clipBoard_.size()) && (pos.y + dr < rows_); ++dr)
	{
		const std::vector<std::pair<BUtilities::Point<size_t>, typename T::value_type>> vs = clipBoard_[dr];
		for (size_t dc = 0; (dc < vs.size()) && (pos.x + dc < columns_); ++dc)
		{
			const std::pair<BUtilities::Point<size_t>, typename T::value_type> v = vs[dc];
			T* w = dynamic_cast<T*>(pads_[pos.y + dr][pos.x + dc]);
			w->setValue (v.second);
			// TODO pad extends
		}
	}
}

template <class T>
void Pattern<T>::deleteValues(const BUtilities::Area<size_t> selection)
{
	for (size_t dr = 0; dr <= selection.getHeight(); ++dr)
	{
		for (size_t dc = 0; dc <= selection.getWidth(); ++dc)
		{
			T* w = dynamic_cast<T*>(pads_[selection.getY() + dr][selection.getX() + dc]);
			w->setValue (w->getMin());
		}
	}
}

template <class T>
void Pattern<T>::xflipValues(const BUtilities::Area<size_t> selection)
{
	for (size_t dr = 0; dr <= selection.getHeight(); ++dr)
	{
		for (size_t dc = 0; dc < (selection.getWidth() + 1) / 2; ++dc)
		{
			T* w1 = dynamic_cast<T*>(pads_[selection.getY() + dr][selection.getX() + dc]);
			T* w2 = dynamic_cast<T*>(pads_[selection.getY() + dr][selection.getX() + selection.getWidth() - dc]);
			typename T::value_type v2 = w2->getValue();
			w2->setValue (w1->getValue());
			w1->setValue (v2);
		}
	}
}

template <class T>
void Pattern<T>::yflipValues(const BUtilities::Area<size_t> selection)
{
	for (size_t dr = 0; dr < (selection.getHeight() + 1) / 2; ++dr)
	{
		for (size_t dc = 0; dc <= selection.getWidth() ; ++dc)
		{
			T* w1 = dynamic_cast<T*>(pads_[selection.getY() + dr][selection.getX() + dc]);
			T* w2 = dynamic_cast<T*>(pads_[selection.getY() + selection.getHeight() - dr][selection.getX() + dc]);
			typename T::value_type v2 = w2->getValue();
			w2->setValue (w1->getValue());
			w1->setValue (v2);
		}
	}
}

template <class T>
inline Widget* Pattern<T>::getPad (const size_t column, const size_t row) const
{
	return ((column < columns_) && (row < rows_) ? pads_[row][column] : nullptr);
}

template <class T>
inline void Pattern<T>::resize ()
{
	double y = getYOffset();
	for (size_t r = 0; r < rows_; ++r)
	{
		double x = getXOffset();
		for (size_t c = 0; c < columns_; ++c)
		{
			pads_[r][c]->resize ();
			pads_[r][c]->moveTo (x, y);
			x += pads_[r][c]->getWidth();
		}
		if (!pads_[r].empty()) y += pads_[r][0]->getHeight();
	}
	Widget::resize ();
}

template <class T>
inline void Pattern<T>::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

template <class T>
inline void Pattern<T>::resize (const BUtilities::Point<> extends)
{
	Widget::resize (extends);
}

template <class T>
inline void Pattern<T>::enter () 
{
	if (isEnterable() && (!isEntered()))
	{
		setKeyPressable(true);
		grabDevice (BDevices::Keys());
		Widget::enter();
	}
}

template <class T>
inline void Pattern<T>::leave () 
{
	if (isEnterable() && isEntered())
	{
		setKeyPressable(false);
		if (isDeviceGrabbed(BDevices::Keys())) freeDevice(BDevices::Keys ());
		Widget::leave();
	}
}

template <class T>
inline void Pattern<T>::update ()
{
	for (size_t r = 0; r < rows_; ++r)
	{
		for (size_t c = 0; c < columns_; /*empty*/)
		{
			size_t st = (allowYMerge_ ? this->getValue()[r][c].first.x + 1 : 1);

			pads_[r][c]->moveTo 
			(
				getXOffset() + getEffectiveWidth() * static_cast<double>(c) / static_cast<double>(columns_) + 0.01 * getEffectiveWidth() / static_cast<double>(columns_),
				getYOffset() + getEffectiveHeight() * static_cast<double>(r) / static_cast<double>(rows_) + 0.01 * getEffectiveHeight() / static_cast<double>(rows_)
			);

			pads_[r][c]->resize 
			(
				(static_cast<double> (st - 1) + 0.98) * getEffectiveWidth() / static_cast<double>(columns_),
				0.98 * getEffectiveHeight() / static_cast<double>(rows_)
			);

			pads_[r][c]->show();

			// TODO Hide pads under merged pads, once merging is established

			c += st;
		}
	}
	Widget::update();
}

template <class T>
inline void Pattern<T>::onButtonPressed (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*>(event);
	if (!pev) return;

	// Enter
	enter();

	// Calculate position
	const BUtilities::Point<size_t> p = getPadIndex (pev->getPosition().x, pev->getPosition().y);

	// Pick mode:
	if (editMode_ == EditMode::pick || (pev->getButton() == BDevices::MouseButton::ButtonType::right)) 
	{
		pads.setValue (dynamic_cast<T*>(pads_[p.y][p.x])->getValue());
		if (isEnterable() && isEntered()) select (p, p);
	}

	// Paste mode:
	else if (editMode_ == EditMode::paste)
	{
		pasteValues (p);
		if (isEnterable() && isEntered()) select (p, p);
	}

	// Selection mode:
	else if (isSelectMode()) 
	{
		if (isEnterable() && isEntered() & selected_ & drag_) select (selectionP1_, p);
		else select (p, p);
	}

	// Default: Invert pad value
	else
	{
		T* w = dynamic_cast<T*>(pads_[p.y][p.x]);
		typename T::value_type v = pads.getValue();
		padOn__ = (w->getValue() != v);
		w->setValue (padOn__ ? v : w->getMin());
		if (isEnterable() && isEntered()) select (p, p);
	}

	Clickable::onButtonPressed (event);
}

template <class T>
inline void Pattern<T>::onButtonReleased (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*>(event);
	if (!pev) return;

	// Calculate position
	const BUtilities::Point<size_t> p = getPadIndex (pev->getPosition().x, pev->getPosition().y);

	if (selected_ && isSelectMode() && (pev->getButton() == BDevices::MouseButton::ButtonType::left)) action (getEditMode(), selection_);
	if (isEnterable() && isEntered() && selected_) select (p, p);
	else selected_ = false;
	update();
	Clickable::onButtonReleased (event);
}

template <class T>
inline void Pattern<T>::onPointerDragged (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*>(event);
	if (!pev) return;

	// Calculate position
	const BUtilities::Point<size_t> p0 = getPadIndex (pev->getOrigin().x, pev->getOrigin().y);
	const BUtilities::Point<size_t> p = getPadIndex (pev->getPosition().x, pev->getPosition().y);
		
	// Selection mode: Drag selection
	if (isSelectMode() && (pev->getButton() == BDevices::MouseButton::ButtonType::left)) select (p0, p);

	// Default:
	else 
	{
		// Calculate previous position
		const BUtilities::Point<size_t> p2 = getPadIndex (pev->getPosition().x - pev->getDelta().x, pev->getPosition().y - pev->getDelta().y);
		T* w = dynamic_cast<T*>(pads_[p.y][p.x]);

		if (p != p2)
		{
			// Pick mode:
			if (editMode_ == EditMode::pick || (pev->getButton() == BDevices::MouseButton::ButtonType::right)) pads.setValue (dynamic_cast<T*>(pads_[p.y][p.x])->getValue());

			// Paste mode:
			else if (editMode_ == EditMode::paste) pasteValues (p);

			// Default: Set or unset pad
			else w->setValue (padOn__ ? pads.getValue() : w->getMin());

			if (isEnterable() && isEntered()) select (p, p);
		}
	}
	Draggable::onPointerDragged (event);
}

template <class T>
inline void Pattern<T>::onKeyPressed (BEvents::Event* event)
{
	BEvents::KeyEvent* kev = dynamic_cast<BEvents::KeyEvent*>(event);
	if (!kev) return;
	if (kev->getWidget() != this) return; 
	
	switch (kev->getKey ())
	{
		case 1 /* CTRL A*/:
			if (isSelectMode()) 
			{
				select	(BUtilities::Point<size_t> (0, 0), 
						 BUtilities::Point<size_t> (columns_ > 0 ? columns_ - 1 : 0, rows_ > 0 ? rows_ - 1 : 0));
			}
			break;

		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::shiftL):
		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::shiftR):
			drag_ = true;
			break;

		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::left):
			if (selected_ && (selection_.getX() > 0))
			{
				const BUtilities::Point<size_t> p = BUtilities::Point<size_t> (selectionP2_.x > 0 ? selectionP2_.x - 1 : 0, selectionP2_.y);
				if (selected_ & drag_ & isSelectMode()) select (selectionP1_, p);
				else select(p, p);
			}
			break;

		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::right):	
			if (selected_ && (selection_.getX() + 1 < columns_))
			{
				const BUtilities::Point<size_t> p = BUtilities::Point<size_t> (selectionP2_.x + 1, selectionP2_.y);
				if (selected_ & drag_ & isSelectMode()) select (selectionP1_, p);
				else select(p, p);
			}
			break;

		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::up):
			if (selected_ && (selection_.getY() > 0))
			{
				const BUtilities::Point<size_t> p = BUtilities::Point<size_t> (selectionP2_.x, selectionP2_.y > 0 ? selectionP2_.y - 1 : 0);
				if (selected_ & drag_ & isSelectMode()) select (selectionP1_, p);
				else select(p, p);
			}
			break;

		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::down):		
			if (selected_ && (selection_.getY() + 1 < rows_))
			{
				const BUtilities::Point<size_t> p = BUtilities::Point<size_t> (selectionP2_.x, selectionP2_.y + 1);
				if (selected_ & drag_ & isSelectMode()) select (selectionP1_, p);
				else select(p, p);
			}
			break;

		case '+':	
			{
				T* w = dynamic_cast<T*>(pads_[selectionP2_.y][selectionP2_.x]);
				if (w)
				{
					BEvents::WheelEvent wev = BEvents::WheelEvent(w, BEvents::Event::EventType::wheelScrollEvent, 0.5 * w->getWidth(), 0.5 * w->getHeight(), 0, -1);
					w->onWheelScrolled(&wev);
				}
			}
			break;

		case '-':	
			{
				T* w = dynamic_cast<T*>(pads_[selectionP2_.y][selectionP2_.x]);
				if (w)
				{
					BEvents::WheelEvent wev = BEvents::WheelEvent(w, BEvents::Event::EventType::wheelScrollEvent, 0.5 * w->getWidth(), 0.5 * w->getHeight(), 0, 1);
					w->onWheelScrolled(&wev);
				}
			}
			break;

		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::enter):	
			if (selected_)
			{
				const BUtilities::Point<size_t> p = selection_.getPosition();
				if (editMode_ == EditMode::edit) 
				{
					T* w = dynamic_cast<T*>(pads_[p.y][p.x]);
					typename T::value_type v = pads.getValue();
					padOn__ = (w->getValue() != v);
					w->setValue (padOn__ ? v : w->getMin());
				}
				else if (editMode_ == EditMode::pick) pads.setValue (dynamic_cast<T*>(pads_[p.y][p.x])->getValue());
				else if (editMode_ == EditMode::paste) pasteValues (p);
				else action (getEditMode(), selection_);

				select (p, p);
			}
			break;

		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::escape):
			// Area selected: reset selection to last point
			if (selected_ & isSelectMode() && (selectionP1_ != selectionP2_)) 
			{
				select (selectionP2_, selectionP2_);
			}

			// Otherwise: Leave
			else
			{
				selected_ = false;
				leave();
			}
			break;

		default:								
			break;
	}

	KeyPressable::onKeyPressed(event);
}

template <class T>
inline void Pattern<T>::onKeyReleased (BEvents::Event* event)
{
	BEvents::KeyEvent* kev = dynamic_cast<BEvents::KeyEvent*>(event);
	if (!kev) return;
	if (kev->getWidget() != this) return;

	BDevices::Keys::KeyType key = static_cast<BDevices::Keys::KeyType>(kev->getKey ());
	switch (key)
	{
		case BDevices::Keys::KeyType::shiftL:
		case BDevices::Keys::KeyType::shiftR:	drag_ = false;
												break;

		default:								break;
	}

	KeyPressable::onKeyReleased(event);
}

template <class T>
inline void Pattern<T>::padChangedCallback (BEvents::Event* event)
{
	BEvents::ValueChangeTypedEvent<typename T::value_type>* vev = dynamic_cast<BEvents::ValueChangeTypedEvent<typename T::value_type>*>(event);
	if (!vev) return;
	T* w = dynamic_cast<T*>(vev->getWidget());
	if (!w) return;
	Pattern<T>* p = dynamic_cast<Pattern<T>*>(w->getParentWidget());
	if (!p) return;

	// Get column/row
	// TODO from coordinates

	// Fallback: iterate
	for (size_t r = 0; r < p->rows_; ++r)
	{
		for (size_t c = 0; c < p->columns_; ++c)
		{
			if (w == p->pads_[r][c])
			{
				value_type v = p->getValue();
				v[r][c].second = w->getValue();
				p->setValue (v);
				break;
			}
		}
	}
}

template <class T>
inline bool Pattern<T>::isSelectMode () const
{
	return	(editMode_ == EditMode::cut) || 
			(editMode_ == EditMode::copy) ||
			(editMode_ == EditMode::del) ||
			(editMode_ == EditMode::xflip) ||
			(editMode_ == EditMode::yflip);
}

template <class T>
inline BUtilities::Point<size_t> Pattern<T>::getPadIndex (const double x, const double y) const
{
	return BUtilities::Point<size_t>
	(
		std::min (std::max (static_cast<int>(static_cast<double>(columns_) * (x - getXOffset()) / getEffectiveWidth()), 0), static_cast<int> (columns_ == 0 ? 0 : columns_ - 1)),
		std::min (std::max (static_cast<int>(static_cast<double>(rows_) * (y - getYOffset()) / getEffectiveHeight()), 0), static_cast<int>(rows_ == 0 ? 0 : rows_ - 1))
	);
}

template <class T>
inline void Pattern<T>::updatePads()
{
	for (size_t r = 0; r < rows_; ++r)
	{
		for (size_t c = 0; c < columns_; ++c)
		{
			T* w = dynamic_cast<T*>(pads_[r][c]);
			w->setRange (pads.getMin(), pads.getMax(), pads.getStep());
			w->setTransferFunction(pads.getTransferFunction());
			w->setReTransferFunction(pads.getReTransferFunction());
		}
	}
}

template <class T>
inline void Pattern<T>::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

template <class T>
inline void Pattern<T>::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

template <class T>
inline void Pattern<T>::draw (const BUtilities::Area<>& area)
	{
		if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return;

		if ((getWidth () >= 1) && (getHeight () >= 1))
		{
			// Draw super class widget elements first
			Widget::draw (area);

			cairo_t* cr = cairo_create (cairoSurface());
			if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
			{
				cairo_scale (cr, surface_.scale, surface_.scale);
				
				// Limit cairo-drawing area
				cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
				cairo_clip (cr);

				const double x0 = getXOffset ();
				const double y0 = getYOffset ();
				const double w = getEffectiveWidth ();
				const double h = getEffectiveHeight ();

				if (selected_ /*&& isSelectMode()*/)
				{
					for (size_t r = 0; r < rows_; ++r)
					{
						for (size_t c = 0; c < columns_; /* empty */)
						{
							size_t st = (allowYMerge_ ? this->getValue()[r][c].first.x + 1 : 1);
							if (selection_.contains(BUtilities::Point<size_t>(c, r)))
							{
								const double xs =	x0 + w * static_cast<double>(c) / static_cast<double>(columns_);
								const double ys = 	y0 + h * static_cast<double>(r) / static_cast<double>(rows_);
								const double ws = 	w * static_cast<double>(st) / static_cast<double>(columns_);
								const double hs = 	h / static_cast<double>(rows_);
								const BStyles::Color color = getBgColors()[getStatus()].illuminate (BStyles::Color::highLighted);
								cairo_rectangle (cr, xs, ys, ws, hs);
								cairo_set_line_width (cr, 0.0);
								cairo_set_source_rgba (cr, CAIRO_RGBA (color));
								cairo_fill (cr);
							}

							c += st;
						}
					}
					
				}

				cairo_destroy (cr);
			}
		}
	}

}

#endif /* BWIDGETS_PATTERN_HPP_ */
