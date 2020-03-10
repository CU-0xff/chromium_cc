// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_TREES_BROWSER_CONTROLS_PARAMS_H_
#define CC_TREES_BROWSER_CONTROLS_PARAMS_H_

#include "cc/cc_export.h"

namespace cc {

struct CC_EXPORT BrowserControlsParams {
  BrowserControlsParams() = default;
  BrowserControlsParams(const BrowserControlsParams& other) = default;
  ~BrowserControlsParams() = default;

  // The height of the top controls (always 0 on platforms where URL-bar hiding
  // isn't supported).
  float top_controls_height = 0.f;

  // The minimum visible height of the top controls.
  float top_controls_min_height = 0.f;

  // The height of the bottom controls.
  float bottom_controls_height = 0.f;

  // The minimum visible height of the bottom controls.
  float bottom_controls_min_height = 0.f;

  // Whether or not the changes to the browser controls heights should be
  // animated.
  bool animate_browser_controls_height_changes = false;

  // Whether or not Blink's viewport size should be shrunk by the height of the
  // URL-bar (always false on platforms where URL-bar hiding isn't supported).
  bool browser_controls_shrink_blink_size = false;

  bool operator==(const BrowserControlsParams& other) const;
  bool operator!=(const BrowserControlsParams& other) const;
};

}  // namespace cc

#endif  // CC_TREES_BROWSER_CONTROLS_PARAMS_H_
