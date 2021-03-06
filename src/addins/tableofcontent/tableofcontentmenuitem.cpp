/*
 * "Table of Contents" is a Note add-in for Gnote.
 *  It lists note's table of contents in a menu.
 *
 * Copyright (C) 2013 Luc Pionchon <pionchon.luc@gmail.com>
 * Copyright (C) 2013 Aurimas Cernius
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* A subclass of ImageMenuItem to show a toc menu item */

#include <glibmm/i18n.h>

#include <gtkmm/stock.h>

#include "iconmanager.hpp"
#include "notewindow.hpp"

#include "tableofcontentmenuitem.hpp"
#include "tableofcontent.hpp"

namespace tableofcontent {


Glib::RefPtr<Gtk::Action> TableofcontentAction::create(const sigc::slot<void, Gtk::Menu*> & slot)
{
  return Glib::RefPtr<Gtk::Action>(new TableofcontentAction(slot));
}

TableofcontentAction::TableofcontentAction(const sigc::slot<void, Gtk::Menu*> & slot)
  : Gtk::Action("TableofcontentAction", Gtk::Stock::JUMP_TO, _("Table of Contents"), _("Table of Contents"))
  , m_update_menu_slot(slot)
{
}

Gtk::Widget *TableofcontentAction::create_menu_item_vfunc()
{
  m_submenu_built = false;
  Gtk::ImageMenuItem *menu_item = new Gtk::ImageMenuItem;
  m_menu = manage(new Gtk::Menu);
  m_menu->signal_hide().connect(
    sigc::mem_fun(*this, &TableofcontentAction::on_menu_hidden));
  menu_item->set_submenu(*m_menu);
  return menu_item;
}

void TableofcontentAction::on_activate()
{
  Gtk::Action::on_activate();
  update_menu();
}

void TableofcontentAction::update_menu()
{
  m_update_menu_slot(m_menu);
  m_submenu_built = true;
}

void TableofcontentAction::on_menu_hidden()
{
  m_submenu_built = false;
}


TableofcontentMenuItem::TableofcontentMenuItem (
                            const gnote::Note::Ptr & note,
                            const std::string      & header,
                            Header::Type             header_level,
                            int                      header_position)
  : m_note            (note)
  , m_header_position (header_position)
{
  //Create a new menu item, with style depending on the header level:
  /* +-----------------+
     |[] NOTE TITLE    | <---- Title     == note icon  + bold note title
     | > Header 1      | <---- Level_1   == arrow icon + header title
     | > Header 1      |
     |   → header 2    | <---- Level_2   == (no icon)  + indent string + header title
     |   → header 2    |
     |   → header 2    |
     | > Header 1      |
     +-----------------+
   */

  set_use_underline (false); //we don't want potential '_' in the header to be used as mnemonic

  if (header_level == Header::Title) {
    set_image(*manage(new Gtk::Image(gnote::IconManager::obj().get_icon(gnote::IconManager::NOTE, 16))));
    Gtk::Label *label = (Gtk::Label*)get_child();
    label->set_markup("<b>" + header + "</b>");
  }
  else if (header_level == Header::Level_1) {
    set_image(*manage(new Gtk::Image(Gtk::Stock::GO_FORWARD, Gtk::ICON_SIZE_MENU)));
    set_label(header);
  }
  else if (header_level == Header::Level_2) {
    set_label("→  " + header);
  }
}


void TableofcontentMenuItem::on_activate ()
{
  if (!m_note) {
    return;
  }

  // Scroll the TextView and place the cursor on the header
  Gtk::TextIter header_iter;
  header_iter = m_note->get_buffer()->get_iter_at_offset (m_header_position);
  m_note->get_window()->editor()->scroll_to (header_iter,
                                              0.0, //[0.0,0.5] within_margin, margin as a fraction of screen size.
                                              0.0, //[0.0,1.0] horizontal alignment of mark within visible area.
                                              0.0);//[0.0,1.0] vertical alignment of mark within visible area.
  m_note->get_buffer()->place_cursor (header_iter);
}


} //namespace
