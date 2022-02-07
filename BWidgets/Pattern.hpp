/* Pattern.hpp
 * Copyright (C) 2018 - 2022  Sven Jähnichen
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
#include "Supports/ValueableTyped.hpp"
#include "../BEvents/PointerEvent.hpp"
#include <cairo/cairo.h>
#include <cstddef>
#include <utility>

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
 *  @tparam T  Widget type for the pad.
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
 *  %Pattern allows to draw a pattern by clicking on the pads or dragging
 *  over the pads via support of Draggable and setting the pad values to 
 *  their @c getMin() or @c getMax() , respectively.
 *
 *  If the select mode is on (by setting the EditMode, e. g., cut, copy, 
 *  delete, swap), pressing the mouse button
 *  or dragging will mark the respective pad instead and the action of the 
 *  selected EditMode will be applied after the button release.
 *
 *  The value of the %Pattern is a 2D vector of @c std::pair with the repective 
 *  pad extensions (default: BUtilities::Point<size_t>(1, 1)) as the first and 
 *  the respective pad value as the second type.
 *
 *  @todo  Support change pattern size.
 *  @todo  Support merge pads by dragging.
 *  @todo  Support select pads.
 *  @todo  Support Journal.
 */
template <class T = Pad<>>
class Pattern : public Widget, 
				public ValueableTyped<std::vector<std::vector<std::pair<BUtilities::Point<size_t>, typename T::value_type>>>>,
				public Clickable, 
				public Draggable
{

public:

	typedef std::vector<std::vector<std::pair<BUtilities::Point<size_t>, typename T::value_type>>> value_type;

	enum EditMode
	{
		MODE_EDIT = 0,
		MODE_SELECT,
		MODE_CUT,
		MODE_COPY,
		MODE_PASTE,
		MODE_DELETE,
		MODE_XSWAP,
		MODE_YSWAP
	};

	enum MergeMode
	{
		MERGE_OFF = 0,
		MERGE_X,
		MERGE_Y,
		MERGE_XY
	};

protected:
	size_t columns_;
	size_t rows_;
	std::vector<std::vector<Widget*>> pads_;
	BUtilities::Point<size_t> selectionPos_;
	BUtilities::Point<int> selectionExt_;
	EditMode editMode_;
	MergeMode mergeMode_;
	bool padOn_;


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
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Pattern	(const size_t columns, const size_t rows, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %Pattern.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param columns  Number of columns.
	 *  @param rows  Number of rows.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Pattern	(const double x, const double y, const double width, const double height, 
			 const size_t columns, const size_t rows,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

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

	void select (const size_t column, const size_t row, int width = 1, int height = 1);

	/**
	 *  @brief  Gets the Wigget for the respective pad.
	 *  @param column  %Pattern column (starting with 0). 
	 *  @param row  %Pattern row (starting with 0).
	 *  @return  Pointer to the Widget for the respective pad.
	 */
	Widget* getPad (const size_t column, const size_t row) const;

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
     *  @brief  Method called upon (mouse) wheel scroll.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a (mouse) wheel scroll. Increases or decreases the value and calls the
	 *  widget static callback function.
     */
    virtual void onPointerDragged (BEvents::Event* event) override;

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
    virtual void draw (const BUtilities::RectArea<>& area) override;
};

template <class T>
inline Pattern<T>::Pattern () : 
	Pattern	(0.0, 0.0, BWIDGETS_DEFAULT_PATTERN_WIDTH, BWIDGETS_DEFAULT_PATTERN_HEIGHT, 0, 0, URID_UNKNOWN_URID, "") 
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
	columns_(columns),
	rows_(rows),
	pads_ (),
	selectionPos_(),
	selectionExt_(),
	editMode_ (MODE_EDIT),
	mergeMode_ (MERGE_OFF),
	padOn_ (true)
{
	for (size_t r = 0; r < rows_; ++r)
	{
		std::vector<std::pair<BUtilities::Point<size_t>, typename T::value_type>> vs;
		std::vector<Widget*> ws;

		for (size_t c = 0; c < columns_; ++c)
		{
			T* w = new T(BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/pad"), "");
			w->setCallbackFunction (BEvents::Event::VALUE_CHANGED_EVENT, padChangedCallback);
			w->setClickable (false);
			w->setEventPassable(BEvents::Event::BUTTON_PRESS_EVENT);
			w->setEventPassable(BEvents::Event::BUTTON_RELEASE_EVENT);
			w->setEventPassable(BEvents::Event::BUTTON_CLICK_EVENT);
			w->setEventPassable(BEvents::Event::POINTER_DRAG_EVENT);
			add (w);
			ws.push_back (w);

			BUtilities::Point<size_t> ext (1, 1);
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

	selectionPos_ = that->selectionPos_;
	selectionExt_ = that->selectionExt_;
	editMode_ = that->editMode_;
	mergeMode_ = that->mergeMode_;
	padOn_ = that->padOn;

	Draggable::operator= (*that);
	Clickable::operator= (*that);
	ValueableTyped<value_type>::operator= (*that);
	Widget::copy (that);
}

template <class T>
void Pattern<T>::select (const size_t column, const size_t row, int width, int height)
{
	selectionPos_.x = (column < columns_ ? column : (columns_ == 0 ? 0 : columns_ - 1));
	selectionPos_.y = (row < rows_ ? row : (rows_ == 0 ? 0 : rows_ - 1));
	selectionExt_.x = std::max (std::min (width, static_cast<int>(columns_) - static_cast<int>(selectionPos_.x)), -static_cast<int>(selectionPos_.x));
	selectionExt_.y = std::max (std::min (height, static_cast<int>(rows_) - static_cast<int>(selectionPos_.y)), -static_cast<int>(selectionPos_.y));
	update();
}

template <class T>
inline Widget* Pattern<T>::getPad (const size_t column, const size_t row) const
{
	return ((column < columns_) && (row < rows_) ? pads_[row][column] : nullptr);
}

template <class T>
inline void Pattern<T>::update ()
{
	for (size_t r = 0; r < rows_; ++r)
	{
		for (size_t c = 0; c < columns_; ++c)
		{
			pads_[r][c]->moveTo 
			(
				getXOffset() + getEffectiveWidth() * static_cast<double>(c) / static_cast<double>(columns_) + 0.01 * getEffectiveWidth() / static_cast<double>(columns_),
				getYOffset() + getEffectiveHeight() * static_cast<double>(r) / static_cast<double>(rows_) + 0.01 * getEffectiveHeight() / static_cast<double>(rows_)
			);

			pads_[r][c]->resize 
			(
				0.98 * getEffectiveWidth() / static_cast<double>(columns_),
				0.98 * getEffectiveHeight() / static_cast<double>(rows_)
			);
		}
	}
	Widget::update();
}

template <class T>
inline void Pattern<T>::onButtonPressed (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*>(event);
	if (!pev) return;

	// Calculate position
	const BUtilities::Point<size_t> p = getPadIndex (pev->getPosition().x, pev->getPosition().y);

	// Selection mode:
	if (isSelectMode()) select (p.x, p.y, 1, 1);

	// Default: Invert pad value
	else
	{
		T* w = dynamic_cast<T*>(pads_[p.y][p.x]);
		padOn_ = (w->getValue() == w->getMin());
		w->setValue (padOn_ ? w->getMax() : w->getMin());
	}

	Clickable::onButtonPressed (event);
}

template <class T>
inline void Pattern<T>::onPointerDragged (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*>(event);
	if (!pev) return;

	// Calculate position
	const BUtilities::Point<size_t> p = getPadIndex (pev->getPosition().x, pev->getPosition().y);
		
	// Selection mode: Drag selection
	if (isSelectMode())
	{
		select	(selectionPos_.x, 
				 selectionPos_.y, 
				 p.x + (p.x >= selectionPos_.x) - selectionPos_.x, 
				 p.y + (p.y >= selectionPos_.y) - selectionPos_.y);
	}

	// Default:
	else 
	{
		// Calculate previous position
		const BUtilities::Point<size_t> p2 = getPadIndex (pev->getPosition().x - pev->getDelta().x, pev->getPosition().y - pev->getDelta().y);
		T* w = dynamic_cast<T*>(pads_[p.y][p.x]);

		// Pad changed: Set or unset pad
		if (p != p2) w->setValue (padOn_ ? w->getMax() : w->getMin());
		
	}
	Draggable::onPointerDragged (event);
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
	return (editMode_ != MODE_EDIT) && (editMode_ != MODE_PASTE);
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
inline void Pattern<T>::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

template <class T>
inline void Pattern<T>::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::RectArea<> (x0, y0, width, height));
}

template <class T>
inline void Pattern<T>::draw (const BUtilities::RectArea<>& area)
	{
		if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

		if ((getWidth () >= 1) && (getHeight () >= 1))
		{
			// Draw super class widget elements first
			Widget::draw (area);

			cairo_t* cr = cairo_create (surface_);
			if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
			{
				// Limit cairo-drawing area
				cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
				cairo_clip (cr);

				const double x0 = getXOffset ();
				const double y0 = getYOffset ();
				const double w = getEffectiveWidth ();
				const double h = getEffectiveHeight ();

				if (isSelectMode() && (selectionExt_ != BUtilities::Point<int>()))
				{
					const double xs =	x0 + w * static_cast<double>(selectionPos_.x + (selectionExt_.x < 0)) / static_cast<double>(columns_);
					const double ys = 	y0 + h * static_cast<double>(selectionPos_.y + (selectionExt_.y < 0)) / static_cast<double>(rows_);
					const double ws = 	w * static_cast<double>(selectionExt_.x - (selectionExt_.x < 0)) / static_cast<double>(columns_);
					const double hs = 	h * static_cast<double>(selectionExt_.y - (selectionExt_.y < 0)) / static_cast<double>(rows_);
					const BStyles::Color color = getBgColors()[getStatus()].illuminate (BStyles::Color::highLighted);
					cairo_rectangle (cr, xs, ys, ws, hs);
					cairo_set_line_width (cr, 0.0);
					cairo_set_source_rgba (cr, CAIRO_RGBA (color));
					cairo_fill (cr);
				}

				cairo_destroy (cr);
			}
		}
	}

}

#endif /* BWIDGETS_PATTERN_HPP_ */
