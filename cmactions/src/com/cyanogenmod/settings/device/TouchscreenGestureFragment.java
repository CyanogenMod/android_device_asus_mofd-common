/*
 * Copyright (C) 2015-2016 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.cyanogenmod.settings.device;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v14.preference.PreferenceFragment;
import android.support.v14.preference.SwitchPreference;
import android.support.v7.preference.Preference;
import android.support.v7.preference.PreferenceCategory;
import android.provider.Settings;
import android.view.ViewGroup;

import cyanogenmod.providers.CMSettings;

public class TouchscreenGestureFragment extends PreferenceFragment {

    private static final String CATEGORY_AMBIENT_DISPLAY = "ambient_display_key";
    private static final String KEY_GESTURE_HAND_WAVE = "gesture_hand_wave";
    private static final String KEY_HAPTIC_FEEDBACK = "touchscreen_gesture_haptic_feedback";
    private static final String KEY_PROXIMITY_WAKE = "proximity_wake_enable";

    private SwitchPreference mAmbientDisplayPreference;
    private SwitchPreference mHandwavePreference;
    private SwitchPreference mProximityWakePreference;
    private SwitchPreference mHapticFeedback;

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
        addPreferencesFromResource(R.xml.touchscreen_panel);

        // Ambient Display
        PreferenceCategory ambientDisplay =
            (PreferenceCategory) findPreference(CATEGORY_AMBIENT_DISPLAY);
        ambientDisplay.setEnabled(isDozeEnabled());
        mHandwavePreference = (SwitchPreference) findPreference(KEY_GESTURE_HAND_WAVE);
        mHandwavePreference.setOnPreferenceChangeListener(mProxPrefListener);
        mProximityWakePreference = (SwitchPreference) findPreference(KEY_PROXIMITY_WAKE);
        mProximityWakePreference.setOnPreferenceChangeListener(mProxPrefListener);
        mHapticFeedback = (SwitchPreference) findPreference(KEY_HAPTIC_FEEDBACK);
        mHapticFeedback.setOnPreferenceChangeListener(mHapticPrefListener);

    }

    @Override
    public void onResume() {
        super.onResume();
        mHapticFeedback.setChecked(CMSettings.System.getInt(getContext().getContentResolver(),
                CMSettings.System.TOUCHSCREEN_GESTURE_HAPTIC_FEEDBACK, 1) != 0);
    }

    private boolean isDozeEnabled() {
        return Settings.Secure.getInt(getContext().getContentResolver(),
                Settings.Secure.DOZE_ENABLED, 1) != 0;
    }

    private Preference.OnPreferenceChangeListener mProxPrefListener =
        new Preference.OnPreferenceChangeListener() {
        @Override
        public boolean onPreferenceChange(Preference preference, Object newValue) {
            if ((boolean) newValue) {
                final String key = preference.getKey();
                if (KEY_GESTURE_HAND_WAVE.equals(key)) {
                    mProximityWakePreference.setChecked(false);
                } else if (KEY_PROXIMITY_WAKE.equals(key)) {
                    mHandwavePreference.setChecked(false);
                }
            }
            return true;
        }
    };

    private Preference.OnPreferenceChangeListener mHapticPrefListener =
        new Preference.OnPreferenceChangeListener() {
        @Override
        public boolean onPreferenceChange(Preference preference, Object newValue) {
            final boolean value = (Boolean) newValue;
            CMSettings.System.putInt(getContext().getContentResolver(),
                    CMSettings.System.TOUCHSCREEN_GESTURE_HAPTIC_FEEDBACK, value ? 1 : 0);
            return true;
        }
    };

}
