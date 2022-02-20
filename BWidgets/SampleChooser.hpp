/* B.Oops
 * Glitch effect sequencer LV2 plugin
 *
 * Copyright (C) 2020 by Sven Jähnichen
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

#ifndef SAMPLECHOOSER_HPP_
#define SAMPLECHOOSER_HPP_

#include "FileChooser.hpp"
#include "HRangeScrollBar.hpp"
#include "CheckBox.hpp"
#include "Frame.hpp"
#include "Image.hpp"
#include "../BMusic/Sample.hpp"
#include <cairo/cairo.h>

#ifndef SF_FORMAT_MP3
#ifndef MINIMP3_IMPLEMENTATION
#define MINIMP3_IMPLEMENTATION
#endif
#endif

#ifndef BWIDGETS_DEFAULT_SAMPLECHOOSER_WIDTH
#define BWIDGETS_DEFAULT_SAMPLECHOOSER_WIDTH (BWIDGETS_DEFAULT_FILECHOOSER_WIDTH + 200)
#endif

#ifndef BWIDGETS_DEFAULT_SAMPLECHOOSER_HEIGHT
#define BWIDGETS_DEFAULT_SAMPLECHOOSER_HEIGHT BWIDGETS_DEFAULT_FILECHOOSER_HEIGHT
#endif

#ifndef BWIDGETS_DEFAULT_SAMPLECHOOSER_SOUNDFILES_REGEX
#define BWIDGETS_DEFAULT_SAMPLECHOOSER_SOUNDFILES_REGEX std::regex (".*\\.((wav)|(wave)|(aif)|(aiff)|(au)|(sd2)|(flac)|(caf)|(ogg)|(mp3))$", std::regex_constants::icase)
#endif

namespace BUtilities {class Sample;}	// Forward declaration

namespace BWidgets 
{

/**
 *  @brief  Menu widget for selection of a file.
 *
 *  The %SampleChooser is a widget based on FileChooser for the selection of 
 *  audio files and samples. It additionally shows the waveform of the
 *  selected audio file and allows to select a range as a Sample.
 */
class SampleChooser : public BWidgets::FileChooser
{
public:

	Image waveform;
	HRangeScrollBar scrollbar;
	Frame startMarker;
	Image startMarkerLine;
	Frame endMarker;
	Image endMarkerLine;
	Label sizeLabel;
	Label startLabel;
	Label endLabel;
	CheckBox loopCheckbox;
	Label loopLabel;
	Label noFileLabel;

	/**
	 *  @brief  Constructs a default SampleChooser object.
	 * 
	 */
	SampleChooser ();

	/**
	 *  @brief  Constructs a default SampleChooser object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	SampleChooser (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Constructs a SampleChooser object with default size
	 *  @param path  Sample path.
	 *  @param filters  Optional, initializer list with filename search
	 *  filters.
     *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %SampleChooser title.
	 */
	SampleChooser	(const std::string& path, std::initializer_list<Filter> filters = {},
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Constructs a SampleChooser object with default size
	 *  @param x  %SampleChooser X origin coordinate.
	 *  @param y  %SampleChooser Y origin coordinate.
	 *  @param width  %SampleChooser width.
	 *  @param height  %SampleChooser height.
	 *  @param path  Sample path.
	 *  @param filters  Optional, initializer list with filename search
	 *  filters.
     *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %SampleChooser title.
	 */
	SampleChooser	(const double x, const double y, const double width, const double height,
					 std::string path = ".", 
					 std::initializer_list<Filter> filters =	{Filter	{BUtilities::Dictionary::get ("All files"), 
					 													 std::regex (".*")},
					 											 Filter	{BUtilities::Dictionary::get ("Sound files"), 
																  		 BWIDGETS_DEFAULT_SAMPLECHOOSER_SOUNDFILES_REGEX}},
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");


	/**
	 *  @brief  Creates a clone of the %SampleChooser. 
	 *  @return  Pointer to the new %SampleChooser.
	 *
	 *  Creates a clone of this widget by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %SampleChooser. 
	 *  @param that  Other %SampleChooser.
	 *
	 *  Copies all properties from another %SampleChooser. But NOT its linkage.
	 */
	void copy (const SampleChooser* that);

	/**
	 *  @brief  Sets the file name.
	 *  @param filename  File name.
	 */
	virtual void setFileName (const std::string& filename) override;

	/**
	 *  @brief  Sets the start point of the sample within a sound file.
	 *  @param start  Start point in frames.
	 */
	void setStart (const int64_t start);

	/**
	 *  @brief  Gets the start point of the sample within a sound file.
	 *  @return  Start point in frames.
	 */
	int64_t getStart() const;

	/**
	 *  @brief  Sets the end point of the sample within a sound file.
	 *  @param start  End point in frames.
	 */
	void setEnd (const int64_t end);

	/**
	 *  @brief  Gets the end point of the sample within a sound file.
	 *  @return  End point in frames.
	 */
	int64_t getEnd() const;

	/**
	 *  @brief  Defines whether the sample will be played in a loop or not.
	 *  @param loop  True if playback in a loop, otherwise false.
	 */
	void setLoop (const bool loop);

	/**
	 *  @brief  Information if the sample will be played in a loop or not.
	 *  @return True if playback in a loop, otherwise false.
	 */
	bool getLoop() const;

	/**
     *  @brief  Method to be called following an object state change.
     */
	virtual void update () override;

protected:

	BMusic::Sample* sample_;


	static void sfileListBoxClickedCallback (BEvents::Event* event);
	static void scrollbarChangedCallback (BEvents::Event* event);
	static void lineDraggedCallback (BEvents::Event* event);
	static void filenameEnteredCallback (BEvents::Event* event);

	void drawWaveform();

	void drawMarkers();
	
	virtual std::function<void (BEvents::Event*)> getFileListBoxClickedCallback() override;
};

inline SampleChooser::SampleChooser () : 
	SampleChooser	(0.0, 0.0, BWIDGETS_DEFAULT_SAMPLECHOOSER_WIDTH, BWIDGETS_DEFAULT_SAMPLECHOOSER_HEIGHT, 
					 ".",	
					 {Filter {BUtilities::Dictionary::get ("All files"), std::regex (".*")},
					  Filter {BUtilities::Dictionary::get ("Sound files"), BWIDGETS_DEFAULT_SAMPLECHOOSER_SOUNDFILES_REGEX}},
					 URID_UNKNOWN_URID, "") 
{

}

inline SampleChooser::SampleChooser (const uint32_t urid, const std::string& title) :
	SampleChooser	(0.0, 0.0, BWIDGETS_DEFAULT_SAMPLECHOOSER_WIDTH, BWIDGETS_DEFAULT_SAMPLECHOOSER_HEIGHT, 
					 ".",	
					 {Filter {BUtilities::Dictionary::get ("All files"), std::regex (".*")},
					  Filter {BUtilities::Dictionary::get ("Sound files"), BWIDGETS_DEFAULT_SAMPLECHOOSER_SOUNDFILES_REGEX}},
					 urid, title) 
{

}

inline SampleChooser::SampleChooser	(const std::string& path, std::initializer_list<Filter> filters,
									 uint32_t urid, std::string title) :
	SampleChooser	(0.0, 0.0, BWIDGETS_DEFAULT_SAMPLECHOOSER_WIDTH, BWIDGETS_DEFAULT_SAMPLECHOOSER_HEIGHT, 
					 path, filters, urid, title)
{

}

inline SampleChooser::SampleChooser	(const double x, const double y, const double width, const double height,
									 std::string path, std::initializer_list<Filter> filters,
									 uint32_t urid, std::string title) :
	FileChooser (x, y, width, height, path, filters, urid, title),
	waveform (),
	scrollbar (),
	startMarker (),
	startMarkerLine (),
	endMarker (),
	endMarkerLine (),
	sizeLabel (BUtilities::Dictionary::get ("frames"), BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), ""),
	startLabel (BUtilities::Dictionary::get ("Selection start"), BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), ""),
	endLabel (BUtilities::Dictionary::get ("Selection end"), BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), ""),
	loopCheckbox (true, false, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/button"), ""),
	loopLabel (BUtilities::Dictionary::get ("Play selection as loop"), BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), ""),
	noFileLabel (BUtilities::Dictionary::get ("No audio file selected"), BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), ""),
	sample_ (nullptr)
{
	//std::vector<std::string> sampleLabels = {"Play selection as loop", "File", "Selection start", "Selection end", "frames", "No audio file selected"};
	//labels.insert (labels.end(), sampleLabels.begin(), sampleLabels.end());
	//for (int i = BWIDGETS_DEFAULT_SAMPLECHOOSER_PLAY_AS_LOOP_INDEX; (i < int(texts.size())) && (i < int(labels.size())); ++i) labels[i] = texts[i];

	fileListBox.setCallbackFunction (BEvents::Event::VALUE_CHANGED_EVENT, sfileListBoxClickedCallback);
	waveform.setBorder ({{BStyles::grey, 1.0}, 0.0, 3.0, 0.0});
	fileNameBox.setCallbackFunction (BEvents::Event::VALUE_CHANGED_EVENT, filenameEnteredCallback);
	startMarker.setCallbackFunction (BEvents::Event::POINTER_DRAG_EVENT, lineDraggedCallback);
	startMarkerLine.setEventPassable (BEvents::Event::BUTTON_PRESS_EVENT);
	startMarkerLine.setEventPassable (BEvents::Event::BUTTON_RELEASE_EVENT);
	startMarkerLine.setEventPassable (BEvents::Event::BUTTON_CLICK_EVENT);
	startMarkerLine.setEventPassable (BEvents::Event::POINTER_DRAG_EVENT);
	endMarker.setCallbackFunction (BEvents::Event::POINTER_DRAG_EVENT, lineDraggedCallback);
	endMarkerLine.setEventPassable (BEvents::Event::BUTTON_PRESS_EVENT);
	endMarkerLine.setEventPassable (BEvents::Event::BUTTON_RELEASE_EVENT);
	endMarkerLine.setEventPassable (BEvents::Event::BUTTON_CLICK_EVENT);
	endMarkerLine.setEventPassable (BEvents::Event::POINTER_DRAG_EVENT);
	scrollbar.setCallbackFunction(BEvents::Event::VALUE_CHANGED_EVENT, scrollbarChangedCallback);
	
	startMarker.add (&startMarkerLine);
	endMarker.add (&endMarkerLine);
	waveform.add (&startMarker);
	waveform.add (&endMarker);
	add (&waveform);
	add (&scrollbar);
	add (&sizeLabel);
	add (&startLabel);
	add (&endLabel);
	add (&loopCheckbox);
	add (&loopLabel);
	add (&noFileLabel);
}

inline Widget* SampleChooser::clone () const 
{
	Widget* f = new SampleChooser (urid_, title_);
	f->copy (this);
	return f;
}

inline void SampleChooser::copy (const SampleChooser* that)
{
	waveform.copy (&that->waveform);
	scrollbar.copy (&that->scrollbar);
	startMarker.copy (&that->startMarker);
	startMarkerLine.copy (&that->startMarkerLine);
	endMarker.copy (&that->endMarker);
	endMarkerLine.copy (&that->endMarkerLine);
	sizeLabel.copy (&that->sizeLabel);
	startLabel.copy (&that->startLabel);
	endLabel.copy (&that->endLabel);
	loopCheckbox.copy (&that->loopCheckbox);
	loopLabel.copy (&that->loopLabel);
	noFileLabel.copy (&that->noFileLabel);

	if (sample_) delete sample_;
	sample_ = new BMusic::Sample (*(that->sample_));

	FileChooser::copy (that);
}

inline void SampleChooser::setFileName (const std::string& filename)
{
	if (filename != fileNameBox.getText())
	{
		FileChooser::setFileName (filename);
		std::string newPath = getPath() + "/" + filename;
		char buf[PATH_MAX];
		char *rp = realpath(newPath.c_str(), buf);
		if (sample_)
		{
			delete (sample_);
			sample_ = nullptr;
		}
		try {sample_ = new BMusic::Sample (rp);}
		catch (std::exception& exc)
		{
			std::cerr << exc.what() << "\n";
			noFileLabel.setText (BUtilities::Dictionary::get ("No preview"));
		}

		if (sample_)
		{
			sample_->start = 0;
			sample_->end = sample_->info.frames;

			scrollbar.setValue (HRangeScrollBar::value_type (0.0, 1.0));
		}

		update();
	}
}

inline void SampleChooser::setStart (const int64_t start)
{
	if (!sample_) return;
	sample_->start = LIMIT (start, 0, sample_->info.frames - 1);
	update();
}

inline int64_t SampleChooser::getStart() const 
{
	return (sample_ ? LIMIT (sample_->start, 0, sample_->info.frames - 1) : 0);
}

inline void SampleChooser::setEnd (const int64_t end)
{
	if (!sample_) return;
	sample_->end = LIMIT (end, 0, sample_->info.frames);
	update();
}

inline int64_t SampleChooser::getEnd() const 
{
	return (sample_ ? LIMIT (sample_->end, 1, sample_->info.frames) : 0);
}

inline void SampleChooser::setLoop (const bool loop) 
{
	loopCheckbox.setValue (loop ? 1.0 : 0.0);
}

inline bool SampleChooser::getLoop() const 
{
	return (loopCheckbox.getValue() != 0.0);
}

inline void SampleChooser::update ()
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
		//loopLabel.setText(labels[BWIDGETS_DEFAULT_SAMPLECHOOSER_PLAY_AS_LOOP_INDEX]);

		// Get extends first
		okButton.resize();
		cancelButton.resize ();
		const double okWidth = (okButton.getWidth() > cancelButton.getWidth() ? okButton.getWidth() : cancelButton.getWidth()) + 4;
		const double okHeight = (okButton.getHeight() > cancelButton.getHeight() ? okButton.getHeight() : cancelButton.getHeight()) + 4;
		pathNameBox.resize();
		const double pathNameHeight = pathNameBox.getHeight();
		fileNameBox.resize();
		const double fileNameHeight = fileNameBox.getHeight();
		fileNameLabel.resize();
		const double fileNameWidth = fileNameLabel.getWidth();

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

		if (h > pathNameHeight + okHeight + fileNameHeight + 60)
		{
			const double fileListBoxHeight = h - pathNameHeight - okHeight - fileNameHeight - 50;

			fileListBox.moveTo (x0 + 10, y0 + pathNameHeight + 20);
			fileListBox.resize (0.4 * w - 15, fileListBoxHeight);
			fileListBox.setItemHeight (20);
			fileListBox.resizeItems();
			fileListBox.show();

			startMarker.resize (6.0, fileListBoxHeight);
			startMarker.show();
			endMarker.resize (6.0, fileListBoxHeight);
			endMarker.show();
			//drawMarkers(); at a later point

			double waveformHeight = fileListBoxHeight;

			if (sample_ && (sample_->info.frames > 0))
			{
				sizeLabel.resize();
				const double sizeHeight = sizeLabel.getHeight();
				startLabel.resize();
				const double startHeight = startLabel.getHeight();
				endLabel.resize();
				const double endHeight = endLabel.getHeight();
				loopLabel.resize();
				const double loopHeight = loopLabel.getHeight();

				if (fileListBoxHeight > sizeHeight + startHeight + endHeight + loopHeight + 50.0)
				{
					waveformHeight = fileListBoxHeight - sizeHeight - startHeight - endHeight - loopHeight - 10.0;
					sizeLabel.moveTo (x0 + 0.4 * w + 5, y0 + pathNameHeight + 20.0 + waveformHeight + 10.0);
					startLabel.moveTo (x0 + 0.4 * w + 5, y0 + pathNameHeight + 20.0 + waveformHeight + 10.0 + sizeHeight);
					endLabel.moveTo (x0 + 0.4 * w + 5, y0 + pathNameHeight + 20.0 + waveformHeight + 10.0 + sizeHeight + startHeight);
					loopCheckbox.resize (0.6 * loopHeight, 0.6 * loopHeight);
					loopCheckbox.moveTo (x0 + 0.4 * w + 5, y0 + pathNameHeight + 20.0 + waveformHeight + 10.0 + sizeHeight + startHeight + endHeight + 0.2 * loopHeight);
					loopLabel.moveTo (x0 + 0.4 * w + 5 + loopHeight, y0 + pathNameHeight + 20.0 + waveformHeight + 10.0 + sizeHeight + startHeight + endHeight);

					sizeLabel.show();
					startLabel.show();
					endLabel.show();
					loopCheckbox.show();
					loopLabel.show();
				}

				else
				{
					sizeLabel.hide();
					startLabel.hide();
					endLabel.hide();
					loopCheckbox.hide();
					loopLabel.hide();
					noFileLabel.hide();
				}
			}

			else
			{
				sizeLabel.hide();
				startLabel.hide();
				endLabel.hide();
				loopCheckbox.hide();
				loopLabel.hide();
			}

			waveform.moveTo (x0 + 0.4 * w + 5, y0 + pathNameHeight + 20);
			waveform.resize (0.6 * w - 15, waveformHeight);
			drawWaveform();
			drawMarkers();
			waveform.show();

			scrollbar.moveTo (x0 + 0.4 * w + 5, y0 + pathNameHeight + 20 + waveformHeight - 12);
			scrollbar.resize (0.6 * w - 15, 10);
			if (sample_ && (sample_->info.frames > 0))
			{
				startMarker.show();
				endMarker.show();
				scrollbar.show();
				noFileLabel.hide();
			}
			else
			{
				startMarker.hide();
				endMarker.hide();
				scrollbar.hide();
				noFileLabel.resize ();
				noFileLabel.moveTo
				(
					x0 + 0.4 * w + 5 + 0.3 * w - 7.5 - 0.5 * noFileLabel.getWidth(),
					y0 + pathNameHeight + 20 + 0.5 * waveformHeight - 0.5 * noFileLabel.getHeight()
				);
				noFileLabel.show();
			}
		}
		else
		{
			fileListBox.hide();
			waveform.hide();
			scrollbar.hide();
			startMarker.hide();
			endMarker.hide();
			sizeLabel.hide();
			startLabel.hide();
			endLabel.hide();
			loopCheckbox.hide();
			loopLabel.hide();
			noFileLabel.hide();
		}

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
		waveform.hide();
		scrollbar.hide();
		startMarker.hide();
		endMarker.hide();
		sizeLabel.hide();
		startLabel.hide();
		endLabel.hide();
		loopCheckbox.hide();
		loopLabel.hide();
		noFileLabel.hide();
		fileNameLabel.hide();
		fileNameBox.hide();
		filterComboBox.hide ();
		confirmBox.hide();
		createBox.hide();
	}

	Widget::update();
}

inline void SampleChooser::sfileListBoxClickedCallback (BEvents::Event* event)
{
	if (!event) return;
	BWidgets::ListBox* w = dynamic_cast<BWidgets::ListBox*>(event->getWidget());
	if (!w) return;
	SampleChooser* fc = dynamic_cast<SampleChooser*>(w->getParent());
	if (!fc) return;

	const size_t val = w->getValue();

	if ((val != 0) && (!fc->fileNameBox.getEditMode()))
	{
		// Directory selected -> one click chdir
		if (val <= fc->dirs_.size())
		{
			fc->fileNameBox.setText ("");
			if (fc->sample_)
			{
				delete (fc->sample_);
				fc->sample_ = nullptr;
			}
			BEvents::ValueChangeTypedEvent<bool> dummyEvent = BEvents::ValueChangeTypedEvent<bool> (&fc->okButton, true);
			fc->okButtonClickedCallback (&dummyEvent);
			//fc->noFileLabel.setText (fc->labels[BWIDGETS_DEFAULT_SAMPLECHOOSER_NO_FILE_INDEX]);
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

inline void SampleChooser::scrollbarChangedCallback (BEvents::Event* event)
{
	if (!event) return;
	HRangeScrollBar* w = dynamic_cast<HRangeScrollBar*>(event->getWidget());
	if (!w) return;
	SampleChooser* fc = dynamic_cast<SampleChooser*>(w->getParent());
	if (!fc) return;

	fc->drawWaveform();
}

inline void SampleChooser::lineDraggedCallback (BEvents::Event* event)
{
	if (!event) return;
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*>(event);
	Frame* w = dynamic_cast<Frame*>(event->getWidget());
	if (!w) return;
	Image* wf = dynamic_cast<Image*>(w->getParent());
	if (!wf) return;
	SampleChooser* fc = dynamic_cast<SampleChooser*>(wf->getParent());
	if ((!fc) || (!fc->sample_) || (fc->sample_->info.frames == 0) || (fc->waveform.getEffectiveWidth() <= 0.0)) return;

	const double start = fc->scrollbar.getValue().first;
	const double range = fc->scrollbar.getValue().second - start;
	const double dp = pev->getDelta().x / fc->waveform.getEffectiveWidth();
	const double df = dp * range * double (fc->sample_->info.frames);

	if (w == &fc->startMarker) fc->sample_->start = LIMIT (fc->sample_->start + df, 0, fc->sample_->info.frames - 1);
	else if (w == &fc->endMarker) fc->sample_->end = LIMIT (fc->sample_->end + df, 1, fc->sample_->info.frames);

	if (fc->sample_->start >= fc->sample_->end) fc->sample_->start = fc->sample_->end - 1;
	fc->drawWaveform();
}

inline void SampleChooser::filenameEnteredCallback (BEvents::Event* event)
{
	if (!event) return;
	Label* l = dynamic_cast<Label*>(event->getWidget());
	if (!l) return;
	SampleChooser* p = (SampleChooser*)l->getParent();
	if (!p) return;

	const std::string s = l->getText();
	p->setFileName (s);
}

inline void SampleChooser::drawWaveform()
{
	const double x0 = waveform.getXOffset();
	const double y0 = waveform.getYOffset();
	const double w = waveform.getEffectiveWidth();
	const double h = waveform.getEffectiveHeight();

	cairo_surface_t* surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);
	cairo_t* cr = cairo_create (surface);
	if (cr && cairo_status (cr) == CAIRO_STATUS_SUCCESS)
	{
		if (sample_ && (sample_->info.frames) && (sample_->info.samplerate) && (w >= 1.0))
		{
			// Scan for min/max
			const double start = scrollbar.getValue().first;
			const double range = scrollbar.getValue().second - start;
			double max = 1.0;
			for (double i = 0.0; i < 1.0; i += 0.25 / w)
			{
				if (fabs (sample_->get (i * double (sample_->info.frames), 0, sample_->info.samplerate)) > max)
				{
					max = fabs (sample_->get (i * double (sample_->info.frames), 0, sample_->info.samplerate));
				}
			}

			cairo_set_line_width (cr, 0.1);
			double lo = sample_->get (start * double (sample_->info.frames), 0, sample_->info.samplerate);
			double hi = lo;
			const double step = 0.1 / w;
			const double minstep = LIMIT (1.0 / (range * double (sample_->info.frames)), 0.01 * step, step);
			for (double x = 0; x < 1.0; x += step)
			{
				double s = 0;
				for (double xm = 0; xm < step; xm += minstep)
				{
					const double f = (start + (x + xm) * range) * double (sample_->info.frames);
					s = sample_->get (f, 0, sample_->info.samplerate);
					if (s > hi) hi = s;
					if (s < lo) lo = s;
				}
				const double frame = (start + x * range) * double (sample_->info.frames);
				if ((frame >= sample_->start) && (frame <= sample_->end)) cairo_set_source_rgba (cr, 1.0, 1.0, 1.0, 1.0);
				else cairo_set_source_rgba (cr, 0.25, 0.25, 0.25, 1.0);
				cairo_move_to (cr, x * w, 0.5 * h - 0.5 * h * lo / max);
				cairo_line_to (cr, x * w, 0.5 * h - 0.5 * h * hi / max);
				cairo_stroke (cr);
				lo = s;
				hi = s + 2.0 * max / h;
			}

			// Set start and end line
			if (range > 0)
			{
				const double sp = (sample_->start / double (sample_->info.frames) - start) / range;
				startMarker.moveTo (x0 + sp * w - 0.5 * startMarker.getWidth(), y0);
				const double ep = (sample_->end / double (sample_->info.frames) - start) / range;
				endMarker.moveTo (x0 + ep * w - 0.5 * endMarker.getWidth(), y0);
			}

			else
			{
				startMarker.moveTo (-startMarker.getWidth(), 0.0);
				endMarker.moveTo (-startMarker.getWidth(), 0.0);
			}

			// Update labels
			sizeLabel.setText
			(
				BUtilities::Dictionary::get ("File") + ": " +
				std::to_string (int (sample_->info.frames / (sample_->info.samplerate * 60))) +
				":" +
				std::to_string ((int (sample_->info.frames / sample_->info.samplerate) % 60) / 10) +
				std::to_string ((int (sample_->info.frames / sample_->info.samplerate) % 60) % 10) +
				" (" +
				std::to_string (sample_->info.frames) +
				") " +
				BUtilities::Dictionary::get ("frames")
			);
			startLabel.setText
			(
				BUtilities::Dictionary::get ("Selection start") + ": " +
				std::to_string (int (sample_->start / (sample_->info.samplerate * 60))) +
				":" +
				std::to_string ((int (sample_->start / sample_->info.samplerate) % 60) / 10) +
				std::to_string ((int (sample_->start / sample_->info.samplerate) % 60) % 10) +
				" (" +
				std::to_string (sample_->start) +
				") " +
				BUtilities::Dictionary::get ("frames")
			);
			endLabel.setText
			(
				BUtilities::Dictionary::get ("Selection end")+ ": " +
				std::to_string (int (sample_->end / (sample_->info.samplerate * 60))) +
				":" +
				std::to_string ((int (sample_->end / sample_->info.samplerate) % 60) / 10) +
				std::to_string ((int (sample_->end / sample_->info.samplerate) % 60) % 10) +
				" (" +
				std::to_string (sample_->end) +
				") " +
				BUtilities::Dictionary::get ("frames")
			);
			sizeLabel.resize();
			startLabel.resize();
			endLabel.resize();
		}

		else
		{

		}
		cairo_destroy (cr);
	}
	waveform.loadImage (BStyles::STATUS_NORMAL, surface);
	cairo_surface_destroy (surface);
}

inline void SampleChooser::drawMarkers ()
{
	startMarkerLine.resize (6.0, waveform.getEffectiveHeight());
	endMarkerLine.resize (6.0, waveform.getEffectiveHeight());
	const BStyles::Color fgColor =getFgColors()[getStatus()];

	cairo_surface_t* s1 = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 6.0, startMarkerLine.getHeight());
	cairo_t* cr1 = cairo_create (s1);
	cairo_move_to (cr1, 3.0, 0.0);
	cairo_line_to (cr1, 3.0, startMarkerLine.getHeight());
	cairo_set_line_width (cr1, 2.0);
	cairo_set_source_rgba (cr1, CAIRO_RGBA(fgColor));
	cairo_stroke (cr1);
	cairo_destroy (cr1);
	startMarkerLine.loadImage (BStyles::STATUS_NORMAL, s1);
	endMarkerLine.loadImage (BStyles::STATUS_NORMAL, s1);
	cairo_surface_destroy (s1);
}

inline std::function<void (BEvents::Event*)> SampleChooser::getFileListBoxClickedCallback()
{
	return sfileListBoxClickedCallback;
}

}

#endif /* SAMPLECHOOSER_HPP_ */
