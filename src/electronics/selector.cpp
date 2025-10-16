#include "electronics/selector.hpp"

#include "autonomous/auton.hpp"
#include "globals.hpp"
#include "main.h" // IWYU pragma: export

Autonomous::AUTON_ROUTINE SelectorScreen::lastAuton;

SelectorScreen::SelectorScreen() {}

/**
 * @brief Updates the user interface for autonomous selection.
 *
 * This function is responsible for updating the content of the dropdown list
 * based on the alliance color. It also handles the state of the skill switch
 * and updates the autonomous routine accordingly.
 *
 * @param e Pointer to the event code.
 */
void SelectorScreen::auton_ui_update(lv_event_t *e) {

  lv_obj_t *tab1 = static_cast<lv_obj_t *>(lv_event_get_current_target(e));
  lv_obj_t *event_obj = static_cast<lv_obj_t *>(lv_event_get_target(e));

  lv_obj_t *autonLabel = lv_obj_get_child(tab1, 2);
  lv_obj_t *allianceSwitch = lv_obj_get_child(tab1, 3);
  lv_obj_t *skillSwitch = lv_obj_get_child(tab1, 4);
  lv_obj_t *auton_dd = lv_obj_get_child(tab1, 5);

  /* Autonomous selector follows this specification for updating the autonomous
   * routine Skills - 0 Red Alliance - 1, 2, 3, ... ,n Blue Alliance - -1, -2,
   * -3, ... ,-n
   */
  if (event_obj == auton_dd) {
    /**
     * Converts dropdown index to 1 based indexing - This is to account for the
     * skills routine which is 0.
     */
    int currentAutonIndex = lv_dropdown_get_selected(auton_dd) + 1;
    bool currentAlliance = lv_obj_has_state(allianceSwitch, LV_STATE_CHECKED);
    globals::alliance = currentAlliance ? globals::SensorColors::BLUE
                                        : globals::SensorColors::RED;
    int autonNum = currentAlliance ? currentAutonIndex * -1 : currentAutonIndex;
    Autonomous::AutonSwitcher(autonNum);
  }
  /* Updates content of the dropdown list based on the alliance color, using
   * the state of the alliance color switch, which is detected through
   * "bubbling".
   */
  else if (event_obj == allianceSwitch) {
    if (lv_obj_has_state(allianceSwitch, LV_STATE_CHECKED)) {
      lv_dropdown_clear_options(auton_dd);
      lv_dropdown_set_options(auton_dd, SelectorScreen::blueAutons);
      lv_obj_set_style_border_color(auton_dd, lv_color_hex(0x0077c8), 0);
    } else {
      lv_dropdown_clear_options(auton_dd);
      lv_dropdown_set_options(auton_dd, SelectorScreen::redAutons);
      lv_obj_set_style_border_color(auton_dd, lv_color_hex(0xd22730), 0);
    }
    // Switches the autonomous routine to the opposite alliance color, accounts
    // for option reset
    Autonomous::AutonSwitcher(Autonomous::auton > 0 ? Autonomous::BLUE_POS
                                                    : Autonomous::RED_NEG);
  } else {
    if (lv_obj_has_state(skillSwitch, LV_STATE_CHECKED)) {
      // Remembers the last competition autonomous
      SelectorScreen::lastAuton = Autonomous::auton;

      // Updates the autonomous routine to skills
      Autonomous::AutonSwitcher(Autonomous::SKILLS);
      lv_obj_add_state(allianceSwitch, LV_STATE_DISABLED);
      lv_obj_add_state(auton_dd, LV_STATE_DISABLED);
    } else {
      Autonomous::AutonSwitcher(SelectorScreen::lastAuton);
      lv_obj_clear_state(allianceSwitch, LV_STATE_DISABLED);
      lv_obj_clear_state(auton_dd, LV_STATE_DISABLED);
    }
  }

  lv_label_set_text_fmt(autonLabel, "Current Auton: %s",
                        Autonomous::autonName.c_str());
}

/**
 * @brief Function to create and initialize the selector screen.
 *
 * This function creates a tab view object and adds two tabs to it: "Autonomous
 * select" and "Drive select". It also adds event callbacks to the tabs for
 * updating the UI. The function creates labels, switches, and a dropdown list
 * for selecting alliance color, skills, and autonomous mode. It also creates a
 * label and a roller for selecting the current drive mode.
 */
void SelectorScreen::selector() {
  /*Create a Tab view object*/
  lv_obj_t *tabview;
  tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 50);

  /*Add 2 tabs*/
  lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Autonomous select");

  /*
   * Both switches are "bubbled" to the tab view. This means that any event on
   * the switches will be updated to the tab view.
   */
  lv_obj_add_event_cb(tab1, auton_ui_update, LV_EVENT_VALUE_CHANGED, NULL);
  // lv_obj_add_event_cb(tab2, drive_update, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_t *tabButtons = lv_tabview_get_tab_btns(tabview);
  lv_obj_set_style_bg_color(tabButtons, lv_color_hex(0x4d0000), 0);
  lv_obj_set_style_text_font(tabButtons, &lv_font_montserrat_18, 0);

  lv_obj_t *label1 = lv_label_create(tab1);
  lv_obj_t *label2 = lv_label_create(tab1);
  lv_obj_t *autonName = lv_label_create(tab1);
  lv_label_set_text(label1, "Alliance");
  lv_label_set_text(label2, "Enable Skills");
  lv_label_set_text_fmt(autonName, "Current Auton: %s",
                        Autonomous::autonName.c_str());
  lv_obj_align(label1, LV_ALIGN_TOP_LEFT, 0, 10);
  lv_obj_align(label2, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_align(autonName, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_text_font(label1, &lv_font_montserrat_20, 0);
  lv_obj_set_style_text_font(label2, &lv_font_montserrat_20, 0);
  lv_obj_set_style_text_font(autonName, &lv_font_montserrat_16, 0);

  /*Add alliance color switch*/
  lv_obj_t *matchSwitch = lv_switch_create(tab1);
  lv_obj_add_flag(matchSwitch, LV_OBJ_FLAG_EVENT_BUBBLE);
  lv_obj_set_style_bg_color(matchSwitch, lv_palette_main(LV_PALETTE_RED),
                            LV_STATE_DEFAULT);
  lv_obj_set_size(matchSwitch, lv_pct(21), lv_pct(27));
  lv_obj_set_style_pad_all(matchSwitch, -5, LV_PART_KNOB);
  lv_obj_align(matchSwitch, LV_ALIGN_TOP_MID, 0, 0);

  /*Add skills switch*/
  lv_obj_t *skillSwitch = lv_switch_create(tab1);
  lv_obj_add_flag(skillSwitch, LV_OBJ_FLAG_EVENT_BUBBLE);
  lv_obj_set_size(skillSwitch, lv_pct(21), lv_pct(27));
  lv_obj_set_style_pad_all(skillSwitch, -5, LV_PART_KNOB);
  lv_obj_align(skillSwitch, LV_ALIGN_CENTER, 0, 0);

  /*Create a drop down list for available autons */
  lv_obj_t *auton_dd = lv_dropdown_create(tab1);
  lv_obj_add_flag(auton_dd, LV_OBJ_FLAG_EVENT_BUBBLE);
  lv_dropdown_set_options(auton_dd, SelectorScreen::redAutons);
  lv_obj_set_style_max_height(auton_dd, 50, 0);
  lv_obj_set_size(auton_dd, lv_pct(35), lv_pct(35));
  lv_obj_set_style_pad_top(auton_dd, 10, 0);
  lv_obj_set_style_pad_bottom(auton_dd, 10, 0);
  lv_obj_set_style_border_width(auton_dd, 4, 0);
  lv_obj_set_style_border_color(auton_dd, lv_color_hex(0xd22730), 0);
  lv_obj_set_style_border_color(auton_dd, lv_color_hex(0x7a7a7a),
                                LV_STATE_DISABLED);
  lv_obj_align(auton_dd, LV_ALIGN_TOP_RIGHT, 0, 0);
}
