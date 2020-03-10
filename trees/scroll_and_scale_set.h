// Copyright 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_TREES_SCROLL_AND_SCALE_SET_H_
#define CC_TREES_SCROLL_AND_SCALE_SET_H_

#include <vector>

#include "cc/cc_export.h"
#include "cc/input/browser_controls_state.h"
#include "cc/input/scroll_snap_data.h"
#include "cc/paint/element_id.h"
#include "cc/trees/layer_tree_host_client.h"
#include "ui/gfx/geometry/scroll_offset.h"
#include "ui/gfx/geometry/vector2d.h"
#include "ui/gfx/transform.h"

namespace cc {

class SwapPromise;

struct CC_EXPORT ScrollAndScaleSet {
  ScrollAndScaleSet();
  ScrollAndScaleSet(const ScrollAndScaleSet&) = delete;
  ~ScrollAndScaleSet();

  ScrollAndScaleSet& operator=(const ScrollAndScaleSet&) = delete;

  struct CC_EXPORT ScrollUpdateInfo {
    ScrollUpdateInfo();
    ScrollUpdateInfo(ElementId id,
                     gfx::ScrollOffset delta,
                     base::Optional<TargetSnapAreaElementIds> snap_target_ids);
    ScrollUpdateInfo(const ScrollUpdateInfo& other);
    ScrollUpdateInfo& operator=(const ScrollUpdateInfo&);
    ElementId element_id;
    gfx::ScrollOffset scroll_delta;

    // The target snap area element ids of the scrolling element.
    // This will have a value if the scrolled element's scroll node has snap
    // container data and the scroll delta is non-zero.
    base::Optional<TargetSnapAreaElementIds> snap_target_element_ids;

    bool operator==(const ScrollUpdateInfo& other) const {
      return element_id == other.element_id &&
             scroll_delta == other.scroll_delta &&
             snap_target_element_ids == other.snap_target_element_ids;
    }
  };

  // The inner viewport scroll delta is kept separate since it's special.
  // Because the inner (visual) viewport's maximum offset depends on the
  // current page scale, the two must be committed at the same time to prevent
  // clamping.
  ScrollUpdateInfo inner_viewport_scroll;

  std::vector<ScrollUpdateInfo> scrolls;
  float page_scale_delta;
  bool is_pinch_gesture_active;

  // Elastic overscroll effect offset delta. This is used only on Mac and shows
  // the pixels that the page is rubber-banned/stretched by.
  gfx::Vector2dF elastic_overscroll_delta;

  // Unconsumed scroll delta used to send overscroll events to the latched
  // element on the main thread;
  gfx::Vector2dF overscroll_delta;

  // The element id of the node to which scrolling is latched. This is used to
  // send overscroll/scrollend DOM events to proper targets whenever needed.
  ElementId scroll_latched_element_id;

  float top_controls_delta;
  float bottom_controls_delta;

  // Used to communicate scrollbar visibility from Impl thread to Blink.
  // Scrollbar input is handled by Blink but the compositor thread animates
  // opacity on scrollbars to fade them out when they're overlay. Blink needs
  // to be told when they're faded out so it can stop handling input for
  // invisible scrollbars.
  struct CC_EXPORT ScrollbarsUpdateInfo {
    ElementId element_id;
    bool hidden = true;

    bool operator==(const ScrollbarsUpdateInfo& other) const {
      return element_id == other.element_id && hidden == other.hidden;
    }
  };
  std::vector<ScrollbarsUpdateInfo> scrollbars;

  std::vector<std::unique_ptr<SwapPromise>> swap_promises;
  BrowserControlsState browser_controls_constraint;
  bool browser_controls_constraint_changed;

  // Set to true when a scroll gesture being handled on the compositor has
  // ended.
  bool scroll_gesture_did_end;

  // Tracks different methods of scrolling (e.g. wheel, touch, precision
  // touchpad, etc.).
  ManipulationInfo manipulation_info;
};

}  // namespace cc

#endif  // CC_TREES_SCROLL_AND_SCALE_SET_H_
