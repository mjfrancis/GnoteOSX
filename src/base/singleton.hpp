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




#ifndef __BASE_SINGLETON_HPP__
#define __BASE_SINGLETON_HPP__


#include <cstddef>

namespace base {

  template <typename T>
  class Singleton
  {
  public:
    static T & obj()
      {
        return obj(NULL);
      }
  protected:
    Singleton()
      {
        obj(static_cast<T*>(this));
      }
  private:
    static T & obj(T * inst)
      {
        static T *instance = NULL;
        if(inst) {
          instance = inst;
        }
        return *instance;
      }
  };

}


#endif
