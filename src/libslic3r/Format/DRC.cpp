// DRC.cpp — stub implementation for Draco (.drc) 3D mesh compression.
//
// The upstream OWzx-local DRC.cpp links against Google Draco
// (<draco/compression/encode.h>). Draco is NOT available in the current
// build environment (no headers, no libs in DEPS_PREFIX), so this stub
// provides linkable symbols that always report failure. Callers
// (ProjectServiceMock::exportSelectedObjects with drcFormat=true) check
// the bool return and surface "Export failed" to the user; the STL path
// remains fully functional. When Draco is later provisioned, replace
// this file with the real implementation from 4cb3b9ce.

#include "libslic3r/Format/DRC.hpp"

namespace Slic3r {

bool load_drc(const char * /*path*/, TriangleMesh * /*meshptr*/) { return false; }
bool load_drc(const char * /*path*/, Model * /*model*/, const char * /*object_name*/) { return false; }
bool store_drc(const char * /*path*/, TriangleMesh * /*mesh*/, int /*bits*/, int /*speed*/) { return false; }
bool store_drc(const char * /*path*/, ModelObject * /*model_object*/, int /*bits*/, int /*speed*/) { return false; }
bool store_drc(const char * /*path*/, Model * /*model*/, int /*bits*/, int /*speed*/) { return false; }

} // namespace Slic3r
