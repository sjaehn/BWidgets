/* Demonstration of BWidgets TK
 * Copyright (C) 2018  Sven Jähnichen
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

#include "BWidgets/BWidgets.hpp"

static void showValue (BEvents::Event* event)
{
	if ((event) && (event->getWidget ()))
	{
		std::cout << ((BWidgets::ValueWidget*) event->getWidget ())->getValue () << std::endl;
	}
}

int main ()
{
	//Define Styles and Colors first
	BColors::ColorSet defaultFgColors = {{{0.0, 0.75, 0.2, 1.0}, {0.0, 1.0, 0.4, 1.0}, {0.0, 0.2, 0.0, 1.0}, {0.0, 0.0, 0.0, 0.0}}};
	BColors::ColorSet defaultToolColors = BColors::greys;
	BStyles::Fill bgPicture = BStyles::Fill ("example-romedalen.png");

	BStyles::StyleSet defaultStyles = {"Widget", {{"background", STYLEPTR (&BStyles::noFill)},
											 	  {"border", STYLEPTR (&BStyles::noBorder)}}};

	BStyles::Border frameBorder = {BStyles::whiteLine1pt, 3.0, 3.0, 10.0};
	BStyles::Border defaultBorder = {BStyles::whiteLine1pt, 0.0, 1.0, 0.0};

	BStyles::Font defaultFont = BStyles::Font ("Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0,
											   BStyles::TEXT_ALIGN_LEFT, BStyles::TEXT_VALIGN_TOP);
	BStyles::Font labelFont = BStyles::Font ("Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0,
											 BStyles::TEXT_ALIGN_CENTER, BStyles::TEXT_VALIGN_MIDDLE);
	BStyles::Font smallFont = BStyles::Font ("Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 8.0,
											 BStyles::TEXT_ALIGN_CENTER, BStyles::TEXT_VALIGN_MIDDLE);

	// And a theme makes global definition of styles much easier
	BStyles::Theme defaultTheme = BStyles::Theme ({
		defaultStyles,
		{"Window", {{"background", STYLEPTR (&BStyles::blackFill)},
					{"border", STYLEPTR (&BStyles::noBorder)}}
		},
		{"Frame", {{"background", STYLEPTR (&BStyles::greyFill)},
				   {"border", STYLEPTR (&frameBorder)}}
		},
		{"Surface", {{"background", STYLEPTR (&BStyles::redFill)},
					 {"border", STYLEPTR (&frameBorder)}}
		},
		{"Label", {{"uses", STYLEPTR (&defaultStyles)},
				   {"textcolors", STYLEPTR (&BColors::blues)},
				   {"font", STYLEPTR (&labelFont)}}
		},
		{"smallLabel", {{"uses", STYLEPTR (&defaultStyles)},
				   {"textcolors", STYLEPTR (&BColors::blues)},
				   {"font", STYLEPTR (&smallFont)}}
		},
		{"Text", {{"uses", STYLEPTR (&defaultStyles)},
				   {"border", STYLEPTR (&defaultBorder)},
				   {"textcolors", STYLEPTR (&BColors::whites)},
				   {"font", STYLEPTR (&defaultFont)}}
		},
		{"Slider", {{"uses", STYLEPTR (&defaultStyles)},
					{"fgcolors", STYLEPTR (&defaultFgColors)},
					{"bgcolors", STYLEPTR (&BColors::darks)}}
		},
		{"Slider/focus",
				  {{"background", STYLEPTR (&BStyles::darkgreyFill)},
				   {"border", STYLEPTR (&defaultBorder)}}
		},

		{"Slider/focus/label",
				  {{"textcolors", STYLEPTR (&BColors::whites)},
				   {"font", STYLEPTR (&labelFont)}}
		},
		{"Dial", {{"uses", STYLEPTR (&defaultStyles)},
				  {"fgcolors", STYLEPTR (&defaultFgColors)},
				  {"bgcolors", STYLEPTR (&BColors::darks)}}
		},
		{"Dial/focus",
				  {{"background", STYLEPTR (&BStyles::darkgreyFill)},
				   {"border", STYLEPTR (&defaultBorder)}}
		},

		{"Dial/focus/label",
				  {{"textcolors", STYLEPTR (&BColors::whites)},
				   {"font", STYLEPTR (&labelFont)}}
		},

		{"DialVal", {{"uses", STYLEPTR (&defaultStyles)},
			   	     {"fgcolors", STYLEPTR (&defaultFgColors)},
					 {"bgcolors", STYLEPTR (&BColors::darks)},
					 {"textcolors", STYLEPTR (&BColors::darks)},
					 {"font", STYLEPTR (&labelFont)}}
		},

		{"DialVal/focus",
				  {{"background", STYLEPTR (&BStyles::darkgreyFill)},
				   {"border", STYLEPTR (&defaultBorder)}}
		},

		{"DialVal/focus/label",
				  {{"textcolors", STYLEPTR (&BColors::whites)},
				   {"font", STYLEPTR (&labelFont)}}
		},
		{"Button", {{"uses", STYLEPTR (&defaultStyles)},
					{"buttoncolors", STYLEPTR (&BColors::darks)},
					{"bgcolors", STYLEPTR (&BColors::darks)},
					{"textcolors", STYLEPTR (&defaultFgColors)},
					{"font", STYLEPTR (&labelFont)}}
		},
		{"Switch", {{"uses", STYLEPTR (&defaultStyles)},
					{"buttoncolors", STYLEPTR (&BColors::darks)},
					{"bgcolors", STYLEPTR (&BColors::darks)},
					{"textcolors", STYLEPTR (&defaultFgColors)}}
		}
	});

	// The starting point is the main window. All widgets will be added to this
	// window later.
	BWidgets::Window* MainWindow = new BWidgets::Window (640, 480, "Window", 0);

	// Definition of a few container widgets.
	BWidgets::Widget Widget2 = BWidgets::Widget (100, 100, 500, 300, "BackgroundWidget");
	Widget2.setBorder (BStyles::Border (BStyles::Line (BColors::blue, 3.0), 0.0, 0.0, 0.0));
	Widget2.setBackground (BStyles::Fill (BColors::darkdarkgrey));
	BWidgets::Widget Widget3 = BWidgets::Widget (80, 10, 500, 300, "Frame");
	Widget3.applyTheme (defaultTheme);
	Widget3.setDraggable (true);
	BWidgets::Widget Widget = BWidgets::Widget (20, 40, 500, 300, "Frame");
	Widget.applyTheme (defaultTheme);
	Widget.setBackground(bgPicture);
	Widget.setClickable (true);
	Widget.setDraggable (true);


	// Label and text widgets
	BWidgets::Label Label1 = BWidgets::Label (100, 120, 340, 16, "This is a label text for testing widget copying");
	Label1.applyTheme (defaultTheme, "Label");
	BWidgets::Label Label2 (Label1);
	Label2.applyTheme (defaultTheme, "Label");
	Label2.moveTo (100,140);
	BWidgets::Label Label2a = Label1;
	Label2a.applyTheme (defaultTheme, "Label");
	Label2a.moveTo (100,160);
	BWidgets::Label Label3 = BWidgets::Label (100, 180, 340, 16, "This is a long label text and it will be shown fully!");
	Label3.applyTheme (defaultTheme, "Label");
	BWidgets::Label Label4 = BWidgets::Label (10, 10, 240, 16, "This is a too long label text and it will be clipped!");
	Label4.applyTheme (defaultTheme, "Label");
	BWidgets::Text Text1 (20, 20, 240, 80, "This is a text widget.\nThe text contains line breaks if the text is too long. Lines are broken on (i) \\n, (ii) space or (iii) any position.");
	Text1.applyTheme (defaultTheme, "Text");

	//Switch
	BWidgets::VSwitch Switch1 (20, 200, 20, 40, "Switch", 0.0);
	Switch1.applyTheme (defaultTheme);
	BWidgets::HSwitch Switch2 (60, 210, 40, 20, "Switch", 0.0);
	Switch2.applyTheme (defaultTheme);

	// Slider widgets
	BWidgets::Label VSliderLabel = BWidgets::Label (10, 10, 80, 16, "VSliders");
	VSliderLabel.applyTheme (defaultTheme, "Label");
	BWidgets::Label VSliderLabel2 = BWidgets::Label (10, 26, 80, 16, "focusable = true");
	VSliderLabel2.applyTheme (defaultTheme, "smallLabel");
	BWidgets::VSlider Slider1 = BWidgets::VSlider (10, 50, 20, 220, "Slider", 80.0, 0.0, 100.0, 0.0);
	Slider1.applyTheme (defaultTheme);
	Slider1.setFocusable (true);
	BWidgets::VSlider Slider2 = BWidgets::VSlider (40, 50, 20, 220, "Slider", 80.0, 0.0, 100.0, -10.0);
	Slider2.applyTheme (defaultTheme);
	Slider2.setFocusable (true);

	BWidgets::Label HSliderLabel = BWidgets::Label (100, 10, 240, 16, "HSliders");
	HSliderLabel.applyTheme (defaultTheme, "Label");
	BWidgets::HSlider Slider3 = BWidgets::HSlider (100, 30, 240, 20, "Slider", 80.0, 0.0, 100.0, 0.0);
	Slider3.applyTheme (defaultTheme);
	BWidgets::HSlider Slider4 = BWidgets::HSlider (100, 60, 240, 20, "Slider", 80.0, 0.0, 100.0, -1);
	Slider4.applyTheme (defaultTheme);
	BWidgets::DisplayHSlider Slider5 = BWidgets::DisplayHSlider (100, 80, 240, 40, "DialVal",
																				   80.0, 0.0, 100.0, 0.0, "%3.1f");
	Slider5.applyTheme (defaultTheme);
	BWidgets::DisplayVSlider Slider6 = BWidgets::DisplayVSlider (60, 50, 40, 220, "DialVal",
																					   80.0, 0.0, 100.0, 1.0, "%3.1f");
	Slider6.applyTheme (defaultTheme);
	Slider6.setFocusable (true);

	// Dial widgets
	BWidgets::Label DialLabel = BWidgets::Label (100, 130, 300, 16, "Dials");
	DialLabel.applyTheme (defaultTheme, "Label");
	BWidgets::Label DialLabel2 = BWidgets::Label (80, 220, 120, 16, "hardChangeable = false");
	DialLabel2.applyTheme (defaultTheme, "smallLabel");
	BWidgets::Label DialLabel3 = BWidgets::Label (200, 220, 80, 16, "focusable = true");
	DialLabel3.applyTheme (defaultTheme, "smallLabel");
	BWidgets::Dial Dial1 = BWidgets::Dial (100, 150, 80, 80, "Dial", 80.0, 0.0, 100.0, 0.0);
	Dial1.applyTheme (defaultTheme);
	Dial1.setHardChangeable (false);
	BWidgets::Dial Dial2 = BWidgets::Dial (200, 150, 80, 80, "Dial", 80.0, 0.0, 100.0, -10.0);
	Dial2.applyTheme (defaultTheme);
	Dial2.setFocusable (true);
	BWidgets::DisplayDial Dial3 = BWidgets::DisplayDial (300, 150, 80, 96, "DialVal", 80.0, 0.0, 100.0, 1.0, "%3.1f");
	Dial3.applyTheme (defaultTheme);

	// Scale widgets
	BWidgets::Label ScaleLabel = BWidgets::Label (380, 10, 80, 16, "Scales");
	ScaleLabel.applyTheme (defaultTheme, "Label");
	BWidgets::Label ScaleLabel2 = BWidgets::Label (360, 26, 120, 16, "hardChangeable = false");
	ScaleLabel2.applyTheme (defaultTheme, "smallLabel");
	BWidgets::VScale Scale1 (380, 50, 10, 80, "Slider", 80.0, 0.0, 100.0, -1);
	Scale1.applyTheme (defaultTheme);
	Scale1.setHardChangeable (false);
	BWidgets::HScale Scale2 (400, 50, 60, 10, "Slider", 80.0, 0.0, 100.0, -1);
	Scale2.applyTheme (defaultTheme);
	Scale2.setHardChangeable (false);

	// Button widgets
	BWidgets::Label ButtonLabel = BWidgets::Label (100, 245, 300, 16, "Buttons");
	ButtonLabel.applyTheme (defaultTheme, "Label");
	BWidgets::Button Button1 = BWidgets::Button (100, 270, 60, 20, "Button", 0.0);
	Button1.applyTheme (defaultTheme);
	BWidgets::ToggleButton Button2 = BWidgets::ToggleButton (180, 270, 60, 20, "Button", 0.0);
	Button2.applyTheme (defaultTheme);
	BWidgets::TextButton Button3 = BWidgets::TextButton (260, 270, 60, 20, "Button", 0.0);
	Button3.applyTheme (defaultTheme);
	BWidgets::TextToggleButton Button4 = BWidgets::TextToggleButton (340, 270, 60, 20, "Button", 0.0);
	Button4.applyTheme (defaultTheme);

	// Drawing surface widgets for direct Cairo drawing
	BWidgets::DrawingSurface Surface = BWidgets::DrawingSurface (20, 340, 320, 75, "Surface");
	Surface.applyTheme (defaultTheme);
	Surface.getBorder ()->setRadius (0.0);
	Surface.getBackground ()->getColor ()->setAlpha (0.5);
	cairo_t* cr = cairo_create (Surface.getDrawingSurface ());
	cairo_set_line_width (cr, 3.0);
	cairo_set_source_rgba (cr, 1.0, 1.0, 0.0, 1.0);
	cairo_arc (cr, 30.0, 30.0, 20.0, 0, 6.28);
	cairo_close_path (cr);
	cairo_fill_preserve (cr);
	cairo_set_source_rgba (cr, 0.0, 0.0, 0.0, 1.0);
	cairo_stroke (cr);
	cairo_arc (cr, 30.0, 0.0, 40.0, 1.26, 1.88);
	cairo_stroke (cr);
	cairo_arc (cr, 20.0, 25.0, 3.0, 0.0, 6.28);
	cairo_close_path (cr);
	cairo_fill (cr);
	cairo_arc (cr, 40.0, 25.0, 3.0, 0.0, 6.28);
	cairo_close_path (cr);
	cairo_fill (cr);
	cairo_set_font_size (cr, 12.0);
	cairo_move_to (cr, 60, 28);
	cairo_show_text (cr, "Surface widget for direct Cairo drawing.");
	cairo_move_to (cr, 60, 44);
	cairo_show_text (cr, "And this widget was set 'dragable'.");
	cairo_destroy (cr);
	Surface.update ();
	Surface.setClickable (true);
	Surface.setDraggable (true);

	// Box widgets
	BWidgets::ChoiceBox choiceBox (10, 10, 100, 40, "ChoiceBox", {"Berlin", "Paris", "London", "Dublin", "Stockholm", "Madrid", "Riga"}, 1.0);
	BWidgets::ListBox listBox (130, 10, 100, 140, "ListBox", {"Mumbai", "Hyderabad", "Lucknow", "Dehli", "Jaipur", "Surat", "Patna", "Agra", "Goa", "Jammu"});
	BWidgets::PopupListBox popupListBox (250, 10, 100, 20, 100, 140, "PopupListBox", {"Arusha", "Moshi", "Tanga", "Dodoma", "Mwanza", "Dar es Salaam", "Mbeya", "Zanzibar"});

	// Add the background widget container to the main window and add all label
	// widgets and switches to the background widget container
	MainWindow->add (Widget2);
	Widget2.add (Label1);
	Widget2.add (Label2);
	Widget2.add (Label2a);
	Widget2.add (Label3);
	Widget2.add (Label4);
	Widget2.add (Text1);
	Widget2.add (Switch1);
	Widget2.add (Switch2);

	// Add Widget3 container to the main window and add all box widgets to
	// Widget3
	MainWindow->add (Widget3);
	Widget3.add (choiceBox);
	Widget3.add (listBox);
	Widget3.add (popupListBox);

	// Add the drawing surface widget directly to the main window
	MainWindow->add (Surface);

	// Add the foreground widget container to the main window and all sliders,
	// buttons and dials to the foreground widget container
	MainWindow->add (Widget);
	Widget.add (VSliderLabel);
	Widget.add (VSliderLabel2);
	Widget.add (HSliderLabel);
	Widget.add (DialLabel);
	Widget.add (DialLabel2);
	Widget.add (DialLabel3);
	Widget.add (ScaleLabel);
	Widget.add (ScaleLabel2);
	Widget.add (ButtonLabel);
	Widget.add (Slider1);
	Widget.add (Slider2);
	Widget.add (Slider3);
	Widget.add (Slider4);
	Widget.add (Dial1);
	Widget.add (Dial2);
	Widget.add (Dial3);
	Widget.add (Slider5);
	Widget.add (Slider6);
	Widget.add (Button1);
	Widget.add (Button2);
	Widget.add (Button3);
	Widget.add (Button4);
	Widget.add (Scale1);
	Widget.add (Scale2);
	Dial2.setCallbackFunction (BEvents::EventType::VALUE_CHANGED_EVENT, showValue);
	Label4.moveTo (150, 200);

	Surface.moveFrontwards ();

	// Message Box with default settings
	BWidgets::MessageBox mBox (260, 230, 200, 100, "mbox", "Message Box", "This is a message box. Press on OK to continue.");
	MainWindow->add (mBox);
	BWidgets::MessageBox mBox2 (280, 250, 200, 100, "mbox",
								"Message Box", "This is a second message box with user defined buttons. Press on one of them to continue.",
								{"Cancel", "Yes", "No"});
	MainWindow->add (mBox2);
	BWidgets::MessageBox mBox3 (mBox2);
	mBox3.moveTo (300, 270);
	mBox3.removeButton ("Cancel");
	MainWindow->add (mBox3);
	BWidgets::MessageBox mBox4 = mBox3;
	mBox4.addButton ("Maybe");
	mBox4.moveTo (320, 290);
	MainWindow->add (mBox4);


	//MainWindow->showChildrenTree (MainWindow, 0);

	// Run until main window is closed
	MainWindow->run ();
	delete MainWindow;

}
