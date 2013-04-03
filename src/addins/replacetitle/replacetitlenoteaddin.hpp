/*
 * gnote
 *
 * Copyright (C) 2011-2012 Aurimas Cernius
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


#ifndef _REPLACETITLE_ADDIN_HPP_
#define _REPLACETITLE_ADDIN_HPP_

#include <gtkmm/imagemenuitem.h>

#include "sharp/dynamicmodule.hpp"
#include "note.hpp"
#include "noteaddin.hpp"

namespace replacetitle {

class ReplaceTitleModule
  : public sharp::DynamicModule
{
public:
  ReplaceTitleModule();
  virtual const char * id() const;
  virtual const char * name() const;
  virtual const char * description() const;
  virtual const char * authors() const;
  virtual int          category() const;
  virtual const char * version() const;
};
  
DECLARE_MODULE(ReplaceTitleModule);

class ReplaceTitleNoteAddin
  : public gnote::NoteAddin
{
public:
  static ReplaceTitleNoteAddin * create()
  {
    return new ReplaceTitleNoteAddin;
  }
  virtual void initialize();
  virtual void shutdown();
  virtual void on_note_opened();
private:
  void replacetitle_button_clicked();
  void on_note_foregrounded();
  void on_note_backgrounded();

  Gtk::ImageMenuItem *m_menu_item;
};


}

#endif
