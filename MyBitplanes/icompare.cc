/*
  This file is part of bitplanes.

  bitplanes is free software: you can redistribute it and/or modify
  it under the terms of the Lesser GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  bitplanes is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  Lesser GNU General Public License for more details.

  You should have received a copy of the Lesser GNU General Public License
  along with bitplanes.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "icompare.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <string.h>
namespace bp {

bool icompare(const std::string& a, const std::string& b)
{
  return !_strnicmp(a.c_str(), b.c_str(), a.size());
}

bool CaseInsenstiveComparator::operator()(const std::string& a,
                                          const std::string& b) const
{
  return _strnicmp(a.c_str(), b.c_str(), std::min(a.size(), b.size())) < 0;
}

} // bp

