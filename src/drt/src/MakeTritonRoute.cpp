////////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (c) 2020, The Regents of the University of California
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////////

#include "triton_route/MakeTritonRoute.h"

#include "GraphicsFactory.h"
#include "dr/FlexDR_graphics.h"
#include "ord/OpenRoad.hh"
#include "pa/FlexPA_graphics.h"
#include "sta/StaMain.hh"
#include "ta/FlexTA_graphics.h"
#include "triton_route/TritonRoute.h"

namespace sta {
// Tcl files encoded into strings.
extern const char* drt_tcl_inits[];
}  // namespace sta

extern "C" {
extern int Drt_Init(Tcl_Interp* interp);
}

namespace ord {

drt::TritonRoute* makeTritonRoute()
{
  return new drt::TritonRoute();
}

void deleteTritonRoute(drt::TritonRoute* router)
{
  delete router;
}

void initTritonRoute(OpenRoad* openroad)
{
  // Define swig TCL commands.
  auto tcl_interp = openroad->tclInterp();
  Drt_Init(tcl_interp);
  sta::evalTclInit(tcl_interp, sta::drt_tcl_inits);

  drt::TritonRoute* router = openroad->getTritonRoute();
  std::unique_ptr<drt::AbstractGraphicsFactory> graphics_factory
      = std::make_unique<drt::GraphicsFactory>();

  router->init(openroad->getDb(),
               openroad->getLogger(),
               openroad->getDistributed(),
               openroad->getSteinerTreeBuilder(),
               std::move(graphics_factory));
}

}  // namespace ord
