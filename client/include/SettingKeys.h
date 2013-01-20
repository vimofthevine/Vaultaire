/*
 * Copyright 2012 Kyle Treubig
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SETTINGKEYS_H
#define SETTINGKEYS_H

namespace vaultaire
{
	// Document library root
	static const QString LIB_ROOT_KEY = "LibraryRootDirectory";
	static const QString DEFAULT_LIB_ROOT = "/tmp";

	// Scanner device
	static const QString SCANNER_DEVICE_KEY = "ScannerDevice";
	static const QString DEFAULT_SCANNER_DEVICE = "";
	// Scan command
	static const QString SCAN_COMMAND_KEY = "ScanCommand";
	static const QString DEFAULT_SCAN_COMMAND = "scanimage -d \%device\%";
	// Scan output suffix
	static const QString SCANNED_SUFFIX_KEY = "ScannedFileSuffix";
	static const QString DEFAULT_SCANNED_SUFFIX = ".pnm";

	// Image conversion
	static const QString DO_CONVERT_KEY = "PerformImageConversion";
	static const QString CONVERT_CMD_KEY = "ImageConversionCommand";
	static const QString DEFAULT_CONVERT_CMD = "convert \%in\% \%out\%";
	static const QString CONVERTED_SUFFIX_KEY = "ConvertedFileSuffix";
	static const QString DEFAULT_CONVERTED_SUFFIX = ".jpg";

	// OCR
	static const QString DO_OCR_KEY = "PerformOCR";
	static const QString OCR_CMD_KEY = "OCRCommand";
	static const QString DEFAULT_OCR_CMD = "gocr -i \%in\% -o \%out\%";
}

#endif
