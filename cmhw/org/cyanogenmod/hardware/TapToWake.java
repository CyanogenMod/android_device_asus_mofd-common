/*
 * Copyright (C) 2014 The CyanogenMod Project
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

package org.cyanogenmod.hardware;

import java.io.File;
import org.cyanogenmod.hardware.util.FileUtils;

public class TapToWake {

    private static final String DCLICK_PATH = "/sys/bus/i2c/devices/i2c-7/7-0038/ftsdclickmode";
    private static final String GESTURES_PATH = "/sys/bus/i2c/devices/i2c-7/7-0038/ftsgesturemode";
    private static final String GESTURES_ON = "1111111";
    private static final String GESTURES_OFF = "0111111";
    private static boolean sEnabled = true;

    public static boolean isSupported() {
        File f1 = new File(DCLICK_PATH);
        File f2 = new File(GESTURES_PATH);
        return f1.exists() && f2.exists();
    }

    public static boolean isEnabled()  {
        return sEnabled;
    }

    public static boolean setEnabled(boolean state)  {
        sEnabled = state;
        return FileUtils.writeLine(DCLICK_PATH, state ? "1" : "0") &&
               FileUtils.writeLine(GESTURES_PATH, state ? GESTURES_ON : GESTURES_OFF);
    }
}
