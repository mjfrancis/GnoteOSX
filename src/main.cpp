/*
 * gnote
 *
 * Copyright (C) 2013 Aurimas Cernius
 * Copyright (C) 2009 Hubert Figuiere
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

#include "config.h"

#include <glibmm/i18n.h>
#include <gtkmm/main.h>

#include "gnote.hpp"

int main(int argc, char **argv)
{

  const char *runtime_sharedir;
  const char *locale_dir;

  runtime_sharedir = getenv ("GNOTE_SHAREDIR");
  if (runtime_sharedir)
  {
    locale_dir = g_build_filename (runtime_sharedir, "locale", NULL);
  }
  else
  {
    locale_dir = GNOTE_LOCALEDIR;
  }

  bindtextdomain(GETTEXT_PACKAGE, locale_dir);
  bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
  textdomain(GETTEXT_PACKAGE);

  Glib::RefPtr<gnote::Gnote> app = gnote::Gnote::create();
  return app->main(argc, argv);
}
