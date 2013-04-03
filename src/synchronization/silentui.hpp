/*
 * gnote
 *
 * Copyright (C) 2012-2013 Aurimas Cernius
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


#ifndef _SYNCHRONIZATION_SILENTUI_HPP_
#define _SYNCHRONIZATION_SILENTUI_HPP_


#include "notemanager.hpp"
#include "syncui.hpp"



namespace gnote {
namespace sync {

  class SilentUI
    : public SyncUI
  {
  public:
    static SyncUI::Ptr create(NoteManager &);
  private:
    explicit SilentUI(NoteManager &);
    virtual void sync_state_changed(SyncState state);
    virtual void note_synchronized(const std::string & noteTitle, NoteSyncType type);
    virtual void note_conflict_detected(NoteManager & manager,
                                        const Note::Ptr & localConflictNote,
                                        NoteUpdate remoteNote,
                                        const std::list<std::string> & noteUpdateTitles);
    virtual void present_ui();
    void on_connecting();
    void on_idle();

    NoteManager & m_manager;
    bool m_ui_disabled;
  };

}
}

#endif
