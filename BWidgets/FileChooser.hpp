/* FileChooser.hpp
 * Copyright (C) 2019 - 2022  Sven Jähnichen
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

#ifndef BWIDGETS_FILECHOOSER_HPP_
#define BWIDGETS_FILECHOOSER_HPP_

#include <cairo/cairo.h>
#include <cstddef>
#include <initializer_list>
#include <regex>
#include <dirent.h>
#include <sys/stat.h>
#include "Box.hpp"
#include "Frame.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/Closeable.hpp"
#include "Symbol.hpp"
#include "TextButton.hpp"
#include "EditLabel.hpp"
#include "ComboBox.hpp"
#include "MessageBox.hpp"

#ifndef BWIDGETS_DEFAULT_FILECHOOSER_WIDTH
#define BWIDGETS_DEFAULT_FILECHOOSER_WIDTH 400
#endif

#ifndef BWIDGETS_DEFAULT_FILECHOOSER_HEIGHT
#define BWIDGETS_DEFAULT_FILECHOOSER_HEIGHT 320
#endif

#ifndef PATH_SEPARATOR
#define PATH_SEPARATOR "/"
#endif

namespace BWidgets
{

/**
 *  @brief  Menu widget for selection of a file.
 *
 *  The %FileChooser is a Valueable Widget based on Frame. It consists of:
 *  * a Label to display the current path,
 *  * a new folder SymbolButton,
 *  * a ListBox with the (filtered) content of the current path,
 *  * a EditLabel to display or edit the selected filename,
 *  * a ComboBox to select filename filter options,
 *  * a "Cancel" button,
 *  * an "OK" / "Open" button,
 *
 *  The ListBox fascilitates selection of files and the navigation through
 *  the file system. A selected file is also shown in the EditLabel.
 *  
 *  Clicking on the new folder SymbolButton opens a dialog and the user is
 *  asked to enter a new folder name. The new folder is created within the
 *  current path shown in the Label.
 *
 *  Clicking on "Cancel" will set the widget value to "" and a 
 *  CloseRequestEvent is emitted.
 *
 *  Clicking on "OK" / "Open" will set the widget value to path + filename 
 *  and a CloseRequestEvent is emitted.
 */
class FileChooser : public Frame, public ValueableTyped<std::string>, public Closeable
{
public:

	/**
	 *  @brief  Filter data type consisting of a regex and a name.
	 */
	typedef std::pair<std::string, std::regex> Filter;

protected:
	std::map<std::string, std::regex> filters_;
	std::vector<std::string> dirs_;
	std::vector<std::string> files_;

public:

	Label pathNameBox;
	SymbolButton newFolderButton;
	ListBox fileListBox;
	Label fileNameLabel;
	EditLabel fileNameBox;
	ComboBox filterComboBox;
	TextButton cancelButton;
	TextButton okButton;
	Label fileListBoxFileLabel;
	Label fileListBoxDirLabel;
	Label filterComboBoxFilterLabel;

	MessageBox confirmBox;

	Box createBox;
	Label createLabel;
	EditLabel createInput;
	Label createError;

	/**
	 *  @brief  Constructs a default FileChooser object.
	 * 
	 */
	FileChooser ();

	/**
	 *  @brief  Constructs a default FileChooser object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	FileChooser (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Constructs a FileChooser object with default size
	 *  @param path  File path.
	 *  @param filters  Optional, initializer list with filename search
	 *  filters.
     *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %FileChooser title.
	 */
	FileChooser	(const std::string& path, std::initializer_list<Filter> filters = {},
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Constructs a FileChooser object with default size
	 *  @param x  %FileChooser X origin coordinate.
	 *  @param y  %FileChooser Y origin coordinate.
	 *  @param width  %FileChooser width.
	 *  @param height  %FileChooser height.
	 *  @param path  File path.
	 *  @param filters  Optional, initializer list with filename search
	 *  filters.
     *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %FileChooser title.
	 */
	FileChooser	(const double x, const double y, const double width, const double height,
				 std::string path = ".", std::initializer_list<Filter> filters = {Filter {BUtilities::Dictionary::get ("All files"), std::regex (".*")}},
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");


	/**
	 *  @brief  Creates a clone of the %FileChooser. 
	 *  @return  Pointer to the new %FileChooser.
	 *
	 *  Creates a clone of this widget by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %FileChooser. 
	 *  @param that  Other %FileChooser.
	 *
	 *  Copies all properties from another %FileChooser. But NOT its linkage.
	 */
	void copy (const FileChooser* that);

	/**
	 *  @brief  Sets the current file path.
	 *  @param path  File path.
	 */
	virtual void setPath (const std::string& path);

	/**
	 *  @brief  Gets the current file path.
	 *  @return  Current file path.
	 */
	std::string getPath () const;

	/**
	 *  @brief  Sets the file name.
	 *  @param filename  File name.
	 */
	virtual void setFileName (const std::string& filename);

	/**
	 *  @brief  Gets the selected file name.
	 *  @return  Selected file name.
	 */
	std::string getFileName () const;

	/**
	 *  @brief  Sets the map of filename search filters.
	 *  @param filters  std::map with filter name and regex filter.
	 */
	void setFilter (const std::map<Filter::first_type, Filter::second_type>& filters);

	/**
	 *  @brief  Gets the map of filename search filters.
	 *  @return  std::map with filter name and regex filter.
	 */
	std::map<Filter::first_type, Filter::second_type> getFilters () const;

	/**
	 *  @brief  Selects and activates a filter.
	 *  @param name Filter name
	 */
	virtual void selectFilter (const std::string& name);
	
	/**
     *  @brief  Optimizes the widget extends.
     *
	 *  Resizes the widget to include all direct children into the widget
	 *  area. Resizes the widget to its standard size if this widget doesn't 
	 *  have any additional children (execept the built-in child widgets).
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
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

protected:

	static void fileListBoxChangedCallback (BEvents::Event* event);
	static void filterComboBoxChangedCallback (BEvents::Event* event);
	static void cancelButtonClickedCallback (BEvents::Event* event);
	static void okButtonClickedCallback (BEvents::Event* event);
	static void confirmClickedCallback (BEvents::Event* event);
	static void createClickedCallback (BEvents::Event* event);
	static void newFolderButtonClickedCallback (BEvents::Event* event);

	void enterDir ();

	void processFileSelected();


	virtual std::function<void (BEvents::Event*)> getFileListBoxClickedCallback();

	bool isDir (const std::string& path, const std::string& name) const;
};

inline FileChooser::FileChooser () : 
	FileChooser (0.0, 0.0, BWIDGETS_DEFAULT_FILECHOOSER_WIDTH, BWIDGETS_DEFAULT_FILECHOOSER_HEIGHT, "", {}, BUTILITIES_URID_UNKNOWN_URID, "") 
{

}

inline FileChooser::FileChooser	(const uint32_t urid, const std::string& title) :
	FileChooser (0, 0, BWIDGETS_DEFAULT_FILECHOOSER_WIDTH, BWIDGETS_DEFAULT_FILECHOOSER_HEIGHT, "", {}, urid, title) 
{

}

inline FileChooser::FileChooser	(const std::string& path, std::initializer_list<Filter> filters, uint32_t urid, std::string title) :
	FileChooser (0, 0, BWIDGETS_DEFAULT_FILECHOOSER_WIDTH, BWIDGETS_DEFAULT_FILECHOOSER_HEIGHT, path, filters, urid, title) 
{

}

inline FileChooser::FileChooser	(const double x, const double y, const double width, const double height,
				 				 std::string path, std::initializer_list<Filter> filters, uint32_t urid, std::string title) :
		Frame (x, y, width, height, urid, title),
		ValueableTyped<std::string> (path),
		Closeable (),
		filters_ (),
		dirs_ (),
		files_ (),

		pathNameBox ("", BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/textbox"), ""),
		newFolderButton (Symbol::SymbolType::newFolder, false, false, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/button"), ""),
		fileListBox ({}, 0, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/listbox"), ""),
		fileNameLabel (BUtilities::Dictionary::get ("File") + ":", BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), ""),
		fileNameBox ("", BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/textbox"), ""),
		filterComboBox ({}, 0, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/combobox"), ""),
		cancelButton (BUtilities::Dictionary::get ("Cancel"), false, false, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/button"), ""),
		okButton (BUtilities::Dictionary::get ("OK"), false, false, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/button"), ""),
		fileListBoxFileLabel ("", BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/listbox/item/file"), ""),
		fileListBoxDirLabel ("", BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/listbox/item/dir"), ""),
		filterComboBoxFilterLabel ("", BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "combobox/listbox/item"), ""),

		confirmBox	(Symbol::SymbolType::warn, "", "", 
					 {BUtilities::Dictionary::get ("Cancel"), BUtilities::Dictionary::get ("OK")}, 
					 BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/box"), ""),
		
		createBox	({BUtilities::Dictionary::get ("Cancel"), BUtilities::Dictionary::get ("OK")}, 
					 BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/box"), ""),
		createLabel ("", BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), ""),
		createInput ("", BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/textbox"), ""),
		createError ("", BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), "")
{
	setPath (path);
	enterDir();

	pathNameBox.setBorder (BStyles::Border (BStyles::greyLine1pt, 0.0, 3.0));
	fileNameBox.setBorder (BStyles::Border (BStyles::greyLine1pt, 0.0, 3.0));
	createInput.setBorder (BStyles::Border (BStyles::greyLine1pt, 0.0, 3.0));
	fileNameLabel.setBorder(BStyles::Border (BStyles::noLine, 0.0, 4.0));

	createBox.setStacking (StackingType::escape);
	confirmBox.setStacking (StackingType::escape);

	setBackground (BStyles::Fill(getBgColors()[BStyles::Status::normal].illuminate (-0.75)));
	setBorder (BStyles::Border  (BStyles::Line (getBgColors()[BStyles::Status::normal].illuminate (BStyles::Color::highLighted), 1.0), 0.0, 0.0));

	fileListBox.setCallbackFunction (BEvents::Event::EventType::ValueChangedEvent, fileListBoxChangedCallback);
	filterComboBox.setCallbackFunction (BEvents::Event::EventType::ValueChangedEvent, filterComboBoxChangedCallback);
	cancelButton.setCallbackFunction (BEvents::Event::EventType::ValueChangedEvent, cancelButtonClickedCallback);
	okButton.setCallbackFunction (BEvents::Event::EventType::ValueChangedEvent, okButtonClickedCallback);
	confirmBox.setCallbackFunction (BEvents::Event::EventType::ValueChangedEvent, confirmClickedCallback);
	newFolderButton.setCallbackFunction (BEvents::Event::EventType::ValueChangedEvent, newFolderButtonClickedCallback);
	createBox.setCallbackFunction (BEvents::Event::EventType::ValueChangedEvent, createClickedCallback);

	for (const Filter& f : filters) 
	{
		filters_[f.first] = f.second;
		filterComboBox.addItem (f.first);
	}
	filterComboBox.setValue (1);

	createBox.add (&createLabel);
	createBox.add (&createInput);
	createBox.add (&createError);

	add (&pathNameBox);
	add (&fileListBox);
	add (&fileNameLabel);
	add (&fileNameBox);
	add (&cancelButton);
	add (&okButton);
	add (&filterComboBox);
	add (&newFolderButton);
}

inline Widget* FileChooser::clone () const 
{
	Widget* f = new FileChooser (urid_, title_);
	f->copy (this);
	return f;
}

inline void FileChooser::copy (const FileChooser* that)
{
	filters_ = that->filters_;
	dirs_ = that->dirs_;
	files_ = that->files_;

	pathNameBox.copy (&that->pathNameBox);
	newFolderButton.copy (&that->newFolderButton);
	fileListBox.copy (&that->fileListBox);
	fileNameLabel.copy (&that->fileNameLabel);
	fileNameBox.copy (&that->fileNameBox);
	filterComboBox.copy (&that->filterComboBox);
	cancelButton.copy (&that->cancelButton);
	okButton.copy (&that->okButton);
	fileListBoxFileLabel.copy (&that->fileListBoxFileLabel);
	fileListBoxDirLabel.copy (&that->fileListBoxDirLabel);
	filterComboBoxFilterLabel.copy (&that->filterComboBoxFilterLabel);

	release (&confirmBox); 
	confirmBox.copy (&that->confirmBox);
	if (that->contains (&that->confirmBox)) add (&confirmBox);

	release (&createBox); 
	createBox.copy (&that->createBox);
	if (that->contains (&that->createBox)) add (&createBox);
	createLabel.copy (&that->createLabel);
	createInput.copy (&that->createInput);
	createError.copy (&that->createError);

	Closeable::operator= (*that);
	ValueableTyped<std::string>::operator= (*that);
	Frame::copy (that);
}

inline void FileChooser::setPath (const std::string& path)
{
	if (path != pathNameBox.getText())
	{
		char buf[PATH_MAX];
		char *rp = realpath(path.c_str(), buf);
		if (rp) pathNameBox.setText (rp);
		else pathNameBox.setText (path);

		update();
	}
}

inline std::string FileChooser::getPath () const 
{
	return pathNameBox.getText();
}

inline void FileChooser::setFileName (const std::string& filename)
{
	if (filename != fileNameBox.getText())
	{
		fileNameBox.setText (filename);
		fileListBox.setValue (filename);
	}
}

inline std::string FileChooser::getFileName () const 
{
	return fileNameBox.getText();
}

inline void FileChooser::setFilter (const std::map<Filter::first_type, Filter::second_type>& filters)
{
	this->filters_ = filters;

	filterComboBox.deleteItem();
	for (const Filter& f : filters) filterComboBox.addItem (f.first);
	filterComboBox.setValue (1);

	enterDir();
	update ();
}

inline std::map<FileChooser::Filter::first_type, FileChooser::Filter::second_type> FileChooser::getFilters () const 
{
	return filters_;
	}

inline void FileChooser::selectFilter (const std::string& name)
{
	filterComboBox.setValue (name);
	enterDir();
	update();
}

inline void FileChooser::resize ()
{
	// Resize to default size first
	resize (BWIDGETS_DEFAULT_FILECHOOSER_WIDTH, BWIDGETS_DEFAULT_FILECHOOSER_HEIGHT);

	// Resize to fit all children widgets
	BUtilities::Area<> a = BUtilities::Area<>();
	for (Linkable* c : children_)
	{
		Widget* w = dynamic_cast<Widget*>(c);
		if (w) a.extend (BUtilities::Area<>(w->getPosition(), w->getPosition() + w->getExtends()));
	}

	resize (a.getExtends() + BUtilities::Point<> (BWIDGETS_DEFAULT_MENU_PADDING + getXOffset(), BWIDGETS_DEFAULT_MENU_PADDING + getYOffset()));
}

inline void FileChooser::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void FileChooser::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void FileChooser::update ()
{
	const double x0 = getXOffset();
	const double y0 = getYOffset();
	const double w = getEffectiveWidth();
	const double h = getEffectiveHeight();

	if ((w >= 40) && (h >= 20))
	{
		const size_t val = fileListBox.getValue();
		if ((val == 0) || (val > dirs_.size())) okButton.label.setText (BUtilities::Dictionary::get ("OK"));
		else okButton.label.setText (BUtilities::Dictionary::get ("Open"));
		//cancelButton.label.setText(BUtilities::Dictionary::get ("Cancel"));

		// Get extends first
		okButton.resize();
		cancelButton.resize ();
		double okWidth = (okButton.getWidth() > cancelButton.getWidth() ? okButton.getWidth() : cancelButton.getWidth()) + 4;
		double okHeight = (okButton.getHeight() > cancelButton.getHeight() ? okButton.getHeight() : cancelButton.getHeight()) + 4;
		pathNameBox.resize();
		double pathNameHeight = pathNameBox.getHeight();
		fileNameBox.resize();
		double fileNameHeight = fileNameBox.getHeight();
		fileNameLabel.resize();
		double fileNameWidth = fileNameLabel.getWidth();

		pathNameBox.moveTo (x0 + 10, y0 + 10);
		pathNameBox.resize (w - pathNameHeight - 30, pathNameHeight);

		newFolderButton.moveTo (x0 + w - 12 - pathNameHeight, y0 + 8);
		newFolderButton.resize (pathNameHeight + 4, pathNameHeight + 4);

		okButton.moveTo (x0 + w - okWidth - 10, y0 + h - okHeight - 10);
		okButton.resize (okWidth, okHeight);

		cancelButton.moveTo (x0 + w - 2 * okWidth - 20, y0 + h - okHeight - 10);
		cancelButton.resize (okWidth, okHeight);

		fileNameLabel.moveTo (x0 + 10, y0 + h - okHeight - fileNameHeight - 20);
		fileNameLabel.resize (fileNameWidth, fileNameHeight);

		fileNameBox.moveTo (x0 + fileNameWidth + 30, y0 + h - okHeight - fileNameHeight - 20);
		fileNameBox.resize (w - fileNameWidth - 40, fileNameHeight);

		filterComboBox.moveTo (x0 + 10, y0 + h - okHeight - 10);
		filterComboBox.resize (w - 2 * okWidth - 40, okHeight);
		filterComboBox.setItemHeight (okHeight);
		filterComboBox.resizeItems();
		filterComboBox.resizeListBox (BUtilities::Point<> (w - 2 * okWidth - 40, filters_.size() * okHeight + 20));

		okButton.show();
		cancelButton.show();
		fileNameLabel.show();
		fileNameBox.show();
		filterComboBox.show ();

		if (h > pathNameHeight + okHeight + fileNameHeight + 50)
		{
			fileListBox.moveTo (x0 + 10, y0 + pathNameHeight + 20);
			fileListBox.resize (w - 20, h - pathNameHeight - okHeight - fileNameHeight - 50);
			fileListBox.setItemHeight (20);
			fileListBox.resizeItems();
			fileListBox.show();
		}
		else fileListBox.hide();

		confirmBox.resize();
		confirmBox.moveTo (0.5 * getWidth() - 0.5 * confirmBox.getWidth(), 0.5 * getHeight() - 0.5 * confirmBox.getHeight());
		confirmBox.show();

		createLabel.resize();
		createInput.resize();
		createError.resize();
		const double createLabelsWidth = (createLabel.getWidth() > createError.getWidth() ? createLabel.getWidth() : createError.getWidth());
		const double createBoxWidth = (createLabelsWidth + 40 > 2 * okWidth + 60 ? createLabelsWidth + 40 : 2 * okWidth + 60);
		const double createBoxHeight = createLabel.getHeight() + createInput.getHeight() + createError.getHeight() + okHeight + 80;
		createBox.resize (createBoxWidth, createBoxHeight);
		createBox.moveTo (0.5 * getWidth() - 0.5 * createBoxWidth, 0.5 * getHeight() - 0.5 * createBoxHeight);
		createLabel.moveTo (20, 20);
		createInput.resize (createBoxWidth - 40, createInput.getHeight());
		createInput.moveTo (20, 30 + createLabel.getHeight());
		createError.moveTo (20, 40 + createLabel.getHeight() + createInput.getHeight());
		createBox.show();
	}

	else
	{
		okButton.hide();
		cancelButton.hide();
		fileListBox.hide();
		fileNameLabel.hide();
		fileNameBox.hide();
		filterComboBox.hide ();
		confirmBox.hide();
		createBox.hide();
	}

	Widget::update();
}

inline void FileChooser::fileListBoxChangedCallback (BEvents::Event* event)
{
	if (!event) return;
	ListBox* w = dynamic_cast<ListBox*>(event->getWidget());
	if (!w) return;
	FileChooser* fc = dynamic_cast<FileChooser*>(w->getParent());
	if (!fc) return;

	const size_t val = w->getValue();

	if ((val != 0) && (!fc->fileNameBox.getEditMode()))
	{
		// Directory selected -> one click chdir
		if (val <= fc->dirs_.size())
		{
			fc->fileNameBox.setText ("");
			BEvents::ValueChangeTypedEvent<bool> dummyEvent = BEvents::ValueChangeTypedEvent<bool> (&fc->okButton, true);
			fc->okButtonClickedCallback (&dummyEvent);
		}

		// File selected
		else
		{
			Label* l = dynamic_cast<Label*>(w->getItem (val));
			if (l) fc->setFileName (l->getText());
		}

		fc->update();
	}
}

inline void FileChooser::filterComboBoxChangedCallback (BEvents::Event* event)
{
	if (!event) return;
	ComboBox* w = dynamic_cast<ComboBox*>(event->getWidget());
	if (!w) return;
	FileChooser* fc = (FileChooser*)w->getParent();
	if (!fc) return;

	fc->enterDir();
	fc->update();
}

inline void FileChooser::cancelButtonClickedCallback (BEvents::Event* event)
{
	if (!event) return;
	TextButton* w = dynamic_cast<TextButton*>(event->getWidget());
	if (!w) return;
	FileChooser* fc = dynamic_cast<FileChooser*>(w->getParent());
	if (!fc) return;

	fc->setValue ("");
	fc->postCloseRequest();
}

inline void FileChooser::okButtonClickedCallback (BEvents::Event* event)
{
	BEvents::ValueChangeTypedEvent<bool>* vev = dynamic_cast<BEvents::ValueChangeTypedEvent<bool>*>(event);
	if (!vev) return;
	if (!vev->getValue()) return;
	TextButton* w = dynamic_cast<TextButton*>(event->getWidget());
	if (!w) return;
	FileChooser* fc = dynamic_cast<FileChooser*>(w->getParent());
	if (!fc) return;
	
	const size_t lb = fc->fileListBox.getValue();

	if (lb != 0)
	{
		// Dircectory selected: Open directory
		if (lb <= fc->dirs_.size())
		{
			Label* l = dynamic_cast<Label*>(fc->fileListBox.getItem (lb));
			if (l)
			{
				std::string newPath = fc->getPath() + PATH_SEPARATOR + l->getText();
				char buf[PATH_MAX];
					char *rp = realpath(newPath.c_str(), buf);
					if (rp) fc->setPath (rp);

				fc->enterDir();
				fc->update();
			}
		}

		// File selected: OK on file
		else fc->processFileSelected();
	}

	// File name set: OK on file
	else if (fc->fileNameBox.getText() != "") fc->processFileSelected();
}

inline void FileChooser::confirmClickedCallback (BEvents::Event* event)
{
	if (!event) return;
	MessageBox* w = dynamic_cast<MessageBox*>(event->getWidget());
	if (!w) return;
	FileChooser* fc = dynamic_cast<FileChooser*>(w->getParentWidget());
	if (!fc) return;

	const size_t button = fc->confirmBox.getValue();

	// Cancel
	if (button == 1.0)
	{
		w->setValue (0.0);
		fc->release (&fc->confirmBox);
	}

	// OK
	else if (button == 2.0)
	{
		w->setValue (0.0);
		fc->setValue (fc->getPath() + PATH_SEPARATOR + fc->getFileName());
		fc->postCloseRequest();
	}
}

inline void FileChooser::createClickedCallback (BEvents::Event* event)
{
	if (!event) return;
	Box* w = dynamic_cast<Box*>(event->getWidget());
	if (!w) return;
	FileChooser* fc = dynamic_cast<FileChooser*>(w->getParentWidget());
	if (!fc) return;

	const size_t button = fc->createBox.getValue();

	// Cancel
	if (button == 1.0)
	{
		w->setValue (0.0);
		fc->release (&fc->createBox);
	}

	// OK
	else if (button == 2.0)
	{
		w->setValue (0.0);
		const std::string newPath = fc->getPath() + PATH_SEPARATOR + fc->createInput.getText();
		if (!mkdir (newPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
		{
			fc->createError.hide();
			fc->enterDir();
			fc->release (&fc->createBox);
		}

		else
		{
			fc->createError.setText (BUtilities::Dictionary::get ("Error") + ": " + BUtilities::Dictionary::get ("Can't create new folder") + ".");
			fc->createError.show();
		}

		fc->update ();
	}
}

inline void FileChooser::newFolderButtonClickedCallback (BEvents::Event* event)
{
	if (!event) return;
	TextButton* w = (TextButton*)event->getWidget();
	if (!w) return;
	FileChooser* fc = (FileChooser*)w->getParent();
	if (!fc) return;

	if (!fc->contains (&fc->createBox))
	{
		fc->createLabel.setText (BUtilities::Dictionary::get ("Create new folder") + ":");
		fc->createInput.setText ("");
		fc->createError.setText (BUtilities::Dictionary::get ("Error") + ": " + BUtilities::Dictionary::get ("Can't create new folder") + ".");
		fc->createError.hide();
		fc->add (&fc->createBox);
		fc->update();
	}
}

inline bool FileChooser::isDir (const std::string& path, const std::string& name) const
{
	std::string full = (path == PATH_SEPARATOR ? path : path + PATH_SEPARATOR) + name;
	struct stat sb;
        if (stat (full.c_str(), &sb)) return false;
	if (S_ISDIR(sb.st_mode)) return true;
	return false;
}

inline void FileChooser::enterDir ()
{
	std::vector<std::string> newFiles;
	std::vector<std::string> newDirs;
	DIR *dir = opendir (getPath().c_str());

	// Scan directory
	// TODO Use C++17 for future versions
	if (dir)
	{
		for (struct dirent* entry = readdir(dir); entry ; entry = readdir(dir))
		{
			if (isDir (getPath(), entry->d_name))
			{
				std::string s = entry->d_name;
				if ((std::regex_match (s, std::regex ("(\\.{1,2})|([^\\.].*)"))))	// Exclude hidden
				{
					newDirs.push_back (entry->d_name);
				}
			}

			else
			{
				std::string s = entry->d_name;
				if (!std::regex_match (s, std::regex ("\\..*")))	// Exclude hidden
				{
					if (filters_.empty()) newFiles.push_back (s);
					else
					{
						Label* l = dynamic_cast<Label*>(filterComboBox.getItem (filterComboBox.getValue()));
						if (l && (std::regex_match (s, filters_[l->getText()]))) newFiles.push_back (s);
					}
				}
			}
		}
		closedir (dir);
	}

	std::sort (newFiles.begin(), newFiles.end());
	std::sort (newDirs.begin(), newDirs.end());

	if ((files_ != newFiles) || (dirs_ != newDirs))
	{
		files_ = newFiles;
		dirs_ = newDirs;

		fileListBox.deleteItem();

		// Directories
		for (std::string const& d : dirs_) 
		{
			fileListBox.addItem (d);
			Label* l = dynamic_cast<Label*>(fileListBox.getItem (d));
			if (l) 
			{
				BStyles::Font f = l->getFont();
				f.weight = CAIRO_FONT_WEIGHT_BOLD;
				l->setFont (f);
			}
		}

		// Files
		for (std::string const& f : files_) fileListBox.addItem (f);

		fileListBox.setTop (1);
	}
}

inline void FileChooser::processFileSelected()
{
	struct stat buffer;
	const std::string fileName = getPath() + PATH_SEPARATOR + getFileName();
	const bool fileExists = (stat (fileName.c_str(), &buffer) == 0);

	// Open file exists dialog
	if (fileExists)
	{
		confirmBox.text.setText (BUtilities::Dictionary::get ("File already exists") + ". " + BUtilities::Dictionary::get ("Overwrite") + "?");
		update();
		if (!contains (&confirmBox)) add (&confirmBox);
	}

	// Open file not exists dialog
	else if (!fileExists)
	{
		confirmBox.text.setText (BUtilities::Dictionary::get ("File not found") + ".");
		update();
		if (!contains (&confirmBox)) add (&confirmBox);
	}

	// Otherwise finish directly
	else
	{
		setValue (getPath() + PATH_SEPARATOR + getFileName());
		postCloseRequest();
	}
}

inline std::function<void (BEvents::Event*)> FileChooser::getFileListBoxClickedCallback()
{
	return fileListBoxChangedCallback;
}

}

#endif /* BWIDGETS_FILECHOOSER_HPP_ */
