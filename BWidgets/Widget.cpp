/* Widget.cpp
 * Copyright (C) 2018 - 2022 by Sven Jähnichen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "Widget.hpp"
#include "Supports/Linkable.hpp"
#include "Window.hpp"
#include "../BEvents/ExposeEvent.hpp"
#include <cstdint>
#include <string>

namespace BWidgets
{

Widget::Widget () : Widget (0.0, 0.0, BWIDGETS_DEFAULT_WIDTH, BWIDGETS_DEFAULT_HEIGHT) {}

Widget::Widget (const double x, const double y, const double width, const double height, uint32_t urid, std::string title) :
	Linkable(),
	Visualizable (width, height),
	EventMergeable(),
	urid_ (urid),
	position_ (x, y),
	stacking_ (STACKING_NORMAL),
	status_(BStyles::Status::STATUS_NORMAL),
	title_ (title),
	style_ ()
{

}

Widget::~Widget ()
{
	// Release from parent (and main) if still linked
	if (parent_) parent_->release (this);

	// Release children
	while (!children_.empty ()) release (children_.back ());
}

Widget* Widget::clone () const 
{
	Widget* w = new Widget (0.0, 0.0, BWIDGETS_DEFAULT_WIDTH, BWIDGETS_DEFAULT_HEIGHT, getUrid());
	w->copy (this);
	return w;
}

void Widget::copy (const Widget* that)
{
	Visualizable::operator= (*that);
	EventMergeable::operator= (*that);
	position_ = that->position_;
	status_ = that->status_;
	title_ = that->title_;
	style_ = that->style_;
	/*...*/
	update();
}

uint32_t Widget::getUrid() const
{
	return urid_;
}

void Widget::rename (std::string& title)
{
	title_ = title;
	update();
}

std::string Widget::getTitle () const
{
	return title_;
}

std::list<Linkable*>::iterator Widget::add (Linkable* child, std::function<void (Linkable* obj)> addfunc)
{
	// Only accept Widgets
	Widget* childWidget = dynamic_cast<Widget*> (child);
	if (!childWidget) return children_.end();

	std::list<Linkable*>::iterator it = Linkable::add 
	(
		child,
		[addfunc] (Linkable* l)
		{
			Widget* w = dynamic_cast<Widget*>(l);
			addfunc (l);
			if (w) w->update ();

			// TODO Stacking
		}
	);

	return it;
}

void Widget::release (std::function<void (Linkable* obj)> releasefunc)
{
	while (!children_.empty ()) release (children_.back (), releasefunc);
}

void Widget::release (Linkable* child, std::function<void (Linkable* obj)> releasefunc)
{
	Widget* childWidget = dynamic_cast<Widget*> (child);
	if (!childWidget) return;
	if (!Linkable::contains (child))
	{
		//std::cerr << "Msg from BWidgets::Widget::release(): Child " << child->name_ << ":" << &(*child)
		//		<< " is not a child of " << name_ << ":" << &(*this) << std::endl;
		return;

	}

	bool wasVisible = childWidget->isVisible ();
	childWidget->hide();
	Linkable::release
	(
		child,
		[releasefunc] (Linkable* l)
		{
			Widget* w = dynamic_cast<Widget*>(l);
			if (w && w->getMainWindow())
			{
				w->getMainWindow()->purgeEventQueue (w);
				w->getMainWindow()->getButtonGrabStack()->remove (w);
				w->getMainWindow()->getKeyGrabStack()->remove (w);
				w->main_ = nullptr;
				releasefunc (l);
			}
			return true;
		}
	);

	if (wasVisible) emitExposeEvent (childWidget->getArea());
}

void Widget::raise ()
{
	if (!parent_) return;
	if (getParent()->getChildren().size() < 2) return;

	std::list<Linkable*>::iterator lit = std::prev(getParent()->getChildren().end(), 2);
	for	(std::list<Linkable*>::iterator it = getParent()->getChildren().begin(); it != lit; ++it)
	{
		if (*it == this)
		{
			std::swap (*it, *(std::next (it)));
			Widget* parentWidget = getParentWidget();
			if (parentWidget && parentWidget->isVisible ()) parentWidget->emitExposeEvent ();
			break;
		}
	}
}

void Widget::drop ()
{
	if (!parent_) return;
	if (getParent()->getChildren().size() < 2) return;

	std::list<Linkable*>::iterator lit = std::prev(getParent()->getChildren().end());
	for	(std::list<Linkable*>::iterator it = std::next (getParent()->getChildren().begin()); it != lit; ++it)
	{
		if (*it == this)
		{
			std::swap (*it, *(std::prev (it)));
			Widget* parentWidget = getParentWidget();
			if (parentWidget && parentWidget->isVisible ()) parentWidget->emitExposeEvent ();
			break;
		}
	}
}

void Widget::dropToBack ()
{
	if (!parent_) return;
	if (getParent()->getChildren().size() < 2) return;

	std::list<Linkable*>::iterator it = std::find (getParent()->getChildren().begin(), getParent()->getChildren().end(), this);
	if (it != getParent()->getChildren().end())
	{
		getParent()->getChildren().erase (it);
		getParent()->getChildren().push_front (this);
		Widget* parentWidget = getParentWidget();
		if (parentWidget && parentWidget->isVisible ()) parentWidget->emitExposeEvent ();
	}
}

void Widget::raiseToFront ()
{
	if (!parent_) return;
	if (getParent()->getChildren().size() < 2) return;

	std::list<Linkable*>::iterator it = std::find (getParent()->getChildren().begin(), getParent()->getChildren().end(), this);
	if (it != getParent()->getChildren().end())
	{
		getParent()->getChildren().erase (it);
		getParent()->getChildren().push_back (this);
		Widget* parentWidget = getParentWidget();
		if (parentWidget && parentWidget->isVisible ()) parentWidget->emitExposeEvent ();
	}
}

Window* Widget::getMainWindow () const 
{
	return dynamic_cast<Window*> (getMain());
}

Widget* Widget::getParentWidget () const {return dynamic_cast<Widget*> (getParent());}

void Widget::show()
{
	if (isVisualizable()) return;

	Visualizable::setSupport (true);

	if (isVisible ())
	{
		// (Re-)draw children as they may become visible too
		forEachChild ([] (Linkable* l)
		{
			Widget* w = dynamic_cast<Widget*>(l);
			if (w && w->isVisible ()) w->draw (0, 0, w->getWidth (), w->getHeight ());
			return w && w->isVisible ();
		});

		// (Re-)draw this widget and post display
		update ();
	}
}

void Widget::hide()
{
	bool wasVisible = isVisible ();

	// Get area occupied by this widget and its children
	BUtilities::RectArea hideArea = getAbsoluteFamilyArea ([] (const Widget* w) {return w->isVisible();});
	Visualizable::setSupport (false);

	if (wasVisible && (this != dynamic_cast<Widget*> (getMainWindow())))
	{
		// Limit area to main boundaries
		hideArea.intersect (getMainWindow()->getAbsoluteArea());

		// Find closest parent that includes the area
		Widget* p = getParentWidget();
		for ( ; p && (!p->getAbsoluteArea().includes (hideArea)); p = p->getParentWidget()) {}

		// Redisplay hidden area
		if (p) p->emitExposeEvent ();
		else getMainWindow()->emitExposeEvent (hideArea);
	}
}

bool Widget::isVisible() const
{
	// Go backwards in widget tree until nullptr
	for (const Widget* w = this; w; w = w->getParentWidget())			
	{
		// widget invisible? -> break as invisible
		if (!w->isVisualizable()) return false;

		// main reached ? -> visible
		if (w == dynamic_cast<Widget*>(getMainWindow())) return true;

		// no main window -> break as invisible;
		if  (!w->getMainWindow()) return false;
	}

	// nullptr reached ? -> not connected to main -> invisible
	return false;						
}

void Widget::moveTo (const double x, const double y) {moveTo (BUtilities::Point (x, y));}

void Widget::moveTo (const BUtilities::Point& position)
{
	if ((position_.x != position.x) || (position_.y != position.y))
	{
		position_ = position;
		if (isVisible () && getParentWidget()) getParentWidget()->emitExposeEvent ();
	}
}

void Widget::moveRel (const double dx, const double dy) 
{
	moveTo (BUtilities::Point (dx + position_.x, dy + position_.y));
}

void Widget::moveRel (const BUtilities::Point& dpos) {moveTo (position_ + dpos);}

double Widget::left () 
{
	return (getParentWidget() ? getParentWidget()->getBorder().margin : 0.0);
}

double Widget::center () 
{
	return (getParentWidget() ? 0.5 * (getParentWidget()->getWidth() - getWidth()) : 0.0);
}

double Widget::right () 
{
	return (getParentWidget() ? getParentWidget()->getWidth() - getParentWidget()->getBorder().margin - getWidth() : 0.0);
}

double Widget::top () 
{
	return (getParentWidget() ? getParentWidget()->getBorder().margin : 0.0);
}

double Widget::middle () 
{
	return (getParentWidget() ? 0.5 * (getParentWidget()->getHeight() - getHeight()) : 0.0);
}

double Widget::bottom () 
{
	return (getParentWidget() ? getParentWidget()->getHeight() - getParentWidget()->getBorder().margin - getHeight() : 0.0);
}

BUtilities::Point Widget::getPosition () const 
{
	return position_;
}

BUtilities::RectArea Widget::getArea () const 
{
	return BUtilities::RectArea (position_, position_ + extends_);
}

BUtilities::Point Widget::getAbsolutePosition () const
{
	BUtilities::Point p = BUtilities::Point (0, 0);
	for (const Widget* w = this; w->getParentWidget(); w = w->getParentWidget()) p += w->getPosition();
	return p;
}

BUtilities::RectArea Widget::getAbsoluteArea () const
{
	BUtilities::RectArea a = getArea();
	a.moveTo (getAbsolutePosition ());
	return a;
}

double Widget::getXOffset () 
{
	if (style_.contains (BUtilities::Urid::urid (STYLEPROPERTY_BORDER_URI)))
	{
		BStyles::Border border = getBorder();
		return border.margin + border.line.width + border.padding;
	}
	return 0.0;
}

double Widget::getYOffset () 
{
	return getXOffset();
}

double Widget::getEffectiveWidth ()
{
	double totalBorderWidth = getXOffset ();
	return (getWidth () > 2 * totalBorderWidth ? getWidth () - 2 * totalBorderWidth : 0);
}

double Widget::getEffectiveHeight ()
{
	double totalBorderHeight = getYOffset ();
	return (getHeight () > 2 * totalBorderHeight ? getHeight () - 2 * totalBorderHeight : 0);
}

BUtilities::RectArea Widget::getEffectiveArea ()
{
	return BUtilities::RectArea (getPosition().x + getXOffset(), getPosition().y + getYOffset(), getEffectiveWidth(), getEffectiveHeight());
}

void Widget::setStatus (const BStyles::Status status)
{
	if (status != status_)
	{
		status_ = status;
		update ();
	}
}

BStyles::Status Widget::getStatus () const 
{
	return status_;
}

void Widget::setStacking (const Widget::Stacking stacking) 
{
	stacking_ = stacking;
}

Widget::Stacking Widget::getStacking () const 
{
	return stacking_;
}

void Widget::setStyle (const BStyles::Style& style)
{
	//if (style != style_)
	{
		style_ = style;

		// Pass child styles to respective children
		for (Linkable* c : children_)
		{
			Widget* w = dynamic_cast<Widget*>(c);
			if (w)
			{
				BStyles::Style::iterator it = style_.find (w->getUrid());
				if (it != style_.end() && style_.isStyle (it)) w->setStyle (it->second.get<BStyles::Style>());
			}
		}

		//update();
	}
}

BStyles::Border Widget::getBorder() const
{
	return style_.getBorder();
}

void Widget::setBorder(const BStyles::Border& border)
{
	if (border != getBorder())
	{
		style_.setBorder (border);
		update();
	}
}

BStyles::Fill Widget::getBackground() const
{
    return style_.getBackground();
}

void Widget::setBackground(const BStyles::Fill& fill)
{
    if (fill != getBackground())
	{
		style_.setBackground(fill);
		update();
	}
}

BStyles::Font Widget::getFont() const
{
    return style_.getFont();
}

void Widget::setFont(const BStyles::Font& font)
{
    if (font != getFont())
	{
		style_.setFont(font);
		update();
	}
}

BStyles::ColorMap Widget::getFgColors() const
{
    return style_.getFgColors();
}

void Widget::setFgColors (const BStyles::ColorMap& colors)
{
    if (colors != getFgColors())
	{
		style_.setFgColors(colors);
		update();
	}
}

BStyles::ColorMap Widget::getBgColors() const
{
    return style_.getBgColors();
}

void Widget::setBgColors (const BStyles::ColorMap& colors)
{
    if (colors != getBgColors())
	{
		style_.setBgColors(colors);
		update();
	}
}

BStyles::ColorMap Widget::getTxColors() const
{
    return style_.getTxColors();
}

void Widget::setTxColors (const BStyles::ColorMap& colors)
{
    if (colors != getTxColors())
	{
		style_.setTxColors(colors);
		update();
	}
}

void Widget::emitExposeEvent ()
{
	BUtilities::RectArea area = getFamilyArea ([] (const Widget* w) {return w->isVisible();});
	area.moveTo (getAbsolutePosition ());
	emitExposeEvent (area);
}

void Widget::emitExposeEvent (const BUtilities::RectArea& area)
{
	Window* main = getMainWindow();
	if (main)
	{
		BEvents::ExposeEvent* event = new BEvents::ExposeEvent (main, this, BEvents::Event::EXPOSE_REQUEST_EVENT, area);
		main->addEventToQueue (event);
	}
}

Widget* Widget::getWidgetAt	(const BUtilities::Point& position, 
							 std::function<bool (Widget* widget)> func,
							 std::function<bool (Widget* widget)> passfunc)
{
	BUtilities::RectArea absarea = getAbsoluteArea ();
	return getWidgetAt (getAbsolutePosition () + position, absarea, absarea, func, passfunc);
}

Widget* Widget::getWidgetAt	(const BUtilities::Point& abspos, 
							 const BUtilities::RectArea& outerArea,
			    			 const BUtilities::RectArea& area, 
							 std::function<bool (Widget* widget)> func,
							 std::function<bool (Widget* widget)> passfunc)
{
	BUtilities::RectArea a = (getStacking() == STACKING_ESCAPE ? outerArea : area);
	BUtilities::RectArea thisArea = getArea();
	thisArea.moveTo (getAbsolutePosition());
	thisArea.intersect (a);
	if (getMainWindow())
	{
		Widget* finalw =
		(
			((thisArea != BUtilities::RectArea ()) && thisArea.contains (abspos)) ? 
			(
				func (this) ?
				this : 
				(
					passfunc (this) ?
					nullptr :
					getMainWindow() // "Sink" to block passing events
				)
			) :
			nullptr);

		for (Linkable* l : children_)
		{
			Widget* w = dynamic_cast<Widget*> (l);
			if (w)
			{
				Widget* nextw = w->getWidgetAt (abspos, outerArea, thisArea, func, passfunc);
				if (nextw) finalw = nextw;
			}
		}
		return finalw;
	}

	else return nullptr;
}

BUtilities::RectArea Widget::getFamilyArea (std::function<bool (const Widget* widget)> func) const
{
	BUtilities::RectArea a = getAbsoluteFamilyArea (func);
	a.moveTo (a.getPosition() - getAbsolutePosition());
	return a;
}

BUtilities::RectArea Widget::getAbsoluteFamilyArea (std::function<bool (const Widget* widget)> func) const
{
	BUtilities::RectArea a = getAbsoluteArea();
	forEachChild 
	(
		[&a, func] (Linkable* l)
		{
			Widget* w = dynamic_cast<Widget*> (l);
			if (w)
			{
				bool check = func (w);
				if (check && (w->getStacking() == STACKING_ESCAPE )) a.extend (w->getAbsoluteArea());
				return check;
			}
			return false;
		}
	);

	return a;
}

void Widget::display (cairo_surface_t* surface, const BUtilities::RectArea& area)
{
	if (isVisible())
	{
		// Calculate absolute area position and start private core method
		BUtilities::RectArea absArea = area;
		absArea.moveTo (absArea.getPosition() + getAbsolutePosition());
		display (surface, absArea, absArea);
	}
}

void Widget::display (cairo_surface_t* surface, const BUtilities::RectArea& outerArea, const BUtilities::RectArea& area)
{
	BUtilities::RectArea a = (getStacking() == STACKING_ESCAPE ? outerArea : area);
	BUtilities::RectArea thisArea = getArea(); 
	thisArea.moveTo (getAbsolutePosition());
	a.intersect (thisArea);
	if (isVisible())
	{
		if (a != BUtilities::RectArea ())
		{
			// Update draw
			if (scheduleDraw_) draw (BUtilities::RectArea (0, 0, getWidth (), getHeight ()));

			// Copy widgets surface onto main surface
			cairo_t* cr = cairo_create (surface);
			cairo_set_source_surface (cr, cairoSurface(), thisArea.getX(), thisArea.getY());
			cairo_rectangle (cr, a.getX (), a.getY (), a.getWidth (), a.getHeight ());
			cairo_fill (cr);
			cairo_destroy (cr);
		}

		for (Linkable* l : children_)
		{
			Widget* w = dynamic_cast<Widget*> (l);
			if (w) w->display (surface, outerArea, a);
		}
	}
}

void Widget::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

void Widget::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::RectArea (x0, y0, width, height));
}

void Widget::draw (const BUtilities::RectArea& area)
{
	Visualizable::draw (area);

	if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return;
	cairo_surface_clear (cairoSurface());
	cairo_t* cr = cairo_create (cairoSurface());

	if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
	{
		// Limit cairo-drawing area
		cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
		cairo_clip (cr);

		BStyles::Border border = getBorder();
		BStyles::Fill background = getBackground();

		// Draw background
		double innerBorders = getXOffset ();
		double innerRadius = (border.radius > border.padding ? border.radius - border.padding : 0);

		if ((getEffectiveWidth () > 0) && (getEffectiveHeight () > 0))
		{
			background.setCairoSource (cr);
			
			// If drawing area < background are, draw only a rectangle for the drawing area (faster)
			if
			(
				(area.getX () >= innerBorders) && (area.getX () + area.getWidth () <= getWidth () - innerBorders) &&
				(area.getY () >= innerBorders) && (area.getY () + area.getHeight () <= getHeight () - innerBorders)
			)
			{
				cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			}
			else
			{
				cairo_rectangle_rounded (cr, innerBorders, innerBorders, getEffectiveWidth (), getEffectiveHeight (), innerRadius, 0b1111);
			}
			cairo_fill (cr);
			

		}

		// Draw border frame
		double outerBorders = border.margin;
		BStyles::Color lc = border.line.color;

		if
		(
			(lc.alpha != 0.0) &&
			(border.line.width != 0.0) &&
			(getWidth () >= 2 * outerBorders) &&
			(getHeight () >= 2 * outerBorders)
		)
		{
			double lw = border.line.width;
			cairo_rectangle_rounded
			(
				cr,
				outerBorders + lw / 2,
				outerBorders + lw / 2,
				getWidth () - 2 * outerBorders - lw,
				getHeight () - 2 * outerBorders - lw,
				border.radius, 0b1111);

			cairo_set_source_rgba (cr, CAIRO_RGBA (lc));
			cairo_set_line_width (cr, lw);
			cairo_stroke (cr);
		}
	}

	cairo_destroy (cr);
}

}
