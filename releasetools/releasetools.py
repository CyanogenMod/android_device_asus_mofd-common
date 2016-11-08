# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import common
import re
import os

TARGET_DIR = os.getenv('OUT')

def FullOTA_Assertions(info):
  AddIfwiAssertion(info, info.input_zip)

def IncrementalOTA_Assertions(info):
  AddIfwiAssertion(info, info.target_zip)

def AddIfwiAssertion(info, input_zip):
  android_info = input_zip.read("OTA/android-info.txt")
  m = re.search(r"require\s+version-ifwi\s*=\s*(\S+)", android_info)
  if m:
    versions = m.group(1).split("|")
    """Assert that the Ifwi version is one of *versions."""
    if "*" not in versions:
      cmd = ('assert(' +
           ' || '.join(['getprop("sys.ifwi.version") == "%s"'% (b,)
                           for b in versions]) +
           ' || abort("This package supports Ifwi Versions: %s; ' +
           ", ".join(["%s" % (b,) for b in versions]) +
           '; this device has Ifwi version " + getprop("sys.ifwi.version") + ".");' +
           ');')
    info.script.AppendExtra(cmd)

def FullOTA_InstallEnd(info):
  info.script.AppendExtra('assert(run_program("/tmp/install/bin/sign_boot.sh") == 0);')

